#include <boost/bind.hpp>

#include <mask/base/WorkerServer.h>

#include <muduo/base/Logging.h>

using namespace mask;
using namespace muduo;

void onConnection(const muduo::net::TcpConnectionPtr& ptr)
{
  LOG_INFO << "onConnection pid " << getpid();
}

void onMessage(const muduo::net::TcpConnectionPtr& conn,
               muduo::net::Buffer* buffer,
               muduo::Timestamp receiveTime)
{
  LOG_INFO << "onMessage pid " << getpid();
}

int main(int argc, char* argv[])
{
  Logger::setLogLevel(Logger::DEBUG);

  int numWorkers = 4;
  std::vector<boost::shared_ptr<WorkerServer> > wokers;

  for (int i = 0; i < numWorkers; i++)
  {
    WorkerServerPtr worker(new WorkerServer(muduo::net::InetAddress(1327),
                                            "Server"));
    worker->setConnectionCallback(boost::bind(&onConnection, _1));
    worker->setMessageCallback(boost::bind(&onMessage, _1, _2, _3));
    worker->start();

    wokers.push_back(worker);
  }

  for (int i = 0; i < numWorkers; i++)
  {
    wokers.at(i)->wait();
  }

  return 0;
}
