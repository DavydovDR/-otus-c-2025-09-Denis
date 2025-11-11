/*
 * parseJSON.c
 *
 *  Created on: 10 нояб. 2025 г.
 *      Author: denis
 */

#include "includes.h"


cJSON *jroot;   			// корневой объект
cJSON *jCurrentCondition;  	// массив текущего состояния
cJSON *jNearestArea;		// массив региона
cJSON *jRequest;			// массив координат запроса
cJSON *jWeather;			// массив погоды
cJSON *jItem;				// служебная переменная для получения объектов cJSON

// интересующие в рамках ДЗ объекты
cJSON *jCurTemp;
cJSON *jMaxTemp;
cJSON *jMinTemp;
cJSON *jWindDir;
cJSON *jWindSpeed;
cJSON *jWeatherDescribe;
cJSON *jAreaName;

char *city;


int parseJSON(char *data, WeatherStruct *weather) {

	// Получение корневого cJSON:
	jroot = cJSON_Parse(data);
	if (NULL == jroot) {
		printf("Error of parsing data");
		return 1;
	}

	// Получение основных массивов:
	jCurrentCondition = cJSON_GetObjectItem(jroot, "current_condition");
	if (NULL == jCurrentCondition) {
		printf("Error of parsing current_condition array");
		return 1;
	}

	jNearestArea = cJSON_GetObjectItem(jroot, "nearest_area");
	if (NULL == jNearestArea) {
		printf("Error of parsing nearest_area array");
		return 1;
	}

	jRequest = cJSON_GetObjectItem(jroot, "request");
	if (NULL == jRequest) {
		printf("Error of parsing request array");
		return 1;
	}

	jWeather = cJSON_GetObjectItem(jroot, "weather");
	if (NULL == jWeather) {
		printf("Error of parsing weather array");
		return 1;
	}

	// Получение первого и единственного объекта из массива "CurrentCondition"
	jItem = cJSON_GetArrayItem(jCurrentCondition, 0);

	// Получение текущей температуры из массива "CurrentCondition"
	jCurTemp = cJSON_GetObjectItem(jItem, "temp_C");
	if (NULL == jCurTemp)
		return 1;
	weather->curTemp = cJSON_GetStringValue(jCurTemp);

	// Получение описания погоды из массива "CurrentCondition"
	jWeatherDescribe = cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(jItem, "weatherDesc"), 0), "value");
	if (NULL == jCurTemp)
		return 1;
	weather->weatherDescribe = cJSON_GetStringValue(jWeatherDescribe);

	// Получение направления и скорости ветра из массива "CurrentCondition"
	jWindDir = cJSON_GetObjectItem(jItem, "winddir16Point");
	if (NULL == jWindDir)
		return 1;
	weather->windDir = cJSON_GetStringValue(jWindDir);

	jWindSpeed = cJSON_GetObjectItem(jItem, "windspeedKmph");
	if (NULL == jWindSpeed)
		return 1;
	weather->windSpeed = cJSON_GetStringValue(jWindSpeed);

	// Получение названия города для сравнения с введенным в аргументах программы
	jAreaName = cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetArrayItem(jNearestArea, 0), "areaName"), 0), "value");
	if (NULL == jAreaName)
		return 1;
	weather->areaName = cJSON_GetStringValue(jAreaName);

	// Получение максимальной и минимальной суточной температуры из массива "weather"
	jMaxTemp = cJSON_GetObjectItem(cJSON_GetArrayItem(jWeather, 0), "maxtempC");
	if (NULL == jMaxTemp)
		return 1;
	weather->maxTemp = cJSON_GetStringValue(jMaxTemp);

	jMinTemp = cJSON_GetObjectItem(cJSON_GetArrayItem(jWeather, 0), "mintempC");
	if (NULL == jMinTemp)
		return 1;
	weather->minTemp = cJSON_GetStringValue(jMinTemp);


	cJSON_Delete(jroot);
	return 0;
}
