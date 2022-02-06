gcc.exe -x c++ -mwindows -o main.o main.c;
gcc.exe -mwindows -o main.exe main.o -lkoolplot 
 -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lstdc++ -lsupc++