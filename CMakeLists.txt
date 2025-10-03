cmake_minimum_required(VERSION 3.0)
project(fox_it14_site)

set(CMAKE_CXX_STANDARD 17)

find_package(Wt REQUIRED)

add_executable(fox_it14_site main.cpp)

target_link_libraries(fox_it14_site PRIVATE Wt::Wt Wt::WtHttp)