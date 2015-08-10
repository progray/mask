#include <mask/base/StringUtil.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>
#include <stdio.h>

namespace mask
{

muduo::string toString(uint8_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRIu8, value);
  return buf;
}

muduo::string toString(uint16_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRIu16, value);
  return buf;
}

muduo::string toString(uint32_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRIu32, value);
  return buf;
}

muduo::string toString(uint64_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRIu64, value);
  return buf;
}

muduo::string toString(int8_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRId8, value);
  return buf;
}

muduo::string toString(int16_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRId16, value);
  return buf;
}

muduo::string toString(int32_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRId32, value);
  return buf;
}

muduo::string toString(int64_t value)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRId64, value);
  return buf;
}

}
