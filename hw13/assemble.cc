#include <stdio.h>
#include <string.h>

#define LIMIT 10000
#define LINE_SIZE 128

//For part 1
void assemble(char[]);
int findOrigin(FILE*);
int firstPass(FILE*, int[], int);
void printLabels(int[]);
void removeSpace(char[]);
void allUppercase(char[]);

//For part 2
int getAdd(char[]);
int getAnd(char[]);
int getTrap(char[]);
int getNot(char[]);
int getLd(char[], int[], int);
int getLdr(char[]);
int getSt(char[], int[], int);
int getStr(char[]);
int getBr(char[], int[], int);
int getIt(int, char[]);
int secondPass(FILE*, int[], int);

void assemble(char filename[])
{
    //Open the file for reading
    FILE *infile = fopen( filename , "r" );

    if (infile != NULL) 
    {    
        //Create labels array and set all elements to -1.  
        int labels[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

        int lc = findOrigin(infile);

        if (lc > -1)
        {
            //Read in label values
            if (!firstPass(infile, labels, lc))
            {
                //Show the labels.
                //printLabels(labels);

                //The following is for part 2
                secondPass(infile, labels, lc);
            }
        }

        //Close the file
        fclose(infile);

    } 
    else 
    {	
        printf("Can't open input file.\n");		
    }    

}


int findOrigin(FILE *infile)
{
    //Each trip through the while loop will read the next line of infile
    //into the line char array as a null terminated string.
    char line[LINE_SIZE]; 

    //The variable lineCount keeps track of how many lines have been read.
    //It is used to guard against infinite loops.  Don't remove anything
    //that has to do with linecount.
    int lineCount = 0; //

    //For getting out of the while loop.
    int done = 0;

    //For getting rid of the trailing newline
    char c;

    int error = 1;
    int i = 0;
    int originValue = 0;
    char *ptr;

    //Read lines until EOF reached or LIMIT lines read.  Limit prevent infinite loop.
    while (!done && lineCount < LIMIT && fscanf(infile, "%[^\n]s", line) != EOF)
    {
        lineCount++;

        fscanf(infile, "%c", &c);  //Get rid of extra newline.

        //printf("%s\n", line);

        //At this point, line contains the next line of the ASM file.
        //Put your code here for seeing if line is an origin.
        //Options:
        //	1. line is an origin (save value, set done = 1).  
        //  2. line is a blank line (skip).
        //  3. line is a comment (skip).
        //  4. line is anything else (print error, set done = 1).

        removeSpace(line);
        allUppercase(line);

        //printf("%s\n", line);
        for (i = 0; i < LINE_SIZE; i++)
        {
            if (line[i] == '.' && line[i+1] == 'O')
            {
                if (line[i+5] == 'X')
                {
                    ptr = &line[i+6];
                    sscanf(ptr, "%X", &originValue);
                    done = 1;
                    error = 0;
                    //printf("Hex Origin found: %X\n", originValue);
                }
                else
                {
                    ptr = &line[i+5];
                    sscanf(ptr, "%d", &originValue);
                    done = 1;
                    error = 0;
                    //printf("Decimal Origin found: %d\n", originValue);
                }
            }
        }

        //Set the line to empty string for the next pass.
        line[0] = 0;
    }


    //At this point you must decide if an origin was found or not.
    //How you do this is up to you.
    //If a good origin was found, check the size.  
    //		if it is too big, print an error and return -1.
    //      if it is not too big, return the value.
    //If a good origin was NOT found, print the error message and return -1.
    if (error == 0)
    {
        if (originValue > 0xFFFF)
        {
            printf("ERROR 2: Bad origin address. Address too big for 16 bits.\n");
            return -1;
        }
        else
        {
            return originValue;
        }
    }
    else
    {
        printf("ERROR 1: Missing origin directive. Origin must be first line in program.");
        return -1;
    }

}

int firstPass(FILE *infile, int labels[], int lc)
{
    //Create a while loop similar to findOrigin.
    //You can rewind if you want to but you shouldn't have to.
    //rewind(infile);

    //Read a line.
    //If the line is a comment, a blank line or the .orig directive, don’t do anything.
    //If the line is a label on a line by itself, save the lc to the labels array at the appropriate position.
    //	For example, if L3, store the lc value in labels[3].
    //If the line is a label followed by .fill, save the lc in labels AND increment lc.
    //If the line is .end, return 0 for done with no error.
    //If the end of file is reached before .end is found print the error and return -1.
    //If the line is one of the allowed instructions (ADD, AND, NOT, LD, LDR, ST, STR, BR, and TRAP) increment the lc.
    //If the line is anything else print the unknown instruction error and return -1.
    char line[LINE_SIZE];
    int lineCount = 0;
    char c;
    int done = 0;
    int i = 0;
    int labelNum = 0;
    int lineFinished = 0;
    int error = 1;
    int instructionFound = 0;
    char fill[10] = {".FILL"};
    char origin[6] = {".ORIG"};
    char comment[2] = {";"};

    while (!done && lineCount < LIMIT && fscanf(infile, "%[^\n]s", line) != EOF)
    {
        lineCount++;

        fscanf(infile, "%c", &c);

        removeSpace(line);
        allUppercase(line);

        //printf("%s\n", line);

        for (i = 0; line[i] != 0; i++)
        {
            if (strstr(line, origin) != NULL || strstr(line, comment) != NULL)
            {
                lineFinished = 1;
            }
            else if (lineFinished != 1 && line[i] == 'L' && ((line[i+1] - 48) > -1) && ((line[i+1] - 48) < 10))
            {
                if (strstr(line, fill) != NULL)
                {
                    labelNum = line[i+1] - 48;
                    //printf("Found Label %d at: %d\n", labelNum, lc);
                    labels[labelNum] = lc;
                    lc++;
                    lineFinished = 1;
                }
                else
                {
                    labelNum = line[i+1] - 48;
                    //printf("Found Label %d at: %d\n", labelNum, lc);
                    labels[labelNum] = lc;
                    lineFinished = 1;
                }
            }
            //line[i] > 32 && line[i] < 127 && line[i] != ';' && line[i] != ' ' && line[i] != '.'
            else if (lineFinished != 1 && line[i] == '.' && line[i+1] == 'E')
            {
                error = 0;
                done = 1;
                lineFinished = 1;
            }
            else if (lineFinished != 1 && line[i] > 32 && line[i] < 127 && line[i] != ';' && line[i] != ' ')
            {
                char instructions[45] = {"ADD,AND,NOT,LD,LDR,ST,STR,BR,TRAP"};
                char *token = strtok(instructions, ",");
                while (instructionFound != 1 && token != NULL)
                {
                    //printf("%s\n", token);
                    //printf("%s\n", line);
                    if (strstr(line, token) != NULL)
                    {
                        //printf("Instruction Found: %s\n", token);
                        lc++;
                        instructionFound = 1;
                        lineFinished = 1;
                    }
                    token = strtok(NULL, ",");
                }
                if (instructionFound == 0)
                {
                    printf("ERROR 3: Unknown instruction.\n");
                    return -1;
                }
            }
        }
        instructionFound = 0;
        lineFinished = 0;
        line[0] = 0;
    }
    if (error == 1)
    {
        printf("ERROR 4: Missing end directive.\n");
        return -1;
    }
    else
    {
        return 0;
    }

}

void printLabels(int labels[])
{
    printf("labels = {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d}\n", labels[0], labels[1], labels[2], labels[3], labels[4], labels[5], labels[6],
            labels[7], labels[8], labels[9]);
}

int secondPass(FILE* infile, int labels[], int lc)
{
    char line[LINE_SIZE];
    int lineCount = 0;
    char c;
    int i = 0;
    int lineFinished = 0;

    rewind(infile);
    printf("%X\n", lc);


    while (lineCount < LIMIT && fscanf(infile, "%[^\n]s", line) != EOF)
    {
        lineCount++;
        fscanf(infile, "%c", &c);

        removeSpace(line);
        allUppercase(line);

        printf("LC: %d\n", lc);

        for (i = 0; line[i] != 0; i++)
        {
            if (lineFinished != 1 && line[i] == ';')
            {
                lineFinished = 1;
            }
            if (line[i] == '.' && line[i+1] == 'F')
            {
                lc++;
                printf("0000\n");
                lineFinished = 1;
            }
            else if (lineFinished != 1 && line[i] == '.' && line[i+1] == 'E')
            {
                return 1;
            }
            else if (lineFinished != 1 && line[i] > 32 && line[i] < 127 && line[i] != ';' && line[i] != ' ')
            {
                int instructionFound = 0;
                char instructions[45] = {"ADD,AND,NOT,LDRR,LD,STRR,ST,BR,TRAP"};
                char *token = strtok(instructions, ",");
                while(instructionFound != 1 && token != NULL)
                {
                    if (strstr(line, token) != NULL)
                    {
                        instructionFound = 1;
                        lc++;
                        //Each of these getters should print the value (just add printf's around them)
                        if (strncmp(token, "ADD", 3) == 0)
                        {
                            printf("Found Instruction ADD\n");
                            printf("%X\n", getAdd(line));
                        }
                        else if (strncmp(token, "AND", 3) == 0)
                        {
                            printf("Found Instruction AND\n");
                            printf("%X\n", getAnd(line));
                        }
                        else if (strncmp(token, "NOT", 3) == 0)
                        {
                            printf("Found Instruction NOT\n");
                            printf("%X\n", getNot(line));
                        }
                        else if (strncmp(token, "LDRR", 4) == 0)
                        {
                            printf("Found Instruction LDR\n");
                            printf("%X\n", getLdr(line));
                        }
                        else if (strncmp(token, "LD", 2) == 0)
                        {
                            printf("Found Instruction LD\n");
                            printf("%X\n", getLd(line, labels, lc));
                        }
                        else if (strncmp(token, "STRR", 4) == 0)
                        {
                            printf("Found Instruction STR\n");
                            printf("%X\n", getStr(line));
                        }
                        else if (strncmp(token, "ST", 2) == 0)
                        {
                            printf("Found Instruction ST\n");
                            printf("%X\n", getSt(line, labels, lc));
                        }
                        else if (strncmp(token, "BR", 2) == 0)
                        {
                            printf("Found Instruction BR\n");
                            printf("0%X\n", getBr(line, labels, lc));
                        }
                        else if (strncmp(token, "TRAP", 4) == 0)
                        {
                            printf("Found Instruction TRAP\n");
                            printf("%X\n", getTrap(line));
                        }
                    }
                    token = strtok(NULL, ",");
                }
                lineFinished = 1;
            }
        }
        lineFinished = 0;
        line[0] = 0;
    }
    return 0;
}

void removeSpace(char line[])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < LINE_SIZE; i++)
    {
        if (line[i] != ' ')
        {
            line[j] = line[i];
            j++;
        }
    }
}

void allUppercase(char line[])
{
    int i = 0;
    for (i = 0; i < LINE_SIZE; i++)
    {
        if (line[i] >= 'a' && line[i] <= 'z')
        {
            line[i] = line[i] - 32;
        }
    }
}

int getAdd(char line[])
{
    int i = 0;
    int value = 4096;
    int destRegister = -1;
    int sourceRegister1 = -1;
    int sourceRegister2 = -1;
    int immediateVal = 0;
    int isImmediate = 0;
    char immediate[2] = {"#"};
    if (strstr(line, immediate) != NULL)
    {
        isImmediate = 1;
    }
    for (i = 0; line[i] != 0; i++)
    {
        if (isImmediate == 1)
        {
            if (line[i] == 'R' && destRegister == -1)
            {
                destRegister = line[i+1] - 48;
                //printf("DR: %d\n", destRegister);
            }
            else if (line[i] == 'R' && destRegister != -1)
            {
                sourceRegister1 = line[i+1] - 48;
                //printf("SR1: %d\n", sourceRegister1);
            }
            else if (line[i] == '#')
            {
                if (line[i+1] == '-')
                {

                    if (line[i+3] != ' ' && line[i+3] != '\n' && line[i+3] > 47 && line[i+3] < 58)
                    {
                        immediateVal = immediateVal - (line[i+3] - 48);
                        immediateVal = immediateVal - 10;
                    }
                    else
                    {
                        immediateVal = immediateVal - (line[i+2] - 48);
                    }
                    //printf("Immediate Value: %d\n", immediateVal);
                }
                else
                {
                    if (line[i+2] != ' ' && line[i+2] != '\n' && line[i+2] > 47 && line[i+2] < 58)
                    {
                        immediateVal = immediateVal + (line[i+2] - 48);
                        immediateVal = immediateVal + 10;
                    }
                    else
                    {
                        immediateVal = immediateVal + (line[i+1] - 48);
                    }
                    //printf("Immediate Value: %d\n", immediateVal);
                }
            }
        }
        if (isImmediate == 0)
        {
            if (line[i] == 'R' && destRegister == -1)
            {
                destRegister = line[i+1] - 48;
                //printf("DR: %d\n", destRegister);
            }
            else if (line[i] == 'R' && destRegister != -1 && sourceRegister1 == -1)
            {
                sourceRegister1 = line[i+1] - 48;
                //printf("SR1: %d\n", sourceRegister1);
            }
            else if (line[i] == 'R' && sourceRegister1 != -1)
            {
                sourceRegister2 = line[i+1] - 48;
                //printf("SR2: %d\n", sourceRegister2);
            }
        }
    }
    if (isImmediate == 0)
    {
        //The amount shifted should be 9 the first time then 6 the second time
        //printf("DR pre-shift: %d\n", destRegister);
        destRegister = destRegister << 9;
        //printf("DR post-shift: %d\n", destRegister);
        value = value | destRegister;
        //printf("Value post-or: %d\n", value);
        //printf("SR1 pre-shift: %d\n", sourceRegister1);
        sourceRegister1 = sourceRegister1 << 6;
        //printf("SR1 post-shift: %d\n", sourceRegister1);
        value = value | sourceRegister1;
        //printf("Value post-or: %d\n", value);
        value = value | sourceRegister2;
        //printf("SR2 value: %d\n", sourceRegister2);
        //printf("Value post-or: %d\n", value);
    }
    else
    {
        destRegister = destRegister << 9;
        value = value | destRegister;
        sourceRegister1 = sourceRegister1 << 6;
        value = value | sourceRegister1;
        value = value | (1 << 5);
        if (immediateVal < 0)
        {
            immediateVal += 32;
        }
        value = value | immediateVal;

    }
    return value;
}

int getAnd(char line[])
{
    int i = 0;
    int value = 20480;
    int destRegister = -1;
    int sourceRegister1 = -1;
    int sourceRegister2 = -1;
    int isImmediate = 0;
    int immediateVal = 0;
    char immediate[2] = {"#"};
    if (strstr(line, immediate) != NULL)
    {
        isImmediate = 1;
    }
    for (i = 0; line[i] != 0; i++)
    {
        if (isImmediate == 1)
        {
            if (line[i] == 'R' && destRegister == -1)
            {
                destRegister = line[i+1] - 48;
            }
            else if (line[i] == 'R' && destRegister != -1)
            {
                sourceRegister1 = line[i+1] - 48;
            }
            else if (line[i] == '#')
            {
                if (line[i+1] == '-')
                {
                    if (line[i+3] != ' ' && line[i+3] != '\n' && line[i+3] > 47 && line[i+3] < 58)
                    {
                        immediateVal = immediateVal - (line[i+3] - 48);
                        immediateVal = immediateVal - 10;
                    }
                    else
                    {
                        immediateVal = immediateVal - (line[i+2] - 48);
                    }
                }
                else
                {
                    if (line[i+2] != ' ' && line[i+2] != '\n' && line[i+2] > 47 && line[i+3] < 58)
                    {
                        immediateVal = immediateVal + (line[i+2] - 48);
                        immediateVal = immediateVal + 10;
                    }
                    else
                    {
                        immediateVal = immediateVal + (line[i+1] - 48);
                    }
                }
            }
        }
        if (isImmediate == 0)
        {
            if (line[i] == 'R' && destRegister == -1)
            {
                destRegister = line[i+1] - 48;
            }
            else if (line[i] == 'R' && destRegister != -1 && sourceRegister1 == -1)
            {
                sourceRegister1 = line[i+1] - 48;
            }
            else if (line[i] == 'R' && sourceRegister1 != -1)
            {
                sourceRegister2 = line[i+1] - 48;
            }
        }
    }
    if (isImmediate == 0)
    {
        //The amount shifted should be 9 the first time then 6 the second time
        destRegister = destRegister << 9;
        value = value | destRegister;
        sourceRegister1 = sourceRegister1 << 6;
        value = value | sourceRegister1;
        value = value | sourceRegister2;
    }
    else
    {
        destRegister = destRegister << 9;
        value = value | destRegister;
        sourceRegister1 = sourceRegister1 << 6;
        value = value | sourceRegister1;
        value = value | (1 << 5);
        if (immediateVal < 0)
        {
            immediateVal += 32;
        }
        value = value | immediateVal;

    }
    return value;

}

int getNot(char line[])
{
    int i = 0;
    int value = 36864;
    int destRegister = -1;
    int sourceRegister = -1;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'R' && destRegister == -1)
        {
            destRegister = line[i+1] - 48;
        }
        else if (line[i] == 'R' && destRegister != -1)
        {
            sourceRegister = line[i+1] - 48;
        }
    }
    destRegister = destRegister << 9;
    value = value | destRegister;
    sourceRegister = sourceRegister << 6;
    value = value | sourceRegister;
    value = value | 63;
    return value;
}

int getTrap(char line[])
{
    int i = 0;
    int value = 61472;
    int instNum = -1;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'X' && line[i+1] == '2')
        {
            instNum = line[i+2] - 48;
        }
    }
    //printf("Vector num: %d\n", instNum);
    value = value | instNum;
    return value;
}

int getLdr(char line[])
{
    int i = 0;
    int value = 24576;
    int destRegister = -1;
    int baseRegister = -1;
    int immediateVal = 0;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'R' && line[i+1] != 'R' && destRegister == -1)
        {
            destRegister = line[i+1] - 48;
            //printf("DR: %d\n", destRegister);
        }
        else if (line[i] == 'R' && line[i+1] != 'R' && destRegister != -1)
        {
            baseRegister = line[i+1] - 48;
            //printf("Base Register: %d\n", baseRegister);
        }
        else if (line[i] == '#')
        {
            if (line[i+1] == '-')
            {
                if (line[i+3] != ' ' && line[i+3] != '\n' && line[i+3] > 47 && line[i+3] < 58)
                {
                    immediateVal = immediateVal - (line[i+3] - 48);
                    immediateVal = immediateVal - 10;
                }
                else
                {
                    immediateVal = immediateVal - (line[i+2] - 48);
                }
            }
            else
            {
                if (line[i+2] != ' ' && line[i+2] != '\n' && line[i+2] > 47 && line[i+2] < 58)
                {
                    immediateVal = immediateVal + (line[i+2] - 48);
                    immediateVal = immediateVal + 10;
                }
                else
                {
                    immediateVal = immediateVal + (line[i+1] - 48);
                }
            }
            //printf("Immediate Value: %d\n", immediateVal);
        }
    }
    destRegister = destRegister << 9;
    value = value | destRegister;
    baseRegister = baseRegister << 6;
    value = value | baseRegister;
    if (immediateVal < 0)
    {
        immediateVal += 64;
    }
    value = value | immediateVal;
    return value;
}

int getStr(char line[])
{
    int i = 0;
    int value = 28672;
    int destRegister = -1;
    int baseRegister = -1;
    int immediateVal = 0;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'R' && line[i+1] != 'R' && destRegister == -1)
        {
            destRegister = line[i+1] - 48;
            //printf("DR: %d\n", destRegister);
        }
        else if (line[i] == 'R' && line[i+1] != 'R' && destRegister != -1)
        {
            baseRegister = line[i+1] - 48;
            //printf("Base Register: %d\n", baseRegister);
        }
        else if (line[i] == '#')
        {
            if (line[i+1] == '-')
            {
                if (line[i+3] != ' ' && line[i+3] != '\n' && line[i+3] > 47 && line[i+3] < 58)
                {
                    immediateVal = immediateVal - (line[i+3] - 48);
                    immediateVal = immediateVal - 10;
                }
                else
                {
                    immediateVal = immediateVal - (line[i+2] - 48);
                }
            }
            else
            {
                if (line[i+2] != ' ' && line[i+2] != '\n' && line[i+2] > 47 && line[i+2] < 58)
                {
                    immediateVal = immediateVal + (line[i+2] - 48);
                    immediateVal = immediateVal + 10;
                }
                else
                {
                    immediateVal = immediateVal + (line[i+1] - 48);
                }
            }
            //printf("Immediate Value: %d\n", immediateVal);
        }
    }
    destRegister = destRegister << 9;
    value = value | destRegister;
    baseRegister = baseRegister << 6;
    value = value | baseRegister;
    if (immediateVal < 0)
    {
        immediateVal += 64;
    }
    value = value | immediateVal;
    return value;

}

int getLd(char line[], int labels[], int lc)
{
    int i = 0;
    int value = 8192;
    int destRegister = 0;
    int pcOffset = 0;
    int labelNum = 0;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'R')
        {
            destRegister = line[i+1] - 48;
            //printf("DR: %d\n", destRegister);
        }
        if (line[i] == 'L' && line[i+1] != 'D')
        {
            labelNum = line[i+1] - 48;
            //printf("Label Num: %d\n", labelNum);
        }
    }
    //printf("Label %d: %d\n", labelNum, labels[labelNum]);
    //printf("LC: %d\n", lc);
    pcOffset = labels[labelNum] - lc;
    //printf("PC Offset: %d\n",  pcOffset);
    destRegister = destRegister << 9;
    value = value | destRegister;
    value = value | pcOffset;
    return value;
}

int getSt(char line[], int labels[], int lc)
{
    int i = 0;
    int value = 12288;
    int sourceRegister = -1;
    int pcOffset = 0;
    int labelNum = -1;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'R')
        {
            sourceRegister = line[i+1] - 48;
            //printf("SR: %d\n", sourceRegister);
        }
        if (line[i] == 'L' && line[i+1] != 'D')
        {
            labelNum = line[i+1] - 48;
            //printf("Label Num: %d\n", labelNum);
        }
    }
    //printf("Label %d: %d\n", labelNum, labels[labelNum]);
    //printf("LC: %d\n", lc);
    pcOffset = labels[labelNum] - lc;
    //printf("PC Offset: %d\n",  pcOffset);
    sourceRegister = sourceRegister << 9;
    value = value | sourceRegister;
    value = value | pcOffset;
    return value;

}

int getBr(char line[], int labels[], int lc)
{
    int i = 0;
    int negative = 0;
    int positive = 0;
    int zero = 0;
    int pcOffset = 0;
    int labelNum = -1;
    int value = 0;
    for (i = 0; line[i] != 0; i++)
    {
        if (line[i] == 'N')
        {
            negative = 1;
        }
        if (line[i] == 'Z')
        {
            zero = 1;
        }
        if (line[i] == 'P')
        {
            positive = 1;
        }
        if (line[i] == 'L')
        {
            labelNum = line[i+1] - 48;
            //printf("Label Num: %d\n", labelNum);
        }
    }
    if (!negative && !zero && !positive)
    {
        negative = 1;
        zero = 1;
        positive = 1;
    }
    //printf("Label %d: %d\n", labelNum, labels[labelNum]);
    //printf("LC: %d\n", lc);
    pcOffset = labels[labelNum] - lc;
    negative = negative << 11;
    //printf("N: %d\n", negative);
    value = value | negative;
    zero = zero << 10;
    //printf("Z: %d\n", zero);
    value = value | zero;
    positive = positive << 9;
    //printf("P: %d\n", positive);
    value = value | positive;
    if (pcOffset < 0)
    {
        pcOffset += 512;
    }
    //printf("PC Offset: %d\n", pcOffset);
    value = value | pcOffset;
    return value;
}
