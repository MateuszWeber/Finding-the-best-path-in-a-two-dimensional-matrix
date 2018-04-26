#include <iostream>
#include <cstdlib>
#include <ctime>    //biblioteka potrzebna do srand(time(NULL));
#include <conio.h>

#define MAX_KOLUMNY_M 39    //zdefiniujemy sobie maksymalna liczbe kolumn na 39
#define MAX_WIERSZE_N 24    //zdefiniujemy sobie maksymalna liczbe kolumn na 39

using namespace std;

//funkcja generujaca liczby pseudolosowe w tablicy
void GenTab( int T[MAX_WIERSZE_N][MAX_KOLUMNY_M], int N, int M )
{
    for (int i = 0; i < N; i++) //dla wszystkich wierszy od 0 do n-1
    {
        for(int j = 0; j < M; j++)  //dla wszystkich kolumn od 0 do m-1
        {
            T[i][j] = rand()%10;  //wpisz reszte dzielenia wygenerowanej liczby przez 10 do tablicy
        }
    }
}

//funkcja wyswietlajaca tablice
void Wyswietl( int T[MAX_WIERSZE_N][MAX_KOLUMNY_M], int N, int M )
{
    for (int i = 0; i < N; i++) //dla wszystkich wierszy od 0 do n-1
    {
        for(int j = 0; j < M; j++)  //dla wszystkich kolumn od 0 do m-1
        {
            cout<<T[i][j]<<" ";  //wpisz wygenerowana liczbe do tablicy
        }
        cout<<endl;     //nowa linia po kazdym wypisanym wierszu
    }
}

//funkcja algorytmu zachlannego
int AlgorytmZachlanny(int T[MAX_WIERSZE_N][MAX_KOLUMNY_M], int N, int M)
{
    int i = 0, j = 0, suma = 0; //deklarujemy zmienne pomocnicze
    suma = T[i][j]; //zaczynamy sumowac sciezke poczawszy od pierwszego elementu

    while((i < N-1) || (j < M-1))   //petle bedziemy wykonywali dopoki nie przejdziemy calej tablicy i znajdziemy sie na ostatnim elemencie
    {
        if( (i < N-1 && ( T[i+1][j] >= T[i][j+1] )) || (j==M-1) ) //jezeli nie jest to ostatni wiersz i element ponizej jest wiekszy od elementu z prawej
        {                                                         //lub jezeli jestesmy juz z ostatniej kolumnie, to:
            suma += T[i+1][j];                                    //sumujemy do naszej sciezki element ponizej,
            i++;                                                  //przechodzimy do nizszego wiersza
            cout<<"DOL ";                                         // i wypisujemy slowo dol w konsoli
        }
        else                    //jezeli powyzszy if nie jest spelniony, to:
        {
            suma += T[i][j+1];  //sumujemy do naszej sciezki element po prawej
            j++;                //przechodzimy do kolejnej kolumny
            cout<<"PRAWO ";     //wypisujemy w prawo
        }
    }
    return suma;                //funkcja zwraca sume naszej sciezki w tablicy
}

//funkcja wypelniajaca wiersze w tablicy pomocniczej
/*
Algorytm oblicza maksymalna mozliwa sciezke dojscia do kazdego elementu tablicy.

Dla przykladowej tablicy 3x3:
3   7   3
5   1   2
9   9   2

Algorytm wykonuje kolejne itaracje obliczajac maksymalna sume dojcia dla kazdego elelementu i trzyma wyniki w tablicy pomocniczej:

I iteracja:
3   10  13
0   0   0
0   0   0

II iteracja:
3   10  13
8   11  15
0   0   0

III iteracja:
3   10  13
8   11  15
17  26  28

Algorytm zachalnny obliczylby sume maksymalnej sciezki przykladowej tablicy jako 17.
Nasz algorytm oblicza 28.
Chcac aby program wypisal sciezke idziemy od ostatniego elementu (liczba 28) i przechodzimy po najwyzszych liczbach do elementu pierwszego (liczba 3),czyli wygladaloby to:
28 - 26 - 17 - 8 - 3
*/
void WypelnijWiersz( int T[MAX_WIERSZE_N][MAX_KOLUMNY_M], int i, int M, int tablicaPomocnicza[MAX_WIERSZE_N][MAX_KOLUMNY_M])
{
    if(i==0)tablicaPomocnicza[i][0] = T[i][0];  //pierwszy element bedzie taki sam
    else tablicaPomocnicza[i][0] = tablicaPomocnicza[i-1][0] + T[i][0]; //dzialanie dla pierwszej kolumny

    for(int j = 1; j < M; j++)      //petle wykonujemy dla wszystkich kolumn
    {
        if( i == 0)tablicaPomocnicza[i][j] = tablicaPomocnicza[i][j-1] + T[i][j];   //obliczamy pierwszy wiersz (mozliwwe sumowanie tylko "z boku"
        else    //pozostale wiersze
        {
            if(tablicaPomocnicza[i-1][j] >= tablicaPomocnicza[i][j-1])  //spwadzanie czy liczba z gory jest wieksza niz liczba z boku
            {
                tablicaPomocnicza[i][j] = tablicaPomocnicza[i-1][j] + T[i][j];  //sumujemy scieze dojscia dodajac liczbe z gory
            }
            else    //jezeli licza z gory jest mniejsza niz liczba z boku
            {
                tablicaPomocnicza[i][j] = tablicaPomocnicza[i][j-1] + T[i][j];  //sumujemy scieze dojscia dodajac liczbe z gory
            }
        }
    }
}

//algorytm szukacjy sciezki w taablicy
int AlgorytmSzukanie(int T[MAX_WIERSZE_N][MAX_KOLUMNY_M], int N, int M)
{

    int tablicaPomocnicza[MAX_WIERSZE_N][MAX_KOLUMNY_M];    //inicjujemy tabele pomocnicza o takim rozmiarze jak glowna tablica

//zerowanie tablicy pomocniczej
    for(int i = 0; i < MAX_WIERSZE_N; i++)  //kazdy wiersz
    {
        for(int j = 0; j < MAX_KOLUMNY_M; j++)  //kazda kolumna
        {
            tablicaPomocnicza[i][j] = 0;    //do kazdego elementu wpisujemy 0
        }
    }

    //tutaj zaczyna dzialac algorytm
    for (int i = 0; i < N; i++)
    {
        WypelnijWiersz(T, i, M, tablicaPomocnicza); //dla kazdego wiersza w tablicy wywolujemy funkcje
    }

    cout<<"Przejscie tablicy algorytmem najlepszym."<<endl;

    int k = N+M;    //zmienna pomocnicza
    int wyniki[k];  //tablica pomocnicza przechowujaca sciezke przejscia
    int i = N - 1;  //ostatni wiersz
    int j = M - 1;  //ostatnia kolumna

    //aby wyswietlicz sciezke przejscia musimy przejsc tablice od konca do poczatku przez najwieksze elementy w tablicy pomocniczej
    while ( i > 0 || j > 0) //wykonujemy dopoki nie dojdziemy do pierszego elementu w tablicy
    {
        if (( i > 0 && tablicaPomocnicza[i-1][j] >= tablicaPomocnicza[i][j-1]) || j == 0)   //jezeli nie jest to pierszy wiersz, a element powyzej jest
        {                                                       //wiekszy od elementu z lewej strony tablicy pomocniczej, lub jesetsmy w pierwszej kolumnie
            i--;                    //przechodzimy do wiersza wyzej
            wyniki[k] = 1;          //zapiszemy sobie ze ruch z gore - dol oznaczymy jako 1
        }
        else    //jezeli powyzszy if nie jest spelniony, czyli ruszczamy sie w prawo - lewo
        {
            wyniki[k] = 2;  //zapiszemy sobie ruch w bok jako 2
            j--;    //przechodzimy do kolumnu w lewo
        }
        k--;    //zmniejszamy indeks w tablicy pomocniczej
    }
//wyswietlanie sciezki przejsca, jedziemy od pierszego elementu
    for (k = 0; k <= N+M ;k++)
    {
        if (wyniki[k] == 1) cout<<"DOL ";   //tak jak powyzej ruch gora do to 1
        else if (wyniki[k] ==2) cout<<"PRAWO ";//2 oznacza ruch w bok
    }

    //wyswietlanie
    cout<<"\nTablica pomocnicza poszczegolnych sum pol przedstawia sie nastapujaco:"<<endl;
    Wyswietl(tablicaPomocnicza,N,M);    //wysiwetlamy tablice pomocnicza

    return tablicaPomocnicza[N-1][M-1]; //zwracamy ostatni element w tablicy, ktry jest liczba najlepszej sciezki w tablicy
}

int main()
{
    int N,M;

    srand(time(NULL));  //ustawienie ziarna generatora liczb pseudolosowych na podstaie czasu z systemu

    cout<<"Najpierw stworzymy tablice wypelniona liczbami losowymi."<<endl;
    cout<<"Podaj wymiaty tablicy:\nN- ilosc wierszy\nM - ilosc kolumn"<<endl;
    cin>>N>>M;

    while(N > MAX_WIERSZE_N){
        cout<<"Wprowadziles zla liczbe wierszy!\nMaksymalna wartosc to: "<<MAX_WIERSZE_N<<endl<<"Sproboj jeszcze raz."<<endl;
        cin>>N;
    }
    while(M > MAX_KOLUMNY_M){
        cout<<"Wprowadziles zla liczbe kolumn!\nMaksymalna wartosc to: "<<MAX_KOLUMNY_M<<endl<<"Sproboj jeszcze raz."<<endl;
        cin>>M;
    }

    int T[MAX_WIERSZE_N][MAX_KOLUMNY_M];

    cout<<"Tworzenie tablicy."<<endl;
    GenTab(T, N, M);

    cout<<"Oto stworzona tablica:"<<endl;
    Wyswietl(T, N, M);

    cout<<"Szukanie najlepszej sciezki algorytmem zachlannym."<<endl;
    int suma = AlgorytmZachlanny(T, N, M);
    cout<<"\nObliczona suma najlepszej sciezki algotytmem zachlanym to: "<<suma<<endl;

    cout<<"\nSzukanie najlepszej sciezki algorytmem najlepszym."<<endl;
    suma = AlgorytmSzukanie(T, N, M);
    cout<<"\nObliczona suma najlepszej sciezki algotytmem najlepszym to: "<<suma<<endl;

    getch();//czekanie na dowolny klawisz
    return 0;
}
