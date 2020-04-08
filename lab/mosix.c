/*Michal Przybylik TI2
 
Program losuje ilosc liczb naturalnych wiekszych od 1 podanych w stalej symbolicznej NUMSIZE.
Nastepnie oblicza sume ich najwiekszych dzielnikow calkowitych.
 
1 parametr wywolania - n liczba tworzonych prcesow potomnych
 
Proces rodzica tworzy dwa potoki oraz n potomkow (n jest parametrem wywolania programu).
Nastepnie losuje i wysyla wszystkie liczby do potoku. Procesy potomne odbieraja, przetwarzaja
i odsylaja wyniki do rodzica, dopoki nie odbiora z potoku liczby -1. Kiedy tak sie stanie koncza
prace. Proces rodzica odbiera liczby od potomkow przez potok i sumuje je. Gdy wszystkie liczby 
zostana odebrane, rodzic wysyla do potoku n liczb -1, co jest sygnalem dla potomkow do zakonczenia
pracy
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define NUMSIZE 512  //liczba liczb do przetworzenia
#define NUMRANGE 1024 //zakres liczby od 2 do NUMRANGE
#define ENDDATA -1

int maxdiv(int n); //deklaracja funkcji zwracajacej najwiekszy calkowity dzielnik liczby naturalnej n wiekszej od 1

int main(int argc, char *argv[])
{
        if (argc != 2)
                perror("skladnia \"nazwa_programu liczba_potomkow\""), exit(1);

        int n;
        if ((n = atoi(argv[1])) <= 0)
                perror("argument musi byc liczba dodatnia"), exit(2);

        int sendpipe[2], recpipe[2];         //utworzenie dwoch potokow, potok sendpipe odpowiada za dane przesylane
        if (pipe(sendpipe) || pipe(recpipe)) //od rodzica do potomkow, potok recpipe za dane wynikowe od potomkow do rodzica
                perror("blad tworzenia potoku"), exit(-2);
        int tosend, rec;

        long int sum = 0;

        int pid;
        int i = n;                         //utworzenie n procesow potomnych przez rodzica
        while (i-- && (pid = fork()) >= 0) //nowo utworzony proces potomny od razu wychodzi
                if (!pid)                  //z petli (jego pid jest rowny 0)
                        break;

        switch (pid) //sprawdz czy proces potomka czy rodzica
        {
        case -1:
                perror("blad tworzenia procesu rodzica");
                i = n;
                tosend = ENDDATA;
                while (i--)
                        write(sendpipe[1], &tosend, sizeof(tosend));
                exit(-1);
                break;
        case 0:                                                                //proces potomka
                while (read(sendpipe[0], &rec, sizeof(rec)) && rec != ENDDATA) //odbieraj, przetwarzaj i odsylaj dane dopoki nie otrzymasz z potoku liczby -1
                {
                        tosend = maxdiv(rec);                       //wykonaj obliczenia
                        write(recpipe[1], &tosend, sizeof(tosend)); //odeslij wynik do rodzica
                }
                exit(0);
                break;
        default:                        //proces rodzica
                srand(time(NULL));
                i = NUMSIZE;            //wylosuj NUMSIZE liczb,
                printf("Wylosowano: "); //wypisz je na wyjscie
                while (i--)             //i wyslij do potomkow przez potok
                {
                        printf("%d ", tosend = (rand() % (NUMRANGE - 2)) + 2); //wylosuj liczbe i wypisz ja
                        write(sendpipe[1], &tosend, sizeof(tosend));           //wyslij wylosowana liczbe do potomka
                }

                i = NUMSIZE; //odbierz wyniki
                while (i--)  //i oblicz sume
                {
                        read(recpipe[0], &rec, sizeof(rec)); //odbierz wynik z potoku
                        sum += rec;                          //dodaj go obliczanej sumy
                }

                i = n;
                tosend = ENDDATA;
                while (i--)                                          //gdy wszystkie liczby zostaly przetworzone wyslij n liczb
                        write(sendpipe[1], &tosend, sizeof(tosend)); //ENDDATA co bedzie sygnalem do zakonczenia pracy potomkow

                printf("\nSuma najwiekszych dzielnikow tych liczb wynosi: %ld\n", sum); //wypisz wynik
                return 0;
                break;
        }
}

int maxdiv(int n) //funkcja najwiekszy calkowity dzielnik liczby wiekszej od 1
{
        if (!(n % 2))         //jesli liczba jest parzysta, to
                return n / 2; //jej najwiekszy calkowity dzielnik jest rowny jej polowie
        else
        {                                          //gdy liczba jest nieparzysta szukaj najwiekszego dzielnika
                int i;                             //sprawdzajac reszty z dzielenia tej liczby przez liczby i z
                for (i = n - 1; i >= sqrt(n); --i) //zakresu [floor(sqrt(n)), n - 1] od konca przedzialu
                        if (!(n % i))              //jesli i jest pierwsza liczba liczac od konca przedzialu,
                                return i;          //ktora dzieli n bez reszty to jest ona szukana liczba
                return 1;                          //w przciwnym wypadku szukana liczba to 1
        }
}
