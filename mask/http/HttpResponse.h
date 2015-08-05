#pragma once

#include <mask/base/Response.h>

namespace mask
{
namespace http
{

class HttpResponse: public Response
{
 public:
  virtual void appendToBuffer(muduo::net::Buffer* buffer);

 private:
}; // HttpResponse

} // http
} // mask
