include(CTest)
include(Catch)

add_executable(nanologmod_test libnanologmod/logger_test.cpp
                                  libnanologmod/stopwatch_test.cpp)
target_link_libraries(nanologmod_test PRIVATE nanologmod
                                                 Catch2::Catch2WithMain)
catch_discover_tests(nanologmod_test)
