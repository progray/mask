#pragma once

#include <map>

#include <muduo/base/copyable.h>
#include <muduo/base/Types.h>

namespace muduo
{
namespace net
{
class Buffer;
}
}

namespace mask
{

class Response : public muduo::copyable
{
 public:
  virtual void addHeader(const muduo::string& field,
                         const muduo::string& value)
  {
    headers_[field]= value;
  }

  virtual void appendToBuffer(muduo::net::Buffer* buffer) = 0;

  const std::map<muduo::string, muduo::string>& headers() const
  {
    return headers_;
  }

  std::map<muduo::string, muduo::string>& headers()
  {
    return headers_;
  }

 protected:
  std::map<muduo::string, muduo::string> headers_;
}; // Response

} // mask
