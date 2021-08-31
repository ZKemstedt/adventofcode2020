set PATH=%PATH%;%1
g++ -g *.c -lpthread --std=c18 -O0 -o %2