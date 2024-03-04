if not exist "..\lib" mkdir ..\lib
if not exist "..\assimp\build" mkdir ..\assimp\build

cmake -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=OFF -DASSIMP_INSTALL=OFF -DASSIMP_BUILD_TESTS=OFF ..\assimp\CMakeLists.txt -B ..\assimp\build
cmake --build ..\assimp\build

copy ..\assimp\build\lib\libassimp.a ..\lib\assimp.lib
copy ..\assimp\build\contrib\zlib\libzlibstatic.a ..\lib\zlib.lib
