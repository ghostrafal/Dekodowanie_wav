// Dekodowanie_wav.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "stdio.h"
#include <complex>
#include <iostream>
#include <valarray>

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
using namespace std;
void fft(CArray& x)
{
	const size_t N = x.size();
	if (N <= 1) return;

	// divide
	CArray even = x[std::slice(0, N / 2, 2)];
	CArray  odd = x[std::slice(1, N / 2, 2)];

	// conquer
	fft(even);
	fft(odd);

	// combine
	for (size_t k = 0; k < N / 2; ++k)
	{
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}
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


unsigned short odczytaj_liczbe(int a, char * tab)
{
	
	unsigned short liczba;
	if (a == 4) {
		
		liczba = ((tab[3] << 24) | (tab[2] << 16) | (tab[1] << 8) | (tab[0] << 0));// -'0';
	}
	else liczba = ((tab[1] << 8) | tab[0]);
	
	return liczba;
}

int main()
{
	Complex test[200];
	
	
	char bufor[4];
	fstream plik;
	plik.open("c.wav", ios::in | ios::binary);
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
		
		
		for (int i = 0; i < 200; ++i)
		{
			plik.read(bufor, 4);
			int v= odczytaj_liczbe(4, bufor);
			//cout<<v<<endl;
			test[i] = v;
			
		}
		CArray data(test, 200);
		fft(data);
		
		string linia;
		fstream plik;

		plik.open("plik.txt", ios::out | ios::app);
		if (plik.good() == true)
		{
			std::cout << "fft" << std::endl;
			for (int i = 1; i < 200; ++i)
			{
				plik << data[i].real()<<' ';
				plik << data[i].imag()<<endl;


			}
			
			plik.close();
		}

		
		//std::cout << "fft" << std::endl;
		//for (int i = 0; i < 200; ++i)
		//{
			//std::cout << data[i] << std::endl;
			
		//}
	}
	else
	{
		perror("Brak dostepu do pliku");
	}


	plik.close();
	


	_getch();
	return 0;
}


