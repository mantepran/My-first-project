#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 

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
   
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}
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
Studentas ivesk() {
    Studentas Laik;
    int m;
    cout << "Iveskite varda: "; cin >> Laik.vard;
    cout << "Iveskite pavarde: "; cin >> Laik.pav;
    cout << "Iveskite namu darbu pazymius (baigus iveskite 0):" << endl;
    while (true) {
        cin >> m;
        if (m == 0) break;
        if (m < 0 || m > 10) {
            cout << "Klaida. Pazymys turi buti nuo 1 iki 10. Bandykite dar kartą: ";
            continue;
        }
        Laik.paz.push_back(m);
    }
    if (Laik.paz.empty()) {
        cout << "Klaida: studentas turi tureti bent viena pazymi!" << endl;
        return ivesk();
    }
    cout << "Iveskite egzamina: "; cin >> Laik.egzas; cout<< endl;
    return Laik;
}
Studentas iveskAtsitiktinai() {
    Studentas Laik;
    cout << "Iveskite varda: "; cin >> Laik.vard;
    cout << "Iveskite pavarde: "; cin >> Laik.pav;
    int kiekNd = random(1, 10);
    for (int i = 0; i < kiekNd; i++) {
        Laik.paz.push_back(random(1, 10));
    }
    cout << "Sugeneruoti " << kiekNd << " namu darbu pazymiai." << endl;

    Laik.egzas = random(1, 10);
    cout << "Sugeneruotas egzamino pazymys: " << Laik.egzas << endl;

    cout << endl;
    return Laik;
}
int main () {  
    srand(time(0));
    vector<Studentas> Grupe;
    for (int j = 0; j < 3; j++) {  
        cout << "Iveskite " << j + 1 << " studenta:\n";
        cout << "Ar norite generuoti pazymius atsitiktinai? (1 - taip, 0 - ne): ";
        int pasirinkimas;
        cin >> pasirinkimas;

        if (pasirinkimas == 1) {
            Grupe.push_back(iveskAtsitiktinai());
        } else {
            Grupe.push_back(ivesk());
        }
    }
    cout<<"Pasirinkite galutinio balo skaiciavimo buda: "<<endl;
    cout<<"1 - Vidurkis"<< endl<<"2 - Mediana"<<endl<<"3 - Abu"<<endl;
    int pasirinkimas;
    cin>>pasirinkimas;
    cout<<endl<<left<<setw(10)<<"Vardas"<<setw(10)<<"Pavarde";

    if (pasirinkimas == 1) cout<<"Galutinis (Vid.)";
    else if (pasirinkimas == 2) cout << "Galutinis (Med.)";
    else if (pasirinkimas == 3) cout << "Galutinis (Vid.) / Galutinis (Med.)";
    cout << endl << "---------------------------------------------------" << endl;

     for (auto temp : Grupe) {
        float sum = 0;
        for (int p : temp.paz) sum += p;
        float vid = sum / temp.paz.size();
        float med = mediana(temp.paz);
        float rezVid = temp.egzas * 0.6 + vid * 0.4;
        float rezMed = temp.egzas * 0.6 + med * 0.4;

        cout << left << setw(10) << temp.vard << setw(10) << temp.pav;
        if (pasirinkimas == 1) cout << setw(15) << fixed << setprecision(2) << rezVid;
        else if (pasirinkimas == 2) cout << setw(15) << fixed << setprecision(2) << rezMed;
        else if (pasirinkimas == 3)
            cout << setw(15) << fixed << setprecision(2) << rezVid
                 << setw(15) << fixed << setprecision(2) << rezMed;
        else cout << "Klaida. Pasirinktas netinkamas simbolis" << endl;
        cout << endl;
     }
}
