g++ -c ..\pbgl\src\*.cpp -I..\pbgl\include -I..\glad\include -I..\stb -I..\cml -L..\lib -lstbi
if not exist "..\lib" mkdir ..\lib
ar -rvs ..\lib\pbgl.lib *.o
del *.o
