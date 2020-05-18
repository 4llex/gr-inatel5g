
official project (QAM modulator, C Scripts adapted from wheberth version)


Here's a quick list for all the steps necessary to build blocks and out-of-tree modules:

Create (do this once per module): gr_modtool create MODULENAME
Add a block to the module: gr_modtool add BLOCKNAME
Create a build directory: mkdir build/
Invoke the make process: cd build && cmake <OPTIONS> ../ && make (Note that you only have to call cmake if you've changed the CMake files)
Invoke the testing: make test or ctest or ctest -V for more verbosity
Install (only when everything works and no tests fail): sudo make install
Ubuntu users: reload the libs: sudo ldconfig
Delete blocks from the source tree: gr_modtool rm REGEX
Disable blocks by removing them from the CMake files: gr_modtool disable REGEX

