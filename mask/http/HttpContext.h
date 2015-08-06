#pragma once

#include <http_parser.h>

#include <muduo/base/copyable.h>
#include <muduo/base/StringPiece.h>
#include <muduo/base/Timestamp.h>

#include <mask/http/HttpRequest.h>

namespace muduo
{
namespace net
{
class Buffer;
}
}

namespace mask
{
namespace http
{

class HttpContext: public muduo::copyable
{
 public:
  HttpContext();

  HttpContext(const HttpContext& rhs);

  const HttpContext& operator=(const HttpContext& rhs);

  ~HttpContext();

  bool parseRequest(muduo::net::Buffer* buffer,
                    muduo::Timestamp receiveTime);

  const HttpRequest& request() const
  {
    return request_;
  }

  bool requestComplete() const
  {
    return requestComplete_;
  }

 private:
  enum HeaderCallback
  {
    kHeaderNullCallback,
    kHeaderFieldCallback,
    kHeaderValueCallback
  };

  static int onMessageBegin(http_parser* parser);
  static int onUrl(http_parser* parser, const char* at, size_t length);
  static int onStatus(http_parser* parser, const char* at, size_t length);
  static int onHeaderField(http_parser* parser, const char* at, size_t length);
  static int onHeaderValue(http_parser* parser, const char* at, size_t length);
  static int onHeadersComplete(http_parser* parser);
  static int onBody(http_parser* parser, const char* at, size_t length);
  static int onMessageComplete(http_parser* parser);
  static int onChunkHeader(http_parser* parser);
  static int onChunkComplete(http_parser* parser);

  void onMessageBegin();
  void onUrl(const muduo::StringPiece& url);
  void onStatus(const muduo::StringPiece& status);
  void onHeaderField(const muduo::StringPiece& field);
  void onHeaderValue(const muduo::StringPiece& value);
  void onHeadersComplete();
  void onBody(const muduo::StringPiece& body);
  void onMessageComplete();

 private:
  http_parser parser_;
  http_parser_settings settings_;
  HttpRequest request_;
  muduo::Timestamp receiveTime_;
  HeaderCallback lastHeaderCallback_;
  muduo::string field_;
  muduo::string value_;
  bool requestComplete_;
}; // HttpContext

} // http
} // mask
