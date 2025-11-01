/*
 * Программа принимает аргументами текстовый файл, заданную кодировку cp1251, iso-8859-5 или koi8-r и выходной файл.
 * Полученный файл с заданной кодировкой  преобразуется в файл в кодировке UTF-8
 * и сохраняетяс в выходной файл.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main(int argc, char** argv) {

	if(argc != 4) {
        printf("USAGE: %s <file> currentCode <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *source = fopen(argv[1], "r");
    if(!source) {
		printf("Failed to open %s for reading!\n", argv[1]);
        return EXIT_FAILURE;
    }

    FILE *result = fopen(argv[3], "w");
	if(!result) {
        printf("Failed to open or create %s for writing!\n", argv[3]);
        fclose(source);
        return EXIT_FAILURE;
    }

	if (strcmp(argv[2], "cp1251") == 0) {
		if (cp1251_to_utf(source, result) != 0) {
			printf("Failed to conversion from cp1251 to UTF-8!\n");
			fclose(source);
			fclose(result);
			return EXIT_FAILURE;
		}
    } else if (strcmp(argv[2], "iso-8859-5") == 0) {
		if (iso8859_5_to_utf(source, result) != 0) {
			printf("Failed to conversion from iso-8859-5 to UTF-8!\n");
			fclose(source);
			fclose(result);
			return EXIT_FAILURE;
		}
    } else if (strcmp(argv[2], "koi8-r") == 0) {
		if (koi8r_to_utf(source, result) != 0) {
			printf("Failed to conversion from koi8-r to UTF-8!\n");
			fclose(source);
			fclose(result);
			return EXIT_FAILURE;
		}

    } else {
		fclose(source);
		fclose(result);
		printf("Enter one of this codes as current code: \"cp1251\", \"iso-8859-5\", \"koi8-r\"\n");
		return EXIT_FAILURE;
	}

	fclose(source);
	fclose(result);
    return EXIT_SUCCESS;
}




