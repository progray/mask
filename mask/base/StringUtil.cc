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

bool isUpper(const muduo::StringPiece& str)
{
  if (str.empty())
  {
    return false;
  }

  for (int i = 0; i < str.size(); i++)
  {
    if (!('A' <= str[i] && str[i] <= 'Z'))
    {
      return false;
    }
  }

  return true;
}

bool isUpper(const muduo::string& str)
{
  return isUpper(muduo::StringPiece(str));
}

muduo::string toUpper(const muduo::string& str)
{
  muduo::string s(str);
  toUpper(&s);
  return s;
}

void toUpper(muduo::string* str)
{
  assert(str);
  for (size_t i = 0; i < str->size(); i++)
  {
    if ('a' <= str->at(i) && str->at(i) <= 'z')
    {
      str->at(i) -= 32;
    }
  }
}

bool isLower(const muduo::StringPiece& str)
{
  if (str.empty())
  {
    return false;
  }

  for (int i = 0; i < str.size(); i++)
  {
    if (!('a' <= str[i] && str[i] <= 'z'))
    {
      return false;
    }
  }

  return true;
}

bool isLower(const muduo::string& str)
{
  return isLower(muduo::StringPiece(str));
}

muduo::string toLower(const muduo::string& str)
{
  muduo::string s(str);
  toLower(&s);
  return s;
}

void toLower(muduo::string* str)
{
  assert(str);
  for (size_t i = 0; i < str->size(); i++)
  {
    if ('A' <= str->at(i) && str->at(i) <= 'Z')
    {
      str->at(i) += 32;
    }
  }
}


std::vector<muduo::string> split(const muduo::string& str, char delim)
{
  std::vector<muduo::string> result;
  size_t begin = 0;
  size_t pos = str.find(delim, begin);
  while (pos != muduo::string::npos)
  {
    result.push_back(str.substr(begin, pos - begin));
    begin = pos + 1;
    pos = str.find(delim, begin);
  }
  result.push_back(str.substr(begin));
  return result;
}

} // mask
