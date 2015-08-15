#include <boost/bind.hpp>

#include <muduo/base/Logging.h>

#include <mask/base/WorkerServer.h>

using namespace mask;

WorkerServer::WorkerServer(const muduo::net::InetAddress& addr,
                           const muduo::string& name)
  : addr_(addr), name_(name),
    process_(boost::bind(&WorkerServer::run, this),
                         name + muduo::string(": Worker Process"))
{
}

void WorkerServer::start()
{
  process_.start();
}

void WorkerServer::wait()
{
  process_.wait();
}

void WorkerServer::run()
{
  eventloop_.reset(new muduo::net::EventLoop());
  server_.reset(new TcpServer(eventloop_.get(), addr_, name_,
                              muduo::net::TcpServer::kReusePort));
  server_->setConnectionCallback(connectionCallback_);
  server_->setMessageCallback(messageCallback_);
  server_->start();
  eventloop_->loop();
  exit(0);
}
