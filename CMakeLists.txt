cmake_minimum_required(VERSION 4.2)
project(sistema_gest_o_biblioteca C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(sistema_gest_o_biblioteca
        include/emprestimo.h
        include/livro.h
        include/menu.h
        include/relatorios.h
        include/usuario.h
        src/emprestimo.c
        src/livro.c
        src/main.c
        src/menu.c
        src/relatorios.c
        src/usuario.c)
