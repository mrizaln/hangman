set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)

FetchContent_Declare(
  linr
  GIT_REPOSITORY https://github.com/mrizaln/linr
  GIT_TAG v0.1.0)
FetchContent_MakeAvailable(linr)

message(STATUS "fetched-libs: created target 'fetch::linr'")
add_library(fetch::linr ALIAS linr)
