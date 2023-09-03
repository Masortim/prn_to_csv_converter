#include <iostream>
#include <fstream>
#include <string>

void setConsoleEncoding();
std::ifstream openPrnFile();
std::ofstream createCsvFile();
void convertPrnToCsv(std::ifstream& prnFile, std::ofstream& csvFile);

int main()
{
    setConsoleEncoding();

    std::ifstream prnFile = openPrnFile();
    std::ofstream csvFile = createCsvFile();

    convertPrnToCsv(prnFile, csvFile);

    prnFile.close();
    csvFile.close();

    std::cout << "Конвертация PRN-файла в CSV-файл завершена успешно" << std::endl;

    system("pause");
    return 0;
}

void setConsoleEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

std::ifstream openPrnFile()
{
    std::string input;
    std::string extension_prn = ".prn";
    std::cout << "Введите имя файла для чтения (*.prn): ";
    std::cin >> input;
    input += extension_prn;
    std::ifstream prnFile(input);
    if (!prnFile)
    {
        std::cout << "Не удалось открыть PRN-файл" << std::endl;
        exit(1);
    }
    return prnFile;
}

std::ofstream createCsvFile()
{
    std::string output;
    std::string extension_csv = ".csv";
    std::cout << "Введите имя файла для записи (*.csv): ";
    std::cin >> output;
    output += extension_csv;
    std::ofstream csvFile(output);
    if (!csvFile)
    {
        std::cout << "Не удалось создать CSV-файл" << std::endl;
        exit(1);
    }
    return csvFile;
}

void convertPrnToCsv(std::ifstream& prnFile, std::ofstream& csvFile)
{
    std::string line;
    while (std::getline(prnFile, line))
    {
        std::string token;
        size_t pos = 0;
        while ((pos = line.find_first_of(" \t\n", pos)) != std::string::npos)
        {
            token = line.substr(0, pos);
            csvFile << token << ",";
            line.erase(0, pos + 1);
        }
        csvFile << std::endl;
    }
}
