set(FETCHCONTENT_QUIET FALSE)

include(FetchContent)

FetchContent_Declare(
  cppread
  GIT_REPOSITORY https://github.com/mrizaln/cppread
  GIT_TAG 25fdd213ef352d1947b248e3bfedf70e6e2be701)
FetchContent_MakeAvailable(cppread)

add_library(fetch::cppread ALIAS cppread)
