OpenCV-Entropy
==============

histGray.cpp is used to calculate the entropy of a grayscale image
histColor.cpp is used to calculate the entropy of color image, the color image is first split into YCbCr and then the histogram and entropy is calculated per each channel
myHist.cpp is used to calculate the entropy of a grayscale image without using OpenCV's calcHist

to compile use:
g++ -ggdb `pkg-config --cflags opencv` -o histGray histGray.cpp `pkg-config --libs opencv`
or use 'buildme.sh'
./buildme.sh histGray.cpp


