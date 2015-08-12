#pragma once

#include <unistd.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include <muduo/base/Types.h>

namespace mask
{

class Process : boost::noncopyable
{
 public:
  explicit Process(const boost::function<void ()>& func,
                   const muduo::string& name = muduo::string());
  ~Process();

  void start();

  void stop();

  void wait();

  int exitStatus() const
  {
    return exitStatus_;
  }

  const muduo::string& name() const
  {
    return name_;
  }

  pid_t pid() const
  {
    return pid_;
  }

 private:
  boost::function<void ()> func_;
  muduo::string name_;
  bool started_;
  pid_t pid_;
  int exitStatus_;
}; // Process

} // mask
