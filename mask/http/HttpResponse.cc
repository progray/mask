#include <mask/http/HttpResponse.h>
#include <muduo/net/Buffer.h>

#include <inttypes.h>
#include <stdio.h>

using namespace mask;
using namespace mask::http;

void HttpResponse::appendToBuffer(muduo::net::Buffer* buffer)
{
  char buf[32];
  snprintf(buf, sizeof buf, "HTTP/%d.%d %d ",
           versionMajor_, versionMinor_, statusCode_);
  buffer->append(buf);
  buffer->append(reasonPhrase_);
  buffer->append("\r\n");

  std::map<muduo::string, muduo::string>::const_iterator citer;
  for (citer = headers_.begin();
       citer != headers_.end();
       citer++)
  {
    buffer->append(citer->first);
    buffer->append(": ");
    buffer->append(citer->second);
    buffer->append("\r\n");
  }

  buffer->append("\r\n");
  buffer->append(body_);
}
