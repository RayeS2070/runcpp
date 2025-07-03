#include <algorithm>
#include <any>
#include <array>
#include <cassert>
#include <cctype>
#include <charconv>
#include <chrono>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <ctime>
#include <entt/entity/fwd.hpp>
#include <exception>
#include <filesystem>
#include <format>
#include <functional>
#include <future>
#include <generator>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <print>
#include <ranges>
#include <shared_mutex>
#include <span>
#include <sstream>
#include <stack>
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include <boost/locale.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/util.hpp>

#include <boost/multi_array.hpp>

#include <boost/exception/exception.hpp>
#include <boost/stacktrace.hpp>
#include <boost/stacktrace/stacktrace.hpp>
#include <boost/stacktrace/this_thread.hpp>

#include <fmt/base.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <spdlog/spdlog.h>

#include <scn/chrono.h>
#include <scn/ranges.h>
#include <scn/scan.h>

#include <entt/entt.hpp>

#include <ext/stackfull_exception.hpp>

// #include <fibonacci.hpp>

template <>
struct fmt::formatter<boost::stacktrace::stacktrace> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.

  auto format(const boost::stacktrace::stacktrace &stacktrace,
              format_context &ctx) const -> format_context::iterator {
    return formatter<string_view>::format(to_string(stacktrace), ctx);
  }
};

namespace {
class Foo {
 public:
  Foo() { std::print("Created\n"); }
  ~Foo() = default;

  Foo(const Foo &) { std::print("True copy foo\n"); }
  Foo(Foo &&) { std::print("Move foo\n"); }
};

auto bar(Foo foo) { return std::make_unique<Foo>(std::move(foo)); }

}  // namespace

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
  try {
    bar({});
  } catch (const ext::StackfullException &sfe) {
    spdlog::error("{} {}", sfe.Where(), sfe.What());
  } catch (const std::exception &e) {
    auto stacktrace = boost::stacktrace::stacktrace::from_current_exception();
    spdlog::error("{} {}", stacktrace, e.what());
  }

  return 0;
}
