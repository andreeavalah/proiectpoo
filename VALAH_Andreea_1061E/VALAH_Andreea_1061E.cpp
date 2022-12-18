#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib> //rand()
#include <iostream>

using namespace std;


class Bilet {
private:
	const string numeCompletCumparator;
	const int cheieRND;
	int id;

	static int genCheieRND() {
		return rand();
	}
	int genID(int ordinBilet) {
		return cheieRND + ordinBilet;
	}

protected:
	int getCheieRND() {
		return this->cheieRND;
	}
public:
	Bilet() : numeCompletCumparator(numeCompletCumparator), cheieRND(0), id(0) {}

	Bilet(string numeCompletCumparator, int ordin) : numeCompletCumparator(numeCompletCumparator), cheieRND(Bilet::genCheieRND()) {
		this->id = genID(ordin);
	}

	string getNumeCompletCumparator() {
		return this->numeCompletCumparator;
	}
	int getID() {
		return this->id;
	}
	void setID(int id) {
		this->id = id;
	}

	int calculeazaOrdinDinID() {
		return id - cheieRND;
	}

	friend istream& operator>>(istream& in, Bilet& b) {

		cout << "\nIntroduceti detalii bilet pentru " << b.numeCompletCumparator << ": ";
		cout << "\nID: ";
		int id;
		do {
			cout << "\nID: ";
			in >> id;
			if (id < 0)
				cout << "\nInvalid! ID >= 0!";
			else
				b.id = id;

		} while (id < 0);
		return in;
	}
	friend ostream& operator<<(ostream& out, Bilet& b) {

		out << "\nBilet pe numele " << b.numeCompletCumparator << " cu id " << b.id;
		return out;
	}

	operator string() {
		return this->numeCompletCumparator;
	}
	int operator()()
	{
		return id;
	}
	//
};
class ZonaLocatie {
private:
	const string nume;
	int nrRanduri;
	int* nrLocuriPeRand;
	bool** ocupat;
public:
	ZonaLocatie(string nume = "NA", int nrRanduri = 0, int* nrLocuriPeRand = NULL, bool** ocupat = NULL) : nume(nume)
	{
		//validare nr locuri
		if (nrRanduri > 0 && nrLocuriPeRand != NULL) {
			this->nrRanduri = nrRanduri;
			this->nrLocuriPeRand = new int[this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->nrLocuriPeRand[i] = nrLocuriPeRand[i];
			}
			this->ocupat = new bool* [this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->ocupat[i] = new bool[this->nrLocuriPeRand[i]]{ false };
			}
			// validare stare ocupat
			if (ocupat != NULL) {
				for (int i = 0; i < nrRanduri; i++) {
					for (int j = 0; j < this->nrLocuriPeRand[i]; j++) {
						this->ocupat[i][j] = ocupat[i][j];
					}
				}
			}
		}
		else {
			this->nrRanduri = 0;
			this->nrLocuriPeRand = NULL;
			this->ocupat = NULL;
		}
	}
	ZonaLocatie(const ZonaLocatie& zl) :nume(zl.nume) {
		//validare nr locuri
		if (zl.nrRanduri > 0 && zl.nrLocuriPeRand != NULL) {
			this->nrRanduri = zl.nrRanduri;
			this->nrLocuriPeRand = new int[this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->nrLocuriPeRand[i] = zl.nrLocuriPeRand[i];
			}
			this->ocupat = new bool* [this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->ocupat[i] = new bool[this->nrLocuriPeRand[i]]{ false };
			}
			// validare stare ocupat
			if (zl.ocupat != NULL) {
				for (int i = 0; i < zl.nrRanduri; i++) {
					for (int j = 0; j < this->nrLocuriPeRand[i]; j++) {
						this->ocupat[i][j] = zl.ocupat[i][j];
					}
				}
			}
		}
		else {
			this->nrRanduri = 0;
			this->nrLocuriPeRand = NULL;
			this->ocupat = NULL;
		}
	}
	ZonaLocatie& operator=(const ZonaLocatie zl)
	{
		if (this != &zl) {
			//stergem 
			if (this->ocupat != NULL && this->nrRanduri > 0) {
				for (int i = 0; i < this->nrRanduri; i++) {
					delete[] this->ocupat[i];
				}
				delete[] this->ocupat;
				this->ocupat = NULL;
			}
			if (this->nrLocuriPeRand) {
				delete[] this->nrLocuriPeRand;
				this->nrLocuriPeRand = NULL;
			}
			//inlocuim
			if (zl.nrRanduri > 0 && zl.nrLocuriPeRand != NULL) {
				this->nrRanduri = zl.nrRanduri;
				this->nrLocuriPeRand = new int[this->nrRanduri];
				for (int i = 0; i < this->nrRanduri; i++) {
					this->nrLocuriPeRand[i] = zl.nrLocuriPeRand[i];
				}
				this->ocupat = new bool* [this->nrRanduri];
				for (int i = 0; i < this->nrRanduri; i++) {
					this->ocupat[i] = new bool[this->nrLocuriPeRand[i]]{ false };
				}
				// validare stare ocupat
				if (zl.ocupat != NULL) {
					for (int i = 0; i < zl.nrRanduri; i++) {
						for (int j = 0; j < this->nrLocuriPeRand[i]; j++) {
							this->ocupat[i][j] = zl.ocupat[i][j];
						}
					}
				}
			}
			else {
				this->nrRanduri = 0;
				this->nrLocuriPeRand = NULL;
				this->ocupat = NULL;
			}
		}
	}

	string getNume()
	{
		return this->nume;
	}
	void setNrRanduri(int nrRanduri) {
		if (nrRanduri > 0)
			this->nrRanduri = nrRanduri;
	}
	int getNrRanduri() {
		return this->nrRanduri;
	}
	void setNrLocuriPeRand(int nrRanduri, int* nrLocuriPeRand)
	{
		// verificam
		if (nrRanduri > 0 && nrLocuriPeRand != NULL) {
			// stergem
			if (this->nrLocuriPeRand) {
				delete[] this->nrLocuriPeRand;
				this->nrLocuriPeRand = NULL;
			}
			//adaugam
			this->nrRanduri = nrRanduri;
			this->nrLocuriPeRand = new int[this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->nrLocuriPeRand[i] = nrLocuriPeRand[i];
			}
		}
	}
	int* getNrLocuriPeRand() {
		if (this->nrRanduri > 0 && this->nrLocuriPeRand != NULL) {
			int* copie = new int[this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				copie[i] = this->nrLocuriPeRand[i];
			}
			return copie;
		}
		else
			return NULL;
	}
	void setOcupat(int nrRanduri, int* nrLocuriPeRand, bool** ocupat)
	{
		//verificam
		if (ocupat != NULL && nrRanduri > 0 && nrLocuriPeRand != NULL) {
			// stergem vechi
			if (this->ocupat != NULL && this->nrRanduri > 0) {
				for (int i = 0; i < this->nrRanduri; i++) {
					delete[] this->ocupat[i];
				}
				delete[] this->ocupat;
				this->ocupat = NULL;
			}
			if (this->nrLocuriPeRand != NULL) {
				delete[] this->nrLocuriPeRand;
				this->nrLocuriPeRand = NULL;
			}
			//adaugam
			this->nrRanduri = nrRanduri;
			this->nrLocuriPeRand = new int[this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->nrLocuriPeRand[i] = nrLocuriPeRand[i];
			}
			this->ocupat = new bool* [this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				this->ocupat[i] = new bool[this->nrLocuriPeRand[i]]{ false };
			}


			for (int i = 0; i < nrRanduri; i++) {
				for (int j = 0; j < this->nrLocuriPeRand[i]; j++) {
					this->ocupat[i][j] = ocupat[i][j];
				}
			}

		}
	}
	bool** getOcupat() {
		if (this->nrRanduri > 0 && this->nrLocuriPeRand != NULL && ocupat != NULL) {

			bool** rez = new bool* [this->nrRanduri];
			for (int i = 0; i < this->nrRanduri; i++) {
				rez[i] = new bool[this->nrLocuriPeRand[i]];
				for (int j = 0; j < this->nrLocuriPeRand[i]; j++) {
					rez[i][j] = ocupat[i][j];
				}
			}
			return rez;
		}
		else
			return NULL;
	}
	~ZonaLocatie()
	{
		if (this->ocupat != NULL && this->nrRanduri > 0) {
			for (int i = 0; i < this->nrRanduri; i++) {
				delete[] this->ocupat[i];
			}
			delete[] this->ocupat;
			this->ocupat = NULL;
		}
		if (this->nrLocuriPeRand) {
			delete[] this->nrLocuriPeRand;
			this->nrLocuriPeRand = NULL;
		}
	}

	friend istream& operator>>(istream& in, ZonaLocatie& zl)
	{
		//stergem
		if (zl.ocupat != NULL && zl.nrRanduri > 0) {
			for (int i = 0; i < zl.nrRanduri; i++) {
				delete[] zl.ocupat[i];
			}
			delete[] zl.ocupat;
			zl.ocupat = NULL;
		}
		if (zl.nrLocuriPeRand) {
			delete[] zl.nrLocuriPeRand;
			zl.nrLocuriPeRand = NULL;
		}

		//add
		cout << "\nIntroduceti detalii despre zona ";
		cout << zl.nume << ":";

		int nrRanduri;
		do {
			cout << "\nnrRanduri: ";
			in >> nrRanduri;
			if (nrRanduri < 0)
				cout << "\nInvalid! nrRanduri >= 0!";
			else
				zl.nrRanduri = nrRanduri;

		} while (nrRanduri < 0);

		if (zl.nrRanduri > 0) { // adica introducem si vectorii

			zl.nrLocuriPeRand = new int[zl.nrRanduri];

			cout << "\nnrLocuriPeRand: ";

			for (int i = 0; i < zl.nrRanduri; i++)
			{
				int locuri;
				do {
					cout << "\n[randul " << i << "]: ";

					in >> locuri;
					if (locuri > 0)
						zl.nrLocuriPeRand[i] = locuri;
					else
						cout << "\nnrLocuriPeRand[i] > 0!";
				} while (locuri <= 0);

			}


			zl.ocupat = new bool* [nrRanduri];
			cout << "\nstare ocupate(introduceti [1=true/0=false]): ";

			for (int i = 0; i < zl.nrRanduri; i++)
			{

				zl.ocupat[i] = new bool[zl.nrLocuriPeRand[i]];
				for (int j = 0; j < zl.nrLocuriPeRand[i]; j++)
				{
					cout << "\n[randul " << i << ", locul " << j << "]: ";
					in >> zl.ocupat[i][j];
				}
			}
		}
		else {
			cout << "\nVectorii nu vor fi introdusi";
			zl.nrLocuriPeRand = NULL;
			zl.ocupat = NULL;
		}

		cout << endl;
		return in;
	}
	friend ostream& operator<<(ostream& out, const ZonaLocatie& zl)
	{
		out << "\nZonaLocatie " << zl.nume << ": ";
		out << "\nnrRanduri: " << zl.nrRanduri;
		if (zl.nrRanduri > 0) { //avem vectorii introdusi
			if (zl.nrLocuriPeRand) {
				out << "\nnrLocuriPeRand: ";

				for (int i = 0; i < zl.nrRanduri; i++)
					out << "\n[randul " << i << "]: are " << zl.nrLocuriPeRand[i] << " locuri";
			}
			else out << "\nnrLocuriPeRand:NULL";
			if (zl.ocupat != NULL && zl.nrLocuriPeRand != NULL) {

				out << "\nstare ocupate: ";
				for (int i = 0; i < zl.nrRanduri; i++)
				{
					for (int j = 0; j < zl.nrLocuriPeRand[i]; j++)
					{
						out << "\n[randul " << i << ", locul " << j << "]: " << zl.ocupat[i][j];
					}
					out << "\n - ";
				}
			}
			else out << "\nocupat:NULL";
		}
		else {
			out << "\nvectorii sunt nuli\n";
		}

		return out;
	}
	//
	int nrTotalLocuri() {
		int suma = 0;
		if (nrRanduri > 0 && nrLocuriPeRand) {
			for (int i = 0; i < nrRanduri; i++) {
				suma += nrLocuriPeRand[i];
			}
		}
		return suma;
	}
	int nrLibere() {
		int suma = 0;
		if (nrRanduri > 0 && nrLocuriPeRand && ocupat) {
			for (int i = 0; i < nrRanduri; i++) {
				if (ocupat[i]) {
					for (int j = 0; j < nrLocuriPeRand[i]; j++) {
						if (!ocupat[i][j])
							suma++;
					}
				}
			}
		}
		return suma;
	}
	explicit operator bool() {
		// true daca s-au ocupat toate locurile
		return  nrLibere() == 0;
	}
	bool operator()(int index1, int index2)
	{
		if (nrRanduri > 0 && nrLocuriPeRand && ocupat) {
			if (index1 <= nrRanduri && index2 <= nrLocuriPeRand[index1] && ocupat[index1][index2])
				return true;
		}
		return false;
	}
	//
};
class Locatie {
private:

	const string nume;
	int nrZone;
	ZonaLocatie** zone;

public:

	Locatie(string nume = "NA", int nrZone = 0, ZonaLocatie** zone = NULL) : nume(nume)
	{
		if (nrZone > 0 && zone != NULL) {
			this->nrZone = nrZone;
			this->zone = new ZonaLocatie * [this->nrZone];
			for (int i = 0; i < this->nrZone; i++) {
				this->zone[i] = new ZonaLocatie(*(zone[i]));
			}
		}
		else {
			this->nrZone = 0;
			this->zone = NULL;
		}
	}
	Locatie(const Locatie& l) : nume(l.nume)
	{
		if (l.nrZone > 0 && l.zone != NULL) {
			this->nrZone = l.nrZone;
			this->zone = new ZonaLocatie * [this->nrZone];
			for (int i = 0; i < this->nrZone; i++) {
				this->zone[i] = new ZonaLocatie(*(l.zone[i]));
			}
		}
		else {
			this->nrZone = 0;
			this->zone = NULL;
		}
	}
	Locatie& operator=(const Locatie& l) {
		//stergem val vechi
		if (this->nrZone > 0 && this->zone != NULL) {
			for (int i = 0; i < this->nrZone; i++)
				if (zone[i] != NULL)
					delete zone[i];
			delete[] zone;
		}
		// adaugam noi
		if (l.nrZone > 0 && l.zone != NULL) {
			this->nrZone = l.nrZone;
			this->zone = new ZonaLocatie * [this->nrZone];
			for (int i = 0; i < this->nrZone; i++) {
				this->zone[i] = new ZonaLocatie(*(l.zone[i]));
			}
		}
		else {
			this->nrZone = 0;
			this->zone = NULL;
		}
	}
	~Locatie() {
		if (this->nrZone > 0 && this->zone != NULL) {
			for (int i = 0; i < this->nrZone; i++)
				if (this->zone[i] != NULL)
					delete this->zone[i];
			delete[] this->zone;
			this->zone = NULL;
		}
	}

	string getNume() {
		return this->nume;
	}
	void setNrZone(int nrZone) {
		if (nrZone > 0)
			this->nrZone = nrZone;
	}
	int getNrZone() {
		return this->nrZone;
	}
	void setZone(int nrZone, ZonaLocatie** zone) {
		//verificam
		if (nrZone > 0 && zone != NULL) {
			//stergem vechi
			if (this->nrZone > 0 && this->zone != NULL) {
				for (int i = 0; i < this->nrZone; i++)
					if (this->zone[i] != NULL)
						delete this->zone[i];
				delete[] this->zone;
				this->zone = NULL;
			}
			//adaugam noi val
			this->nrZone = nrZone;
			this->zone = new ZonaLocatie * [this->nrZone];
			for (int i = 0; i < this->nrZone; i++) {
				this->zone[i] = new ZonaLocatie(*(zone[i]));
			}
		}
	}


	friend istream& operator>>(istream& in, Locatie& l) {

		if (l.nrZone > 0 && l.zone != NULL) {
			for (int i = 0; i < l.nrZone; i++)
				if (l.zone[i] != NULL)
					delete l.zone[i];
			delete[] l.zone;
			l.zone = NULL;
		}

		cout << "\nIntroduceti detalii despre locatia " << l.nume;

		int nrZone;
		do {
			cout << "\nnrZone: ";
			in >> nrZone;
			if (nrZone < 0)
				cout << "\nInvalid! nrZone >= 0!";
			else
				l.nrZone = nrZone;

		} while (nrZone < 0);
		if (l.nrZone > 0) {
			l.zone = new ZonaLocatie * [l.nrZone];
			for (int i = 0; i < l.nrZone; i++)
			{
				cout << "\nnumeZona " << i << ": ";
				string s;
				in >> s;
				l.zone[i] = new ZonaLocatie(s);
				in >> *(l.zone[i]);
			}
		}
		else
			cout << "\nNu introducem vector";
		return in;
	}
	friend ostream& operator<<(ostream& out, Locatie& l) {
		out << "\nLocatia " << l.nume;
		out << "\nnrZone: " << l.nrZone;
		if (l.nrZone > 0) {
			for (int i = 0; i < l.nrZone; i++)
			{
				out << *l.zone[i];
			}
		}
		else
			cout << "\nNu avem vector\n";
		return out;
	}

	ZonaLocatie& operator[](int index)
	{
		if (index >= 0 && index < nrZone)
			return *(this->zone[index]);
		else
			throw exception("index invalid");
	}

	float ratieOcupare() {
		float total = 0;
		float lipsa = 0;
		if (nrZone > 0 && zone) {
			for (int i = 0; i < nrZone; i++) {
				if (zone[i])
				{
					total += zone[i]->nrTotalLocuri();
					lipsa += zone[i]->nrLibere();
				}
			}
		}
		return 1.0 - (lipsa / total);
	}
	bool esteMajoritateaOcupata() {
		return ratieOcupare() > 0.6;
	}

	bool operator> (Locatie& l)
	{
		const float r1 = this->ratieOcupare();
		const float r2 = l.ratieOcupare();
		if (r1 > r2)
			return true;
		return false;
	}
	bool operator>= (Locatie& l)
	{
		const float r1 = this->ratieOcupare();
		const float r2 = l.ratieOcupare();
		if (r1 >= r2)
			return true;
		return false;
	}
};

class Eveniment {
private:

	char* nume;
	float pretBilet;

	Locatie* locatie;
	int nrBileteVandute;
	Bilet** bileteVandute;

	static int nrEvenimenteTotal;
public:
	Eveniment() : nume(NULL), pretBilet(0), locatie(NULL), nrBileteVandute(0), bileteVandute(NULL)
	{
		Eveniment::nrEvenimenteTotal++;
	}
	Eveniment(char* nume, float pretBilet, Locatie* locatie, int nrBileteVandute, Bilet** bileteVandute) : nume(NULL), pretBilet(pretBilet)
	{
		Eveniment::nrEvenimenteTotal++;
		if (nume) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else {
			this->nume = NULL;
		}
		if (locatie) {
			this->locatie = new Locatie(*locatie);
		}
		else {
			this->locatie = NULL;
		}
		if (nrBileteVandute > 0 && bileteVandute != NULL) {
			this->nrBileteVandute = nrBileteVandute;
			this->bileteVandute = new Bilet * [nrBileteVandute];
			for (int i = 0; i < this->nrBileteVandute; i++)
			{
				this->bileteVandute[i] = new Bilet(*(bileteVandute[i]));
			}
		}
		else {
			this->nrBileteVandute = 0;
			this->bileteVandute = NULL;
		}

	}
	Eveniment(const Eveniment& e)
	{
		Eveniment::nrEvenimenteTotal++;
		this->pretBilet = e.pretBilet;
		if (e.nume) {
			this->nume = new char[strlen(e.nume) + 1];
			strcpy(this->nume, e.nume);
		}
		else {
			this->nume = NULL;
		}
		if (locatie) {
			this->locatie = new Locatie(*(e.locatie));
		}
		else {
			this->locatie = NULL;
		}
		if (e.nrBileteVandute > 0 && e.bileteVandute != NULL) {
			this->nrBileteVandute = e.nrBileteVandute;
			this->bileteVandute = new Bilet * [e.nrBileteVandute];
			for (int i = 0; i < this->nrBileteVandute; i++)
			{
				this->bileteVandute[i] = new Bilet(*(e.bileteVandute[i]));
			}
		}
		else {
			this->nrBileteVandute = 0;
			this->bileteVandute = NULL;
		}
	}
	Eveniment& operator=(const Eveniment& e) {
		if (this != &e) {
			//stergem
			if (this->nume) {
				delete this->nume;
				this->nume = NULL;
			}
			if (this->locatie) {
				delete this->locatie;
				this->locatie = NULL;
			}
			if (this->nrBileteVandute > 0 && this->bileteVandute != NULL) {
				for (int i = 0; i < this->nrBileteVandute; i++) {
					if (this->bileteVandute[i])
						delete this->bileteVandute[i];
				}
				delete[] bileteVandute;

				this->nrBileteVandute = 0;
				this->bileteVandute = NULL;
			}
			// add valori noi
			if (e.nume) {
				this->nume = new char[strlen(e.nume) + 1];
				strcpy(this->nume, e.nume);
			}
			else {
				this->nume = NULL;
			}
			if (locatie) {
				this->locatie = new Locatie(*(e.locatie));
			}
			else {
				this->locatie = NULL;
			}
			if (e.nrBileteVandute > 0 && e.bileteVandute != NULL) {
				this->nrBileteVandute = e.nrBileteVandute;
				this->bileteVandute = new Bilet * [e.nrBileteVandute];
				for (int i = 0; i < this->nrBileteVandute; i++)
				{
					this->bileteVandute[i] = new Bilet(*(e.bileteVandute[i]));
				}
			}
			else {
				this->nrBileteVandute = 0;
				this->bileteVandute = NULL;
			}
		}
		return *this;
	}
	~Eveniment()
	{
		if (this->nume) {
			delete this->nume;
			this->nume = NULL;
		}
		if (this->locatie) {
			delete this->locatie;
			this->locatie = NULL;
		}
		if (this->nrBileteVandute > 0 && this->bileteVandute != NULL) {
			for (int i = 0; i < this->nrBileteVandute; i++) {
				if (this->bileteVandute[i])
					delete this->bileteVandute[i];
			}
			delete[] bileteVandute;

			this->nrBileteVandute = 0;
			this->bileteVandute = NULL;
		}
		Eveniment::nrEvenimenteTotal--;
	}


	void setNume(const char* nume)
	{
		if (nume != NULL) {
			//stergem
			if (this->nume) {
				delete this->nume;
				this->nume = NULL;
			}
			//adaugam
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	void setNume(char* nume)
	{
		if (nume != NULL) {
			//stergem
			if (this->nume) {
				delete this->nume;
				this->nume = NULL;
			}
			//adaugam
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}
	char* getNume()
	{
		if (this->nume) {
			char* copie = new char[strlen(this->nume) + 1];
			strcpy(copie, this->nume);
			return copie;
		}
		else {
			return NULL;
		}
	}
	void setPretBilet(float pretBilet) {
		this->pretBilet = pretBilet;
	}
	float getPretBilet() {
		return pretBilet;
	}
	void setLocatie(Locatie* locatie) {

		if (this->locatie) {
			delete this->locatie;
			this->locatie = NULL;
		}
		this->locatie = new Locatie(*locatie);

	}
	Locatie* getLocatie() {
		return new Locatie(*this->locatie);
	}

	void setNrBileteVandute(int nrBileteVandute) {
		if (nrBileteVandute > 0) {
			this->nrBileteVandute = nrBileteVandute;
		}

	}

	int getNrBileteVandute() {
		return this->nrBileteVandute;
	}
	void setBileteVandute(int nrBileteVandute, Bilet* bilete) {
		//verificam
		if (nrBileteVandute > 0 && bileteVandute != NULL) {
			//stergem
			if (this->nrBileteVandute > 0 && this->bileteVandute != NULL) {
				for (int i = 0; i < this->nrBileteVandute; i++) {
					if (this->bileteVandute[i])
						delete this->bileteVandute[i];
				}
				delete[] this->bileteVandute;

				this->nrBileteVandute = 0;
				this->bileteVandute = NULL;
			}
			//adaugam
			this->nrBileteVandute = nrBileteVandute;
			this->bileteVandute = new Bilet * [this->nrBileteVandute];
			for (int i = 0; i < this->nrBileteVandute; i++) {
				this->bileteVandute[i] = new Bilet(bilete[i]);
			}
		}
	}

	Bilet** getBileteVandute() {
		if (this->nrBileteVandute > 0 && this->bileteVandute != NULL)
		{
			Bilet** copie = new Bilet * [this->nrBileteVandute];
			for (int i = 0; i < this->nrBileteVandute; i++) {
				copie[i] = new Bilet(*(this->bileteVandute[i]));
			}
			return copie;
		}
		else {

			return NULL;
		}
	}
	static int getNrEvenimenteTotal() {
		return nrEvenimenteTotal;
	}
	static void setNrEvenimenteTotal(int nr) {
		if (nr >= 0)
			Eveniment::nrEvenimenteTotal = nr;

	}

	friend istream& operator>>(istream& in, Eveniment& e) {

		if (e.nume) {
			delete e.nume;
			e.nume = NULL;
		}
		if (e.locatie) {
			delete e.locatie;
			e.locatie = NULL;
		}
		if (e.nrBileteVandute > 0 && e.bileteVandute != NULL) {
			for (int i = 0; i < e.nrBileteVandute; i++) {
				if (e.bileteVandute[i])
					delete e.bileteVandute[i];
			}
			delete[] e.bileteVandute;

			e.nrBileteVandute = 0;
			e.bileteVandute = NULL;
		}


		cout << "\nNume eveniment: ";
		string nume;
		in >> nume;
		e.setNume(nume.c_str());

		float pret;
		do {
			cout << "\npret bilet: ";
			in >> pret;
			if (pret < 0)
				cout << "\nInvalid! pret >= 0!";
			else
				e.pretBilet = pret;

		} while (pret < 0);

		cout << "\nIntroduceti locatie: ";
		cout << "\nNume locatie: ";
		string s;
		in >> s;
		e.locatie = new Locatie(s);
		in >> *(e.locatie);


		int nrBileteVandute;
		do {
			cout << "\nnrBileteVandute: ";
			in >> nrBileteVandute;
			if (nrBileteVandute < 0)
				cout << "\nInvalid! nrBileteVandute >= 0!";
			else
				e.nrBileteVandute = nrBileteVandute;

		} while (nrBileteVandute < 0);

		if (e.nrBileteVandute > 0) {
			e.bileteVandute = new Bilet * [nrBileteVandute];

			for (int i = 0; i < e.nrBileteVandute; i++) {
				cout << "\nNume complet cumparator";
				string cumparator;
				in >> cumparator;

				e.bileteVandute[i] = new Bilet(cumparator, i);
			}
		}
		else {
			cout << "\nNu exista bilete vandute";
		}

		return in;
	}
	friend ostream& operator<<(ostream& out, Eveniment& e) {

		out << "\nNr TOTAL evenimente: " << Eveniment::nrEvenimenteTotal;
		out << "\nNume eveniment: " << e.nume;
		out << "\npretBilet: " << e.pretBilet;

		out << "\nNume locatie: " << *(e.locatie);
		out << "\nnrBileteVandute: " << e.nrBileteVandute;

		if (e.nrBileteVandute > 0) {
			for (int i = 0; i < e.nrBileteVandute; i++) {
				out << *(e.bileteVandute[i]);
			}
		}
		else {
			cout << "\nNu exista bilete vandute";
		}
		return out;
	}

	Eveniment& operator++()
	{
		pretBilet += 1.0;
		return *this;
	}
	Eveniment operator++(int)
	{
		Eveniment copie = *this;
		pretBilet += 1.0;

		return copie;
	}

};

int Eveniment::nrEvenimenteTotal = 0;


int main()
{

	//Testare zona locatie
	/*ZonaLocatie zl1;
	cout << zl1;

	int vipnrranduri = 2;
	int* vipnrperand = new int[2] {4, 6};
	bool viprand1[4] = { true, false, true, false };
	bool viprand2[6] = { true,true,true,true,true,true };
	bool** vipocupate = new bool* [2] {viprand1, viprand2};
	ZonaLocatie zl2("VIP", 2, vipnrperand, vipocupate);
	cout << zl2;

	ZonaLocatie zl3("Normal");

	zl3.setNrRanduri(1);
	zl3.setNrLocuriPeRand(1, new int[1] {3});
	cout << zl3;
	zl3.setOcupat(1, new int[1] {3}, new bool* [1] {new bool[3] {false, true, false}});
	cout << zl3;

	cin >> zl3;

	cout << endl << zl3;*/

	/*Locatie l1;
	cout << endl;
	cout << l1;*/

	int vipnrranduri = 2;
	int* vipnrperand = new int[2]{ 4, 6 };
	bool viprand1[4] = { true, false, true, false };
	bool viprand2[6] = { true,true,true,true,true,true };
	bool** vipocupate = new bool* [2]{ viprand1, viprand2 };
	ZonaLocatie zl2("VIP", 2, vipnrperand, vipocupate);

	ZonaLocatie zl3("Normal");
	zl3.setOcupat(1, new int[1]{ 3 }, new bool* [1]{ new bool[3] {false, true, false} });

	Locatie l2("Cinema233", 2, new ZonaLocatie * [2]{ &zl2, &zl3 });
	/*cout << endl;
	cout << l2;

	cin >> l2;
	cout << l2;*/

	char numeeveniment[] = "eveniment1";
	Eveniment e1(numeeveniment, 3.4, &l2, 2, new Bilet * [2]{ new Bilet("Ion", 0), new Bilet("Maria", 1) });
	cout << e1;
	return 0;
}
