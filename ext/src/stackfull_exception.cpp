#include <ext/stackfull_exception.hpp>

#include <boost/stacktrace/stacktrace.hpp>

namespace ext {

StackfullException::StackfullException()
    : trace_(boost::stacktrace::stacktrace{}) {}

StackfullException::StackfullException(std::string_view msg)
    : trace_(boost::stacktrace::stacktrace{}), message_(msg) {}

boost::stacktrace::stacktrace StackfullException::Where() const {
  return trace_;
}

std::string_view StackfullException::What() const { return message_; }

const char* StackfullException::what() const noexcept {
  return message_.c_str();
}

}  // namespace ext
