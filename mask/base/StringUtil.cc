#include <mask/base/StringUtil.h>

#include <ctype.h>
#include <functional>
#include <iterator>

#include <rapidjson/internal/itoa.h>
#include <rapidjson/internal/dtoa.h>

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
  char* p = rapidjson::internal::u32toa(value, buf);
  *p = '\0';
  return buf;
}

muduo::string toString(uint64_t value)
{
  char buf[32];
  char* p = rapidjson::internal::u64toa(value, buf);
  *p = '\0';
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
  char* p = rapidjson::internal::i32toa(value, buf);
  *p = '\0';
  return buf;
}

muduo::string toString(int64_t value)
{
  char buf[32];
  char* p = rapidjson::internal::i64toa(value, buf);
  *p = '\0';
  return buf;
}

muduo::string toString(float value)
{
  return toString(static_cast<double>(value));
}

muduo::string toString(double value)
{
  char buf[32];
  char* p = rapidjson::internal::dtoa(value, buf);
  *p = '\0';
  return buf;
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

muduo::string join(const std::vector<muduo::string>& strs,
                   const muduo::string& str)
{
  muduo::string result;

  if (strs.size() == 0)
  {
    return result;
  }

  result.append(strs.at(0));
  for (size_t i = 1; i < strs.size(); i++)
  {
    result.append(str);
    result.append(strs.at(i));
  }

  return result;
}

muduo::string& ltrim(muduo::string* str)
{
  assert(str);
  str->erase(str->begin(), std::find_if(str->begin(), str->end(),
                                        std::not1(std::ptr_fun(isspace))));
  return *str;
}

muduo::string& rtrim(muduo::string* str)
{
  assert(str);
  str->erase(std::find_if(str->rbegin(), str->rend(),
                          std::not1(std::ptr_fun(isspace))).base(), str->end());
  return *str;
}

muduo::string& trim(muduo::string* str)
{
  assert(str);
  ltrim(str);
  rtrim(str);
  return *str;
}

muduo::StringPiece ltrim(const muduo::StringPiece& str)
{
  const char* p = std::find_if(str.begin(), str.end(),
                               std::not1(std::ptr_fun(isspace)));
  return muduo::StringPiece(p, str.end() - p);
}

muduo::StringPiece rtrim(const muduo::StringPiece& str)
{
  const char* p = std::find_if(std::reverse_iterator<const char*>(str.end()),
                               std::reverse_iterator<const char*>(str.begin()),
                               std::not1(std::ptr_fun(isspace))).base();
  return muduo::StringPiece(str.begin(), p - str.begin());
}

muduo::StringPiece trim(const muduo::StringPiece& str)
{
  return rtrim(ltrim(str));
}

} // mask
