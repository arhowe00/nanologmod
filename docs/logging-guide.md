# Logging Guide

"Leveled logging" has two main interaction points: the Logger and the Sink. The
Logger decides what gets output, and the Sink decides where it gets output.

## The Logger

A Logger's level will make it only output messages at least as severe as that
level. For example, construct your logger with `warn` as the level, and nothing
will be output to the Sink when `logger.info("Nothing wrong here!")` is called.

In typical use cases, your application code has a bunch of `logger.*` calls with
certain levels depending on the severity of the information. Then, somewhere
separately, you actually initialize the logger with a specific logging level. A
common example is based on command line flags (`-v` or `-vv`), allowing more or
less of the `logger.*` calls be seen in the Sink. In the example below, only 2
messages will be seen in the Sink.

```cpp
// `my_application_code.cpp`:
void do_a_thing(Logger logger) {
    logger.debug("Loading config");
    logger.info("Server started");
    logger.warn("Retry failed");
    logger.error("Cannot open file");
}

// somewhere in `main.cpp`:
int main() {
    nanologgermod::Logger logger;
    logger.setLevel(nanologgermod::Level::Warn);  // skips info and debug calls
    do_a_thing(logger);
}
```

## The Sink

The Sink decides where output goes. It's a function that receives formatted
strings from the Logger. Default is stderr. Provide a custom function to route
logs anywhere: files, network sockets, databases, multiple destinations. The
Logger formats and filters. The Sink does I/O. 

```cpp
std::ofstream logFile("app.log");

logger.setSink([&](std::string_view msg) {
    logFile << msg << std::endl;
});

// Multiple outputs
logger.setSink([&](std::string_view msg) {
    std::cerr << msg << std::endl;
    logFile << msg << std::endl;
});
```
