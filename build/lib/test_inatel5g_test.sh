#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/build/lib:$PATH
export LD_LIBRARY_PATH=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-inatel5g 
