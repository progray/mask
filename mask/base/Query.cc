#include <mask/base/Query.h>

#include <algorithm>

using namespace mask;

bool Query::parse(const muduo::StringPiece& query_string)
{
  static const char* kAssignment = "=";
  static const char* kAmpersand = "&";

  const char* key = query_string.begin();
  const char* value = query_string.end();
  const char* amp;
  const char* assign;
  const char* tmp;

  query_.clear();
  keys_.clear();

  do
  {
    amp = std::search(key, query_string.end(),
                      kAmpersand, kAmpersand + 1);

    assign = std::search(key, amp,
                         kAssignment, kAssignment + 1);

    if (assign < amp)
    {
      if (assign - key > 0 && amp - assign > 1)
      {
        value = assign + 1;
        tmp = std::search(value, amp,
                          kAssignment, kAssignment + 1);
        if (tmp != amp)
        {
          return false;
        }
        keys_.push_back(muduo::string(key, assign - key));
        query_.insert(make_pair(muduo::string(key, assign - key),
                                muduo::string(value, amp - value)));
      }
      else
      {
        return false;
      }
    }
    else
    {
      if (key != query_string.end())
      {
        return false;
      }

      if (value != query_string.end())
      {
        return false;
      }
    }
    key = amp + 1;
  } while (amp != query_string.end());

  query_string_ = query_string.as_string();

  return true;
}

muduo::string Query::operator[](const muduo::string& key) const
{
  muduo::string value;

  Query::const_iterator citer;
  std::pair<Query::const_iterator,
            Query::const_iterator> range = query_.equal_range(key);

  for (citer = range.first; citer != range.second; citer++)
  {
    value = citer->second;
  }

  return value;
}
