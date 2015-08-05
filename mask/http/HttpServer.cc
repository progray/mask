#include <mask/http/HttpServer.h>

#include <boost/any.hpp>
#include <boost/bind.hpp>

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <mask/http/HttpContext.h>
#include <mask/http/HttpResponse.h>

using namespace mask;
using namespace mask::http;

HttpServer::HttpServer(muduo::net::EventLoop* eventloop,
                       const muduo::net::InetAddress& addr,
                       const muduo::string& name)
  : server_(eventloop, addr, name)
{
  server_.setConnectionCallback(boost::bind(&HttpServer::onConnection,
                                            this, _1));
  server_.setMessageCallback(boost::bind(&HttpServer::onMessage,
                                         this, _1, _2, _3));
}

void HttpServer::start()
{
  server_.start();
}

void HttpServer::stop()
{
}

void HttpServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
  if (conn->connected())
  {
    conn->setContext(HttpContext());
  }
}

void HttpServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buffer,
                           muduo::Timestamp reveiveTime)
{
  HttpContext* context = boost::any_cast<HttpContext>(conn->getMutableContext());
  if (!context->parseRequest(buffer, reveiveTime))
  {
    conn->shutdown();
  }
  if (context->requestComplete())
  {
    onRequest(conn, context->request());
  }
}

void HttpServer::onRequest(const muduo::net::TcpConnectionPtr& conn,
                           const HttpRequest& request)
{
  LOG_INFO << "HttpServer::onRequest reveiveTime: "
           << request.receiveTime().toFormattedString();
}
