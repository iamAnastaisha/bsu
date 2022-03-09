cd .\Number
g++ -c Number.cpp -o lib_number.o
ar rcs lib_number.lib lib_number.o
cp lib_number.lib ../Vector
cp lib_number.lib ../TestClient
rm lib_number.o
cd ../Vector
g++ -c Vector.cpp -o lib_vector.o
g++ lib_vector.o lib_number.lib  -shared -o lib_vector.dll
cp lib_vector.dll ../TestClient
rm lib_vector.o
cd ../TestClient
g++ -c TestClient.cpp -o main.o
g++ -o main main.o lib_vector.dll
./main

rm main.o
rm lib_vector.dll
rm lib_number.lib

cd ../Number
rm lib_number.lib

cd ../Vector
rm lib_number.lib
rm lib_vector.dll

cd ..