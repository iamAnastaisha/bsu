#!/bin/bash

cd Number_lib
g++ -c library.cpp -o lib_number.o
ar rcs lib_number.a lib_number.o
cp lib_number.a ../Vector_lib
cp lib_number.a ../TestClient
rm lib_number.o
cd ../Vector_lib
g++ -c library.cpp -o lib_vector.o
g++ lib_vector.o lib_number.a  -shared -o lib_vector.so
cp lib_vector.so ../TestClient
rm lib_vector.o
cd ../TestClient
g++ -c main.cpp -o main.o
g++ -o main main.o lib_number.a lib_vector.so
sudo mv lib_vector.so /usr/lib
./main
rm main.o
rm lib_number.a
cd ../Number_lib
rm lib_number.a

cd ../Vector_lib
rm lib_number.a
rm lib_vector.so


