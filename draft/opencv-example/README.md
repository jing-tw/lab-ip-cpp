# Multiple Object Tracking
## ByteTrack

```
# build shared library
cd ByteTrack-cpp
mkdir build
cd build
cmake ..
make

# copy the shared library
cp libbytetrack.so ../../opencv-example
```

## Usage
```
# build example
cd opencv-example
./build.sh

# run test
./bin/demo
```