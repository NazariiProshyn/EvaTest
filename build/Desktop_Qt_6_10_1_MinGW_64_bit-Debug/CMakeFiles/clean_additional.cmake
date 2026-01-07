# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\EvaTest_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\EvaTest_autogen.dir\\ParseCache.txt"
  "EvaTest_autogen"
  )
endif()
