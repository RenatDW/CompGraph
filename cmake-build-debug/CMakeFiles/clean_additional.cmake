# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/CompGraph_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/CompGraph_autogen.dir/ParseCache.txt"
  "CompGraph_autogen"
  )
endif()
