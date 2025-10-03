#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
#include <fstream> 

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
using std::ifstream;
using std::fstream;
using std::ofstream;
using std::getline;

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
    return Laik;
}
vector<Studentas> nuskaitykFailoDuomenis(string failoVardas) {
    vector<Studentas> sarasas;
    ifstream fin(failoVardas);
    if (!fin) {
        return sarasas;
    }
    string header;
    getline(fin, header); 
    while (true) {
        Studentas s;
        if (!(fin >> s.vard >> s.pav)) break; 
        vector<int> laik;
        int paz;
        while (fin >> paz) {
            laik.push_back(paz);
            if (fin.peek() == '\n') break; 
        }
        if (!laik.empty()) {
            s.egzas = laik.back(); 
            laik.pop_back();
            s.paz = laik;
        }
        sarasas.push_back(s);
    }
    return sarasas;
}
void atsitiktiniaiStudentai(const string& failoVardas, int irasuKiekis) {
    ofstream fout(failoVardas);
    if (!fout) {
        cout << "Nepavyko sukurti failo: " << failoVardas << "\n";
        return;
    }
    fout << left << "Vardas " << "Pavarde";
    for (int i = 1; i <= 5; i++) fout << "ND" << i << " ";
    fout << "Egzaminas" << "\n";

    for (int i = 1; i <= irasuKiekis; i++) {
        fout << "Vardas" << i << " Pavarde" << i << " ";
        for (int j = 0; j < 5; j++) {
            fout << random(1, 10) << " ";
        }
        fout << random(1, 10) << "\n";
    }
    fout.close();
}

bool pagalVarda(const Studentas& a, const Studentas& b) {
    return a.vard < b.vard;
}
bool pagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pav < b.pav;
}
int main () {  
    srand(time(0));
    vector<Studentas> Grupe;
    int veiksmas;

    while (true) {
        cout << "Programos veiksmu meniu:" << endl;
        cout << "1 - Prideti studenta" << endl;
        cout << "2 - Rodyti rezultatus" << endl;
        cout << "3 - Nuskaityti faila" << endl;
        cout << "4 - Sugeneruoti atsitiktinius failus" <<endl;
        cout << "5 - Iseiti" << endl;
        cout << "Pasirinkite: ";
        cin >> veiksmas;

        sort(Grupe.begin(), Grupe.end(), pagalPavarde);
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
            cout << "Kiek studentu parodyti? (0 - visus): ";
            int kiekParodyti;
            cin >> kiekParodyti;
            cout<<"Pasirinkite galutinio balo skaiciavimo buda: "<<endl;
            cout<<"1 - Vidurkis"<< endl<<"2 - Mediana"<<endl<<"3 - Abu"<<endl;
            int pasirinkimas;
            cin>>pasirinkimas;
            cout << "Rikiuoti pagal: 1 - Varda, 2 - Pavarde: ";
            int rikiuoti;
            cin >> rikiuoti;
            if (rikiuoti == 1)
                sort(Grupe.begin(), Grupe.end(), pagalVarda);
            else
                sort(Grupe.begin(), Grupe.end(), pagalPavarde);
            
            cout << "Kur norite spausdinti rezultatus? (1 - ekrane, 2 - i faila): ";
            int kur;
            cin >> kur;
            ofstream failas;
            if (kur == 2) {
                failas.open("parodyta.txt");
                if (!failas) {
                    cout << "Nepavyko sukurti failo, spausdiname ekrane." << endl;
                    kur = 1;
                }
            }
            if (kur == 1) {
                cout<<endl<<left<<setw(15)<<"Vardas"<<setw(15)<<"Pavarde";
                if (pasirinkimas == 1) cout<<"Galutinis (Vid.)";
                else if (pasirinkimas == 2) cout << "Galutinis (Med.)";
                else if (pasirinkimas == 3) cout << "Galutinis (Vid.) / Galutinis (Med.)";
                cout << endl << "---------------------------------------------------" << endl;
            }
            else if (kur == 2) {
                failas << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
                if (pasirinkimas == 1) failas << "Galutinis (Vid.)";
                else if (pasirinkimas == 2) failas << "Galutinis (Med.)";
                else if (pasirinkimas == 3) failas << "Galutinis (Vid.) / Galutinis (Med.)";
                failas << endl << "---------------------------------------------------" << endl;
            }        
            int kiek = 0;
            for (auto temp : Grupe) {
                if (kiekParodyti != 0 && kiek >= kiekParodyti) break;
                float sum = 0;
                for (int p : temp.paz) sum += p;
                float vid = sum / temp.paz.size();
                float med = mediana(temp.paz);
                float rezVid = temp.egzas * 0.6 + vid * 0.4;
                float rezMed = temp.egzas * 0.6 + med * 0.4;
                
                if (kur == 1) {
                    cout << left << setw(15) << temp.vard << setw(15) << temp.pav;
                    if (pasirinkimas == 1) cout << setw(15) << fixed << setprecision(2) << rezVid;
                    else if (pasirinkimas == 2) cout << setw(15) << fixed << setprecision(2) << rezMed;
                    else if (pasirinkimas == 3)
                        cout << setw(15) << fixed << setprecision(2) << rezVid
                        << setw(15) << fixed << setprecision(2) << rezMed;
                    cout << endl;
                }
                else if (kur == 2) {
                    failas << left << setw(15) << temp.vard << setw(15) << temp.pav;
                    if (pasirinkimas == 1) failas << setw(15) << fixed << setprecision(2) << rezVid;
                    else if (pasirinkimas == 2) failas << setw(15) << fixed << setprecision(2) << rezMed;
                    else if (pasirinkimas == 3)
                        failas << setw(15) << fixed << setprecision(2) << rezVid
                        << setw(15) << fixed << setprecision(2) << rezMed;
                    failas << endl;
                }
                kiek++;
            } failas.close();
        }
        else if (veiksmas == 3) {
            vector<Studentas> isFailo = nuskaitykFailoDuomenis("kursiokai.txt");
            if (isFailo.empty()) {
                cout << "Nepavyko atidaryti failo arba failas tuscias!" << endl;
            } 
            else {
            Grupe.insert(Grupe.end(), isFailo.begin(), isFailo.end());
            cout << "Failas nuskaitytas sekmingai." << endl;
            }
        }
        else if (veiksmas == 4) {
            atsitiktiniaiStudentai("studentai_1000.txt", 1000);
            atsitiktiniaiStudentai("studentai_10000.txt", 10000);
            atsitiktiniaiStudentai("studentai_100000.txt", 100000);
            atsitiktiniaiStudentai("studentai_1000000.txt", 1000000);
            atsitiktiniaiStudentai("studentai_10000000.txt", 10000000);
            cout << "Failai sekmingai sukurti." << endl << endl;
        }
        else if (veiksmas == 5) {
            cout << "Programa baigia darba." << endl;
            break;
        }
        cout << endl;
    }
}
