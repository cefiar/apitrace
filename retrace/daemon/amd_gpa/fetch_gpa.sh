#!/bin/sh

git clone git://github.com/GPUOpen-Tools/GPA.git
python -u GPA/Scripts/UpdateCommon.py
cd Build/Linux && sh build.sh debug skip32bitbuild skipopencl skiphsa skiptests
