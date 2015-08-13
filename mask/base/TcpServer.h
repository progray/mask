#pragma once

#include <sys/signalfd.h>

#include <map>

#include <muduo/net/Channel.h>
#include <muduo/net/TcpServer.h>

namespace mask
{

class TcpServer: boost::noncopyable
{
 public:
  typedef boost::function<void (mask::TcpServer*,
                                const struct signalfd_siginfo&)> SignalCallback;

  TcpServer(muduo::net::EventLoop* eventloop,
            const muduo::net::InetAddress& addr,
            const muduo::string& name);

  virtual ~TcpServer();

  muduo::net::EventLoop* eventloop()
  {
    return server_.getLoop();
  }

  void addSignalCallback(int signo, const SignalCallback& cb);

  virtual void start();
  virtual void stop();

  virtual void handleRead();

 protected:
  muduo::net::TcpServer server_;
  int signalFd_;
  boost::shared_ptr<muduo::net::Channel> signalChannel_;
  std::map<int, SignalCallback> signalCallbacks_;
}; // TcpServer

} // mask
