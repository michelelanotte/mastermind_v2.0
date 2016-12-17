#include "operazioni.h"

//-------------------------- Nuova partita-------------------------------------------------------------------------------------

void Nuova_partita(int numero_tentativi, int doppioni, int lunghezza)
{
	dati_gioco info_partita;
	int esito_parole_uguali;
	int contatore_tentativi;
	int spazio_libero;
	int tentativi_stampabili;
	int x, y;
	int i = 0;

	Scrivere_info_partita(&info_partita, numero_tentativi, lunghezza);
	Generare_parola(&info_partita, doppioni, lunghezza);
	contatore_tentativi = 0;
	do {
		system("cls");
		Stampare_titolo();
		Scrivere_tentativo_corrente(&info_partita, contatore_tentativi);

		spazio_libero = N_RIGHE_DISPLAY - (6 + lunghezza);
		y = 2;
		if(contatore_tentativi < spazio_libero)
		{
			x = 0;
			i =  0;
			while( i < contatore_tentativi)
			{
				Stampare_risultati_precedenti(info_partita, i, y);
				i = i + 1;
				y = y + 1;
			}
		}
		else
		{
			tentativi_stampabili = contatore_tentativi - spazio_libero;
			i = tentativi_stampabili;
			while(i < contatore_tentativi)
			{
				Stampare_risultati_precedenti(info_partita, i, y);
				i = i + 1;
				y = y + 1;
			}
		}

			gotoxy(x, y);
			printf("\e[1m \e[4m\n----------- TENTATIVO NUMERO: %d -----------\e[0m", contatore_tentativi + 1);
		    Acquisire_parola_utente(&info_partita, y + 3, contatore_tentativi);

	    Valutazione_parola(&info_partita, contatore_tentativi);
	    esito_parole_uguali = Controllo_parole_uguali(info_partita, contatore_tentativi);  //restituisce 1 se la parola(codice) è stata indovinata
	    contatore_tentativi = contatore_tentativi + 1;
	}while(esito_parole_uguali != 1 && (contatore_tentativi < numero_tentativi));
	Stampare_esito(info_partita, esito_parole_uguali, contatore_tentativi);
	system("pause");
	return;
}

void Generare_parola(dati_gioco *info_partita, int doppioni, int lunghezza)
{
	int i;
	int numero_generato;
	srand(time(NULL));   //funzione della libreria time.h che permetterà in seguito di generare il codice da indovinare
	i = 0;
	while(i < lunghezza)
    {
	    do {
	        numero_generato = rand() % (VALMAX + VALMIN );  //tale istruzione genera un numero casuale che sia compreso tra VALMAX e VALMIN
		}while((doppioni == 0) && (Simbolo_presente(numero_generato, *info_partita, i)));
		Scrivere_elemento_generato(numero_generato, info_partita, i);
		printf("%d ", numero_generato);
	    i = i + 1;
	}
	system("pause");
	return;
}

int Simbolo_presente(int numero_generato, dati_gioco info_partita, int posizione_elemento)
{
	int i;
	int esito_ricerca = 0;
	i = 0;
	while(i < Leggere_difficolta(info_partita))
	{
	    if((numero_generato == Leggere_elemento_generato(info_partita, i)) && (i != posizione_elemento))
	    {
	        esito_ricerca = 1;
	    }
	    i = i + 1;
	}
	return esito_ricerca;
}

void Valutazione_parola(dati_gioco *info_partita, int tentativo)
{
	 int i, j;
	  int simbolo_codice_utente, simbolo_codice_generato;
	  int valore_codice_utente, valore_codice_generato;
	  char corretto, presente;
	  int contatore_corretti, contatore_presenti;
	  codice temp_utente, temp_generato;
	  char valutazione[LUNGHEZZA_MAX];
	  int lunghezza = Leggere_difficolta(*info_partita);
	  Inizializzare_valutazione(valutazione, lunghezza);

	  corretto = 'c';
	  presente = 'p';
	  simbolo_codice_utente = -2;
	  simbolo_codice_generato = -1;

	  i = 0;
	  while(i < Leggere_difficolta(*info_partita))  //questo ciclo permette di individuare i numeri corretti che si trovano nel codice inserito da tastiera
	  {
		valore_codice_utente = Leggere_elemento_utente(*info_partita, i, tentativo);
		valore_codice_generato = Leggere_elemento_generato(*info_partita, i);
	    if(valore_codice_utente == valore_codice_generato)
	    {
	      Scrivere_elemento_temp(simbolo_codice_utente, &temp_utente, i);
	      Scrivere_elemento_temp(simbolo_codice_generato, &temp_generato, i);
	      Scrivere_valutazione(corretto, valutazione, i);
	    }
	    else
	    {
	      Scrivere_elemento_temp(valore_codice_utente, &temp_utente, i);
	      Scrivere_elemento_temp(valore_codice_generato, &temp_generato, i);
	    }
	    i = i + 1;
	  }

	  //le istruzioni che seguono permettono di individuare i numeri del codice inserito da tastiera presenti nel codice generato
	  i = 0;
	  while(i < lunghezza)
	  {
	    j = 0;
	    while(j < lunghezza)
	    {
	      if(Leggere_elemento_temp(temp_utente, i) == Leggere_elemento_temp(temp_generato, j))
	      {
	        Scrivere_valutazione(presente, valutazione, i);
	        Scrivere_elemento_temp(simbolo_codice_utente, &temp_utente, i);
	        Scrivere_elemento_temp(simbolo_codice_generato, &temp_generato, j);
	      }
	      j = j + 1;
	    }
	    i = i + 1;
	  }
      Conteggiare_valutazioni(&contatore_presenti, &contatore_corretti, valutazione, lunghezza);
      info_partita->info_cod_utente[tentativo].corretti = contatore_corretti;
      info_partita->info_cod_utente[tentativo].sbagliati = contatore_presenti;
	  return;
	}


int Controllo_parole_uguali(dati_gioco info_partita, int tentativo)
{
	  int esito = 0;
	  if(Leggere_corretti(info_partita, tentativo) == Leggere_difficolta(info_partita))
	  {
	    esito = 1;
	  }
	  return esito;
}

void Conteggiare_valutazioni(int *conteggio_presenti, int *conteggio_corretti, char valutazione[LUNGHEZZA_MAX], int lunghezza)
{
	int i = 0;
	*conteggio_presenti = 0;
	*conteggio_corretti = 0;
	while(i < lunghezza)
	{
		if(valutazione[i] == 'c')
		{
			*conteggio_corretti = *conteggio_corretti + 1;
		}
		else
		{
			if(valutazione[i] == 'p')
			{
				*conteggio_presenti = *conteggio_presenti + 1;
			}
		}
		i = i + 1;
	}
	return;
}

//-------------------------------------------------------------------------------------------------------------------------------

void Impostazioni(int *lunghezza, int *numero_tentativi, int *doppioni)
{
	int x, y;
	int esc;
	char esc_carattere;

	Acquisizione_difficolta(*lunghezza, *numero_tentativi);
	y = 7;
	Pulire_riga(y);
    Acquisire_ammissione_doppioni(*doppioni);
    y = 9;
    Pulire_riga(y);
	x = 0;
	y = 23;
	gotoxy(x, y);
	printf("\e[8m");
    while(esc != 27)
    {
        esc_carattere = getch();
        esc = (int)esc_carattere;
        if(esc == 27)
        {
            Pagina_principale();
        }
    }
    return;
}

void Acquisizione_difficolta(int lunghezza, int numero_tentativi)
{
    char difficolta[DIM_MAX];
	int livello_difficolta;
	int x, y;
	int esito_acquisizione = 0;
	do {
		system("cls");
	    y = 24;
	    x = 0;
	    gotoxy(x, y);
		printf("\e[47m \e[30m  Premere ESC per tornare al menu' principale                                  \e[0m");
    	Pulire_riga(x);
    	if(esito_acquisizione == 1)
    	{
    		x = 15;
			y = 7;
    	    gotoxy(x, y);
            printf("\e[31m \e[1mErrore nella digitazione!\e[37m\e[0m");
            esito_acquisizione = 0;
    	}
		Stampare_titolo();
	    Stampare_livelli_difficolta();
	    x = 0;
	    y = 7;
	    gotoxy(x, y);
	    scanf("%s", difficolta);
	    if(strlen(difficolta) == 1)
	    {
	        livello_difficolta = (int)*difficolta;  //livello_difficolta assumerà il valore ASCII del carattere inserito
	        if((livello_difficolta < 49) || (livello_difficolta > 51))  //49 è il codice ASCII di 1, 51 è il codice ASCII di 3
	        {
	            esito_acquisizione = 1;
	        }
	    }
	    else
	    {
            esito_acquisizione = 1;
	    }
	}while((livello_difficolta < 49) || (livello_difficolta > 51));
	livello_difficolta = livello_difficolta - 48;  //sottraendo 48 al valore di livello_difficolta, si ricava un numero(1,2 0 3) corrispondente al livello scelto dall'utente
	if(livello_difficolta == 1)
	{
		lunghezza = 4;
		numero_tentativi = 9;
	}
	else
	{
	    if(livello_difficolta == 2)
	    {
	        lunghezza = 6;
	        numero_tentativi = 18;
	    }
	    else
	    {
	        lunghezza = 8;
	        numero_tentativi = 27;
	    }
	}
	return;
}

void Acquisire_ammissione_doppioni(int doppioni)
{
	char risposta;
	int x, y;
	do {
	    y = 24;
	    x = 0;
	    gotoxy(x, y);
		printf("\e[47m \e[30m  Premere ESC per tornare al menu' principale                                  \e[0m");
        x = 64;
		y = 10;
		while(x < N_COLONNE_DISPLAY)
		{
			gotoxy(x, y);
			printf(" ");
			x = x + 1;
		}
		x = 0;
		gotoxy(x, y);
	    printf("Vuoi permettere anche i doppioni nel codice da indovinare? (s/n)");
		fflush(stdin);
	    scanf("%c", &risposta);
	    if(risposta == 's')
	    {
	      doppioni = 1;
	    }
	    else
	    {
		  if(risposta == 'n')
		  {
		    doppioni = 0;
		  }
		  else
		  {
		      y = 9;
		      gotoxy(x, y);
		      printf("\e[31m \e[1mErrore nella digitazione della risposta! \e[37m\e[0m");
		  }
	    }
	  }while((risposta != 's') && (risposta != 'n'));
	  return;
}
