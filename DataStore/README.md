# Data Store

Data Store is module storing the CDL data from VSSDataCollector.

# Installation

### Tested Environment
Data Store is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit
* Qt 5.6.1 (for test application)

### Precondition
To build Data Store, following package are required
* sqlite3 3.8.2 (or later)
* Boost 1.54 (or later)
    * system, system, thread, log, filesystem, date_time

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:

#### CDL

        $ git clone https://github.com/GENIVI/cat-data-logger.git

        $ git checkout trial-integration-with-rvi


### Build & Install
#### Data Store build & install
In Data Store directory of CDL, build & install using following command:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ sudo make install
    
#### Test Application build & install
Navigate to the test directory of DataStoreTestApp, and build & install using following command:

        $ qmake -r -spec linux-g++
        $ make
        $ make install

After the installation, you can find binary(Data Store Test Application) and other files for configuration and generated Store_Config JSON in deploy directory

# Usage

### Run
Prepare one terminal windows and navigate to the deploy directory of test.
Before run test application, add library search path for `DataStoreManager` library to the `LD_LIBRARY_PATH` using following command in terminal:

        $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

Run Data Store Test application on terminal

        $ ./DataStoreTestApp
        
The DataStoreTestApp generates cdl sample data randomly, and call the storeData function in DataStoreManager.
On the DataStoreManager side, you can check the created json file and database file which manages the lists of files in the storage.

### Configuration file for data store
Configuration file element explanation:
* DataStoreLocation 
    * Absolute path to store the collected data as file
* MaxFileSize
    * The maximum file size
* MaxSotrageSize
    * The maximum storage size
* MaxFileExpirePeriod
     * The file will be deleted after specified amount of time
* TransactionBufferSize
     * Number of data to be stored in file at once

Example

    {
         "DataStoreLocation": "/tmp/cdl/StoreCDLDataFile",
         "MaxFileSize": "15",                     //unit : kByte
         "MaxStorageSize": "100",                 //unit : kByte
         "MaxFileExpirePeriod": "60",             //unit : minutes
         "TransactionBufferSize": "20"            //unit : counts
    }

### Environment variables
Data Store needs a environment variable for run such as configuration file for data store.
* **STORE_CONFIG_FILE**
    * user defined configuration file for data store (e.g store_config_file.json)

