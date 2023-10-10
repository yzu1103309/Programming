cmake_minimum_required(VERSION 3.22)
project(1103309___hw11)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1103309___hw11
        Account.cpp
        Account.h
        "Assignment 11.cpp"
        BalanceInquiry.cpp
        BalanceInquiry.h
        BankDatabase.cpp
        BankDatabase.h
        Deposit.cpp
        Deposit.h
        Transaction.cpp
        Transaction.h
        Withdrawal.cpp
        Withdrawal.h)
