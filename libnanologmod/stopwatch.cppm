module;

#include <chrono>

export module nanologmod.stopwatch;

export namespace nanologmod {

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

} // namespace nanologmod
