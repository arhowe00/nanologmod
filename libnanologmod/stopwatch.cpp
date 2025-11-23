module nanologmod.stopwatch;

namespace nanologmod {

Stopwatch::Stopwatch()
    : start_(std::chrono::steady_clock::now()),
      start_of_recent_lap_(std::chrono::steady_clock::now()) {}

void Stopwatch::reset() {
    start_ = std::chrono::steady_clock::now();
    start_of_recent_lap_ = start_;
}

std::chrono::duration<double> Stopwatch::elapsed() const {
    return std::chrono::steady_clock::now() - start_;
}

void Stopwatch::reset_lap() {
    start_of_recent_lap_ = std::chrono::steady_clock::now();
}

std::chrono::duration<double> Stopwatch::elapsed_lap() const {
    return std::chrono::steady_clock::now() - start_of_recent_lap_;
}

} // namespace nanologmod
