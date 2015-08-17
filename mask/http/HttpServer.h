#pragma once

#include <muduo/net/TcpServer.h>

#include <mask/base/Callback.h>

namespace mask
{
namespace http
{

class HttpRequest;
class HttpResponse;

class HttpServer : boost::noncopyable
{
  public:
   typedef boost::function<void (const HttpRequest&,
                                       HttpResponse*)> HttpCallback;

   HttpServer(muduo::net::EventLoop* eventloop,
              const muduo::net::InetAddress& addr,
              const muduo::string& name,
              muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort);

   void start();

   void stop();

   void setThreadNum(int numThreads)
   {
     server_.setThreadNum(numThreads);
   }

   void setHttpCallback(const HttpCallback& cb)
   {
     httpCallback_ = cb;
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
   HttpCallback httpCallback_;
}; // HttpServer

} // http
} // mask
