cmake_minimum_required(VERSION 3.7)

set (CMAKE_CXX_STANDARD 14)

if (NOT WINDOWS_STORE AND NOT WINDOWS_PHONE)
  include_directories("/usr/local/include"
  "/usr/local/opt/openssl/include")
  link_directories("/usr/local/lib"
  "/usr/local/opt/openssl/lib")
  add_executable(bing_request bing_request.cc)
  target_link_libraries(bing_request cpprest)
endif()
