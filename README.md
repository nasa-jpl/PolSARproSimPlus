PolSARproSim+: A coherent, polarimetric simulation of forests
================================================================================

This is the This is the Public Open Source repository for PolSARproSim+, an ANSI-C based software to simulate SAR/PolSAR/PolInSAR/TomoSAR echoes from forests.

 ## Directory Structure:
   * `<dir>/src`: This folder contains the c-source files
   * `<dir>/include`: This folder contains the c-header files
   * `<dir>/bin`: this folder should contain the simulator binary: `pspsim` once compiled
   * `<dir>/docs`: This contains documentation, including ppt slides from conferences
   * `<dir>/example`: This folder contains files needed to run an example simulation
 
 
## Compiling the code
The code can be compiled two ways, using `make` or the `meson` build system

### Compile using `meson` - preferred
   * In `<dir>` type
        * `$ meson setup builddir` 
        * `$ cd builddir`
        * `$ ninja` or `$ meson compile` will put binary in `builddir`, add it to your bash path
   * meson (https://mesonbuild.com/) and ninja are available on pip/conda etc.

### Compile using `make`
   * In `<dir>/src`: simply type 
      * `$ make install`. If successful you should have `pspsim` in `<dir>/bin`
   * add `<dir>/bin` to your bash path
   * requires libxml, and lpthreads and path to those libraries might need to be updated in the Makefile



## Running the code
   * To run simply type `$ pspsim`. This will tell you how to use it.             
     * To run the example:
        * `$ cd <dir>/example`
        * `$ pspsim run1.sar <prefix> <outputdir>`. This will put simulated SLC images and ancilliary data in `<outputdir>`


