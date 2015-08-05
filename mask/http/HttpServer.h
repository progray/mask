#pragma once

#include <muduo/net/TcpServer.h>

#include <mask/base/Callback.h>

namespace mask
{
namespace http
{

class HttpRequest;

class HttpServer : boost::noncopyable
{
  public:
   HttpServer(muduo::net::EventLoop* eventloop,
              const muduo::net::InetAddress& addr,
              const muduo::string& name);

   void start();

   void stop();

   void setThreadNum(int numThreads)
   {
     server_.setThreadNum(numThreads);
   }

   void setCallback(const Callback& cb)
   {
     callback_ = cb;
   }

  private:
   void onConnection(const muduo::net::TcpConnectionPtr& conn);

   void onMessage(const muduo::net::TcpConnectionPtr& conn,
                  muduo::net::Buffer* buffer,
                  muduo::Timestamp reveiveTime);

   void onRequest(const muduo::net::TcpConnectionPtr& conn,
                  const HttpRequest& request);

  private:
   muduo::net::TcpServer server_;
   Callback callback_;
}; // HttpServer

} // http
} // mask
