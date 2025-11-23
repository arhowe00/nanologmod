module;

#include <format>
#include <functional>
#include <string_view>

export module nanologmod.logger;

export namespace nanologmod {

/// Log severity levels in ascending order.
///
/// Messages are filtered based on the minimum level set. Level::None blocks all messages.
enum class Level { Debug, Info, Warn, Error, None };

/// Function type for handling log output.
///
/// Sinks receive formatted messages without trailing newlines.
using LogSink = std::function<void(std::string_view)>;

/// Logger with severity filtering and pluggable output.
///
/// Default configuration outputs to stderr with Info level filtering.
/// Messages are formatted using std::format with severity prefixes like "[INFO] ".
class Logger {
public:
    /// Constructs logger with stderr sink and Info level.
    Logger();

    /// Constructs logger with custom sink and Info level.
    explicit Logger(LogSink sink);

    /// Sets minimum severity level for message filtering.
    void setLevel(Level level);

    /// Replaces the output sink.
    void setSink(LogSink sink);

    /// Logs formatted message at debug level.
    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args);

    /// Logs formatted message at info level.
    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args);

    /// Logs formatted message at warn level.
    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args);

    /// Logs formatted message at error level.
    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args);

    /// Outputs message directly without prefix or level filtering.
    void raw(std::string_view message);

private:
    void log(Level msg_level, std::string_view prefix, std::string_view message);

    Level level_;
    LogSink sink_;
};

template <typename... Args>
void Logger::debug(std::format_string<Args...> fmt, Args&&... args) {
    log(Level::Debug, "[DEBUG] ", std::format(fmt, std::forward<Args>(args)...));
}

template <typename... Args>
void Logger::info(std::format_string<Args...> fmt, Args&&... args) {
    log(Level::Info, "[INFO] ", std::format(fmt, std::forward<Args>(args)...));
}

template <typename... Args>
void Logger::warn(std::format_string<Args...> fmt, Args&&... args) {
    log(Level::Warn, "[WARN] ", std::format(fmt, std::forward<Args>(args)...));
}

template <typename... Args>
void Logger::error(std::format_string<Args...> fmt, Args&&... args) {
    log(Level::Error, "[ERROR] ", std::format(fmt, std::forward<Args>(args)...));
}

} // namespace nanologmod
