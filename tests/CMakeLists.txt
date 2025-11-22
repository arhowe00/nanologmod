include(CTest)
include(Catch)

add_executable(nanologgermod_test libnanologgermod/logger_test.cpp
                                  libnanologgermod/stopwatch_test.cpp)
target_link_libraries(nanologgermod_test PRIVATE nanologgermod
                                                 Catch2::Catch2WithMain)
catch_discover_tests(nanologgermod_test)
