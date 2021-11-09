cmake_minimum_required(VERSION 3.21)
project(cpp)

set(CMAKE_CXX_STANDARD 14)


add_executable(mytalk_server network-test/mytalk_server.cpp)
add_executable(mytalk_client network-test/mytalk_client.cpp)
add_executable(echo_splice network-test/echo_splice.cpp)
add_executable(unblockconnect network-test/unblockconnect.cpp)
add_executable(multi_port network-test/multi_port.cpp)
add_executable(unievent network-test/unievent.cpp)
add_executable(connect_timeout network-test/connect_timeout.cpp)
add_executable(nonactive_conn network-test/nonactive_conn.cpp)