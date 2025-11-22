module;

#include <format>
#include <functional>
#include <string>
#include <string_view>

export module nanologgermod:logger;

export namespace nanologgermod {

enum class Level { Debug, Info, Warn, Error, None };

using LogSink = std::function<void(std::string_view)>;

class Logger {
public:
    Logger();
    explicit Logger(LogSink sink);

    void setLevel(Level level);
    void setSink(LogSink sink);

    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args);

    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args);

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args);

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args);

    void raw(std::string_view message);

private:
    // TODO: Implementation details
};

} // namespace nanologgermod
