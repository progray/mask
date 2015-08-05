#pragma once

#include <map>

#include <boost/noncopyable.hpp>

#include <muduo/base/Types.h>

#include <mask/base/Callback.h>

namespace mask
{

class App : boost::noncopyable
{
 public:
  virtual void dispatchRequest(const Request& reqeust,
                               Response* response);

  void operator()(const Request& reqeust, Response* response);

 private:
  std::map<muduo::string, Callback> callbacks_;
}; // App

} // mask
