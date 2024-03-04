@echo off
echo #define STB_IMAGE_IMPLEMENTATION > stbimage.cpp
echo #include "stb_image.h" >> stbimage.cpp
if not exist "..\lib" mkdir ..\lib
g++ -c stbimage.cpp -I..\stb
ar -rvs ..\lib\stbi.lib *.o
del *.o
del *.cpp
