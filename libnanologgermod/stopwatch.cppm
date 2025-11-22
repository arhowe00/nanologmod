module;

#include <string>

export module nanologgermod:stopwatch;

export namespace nanologgermod {

class Stopwatch {
public:
    Stopwatch();

    void reset();
    double getSeconds() const;
    std::string str() const;

private:
    // TODO: Implementation details
};

} // namespace nanologgermod
