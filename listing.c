#include <stdio.h>
#include <Windows.h>

void setConsoleEncoding();

FILE* openPrnFile();

FILE* createCsvFile();

void convertPrnToCsv(FILE* prnFile, FILE* csvFile);

int main()
{
	setConsoleEncoding();

    FILE* prnFile = openPrnFile();
    FILE* csvFile = createCsvFile();

    convertPrnToCsv(prnFile, csvFile);

    fclose(prnFile);
    fclose(csvFile);

    printf("Конвертация PRN-файла в CSV-файл завершена успешно\n");

    system("pause");
    return 0;
}

void setConsoleEncoding()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

FILE* openPrnFile()
{
    char input[100];
    char extension_prn[] = ".prn";
    printf("Введите имя файла для чтения (*.prn): ");
    scanf("%s", input);
    strcat(input, extension_prn);
	FILE* prnFile = fopen(input, "r");
	if (prnFile == NULL)
	{
        printf("Не удалось открыть PRN-файл\n");
        exit(1);
    }
    return prnFile;
}

FILE* createCsvFile()
{
    char output[100];
    char extension_csv[] = ".csv";
    printf("Введите имя файла для записи (*.csv): ");
    scanf("%s", output);
    strcat(output, extension_csv);
    FILE* csvFile = fopen(output, "w");
	if (csvFile == NULL)
	{
        printf("Не удалось создать CSV-файл\n");
        exit(1);
    }
    return csvFile;
}

void convertPrnToCsv(FILE* prnFile, FILE* csvFile)
{
	char line[256];
	while (fgets(line, sizeof(line), prnFile))
	{
		char* token = strtok(line, " \t\n");
		while (token != NULL)
		{
            fprintf(csvFile, "%s,", token);
            token = strtok(NULL, " \t\n");
		}
        fprintf(csvFile, "\n");
    }
}
