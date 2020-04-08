Author: Tom Dimech/Awab Asher
-------------------------------------------------------------------------------------------------------------
Date: 22/03/2018
-------------------------------------------------------------------------------------------------------------
Compiling the code

When loading up shell type "cd C:/YOURPATH/pnmdump-1.0" where YOURPATH is the path to wherever the file is 
saved on your machine.

In the main terminal type in:
$ make
This compiles the code from a C file into a machine readable code in the form of an .exe file
Then, type in:
$ ./pnmdump.exe and any of the following arguments: 
	--hexdump [FILE], 
	--version, 
	--usage,
	--P2toP5 [INFILE] [OUTFILE], 
	--P5toP2 [INFILE] [OUTFILE], 
	--rotate [INFILE] [OUTFILE],
	--rotate90 [INFILE] [OUTFILE].
The code is then able to run on the computer.

Any deviation from the listed arguments would result in error message displayed to stderr:
pnmdump: bad arguments
Usage:
./pnmdump.exe --version
./pnmdump.exe --usage
./pnmdump.exe --hexdump [FILE]
./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]

./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]

./pnmdump.exe --rotate [INFILE] [OUTFILE]

./pnmdump.exe --rotate90 [INFILE] [OUTFILE]

Whilst testing the code we discovered that the runtest-1.0.py would not accept the above
as the error message and in addition the same can be be said about the --usage argument
obviously not including the "pnmdump: bad arguments" before. In order to allow the proper
printing of the usage function and error messages we edited the value of USAGE in 
runtest-1.0.py to include:

./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]

./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]

./pnmdump.exe --rotate [INFILE] [OUTFILE]

./pnmdump.exe --rotate90 [INFILE] [OUTFILE]

As a result all functions are now printed in both cases and the code still passes the
tests.

In order to test the code against the test files that has been supplied
"make test" can be typed into the shell and the code will be compiled
and the test script will be ran.
-------------------------------------------------------------------------------------------------------------
Short description of what the code does:

	A C program that can do simple processing of pgm image files.
	This code processes image files in the form of pgm files as well as
	performing a hexadecimal dump of the file contents.
	There are functions that convert the pgm files in the format of P2
	to the P5 format, which is from asci to binary format.
	
	As well as this the code also does a conversion from P5 to P2 or from
	binary to asci. The code can rotate the image in the line y = x or 
	in other words creates the transpose of the image.
	
	There is a second rotate functionality that rotates the image by 90
	degrees.
	
	The hexadecimal dump prints the number of bytes read in hex, the
	characters and their hexadecimal equivalent in the file into stdout
	it only prints 8 characters per line.
	
	There are two more commands, one which prints the version of the code
	to stdout and another which prints how to use each command into the stdout.


--------------------------------------------------------------------------------------------------------------
How to use the code and examples of output
For example:
After typing in 
$ make
gcc -std=c99 -Wall practice.c -o practice.exe

Type in any of the arguments listed above:

e.g:
$ ./pnmdump.exe --version
1.0

$ ./pnmdump.exe --usage
Usage:
./pnmdump.exe --version
./pnmdump.exe --usage
./pnmdump.exe --hexdump [FILE]

$ ./pnmdump.exe blah blah blah
pnmdump: bad arguments
Usage:
./pnmdump.exe --version
./pnmdump.exe --usage
./pnmdump.exe --hexdump [FILE]

$ ./pnmdump.exe --hexdump Makefile
0000000  24 $  43 C  46 F  4C L  41 A  47 G  53 S  20
0000008  3D =  20    2D -  73 s  74 t  64 d  3D =  63 c
0000010  39 9  39 9  20    2D -  57 W  61 a  6C l  6C l
0000018  0D .  0A .  0D .  0A .  61 a  6C l  6C l  3A :
0000020  20    70 p  6E n  6D m  64 d  75 u  6D m  70 p
0000028  2E .  65 e  78 x  65 e  20    0D .  0A .  0D .
0000030  0A .  25 %  2E .  65 e  78 x  65 e  3A :  20
0000038  25 %  6D m  61 a  69 i  6E n  2E .  63 c  0D .
0000040  0A .  09 .  67 g  63 c  63 c  20    24 $  28 (
0000048  43 C  46 F  4C L  41 A  47 G  53 S  29 )  20
0000050  24 $  3C <  20    2D -  6F o  20    24 $  40 @
0000058  0D .  0A .  0D .  0A .  74 t  65 e  73 s  74 t
0000060  3A :  20    70 p  6E n  6D m  64 d  75 u  6D m
0000068  70 p  2E .  65 e  78 x  65 e  0D .  0A .  09 .
0000070  70 p  79 y  74 t  68 h  6F o  6E n  20    74 t
0000078  65 e  73 s  74 t  73 s  2F /  72 r  75 u  6E n
0000080  74 t  65 e  73 s  74 t  73 s  2D -  31 1  2E .
0000088  30 0  2E .  70 p  79 y  20    2E .  2F /  70 p
0000090  6E n  6D m  64 d  75 u  6D m  70 p  2E .  65 e
0000098  78 x  65 e
000009a
--------------------------------------------------------------------------------------------------------------

Changelog
	18 March 2018 	Changed the way of reading P2 files to fscanf.
	19 March 2018 	Changed the declaration of 2-D arrays to static int from int.
	20 March 2018	Changed the hexdump part to make it more compact using one single 'while' loop.
	21 March 2018	Fixed typo for printing out errors for corrupted files.
	22 March 2018	Adding newline character after writing file type on first line.
	
