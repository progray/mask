#pragma once

#include <muduo/base/Types.h>
#include <muduo/base/StringPiece.h>

// https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#64-bit_Portability

// printf macros for size_t, in the style of inttypes.h
#ifdef _LP64
#define __PRIS_PREFIX "z"
#else
#define __PRIS_PREFIX
#endif

// Use these macros after a % in a printf format string
// to get correct 32/64 bit behavior, like this:
// size_t size = records.size();
// printf("%"PRIuS"\n", size);

#define PRIdS __PRIS_PREFIX "d"
#define PRIxS __PRIS_PREFIX "x"
#define PRIuS __PRIS_PREFIX "u"
#define PRIXS __PRIS_PREFIX "X"
#define PRIoS __PRIS_PREFIX "o"

namespace mask
{

muduo::string toString(uint8_t value);
muduo::string toString(uint16_t value);
muduo::string toString(uint32_t value);
muduo::string toString(uint64_t value);

muduo::string toString(int8_t value);
muduo::string toString(int16_t value);
muduo::string toString(int32_t value);
muduo::string toString(int64_t value);

bool isUpper(const muduo::StringPiece& str);
bool isUpper(const muduo::string& str);
muduo::string toUpper(const muduo::string& str);
void toUpper(muduo::string* str);

bool isLower(const muduo::StringPiece& str);
bool isLower(const muduo::string& str);
muduo::string toLower(const muduo::string& str);
void toLower(muduo::string* str);

} // mask
