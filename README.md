# KeyLogger-C
A simple Command Line interface (CLI ) keylogger made with C program.

The keylogger currently can only runs within the termianl. There is a problem exiting the program, ctrl+c won't work. 
Matter of fact only your mouse will work So you have to manuver/hover your mouse crusor to close the window from that [x] icon or From [File>Quite].  

How to use??
First open your terminal, 
gcc keylog.c -o keylog -lX11 
then, ./keylog.c
It runs the program. If it doesn't, Run it with using sudo.
