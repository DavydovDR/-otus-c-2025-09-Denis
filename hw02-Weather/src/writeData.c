
#include "includes.h"

size_t writeData(void *content, size_t size, size_t countOfmembers, void *ptr) {

	size_t dataSize = size * countOfmembers;									// определение объема необходимой памяти

	MemoryStruct *dataStruct = (MemoryStruct*) ptr;								// инициализация структуры памяти

	char *buffer = realloc(dataStruct->data, dataStruct->size + dataSize +1);	// выделение памяти для хранения данных

	if (!buffer) {																// обработка ошибки выделения памяти
		printf("realloc returned error!\n");
		exit(EXIT_FAILURE);
	}

	dataStruct->data = buffer;													// присвоение указателю data адреса выделенной памяти
	memmove(&(dataStruct->data[dataStruct->size]), content, dataSize);			// копирование входных данных в область памяти data
	dataStruct->size += dataSize;												// сохранение объема записанных данных
	dataStruct->data[dataStruct->size] = 0;										// запись нуля в последнюю ячейку выделенной памяти (для curl)

	return dataSize;
}
