#include <boost/bind.hpp>

#include <mask/base/TcpServer.h>
#include <mask/base/Worker.h>

#include <muduo/base/Logging.h>

using namespace mask;
using namespace muduo;

class EchoServer: public mask::TcpServer
{
 public:
  EchoServer(muduo::net::EventLoop* eventloop,
             const muduo::net::InetAddress& addr,
             const muduo::string& name,
             muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort)
    : TcpServer(eventloop, addr, name, option)
  {
    setThreadNum(2);
  }

  ~EchoServer()
  {
  }

  void onConnection(const muduo::net::TcpConnectionPtr& conn)
  {
    LOG_DEBUG << "onConnection pid " << getpid();
  }

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buffer,
                 muduo::Timestamp reveiveTime)
  {
    LOG_DEBUG << "onMessage pid " << getpid()
              << " " << buffer->retrieveAsString(buffer->readableBytes());
  }
};

int main(int argc, char* argv[])
{
  Logger::setLogLevel(Logger::DEBUG);

  int numWorkers = 4;
  std::vector<boost::shared_ptr<Worker<EchoServer> > > wokers;

  for (int i = 0; i < numWorkers; i++)
  {
    boost::shared_ptr<Worker<EchoServer> > worker(new Worker<EchoServer>(
                                                  muduo::net::InetAddress(1327),
                                                  "Server"));
    worker->start();
    wokers.push_back(worker);
  }

  for (int i = 0; i < numWorkers; i++)
  {
    wokers.at(i)->wait();
  }

  return 0;
}
