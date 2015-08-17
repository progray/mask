#include <mask/base/Url.h>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using muduo::string;

using mask::Url;

BOOST_AUTO_TEST_CASE(testParse)
{
  Url url;
  bool ok;

  ok = url.parse("https://www.google.com/?gws_rd=ssl#q=mask");
  BOOST_ASSERT(ok);
  BOOST_ASSERT(url.scheme() == "https");
  BOOST_ASSERT(url.host() == "www.google.com");
  BOOST_ASSERT(url.query_string() == "gws_rd=ssl");
  BOOST_ASSERT(url.fragment() == "q=mask");
}
