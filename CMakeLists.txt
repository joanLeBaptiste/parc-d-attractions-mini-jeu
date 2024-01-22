cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET main.c sous_prog_jeu.c headerBallon.h "Create Crossy Road.c" plateau_prog.c snake_prog.c ranch_jackpot.c taupe_prog.c)
target_link_libraries(PROJET -lmingw32 -lalleg44)
