#pragma once

#include <boost/noncopyable.hpp>

#include <muduo/net/EventLoop.h>

#include <mask/base/Process.h>
#include <mask/base/TcpServer.h>

namespace mask
{

class WorkerServer : boost::noncopyable
{
 public:
  WorkerServer(const muduo::net::InetAddress& addr,
               const muduo::string& name);

  void start();

  void wait();

  void setConnectionCallback(const muduo::net::ConnectionCallback& cb)
  {
    connectionCallback_ = cb;
  }

  void setMessageCallback(const muduo::net::MessageCallback& cb)
  {
    messageCallback_ = cb;
  }

  mask::Process& process()
  {
    return process_;
  }

 private:
  void run();

  boost::shared_ptr<muduo::net::EventLoop> eventloop_;
  muduo::net::InetAddress addr_;
  muduo::string name_;
  boost::shared_ptr<mask::TcpServer> server_;
  muduo::net::ConnectionCallback connectionCallback_;
  muduo::net::MessageCallback messageCallback_;
  mask::Process process_;
}; // WorkerServer

typedef boost::shared_ptr<WorkerServer> WorkerServerPtr;

} // mask
