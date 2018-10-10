#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


char speChar(char hex) {
	int i = 0;
	char arr[] = 
	{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
	,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E
	,0x1F,0x20,0x7F};
	
	while (i<sizeof(arr)) {
		if (hex == arr[i]) {
			return 0x00;
		}
		i++;
	}
	return hex;
}

int main(int arg, char* argc[])
{
	//Defining format	
	int* addr = (int*)0x00000000;
	printf("\t\t00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F \n");
	printf("\t\t===============================================");
	printf("\n%p\t", addr);
	//Opening file
	FILE* pFile;
	int i = 0, j = 0;
	char* filename = (char*)argc[1];
	int file = fopen_s(&pFile, filename, "rb");
	//Calculation of file size
	fseek(pFile, 0, SEEK_END);
	int filesize = ftell(pFile);
	//Point the file pointer back to file original
	fseek(pFile, 0, SEEK_SET);
	//Create dynamic buffer in heap zone
	unsigned char* buf = (unsigned char*)malloc(sizeof(char)*filesize);
	memset(buf, 0, filesize);
	if (file == 0) {
		int read = fread_s(buf, sizeof(char)*filesize, filesize, 1, pFile);
		while (i <filesize) {//filesize
			if (j<16) {
				printf("%02x ", buf[i]);
				j++;
				i++;
			}
			else {
				j = i - 16;
				printf(" \t");
				while (j<i) {
					printf("%c ", speChar(buf[j]));
					j++;
				}
				j = 0;
				printf("\n%p\t",addr+=4);
			}
			
		}
	}
	else {
		fclose(pFile);
		return 0;
	}
	fclose(pFile);
	free(buf);
}

