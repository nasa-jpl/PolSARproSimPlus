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

