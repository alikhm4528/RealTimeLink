# Realtime link project
to compile the project for Interleaving algorithm, go to project directory and use folowing commands:
```
mkdir build
cd build
cmake -DALG=INTERLEAVING ..
make
cd bin
./RealTimeLink
```
also for Hamming algorithm:
```
mkdir build
cd build
cmake -DALG=HAMMING ..
make
cd bin
./RealTimeLink
```
the outputData.bin file would be in Database directory.
