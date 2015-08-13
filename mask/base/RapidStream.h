#pragma once

#include <muduo/base/StringPiece.h>
#include <muduo/base/Types.h>

namespace mask
{

class RapidStream
{
 public:
  static const size_t kDefaultCapacity = 1024;

  RapidStream();

  RapidStream& operator << (uint32_t value);
  RapidStream& operator << (uint64_t value);

  RapidStream& operator << (int32_t value);
  RapidStream& operator << (int64_t value);

  RapidStream& operator << (double value);

  RapidStream& operator << (const muduo::StringPiece& s);

  const muduo::string& str() const
  {
    return str_;
  }

 private:
  muduo::string str_;
}; // RapidStream

} // mask
