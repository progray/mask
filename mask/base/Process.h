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

  int status() const
  {
    return status_;
  }

  bool exited() const
  {
    return WIFEXITED(status_);
  }

  int exit_status() const
  {
    assert(exited());
    return WEXITSTATUS(status_);
  }

  bool signaled() const
  {
    return WIFSIGNALED(status_);
  }

  int term_signal() const
  {
    assert(signaled());
    return WTERMSIG(status_);
  }

#ifdef WCOREDUMP
  bool coredumped() const
  {
    assert(signaled());
    return WCOREDUMP(status_);
  }
#endif

  bool stopped() const
  {
    return WIFSTOPPED(status_);
  }

  int stop_signal() const
  {
    assert(stopped());
    return WSTOPSIG(status_);
  }

  bool continued() const
  {
    return WIFCONTINUED(status_);
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
  int status_;
}; // Process

} // mask
