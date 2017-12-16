#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct aut{
	char kateg[50];
	char znacka[50];
	char predaj[100];
	int cena;
	int rokv;
	char stav[200];
	struct aut *next;
} AUTO;
void uvolni(AUTO *prv, AUTO *akt, int i)
{
	int j;
	for (j = 1; j < i; j++) {
		prv->next = akt->next;
		free(akt);
		akt = prv->next;
	}
	free(prv);
}
void Nacitanie(int *po, AUTO **prv, AUTO **akt) {
	int i = 0, c, q = 0;
	FILE *fr;
	if ((fr = fopen("auta.txt", "r")) == NULL) {
		printf("neotvoreny subor"); exit(1);
	}
	while ((c = getc(fr)) != EOF)
	{
		if (c == '\n') i++;
		if (c == '\n'&& i == 7) { q++; i = 0; }
	}
	printf("Nacitalo sa %d zaznamov\n", q);
	*po = q;
	if (((*prv) = (AUTO **)malloc(sizeof(AUTO))) == NULL) {
		printf("Malo pamate.\n");
		exit(1);
	}
	rewind(fr);
	*akt = *prv;
	AUTO *pom;
	char ret[200];
	for (i = 1; i <= q; i++) {
		pom = (*akt);
		fgets(ret, 3, fr);
		fgets(ret, 50, fr);
		ret[(strlen(ret) - 1)] = 0;// vymazanie '\n' z konca, pre lahsiu pracu v inych funkciach
		strcpy(((*akt)->kateg), ret);
		fgets(ret, 50, fr);
		ret[(strlen(ret) - 1)] = 0;
		strcpy(((*akt)->znacka), ret);
		fgets(ret, 100, fr);
		ret[(strlen(ret) - 1)] = 0;
		strcpy(((*akt)->predaj), ret);
		fscanf(fr, "%d\n", &pom->cena);
		fscanf(fr, "%d\n", &pom->rokv);
		fgets(ret, 200, fr);
		ret[(strlen(ret) - 1)] = 0;
		strcpy(((*akt)->stav), ret);
		if (i != q) {
			if ((((*akt)->next) = (AUTO **)malloc(sizeof(AUTO))) == NULL) {
				printf("Malo pamate.\n");
				exit(1);
			};
			(*akt) = (*akt)->next;
		}
	}
}
void Vypis(int poc, AUTO **prv, AUTO **aktu) {
	int i;
	AUTO *curr;
	curr = (prv);
	for (i = 0; i < poc; i++) {
		printf("%d.\n", i + 1);
		printf("kategoria: %s\n", (curr)->kateg);
		printf("znacka: %s\n", (curr)->znacka);
		printf("predajca: %s\n", (curr)->predaj);
		printf("cena: %d\n", (curr)->cena);
		printf("rok vyroby: %d\n", (curr)->rokv);
		printf("stav vozidla: %s\n", (curr)->stav);
		(curr) = (curr)->next;
	}
}

void Hladanie(int poc, AUTO **prv) {
	if (poc != 0) {
		int i, c, q = 0;
		scanf("%d", &c);
		AUTO *cur;
		cur = prv;
		for (i = 0; i < poc; i++) {
			if (c >= (cur->cena)) {
				++q;
				printf("%d.\n", q);
				printf("kategoria: %s\n", (cur)->kateg);
				printf("znacka: %s\n", (cur)->znacka);
				printf("predajca: %s\n", (cur)->predaj);
				printf("cena: %d\n", (cur)->cena);
				printf("rok vyroby: %d\n", (cur)->rokv);
				printf("stav vozidla: %s\n", (cur)->stav);
			}
			(cur) = (cur)->next;
		}
		if (q == 0) printf("V ponuke su len auta s vyssou cenou\n");
	}
}
void Pridanie(int h, int *p, AUTO **prv, AUTO **akt) {
	int i, n;
	scanf("%d", &n);
	if (n <= 0) exit(1);
	AUTO *new, *pom;
	if (((new) = (AUTO **)malloc(sizeof(AUTO))) == NULL) {
		printf("Malo pamate.\n");
		return;
	}
	char ret[200];
	getchar();
	gets_s((new->kateg), 200);
	gets_s((new->znacka), 200);
	gets_s((new->predaj), 200);
	scanf("%d", &(new)->cena);
	scanf("%d", &new->rokv);
	getchar();
	gets_s((new->stav), 200);
	if (*prv == NULL) { (*prv) = new; }//ak nie je vztvoreny zoznam
	else {
	pom = akt;
	if (n == 1) {
		new->next = (*prv);		// pridanie na 1. miesto
		*prv = new;

	}
	else if (n > 1 && n <= h) {
		for (i = 1; i < n - 1; i++) {//pridanie do stredu
			pom = pom->next;
		}
		new->next = pom->next;
		pom->next = new;
		pom = new->next;
	}
	else if (n > h) {
		for (i = 0; i < h - 1; i++) {// na koniec
			pom = pom->next;
		}
		pom->next = new;
		new->next = NULL;
	}
	}
	*p = h + 1;
}
void Zmaz(int n, int *poc, AUTO **prv, AUTO **akt) {
	if (akt == NULL) exit(1);
	AUTO *pom;
	AUTO *pred;
	int i, j, q = 0, c = 0;
	char ret[50];
	char po[50];
	getchar();
	gets_s(ret, 50);
	for (i = 0; i < (strlen(ret)); i++) {
		ret[i] = tolower(ret[i]);// tolower pre porovnavanie
	}
	pom = akt;
	for (i = 0; i < n; i++) {
		strcpy(po, (pom->znacka));
		for (j = 0; j < (strlen((pom->znacka))) - 1; j++) {
			po[j] = tolower(po[j]);
		}
		if ((strstr(po, ret)) != NULL) {
			if (i == q && ((n - q) != 1)) { //mazanie prvej pozicie
				*prv = pom->next;
				q++;
				free(pom);
				pom = *prv;
			}
			else if (i != q && i<n - 1) {// mazanie strednych
				pred->next = pom->next;
				free(pom);
				pom = pred->next;
				q++;
			}
			else if (i != q && i == (n - 1)) {// mazanie konecneho, zoznam neostane prazdny
				pred->next = pom->next;
				free(pom);
				pom = pred->next;
				q++;
			}
			else if ((n - q) == 1) { free((pom)); q++; *prv = NULL; }// kompletne mazanie
		}
		else { pred = pom; pom = pom->next; }
	}
	*poc = n - q;
	printf("Zmazalo sa %d zaznamov\n", q);
}
void Aktual(int *poc, AUTO **akt) {
	if (poc == 0) { printf("Zoznam nie je vytvoreny\n"); return; }
	int i, c, q = 0;
	char ret[50];
	AUTO *new, *pom;
	if (((new) = (AUTO **)malloc(sizeof(AUTO))) == NULL) {
		printf("Malo pamate.\n");
		return;
	}
	getchar();
	gets_s(ret, 50);
	scanf("%d", &c);
	getchar();
	gets_s((new->kateg), 200);
	gets_s((new->znacka), 200);
	gets_s((new->predaj), 200);
	scanf("%d", &(new)->cena);
	scanf("%d", &new->rokv);
	getchar();
	gets_s((new->stav), 200);
	pom = akt;
	new->stav[(strlen(new->stav)) - 1] = '\n';
	for (i = 0; i < poc; i++) {
		if ((strcmp(ret, (pom->znacka))) == 0 && c == (pom->cena)) {
			q++;
			strcpy((pom->kateg), new->kateg);
			strcpy((pom->znacka), new->znacka);
			strcpy((pom->predaj), new->predaj);
			strcpy((pom->stav), new->stav);
			pom->cena = new->cena;
			pom->rokv = new->rokv;
		}
		pom = pom->next;
	}
	printf("Aktualizovalo sa %d zaznamov\n", q);
	free(new);
}
int main() {
	int i, poc = 0, c, n;
	AUTO *prvy = NULL, *aktu, *posl;
	while ((c = getchar()) != 'k') {
		switch (c)
		{
		case 'n':
			if (poc != 0) {
				aktu = prvy->next;
				uvolni(prvy, aktu, poc);
			}

			Nacitanie(&poc, &prvy, &aktu); break;
		case 'v':
			if (poc != 0) { Vypis(poc, prvy, aktu); } break;
		case 'h':
			if (poc != 0) { Hladanie(poc, prvy); }break;
		case 'p':
			n = poc; aktu = prvy; Pridanie(n, &poc, &prvy, aktu); break;
		case 'z':
			if (poc != 0) { n = poc; aktu = prvy; Zmaz(n, &poc, &prvy, aktu); }break;
		case 'a':
			if (poc != 0) { aktu = prvy; Aktual(poc, aktu); }break;
		}

	}
	if (poc != 0) {
		aktu = prvy->next;
		uvolni(prvy, aktu, poc); 
	}
	return 0;
}