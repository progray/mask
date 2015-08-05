#include <mask/app/app.h>

using namespace mask;

void App::dispatchRequest(const Request& reqeust, Response* response)
{
}

void App::operator()(const Request& request, Response* response)
{
  dispatchRequest(request, response);
}
