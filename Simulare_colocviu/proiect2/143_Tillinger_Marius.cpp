/*  Tillinger Marius 143
 * Mingw
 * Stefan Deaconu
 * */


#include <iostream>
#include <vector>
#include <cstring>      //i dont need it but it's good to have anyways
#include <memory>
#include "util/IoBase.h"

using namespace std;

struct Data {       //data structure for remembering calendar data types
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
        cout << "Data:\n";
        cout << "zi: "; is >> datainf.zi; cout << "luna: "; is >> datainf.luna; cout << "an: "; is >> datainf.an;
        cout << "Nume: ";
        is >> nume;
        cout << "Metoda: ";
        is >> metoda;
        cout << "Registrii (scrieti NONE pentru a trece mai departe): ";
        registrii.clear();
        string registru;

        do {
            is >> registru;
            registrii.push_back(registru);
        }while (registru != "NONE");

        //am citit toate datele importante pentru clasa Malware

        return is;
    }

    ostream &write(ostream &os) const override {        //functie de afisare importata din laboratoare
        IoBase::write(os);
        cout << "Impact: ";
        os << impact<<endl;
        cout << "Data:\n";
        cout << "zi: "; os << datainf.zi; cout << ", luna: "; os << datainf.luna; cout << ", an: "; os << datainf.an<<endl;
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

class Rootkit: virtual public Malware {     //mostenire clasa Malware
protected:
    vector<string> importuri;
    vector<string> semnificative;
public:
    Rootkit() {}

    istream &read(istream &is) override {       //mostenire functie de citire
        Malware::read(is);
        string import;
        string semnificativ;
        cout << "Importuri (scrieti NONE pentru a trece mai departe): " ;
        importuri.clear();
        semnificative.clear();      //golim vectorii

        do {
            is >> import;
            importuri.push_back(import);
        }while (import != "NONE");

        cout << "Semnificative (scrieti NONE pentru a trece mai departe): ";

        do {
            is >> semnificativ;
            semnificative.push_back(semnificativ);
        }while (semnificativ != "NONE");

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

class Keylogger : virtual public Malware {      //alta mostenire
protected:
    vector<string> functii;
    vector<string> taste;
public:
    Keylogger() {}

    istream &read(istream &is) override {       //citire pentru keylogger
        Malware::read(is);
        functii.clear();
        taste.clear();
        cout << "Fuctii (scrieti NONE pentru a trece mai departe): ";
        string functie;
        string tasta;

        do {
            is >> functie;
            functii.push_back(functie);
        }while (functie != "NONE");

        cout << "Taste (scrieti NONE pentru a trece mai departe): ";

        do {
            is >> tasta;
            taste.push_back(tasta);
        }while (tasta != "NONE");

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
    Kernel_Keylogger() {}

    istream &read(istream &is) override {       //cititm proprietatile obiectului mostenit in diamant
        Rootkit::read(is);

        Keylogger::functii.clear();
        Keylogger::taste.clear();
        cout << "Fuctii (scrieti NONE pentru a trece mai departe): ";
        string functie;
        string tasta;

        do {
            is >> functie;
            Keylogger::functii.push_back(functie);
        }while (functie != "NONE");

        cout << "Taste (scrieti NONE pentru a trece mai departe): ";

        do {
            is >> tasta;
            Keylogger::taste.push_back(tasta);
        }while (tasta != "NONE");

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

    ostream &write(ostream &os) const override {        //citire Kernel Keylogger la care inca nu stiu daca merge
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

class Ransomware : public Malware {     //malware public inheritence for malware type ransomware
protected:
    int rating;
    int obfuscare;
public:
    Ransomware() {}

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

//deleted shared_ptr for being useless

class Computer {
protected:
    static int  contor;
    const  int id;
    vector<shared_ptr<Malware>> listaMalware;
    int ratingFinal;        //ratingul final se calculeaza si este initial 0
public:
    friend istream &operator>>(istream &in, Computer &c);
    friend ostream &operator<<(ostream &out, const Computer &c);
    Computer();

    const int getId() const;

    const vector<shared_ptr<Malware>> &getListaMalware() const;

    int getRatingFinal() const;
};

istream &operator>> ( istream &in, Computer &c ) {      //operatorul de citire pentru cate un calculator
    int tip;
    cout << "\n";
    cout << "Alegeti tipul malwareului din meniul de mai jos sau apasati 5 pentru a merge mai departe\n";
    cout << "Tipul malwareului (1: Rootkit, 2: Keylogger, 3: Kernel-Keylogger, 4: Ransomware): \n";
    shared_ptr<Malware> m;
    do {
        cin >> tip;                                                         //changing the type of malware we are working with
        if (tip == 1) {
            m = make_shared<Rootkit>();
            cin >> *m;
            c.listaMalware.push_back(m);
        } else if (tip == 2) {
            c.listaMalware.push_back(make_shared<Keylogger>());
        } else if (tip == 3) {
            c.listaMalware.push_back(make_shared<Kernel_Keylogger>());
        } else if (tip == 4) {
            c.listaMalware.push_back(make_shared<Ransomware>());
        } else {
            break;
        }
    }while (tip >=1 && tip <=4);

    return in;
}

int Computer::contor = 0;

Computer::Computer() : id(contor++) {}

const int Computer::getId() const {
    return id;
}

const vector<shared_ptr<Malware>> &Computer::getListaMalware() const {
    return listaMalware;
}

int Computer::getRatingFinal() const {
    return ratingFinal;
}
//automatic id incrementation


class Meniu {       //basic menu class for adding interface
private:
    vector<Computer> calculatoare;
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
                cout << "----------------------------------------------||----------------------------------------------------\n";
                break;
            }
        }
    }

    //menu functions

    void citireCalc();
    void afisareCalc();
    void afisareOrd();
    void afisarePrimeK();
    void afisareProcent();

};

void Meniu::citireCalc () {
    int n;
    Meniu::calculatoare.clear();
    cout << "Numarul calculatoarelor: "; cin >> n;      //input nr of computers
    Computer c;

    for ( int i=0; i<n; i++ ) {
        cout << "Adaugati calculator: "; cin >> c;      //read every computer and adding it to the list of computers in the firm
        Meniu::calculatoare.push_back(c);
    }
}

void Meniu::afisareCalc() {

    for ( int i=0; i<Meniu::calculatoare.size(); i++ ) {
        cout << "Calculatorul cu id: " << Meniu::calculatoare[i].getId() << ", ";
        cout << "cu lista de malwareuri: ";

        for ( int j=0; j<Meniu::calculatoare[i].getListaMalware().size(); j++ ) {
            cout << *Meniu::calculatoare[i].getListaMalware()[j] << " ";
        }

        cout << "cu ratingul final de: " << Meniu::calculatoare[i].getRatingFinal() << "\n\n";
    }
}

void Meniu::afisareOrd() {

}

void Meniu::afisarePrimeK() {

}

void Meniu::afisareProcent() {

}

int main() {
    Meniu m;
    m.run();
    return 0;
}