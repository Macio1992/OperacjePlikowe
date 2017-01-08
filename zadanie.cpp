/*
    Napisz program wyswietlajacy plik na ekranie: dziesietnie oraz tekstowo w dwoch kolumnach.
    Program powinien miec nastepujace funkcje:
    1. Otwarcie pliku
    2. Zamkniecie pliku
    3. Tryb wyswietlania: tekstowo
    4. Tryb wyswietlania: dziesietnie + tekstowo
    5. Dalej (przewijanie ekranu - page down)
    6. Wstecz (przewijanie ekranu - page down)
    7. Koniec
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#define ILOSC_SLOW 25

using namespace std;

void czytaj(ifstream &, bool);
void wypiszInstrukcje();

int main(){

    ifstream plik;

    char wybor = 0;
    string nazwa;

    do{
        wypiszInstrukcje();
        cin>>wybor;
        switch(wybor){
            case 'O':
            case 'o':{
                if(!plik.is_open() && plik.good()){
                    //cout<<"Podaj nazwe pliku:"<<endl;
                    //cin >> nazwa;
                    nazwa = "tekst.txt";
                    plik.open(nazwa.c_str(), ios::binary);
                } else 
                    cout<<"Otworzono plik poprawnie. Jak chcesz otworzyc inny wybierz opcje nr 2"<<endl;
                
                 if(!plik)
                    cout<<"Blad podczas otwierania pliku"<<endl;
                 else
                    cout<<"Poprawnie otworzono plik o nazwie: "<<nazwa<<endl;
                break;
            }
            case 'Z':
            case 'z': {
                if(plik.is_open()){
                    plik.close();
                    cout<<"Poprawnie zamknieto plik: "<<nazwa<<endl;
                } 
                else
                    cout<<"Plik zamknieto. Otworz inny uzywajac opcji nr 1"<<endl;
                break;
            }
            case 'T':
            case 't':{
                if(!plik.is_open())
                    cout<<"Nie otworzono zadnego pliku."<<endl;
                else
                    czytaj(plik, false);
                
                break;
            }
            case 'D':
            case 'd': {
                if(!plik.is_open())
                    cout<<"Nie otworzono zadnego pliku."<<endl;
                else
                    czytaj(plik, true);

                break;
            }
            case 'K':
            case 'k':{
                wybor = 'K';
                break;
            }
            default:{
                cout<<"Wybierz O lub K lub T lub D. Zadnych innych znakow"<<endl;
                break;
            }
        }
    } while(!(wybor == 'K' || wybor == 'k'));
    cout<<"Koniec programu"<<endl;

    return 0;
}

void czytaj(ifstream &plik, bool czyDziesietnie){
    system("cls");
    int i = 0, size = 0, koniec;
    char ch;
    
    plik.seekg(0, ios::end);
    koniec = plik.tellg()/sizeof(int);

    plik.seekg(0, ios::beg);
    while(plik >>noskipws >> ch && size < ILOSC_SLOW){
        if(!czyDziesietnie)
            cout<<ch;
        else
            cout<<ch<<": "<<(int)ch<<" ";
        size = plik.tellg();
        size /= sizeof(int);
        plik.clear();
    }
    cout<<endl;
    plik.clear();

    char c;
    do{
        cout<<"D - Dalej"<<endl;
        cout<<"W - Wstecz"<<endl;
        cout<<"K - Koniec przegladania tego pliku"<<endl;
        cin >> c;
        switch(c){
            case 'D':
            case 'd':{
                
                plik.clear();
                int size2;
                if(plik.tellg()/sizeof(int) == koniec){
                    cout<<"Jestes na koncu pliku"<<endl;
                    size = size2+ILOSC_SLOW;
                    size2 = (size2 - ILOSC_SLOW)+ILOSC_SLOW;
                    plik.seekg(size2*sizeof(int), ios::beg);
                } else {
                    size = plik.tellg()/sizeof(int);
                    plik.seekg(size*sizeof(int), ios::beg);
                    size2 = size+ILOSC_SLOW;
                    while(plik >>noskipws >> ch && size < size2){
                        if(!czyDziesietnie)
                            cout<<ch;
                        else
                            cout<<ch<<": "<<(int)ch<<" ";
                        size = plik.tellg();
                        size /= sizeof(int);
                        plik.clear();
                    }
                    cout<<endl;
                    
                }

                break;
            }
            case 'W':
            case 'w':{
                int size2;
                plik.clear();
                if(plik.tellg()/sizeof(int) == ILOSC_SLOW){
                    cout<<"Jestes na poczatku pliku"<<endl;
                    plik.seekg(0, ios::beg);
                    size = plik.tellg()/sizeof(int);
                    while(plik >>noskipws >> ch && size < ILOSC_SLOW){
                        if(!czyDziesietnie)
                            cout<<ch;
                        else
                            cout<<ch<<": "<<(int)ch<<" ";
                        size = plik.tellg();
                        size /= sizeof(int);
                        plik.clear();
                    }
                    cout<<endl;
                } else {
                    size = size - 25;
                    size2 = size - 25;
                    plik.seekg(size2*sizeof(int), ios::beg);

                    while(plik >>noskipws >> ch && size2 < size){
                        if(!czyDziesietnie)
                            cout<<ch;
                        else
                            cout<<ch<<": "<<(int)ch<<" ";
                        size2 = plik.tellg();
                        size2 /= sizeof(int);
                        plik.clear();
                    }
                    cout<<endl;
                }
                
                break;
            }
            case 'K':
            case 'k':{
                c = 'k';
                break;
            }
            default:{
                cout<<"Wybierz D lub K"<<endl;
                break;
            }
        }
    } while(!(c == 'K' || c == 'k'));

    plik.clear();
    plik.seekg(0, ios::beg);
}

void wypiszInstrukcje(){
    cout<<"Wybierz:"<<endl;
    cout<<"O - Otwarcie pliku"<<endl;
    cout<<"Z - Zamkniecie pliku"<<endl;
    cout<<"T - Tryb wyswietlania: tekstowo"<<endl;
    cout<<"D - Tryb wyswietlania: dziesietnie + tekstowo"<<endl;
    cout<<"K - Koniec"<<endl;
}