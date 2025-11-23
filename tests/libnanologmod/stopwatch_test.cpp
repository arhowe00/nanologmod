import nanologmod.stopwatch;
#include <chrono>
#include <thread>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace nanologmod;
using namespace std::chrono_literals;

TEST_CASE("Stopwatch starts on construction") {
    Stopwatch sw;
    std::this_thread::sleep_for(10ms);

    REQUIRE(sw.elapsed().count() >= 0.01);
}

TEST_CASE("Stopwatch elapsed increases over time") {
    Stopwatch sw;
    std::this_thread::sleep_for(10ms);
    auto first = sw.elapsed();

    std::this_thread::sleep_for(10ms);
    auto second = sw.elapsed();

    REQUIRE(second > first);
}

TEST_CASE("Stopwatch reset restarts timing") {
    Stopwatch sw;
    std::this_thread::sleep_for(20ms);

    sw.reset();
    auto elapsed = sw.elapsed();

    REQUIRE(elapsed.count() < 0.01);
}

TEST_CASE("Stopwatch lap timing starts with stopwatch") {
    Stopwatch sw;
    std::this_thread::sleep_for(10ms);

    REQUIRE(sw.elapsed_lap().count() >= 0.01);
}

TEST_CASE("Stopwatch reset_lap does not affect main timer") {
    Stopwatch sw;
    std::this_thread::sleep_for(10ms);
    auto before = sw.elapsed();

    sw.reset_lap();
    auto after = sw.elapsed();

    REQUIRE(after >= before);
    REQUIRE(sw.elapsed_lap().count() < after.count());
}

TEST_CASE("Stopwatch reset also resets lap timer") {
    Stopwatch sw;
    std::this_thread::sleep_for(10ms);
    sw.reset_lap();
    std::this_thread::sleep_for(10ms);

    sw.reset();

    REQUIRE(sw.elapsed().count() == Catch::Approx(sw.elapsed_lap().count()).margin(1e-6));
}

TEST_CASE("Stopwatch multiple lap resets") {
    Stopwatch sw;
    std::this_thread::sleep_for(10ms);
    sw.reset_lap();
    std::this_thread::sleep_for(10ms);
    sw.reset_lap();
    std::this_thread::sleep_for(10ms);

    auto lap = sw.elapsed_lap();
    auto total = sw.elapsed();

    REQUIRE(lap.count() >= 0.01);
    REQUIRE(total.count() >= 0.03);
    REQUIRE(lap < total);
}
