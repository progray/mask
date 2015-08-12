#include <mask/base/RapidStream.h>
#include <rapidjson/internal/itoa.h>

using namespace mask;

using rapidjson::internal::u32toa;
using rapidjson::internal::u64toa;
using rapidjson::internal::i32toa;
using rapidjson::internal::i64toa;

RapidStream::RapidStream()
{
  str_.reserve(kDefaultCapacity);
}

RapidStream& RapidStream::operator << (uint32_t value)
{
  char buf[32];
  char* end = u32toa(value, buf);
  str_.append(buf, end);
  return *this;
}

RapidStream& RapidStream::operator << (uint64_t value)
{
  char buf[32];
  char* end = u64toa(value, buf);
  str_.append(buf, end);
  return *this;
}

RapidStream& RapidStream::operator << (int32_t value)
{
  char buf[32];
  char* end = i32toa(value, buf);
  str_.append(buf, end);
  return *this;
}

RapidStream& RapidStream::operator << (int64_t value)
{
  char buf[32];
  char* end = i64toa(value, buf);
  str_.append(buf, end);
  return *this;
}

RapidStream& RapidStream::operator << (const muduo::StringPiece& s)
{
  str_.append(s.data(), s.size());
  return *this;
}
