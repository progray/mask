#include <mask/base/RapidStream.h>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using mask::RapidStream;
using muduo::string;

BOOST_AUTO_TEST_CASE(test)
{
  RapidStream rs;
  string mask("mask");
  rs << 1234 << -1234 << "abcdABCD" << mask;
  BOOST_CHECK(rs.str() == "1234-1234abcdABCDmask");
}
