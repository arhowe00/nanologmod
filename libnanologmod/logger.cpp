module;

#include <format>
#include <functional>
#include <iostream>
#include <string_view>

module nanologmod.logger;

namespace nanologmod {

namespace {

void default_sink(std::string_view message) {
    std::cerr << message << '\n';
}

} // anonymous namespace

Logger::Logger() : level_(Level::Info), sink_(default_sink) {}

Logger::Logger(LogSink sink) : level_(Level::Info), sink_(std::move(sink)) {}

void Logger::setLevel(Level level) {
    level_ = level;
}

void Logger::setSink(LogSink sink) {
    sink_ = std::move(sink);
}

void Logger::log(Level msg_level, std::string_view prefix, std::string_view message) {
    if (msg_level >= level_) {
        sink_(std::format("{}{}", prefix, message));
    }
}

void Logger::raw(std::string_view message) {
    sink_(message);
}

} // namespace nanologmod
