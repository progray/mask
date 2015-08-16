#pragma once

#include <sys/signalfd.h>
#include <signal.h>

#include <map>

#include <boost/scoped_ptr.hpp>

#include <muduo/net/Callbacks.h>
#include <muduo/net/Channel.h>
#include <muduo/net/TcpServer.h>

namespace mask
{

class TcpServer: boost::noncopyable
{
 public:
  typedef boost::function<void (const struct signalfd_siginfo&)> SignalCallback;

  TcpServer(muduo::net::EventLoop* eventloop,
            const muduo::net::InetAddress& addr,
            const muduo::string& name,
            muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort);

  virtual ~TcpServer();

  virtual void onConnection(const muduo::net::TcpConnectionPtr& conn);

  virtual void onMessage(const muduo::net::TcpConnectionPtr& conn,
                         muduo::net::Buffer* buffer,
                         muduo::Timestamp reveiveTime);

  const muduo::string& name() const
  {
    return server_.name();
  }

  muduo::net::EventLoop* eventloop()
  {
    return server_.getLoop();
  }

  void setThreadNum(int numThreads)
  {
    server_.setThreadNum(numThreads);
  }

  void addSignalCallback(int signo, const SignalCallback& cb);

  void start();

  void stop();

 protected:
  void handleRead();

  muduo::net::TcpServer server_;
  int signalFd_;
  boost::scoped_ptr<muduo::net::Channel> signalChannel_;
  std::map<int, SignalCallback> signalCallbacks_;
}; // TcpServer

} // mask
