# fingerprint

MSIAM project M1.
Preprocessing of fingerprint images.

How to launch tests:

1/ Open the Makefile, then modify the source by giving the test that you need to execute.

For example, if you want to launch the test of the new remap, you just have to type in the Makefile :
SRC      :=$(wildcard src/*.cpp)   \
        $(wildcard src/remap/*.cpp) \


2/ Then go on your terminal at the root of the project "fingerprint" and just execute this line of command: "make clean; make; ./build/apps/program"   


3/ To access to the documentation: go on your terminal in the folder /fingerprint/build/doc/html and type the command "firefox files.html"     
