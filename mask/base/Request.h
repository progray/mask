#pragma once

#include <map>

#include <muduo/base/copyable.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/Types.h>

#include <mask/base/Query.h>

namespace muduo
{
namespace net
{
class Buffer;
}
}

namespace mask
{

class Request : public muduo::copyable
{
 public:
  virtual void appendToBuffer(muduo::net::Buffer* buffer) = 0;

  void addHeader(const muduo::string& field,
                 const muduo::string& value)
  {
    headers_[field]= value;
  }

  muduo::string getHeader(const muduo::string& field) const
  {
    muduo::string value;
    std::map<muduo::string, muduo::string>::const_iterator citer = headers_.find(field);
    if (citer != headers_.end())
    {
      value = citer->second;
    }
    return value;
  }

  const std::map<muduo::string, muduo::string>& headers() const
  {
    return headers_;
  }

  std::map<muduo::string, muduo::string>& headers()
  {
    return headers_;
  }

  muduo::Timestamp receiveTime() const
  {
    return receiveTime_;
  }

  void setReceiveTime(muduo::Timestamp receiveTime)
  {
    receiveTime_ = receiveTime;
  }

  const muduo::string& method() const
  {
    return method_;
  }

  void setMethod(const muduo::string& method)
  {
    method_ = method;
  }

  Query& get()
  {
    return get_;
  }

  const Query& get() const
  {
    return get_;
  }

  Query& post()
  {
    return post_;
  }

  const Query& post() const
  {
    return post_;
  }

  const muduo::string& body() const
  {
    return body_;
  }

  void setBody(const muduo::string& body)
  {
    body_ = body;
  }

 protected:
  muduo::string method_;
  std::map<muduo::string, muduo::string> headers_;
  muduo::Timestamp receiveTime_;
  muduo::string body_;
  Query get_;
  Query post_;
}; // Request

} // mask
