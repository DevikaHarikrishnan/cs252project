# CS252 Operating Systems - Minors course - Assignment
## Individual Submission - Medium Level - Chapter 2 Project 1

### Aim of the project
The project aims to create a kernel module and load the same into the Linux kernel. Also, the kernel module is modified so that it creates an entry
in the /proc file system

![image](https://user-images.githubusercontent.com/65976375/142977921-f0984d46-a698-4842-982a-b4909faccc43.png)

Image Ref:https://xdecroc.wordpress.com/2016/03/04/an-introduction-to-linux-loadable-kernel-modules/

### Environment Setup
I used the Linux virtual machine provided with the OS concepts text.This ensured that any errors in the code which has the potential to cause a system crash can be handled by rebooting the system. The virtual machine provided command-line based Ubuntu Server running version 4.4 of the Linux kernel.I followed the instructions in the link http://cs.westminstercollege.edu/~greg/osc10e/vm/index.html to install virtual box and virtual machine. I referred source code available in the OS concepts website and referred the github link https://github.com/KhanhNguyen4999/Simple_shell_linux_c . In addition to the OS concepts book, I referred https://www.geeksforgeeks.org/making-linux-shell-c/ for more understanding

### Challenges faced
The major challenge was lack of UI. I had to depend on the terminal and commands to create, update, save source code files and to compile. Troubleshooting and connecting to github was also difficult. I faced compile issues due to unidentified header files. The publicly available source code and source code in the text was not compiling and had to be redone to ensure that the requirements are fulfilled.

### Workaround to overcome the challenges

I watched the video https://www.youtube.com/watch?v=WW3KiOUx5sQ to install Ubuntu Desktop, which provided a graphical user interface.I downloaded Ubuntu 20.04.3 LTS from https://ubuntu.com/download/desktop and installed in Oracle virtual box. I then installed visual studio code in Ubuntu by following the steps in the link https://linuxize.com/post/how-to-install-visual-studio-code-on-ubuntu-20-04/. I then installed the C++ extension in VS Code for gcc compiler. I referred the following link to do it https://code.visualstudio.com/docs/cpp/config-linux. I used the git extension in VSCode to setup git and connect to my github repository. I referred these links to do it https://adamtheautomator.com/visual-studio-code-github-setup/ and https://www.digitalocean.com/community/tutorials/how-to-use-git-integration-in-visual-studio-code

### Project Work

The first part of the project involved creating and inserting a module into the Linux kernel and loading and removing the modules. The requirements are as follows
1. Print out the value of GOLDEN RATIO PRIME in the simple init() function.
2. Print out the greatest common divisor of 3,300 and 24 in the simple exit() function
3. Print out the values of jiffies and HZ in the simple init() function.
4. Print out the value of jiffies in the simple exit() function.

The above requirements are coded in **simple.c** file

The second part of the project involved designing kernel modules that create additional entries in the /proc file system involving both kernel statistics and information related to specific processes

The requirements involved in this part are as follows
1.Design a kernel module that creates a /proc file named /proc/jiffies that reports the current value of jiffies when the /proc/jiffies file is read, such as with the command cat /proc/jiffies.Be sure to remove /proc/jiffies when the module is removed.
This is coded in **readjiffies.c**
2.Design a kernel module that creates a proc file named /proc/seconds that reports the number of elapsed seconds since the kernel module was loaded. This will involve using the value of jiffies as well as the HZ rate. When a user enters the command cat /proc/seconds your kernel module will report the number of seconds that have elapsed since the kernel module was first loaded. Be sure to remove /proc/seconds when the module is removed.
This is coded in **timeelapsed.c**

## Output to simple.c
![image](https://user-images.githubusercontent.com/65976375/142978999-3f25c498-89f7-486d-8cf2-c761d1280617.png)
![image](https://user-images.githubusercontent.com/65976375/142979053-532d16b4-815f-4ee9-acf1-3db977d51add.png)

## Output to readjiffies.c
![image](https://user-images.githubusercontent.com/65976375/142979271-9c361701-5b9f-429d-9b00-0d12d105f120.png)
![image](https://user-images.githubusercontent.com/65976375/142979324-6d3b4103-d49b-4ee3-8e93-10740d0d5cc8.png)

## Output to timeelapsed.c

https://user-images.githubusercontent.com/65976375/142979519-2ca7505a-fb64-4846-9857-f1ba5726bbc4.mp4

