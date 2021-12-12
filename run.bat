
echo Compiling ai_game.exe...
@echo off
g++ -Ofast *.cpp src/*.cpp -lpthread -o ai_game.exe
.\ai_game.exe