#include <mask/base/Query.h>

#define BOOST_TEST_MAIN
//#define BOOST_TEST_DYN_LINK
//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

using muduo::string;

using mask::Query;

BOOST_AUTO_TEST_CASE(testParse)
{
  Query query;
  BOOST_CHECK(query.parse(""));
  BOOST_CHECK(!query.parse("="));
  BOOST_CHECK(!query.parse("&"));
  BOOST_CHECK(!query.parse("a"));
  BOOST_CHECK(!query.parse("a="));
  BOOST_CHECK(!query.parse("a=&"));
  BOOST_CHECK(!query.parse("&a=1"));
  BOOST_CHECK(query.parse("a=1"));
  BOOST_CHECK(query["a"] == "1");
  BOOST_CHECK(!query.parse("a==1"));
  BOOST_CHECK(!query.parse("a=1="));
  BOOST_CHECK(!query.parse("a&1"));
  BOOST_CHECK(!query.parse("a=1&"));
  BOOST_CHECK(!query.parse("a=1&b=2&"));
  BOOST_CHECK(!query.parse("a=1&b"));
  BOOST_CHECK(query.parse("a=1&b=2"));
  BOOST_CHECK(query["a"] == "1");
  BOOST_CHECK(query["b"] == "2");
  BOOST_CHECK(query.parse("a=1&b=2&c=3"));
  BOOST_CHECK(!query.parse("a=1&b=2c=3"));
  BOOST_CHECK(!query.parse("a=1&&b=2"));
  BOOST_CHECK(!query.parse("a==1&b=2"));
  BOOST_CHECK(!query.parse("a=1&b==2"));
  BOOST_CHECK(query.parse("a=1&b=2&a=3&c=4"));
  BOOST_CHECK(query["a"] == "3");
  BOOST_CHECK(query["b"] == "2");
  BOOST_CHECK(query["c"] == "4");
  BOOST_CHECK(query["d"] == "");
  std::vector<muduo::string> keys;
  keys.push_back("a");
  keys.push_back("b");
  keys.push_back("a");
  keys.push_back("c");
  BOOST_CHECK(query.keys() == keys);
}
