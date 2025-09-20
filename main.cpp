#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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
    float rez;
    };

int main () {  
    Studentas Laik;
    int sum = 0, n, m;
    cout<<"Iveskite varda: "; cin>>Laik.vard;
    cout<<"Iveskite pavarde: "; cin>>Laik.pav;
    cout<<"Kiek pazymiu turi studentas? "; cin>>n;
    for (int i=0;i<n;i++){
        cout<<"Iveskite "<<i+1<< "paz. is "<<n<<" : "; cin>>m;
        Laik.paz.push_back(m);
        sum+=m;
    }
    cout<<"Iveskite egzamina: "; cin>>Laik.egzas;
    Laik.rez= Laik.egzas*0.6 + double(sum)/double(Laik.paz.size()) *0.4;

    cout << fixed << setprecision(2);
    cout << left << setw(15) << "Vardas"
     << left << setw(15) << "Pavarde"
     << right << setw(15) << "Galutinis (vid.)" << endl;
    cout << "------------------------------------------" << endl;
    cout << left << setw(15) << Laik.vard
     << left << setw(15) << Laik.pav
     << right << setw(15) << Laik.rez << endl;
}
