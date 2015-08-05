#pragma once

#include <mask/base/Request.h>

namespace mask
{
namespace http
{

class HttpRequest : public Request
{
 public:
  virtual void appendToBuffer(muduo::net::Buffer* buffer);

 private:
}; // HttpRequest

} // http
} // mask
