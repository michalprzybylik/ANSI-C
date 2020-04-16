/*
Michał Przybylik TI2
PVM minimum, maksimum macierzy
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "pvm3.h"

#define N 6									 //liczba wierszy macierzy
#define M 9									 //liczna kolumn macierzy
#define NUMRANGE 1000						 //zakres liczb w macierzy od 0 do NUMRANGE
#define BINPATH "/home/pvm/pvm3/lab/example" //sciezka do programu

void rodzic() //proces rodzica
{
	struct pvmhostinfo *hostp;
	int ilhost, ilarch, tid, tidmaster;
	char buffer[64];

	/* pobranie i wydrukowanie nazwy maszyny rodzica */
	gethostname(buffer, 20);
	printf("Rodzic: %s\n", buffer);

	/*inicjalizacja macierzy A wymiaru NxM losowymi liczbami
	z zakresu [0, NUMRANGE) i wydrukowanie jej.*/
	srand(time(NULL));
	int A[N][M];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%3d ", A[i][j] = rand() % NUMRANGE);
		printf("\n");
	}

	/* zgloszenie procesu do systemu PVM jesli wystapil
	   blad to wyjdz z kodem bledu 1 */
	if (tidmaster = pvm_mytid() < 0)
	{
		pvm_perror("enroll");
		exit(1);
	}

	/* sprawdzenie konfiguracji maszyny wirtualnej */
	pvm_config(&ilhost, &ilarch, &hostp);

	/* wydrukuj liste hostow, tworz proces potomny na kazdym z hostow,
	   az do wyczerpania hostow lub wierszy. jesli wywolanie procesu 
	   potomnego nie powiodlo sie wyswietl komunikat o bledzie i idz 
	   do nastepnego hosta. jesli udalo sie utworzyc proces potomny 
	   zlicz go i wyslij do niego wiersz macierzy i zlicz wyslany wiersz */
	printf("Hosty PVM: %d\n", ilhost);
	int i, nhosts = 0, nrows = 0;
	for (i = 0; i < ilhost && nrows < N; i++)
	{
		printf("\t%s\n", hostp[i].hi_name);
		if (!pvm_spawn(BINPATH, 0, PvmTaskHost, hostp[i].hi_name, 1, &tid))
			printf("błąd uruchomienia procesu na %s\n", hostp[i].hi_name);
		else
		{
			pvm_initsend(PvmDataDefault);
			pvm_pkint(A[nrows], M, 1);
			pvm_send(tid, 100);
			nhosts++;
			nrows++;
		}
	}

	/* dopoki sa wiersze do wyslania, odbierz przetworzone dane od potomka
	   sprawdz, ktory potomek wyslal dane, przetworz odebrane dane i wyslij
	   do wolnego potomka nastepny wiersz. */
	int bufid, nbytes, msgtag;
	int recminmax[2];
	int min = NUMRANGE, max = 0;
	for (; nrows < N; nrows++)
	{
		bufid = pvm_recv(-1, 200);
		pvm_bufinfo(bufid, &nbytes, &msgtag, &tid);
		pvm_upkint(recminmax, 2, 1);
		if (recminmax[0] < min)
			min = recminmax[0];
		if (recminmax[1] > max)
			max = recminmax[1];
		pvm_initsend(PvmDataDefault);
		pvm_pkint(A[nrows], M, 1);
		pvm_send(tid, 100);
	}
	/* odbierz dane dla pozostalych, przetworz je i zakoncz procesy potomne */
	while (nhosts--)
	{
		bufid = pvm_recv(-1, 200);
		pvm_bufinfo(bufid, &nbytes, &msgtag, &tid);
		pvm_upkint(recminmax, 2, 1);
		if (recminmax[0] < min)
			min = recminmax[0];
		if (recminmax[1] > max)
			max = recminmax[1];
		pvm_kill(tid);
	}

	/* wyswietl wynik i zakoncz proces rodzica*/
	printf("min = %d, max = %d\n", min, max);
	pvm_exit();
	exit(0);
}

void potomek() //proces potomka
{
	int tidmaster;
	tidmaster = pvm_parent(); //uzyskaj id rodzica
	int row[M];
	int minmax[2];
	/* odbiersz kolejne wiersze od rodzica, szukaj w nich
	   minimum i maksiumum, a nastepnie odslij wynik od rodzica */
	while (1)
	{
		pvm_recv(tidmaster, 100);
		pvm_upkint(row, M, 1);
		minmax[0] = minmax[1] = row[0];
		for (int i = 1; i < M; i++)
		{
			if (row[i] < minmax[0])
				minmax[0] = row[i];
			if (row[i] > minmax[1])
				minmax[1] = row[i];
		}
		pvm_initsend(PvmDataDefault);
		pvm_pkint(minmax, 2, 1);
		pvm_send(tidmaster, 200);
	}
}

int main(void)
{
	if (pvm_parent() == PvmNoParent)
		rodzic();
	else
		potomek();
}
