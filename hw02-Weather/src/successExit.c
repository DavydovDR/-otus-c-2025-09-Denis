#include "includes.h"

int successExit(CURL *curl, MemoryStruct dataStruct) {

	curl_easy_cleanup(curl);	// закрытие сессии CURL
	curl_global_cleanup();		// освобождает ресурсов CURL
	free(dataStruct.data);			// освобождение памяти, выделенной под сохранение данных

	return EXIT_SUCCESS;
}
