/*
 ============================================================================
 Name        : hw01var2.c
 Author      : DavydovDR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "utils.h"


int *eocdStartBytes;		// массив адресов начала сигнатур EOCD
int *eocdCounter;			// счетчик найденных сигнатур EOCD

int *lfhStartBytes;			// массив адресов начала сигнатур LFH
int *lfhCounter;			// счетчик найденных сигнатур LFH

int *cdfhStartBytes;		// массив адресов начала сигнатур CDFH
int *cdfhCounter;			// счетчик найденных сигнатур CDFH

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printf("USAGE: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE* file = fopen(argv[1], "rb");
	if(!file) {
		printf("Failed to open %s for reading!\n", argv[1]);
		return EXIT_FAILURE;
	}

	// инициализация счетчика сигнатур EOCD нулевым значением
	int tempEocdCounter = 0;
	eocdCounter = &tempEocdCounter;

	// поиск сигнатур EOCD в файле
	eocdStartBytes = findSignature(file, eocdSignature, eocdCounter);

	// завершение работы, если сигнатуры EOCD не найдены
	if (*eocdCounter == 0) {
		printf("File %s is not ZIP\n", argv[1]);
		goto exit;
	}

	// проверка на уникальность сигнатуры EOCD в файле
	if(*eocdCounter > 1)  {
		printf("File %s contains more then one EOCD signatures. File is damaged\n", argv[1]);
		goto exit;
	}

	// инициализация счетчика сигнатур LFH нулевым значением
	int tempLfhCounter = 0;
	lfhCounter = &tempLfhCounter;

	// поиск сигнатур LFH в файле
	lfhStartBytes = findSignature(file, lfhSignature, lfhCounter);

	// инициализация счетчика сигнатур CDFH нулевым значением
	int tempCdfhCounter = 0;
	cdfhCounter = &tempCdfhCounter;

	// поиск сигнатур CDFH в файле
	cdfhStartBytes = findSignature(file, cdfhSignature, cdfhCounter);

	// проверка на соответствие количества записей в EOCD количеству найденных LFH и CDFH
	fseek(file, *eocdStartBytes + 10, SEEK_SET);
	int byte1 = fgetc(file);
	int byte2 = fgetc(file);
	if ( byte1 + (byte2 << 8) != *lfhCounter) {
		printf("Amount of LFH and total central directory record in file %s "
				"not equal. File is damaged\n", argv[1]);
		goto exit;
	}
	if (*lfhCounter != *cdfhCounter) {
		printf("Amount of LFH  and amount of CDFH in file %s not equal.\n"
				"File is damaged!\n", argv[1]);
		goto exit;
	}
	// вывод имен файлов и директорий
	for (int i = 0; i < *lfhCounter; i++) {
		fseek(file, lfhStartBytes[i] + 26, SEEK_SET);
		byte1 = fgetc(file);
		byte2 = fgetc(file);
		int fileNameLenght = byte1 + (byte2 << 8);
		fseek(file, 2, SEEK_CUR);
		char *fileName = calloc(fileNameLenght, sizeof(char));
		fread(fileName, 1, fileNameLenght, file);
		printf("%s\n", fileName);
		free(fileName);
	}

	exit:
	if (fclose(file) != 0) {
		printf("Failed to close %s!\n", argv[1]);
		return EXIT_FAILURE;;
	}
	return EXIT_SUCCESS;
}
