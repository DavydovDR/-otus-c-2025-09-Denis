
#include <stdio.h>
#include <stdlib.h>
#include <curl\curl.h>		// https://github.com/curl/curl.git
#include <cJSON\cJSON.h>	// https://github.com/DaveGamble/cJSON.git

typedef struct MemoryStruct{
	char *data;
	size_t size;
} MemoryStruct;

typedef struct WeatherStruct{
	char *curTemp;
	char *maxTemp;
	char *minTemp;
	char *windDir;
	char *windSpeed;
	char *weatherDescribe;
	char *areaName;
} WeatherStruct;

size_t writeData(void *content, size_t size, size_t countOfmembers, void *ptr);

int parseJSON(char *data, WeatherStruct *weather);

int successExit(CURL *, MemoryStruct data);
