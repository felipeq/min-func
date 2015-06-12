#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define ILOSC_OPERACJI 6
#define ILOSC_SYMBOLI 10

typedef void(*FunkcjaT)(vector<double>&);
struct Operacja
{
	string symbol;
	FunkcjaT funkcja;
};
struct Argument
{
	int dolnaGranicaZakresu;
	int gornaGranicaZakresu;
	string funkcja;
	double wynikFunkcji;
	char symbol;
};

void dodaj(vector<double> &stos);
void odejmij(vector<double> &stos);
void pomnoz(vector<double> &stos);
void podziel(vector<double> &stos);
void pierwiastek(vector<double> &stos);
void wartoscBezwzgledna(vector<double> &stos);

char tablicaSymboli[ILOSC_SYMBOLI] = { 'x','y','z','a','b','c','d','e','f','g' };
string tablicaSymboliOperacji[ILOSC_OPERACJI] = { "+","-","*","/","sqrt","abs" };
FunkcjaT tablicaFunkcjiOperacji[ILOSC_OPERACJI] = { dodaj,odejmij,pomnoz,podziel,pierwiastek,wartoscBezwzgledna };

Argument argumenty[ILOSC_SYMBOLI];
Operacja operacje[ILOSC_OPERACJI];

int n;
int t;

Argument* pobierzArgumentDlaSymbolu(char symbol);

bool jestSymbolem(char wyrazenie);
bool jestLiczba(string wyrazenie);
bool jestOperacja(string operacja);

void wykonajOperacje(string operacja, vector<double> &stos);
void obliczFunkcje(Argument &argument);


int main()
{
	cin >> n;
	cin >> t;

	// Przypisanie symboli argumentom
	for (int i = 0;i < n;i++)
	{
		argumenty[i].symbol = tablicaSymboli[i];
	}

	// Przypisanie funkcji i symboli operacjom
	for (int i = 0;i < ILOSC_OPERACJI;i++)
	{
		operacje[i].symbol = tablicaSymboliOperacji[i];
		operacje[i].funkcja = tablicaFunkcjiOperacji[i];
	}

	// Wczytywanie granic zakresu
	for (int i = 0;i < n;i++)
	{
		cin >> argumenty[i].dolnaGranicaZakresu;
		cin >> argumenty[i].gornaGranicaZakresu;
	}

	// Wczytywanie funkcji
	string wyrazenie;
	Argument *wprowadzanyArgument = nullptr;
	while (cin >> wyrazenie)
	{
		if (jestSymbolem(wyrazenie[0]))
		{
			wprowadzanyArgument = pobierzArgumentDlaSymbolu(wyrazenie[0]);
			continue;
		}
		wprowadzanyArgument->funkcja += wyrazenie + " ";
	}
	for (int i = 0;i < n; i++)
	{
		obliczFunkcje(argumenty[i]);
	}
	system("pause");
}

void dodaj(vector<double> &stos)
{
	double a = stos.back();
	stos.pop_back();
	double b = stos.back();
	stos.pop_back();
	stos.push_back(a + b);
}

void odejmij(vector<double>& stos)
{
	double a = stos.back();
	stos.pop_back();
	double b = stos.back();
	stos.pop_back();
	stos.push_back(b - a);
}

void pomnoz(vector<double>& stos)
{
	double a = stos.back();
	stos.pop_back();
	double b = stos.back();
	stos.pop_back();
	stos.push_back(a*b);
}

void podziel(vector<double>& stos)
{
	double a = stos.back();
	stos.pop_back();
	double b = stos.back();
	stos.pop_back();
	stos.push_back(b / a);
}

void pierwiastek(vector<double>& stos)
{
	double a = stos.back();
	stos.pop_back();
	stos.push_back(sqrt(a));
}

void wartoscBezwzgledna(vector<double>& stos)
{
	double a = stos.back();
	stos.pop_back();
	stos.push_back(abs(a));
}

Argument* pobierzArgumentDlaSymbolu(char symbol)
{
	for (int i = 0;i < n;i++)
	{
		if (argumenty[i].symbol == symbol)
			return &argumenty[i];
	}
	return nullptr;
}
bool jestSymbolem(char wyrazenie)
{
	for (int i = 0;i < n;i++)
	{
		if (wyrazenie == tablicaSymboli[i])
		{
			return true;
		}
	}
	return false;
}

bool jestLiczba(string wyrazenie)
{
	char* endptr = 0;
	strtod(wyrazenie.c_str(), &endptr);

	if (*endptr != '\0' || endptr == wyrazenie)
		return false;
	return true;
}

bool jestOperacja(string operacja)
{
	for (int i = 0;i < ILOSC_OPERACJI;i++)
	{
		if (operacje->symbol == operacja)
			return true;
	}
	return false;
}

void wykonajOperacje(string symbol, vector<double> &stos)
{
	for (int i = 0;i < ILOSC_OPERACJI;i++)
	{
		if (operacje[i].symbol == symbol)
		{
			operacje[i].funkcja(stos);
			return;
		}
	}
}
void obliczFunkcje(Argument &argument)
{
	vector<double> stos;
	string wyrazenie = "";
	string funkcja = argument.funkcja;
	for (int i = 0;i < funkcja.length();i++)
	{
		if (funkcja[i] == ' ')
		{
			if (jestLiczba(wyrazenie))
				stos.push_back(stod(wyrazenie));
			else if (jestOperacja(wyrazenie))
				wykonajOperacje(wyrazenie, stos);

			wyrazenie = "";
			continue;
		}
		wyrazenie += funkcja[i];
	}
	argument.wynikFunkcji = stos.back();
}