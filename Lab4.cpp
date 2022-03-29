#include<bits/stdc++.h>
using namespace std;

class Student {
    string nume;
    string prenume;
    int grupa;
    int semigrupa;
    vector <int> note;
public:
    Student () { //default constructor 
        grupa = 0;
        semigrupa = 0;
    }

    Student (string word1, string word2, int num1, int num2, vector <int> _note) {
        nume = word1;
        prenume = word2;
        grupa = num1;
        semigrupa = num2;
        note = _note;
    }

    string getNume () const {
        return nume;
    }
    
    string getPrenume() const {
        return prenume;
    }

    int getGrupa() const {
        return grupa;
    }

    int getSemigrupa() const {
        return semigrupa;
    }
    
    const vector<int>& getNote() {
        return note;
    }

    void setNume(string word);
    void setPrenume(string word);
    void setGrupa(int num);
    void setSemigrupa(int num);
    void setNote(vector<int> _note);
    friend istream &operator>>(istream &is, Student &student);
    friend ostream &operator<<(ostream &os, const Student &student);

    void operator+=(int notaNoua) {
        note.push_back(notaNoua);
    }

    Student &operator-=(Student &c) {
        note.clear();
        return *this;
    }
};

void Student::setNume(string word) {
    Student::nume = word;
}

void Student::setPrenume(string word) {
    Student::prenume = word;
}

void Student::setGrupa(int num) {
    Student::grupa = num;
}

void Student::setSemigrupa(int num) {
    Student::semigrupa = num;
}

void Student::setNote(vector<int> _note) {
    Student::note = _note;
}

istream &operator>>(istream &is, Student &student) {
    cout<<"Numele: ";
    is >> student.nume;
    cout<<"Prenume: ";
    is >> student.prenume;
    cout<<"Grupa: ";
    is >> student.grupa;
    cout<< "Semigrupa: ";
    is >> student.semigrupa;
    cout<<"Numarul de note: ";
    student.note.clear();
    int n;
    is>>n;
    cout<<"Notele sunt: ";
    for (int i=0; i<n; i++) {
        int nota;
        is>>nota;
        student.note.push_back(nota);
    }

    return is;
}

ostream &operator<<(ostream &os, const Student &student) {
    os<<"Numele este: "<<student.nume<<", "
        <<"Prenumele este: "<<student.prenume<<", "
        <<"Grupa este: "<<student.grupa<<" "
        <<"Semigrupa este: "<<student.semigrupa<<", ";
    os<<"Notele sunt: ";
    for (int i=0; i<student.note.size(); i++) {
        os<<student.note[i]<<" ";
    }
    os<<endl;

    return os;
}

int main() {
    Student student;

    cin>>student;

    student+=10;
    student+=8;

    cout<<student;

    student-=;
    cout<<student;

    return 0;
}