#include "operazioni.h"


//-------------------------- Nuova partita-------------------------------------------------------------------------------------

void Nuova_partita(settings *impostazioni)
{
	dati_gioco info_partita;
	int esito_parole_uguali;
	int contatore_tentativi;
	int spazio_libero;
	int tentativi_stampabili;
	int n_righe_utilizzate = 13; //sono le righe già utilizzate(ad esempio per inserire il codice, la riga per indicare la presenza di un errore...
	int esc;
	int x, y;
	int i = 0;

	Scrivere_info_partita(&info_partita, *impostazioni);
	Generare_parola(&info_partita, *impostazioni);
	contatore_tentativi = 0;
	do {
		system("cls");
		Stampare_titolo();
		Scrivere_tentativo_corrente(&info_partita, contatore_tentativi);

		spazio_libero = N_RIGHE_DISPLAY - n_righe_utilizzate;   //spazio_libero indica quanto spazio è disponibile per stampare
		y = 2;												    //         i risultati dei tentativi precedenti
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
			tentativi_stampabili = contatore_tentativi - spazio_libero;  //tentativi_stampabili contiene il numero di tentativi stampabili
			i = tentativi_stampabili;                                    // se tutti i tentativi precedenti non possono essere stampati
			while(i < contatore_tentativi)                               // per motivi legati allo spazio disponibile
			{
				Stampare_risultati_precedenti(info_partita, i, y);
				i = i + 1;
				y = y + 1;
			}
		}
		gotoxy(x, y);
		printf("\e[1m \e[4m\n----------- TENTATIVO NUMERO: %d -----------\e[0m", contatore_tentativi + 1);
		Acquisire_parola_utente(&info_partita, y + 3, contatore_tentativi, spazio_libero, impostazioni);

	    Valutazione_parola(&info_partita, contatore_tentativi);
	    esito_parole_uguali = Controllo_parole_uguali(info_partita, contatore_tentativi);  //restituisce 1 se la parola(codice) è stata indovinata
	    contatore_tentativi = contatore_tentativi + 1;
	}while(esito_parole_uguali != 1 && (contatore_tentativi < Leggere_max_tentativi(*impostazioni)));
	Stampare_esito(info_partita, esito_parole_uguali, contatore_tentativi);

	x = 0;
	y = 23;
	gotoxy(x, y);
    printf("\e[47m \e[30mPremere \e[4mCTRL^R\e[0m\e[47m\e[30m per tornare al menu' principale.                                ");
    printf("\n Premere \e[4mCTRL^Q\e[0m\e[47m\e[30m per uscire dal gioco.                                           \e[0m");
    y = 22;
    gotoxy(x, y);
    while((esc != 18) && (esc != 17))
    {
    	esc = (int)getch();
    }
    if(esc == 18)
    {
    	Pagina_principale(impostazioni);
    }
    else
    {
    	exit(1);
    }
	return;
}

void Generare_parola(dati_gioco *info_partita, settings impostazioni)
{
	int i;
	int numero_generato;
	srand(time(NULL));   //funzione della libreria time.h che permetterà in seguito di generare il codice da indovinare
	i = 0;
	while(i < Leggere_lunghezza(impostazioni))
    {
	    do {
	        numero_generato = rand() % (VALMAX + VALMIN );  //tale istruzione genera un numero casuale che sia compreso tra VALMAX e VALMIN
		}while((Leggere_doppioni(impostazioni) == 0) && (Simbolo_presente(numero_generato, *info_partita, i)));
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


//----------------------------Carica partita---------------------------------------------------------------------

void Salvataggio_partita(int y, int x, dati_gioco *info_partita, settings *impostazioni)
{
	int esito_risposta;
	int colonna_risposta = 55;
	int colonna_stampa_messaggi = 0;
	FILE *slot;
	char risposta[DIM_MAX];

	Cancellare_errore(x, y);
	Pulire_riga(y + 1);

	if((slot = fopen("salvataggio.bin", "rb")) != NULL)
	{
		fclose(slot);
		gotoxy(colonna_stampa_messaggi, y + 1);
		printf("Esiste gia' un salvataggio. Vuoi sovrascriverlo? (s/n)");
		esito_risposta = 0;
		do{
			gotoxy(colonna_risposta, y + 1);
			scanf("%s", risposta);
			if(strlen(risposta) == 1)
			{
				if(*risposta == 's')
				{
					esito_risposta = 1;
				}
				else
				{
					if(*risposta == 'n')
					{
						Pulire_riga(y + 1);
						Pulire_riga(y + 2);
						esito_risposta = 2;
					}
					else
					{
						gotoxy(x, y + 2);
						Cancellare_errore(colonna_risposta, y + 1);
						printf("\e[31m \e[1mErrore nella digitazione della risposta! \e[37m\e[0m");
					}
				}
			}
			else
			{
				gotoxy(x, y + 2);
				Cancellare_errore(colonna_risposta, y + 1);
				printf("\e[31m \e[1mErrore nella digitazione della risposta! \e[37m\e[0m");
			}
		}while(esito_risposta == 0);
	}
	else
	{
		esito_risposta = 1;
	}

	if(esito_risposta == 1)
	{
		if((slot = fopen("salvataggio.bin", "wb")) == NULL)
		{
			Pulire_riga(y + 2);
			gotoxy(0, y + 2);
			printf("Impossibile salvare partita!");
		}
		else
		{
			if(fwrite(&info_partita, sizeof(dati_gioco), 1, slot) != 0)
			{
				Pulire_riga(y + 1);
				gotoxy(0, y + 2);
				fclose(slot);
				Pagina_principale(impostazioni);
			}
		}
	}
	return;
}


//----------------------------Impostazioni del gioco-------------------------------------------------------------

void Impostazioni(settings *impostazioni)
{
	int x, y;
	int uscita;

	Acquisizione_difficolta(impostazioni);
	x = 15;
	y = 11;
	Cancellare_errore(x, y);
    Acquisire_ammissione_doppioni(impostazioni);
    y = 13;
    Pulire_riga(y);
	x = 0;
	y = 23;
	gotoxy(x, y);
	printf("\e[8m");
    printf("\e[47m \e[30mPremere \e[4mCTRL^R\e[0m\e[47m\e[30m per tornare al menu' principale.                                ");
    printf("\n Premere \e[4mCTRL^Q\e[0m\e[47m\e[30m per chiudere il gioco.                                          \e[0m");
    y = 22;
    gotoxy(x, y);
    while((uscita != 18) && (uscita != 17))
    {
    	uscita = (int)getch();
    }
    if(uscita == 18)
    {
    	Pagina_principale(impostazioni);
    }
    else
    {
    	exit(1);
    }
    return;
}

void Acquisire_ammissione_doppioni(settings *impostazioni)
{
	char risposta[DIM_MAX];
	int esito_risposta = 0;
	int doppioni;
	int x, y;
	do {
		x = 0;
    	y = 23;
    	gotoxy(x, y);
        printf("\e[47m \e[30mPremere \e[4mCTRL^R\e[0m\e[47m\e[30m e di seguito \e[4mINVIO\e[0m\e[47m\e[30m per tornare al menu' principale.      ");
        printf("\n Premere \e[4mCTRL^Q\e[0m\e[47m\e[30m e di seguito \e[4mINVIO\e[0m\e[47m\e[30m  per chiudere il gioco.                     \e[0m");
		y = 14;
		Pulire_riga(y);
		x = 0;
		gotoxy(x, y);
	    printf("Vuoi permettere anche i doppioni nel codice da indovinare? (s/n)");
		fflush(stdin);
	    scanf("%s", risposta);

	    if(strlen(risposta) == 1)
	    {
	    	if((int)*risposta == 18)
	    	{
	    		esito_risposta = 1;
	   	   	    Pagina_principale(impostazioni);
	    	}
	       	else
	       	{
	       	   	if((int)*risposta == 17)
	       	  	{
	       	   		exit(1);
	       	   	}
	       	   	else
	       	   	{
	       	   		if(*risposta == 's')
	       	   		{
	       	   			esito_risposta = 1;
	       	   			doppioni = 1;
	       	   			Scrivere_doppioni(impostazioni, doppioni);
	       	   		}
	       	   		else
	       	   		{
	       	   			if(*risposta == 'n')
	       	   			{
	       	   				esito_risposta = 1;
	       	   				doppioni = 0;
	       	   				Scrivere_doppioni(impostazioni, doppioni);
	       	   			}
	       	   			else
	       	   			{
	       	   				y = 13;
	       	   				gotoxy(x, y);
	       	   				printf("\e[31m \e[1mErrore nella digitazione della risposta! \e[37m\e[0m");
	       	   			}
	       	   		}
	       	   	}
	       	}
	    }
	    else
	    {
	    	y = 13;
	    	gotoxy(x, y);
	      	printf("\e[31m \e[1mErrore nella digitazione della risposta! \e[37m\e[0m");
	   	}
    }while(esito_risposta == 0);
    return;
}

void Acquisizione_difficolta(settings *impostazioni)
{
    char difficolta[DIM_MAX];
	int livello_difficolta;
	int lunghezza, numero_tentativi;
	int x, y;
	int esito_acquisizione_errata = 0;
	do {
		system("cls");

		x = 0;
    	y = 23;
    	gotoxy(x, y);
        printf("\e[47m \e[30mPremere \e[4mCTRL^R\e[0m\e[47m\e[30m e di seguito \e[4mINVIO\e[0m\e[47m\e[30m per tornare al menu' principale.             ");
        printf("\n Premere \e[4mCTRL^Q\e[0m\e[47m\e[30m e di seguito \e[4mINVIO\e[0m\e[47m\e[30m per chiudere il gioco.                                   \e[0m");

        if(esito_acquisizione_errata == 1)
    	{
    		x = 15;
			y = 11;
    	    gotoxy(x, y);
            printf("\e[31m \e[1mErrore nella digitazione!\e[37m\e[0m");
            esito_acquisizione_errata = 0;
    	}

		Stampare_titolo();
	    Stampare_livelli_difficolta();
	    x = 63;
	    y = 7;
	    gotoxy(x, y);
	    scanf("%s", difficolta);
	    if(strlen(difficolta) == 1)
	    {
	    	if((int)*difficolta == 18)
	    	{
	    		Pagina_principale(impostazioni);
	    	}
	    	else
	    	{
	    		if((int)*difficolta == 17)
	    		{
	    			exit(1);
	    		}
	    		else
	    		{
	        		livello_difficolta = (int)*difficolta;  //livello_difficolta assumerà il valore ASCII del carattere inserito
	        		if((livello_difficolta < 49) || (livello_difficolta > 51))  //49 è il codice ASCII di 1, 51 è il codice ASCII di 3
	        		{
	        			esito_acquisizione_errata = 1;
	        		}
	        	}
	    	}
	    }
	    else
	    {
	    	esito_acquisizione_errata = 1;
	    }
	}while(((livello_difficolta < 49) || (livello_difficolta > 51)) && (livello_difficolta != 18));
	livello_difficolta = livello_difficolta - 48;  //sottraendo 48 al valore di livello_difficolta, si ricava un numero(1,2 0 3) corrispondente al livello scelto dall'utente
	if(livello_difficolta == 1)
	{
		lunghezza = 4;
		numero_tentativi = 9;
		Scrivere_max_tentativi(impostazioni, numero_tentativi);
		Scrivere_lunghezza(impostazioni, lunghezza);
	}
	else
	{
	    if(livello_difficolta == 2)
	    {
	        lunghezza = 6;
	        numero_tentativi = 18;
			Scrivere_max_tentativi(impostazioni, numero_tentativi);
			Scrivere_lunghezza(impostazioni, lunghezza);
	    }
	    else
	    {
	        lunghezza = 8;
	        numero_tentativi = 27;
			Scrivere_max_tentativi(impostazioni, numero_tentativi);
			Scrivere_lunghezza(impostazioni, lunghezza);
	    }
	}
	return;
}
