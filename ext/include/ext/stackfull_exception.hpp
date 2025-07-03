#pragma once

#include <exception>
#include <string_view>

#include <boost/stacktrace.hpp>
#include <boost/stacktrace/stacktrace.hpp>

namespace ext {

class StackfullException : public std::exception {
 public:
  StackfullException();
  ~StackfullException() override = default;

  StackfullException(std::string_view message);

  StackfullException(const StackfullException&) = delete;
  StackfullException(StackfullException&&) noexcept = default;

  StackfullException& operator=(const StackfullException&) = delete;
  StackfullException& operator=(StackfullException&&) noexcept = default;

  virtual boost::stacktrace::stacktrace Where() const;
  virtual std::string_view What() const;

  const char* what() const noexcept override;

 private:
  boost::stacktrace::stacktrace trace_;
  std::string message_;
};

class RuntimeError : public StackfullException {
 public:
  using StackfullException::StackfullException;
};

class LogincError : public StackfullException {
 public:
  using StackfullException::StackfullException;
};

}  // namespace ext