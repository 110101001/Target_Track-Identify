# Target_Track-identify



Warning: Unfinished!



This program's function is mult-target track&identify. It's a course design of Computer Vision.



This Program use following methods:

    SURF(harris no longer used)

    KalmanFilter

    Background differentiation



COMPILE:

    To compile, you need a Cmake(vision 3.5.0 or higher), g++(vision 7 or higher) and OpenCV(4.0.0, including opencv contrib, more specifically, the xfeatures2d module)

    Create a directory for build:

        mkdir build

    Compile makefile:

        cd build

        cmake ..

    Compile:

        make

    A executable file tracker should be generated.
