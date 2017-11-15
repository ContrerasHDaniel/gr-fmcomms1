#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/daniel/gr-fmcomms1/lib
export PATH=/home/daniel/gr-fmcomms1/build/lib:$PATH
export LD_LIBRARY_PATH=/home/daniel/gr-fmcomms1/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-fmcomms1 
