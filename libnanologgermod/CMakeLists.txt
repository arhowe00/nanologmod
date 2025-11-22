add_library(nanologgermod)

target_sources(
  nanologgermod PUBLIC FILE_SET CXX_MODULES FILES logger.cppm stopwatch.cppm)

target_compile_features(nanologgermod PUBLIC cxx_std_23)

target_compile_options(nanologgermod PRIVATE -Wdocumentation)
