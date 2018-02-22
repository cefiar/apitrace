#!/bin/sh

git clone git://github.com/GPUOpen-Tools/GPA.git
python -u GPA/Scripts/UpdateCommon.py
cd GPA/Build/Linux
sh build.sh gtestlibdir /home/majanes/src/apitrace/build/ debug skip32bitbuild skipopencl skiphsa

# skiptests
