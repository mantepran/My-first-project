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
float mediana(vector<int> paz) {
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
Studentas ivesk(const string &vard, const string &pav) {
    Studentas Laik;
    Laik.vard = vard;
    Laik.pav = pav;
    int m;
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
        return ivesk(vard, pav);
    }
    cout << "Iveskite egzamina: "; cin >> Laik.egzas; cout<< endl;
    return Laik;
}
Studentas iveskAtsitiktinai(const string &vard, const string &pav) {
    Studentas Laik;
    Laik.vard = vard;
    Laik.pav = pav;
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
    int veiksmas;

    while (true) {
        cout << "Programos veiksmu meniu:" << endl;
        cout << "1 - Prideti studenta" << endl;
        cout << "2 - Rodyti rezultatus" << endl;
        cout << "3 - Iseiti" << endl;
        cout << "Pasirinkite: ";
        cin >> veiksmas;

        if (veiksmas == 1) {
            string vard, pav;
            cout << "Iveskite varda: ";
            cin >> vard;
            cout << "Iveskite pavarde: ";
            cin >> pav;

            int gen;
            cout << "Ar generuoti pazymius atsitiktinai? (1 - taip, 0 - ne): ";
            cin >> gen;

            Studentas s;
            if (gen == 1) s = iveskAtsitiktinai(vard, pav);
            else s = ivesk(vard, pav);

            if (!s.paz.empty()) Grupe.push_back(s);
        }
        else if (veiksmas == 2) {
            if (Grupe.empty()) {
                cout << "Studentu sarasas tuscias." << endl << endl;
                continue;
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
        else 
            cout << "Klaida. Pasirinktas netinkamas simbolis";
        cout << endl;
            }
        }
        else if (veiksmas == 3) {
            cout << "Programa baigia darba." << endl;
            break;
        }
    }
}
