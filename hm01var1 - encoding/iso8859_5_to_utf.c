#include <stdio.h>
#include <stdlib.h>

int iso8859_5_to_utf(FILE *currentFile, FILE *resultFile) {

	int symbol;
	int highByte;
	int lowByte;

	while((symbol = getc(currentFile)) != EOF){
		if (symbol > 0xAF && symbol < 0xF0){	// если символ относится к кириллице, то преобразуем

			/* символы с кодами от 0х80 до 0хBF преднамеренно пропущены, как неприменяемые в тексте задания */
			symbol = symbol + 0x360;		// добавляем смещение для получения кодировки кириллицы в UTF-8

			highByte = symbol >> 6;			// вычленяем 5 старших битов
			highByte = highByte | 0xC0;		// устанавливаем старшие разряды в 110
			fputc(highByte, resultFile);

			lowByte = symbol & 0x3F;		// обнуляем все биты старшего байта и выставляем 10 в старших битах младшего байта
			lowByte = lowByte | 0x80;
			symbol = highByte + lowByte;	// собираем младший и старщий байты
			fputc(lowByte, resultFile);
		} else
			fputc(symbol, resultFile);		// если символ не кириллический, то просто переносим
	}

	return 0;
}

