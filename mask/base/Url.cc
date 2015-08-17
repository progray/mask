#include <http_parser.h>

#include <mask/base/Url.h>

using namespace mask;

bool Url::parse(const muduo::StringPiece& str)
{
  struct http_parser_url url;
  if (http_parser_parse_url(str.data(), str.size(), false, &url))
  {
    return false;
  }

  if (url.field_set & (1 << UF_SCHEMA))
  {
    scheme_.assign(str.data() + url.field_data[UF_SCHEMA].off,
                   url.field_data[UF_SCHEMA].len);
  }

  if (url.field_set & (1 << UF_HOST))
  {
    host_.assign(str.data() + url.field_data[UF_HOST].off,
                 url.field_data[UF_HOST].len);
  }

  if (url.field_set & (1 << UF_PORT))
  {
    port_ = url.port;
  }

  if (url.field_set & (1 << UF_PATH))
  {
    path_.assign(str.data() + url.field_data[UF_PATH].off,
                 url.field_data[UF_PATH].len);
  }

  if (url.field_set & (1 << UF_QUERY))
  {
    query_string_.assign(str.data() + url.field_data[UF_QUERY].off,
                 url.field_data[UF_QUERY].len);
  }

  if (url.field_set & (1 << UF_FRAGMENT))
  {
    fragment_.assign(str.data() + url.field_data[UF_FRAGMENT].off,
                     url.field_data[UF_FRAGMENT].len);
  }

  return true;
}
