#include <boost/bind.hpp>

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <mask/base/TcpServer.h>

class EchoServer: public mask::TcpServer
{
 public:
  EchoServer(muduo::net::EventLoop* eventloop,
             const muduo::net::InetAddress& addr,
             const muduo::string& name,
             muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort)
    : TcpServer(eventloop, addr, name, option)
  {
    addSignalCallback(SIGUSR1, boost::bind(&EchoServer::handleUsr1, this, _1));
    addSignalCallback(SIGUSR2, boost::bind(&EchoServer::handleUsr2, this, _1));
  }

  ~EchoServer()
  {
  }

  void onConnection(const muduo::net::TcpConnectionPtr& conn)
  {
    LOG_DEBUG << "onConnection pid " << getpid();
  }

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buffer,
                 muduo::Timestamp reveiveTime)
  {
    LOG_DEBUG << "onMessage pid " << getpid()
              << " " << buffer->retrieveAsString(buffer->readableBytes());
  }

  void handleUsr1(const struct signalfd_siginfo& siginfo)
  {
    LOG_DEBUG << siginfo.ssi_signo;
  }

  void handleUsr2(const struct signalfd_siginfo& siginfo)
  {
    LOG_DEBUG << siginfo.ssi_signo;
  }
};

int main(int argc, char* argv[])
{
  muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
  muduo::net::EventLoop eventloop;
  EchoServer server(&eventloop, muduo::net::InetAddress(5813),
                    "EchoServer");
  server.start();
  eventloop.loop();
  return 0;
}
