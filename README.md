PolSARproSim+: A coherent, polarimetric simulation of forests
================================================================================

This is the internal JPL repository for PolSARproSim+ 
 * Get the source code:
   * type `git clone https://github.jpl.nasa.gov/rahmed/pspsim.git <dir>`, where `<dir>` is the optional directory name for whatever you want the software directory to be called. If you don't provide this name, git will clone the software in `<where you are>/pspsim`
 * Directory Structure: 
   * `<dir>/bin`: this folder should contain the simulator binary: `pspsim_dev`.
   * `<dir>/docs`: This contains documentation, including ppt slides from conferences
   * `<dir>/example`: This folder contains files needed to run an example simulation
   * `<dir>/include`: This folder contains the c-header files
   * `<dir>/src`: This folder contains the c-source files
 * Compiling:
   * In `<dir>/src`: type make install. If succesful you should have `pspsim_dev` in `<dir>/bin`
   * requires libxml, and lpthreads
 * Running:	
   * add `<dir>/bin` to your bash path
   * in your workdir type `pspsim_dev`. This will tell you how to use it. 
     * To run the example type `pspsim_dev run1.sar <prefix> <outputdir>`. This will put simulated SLC images and ancilliary data in `<outputdir>`

## what I had to do to make this software run on Zodiac
 1. Install miniconda2 (https://conda.io/miniconda.html)
 2. Install libmxl2 using miniconda
    * `conda install libxml2` (this installs `libxml`, `liconv` and `lz` on `/home/rahmed/miniconda2/lib` & `/home/rahmed/miniconda2/include/`
 3. Change makefile to point to libxml installation
    * set: `LDFLAGS = -lm -L/home/rahmed/miniconda2/lib -lxml2 -liconv -lz`
    * set: `INCDIR = -I$(HOME)/include -I/home/rahmed/miniconda2/include/libxml2`
 4. Change LD_LIBRARY_PATH
    * In my .bashrc I added: `export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/rahmed/miniconda2/lib/"`

 If on Zodiac, one should be able to use these libraries from Razi's folder and run polsarprosim.

