add_library(nanologmod)

target_sources(
  nanologmod
  PUBLIC FILE_SET CXX_MODULES FILES logger.cppm stopwatch.cppm
  PRIVATE stopwatch.cpp)

target_compile_features(nanologmod PUBLIC cxx_std_23)

target_compile_options(nanologmod PRIVATE -Wdocumentation)
