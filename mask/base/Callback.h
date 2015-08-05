#pragma once

#include <boost/function.hpp>

namespace mask
{

class Request;
class Response;

typedef boost::function<void (const Request&, Response*)> Callback;

} // maksk
