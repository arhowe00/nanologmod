module;

#include <format>
#include <functional>
#include <string>
#include <string_view>

export module nanologmod.logger;

export namespace nanologmod {

/// Log severity levels.
enum class Level { Debug, Info, Warn, Error, None };

/// Function type for handling log output.
using LogSink = std::function<void(std::string_view)>;

/// Logger with severity filtering and custom output.
class Logger {
public:
    /// Construct with stderr sink.
    Logger();

    /// Construct with custom sink.
    explicit Logger(LogSink sink);

    /// Set minimum severity level.
    void setLevel(Level level);

    /// Set output sink.
    void setSink(LogSink sink);

    /// Log at debug level.
    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args);

    /// Log at info level.
    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args);

    /// Log at warn level.
    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args);

    /// Log at error level.
    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args);

    /// Output unformatted message.
    void raw(std::string_view message);

private:
    // TODO: Implementation details
};

} // namespace nanologmod
