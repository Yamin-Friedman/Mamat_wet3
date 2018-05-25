cmake_minimum_required(VERSION 3.9)
project(test_squad C)

set(CMAKE_C_STANDARD 99)

add_executable(test_squad main.c ../Soldier.c ../Soldier.h ../APC.c ../APC.h ../defs.h ../List.h ../List.c ../Squad.c ../Squad.h)