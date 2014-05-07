C-Based-Operating-System
========================

Note: In it's current state the OS won't work. It needs the simulator which I will upload soon. 


Has all the capabilities of a CP/M-like OS. 

This readme assumes that you are running on a system that can run .jar files. 

The step-by-step guide is based on the Linux Ubuntu OS. Adjust to Windows and iOS accordingly

To start, follow these steps:

1. Create a directory where all these files will be stored

2.  run the accompanying .sh script by typing :./compileOS.sh
   - This script will create a file called floppya.img, which will be used to boot the OS. It will also create all necessary files for the 
     execution of the OS. 

3.  In the simulator that will appear, on the top where it says Floppya Drive A, please choose the floppya.img file which was created.

4. You should now see a prompt for the shell! These are the supported instructions:
   - execute <filename>
   - create <newfilename>
   - copy <oldfile> <newfile>
   - delete <filename>
  

