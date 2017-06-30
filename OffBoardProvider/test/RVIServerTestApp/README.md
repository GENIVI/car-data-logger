# RVIServerTestApp

RVIServerTestApp is an application implemented as a server using RVI and displays the result of the transferred files with graph.

# Installation

### tested Environment
`RVIServerTestApp` is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit
* Qt 5.6.1 (for test application)

### Precondition
To build RVIServerTestApp, following package are required
* Boost 1.54 (or later)
    * system, thread, date_time, iostreams
* python 2.7.6
* [rvi_core 0.5.1](https://github.com/GENIVI/rvi_core/releases)

### Build & Install
In RVIServerTestApp directory, build & install using following command:

    $ qmake -r -spec linux-g++
    $ make
    $ make install

After the installation, you can find binary(`RVIServerTestApp`) in `deploy` directory.

# Usage

### Run
Prepare a terminal window and navigate to the deploy directory of RVIServerTestApp.

Run `RVIServerTestApp` on the terminal.

        $ ./RVIServerTestApp

When the `RVIServerTestApp` starts, you can see the node information of service on terminal.

Then you should replace the node information in the `rvi_call.py` located in `/usr/lib/rvi_core` directory with generated node information.

* Generated Node URL :

        $ genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_data
        $ genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_start
        $ genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_finish

* Replaced `rvi_call.py` :

        $ transmission_start_service = "genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_start"
        $ transmission_send_data_service = "genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_data"
        $ transmission_finish_service = "genivi.org/node/17f46d5a-e91f-438b-bc9b-55af49be86f6/transmission_finish"

After that, you can run the `OffBoardProviderTestApp`, and RVIServer will receive the sample JSON files.
