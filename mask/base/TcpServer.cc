#include <signal.h>
#include <unistd.h>

#include <boost/bind.hpp>

#include <muduo/base/Logging.h>
#include <mask/base/TcpServer.h>

using namespace mask;

TcpServer::TcpServer(muduo::net::EventLoop* eventloop,
                     const muduo::net::InetAddress& addr,
                     const muduo::string& name,
                     muduo::net::TcpServer::Option option)
  : server_(eventloop, addr, name, option),
    signalFd_(-1)
{
}

TcpServer::~TcpServer()
{
  if (signalChannel_)
  {
    signalChannel_->disableAll();
    signalChannel_->remove();
    int ret = ::close(signalFd_);
    if (ret == -1)
    {
      LOG_SYSFATAL << "close failed";
    }
  }
}

void TcpServer::addSignalCallback(int signo, const SignalCallback& cb)
{
  assert(signalCallbacks_.find(signo) == signalCallbacks_.end());
  signalCallbacks_[signo] = cb;
}

void TcpServer::start()
{
  sigset_t mask;
  std::map<int, SignalCallback>::const_iterator citer;
  int ret;

  ret = sigemptyset(&mask);
  if (ret == -1)
  {
    LOG_SYSFATAL << "sigemptyset failed";
  }

  for (citer = signalCallbacks_.begin();
       citer != signalCallbacks_.end();
       citer++)
  {
    ret = sigaddset(&mask, citer->first);
    if (ret == -1)
    {
      LOG_SYSFATAL << "sigaddset failed";
    }
  }

  ret = sigprocmask(SIG_BLOCK, &mask, NULL);
  if (ret == -1)
  {
    LOG_SYSFATAL << "sigprocmask failed";
  }

  signalFd_ = signalfd(-1, &mask, SFD_NONBLOCK | SFD_CLOEXEC);
  if (signalFd_ == -1)
  {
    LOG_SYSFATAL << "signalfd failed";
  }

  signalChannel_.reset(new muduo::net::Channel(eventloop(), signalFd_));
  signalChannel_->setReadCallback(boost::bind(&TcpServer::handleRead, this));
  signalChannel_->enableReading();

  server_.start();
}

void TcpServer::stop()
{
}

void TcpServer::handleRead()
{
  struct signalfd_siginfo siginfo;
  // FIXME
  ssize_t n = read(signalFd_, &siginfo, sizeof siginfo);
  if (n != sizeof siginfo)
  {
    LOG_ERROR << "TcpServer::handleRead() read " << n << " bytes";
  }
  std::map<int, SignalCallback>::const_iterator citer;
  citer = signalCallbacks_.find(siginfo.ssi_signo);
  if (citer == signalCallbacks_.end())
  {
    LOG_ERROR << "TcpServer::handleRead() unknown signo" << siginfo.ssi_signo;
  }
  citer->second(this, siginfo);
}
