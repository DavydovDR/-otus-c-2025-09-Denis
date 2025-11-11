/*
 * writeData.c
 *
 *  Created on: 10 нояб. 2025 г.
 *      Author: denis
 */

#include "includes.h"

size_t writeData(void *content, size_t size, size_t countOfmembers, void *ptr) {

	size_t dataSize = size * countOfmembers;// определение объема необходимой памяти

	MemoryStruct *dataStruct = (MemoryStruct*) ptr;// инициализация структуры памяти

	char *buffer = realloc(dataStruct->data, dataStruct->size + dataSize +1);	// выделение памяти для хранения данных

	if (!buffer) {							// обработка ошибки выделения памяти
		printf("realloc returned error!\n");
		exit(EXIT_FAILURE);
	}

	dataStruct->data = buffer;	// копирование адреса выделенной памяти в указатель memory структуры
	memmove(&(dataStruct->data[dataStruct->size]), content, dataSize);	// копирование входных данных в область памяти memory
	dataStruct->size += dataSize;	// сохранение объема записанных данных в переменную size структуры
	dataStruct->data[dataStruct->size] = 0;

	return dataSize;
}
