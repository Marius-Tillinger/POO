/*  Tillinger Marius 143
 * Mingw
 * Stefan Deaconu
 * */


#include <iostream>
#include <vector>
#include <cstring>
#include <memory>
#include "util/IoBase.h"

using namespace std;

struct Data {
    int zi, luna, an;
};

class Malware : public IoBase {     //clasa Malware va primi functii din Iobase, din exercitiile din laborator
protected:
    float impact;
    Data datainf;
    string nume;
    string metoda;
    vector<string>  registrii;
public:
    istream &read(istream &is) override {  //metoda de citire implementata la laborator
        IoBase::read(is);
        cout << "Impact: ";
        is >> impact;
        cout << "Data: ";
        is >> datainf.zi >> datainf.luna >> datainf.an;
        cout << "Nume: ";
        is >> nume;
        cout << "Metoda: ";
        is >> metoda;
        cout << "Registrii: ";
        registrii.clear();
        string registru;
        do {
            is >> registru;
            registrii.push_back(registru);
        }while (registru != "");

        //am citit toate datele importante pentru clasa Malware

        return is;
    }

    ostream &write(ostream &os) const override {        //functie de afisare importata din laboratoare
        IoBase::write(os);
        cout << "Impact: ";
        os << impact<<endl;
        cout << "Data: ";
        os << datainf.zi << datainf.luna << datainf.an<<endl;
        cout << "Nume: ";
        os << nume<<endl;
        cout << "Metoda: ";
        os << metoda<<endl;
        cout << "Registrii: ";

        for (int i=0; i<registrii.size(); i++) {
            os << registrii[i] << " ";
        }
        cout<< endl;

        return os;
    }
};

class Rootkit: public Malware {     //mostenire clasa Malware
protected:
    vector<string> importuri;
    vector<string> semnificative;
public:
    istream &read(istream &is) override {       //mostenire functie de citire
        Malware::read(is);
        string import;
        string semnificativ;
        cout << "Importuri: " ;
        importuri.clear();
        semnificative.clear();      //golim vectorii

        do {
            is >> import;
            importuri.push_back(import);
        }while (import != "");

        cout << "Semnificative: ";

        do {
            is >> semnificativ;
            semnificative.push_back(semnificativ);
        }while (semnificativ != "");

        return is;

        //am citit atributele clasei Rootkit
    }

    ostream &write(ostream &os) const override {        //afisare rootkit
        Malware::write(os);
        cout << "Importuri: ";

        for (int i=0; i<importuri.size(); i++) {
            os << importuri[i] << " ";
        }
        cout<< endl;

        cout << "Semnificative: ";

        for (int i=0; i<semnificative.size(); i++) {
            os << semnificative[i] << " ";
        }
        cout<< endl;

        return os;
    }
};

class Keylogger : public Malware {      //alta mostenire
protected:
    vector<string> functii;
    vector<string> taste;
public:
    istream &read(istream &is) override {       //citire pentru keylogger
        Malware::read(is);
        functii.clear();
        taste.clear();
        cout << "Fuctii: ";
        string functie;
        string tasta;

        do {
            is >> functie;
            functii.push_back(functie);
        }while (functie != "");

        cout << "Taste: ";

        do {
            is >> tasta;
            taste.push_back(tasta);
        }while (tasta != "");

        return is;
    }

    ostream &write(ostream &os) const override {        //afisare keylogger
        Malware::write(os);
        cout << "Functii: ";

        for (int i=0; i<functii.size(); i++) {
            os << functii[i] << " ";
        }
        cout<< endl;

        cout << "Taste: ";

        for (int i=0; i<taste.size(); i++) {
            os << taste[i] << " ";
        }
        cout<< endl;

        return os;
    }
};

class Kernel_Keylogger : public Rootkit, public Keylogger {     //mostenire in diamant
protected:
    bool fisiereAscunse;
    bool registriiAscunsi;
public:
    istream &read(istream &is) override {       //cititm proprietatile obiectului mostenit in diamant
       Rootkit::read(is);

       Keylogger::functii.clear();
       Keylogger::taste.clear();
       cout << "Fuctii: ";
       string functie;
       string tasta;

       do {
           is >> functie;
           Keylogger::functii.push_back(functie);
       }while (functie != "");

       cout << "Taste: ";

       do {
           is >> tasta;
           Keylogger::taste.push_back(tasta);
       }while (tasta != "");

       cout << "Fisiere ascunse? (Da/Nu): ";
       string raspuns;
       cin >> raspuns;

       if (raspuns == "Da") {
           fisiereAscunse = true;
       }
       else if (raspuns == "Nu") {
           fisiereAscunse = false;
       }

        cout << "Registrii ascunsi? (Da/Nu): ";
        cin >> raspuns;

        if (raspuns == "Da") {
            registriiAscunsi = true;
        }
        else if (raspuns == "Nu") {
            registriiAscunsi = false;
        }
    }

    ostream &write(ostream &os) const override {
        Rootkit::write(os);

        cout << "Functii: ";

        for (int i=0; i<Keylogger::functii.size(); i++) {
            os << Keylogger::functii[i] << " ";
        }
        cout<< endl;

        cout << "Taste: ";

        for (int i=0; i<Keylogger::taste.size(); i++) {
            os << Keylogger::taste[i] << " ";
        }
        cout<< endl;

        cout<< "Ascunse: ";

        if (fisiereAscunse) {
            cout << "fisiere au fost ascunse. \n";
        }
        else {
            cout << "fisiere nu au fost ascunse. \n";
        }

        if (registriiAscunsi)  {
            cout << "registrii au fost ascunsi. \n";
        }
        else {
            cout << "registrii nu au fost ascunsi. \n";
        }

        cout <<endl;
    }
};

class Ransomware : public Malware {
protected:
    int rating;
    int obfuscare;
public:
    istream &read(istream &is) override {
        Malware::read(is);
        cout << "Rating: ";
        is >> rating;
        cout << "Obfuscare: ";
        is >>obfuscare;

        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        cout << "Rating: ";
        os << rating << endl;
        cout << "Obfuscare: ";
        os << obfuscare << endl;

        return os;
    }
};


class Computer : public IoBase{
protected:
    static int  contor;
    const  int id;
    vector<shared_ptr<Malware>> listaMalware;
    int ratingFinal;
public:
    istream &read (istream &is) {
        IoBase::read(is);
        int tip;
        cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): ";
        do {
            cin >> tip;
            if (tip == 1) {
                listaMalware.push_back(make_shared<Rootkit>());
            } else if (tip == 2) {
                listaMalware.push_back(make_shared<Keylogger>());
            } else if (tip == 3) {
                //listaMalware.push_back(make_shared<Kernel_Keylogger>());
            } else if (tip == 4) {
                listaMalware.push_back(make_shared<Ransomware>());
            } else {
                break;
            }
        }while (tip >=1 && tip <=4);
    }

    Computer();
};

int Computer::contor = 0;

Computer::Computer() : id(contor++) {}


class Meniu {
private:
    vector<Computer> calculatoare;
    vector<shared_ptr<Malware>> malwareuri;
public:

    void listeazaOptiuni() {
        cout << "1. afisarea informatiilor pentru fiecare calculator \n";
        cout << "2. afisarea informatiilor pentru fiecare calculator fiind ordonate dupa ratingul final \n";
        cout << "3. afisarea primelor k calculatoare ordonate dupa ratingul final \n";
        cout << "4. afisarea procentului de computere infectate din firma \n";
        cout << "5. Cititi n calculatoare si m malware uri pentru fiecare calculator \n";
        cout << "6. Stop \n";
    }
    //option picker
    int alegeOptiune() {
        int option;

        cout << "Alegeti o optiune: ";
        cin >> option;
        cout<<endl;

        if (option >=1 && option <=6)
            return option;
    }
    //main loop
    void run() {
        // meniul interactiv
        while(true) {
            listeazaOptiuni();
            // alegem optiune
            int option = alegeOptiune();
            if (option == 5) {
                citireCalc();
            }else if (option >6 || option <1) {
                cout << "Nu ai aceasta optiune, mai incearca :)\n\n";
            } else if (option == 1) {
                afisareCalc();
            } else if (option == 2) {
                afisareOrd();
            } else if (option == 3) {
                afisarePrimeK();
            } else if (option == 4) {
                afisareProcent();
            } else if (option == 6) {
                break;
            }
        }
    }

    void citireCalc() {
        int n;
        cin >> n;

        for (int i=0; i<n; i++) {
            
        }
    }

    void afisareCalc() {}
    void afisareOrd() {}
    void afisarePrimeK() {}
    void afisareProcent() {}
};

int main() {
    Meniu m;
    m.run();
    return 0;
}
