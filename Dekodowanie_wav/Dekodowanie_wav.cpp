// Dekodowanie_wav.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

string odczytaj_napis(int a, char *tab)
{
	string napis;
	for (int i = 0; i<a; i++)
	{
		napis = napis + *tab;
		tab++;
	}
	return napis;
}

short odczytaj_liczbe(int a, char *tab)
{
	short liczba;
	if (a == 4) liczba = (tab[3] << 0x18) | (tab[2] << 0x10) | (tab[1] << 8) | tab[0];
	else liczba = ((tab[1] << 8) | tab[0]);

	return liczba;
}


int main()
{
	char bufor[4];
	fstream plik;
	plik.open("m.wav", ios::in | ios::binary);
	if (plik.good() == true)
	{
		cout << "Uzyskano dostep do pliku!" << endl;

		/*odczytywanie identyfikatora pliku*/
		plik.read(bufor, 4);
		cout << "Identyfikator pliku:  " << odczytaj_napis(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Liczba danych:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Format ID:  " << odczytaj_napis(4, bufor) << endl;



		plik.read(bufor, 4);
		cout << "Opis ID:  " << odczytaj_napis(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Rozmiar opisu:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 2);
		cout << "Format audio (1-bez kompresji, modulacja PCM.):  " << odczytaj_liczbe(2, bufor) << endl;

		plik.read(bufor, 2);
		cout << "Liczba kanalow (1 - mono, 2 - stereo):  " << odczytaj_liczbe(2, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Czestotliwosc:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Czestotliwosc bajtow:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 2);
		cout << "Rozmiar probki:  " << odczytaj_liczbe(2, bufor) << endl;

		plik.read(bufor, 2);
		cout << "Rozdzielczosc:  " << odczytaj_liczbe(2, bufor) << endl;



		plik.read(bufor, 4);
		cout << "Dane ID:  " << odczytaj_napis(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Rozmiar danych:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Dane:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Dane:  " << odczytaj_liczbe(4, bufor) << endl;

		plik.read(bufor, 4);
		cout << "Dane:  " << odczytaj_liczbe(4, bufor) << endl;
	}
	else
	{
		perror("Brak dostepu do pliku");
	}


	plik.close();



	return 0;
}


