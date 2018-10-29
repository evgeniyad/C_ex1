/**
 * @func analyzeProteinFile
 * Function gets pointer to a file, reads it line by line,
 * and stores coordinates of real atoms in the
 * @param fileName name of the File to read
 * @return
 */
int analyzeProteinFile(char* fileName)
{
    
    FILE* fileToRead = fopen(fileName, "r");

    if(fileToRead == NULL)  //checking for errors in opening the file
    {
        printf("Error opening file: %s", fileName);
        exit(EXIT_FAILURE);
    }

    float* coordTable[COORD_NUM][MAX_ATOM_NUM];//ANY ELEGANT WAY NOT TO SPEND SO MUCH SPACE (3*20.000) IN ADVANCE
    
 	char newLine[MAX_LINE_SIZE];
    unsigned atomNum = 0; //counter for read atoms

    float x,y,z;
    /**
     * reads atoms until hasn't reach EOF or hasn't counted 20000 atoms
     */
 	while(fgets(newLine, MAX_LINE_SIZE, fileToRead) && (atomNum <= MAX_ATOM_NUM))
 	{
        if( isAtom(newLine))
        {
            x=strtof(newLine[])

        }else //line is not a legitimate atom line - we ignore it
        {

            continue;
        }

 	}

    fclose(fileToRead);
 	return atomNum;

}

/**
 * function decides if given line starts with "ATOM"
 * and therefore is legitimate atom line
 * @param line the line to heck
 * @return true iff line is an atom line
 */
bool isAtom(const char *line)
{
    return strncmp(ATOM_FLAG, line, FLAG_LEN) == 0;
}

/**
 * The function gets a line(in form of string),
 * looks for X, Y and Z coordinates and extracts them in form of floats to given locations
 * @param line pointer to line to extract coordinates from
 * @param x pointer to float to store X coordinate
 * @param y  pointer to float to store y coordinate
 * @param z  pointer to float to store z coordinate
 * @return EXIT_SUCCESS iff all three of the floats were successfully extracted
 */
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


//to check after strtod
char input[50]; // init
char *end;
double result = 0;
errno = 0;
result = strtod(input, &end);
if(result == 0 && (errno != 0 || end == input)) 
{
    fprintf(stderr, "Error: input is not a valid double\n");
    exit(EXIT_FAILURE);
}
*/
