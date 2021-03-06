#include <stdio.h>
#include <string.h>
void assemble(char[]);

int firstPass(FILE* file, int* labels, int lc);
void printLabels(int* labels);

int main(int argc, char **argv)
{
	
	
	
	if (argc > 1)
	{
		assemble(argv[1]);
	}
	else
	{
		char filename[128] = "test1.asm";		
		assemble(filename);
		printf("----------------------------------------------------------------\n");
		printf("labels = {12292, 12302, 12311, 12312, 12313, -1, -1, -1, -1, -1}\n");
		printf("If your code is correct, the line above the dashed line\n");
		printf("should EXACTLY match the line below the dashed line.\n");
	}
}
