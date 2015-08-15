#pragma once

#include <sys/signalfd.h>

#include <map>

#include <muduo/net/Callbacks.h>
#include <muduo/net/Channel.h>
#include <muduo/net/TcpServer.h>

namespace mask
{

class TcpServer: boost::noncopyable
{
 public:
  //typedef muduo::net::ConnectionCallback ConnectionCallback;
  //typedef muduo::net::MessageCallback MessageCallback;
  typedef boost::function<void (mask::TcpServer*,
                                const struct signalfd_siginfo&)> SignalCallback;

  TcpServer(muduo::net::EventLoop* eventloop,
            const muduo::net::InetAddress& addr,
            const muduo::string& name,
            muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort);

  virtual ~TcpServer();

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

  /// Set connection callback.
  /// Not thread safe.
  void setConnectionCallback(const muduo::net::ConnectionCallback& cb)
  {
    server_.setConnectionCallback(cb);
  }

  /// Set message callback.
  /// Not thread safe.
  void setMessageCallback(const muduo::net::MessageCallback& cb)
  {
    server_.setMessageCallback(cb);
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
