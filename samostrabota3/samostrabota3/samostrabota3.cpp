#include<iostream>
#include <fstream>
#include<string>
#include<conio.h>

using namespace std;

struct my {
	int number1 = 0;
	int number2 = 0;
	string str1;
	string str2;
} st;

my* readDataFromFile(string, int&);
my* resizeArray(int&, int, my*);
void writeMasInFile(string, my*, int, int);
int findSizeOfFile(string);
void sort(string, my*, int);

my* readDataFromFile(string fileName, int& size)
{
	ifstream file(fileName);
	file.open(fileName, ios::in);

	if (!file.is_open()) {
		return nullptr;
	}

	size <= 0 ? size = 10 : size = size;
	my* mas = new my[size];

	int numberOfLines = 0;

	while (!file.eof())
	{
		if (numberOfLines == size)
		{
			mas = resizeArray(size, size + 1, mas);
		}

		file >> mas[numberOfLines].number1;
		file >> mas[numberOfLines].number2;
		file >> mas[numberOfLines].str1;
		file >> mas[numberOfLines].str2;

		numberOfLines++;
	}

	mas = resizeArray(size, numberOfLines - 1, mas);
	file.close();
}

my* resizeArray(int& oldSize, int newSize, my* mas)
{
	if (oldSize == newSize) {
		return mas;
	}

	my* newMas = new my[newSize];
	oldSize = newSize < oldSize ? oldSize : oldSize;

	for (int i = 0; i < oldSize; i++)
	{
		newMas[i] = mas[i];
	}

	oldSize = newSize;

	delete[] mas;

	return newMas;
}

void writeMasInFile(string path, my* mas, int size, int openMode)
{
	ofstream fout(path, openMode);
	fout.open(path, ios::out);

	if (!fout.is_open())
	{
		cout << "ERROR!" << endl;
		return;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		fout << mas[i].number1 << " " << mas[i].number2 << " " << mas[i].str1 << " " << mas[i].str2 << endl;
	}

	fout.close();
}

int findSizeOfFile(string fileName)
{
	ifstream file(fileName);
	file.open(fileName, ios::in);

	if (!file.is_open()) {
		return 0;
	}

	file.seekg(0, std::ios_base::end);

	int sizeOfFile = file.tellg();

	file.close();

	return  sizeOfFile;
}

void sort(string fileName, my* mas, int size)
{
	ifstream file(fileName);
	file.open(fileName, ios::in);

	if (!file.is_open()) {
		return;
	}

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; i < size; j++)
		{
			my pr;
			if (mas[i].number1 > mas[j].number1)
			{
				pr = mas[i];
				mas[i] = mas[j];
				mas[j] = pr;
			}
		}
	}

	file.close();
}

int main()
{
	int size = 1;

	string fileName = "firstFile.txt";
	my* mas = readDataFromFile(fileName, size);

	string path = "newFile.txt";
	writeMasInFile(path, mas, size, ios_base::out);

	cout << "\nSize of file is " << findSizeOfFile(fileName) << endl;
	sort(fileName, mas, size);
}