cmake_minimum_required(VERSION 3.30)
project(Dantes_Adventure C)

set(CMAKE_C_STANDARD 11)

add_executable(Dantes_Adventure main.c
        Player.h
        Player.c
        Inventory.h
        Item.h
        Item.c
        Room.h
        Room.c
        Entity.h
        Entity.c
)
