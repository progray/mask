#include <mask/http/HttpServer.h>
#include <muduo/net/EventLoop.h>

using namespace mask;
using namespace mask::http;

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
  EventLoop eventloop;
  HttpServer server(&eventloop, InetAddress(8000), "HttpServer");
  server.start();
  eventloop.loop();

  return 0;
}
