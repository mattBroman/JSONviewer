-Before running this application, all of the json files must be moved 
into the provided directory entitled "dataset". The user must also 
ensure that "fltk" is properly installed on their machine.

-In order to compile the code, the first step is to use the
 given makefile by typing the command:
 
 make
 
-The next step is to link the library to the rest of the data 
using the line below:

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

- At this point the Application is ready for use and can be run using:

./JSONviewer
