# `import nanologmod;`

nanologmod is a lightweight >C++20 module that provides thread-safe logging.
It supports configurable log levels, alternate outputs (stdout, file, custom),
formatted output via `std::format`, and includes a stopwatch class for timing
things. For a quick guide to leveled logging, see
[docs/logging-guide.md](docs/logging-guide.md).

## Example

To use it, construct a Logger object and call logging methods with format
strings.

```cpp
nanologmod::Logger log;                    // Defaults to stderr
log.info("Starting application version {}", "1.0.0");
log.warn("Cache size {} exceeds limit {}", currentSize, maxSize);

nanologmod::Stopwatch timer;               // Starts immediately
// ... do work ...
log.info("Operation completed in {:.2f}s", timer.elapsed().count());
```

Logger outputs are formatted as `[HH:MM:SS] [LEVEL] Message content`. Stopwatch
methods return `std::chrono::duration<double>` representing seconds. Call
`.count()` on the result to get a numeric value for formatting or comparison.

## Using in Your Project

One easy way is to use git submodules with cmake. Assuming your modules are in
`external/`:

```bash
git submodule add https://github.com/arhowe00/nanologmod.git external/nanologmod
git submodule update --init --recursive
```

Add to your `CMakeLists.txt`:

```cmake
add_subdirectory(external/nanologmod/libnanologmod)
target_link_libraries(your_app PRIVATE nanologmod)
```

In your C++ file, `import nanologmod;` should work at the top.

```cpp
import nanologmod;

int main() {
    nanologmod::Logger log;
    log.info("Application started");
}
```

## Custom Sinks

Sinks let you log to alternative outputs than stdout. For instance, a file.
They are simple functions: `std::function<void(std::string_view)>`. This enables
file logging, network logging, dual output, or any custom behavior without
modifying the logger.

```cpp
std::ofstream logFile("app.log");
nanologmod::LogSink fileSink = [&](std::string_view msg) {
    logFile << msg << std::endl;
};

nanologmod::Logger log(fileSink);
log.info("This writes to the file");
```

## Limitations

This module implements minimal, essential logging functionality. This is not a
sophisticated framework with features like log rotation, asynchronous buffering,
or complex filtering. It gives application builders formatted logging without
writing their own implementation.
