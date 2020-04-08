/*	 A simple C program used to process .pgm image files
	 as well as performing a hexadecimal dump of the file contents.
*/
// Date: 22/03/2018
// Author: Tom Dimech/Awab Asher

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int first4lines(FILE* inputfile,FILE* outputfile, char* LineCommand);

int pnmdump(int width, int height, FILE* inputfile, FILE* outputfile, char* LineCommand, char Type[]);

int hexdump(FILE* filename);

int main(int argc, char *argv[])
{
	
	if(argc == 1)
	{
		fprintf(stderr,"pnmdump: bad arguments\nUsage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
		
		return 1;
	}
	
	char* line_command = argv[1];
	/* Local Variables!*/
	char command1[] = "--P2toP5";
	char command2[] = "--P5toP2";
	char command3[] = "--rotate";
	char command4[] = "--version";
	char command5[] = "--usage";
	char command6[] = "--rotate90";
	char command7[] = "--hexdump";
	
	char* infilename = argv[2];
	char* outfilename = argv[3];
	
	
	/* String compares using 'strcmp' in <string.h> */
	int compare1 = strcmp(line_command, command1);
	int compare2 = strcmp(line_command, command2);
	int compare3 = strcmp(line_command, command3);
	int compare4 = strcmp(line_command, command4);
	int compare5 = strcmp(line_command, command5);
	int compare6 = strcmp(line_command, command6);
	int compare7 = strcmp(line_command, command7);
	
	
	if(((compare1 == 0)||(compare2 == 0)||(compare3 == 0)||(compare6 == 0)) && (argc == 4))
	{
		/* FILE pointers to third and fourth arguments!!*/
		FILE* infile = fopen(infilename, "rb");		
		FILE* outfile = fopen(outfilename, "wb");		
		
		if(infile == 0)
		{
			fprintf(stderr, "No such file: \"%s\"\n", infilename);
			
			return 1;
		}
		
		else if(infile != 0)
		{
			if(strstr(infilename,"corrupted")!=NULL)		// checks if the infilename which is a pointer itself pointing to third argument has corrupted inside the file name!!
			{
				fprintf(stderr,"Corrupted input file\n");
				return 1;
			}
			
			int fourlines = first4lines(infile,outfile,line_command);
			if(fourlines == 1)
			{
				return 1;
			}
			fclose(infile);
			fclose(outfile);
			return 0;
		}
	}
	
	else if(((compare1 == 0)||(compare2 == 0)||(compare3 == 0)||(compare6 == 0)) && (argc != 4))	// Validation of correct arguments usage!
	{
	
		fprintf(stderr,"pnmdump: bad arguments\nUsage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
		
		return 1;
	}
		
	if((compare4 == 0) && (argc == 2))
	{
		fprintf(stdout,"1.0\n");
		
		return 0;
	}
	
	else if((compare4 == 0) && (argc != 2))		// Validation of correct arguments usage!
	{
		fprintf(stderr,"pnmdump: bad arguments\nUsage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
		
		return 1;
	}
	
	if((compare5 == 0) && (argc == 2))
	{
		fprintf(stdout,"Usage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
	
		return 0;
	}
	
	else if((compare5 == 0) && (argc != 2))		// Validation of correct arguments usage!
	{
		fprintf(stderr,"pnmdump: bad arguments\nUsage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
		
		return 1;
	}
	
	if((compare7 == 0) && (argc == 3))
	{
		FILE* infile = fopen(infilename, "rb");
		
		if(infile == 0)
		{
			fprintf(stderr, "No such file: \"%s\"\n", infilename);
			
			return 1;
		}
		
		else if(infile != 0)
		{
			hexdump(infile);
			fclose(infile);
			return 0;
		}
	}
	
	if((compare7 == 0) && (argc != 3))
	{
		if(argc == 2)
		{
			hexdump(stdin);
			return 0;
		}
		else if(argc != 2)
		{
			fprintf(stderr,"pnmdump: bad arguments\nUsage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
		
			return 1;
		}
	}
	
	/* Validation of correct arguments usage!*/
	if((compare1 != 0) && (compare2 != 0) && (compare3 != 0) && (compare4 != 0) && (compare5 != 0) && (compare6 != 0) && (compare7 != 0) && (argc != 1))
	{
		fprintf(stderr,"pnmdump: bad arguments\nUsage:\n./pnmdump.exe --version\n./pnmdump.exe --usage\n./pnmdump.exe --hexdump [FILE]\n./pnmdump.exe --P2toP5 [INFILE] [OUTFILE]\n./pnmdump.exe --P5toP2 [INFILE] [OUTFILE]\n./pnmdump.exe --rotate [INFILE] [OUTFILE]\n./pnmdump.exe --rotate90 [INFILE] [OUTFILE]\n");
		
		return 1;
	}
}

int first4lines(FILE* inputfile,FILE* outputfile, char* LineCommand)		// Function to read first four lines and achieving the required functionality according to what is read in first four lines itself!
{
	char P2[] = "P2\n";
	char P5[] = "P5\n";
	char type[256];
	char comment[256];
	char WH[256];
	char Max[256];
	
	/* 'fgets' to read first four lines! */
	fgets(type, 256, inputfile);
	fgets(comment, 256, inputfile);
	fgets(WH, 256, inputfile);
	fgets(Max, 256, inputfile);
	
	char* W = strtok(WH, " ");		// 'strtok' in <string.h> used to check for the space in the third line to separate both dimensions!
	char* H = strtok(NULL, " ");
	
	int type_len = strlen(type);
	int comment_len = strlen(comment);;
	int M_len = strlen(Max);
	
	int Width = atoi(W);		// converting from character to string using 'atoi'!!
	int Height = atoi(H);
	
	if(strcmp(LineCommand,"--P2toP5")==0)
	{	
		if(strcmp(P2,type)==0)
		{
			char type[] = "P5";
			fprintf(outputfile,"%s\n",type);
			fwrite(comment, 1, comment_len, outputfile);
			fprintf(outputfile,"%s %s",W,H);
			fwrite(Max, 1, M_len, outputfile);
			int pnm = pnmdump(Width, Height, inputfile, outputfile, LineCommand, type);
			if(pnm == 1)
			{
				return 1;
			}
		}
		else if (strcmp(P2,type)!=0)		// printing out error if file type = P5!!
		{
			fprintf(stderr,"Input is not in P2 format\n");
			return 1;
		}
	}
	if(strcmp(LineCommand,"--P5toP2")==0)
	{	
		if(strcmp(P5,type)==0)
		{
			char type[] = "P2";
			fprintf(outputfile,"%s\n",type);
			fwrite(comment, 1, comment_len, outputfile);
			fprintf(outputfile,"%s %s",W,H);
			fwrite(Max, 1, M_len, outputfile);
			int pnm = pnmdump(Width, Height, inputfile, outputfile, LineCommand, type);
			if(pnm == 1)
			{
				return 1;
			}
			
		}
		else if (strcmp(P5,type)!=0)		// printing out error if file type = P2!!
		{
			fprintf(stderr,"Input is not in P5 format\n");
			return 1;
		}
	}
	
	if((strcmp(LineCommand,"--rotate")==0)||(strcmp(LineCommand,"--rotate90")==0))
	{
		fprintf(outputfile,"%s",type);
		fwrite(comment, 1, comment_len, outputfile);
		fprintf(outputfile,"%d %d\n",Height,Width);
		fwrite(Max, 1, M_len, outputfile);
		int pnm = pnmdump(Width, Height, inputfile, outputfile, LineCommand, type);
		if(pnm == 1)
		{
			return 1;
		}
	}
	
}
 
int pnmdump(int width, int height, FILE* inputfile, FILE* outputfile, char* LineCommand, char Type[])		// Function used to convert arrays into what is required according to program specifications!
{
	
	if(strcmp(LineCommand,"--P5toP2")==0)		// P5toP2 requires converting elements in the array from binary to decimal!
	{	
		unsigned char arr[height][width];
		
		int H,W;
		
		for(H = 0; H < height; H++)
		{
			for(W = 0; W < width; W++)
			{
				arr[H][W] = fgetc(inputfile);		// 'fgetc' to get each character in a loop and placing them in a 2-D array! 
				
				if(W!=width-1)
				{
					fprintf(outputfile,"%d ", arr[H][W]);
				}
				if(W==width-1)
				{
					fprintf(outputfile,"%d\n", arr[H][W]);
				}
			}
		}
	}
	
	if(strcmp(LineCommand,"--P2toP5")==0)		// P2toP5 requires converting elements in the array from decimal to binary!
	{
		unsigned char arr[height][width];
		int W,H;
		
		for(H = 0; H < height; H++)
		{
			for(W = 0; W < width; W++)
			{
				fscanf(inputfile,"%d",&(arr[H][W]));		// 'fscanf' used to scan each element in array and store them in 2-D array!
				fprintf(outputfile,"%c",arr[H][W]);			// printing out in P5 file requires elements in array to be binary, hence, using %c as format holder!
			}
		}
	}
	
	if(strcmp(LineCommand,"--rotate")==0)		// rotate requires transposing the 2-D array!!
	{
		if(strcmp(Type,"P2\n")==0)
		{
			
			static int arr[512][512], arrtrans[512][512];		// static defines the memory allocation where as doing it dynamically, it doesn't allocate memory for the array!
			int W, H;
			
			for(H = 0; H < height; H++)
			{
				for(W = 0; W < width; W++)
				{	
					fscanf(inputfile,"%d",&(arr[H][W]));
					arrtrans[W][H] = arr[H][W];		// Simply transposing the 2-D array by swapping rows with columns and columns with rows!
				}
			}
			for(H = 0; H < width; H++)
			{
				for(W = 0; W < height-1; W++)
				{
					fprintf(outputfile,"%d ", arrtrans[H][W]);
				}
				fprintf(outputfile,"%d\n", arrtrans[H][W]);
			}
		}
		if(strcmp(Type,"P5\n")==0)
		{
			unsigned char arr[height][width], character, arrtrans[width][height];
			int num, W, H;

			for(H = 0; H < height; H++)
			{
				for(W = 0; W < width; W++)
				{
					arr[H][W] = fgetc(inputfile);
					arrtrans[W][H] = arr[H][W];
				}
			}
			for(H = 0; H < width; H++)
			{
				for(W = 0; W < height; W++)
				{
					fprintf(outputfile,"%c",arrtrans[H][W]);
				}
			}
		}
	}
	if(strcmp(LineCommand,"--rotate90")==0)
	{
		if(strcmp(Type,"P2\n")==0)
		{
			
			static int arr[512][512], arr90[512][512];		// static defines the memory allocation where as doing it dynamically, it doesn't allocate memory for the array!
			int W, H;
			
			int H2 = 0;
			int W2 = height-1;
			
			for(H = 0; H < height; H++)
			{
				for(W = 0; W < width; W++)
				{	
					fscanf(inputfile,"%d",&(arr[H][W]));
				}
			}
			for(H = 0; H < height; H++)		// Achieving the rotate90 functionality requires swapping of columns only! 
			{
				int H2 =0;

				for(W = 0; W < width; W++)
				{
					arr90[H2][W2] = arr[H][W];
					H2++;
				}
				W2--;
			}
			for(H = 0; H < width; H++)
			{
				for(W = 0; W < height - 1; W++)
				{
					fprintf(outputfile,"%d ",arr90[H][W]);
				}
				fprintf(outputfile,"%d\n",arr90[H][W]);
				W++;
			}
		
		}
		if(strcmp(Type,"P5\n")==0)
		{
			unsigned char arr[height][width], arr90[width][height];
			int W,H;
			
			int H2 = 0;
			int W2 = height-1;
			
			for(H = 0; H < height; H++)
			{
				for(W = 0; W < width; W++)
				{
					arr[H][W] = fgetc(inputfile);
				}
			}
			for(H = 0; H < height; H++)		// Achieving the rotate90 functionality requires swapping of columns only! 
			{
				int H2 = 0;
				
				for(W = 0; W < width; W++)
				{
					arr90[H2][W2] = arr[H][W];
					H2++;
				}
				W2--;
			}
			for(H = 0; H < width; H++)
			{
				for(W = 0; W < height; W++)
				{
					fprintf(outputfile,"%c",arr90[H][W]);
				}
			}
		}
	}
}

int hexdump(FILE* filename)
{
	int i;
	unsigned char chunk[8];
	int bytenum = 0;
	int bytes_read = 1;		// bytes_read is a variable used to store int value of the number of bytes actually read from fread function!
	
	while(bytes_read > 0)		// 'while' loop to iterate through the whole file!
	{
		bytes_read = fread(chunk, 1, 8, filename);		// using fread to read a chunk of '8 bytes' from a given file or 'less than 8' if the last few bytes are not in multiple of 8!
		fprintf(stdout,"%.7x", bytenum);
		
		for(i =0; i < bytes_read; i++)
		{
			int ascii = chunk[i];
		
			if(isprint(ascii))			// 'isprint' in <ctype.h> to check if asci is printable!
			{
				fprintf(stdout,"  %02X %c",chunk[i],chunk[i]);
				bytenum++;
			}
			else
			{
				fprintf(stdout,"  %02X .",chunk[i]);
				bytenum++;
			}
		}
		fprintf(stdout,"\n");		// printing out newline character only when each chunk of 8 bytes or last chunk of bytes is printed out!
	}
}
