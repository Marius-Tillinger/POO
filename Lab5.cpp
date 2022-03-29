#include<bits/stdc++.h>
using namespace std;

struct Nota {
    int value;
    string subject;
    friend ostream& operator<<(ostream &os, Nota nota) {
        os<<nota.subject<<": "<<nota.value;

        return os;
    }
};

template<typename T> ostream& operator<<(ostream &os, vector<T> &vec) {
    for (int i=0; i<vec.size(); i++) {
        os<<vec[i]<<" ";
    }

    return os;
}

class PersoanaEvaluata {
protected:
    vector<Nota> note;

public:
    PersoanaEvaluata(const vector<Nota> &note) : note(note) {}

    double medie () {
        double sum=0;
        for (auto nota:note) {
            sum += nota.value;
        }
        return sum/note.size();
    }

    const vector<Nota>& getNote() {
        return note;
    }

    void setNote(vector<Nota> _note) {
        note = _note;
    }
};

class Pupil : public PersoanaEvaluata {
    string cycle;
public:
    Pupil(const vector<Nota> &note, const string cycle) : PersoanaEvaluata(note), cycle(cycle) {}
    void showGradeSheet() {
        for (auto nota:note) {
            cout<<nota.subject<<":"<<nota.value<<"\n";
        }
    }

    void gradesGroupedbySubject() {
        vector<string> Materii;
        for (auto nota:note) {
            if (find(Materii.begin(), Materii.end(), nota.subject) == Materii.end()) {
                Materii.push_back(nota.subject);
            }
        }

        for (auto materie:Materii) {
            cout<<materie<<": ";
            for (auto nota:note) {
                if (materie == nota.subject) {
                    cout<<nota.value<<" ";
                }
            }
            cout<<endl;
        }
    }

    string getCycle() {
        return cycle;
    }

    void setCycle(string _cycle) {
        cycle = _cycle;
    }
};

int main() {
    vector<Nota> chestii;
    Nota var;
    for (int i=0; i<5; i++) {
        cin>>var.value;
        cin>>var.subject;
        chestii.push_back(var);
    }

    string a = "liceu";

    // Pupil p(chestii, a);
    // PersoanaEvaluata p1(chestii);
    // p.showGradeSheet();
    // p.gradesGroupedbySubject();
    // cout<<endl;
    // cout<<endl;
    cout<<chestii<<endl;;

    return 0;
}