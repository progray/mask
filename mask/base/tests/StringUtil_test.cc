#include <mask/base/StringUtil.h>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace mask;
using muduo::string;
using muduo::StringPiece;

BOOST_AUTO_TEST_CASE(testIsUpper)
{
  BOOST_CHECK(isUpper(StringPiece("")) == false);
  BOOST_CHECK(isUpper(StringPiece("1234abcd")) == false);
  BOOST_CHECK(isUpper(StringPiece("abcdWXYZ")) == false);
  BOOST_CHECK(isUpper(StringPiece("ABCDWXYZ")) == true);
}

BOOST_AUTO_TEST_CASE(testToUpper)
{
  BOOST_CHECK(toUpper("") == "");
  BOOST_CHECK(toUpper("1234abcd") == "1234ABCD");
  BOOST_CHECK(toUpper("1234abcdWXYZ") == "1234ABCDWXYZ");
}

BOOST_AUTO_TEST_CASE(testIsLower)
{
  BOOST_CHECK(isLower(StringPiece("")) == false);
  BOOST_CHECK(isLower(StringPiece("1234abcd")) == false);
  BOOST_CHECK(isLower(StringPiece("abcdWXYZ")) == false);
  BOOST_CHECK(isLower(StringPiece("abcdwxyz")) == true);
  BOOST_CHECK(isLower(StringPiece("ABCDWXYZ")) == false);
}

BOOST_AUTO_TEST_CASE(testToLower)
{
  BOOST_CHECK(toLower("") == "");
  BOOST_CHECK(toLower("1234abcd") == "1234abcd");
  BOOST_CHECK(toLower("1234abcdWXYZ") == "1234abcdwxyz");
}

BOOST_AUTO_TEST_CASE(testSplit)
{
  string query_string;
  std::vector<string> result;

  query_string = "a=1&b=2&c=3";
  result = split(query_string, '&');
  BOOST_CHECK(result.size() == 3);
  BOOST_CHECK(result.at(0) == "a=1");
  BOOST_CHECK(result.at(1) == "b=2");
  BOOST_CHECK(result.at(2) == "c=3");

  result = split(query_string, ' ');
  BOOST_CHECK(result.size() == 1);
  BOOST_CHECK(result.at(0) == query_string);

  result = split(query_string, '=');
  BOOST_CHECK(result.size() == 4);
}
