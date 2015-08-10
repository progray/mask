#include <mask/base/StringUtil.h>

#include <rapidjson/internal/itoa.h>

#include <algorithm>

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

muduo::string toUpper(const muduo::StringPiece& str)
{
  muduo::string s(str.data(), str.size());
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

muduo::string toLower(const muduo::StringPiece& str)
{
  muduo::string s(str.data(), str.size());
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

std::vector<muduo::StringPiece> split(const muduo::StringPiece& str,
                                      const muduo::StringPiece& delim)
{
  std::vector<muduo::StringPiece> result;
  const char* first = str.begin();
  const char* last = str.end();
  const char* pos = std::search(first, last, delim.begin(), delim.end());
  while (pos != last)
  {
    result.push_back(muduo::StringPiece(first, pos - first));
    first = pos + delim.size();
    pos = std::search(first, last, delim.begin(), delim.end());
  }
  result.push_back(muduo::StringPiece(first, pos - first));
  return result;
}

} // mask
