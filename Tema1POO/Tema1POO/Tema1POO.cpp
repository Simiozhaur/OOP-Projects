/*
Tema 13. Clasa ”Polinom” - reprezentat ca tablou unidimensional (prin gradul polinomului si vectorul
coeficientilor (coeficientii vor apartine la monoame de grade consecutive), de dimensiune egala cu gradul
plus 1, de la cel al termenului liber la cel de grad maxim.
- fiecare coeficient va fi de tip double;
- membri privati pentru vectorul propriuzis si numarul de elemente;
 - constructori pentru initializare si copiere;
- destructor (în cazul alocarii statice, se seteaza dimensiunea vectorului la zero, iar în cazul alocarii
dinamice, se dezaloca zona de memorie utilizata);
- metoda publica pentru calculul valorii unui polinom intr-un punct;
- suma a doua polinoame, implementata prin supraincarcarea operatorului +;
- diferenta a doua polinoame, implementata prin supraincarcarea operatorului -;
- produsul a doua polinoame, implementat prin supraincarcarea operatorului *;
*/

#include <iostream>;
#include <stdlib.h>;
#include <math.h>;
#include <cstdio>;

using namespace std;

class Polinom
{
protected: 
	int gradmax;
	double* coef;
public:

// Getteri si Setteri pentru gradmax si vectorul de coeficienti;
	void SetGradmax(int gradmax)
	{
		this->gradmax = gradmax;
		coef = new double[gradmax];
	}
	int GetGradmax() { return gradmax; }
	void SetCoef(int i, double val)
	{
		if (i <= gradmax) {
			coef[i] = val;
		}
		else
			cout << "Eroare coeficient";
	}
	double GetCoef(int i) { return (coef[i]); }
	
	void ToPrint();
	double SolvePoint(int);

	void CitireMultipla(Polinom* p)
	{
		int n;
		cout << "Numarul de polinoame";
		cin >> n;
		p = new Polinom[n];
		for (int i = 0; i < n; i++)
		{
			cin >> p[i];
			cout << p[i];
		}
	}

	//Prototipuri overload
	Polinom operator+(Polinom&);
	friend Polinom operator+(Polinom&);
	Polinom operator-(Polinom&);
	friend Polinom operator-(Polinom&);
	Polinom operator*(Polinom&);
	friend Polinom operator*(Polinom&);
	friend istream& operator >> (istream& in, Polinom& p);
	Polinom operator<<(ostream& out);
	friend ostream& operator<<(ostream& out, Polinom& p)
	{
		for (int i = p.gradmax-1; i > 0; i--)
		{
			if (p.coef[i] != 0) {
				out << p.coef[i] << "*x^" << i;
				if (i != 0)
					p.coef[i-1] > 0 ? out << " +" : out << " ";
			}
		}
		out << p.coef[0] << endl;
		return out;
	}

//Prototipuri constructori si destructori
	Polinom(int, double*);
	Polinom(const Polinom& pol);
	Polinom();
	~Polinom() {
		delete[] coef;
	}
};

//Constructor
Polinom::Polinom(int size, double* arr)
{
	coef = new double[size];
	for (int i = 0; i < size; i++)
	{
		this->coef[i] = arr[i];
	}
	this->gradmax = size;
}

//Constructor de copiere
Polinom::Polinom(const Polinom& pol)
{
	coef = new double[pol.gradmax];
	for (int i = 0; i < pol.gradmax; i++)
	{
		this->coef[i] = pol.coef[i];
	}
	this->gradmax = pol.gradmax;
}

//Constructor gol
Polinom::Polinom()
{
	this->gradmax = 0;
	coef = new double[0];
	coef[0] = 0;
}


//Overload la operatorul >>
istream& operator >> (istream& in, Polinom& p)
{
	cout << "Gradul polinomului:";
	in >> p.gradmax;
	p.coef = new double[p.gradmax];
	for (int i = 0; i < p.gradmax; i++)
	{
		cout << "Coeficient x^" << i << " ";
		in >> p.coef[i];
	}
	return in;
}


void Polinom::ToPrint()
{
	for (int i = gradmax-1; i >= 0; i--)
	{	
		if (coef[i] != 0) {
			cout << coef[i] << "*x^" << i;
			if (i != 0)
				cout << " +";
		}
	}
	cout << endl;
}

//Metoda de rezolvare a polinomului intr-un punct
double Polinom::SolvePoint(int n)
{
	double sum = 0;
	for (int i = 0; i < gradmax; i++) {
		sum += coef[i] * pow(n, i);
	}
	return sum;
}

//Overload la operatorul +
Polinom Polinom::operator+(Polinom& b) {
	Polinom psum;
//If pentru alocarea memoriei cat cel mai mare grad dintre cele doua polinoame
	if (this->gradmax >= b.gradmax) {
		psum.gradmax = this->gradmax;
		psum.coef = new double[this->gradmax];
	}
	else {
		psum.gradmax = b.gradmax;
		psum.coef = new double[b.gradmax];
	}

//Adunarea propriu-zisa
	for (int i = 0; i < psum.gradmax; i++)
	{
		psum.coef[i] = this->coef[i] + b.coef[i];
	}

	return psum;
}

//Overload la operatorul -
Polinom Polinom::operator-(Polinom& d) {
	Polinom pdif;
//If pentru alocarea memoriei cat cel mai mare grad dintre cele doua polinoame
	if (this->gradmax >= d.gradmax) {
		pdif.gradmax = this->gradmax;
		pdif.coef = new double[this->gradmax];
	}
	else {
		pdif.gradmax = d.gradmax;
		pdif.coef = new double[d.gradmax];
	}

	for (int i = 0; i < pdif.gradmax; i++)
	{
		pdif.coef[i] = this->coef[i] - d.coef[i];
	}

	return pdif;
}

//Overload la operatorul *
Polinom Polinom::operator*(Polinom& m) {
	Polinom pmul;
//Alocarea memoriei pentru noul polinom
	pmul.gradmax = (this->gradmax + m.gradmax)-1;
	pmul.coef = new double[pmul.gradmax];

	for (int i = 0; i < pmul.gradmax; i++)
	{
		pmul.coef[i] = 0;
	}
	
//Inmultirea fiecarui termen cu fiecare termen si adunate in i+j;
	for (int i = 0; i < this->gradmax; i++)
	{
		for (int j = 0; j < m.gradmax; j++)
		{
			pmul.coef[i + j] += this->coef[i] * m.coef[j];
		}
	}
	return pmul;
}


int main()
{	//Main pentru testare
	double test[4] = { 5, +3 , -2, 5 };
	double test2[3] = { -2, -5, 2 };
	Polinom p1 = Polinom(4, test);
	Polinom p2 = Polinom(3, test2);
	Polinom p3 = p1 * p2;
	Polinom p4;
	cin >> p4;
	cout << p4;
	cout << p1;
	cout << p2;
	cout << p3;
}

