module;

#include <chrono>

export module nanologmod.stopwatch;

export namespace nanologmod {

/// Measures elapsed time intervals using high-resolution clock.
///
/// Supports lap timing, which measures intervals between checkpoints while
/// keeping the overall timer running (similar to lap features in phone clock apps).
class Stopwatch {
public:
    /// Constructs and starts the stopwatch at the current instant.
    Stopwatch();

    /// Resets the stopwatch and lap timer to begin measuring from the current instant.
    void reset();

    /// Returns the time elapsed since construction or the most recent reset.
    ///
    /// The duration uses floating point seconds and should be converted using
    /// chrono duration casts for specific units (e.g. std::chrono::seconds).
    std::chrono::duration<double> elapsed() const;

    /// Resets the lap timer to the current instant without affecting the main timer.
    void reset_lap();

    /// Returns the time elapsed since the most recent lap reset.
    std::chrono::duration<double> elapsed_lap() const;

private:
    std::chrono::steady_clock::time_point start_;
    std::chrono::steady_clock::time_point start_of_recent_lap_;
};

} // namespace nanologmod
