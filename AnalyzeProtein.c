
/**
 * Program AnalyzeProtein gets several (min 1) files with protein data
 * and analyzes each one
 * For every protein file there will be printed: um of atoms found in it,
 * the center of the protein, its radius and the max distance between atoms in
 * the protein
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>



//-----DEFINITIONS OF MACROS--------------------------

#define MIN_ARGUMENTS 2 /** first: argument always program's name
							second etc: File names
							**/

#define MAX_LINE_SIZE 81 //maximum allowed line length  + 1 for newline character
#define MAX_ATOM_NUM 20000 //we read 20.000 atoms max and ignore the rest

#define ATOM_FLAG "ATOM  " //according to school solution only lines that start this way are legit
#define FLAG_LEN 6

#define COORD_NUM 3
#define X_START 31
#define Y_START 39
#define Z_START 47
#define COORD_LENGTH 8

/**
 * @func analyzeProteinFile
 * Function gets pointer to a file, reads it line by line,
 * and prints out the Name of the file, num of atoms read in it,
 * the center of the protein, its radius and the max distance between atoms in
 * the protein
 * @param fileName name of the File to read
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int analyzeProteinFile(char* fileName);

/**
 * function decides if given line starts with "ATOM"
 * and therefore is legitimate atom line
 * @param line the line to heck
 * @return true iff line is an atom line
 */
_Bool isAtom(const char* line);

/**
 * The function gets a line(in form of string),
 * looks for X, Y and Z coordinates and extracts them in form of floats to given locations
 * @param line pointer to line to extract coordinates from
 * @param x pointer to float to store X coordinate
 * @param y  pointer to float to store y coordinate
 * @param z  pointer to float to store z coordinate
 * @return EXIT_SUCCESS iff all three of the floats were successfully extracted
 */
int extractCoordinates(char* line);

//------PROGRAM FLOW--------------------------------

int main(int argc, char* argv[])
{


	if(argc < MIN_ARGUMENTS) //not enough arguments to run the programm
	{
		printf("Usage: AnalyzeProtein <pdb1> <pdb2> ...\n");
		exit(EXIT_FAILURE);
	}
	

	unsigned int numOfFiles = argc - 1; // number of files to analyze


	for( unsigned int i = 0; i < numOfFiles; i++)
	{

		analyzeProteinFile(argv[i + 1]);
		printf("Analyzed file num %d \n", i);
		
	}

	return EXIT_SUCCESS;

}

//--------------------------------------------------functions--------------------------------------


int analyzeProteinFile(char* fileName)
{
    FILE* fileToRead = fopen(fileName, "r");
    if(fileToRead == NULL)  //checking for errors in opening the file
    {
        printf("Error opening file: %s \n", fileName);
        exit(EXIT_FAILURE);
    }
    printf("Opened file %s \n", fileName);

    char newLine[MAX_LINE_SIZE];

    while(fgets(newLine, MAX_LINE_SIZE, fileToRead))
    {
        if( isAtom(newLine))
        {
            printf("linee is %s", newLine);
            printf("line is ATOM \n");
            extractCoordinates(newLine);
        }else //line is not e legitimate atom line - we ignore it
        {
            printf("NO\n");

        }
    }

    fclose(fileToRead);
    return EXIT_SUCCESS;

}


_Bool isAtom(const char* line)
{
    return (strncmp(ATOM_FLAG, line, FLAG_LEN) == 0);
}


int extractCoordinates(char* line)
{
    errno = 0;
    char coordString[COORD_LENGTH+1];
    char* endp;
    strncpy(coordString, line+X_START, COORD_LENGTH);
    float x = strtof( coordString, &endp);
    printf("x is %f", x);

    strncpy(coordString, line+Y_START, COORD_LENGTH);
    float y = strtof( coordString, &endp);
    printf("y is %f", y);

    strncpy(coordString, line+Z_START, COORD_LENGTH);
    float z = strtof(coordString, &endp);
    printf("z is %f", z);

    if((x==0||y==0||z==0) && (errno != 0 || endp == line ))
    {
        fprintf(stderr, "Error: input is not a valid float\n" );
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
