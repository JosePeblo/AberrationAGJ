g++ .\src\Scene\*.cpp ^
.\src\Sandbox\*.cpp ^
.\src\Rendering\*.cpp ^
.\src\ObjectTree\*.cpp ^
.\src\Controller\*.cpp ^
-o app.exe ^
-I .\src ^
-I .\vendor\glad\include ^
-I .\vendor\glfw\include ^
-I .\vendor\pbgl\include ^
-I .\vendor\assimp\include ^
-I .\vendor\assimp\build\include ^
-I .\vendor\assimp\build\contrib ^
-I .\vendor\cml ^
-L .\vendor\lib ^
-lglad ^
-lglfw3 ^
-lpbgl ^
-lstbi ^
-lopengl32 ^
-lmingw32 ^
-lComdlg32 ^
-lUser32 ^
-lGdi32 ^
-lassimp ^
-lzlib ^
-Wall ^
-ggdb ^
-std=c++17

app.exe