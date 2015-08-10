#include <mask/http/HttpContext.h>

#include <stdio.h>

#include <muduo/net/Buffer.h>

#define BOOST_TEST_MAIN
//#define BOOST_TEST_DYN_LINK
//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

using muduo::string;
using muduo::Timestamp;
using muduo::net::Buffer;

using mask::http::HttpContext;
using mask::http::HttpRequest;

BOOST_AUTO_TEST_CASE(testParseRequestAllInOne)
{
  HttpContext context;
  Buffer buffer;
  buffer.append("GET /decimalbell HTTP/1.1\r\n"
                "Host: github.com\r\n"
                "\r\n");

  BOOST_CHECK(context.parseRequest(&buffer, Timestamp::now()));
  BOOST_CHECK(context.requestComplete());
  const HttpRequest& request = context.request();
  BOOST_CHECK_EQUAL(request.getHeader("Host"), string("github.com"));
  BOOST_CHECK_EQUAL(request.getHeader("User-Agent"), string(""));
}

BOOST_AUTO_TEST_CASE(testParseRequestInTwoPieces)
{
  string all("GET /decimalbell HTTP/1.1\r\n"
             "Host: github.com\r\n"
             "\r\n");

  for (size_t sz = 0; sz < all.size(); ++sz)
  {
    HttpContext context;
    Buffer buffer;
    buffer.append(all.c_str(), sz);
    BOOST_CHECK(context.parseRequest(&buffer, Timestamp::now()));
    BOOST_CHECK(!context.requestComplete());

    buffer.append(all.c_str() + sz, all.size() - sz);
    BOOST_CHECK(context.parseRequest(&buffer, Timestamp::now()));
    BOOST_CHECK(context.requestComplete());
    const HttpRequest& request = context.request();
    BOOST_CHECK_EQUAL(request.getHeader("Host"), string("github.com"));
    BOOST_CHECK_EQUAL(request.getHeader("User-Agent"), string(""));
  }
}

BOOST_AUTO_TEST_CASE(testParseRequestEmptyHeaderValue)
{
  HttpContext context;
  Buffer buffer;
  buffer.append("GET /decimalbell HTTP/1.1\r\n"
                "Host: github.com\r\n"
                "User-Agent:\r\n"
                "Accept-Encoding: \r\n"
                "\r\n");

  BOOST_CHECK(context.parseRequest(&buffer, Timestamp::now()));
  BOOST_CHECK(context.requestComplete());
  const HttpRequest& request = context.request();
  BOOST_CHECK_EQUAL(request.getHeader("Host"), string("github.com"));
  BOOST_CHECK_EQUAL(request.getHeader("User-Agent"), string(""));
  BOOST_CHECK_EQUAL(request.getHeader("Accept-Encoding"), string(""));
}

BOOST_AUTO_TEST_CASE(testParseRequestFailed)
{
  HttpContext context;
  Buffer buffer;
  buffer.append("GET /decimalbell HTTP/1.1\r\n"
                "Host: github.com\r\n"
                "User-Agent\r\n"
                "\r\n");

  BOOST_CHECK(!context.parseRequest(&buffer, Timestamp::now()));
}

BOOST_AUTO_TEST_CASE(testParseRequestQuery)
{
  HttpContext context;
  Buffer buffer;
  buffer.append("GET /decimalbell?tab=repositories HTTP/1.1\r\n"
                "Host: github.com\r\n"
                "\r\n");

  BOOST_CHECK(context.parseRequest(&buffer, Timestamp::now()));
  BOOST_CHECK(context.requestComplete());
  const HttpRequest& request = context.request();
  BOOST_CHECK_EQUAL(request.getHeader("Host"), string("github.com"));
  BOOST_CHECK_EQUAL(request.getHeader("User-Agent"), string(""));
  BOOST_CHECK_EQUAL(request.get()["tab"], "repositories");
}

BOOST_AUTO_TEST_CASE(testParseRequestPost)
{
  HttpContext context;

  muduo::string body("tab=repositories");
  char content_length[64];
  snprintf(content_length, 64, "Content-Length: %d\r\n",
           static_cast<int>(body.size()));

  Buffer buffer;
  buffer.append("POST /decimalbell HTTP/1.1\r\n"
                "Host: github.com\r\n");
  buffer.append(content_length);
  //buffer.append("Content-Type: application/x-www-form-urlencoded\r\n");
  buffer.append("\r\n");
  buffer.append(body);

  BOOST_CHECK(context.parseRequest(&buffer, Timestamp::now()));
  BOOST_CHECK(context.requestComplete());
  const HttpRequest& request = context.request();
  BOOST_CHECK_EQUAL(request.getHeader("Host"), string("github.com"));
  BOOST_CHECK_EQUAL(request.getHeader("User-Agent"), string(""));
  BOOST_CHECK_EQUAL(request.method(), "POST");
  BOOST_CHECK_EQUAL(request.post()["tab"], "repositories");
  BOOST_CHECK_EQUAL(request.body(), body);
}

BOOST_AUTO_TEST_CASE(testVersion)
{
  HttpRequest request;
  BOOST_CHECK(request.versionMajor() == 1);
  BOOST_CHECK(request.versionMinor() == 1);
  BOOST_CHECK(request.version() == "1.1");
}
