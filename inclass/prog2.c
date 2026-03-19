#include <stdio.h>

int main() {
	// files are stored in seondary storage (disk - ssd/hdd)
	// when a c program accesses a file
	// 1. the os reads data from the disk
	// 2. that data is copied into RAM as buffer
	// buffer is temporary data
	// 3. your program works with the buffer data
	

	FILE *fp = fopen("sample.txt", "r"); // opens file in read mode
	char buffer[100];

	// fwrite, fputc, fputs, fprintf (functions that let you write to a file)
	// fread, fgetc, fgets, fscanf (functions that let you read a file)
	
	fgets(buffer, sizeof(buffer), fp);

	printf("%s", buffer);
}

