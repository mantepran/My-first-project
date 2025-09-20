#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;

struct Studentas{
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    };
float mediana(vector<int> &paz) {
    sort(paz.begin(), paz.end());
    int dyd = paz.size();
    if (dyd == 0) {
        return 0;
    }
    if (dyd % 2 == 0) {
        return (paz[dyd / 2 - 1] + paz[dyd / 2]) / 2.0;
    } else {
        return paz[dyd / 2];
    }
}

int main () {  
    Studentas Laik;
    int sum = 0, n, m;
    cout<<"Iveskite varda: "; cin>>Laik.vard;
    cout<<"Iveskite pavarde: "; cin>>Laik.pav;
    cout<<"Kiek pazymiu turi studentas? "; cin>>n;
    if (n <= 0) {
        cout<<"Klaida. Studentas turi turėti bent vieną pažymį!"<<endl;
        return 1;
    }
    for (int i=0;i<n;i++){
        cout<<"Iveskite "<<i+1<< "paz. is "<<n<<" : "; cin>>m;
        Laik.paz.push_back(m);
        sum+=m;
    }
    cout<<"Iveskite egzamina: "; cin>>Laik.egzas; cout<<endl;
    
    float vid = (float)(sum) / n;
    float med = mediana(Laik.paz);
    float rezVid = Laik.egzas * 0.6 + vid * 0.4;
    float rezMed = Laik.egzas * 0.6 + med * 0.4;

    cout<<"Pasirinkite galutinio balo skaiciavimo buda: "<<endl;
    cout<<"1 - Vidurkis"<< endl<<"2 - Mediana"<<endl<<"3 - Abu"<<endl;

    int pasirinkimas;
    cin>>pasirinkimas;

    cout<<endl<<left<<setw(10)<<"Vardas"<<setw(10)<<"Pavarde";

    if (pasirinkimas == 1) {
        cout<<"Galutinis (Vid.)"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout << left << setw(10) << Laik.vard
            << setw(10) << Laik.pav
            << setw(20) << fixed << setprecision(2) << rezVid << endl;

    } else if (pasirinkimas == 2) {
        cout << "Galutinis (Med.)" << endl;
        cout << "------------------------------------------" << endl;
        cout << left << setw(10) << Laik.vard
             << setw(10) << Laik.pav
             << setw(20) << fixed << setprecision(2) << rezMed << endl;

    } else if (pasirinkimas == 3) {
        cout << "Galutinis (Vid.) / Galutinis (Med.)" << endl;
        cout << "------------------------------------------" << endl;
        cout << left << setw(10) << Laik.vard
             << setw(10) << Laik.pav
             << setw(20) << fixed << setprecision(2) << rezVid
             << setw(20) << fixed << setprecision(2) << rezMed << endl;

    } else {
        cout << "Klaida. Pasirinktas netinkamas simbolis" << endl;
    }
}
