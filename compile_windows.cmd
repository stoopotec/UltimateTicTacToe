C:/mingw64/bin/g++.exe -c main.cpp -I"C:\SFML-2.6.1\include"

C:/mingw64/bin/g++.exe -c interface.cpp -I"C:\SFML-2.6.1\include"

C:/mingw64/bin/g++.exe main.o playground.cpp player.cpp console_player.cpp bot_player.cpp interface.o -o main.exe -L"C:\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system

pause