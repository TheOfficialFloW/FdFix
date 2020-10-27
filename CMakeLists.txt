cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(fd_fix)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -nostdlib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

add_executable(fd_fix
  main.c
)

target_link_libraries(fd_fix
  SceSysclibForDriver_stub
  taihenForKernel_stub
)

vita_create_self(fd_fix.skprx fd_fix CONFIG exports.yml UNSAFE)

add_custom_target(copy
  COMMAND cp fd_fix.skprx F:/tai/fd_fix.skprx
  DEPENDS fd_fix.skprx
)
