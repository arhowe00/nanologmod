# `import nanologgermod;`

nanologgermod is a lightweight >C++20 module that provides thread-safe logging.
It supports configurable log levels, alternate outputs (stdout, file, custom),
formatted output via `std::format`, and includes a stopwatch class for timing
things. For a quick guide to leveled logging, see
[docs/logging-guide.md](docs/logging-guide.md).

## Example

To use it, construct a Logger object and call logging methods with format
strings.

```cpp
nanologgermod::Logger log;                    // Defaults to stdout
log.info("Starting application version {}", "1.0.0");
log.warn("Cache size {} exceeds limit {}", currentSize, maxSize);

nanologgermod::Stopwatch timer;               // Starts immediately
// ... do work ...
log.info("Operation completed in {}", timer.str());
```

Logger outputs are formatted as: `[HH:MM:SS] [LEVEL] Message content`. This is
not configurable.

The Stopwatch provides elapsed time measurements and returns human-readable
strings like "1.45s" or "350ms".

## Using in Your Project

One easy way is to use git submodules with cmake. Assuming your modules are in
`external/`:

```bash
git submodule add https://github.com/arhowe00/nanologgermod.git external/nanologgermod
git submodule update --init --recursive
```

Add to your `CMakeLists.txt`:

```cmake
add_subdirectory(external/nanologgermod/libnanologgermod)
target_link_libraries(your_app PRIVATE nanologgermod)
```

In your C++ file, `import nanologgermod;` should work at the top.

```cpp
import nanologgermod;

int main() {
    nanologgermod::Logger log;
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
nanologgermod::LogSink fileSink = [&](std::string_view msg) {
    logFile << msg << std::endl;
};

nanologgermod::Logger log(fileSink);
log.info("This writes to the file");
```

## Limitations

This module implements minimal, essential logging functionality. This is not a
sophisticated framework with features like log rotation, asynchronous buffering,
or complex filtering. It gives application builders formatted logging without
writing their own implementation.
