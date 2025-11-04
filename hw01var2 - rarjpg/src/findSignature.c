/*
 * findSignature.c
 *
 *  Created on: 2 нояб. 2025 г.
 *      Author: denis
 */

#include <stdio.h>
#include <stdlib.h>

int* findSignature(FILE *file, const int signature[], int *counter) {

	int *signaturesArray = NULL;					// общее количество найденных сигнатур
	int position = 0;				// адрес стартового байта найденной сигнатуры
	long fileSize = 0;				// размер файла
	int currentSymbol = 0;				// переменная для считывания текущего байта
	int filePointer = 0;

	// определение размера файла в байтах путем установки указателя в конец файла и определения его адреса
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);

	// проход файла для подсчета количества сигнатур
	fseek(file, 0, 0);										// установка указателя в начало файла
	for (long i = 0; i < fileSize; i++) {
		currentSymbol = fgetc(file);						// считывание очередного байта из файла
		if (currentSymbol == signature[0]) {				// если считанный байт совпал с первым байтом сигнатуры, то
			currentSymbol = fgetc(file);					// считывание очередного байта  из файла
			if (currentSymbol == signature[1]) {			// если считанный байт совпал со вторым байтом сигнатуры, то
				currentSymbol = fgetc(file);				// считывание очередного байта  из файла
				if (currentSymbol == signature[2]) {		// если считанный байт совпал с третьим байтом сигнатуры, то
					currentSymbol = fgetc(file);			// считывание очередного байта  из файла
					if (currentSymbol == signature[3]) {	// если 4 считанных байта совпали с заданной сигнатурой, то
						counter[0]++;
					}
				}
			}
		}
	}

	// выделение памяти для сохранения адресов сигнатур
	if (counter[0] != 0) {
		signaturesArray = (int*) calloc(*counter, sizeof(int));
		if (!signaturesArray) {
			printf("Error of realloc function");
		}
	}

	// повторный проход файла для записи начальных адресов сигнатур
	fseek(file, 0, 0);										// установка указателя в начало файла
	for (long i = 0; i < fileSize; i++) {
		currentSymbol = fgetc(file);							// считывание очередного байта из файла
		if (currentSymbol == signature[0]) {					// если считанный байт совпал с первым байтом сигнатуры, то
			currentSymbol = fgetc(file);						// считывание очередного байта  из файла
			if (currentSymbol == signature[1]) {				// если считанный байт совпал со вторым байтом сигнатуры, то
				currentSymbol = fgetc(file);					// считывание очередного байта  из файла
				if (currentSymbol == signature[2]) {			// если считанный байт совпал с третьим байтом сигнатуры, то
					currentSymbol = fgetc(file);				// считывание очередного байта  из файла
					if (currentSymbol == signature[3]) {		// если 4 считанных байта совпали с заданной сигнатурой, то
						filePointer = ftell(file) - 4;
						signaturesArray[position] = filePointer;	// запись в буфер адрес первого совпавшего байта
						position++;

					}
				}
			}
		}
	}

	return signaturesArray;
}




