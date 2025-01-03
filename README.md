# KeyLogger-C
A simple Command Line interface (CLI ) keylogger made with C program.

The keylogger currently will only run within the Termianl. There will be a problem while exiting the program, ```Ctrl+C``` won't work. 
Matter of fact, only your mouse will work So you have to manuver/hover your mouse crusor to close the Terminal from the ```[x]``` icon or From ```[File>Quite]```.  

Running the keylogger:
First open your terminal, 
```gcc keylog.c -o keylog -lX11```
then, ```./keylog.c``` to run the program. If it doesn't, Run it with using ***sudo***.
