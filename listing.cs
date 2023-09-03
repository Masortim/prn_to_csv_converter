using System;
using System.IO;

class Program
{
    static void Main()
    {
        SetConsoleEncoding();

        FileStream prnFile = OpenPrnFile();
        FileStream csvFile = CreateCsvFile();

        ConvertPrnToCsv(prnFile, csvFile);

        prnFile.Close();
        csvFile.Close();

        Console.WriteLine("Конвертация PRN-файла в CSV-файл завершена успешно");
        Console.ReadLine();
    }

    static void SetConsoleEncoding()
    {
        Console.InputEncoding = System.Text.Encoding.GetEncoding(1251);
        Console.OutputEncoding = System.Text.Encoding.GetEncoding(1251);
    }

    static FileStream OpenPrnFile()
    {
        Console.Write("Введите имя файла для чтения (*.prn): ");
        string input = Console.ReadLine();
        string path = input + ".prn";
        
        try
        {
            return new FileStream(path, FileMode.Open, FileAccess.Read);
        }
        catch (FileNotFoundException)
        {
            Console.WriteLine("Не удалось открыть PRN-файл");
            Environment.Exit(1);
            return null; // Эта строка никогда не выполнится, но компилятор требует ее наличие
        }
    }

    static FileStream CreateCsvFile()
    {
        Console.Write("Введите имя файла для записи (*.csv): ");
        string output = Console.ReadLine();
        string path = output + ".csv";

        try
        {
            return new FileStream(path, FileMode.Create, FileAccess.Write);
        }
        catch (IOException)
        {
            Console.WriteLine("Не удалось создать CSV-файл");
            Environment.Exit(1);
            return null; // Эта строка никогда не выполнится, но компилятор требует ее наличие
        }
    }

    static void ConvertPrnToCsv(FileStream prnFile, FileStream csvFile)
    {
        StreamReader reader = new StreamReader(prnFile);
        StreamWriter writer = new StreamWriter(csvFile);

        string line;
        while ((line = reader.ReadLine()) != null)
        {
            string[] tokens = line.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (string token in tokens)
            {
                writer.Write(token + ",");
            }
            writer.WriteLine();
        }

        reader.Close();
        writer.Close();
    }
}
