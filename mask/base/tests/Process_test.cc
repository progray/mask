#include <mask/base/Process.h>

#include <muduo/base/Logging.h>

using namespace mask;
using namespace muduo;

void helloworld()
{
  LOG_INFO << "Hello World!";
}

int main(int argc, char* argv[])
{
  Logger::setLogLevel(Logger::DEBUG);

  Process process(helloworld, "HelloWorld");
  process.start();
  process.wait();

  return 0;
}
