cmake_minimum_required(VERSION 3.23)
project(Labs_secondsemest C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab1_secondsemest src/Lab№1/Source.c src/Lab№1/Header.h src/Lab№1/Func.c)
add_executable(Lab2_1_secondsemest src/Lab№2/Compression/Source.c src/Lab№2/Compression/Compression.c src/Lab№2/Compression/Compression.h src/Lab№2/Compression/List.c src/Lab№2/Compression/List.h src/Lab№2/Compression/Stack.c src/Lab№2/Compression/Stack.h src/Lab№2/Compression/Words.c src/Lab№2/Compression/Words.h)
add_executable(Lab2_2_secondsemest src/Lab№2/decomression/Source.c src/Lab№2/decomression/Decompression.c src/Lab№2/decomression/Decompression.h src/Lab№2/decomression/List.c src/Lab№2/decomression/List.h src/Lab№2/decomression/Words.c src/Lab№2/decomression/Words.h)
add_executable(Lab3_secondsemest src/Lab№3/Source.c src/Lab№3/Header.h src/Lab№3/Func.c src/Lab№3/Menu.c src/Lab№3/Menu.h src/Lab№3/Check_choice.c src/Lab№3/Check_choice.h src/Lab№3/File_picture.h src/Lab№3/File_picture.c)
add_executable(Lab4_secondsemest src/Lab№4/Main.c src/Lab№4/check.c src/Lab№4/check.h src/Lab№4/strings.c src/Lab№4/strings.h src/Lab№4/tree.c src/Lab№4/tree.h)
add_executable(Lab5_secondsemest src/Lab№5/Source.c src/Lab№5/cache.c src/Lab№5/cache.h src/Lab№5/check.c src/Lab№5/check.h src/Lab№5/file.c src/Lab№5/file.h src/Lab№5/hash.c src/Lab№5/hash.h src/Lab№5/main_func.c src/Lab№5/main_func.h)
