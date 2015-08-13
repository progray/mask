#include <signal.h>

#include <boost/bind.hpp>

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <mask/base/TcpServer.h>

void handleUsr1(mask::TcpServer*, const struct signalfd_siginfo& siginfo)
{
  LOG_DEBUG << siginfo.ssi_signo;
}

void handleUsr2(mask::TcpServer*, const struct signalfd_siginfo& siginfo)
{
  LOG_DEBUG << siginfo.ssi_signo;
}

int main(int argc, char* argv[])
{
  muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
  muduo::net::EventLoop eventloop;
  mask::TcpServer server(&eventloop, muduo::net::InetAddress(5813),
                         "TcpServer");
  server.addSignalCallback(SIGUSR1, boost::bind(&handleUsr1, _1, _2));
  server.addSignalCallback(SIGUSR2, boost::bind(&handleUsr2, _1, _2));
  server.start();
  eventloop.loop();
  return 0;
}
