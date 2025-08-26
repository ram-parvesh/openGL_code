To build and run 
./opengl

# simple build command
mkdir build
cmake ..
make

# Use all available cores
cmake --build . --parallel

# Specify a specific number of cores, e.g., 4
cmake --build . --parallel 4

# Configure the project for a release build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
# In the build directory, before running cmake --build
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Build the project using all available cores and verbose output
cmake --build . --verbose --parallel