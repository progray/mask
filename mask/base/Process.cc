#include <sys/types.h>
#include <sys/wait.h>

#include <mask/base/Process.h>

#include <muduo/base/Logging.h>

using namespace mask;

Process::Process(const boost::function<void ()>& func,
                 const muduo::string& name)
  : func_(func), name_(name), started_(false),
    pid_(-1), status_(0)
{
  LOG_DEBUG << "ctor[" << this << "]" << " in process " << getpid();
}

Process::~Process()
{
  LOG_DEBUG << "dtor[" << this << "]" << "in process " << getpid();
}

void Process::start()
{
  assert(!started_);
  started_ = true;

  pid_t pid = fork();
  if (pid < 0)
  {
    started_ = false;
    LOG_SYSFATAL << "fork failed";
    assert(false);
  }
  else if (pid > 0)
  {
    LOG_INFO << "current process pid: " << getpid()
             << " child process pid: " << pid;
    pid_ = pid;
  }
  else
  {
    // child process
    LOG_INFO << "current process pid: " << getpid()
             << " parent process pid: " << getppid();
    func_();
  }
}

void Process::wait()
{
  assert(started_);

  if (pid_ > 0)
  {
    pid_t retval = waitpid(pid_, &status_, 0);
    LOG_DEBUG << "waitpid pid " << pid_ << " in process " << getpid()
              << " status " << status_ << " retval " << retval;
  }
}
