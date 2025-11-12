
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl\curl.h>		// https://github.com/curl/curl.git
#include <cJSON\cJSON.h>	// https://github.com/DaveGamble/cJSON.git


#define URL "http://www.wttr.in/"
#define REQUEST_FORMAT "?format=j2"


// структура буфера для временного хранения данных, полученных curl
typedef struct MemoryStruct{
	char *data;
	size_t size;
} MemoryStruct;


// структура для сохранения значений объектов JSON
typedef struct WeatherStruct{
	char *curTemp;
	char *maxTemp;
	char *minTemp;
	char *windDir;
	char *windSpeed;
	char *weatherDescribe;
	char *areaName;
} WeatherStruct;

// функция, передаваемая в curl для записи данных в буфер
size_t writeData(void *content, size_t size, size_t countOfmembers, void *ptr);

// функция парсинга JSON объекта
int parseJSON(char *data, WeatherStruct *weather);

// функция успешного завершения работы. ЗАкрывает потоки, освобождает память
int successExit(CURL *, MemoryStruct data);
