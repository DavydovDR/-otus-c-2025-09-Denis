#include <stdlib.h>
#include <stdio.h>
#include ".\curl\include\curl\curl.h"


CURL *curl;

char *location;

int main(int args, char **argv) {

	if (args !=2) {
		printf("Use \"%s location\"", argv[0]);
		return EXIT_FAILURE;
	}

	location = strdup(argv[1]);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://wttr.in/");
	}

	return 0;
}

