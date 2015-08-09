#pragma once

#include <map>

#include <muduo/base/copyable.h>
#include <muduo/base/Types.h>

#include <mask/base/StringUtil.h>

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
  Response();

  virtual void appendToBuffer(muduo::net::Buffer* buffer) = 0;

  void addHeader(const muduo::string& field,
                 const muduo::string& value)
  {
    headers_[field]= value;
  }

  const std::map<muduo::string, muduo::string>& headers() const
  {
    return headers_;
  }

  std::map<muduo::string, muduo::string>& headers()
  {
    return headers_;
  }

  void setStatusCode(uint32_t statusCode)
  {
    statusCode_ = statusCode;
  }

  void setReasonPhrase(const muduo::string& reasonPhrase)
  {
    reasonPhrase_ = reasonPhrase;
  }

  void setVersion(uint16_t versionMajor, uint16_t versionMinor);

  void setBody(const muduo::string& body)
  {
    body_ = body;
    addHeader("Content-Length", toString(body.size()));
  }

  void setContent(const muduo::string& content)
  {
    setBody(content);
  }

  void setContentType(const muduo::string& content_type)
  {
    addHeader("Content-Type", content_type);
  }

 protected:
  std::map<muduo::string, muduo::string> headers_;
  uint32_t statusCode_;
  muduo::string reasonPhrase_;
  uint16_t versionMajor_;
  uint16_t versionMinor_;
  muduo::string version_;
  muduo::string body_;
}; // Response

} // mask
