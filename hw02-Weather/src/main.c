#include "includes.h"

char *fullUrl;

CURL *curl;
CURLcode curlResult;
MemoryStruct dataStruct;
char errorBuffer[CURL_ERROR_SIZE];



WeatherStruct weather;

int main(int args, char **argv) {

	if (args != 2) {
		printf("Use \"%s --your location\"\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// формирование url
	fullUrl = (char *) calloc(strlen(URL) + strlen(argv[1]) + strlen(REQUEST_FORMAT) + 1, sizeof(char));
	strcat(fullUrl, URL);
	strcat(fullUrl, argv[1]);
	strcat(fullUrl, REQUEST_FORMAT);


	dataStruct.data = malloc(1);
	dataStruct.size = 0;

	curlResult = curl_global_init(CURL_GLOBAL_ALL);	// настройка среды, необходимой для работы curl. Установлены все возможные биты.
	if (curlResult != CURLE_OK) {
		printf("curl global init error: returned %d!\n", curlResult);
		exit(EXIT_FAILURE);
	}

	curl = curl_easy_init(); // открытие сессии CURL
	if (!curl) {
		printf("CURL handle not created!\n");
		exit(EXIT_FAILURE);
	}

	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);			// буфер для сохранения описания возможной ошибки CURL
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/8.16.0");	// выбор агента в GET заголовке
	curl_easy_setopt(curl, CURLOPT_URL, fullUrl);						// адрес для отправки http запросов
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);			// функция для записи данных сессии
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void* )&dataStruct);		// буфер для записи данных сессии
//	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);							// подробный вывод работы curl


	curlResult = curl_easy_perform(curl);
	if (curlResult != CURLE_OK) {
		printf("curl_easy_perform error: %s!\n", errorBuffer);
		exit(EXIT_FAILURE);
	}

	// парсинг JSON-ответа и вывод интересующих элементов
	int result = parseJSON(dataStruct.data, &weather);
	if (result == 0) {
		printf("Chosen area is: %s\n", weather.areaName);
		printf("Current temperature: %s C\n", weather.curTemp);
		printf("Weather describe: %s\n", weather.weatherDescribe);
		printf("Wind direction: %s\n", weather.windDir);
		printf("Wind speed: %s kmph\n", weather.windSpeed);
		printf("Minimum and maximum temperatures of the day: %s and %s C\n", weather.minTemp, weather.maxTemp);
	}

	return (successExit(curl, dataStruct));
}

