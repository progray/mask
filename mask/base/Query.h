#pragma once

#include <map>
#include <vector>

#include <muduo/base/copyable.h>
#include <muduo/base/Types.h>
#include <muduo/base/StringPiece.h>

namespace mask
{

class Query : public muduo::copyable
{
 public:
  typedef std::multimap<muduo::string, muduo::string>::const_iterator
          const_iterator;

  typedef std::multimap<muduo::string, muduo::string>::iterator
          iterator;

  bool parse(const muduo::StringPiece& query_string);

  muduo::string operator[](const muduo::string& key) const;

  const_iterator begin() const
  {
    return query_.begin();
  }

  iterator begin()
  {
    return query_.begin();
  }

  const_iterator end() const
  {
    return query_.end();
  }

  iterator end()
  {
    return query_.end();
  }

  const muduo::string& query_string() const
  {
    return query_string_;
  }

  const std::multimap<muduo::string, muduo::string>& query() const
  {
    return query_;
  }

  const std::vector<muduo::string> keys() const
  {
    return keys_;
  }

 private:
  muduo::string query_string_;
  std::multimap<muduo::string, muduo::string> query_;
  std::vector<muduo::string> keys_;
}; // Query

} // mask
