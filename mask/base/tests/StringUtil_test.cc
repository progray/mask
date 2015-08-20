#include <mask/base/StringUtil.h>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace mask;
using muduo::string;
using muduo::StringPiece;

BOOST_AUTO_TEST_CASE(testToString)
{
  BOOST_CHECK(toString(42) == "42");
  BOOST_CHECK(toString(INT64_MIN) == "-9223372036854775808");
  BOOST_CHECK(toString(UINT64_MAX) == "18446744073709551615");
}

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

BOOST_AUTO_TEST_CASE(testSplitStringPiece)
{
  string headers;
  std::vector<StringPiece> result;

  headers = "Host: github.com\r\n"
            "Connection: keep-alive\r\n"
            "DNT: 1\r\n"
            "\r\n";
  result = split(headers, "\r\n");
  BOOST_CHECK(result.size() == 5);
  BOOST_CHECK(result.at(0).as_string() == "Host: github.com");
  BOOST_CHECK(result.at(1).as_string() == "Connection: keep-alive");
  BOOST_CHECK(result.at(2).as_string() == "DNT: 1");
  BOOST_CHECK(result.at(3).as_string() == "");
  BOOST_CHECK(result.at(4).as_string() == "");

  result = split(headers, "=");
  BOOST_CHECK(result.size() == 1);
  BOOST_CHECK(result.at(0) == headers);
}

BOOST_AUTO_TEST_CASE(testLtrim)
{
  string str;

  str = "";
  BOOST_CHECK(ltrim(&str) == "");

  str = "123abc";
  BOOST_CHECK(ltrim(&str) == "123abc");

  str = " 123abc";
  BOOST_CHECK(ltrim(&str) == "123abc");

  str = " \r\r\n\v\f123abc \r\r\n\v\f";
  BOOST_CHECK(ltrim(&str) == "123abc \r\r\n\v\f");
}

BOOST_AUTO_TEST_CASE(testRtrim)
{
  string str;

  str = "";
  BOOST_CHECK(rtrim(&str) == "");

  str = "123abc";
  BOOST_CHECK(rtrim(&str) == "123abc");

  str = " 123abc";
  BOOST_CHECK(rtrim(&str) == " 123abc");

  str = "123abc ";
  BOOST_CHECK(rtrim(&str) == "123abc");

  str = " \r\r\n\v\f123abc \r\r\n\v\f";
  BOOST_CHECK(rtrim(&str) == " \r\r\n\v\f123abc");
}

BOOST_AUTO_TEST_CASE(testTrim)
{
  string str;

  str = "";
  BOOST_CHECK(trim(&str) == "");

  str = "123abc";
  BOOST_CHECK(trim(&str) == "123abc");

  str = " 123abc";
  BOOST_CHECK(trim(&str) == "123abc");

  str = " \r\r\n\v\f123abc \r\r\n\v\f";
  BOOST_CHECK(trim(&str) == "123abc");
}

BOOST_AUTO_TEST_CASE(testJoin)
{
  std::vector<muduo::string> strs;

  BOOST_CHECK(join(strs, " ") == "");

  strs.push_back("a");
  BOOST_CHECK(join(strs, " ") == "a");
  strs.push_back("3");
  BOOST_CHECK(join(strs, "=") == "a=3");
}
