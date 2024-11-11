cmake_minimum_required(VERSION 3.29)
project(restaurante)

set(CMAKE_CXX_STANDARD 20)

add_executable(cadastro_bolsistas main.c
        main.c
        fila.c
        fila.h
        pilha.c
        pilha.h
        acoes.c
        acoes.h)
