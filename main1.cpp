#include <iostream>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

class IrrationalFraction;

class Fraction : public IoBase {
protected:
    int a, b;
public:
    // constructori
    Fraction(int a, int b) : a(a), b(b) {}

    Fraction() {}

    // IoBase - overrided functions
    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "a: ";
        is >> a;
        cout << "b: ";
        is >> b;
         cout << a <<"/" << b;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << a << "/";
        cout << b;
        return os;
    }

    friend bool operator<(Fraction &g, IrrationalFraction &f);
    friend float operator*(Fraction &g, IrrationalFraction &f);
};

class IrrationalFraction : public Fraction {
private:
    // adaugam si radicalul dintr-un numar real
    double underSqrt;
public:
    // constructori:
    IrrationalFraction() {}
    IrrationalFraction(int a, int b, double underSqrt): Fraction(a,b), underSqrt(underSqrt) {}

    // IoBase - overrided functions
    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "a: ";
        is >> a;
        cout << "b: ";
        is >> b;
        cout << "sqrt: ";
        is >> underSqrt;
        cout << a <<"/" << b << "*" << "sqrt(" << underSqrt << ")";
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << a << "/";
        cout << b << "*";
        cout<< "sqrt("<<underSqrt<< ")";
        return os;
    }

    friend bool operator<(Fraction &g,  IrrationalFraction &f);
    friend float operator*(Fraction &g, IrrationalFraction &f);
};

// Vom implementa cele doua clase
// Vom implementa <
// TODO aici editorul are un feature fain, genereaza toti op >, < etc

/*
Exemplu input:

2 3         -> citim fractia 2/3
1 2 2       -> citim fractia 1/2*sqrt(2)

Ca indiciu, vom avea 2/3 < 1/2*sqrt(2).
*/


bool operator<(Fraction &g,  IrrationalFraction &f) {
    float termen1, termen2;
    termen1 = g.a/g.b;
    termen2 = f.a * f.underSqrt/ f.b;
    if (termen1 < termen2) {
        return true;
    }
    else {
        return false;
    }
}

float operator*(Fraction &g, IrrationalFraction &f) {
    float termen1, termen2;
    termen1 = (float)g.a/g.b;
    termen2 = (float)f.a * f.underSqrt/ f.b;
    float rezultat;
    rezultat = termen1 * termen2;
    return rezultat;
}

// functie catre clasa de baza:
// TODO testati ce se intampla daca eliminati ampersand-ul
void show(const Fraction f) {
    cout << "Fractia este: " << f << '\n';
}

int main() {
    // level 0: constructori si operatori de afisare
    Fraction f1(2,3);
    IrrationalFraction f2(1,2,2);

//    // TODO Level 1: operator de citire
//    cin >> f1;
//    cin >> f2;
//    cout << f1 << " si " << f2;

    Fraction f3;
    IrrationalFraction f4;
    cin>>f3;
    cout<<endl;
    cin>>f4;
    cout<<endl;
    cout<<f3<< " si " <<f4;
    cout<<endl;

//    // TODO level 2: Operator supraincarcat cu clase diferite
//    if (f1 < f2) {
//        cout << f1 << " < " << f2 << '\n';
//    } else {
//        cout << f2 << " < " << f1 << '\n';
//    }

    if (f3 < f4) {
        cout << f3 << " < " << f4;
        cout<<endl;
    }
    else {
        cout << f4 << " < " << f3;
        cout<<endl;
    }

//    // TODO Level 3: operatori si metode
//    cout << f1 * f2 << '\n';
//    // TODO Intrebari spre rezolvare:
//    //  -----------------------------
//    // TODO Cand inmultim doua fractii, una de forma a/b si cealalta a/b*sqrt(c),
//    //      la ce forma ajungem?

    float chestie;

    chestie = f3 * f4;

    cout << chestie;
    cout << endl;
    
    // Aveti deja implementata functia globala show(Fraction f).
    // TODO Ce se intampla cand urmatoarele 2 linii de cod?
    show(f1);
    show(f2);
    // TODO dar daca adaugam & la parametrul din show?
}