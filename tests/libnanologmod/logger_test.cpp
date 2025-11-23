import nanologmod.logger;
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace nanologmod;

TEST_CASE("Logger accepts custom sink") {
    std::vector<std::string> messages;
    Logger logger([&](std::string_view msg) { messages.emplace_back(msg); });

    logger.info("test message");

    REQUIRE(messages.size() == 1);
    REQUIRE(messages[0] == "[INFO] test message");
}

TEST_CASE("Logger formats messages with arguments") {
    std::vector<std::string> messages;
    Logger logger([&](std::string_view msg) { messages.emplace_back(msg); });

    logger.info("value: {}", 42);

    REQUIRE(messages.size() == 1);
    REQUIRE(messages[0] == "[INFO] value: 42");
}

TEST_CASE("Logger level filtering blocks lower levels") {
    std::vector<std::string> messages;
    Logger logger([&](std::string_view msg) { messages.emplace_back(msg); });

    logger.setLevel(Level::Warn);
    logger.debug("debug");
    logger.info("info");
    logger.warn("warn");
    logger.error("error");

    REQUIRE(messages.size() == 2);
    REQUIRE(messages[0] == "[WARN] warn");
    REQUIRE(messages[1] == "[ERROR] error");
}

TEST_CASE("Logger None level blocks all messages") {
    std::vector<std::string> messages;
    Logger logger([&](std::string_view msg) { messages.emplace_back(msg); });

    logger.setLevel(Level::None);
    logger.debug("debug");
    logger.info("info");
    logger.warn("warn");
    logger.error("error");

    REQUIRE(messages.empty());
}

TEST_CASE("Logger raw output bypasses level filtering") {
    std::vector<std::string> messages;
    Logger logger([&](std::string_view msg) { messages.emplace_back(msg); });

    logger.setLevel(Level::None);
    logger.raw("raw message");

    REQUIRE(messages.size() == 1);
    REQUIRE(messages[0] == "raw message");
}

TEST_CASE("Logger setSink changes output destination") {
    std::vector<std::string> messages1;
    std::vector<std::string> messages2;

    Logger logger([&](std::string_view msg) { messages1.emplace_back(msg); });

    logger.info("first");

    logger.setSink([&](std::string_view msg) { messages2.emplace_back(msg); });

    logger.info("second");

    REQUIRE(messages1.size() == 1);
    REQUIRE(messages1[0] == "[INFO] first");
    REQUIRE(messages2.size() == 1);
    REQUIRE(messages2[0] == "[INFO] second");
}
