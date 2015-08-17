#pragma once

#include <muduo/base/Types.h>
#include <muduo/base/StringPiece.h>

namespace mask
{

class Url
{
 public:
  bool parse(const muduo::StringPiece& str);

  const muduo::string& scheme() const
  {
    return scheme_;
  }

  const muduo::string& host() const
  {
    return host_;
  }

  const muduo::string& user() const
  {
    return user_;
  }

  const muduo::string& password() const
  {
    return password_;
  }

  int port() const
  {
    return port_;
  }

  const muduo::string& path() const
  {
    return path_;
  }

  const muduo::string& query_string() const
  {
    return query_string_;
  }

  const muduo::string& fragment() const
  {
    return fragment_;
  }

 private:
  muduo::string scheme_;
  muduo::string host_;
  muduo::string user_;
  muduo::string password_;
  int port_;
  muduo::string path_;
  muduo::string query_string_;
  muduo::string fragment_;
}; // Url

} // mask
