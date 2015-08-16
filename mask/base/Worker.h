#pragma once

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <muduo/net/EventLoop.h>

#include <mask/base/Process.h>
#include <mask/base/TcpServer.h>

namespace mask
{

template <typename TTcpServer>
class Worker : public Process
{
 public:
  Worker(const muduo::net::InetAddress& addr,
         const muduo::string& name)
   : Process(boost::bind(&Worker<TTcpServer>::run, this),
                         name + muduo::string(": Worker Process")),
     addr_(addr), name_(name)
  {
  }

  void run()
  {
    eventloop_.reset(new muduo::net::EventLoop());
    server_.reset(new TTcpServer(eventloop_.get(), addr_, name_,
                                 muduo::net::TcpServer::kReusePort));
    server_->start();
    eventloop_->loop();
    exit(0);
  }

 private:
  boost::scoped_ptr<muduo::net::EventLoop> eventloop_;
  muduo::net::InetAddress addr_;
  muduo::string name_;
  boost::scoped_ptr<TTcpServer> server_;
}; // Worker

} // mask
