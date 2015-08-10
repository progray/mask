#include <mask/base/StringUtil.h>

#include <rapidjson/internal/itoa.h>

namespace mask
{

muduo::string toString(uint8_t value)
{
  return toString(static_cast<uint32_t>(value));
}

muduo::string toString(uint16_t value)
{
  return toString(static_cast<uint32_t>(value));
}

muduo::string toString(uint32_t value)
{
  char buf[32];
  rapidjson::internal::u32toa(value, buf);
  return buf;
}

muduo::string toString(uint64_t value)
{
  char buf[32];
  rapidjson::internal::u64toa(value, buf);
  return buf;
}

muduo::string toString(int8_t value)
{
  return toString(static_cast<int32_t>(value));
}

muduo::string toString(int16_t value)
{
  return toString(static_cast<int32_t>(value));
}

muduo::string toString(int32_t value)
{
  char buf[32];
  rapidjson::internal::i32toa(value, buf);
  return buf;
}

muduo::string toString(int64_t value)
{
  char buf[32];
  rapidjson::internal::i64toa(value, buf);
  return buf;
}

} // mask
