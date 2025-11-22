module;

#include <chrono>

export module nanologgermod.stopwatch;

export namespace nanologgermod {

/// Timer for measuring elapsed time.
class Stopwatch {
public:
    /// Start timer.
    Stopwatch();

    /// Reset timer to current instant.
    void reset();

    /// Get elapsed duration.
    std::chrono::duration<double> elapsed() const;

private:
    // TODO: Implementation details
};

} // namespace nanologgermod
