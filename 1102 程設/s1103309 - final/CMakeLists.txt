cmake_minimum_required(VERSION 3.22)
project(s1103309___final)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(s1103309___final
        Account.cpp
        Account.h
        AccountDatabase.cpp
        AccountDatabase.h
        Date.cpp
        Date.h
        "Final Exam.cpp"
        Login.cpp
        Login.h
        MakingOrder.cpp
        MakingOrder.h
        Order.cpp
        Order.h
        OrderDatabase.cpp
        OrderDatabase.h)
