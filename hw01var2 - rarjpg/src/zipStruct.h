/*
 * Описание структуры zip-архива
 */

const int lfhSignature[4] = {0x50, 0x4b, 0x03, 0x04};
const int ddSignature[4] = {0x50, 0x4b, 0x07, 0x08};
const int cdfhSignature[4] = {0x50, 0x4b, 0x01, 0x02};
const int eocdSignature[4] = {0x50, 0x4b, 0x05, 0x06};

struct LocalFileHeader {
    /// Обязательная сигнатура, равна 0x04034b50
   int signature; 						// 4 байта
    // Минимальная версия для распаковки
    int versionToExtract;				// 2 байта (смещение 4)
    // Битовый флаг
    int generalPurposeBitFlag;			// 2 байта (смещение 6)
    // Метод сжатия (0 - без сжатия, 8 - deflate)
    int compressionMethod;				// 2 байта (смещение 8)
    // Время модификации файла
    int modificationTime;				// 2 байта (смещение 10)
    // Дата модификации файла
    int modificationDate;				// 2 байта (смещенеи 12)
    // Контрольная сумма
    int crc32;							// 4 байта (смещение 14)
    // Сжатый размер
    int compressedSize;					// 4 байта (смещение 18)
    // Несжатый размер
    int uncompressedSize;				// 4 байта (смещение 22)
    // Длина название файла
    int filenameLength;					// 2 байта (смещение 26)
    // Длина поля с дополнительными данными
    int extraFieldLength;				// 2 байта (смещение 28)
    // Название файла (размером filenameLength)
    char *filename;						// 1 байт (смещение 29)
    // Дополнительные данные (размером extraFieldLength)
    char *extraField;					// 1 байт (смещение 29 + filenameLength)
};

struct DataDescriptor {
    // Необязательная сигнатура, равна 0x08074b50
    unsigned int signature;
    // Контрольная сумма
    unsigned int crc32;
    // Сжатый размер
    unsigned int compressedSize;
    // Несжатый размер
    unsigned int uncompressedSize;
};

struct CentralDirectoryFileHeader {
    // Обязательная сигнатура, равна 0x02014b50
    unsigned int signature;
    // Версия для создания
    unsigned int versionMadeBy;
    // Минимальная версия для распаковки
    unsigned int versionToExtract;
    // Битовый флаг
    unsigned int generalPurposeBitFlag;
    // Метод сжатия (0 - без сжатия, 8 - deflate)
    unsigned int compressionMethod;
    // Время модификации файла
    unsigned int modificationTime;
    // Дата модификации файла
    unsigned int modificationDate;
    // Контрольная сумма
    unsigned int crc32;
    // Сжатый размер
    unsigned int compressedSize;
    // Несжатый размер
    unsigned int uncompressedSize;
    // Длина название файла
    unsigned int filenameLength;
    // Длина поля с дополнительными данными
    unsigned int extraFieldLength;
    // Длина комментариев к файлу
    unsigned int fileCommentLength;
    // Номер диска
    unsigned int diskNumber;
    // Внутренние аттрибуты файла
    unsigned int internalFileAttributes;
    // Внешние аттрибуты файла
    unsigned int externalFileAttributes;
    // Смещение до структуры LocalFileHeader
    unsigned int localFileHeaderOffset;
    // Имя файла (длиной filenameLength)
    char *filename;
    // Дополнительные данные (длиной extraFieldLength)
    char *extraField;
    // Комментарий к файла (длиной fileCommentLength)
    char *fileComment;
};

struct EOCD {
    // Обязательная сигнатура, равна 0x06054b50 - 4 байта
    int signature;
    // Номер диска - 2 байта
    int diskNumber;
    // Номер диска, где находится начало Central Directory - 2 байта
    int startDiskNumber;
    // Количество записей в Central Directory в текущем диске - 2 байта
    int numberCentralDirectoryRecord;
    // Всего записей в Central Directory - 2 байта
    int totalCentralDirectoryRecord;
    // Размер Central Directory
    int sizeOfCentralDirectory;
    // Смещение Central Directory
    int centralDirectoryOffset;
    // Длина комментария
    int commentLength;
    // Комментарий (длиной commentLength)
    char *comment;
};




