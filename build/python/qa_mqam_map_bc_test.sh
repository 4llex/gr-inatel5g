#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/python
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/build/python:$PATH
export LD_LIBRARY_PATH=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/build/swig:$PYTHONPATH
/usr/bin/python2 /home/alexrosa/Documentos/GNURADIO/5gIoT/gr-inatel5g/python/qa_mqam_map_bc.py 
