cmake_minimum_required(VERSION 3.22)
project(1103309___hw12)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1103309___hw12
        "Assignment 12.cpp"
        AvailRoom.cpp
        AvailRoom.h
        AvailRoomDatabase.cpp
        AvailRoomDatabase.h
        Date.cpp
        Date.h
        MakeReservation.cpp
        MakeReservation.h
        Reservation.cpp
        Reservation.h
        ReservationDatabase.cpp
        ReservationDatabase.h
        ReservationInquiry.cpp
        ReservationInquiry.h)
