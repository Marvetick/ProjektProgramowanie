//#include "stdafx.h"
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ntverp.h"
#include "string"
#include "fstream"
#include "algorithm"
using namespace std;

struct rekord
{
	const char* nazwa = new char[256];
	const char* producent = new char[256];
	const char* model = new char[50];
	int kategoria;
	int liczba_sztuk;
	float cena;
	const char* data_dostawy = new char[8];
	const char* uwagi = new char[1000];
};
int ZmienPliki()
{
	int ret = 0;
	char oldname[] = "data2.txt";
	char newname[] = "data.txt";

	if (remove("data.txt") != 0)
	{
		perror("Error");
	}
	else
	{
		rename(oldname, newname);
		puts("Rekordy usuniete pomyslnie");
	}
	ret = 1;
	return ret;
}
int ZmienDane(){
	int ret = 0;
	int ir = 0;
	string recId;
	printf("Podaj id rekordu, w ktory chcesz zmienic.\n");
	getline(cin, recId);
	ofstream pisz;
	pisz.open("data2.txt", std::ios::app);
	ifstream stream;
	string line;
	stream.open("data.txt");
	while (getline(stream, line))
	{
		if (ir == stoi(recId))
		{
			string nazwa, producent, model, uwagi, kategoria, liczba_sztuk, cena, data_dostawy;
			int iKategoria;
			printf("\tRekord do zmiany : \n");
			printf("\t%d|", ir);
			printf(line.c_str());
			printf("\n");
			printf("Podaj nowe dane\n");
			printf("Nazwa : ");
			getline(cin, nazwa);
			printf("Producent : ");
			getline(cin, producent);
			printf("Model : ");
			getline(cin, model);
			printf("Kategoria (1 : procesor/2 : karta graficzna/3 : peryferia/4 : plyta glowna/5 : ram/6 : reszta) ");
			getline(cin, kategoria);
			iKategoria = stoi(kategoria);
			printf("Liczba sztuk : ");
			getline(cin, liczba_sztuk);
			printf("Cena : ");
			getline(cin, cena);
			printf("Data dostawy (DD-MM-YY) : ");
			getline(cin, data_dostawy);
			printf("Uwagi : ");
			getline(cin, uwagi);

			pisz << nazwa << '|';
			pisz << producent << '|';
			pisz << model << '|';
			pisz << iKategoria << '|';
			pisz << liczba_sztuk << '|';
			pisz << cena << '|';
			pisz << data_dostawy << '|';
			pisz << uwagi << '\n';
		}
		else
		{
			pisz << line << '\n';
		}
			ir += 1;
	}
	stream.close();
	pisz.close();
	if (ZmienPliki() == 1)
		ret = 1;
	return ret;
}
int UsunRekord()
{
	int idsToDelete[10];
	int iy = 0;
	int ir = 0;
	int ret = 0;
	string idToDelete;
				//przefiltruj
	printf("Podaj ID rekordu, ktory chcesz usunac \n");
	getline(cin, idToDelete);
	//idToDelete = idToDelete[0];
	//int size = idToDelete.size();
	/*if (size > 1)
	{
		for (int ix = 0; ix < idToDelete.length(); ix++)
		{
			if (idToDelete[ix] != ',')
			{
				idsToDelete[iy] = stoi(idToDelete.substr(ix,1));
				iy += 1;
			}
		}
	}
	else*/
		idsToDelete[0] = stoi(idToDelete);
	ofstream pisz;
	pisz.open("data2.txt", std::ios::app);
	ifstream stream;
	string line;
	stream.open("data.txt");
	while (getline(stream, line))
	{
		if (find(idsToDelete, idsToDelete + 10, ir) != idsToDelete + 10)
		{
			ir += 1;
		}
		else
		{
			pisz << line << "\n";
			ir += 1;
		}
	}
	pisz.close();
	stream.close();
	char oldname[] = "data2.txt";
	char newname[] = "data.txt";
	
	if (remove("data.txt") != 0)
	{
		perror("Error");
	}
	else
	{
		rename(oldname, newname);
		puts("Rekordy usuniete pomyslnie");
		ret = 1;
	}
	return ret;
}
int FiltrujDane()
{
	int ret = 0;
	string colFilter;
	string filter;
	printf("Podaj kolumne do filtrowania (1 : Nazwa/ 2 : Model/ 3 : Producent)\n");
	getline(cin,colFilter);
	printf("Podaj ciag do filtracji\n");
	getline(cin, filter);
	int i = 0;
	printf(" -----------------------------------------------------------------------\n|lp|nazwa|producent|model|kategoria|liczba sztuk|cena|data dostawy|uwagi|\n -----------------------------------------------------------------------\n");
	ifstream stream;
	string line;
	stream.open("data.txt");
	while (getline(stream, line))
	{
		string* arr = new string[8];
		//int ix = 0;
		int iy = 0;
		for (int ix = 0; ix < line.length(); ix++)
		{
			if (line[ix] != '|')
				arr[iy] += line[ix];
			else
				iy += 1;
		}	
		if (colFilter == "1")
			if (arr[0] == filter)
			{
				printf("\t%d|", i);
				printf(line.c_str());
				printf("\n");
			}
		else if (colFilter == "2")
			if (arr[1] == filter)
			{
				printf("\t%d|", i);
				printf(line.c_str());
				printf("\n");
			}
		else if (colFilter == "3")
			if (arr[2] == filter)
			{
				printf("\t%d|", i);
				printf(line.c_str());
				printf("\n");
			}
		i += 1;
	}
	ret = 1;
	stream.close();
	return ret;
}
int WyswietlDane()
{
	int ret = 0;
	int i = 0;
	printf(" -----------------------------------------------------------------------\n|lp|nazwa|producent|model|kategoria|liczba sztuk|cena|data dostawy|uwagi|\n -----------------------------------------------------------------------\n");
	ifstream stream;
	string line;
	stream.open("data.txt");
	while (getline(stream, line))
	{
		/*getline(stream, line);*/
		printf("\t%d|", i);
		printf(line.c_str());
		printf("\n");
		i += 1;
	}
	ret = 1;
	stream.close();
	return ret;
}
int Dodaj_Nowy()
{
	rekord nowy;
	string nazwa, producent, model, uwagi, kategoria, liczba_sztuk, cena, data_dostawy;
	int iKategoria;
	//time_t tData_dostawy;
	int ret = 0;
	printf("Nazwa : ");
		getline(cin, nazwa);
		nowy.nazwa = nazwa.c_str();
	printf("Producent : ");
		getline(cin, producent);
		nowy.producent = producent.c_str();
	printf("Model : ");
		getline(cin, model);
		nowy.model = model.c_str();
	printf("Kategoria (1 : procesor/2 : karta graficzna/3 : peryferia/4 : plyta glowna/5 : ram/6 : reszta) ");
		getline(cin, kategoria);
		iKategoria = stoi(kategoria);
		if (iKategoria >= 1 && iKategoria < 7)
			nowy.kategoria = iKategoria;
	printf("Liczba sztuk : ");
		getline(cin, liczba_sztuk);
		nowy.liczba_sztuk = stoi(liczba_sztuk);
	printf("Cena : ");
		getline(cin, cena);
		nowy.cena = stof(cena);
	printf("Data dostawy (DD-MM-YY) : ");
		getline(cin, data_dostawy);
		nowy.data_dostawy = data_dostawy.c_str();
	printf("Uwagi : ");
		getline(cin, uwagi);
		nowy.uwagi = uwagi.c_str();
	ofstream stream;
	stream.open("data.txt", std::ios::app);

	stream << nowy.nazwa << '|';
	stream << nowy.producent << '|';
	stream << nowy.model << '|';
	stream << nowy.kategoria << '|';
	stream << nowy.liczba_sztuk << '|';
	stream << nowy.cena << '|';
	stream << nowy.data_dostawy << '|';
	stream << nowy.uwagi << '\n';
	//stream << "dodano nowy";
	stream.close();
	//stream << nowy.nazwa << '|' << nowy.producent. << '|' << nowy.model << '|' << nowy.kategoria << '|' << nowy.liczba_sztuk << '|' << nowy.cena << '|' << nowy.data_dostawy << '|' << nowy.uwagi;
	printf("Dodano rekord\n");
	ret = 1;
	return ret;
}

int ArrSzukaj(int arr[], int len, int seek)
{
	for (int i = 0; i < len; ++i)
	{
		if (arr[i] == seek) return i;
	}
	return -1;
}
int main()
{
	int ret = 0;
	string menu;
	int men_num;
	printf("Program do inwentaryzacji czesci komputerowych\n");
	printf("Menu :\n\t1.Wyswietl wszystko\n\t2.Dodaj nowy\n\t3.Usun\n\t4.Zmien dane\n\t5.Wyszukaj\n. Wpisz Menu x, aby wybrac pozycje.\n");
	while (getline(cin, menu)){
		try
		{
			menu = menu.substr(5, 1);
					const char* c = menu.c_str();
					men_num = atoi(c);
					switch (men_num)
					{
					case 1:
						WyswietlDane();
						break;
					case 2:
						Dodaj_Nowy();
						break;
					case 3:
						UsunRekord();
						break;
					case 4:
						ZmienDane();
						break;
					case 5:
						FiltrujDane();
						break;
					default:
						WyswietlDane();
						break;
					}
		}
		catch (exception ex){
			WyswietlDane();
		}
	}
	system("PAUSE");
	return 0;
}
