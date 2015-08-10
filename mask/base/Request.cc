#include <mask/base/Request.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>
#include <stdio.h>

using namespace mask;

Request::Request()
{
  setVersion(1, 1);
}

void Request::setVersion(uint16_t versionMajor, uint16_t versionMinor)
{
  char buf[32];
  snprintf(buf, sizeof buf, "%"PRIu16".%"PRIu16, versionMajor, versionMinor);
  version_.assign(buf);
  versionMajor_ = versionMajor;
  versionMinor_ = versionMinor;
}
