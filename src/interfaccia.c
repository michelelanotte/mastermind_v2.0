#include "interfaccia.h"

void Pagina_principale()
{
	char scelta[DIM_MAX];
	int voce_menu;
	int esito_scelta = 0;
	int numero_tentativi = 4;
	int lunghezza = 4;
	int doppioni = 1;
	int x, y;

	do {
	    system("cls");
		Stampare_titolo();
		Stampare_menu();
	    if(esito_scelta == 1)
	    {
	    	x = 24;
	    	y = 8;
	    	gotoxy(x, y);
	    	printf("\e[31m \e[1mErrore nella digitazione!\e[37m \e[0m");
	    }
	    x = 0;
	    y = 10;
	    gotoxy(x, y);
	    printf("Inserire numero corrispondente alla voce desiderata: ");
	    scanf("%s", scelta);
	    if(strlen(scelta) == 1)
	    {
	        voce_menu = (int)*scelta;  //livello_difficolta assumerà il valore ASCII del carattere inserito
	        if((voce_menu < 49) || (voce_menu > 52))  //49 è il codice ASCII di 1, 51 è il codice ASCII di 3
	        {
	            esito_scelta = 1;
	        }
	    }
	    else
	    {
	        esito_scelta = 1;
	    }
	}while((voce_menu < 49) || (voce_menu > 52));

	voce_menu = voce_menu - 48;
	if(voce_menu == 1)
	{
	    Nuova_partita(numero_tentativi, doppioni, lunghezza);
	}
	else
	{
		if(voce_menu == 2)
		{
	        //Carica_partita();
		}
		else
		{
			if(voce_menu == 3)
			{
				Impostazioni(&lunghezza, &numero_tentativi, &doppioni);
			}
			else
			{
				//Aiuto();
			}
		}
	}
	return;
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Stampare_titolo()
{
	int x = 0;
	int y = 0;
	gotoxy(x, y);
	printf("\e[1m ------------------( M | A | S | T | E | R | M | I | N | D )------------------ \e[0m");
	return;
}

void Stampare_menu()
{
	int x = 29;
	int y = 2;
	gotoxy(x, y);
	printf("      MENU      ");
	y = 3;
	gotoxy(x, y);
	printf("1. Nuova partita ");
	y = 4;
	gotoxy(x, y);
	printf("2. Carica partita ");
	y = 5;
	gotoxy(x, y);
	printf("3. Impostazioni ");
	y = 6;
	gotoxy(x, y);
	printf("4. Aiuto ");
	return;
}

void Stampare_risultati_precedenti(dati_gioco info_partita, int tentativo, int y)
{
	int i;
	int x;
	x = 0;
	gotoxy(x, y);
	printf("Tentativo: %d", tentativo + 1);
	printf("  Codice:");
	i = 0;
	while(i < Leggere_difficolta(info_partita))
	{
		printf(" %d ", Leggere_elemento_utente(info_partita, i, tentativo));
		i = i + 1;
	}
	printf(" Elementi corretti: %d", Leggere_corretti(info_partita, tentativo));
	printf("  Elementi presenti: %d", Leggere_presenti(info_partita, tentativo));
	return;
}

void Acquisire_parola_utente(dati_gioco *info_partita, int riga, int tentativo)
{
    int i;
	int numero;
	char numero_input[DIM_MAX];
	int x;
	int posizione_errore = 25;
	int esito_acquisizione = 0;
	x = 0;
	gotoxy(x, riga);
	printf(" Inserire il codice da verificare: \n");
	riga = riga + 1;
	i = 0;
	while(i < Leggere_difficolta(*info_partita))
	{
	    do {
	    	Pulire_riga(riga);

	    	if(esito_acquisizione == 1)
        	{
        	    gotoxy(posizione_errore, riga);
                printf("\e[31m \e[1mErrore! Inserire numero tra 0 e 9!\e[37m\e[0m");
                esito_acquisizione = 0;
        	}

	    	x = 0;
	    	gotoxy(x, riga);
	        printf(" %d. ", i + 1);
	        fflush(stdin);
	        x = 3;
	        gotoxy(x, riga);
	        scanf("%s", numero_input);
	        if(strlen(numero_input) == 1)
	        {
	            numero = (int)*numero_input;
	            if(numero < 48 || numero > 57)  //48 è il codice ASCII dello 0 mentre 57 è il codice ASCII di 9
	            {
	                esito_acquisizione = 1;
	            }
	        }
	        else
	        {
	        	esito_acquisizione = 1;
	        }
		}while(numero < 48 || numero > 57);
	    numero = numero - 48;
		Scrivere_elemento_utente(numero, info_partita, i, tentativo);
	    i = i + 1;
	    riga = riga + 1;
	    Cancellare_errore(posizione_errore, riga - 1);
	}
	return;
}

void Pulire_riga(int y)
{
	int x = 0;
	while(x < N_COLONNE_DISPLAY)
	{
		gotoxy(x, y);
		printf(" ");
		x = x + 1;
	}
	return;
}

void Cancellare_errore(int x, int y)
{
	while(x < N_COLONNE_DISPLAY)
	{
		gotoxy(x, y);
		printf(" ");
		x = x + 1;
	}
	return;
}

void Stampare_esito(dati_gioco info_partita, int esito_parole_uguali, int tentativo_ultimo)
{
	system("cls");
	Stampare_titolo();
    int i;
	if(esito_parole_uguali)
    {
	    printf("\e[1m\n\nSEI RIUSCITO A TROVARE LA COMBINAZIONE GIUSTA IN %d TENTATIVI! COMPLIMENTI!\n\e[0m", tentativo_ultimo);
	}
	else
	{
	   	printf("--------------------------------------------------------------------------");
	   	printf("\n\nIl codice da indovinare era il seguente: \n");
	   	i = 0;
	   	while(i < Leggere_difficolta(info_partita))
	   	{
	  	    printf(" %d ", Leggere_elemento_generato(info_partita, i));
	    	i = i + 1;
	    }
	    printf("\e[1m\n\nNON SEI STATO FORTUNATO! NON SEI RIUSCITO A TROVARE LA COMBINAZIONE GIUSTA!\n\e[0m");
	}
	return;
}

void Stampare_livelli_difficolta()
{
	int x, y;
	x = 25;
	y = 2;
	gotoxy(x, y);
    printf("\nInserire il numero corrispondente alla difficolta' desiderata: \n1.Facile \n");
    printf("2.Intermedio\n");
    printf("3.Difficile\n");
    return;
}
