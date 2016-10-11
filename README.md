# Car Data Logger Proof-of-Concept
The component Car Data Logger is responsible for collecting, storing car related data, and providing the data to other GENIVI compliance components and off-board servers.

CDL is started from an idea that if we could collect, store, and provide car related data, it would make a very valuable service to auto-makers, users, and other GENIVI compliance components.

So, the goal of CDL is defining what kind of data should be collected, how to collect, and store data properly.  It should also provide data to on-board and off-board (devices.)

Additionally, guaranteeing the data integrity is required and security of data should be considered as well.

This PoC realizes concept of Data Collect, Store and Provide requirements of the CDL Vehicle Level Requirements, especially focused on the Vehicle Data.

# Installation 
 
### Tested Environment 
This PoC is implemented and tested on: 
* VMWare Workstation 12 Player (12.1.1 build-3770994) 
* Ubuntu 14.04 64bit
* Qt 5.6.1
 
### Precondition 
To build the PoC, following packages are required 
* CommonAPI 3.1.5 (including DBus and SOME/IP Runtime) 
* vSomeIP 2.0.1 
* automotive-dlt 2.15 (or later) 
* Qt5 (5.6.1 is recommended) 

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:

    $ git clone https://github.com/GENIVI/car-data-logger.git

    $ git checkout proof-of-concept

## Build & Install 
All applications are implemented based on Qt5. 
Before build the project, please make sure Qt is properly installed using following command in the terminal window.

    $ qmake -version
    
In order to build the project the pkgconfig files of the patched `libdbus` library must be added to the `PKG_CONFIG_PATH`. 
For example, if the patched libdbus library is available in `/usr/local`, set the PKG_CONFIG_PATH variable as follows:

    $ export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH 
    
Now use qmake to build the project. Default CONFIG value is `release` 

    $ qmake -r -spec linux-g++ CONFIG+=[debug|release] 
    $ make 
    $ make install
    
After the installation, you can find binaries, libraries and other files in deploy/debug or deploy/release directory depending on build option. 

# Usage 
 
### Run 
Navigate to the installed directory. 

    $ cd deploy/debug or cd deploy/release
    
Before run applications, add library search path for the patched `libdbus` to the `LD_LIBRARY_PATH`.
For example, if the patched libdbus library is available in `/opt/lib`, set the LD_LIBRARY_PATH variable as follows:

    $ export LD_LIBRARY_PATH=/opt/lib:$LD_LIBRARY_PATH

Enter the following command in the terminal window.

    $ ./run_all.sh
