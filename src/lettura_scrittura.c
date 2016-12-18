#include "lettura_scrittura.h"

void Scrivere_info_partita(dati_gioco *info_partita, int numero_tentativi, int lunghezza)
{
	info_partita->max_tentativi = numero_tentativi;
	info_partita->lunghezza_codice = lunghezza;
	return;
}

void Scrivere_elemento_generato(int numero_generato, dati_gioco *info_partita, int posizione)
{
	(info_partita->codice_generato[posizione]) = numero_generato;
	return;
}

void Scrivere_tentativo_corrente(dati_gioco *info_partita, int tentativo)
{
	info_partita->tentativo = tentativo;
	return;
}

void Scrivere_elemento_utente(int numero, dati_gioco *info_partita, int posizione, int tentativo)
{
	info_partita->info_cod_utente[tentativo].codice_utente[posizione] = numero;
	return;
}

void Scrivere_elemento_temp(int valore, codice *codice_temp, int posizione)
{
	codice_temp->codice_gioco[posizione] = valore;
	return;
}

void Inizializzare_valutazione(char valutazione[LUNGHEZZA_MAX], int lunghezza)
{
	int i = 0;
	char spazio = ' ';
	while(i < lunghezza)
	{
		valutazione[i] = spazio;
        i = i + 1;
	}
	return;
}

void Scrivere_valutazione(char carattere, char valutazione[LUNGHEZZA_MAX], int posizione)
{
	valutazione[posizione] = carattere;
	return;
}


int Leggere_difficolta(dati_gioco info_partita)
{
	return info_partita.lunghezza_codice;
}

int Leggere_elemento_generato(dati_gioco info_partita, int posizione)
{
	return info_partita.codice_generato[posizione];
}

int Leggere_elemento_utente(dati_gioco info_partita, int posizione, int tentativo)
{
	return info_partita.info_cod_utente[tentativo].codice_utente[posizione];
}

int Leggere_corretti(dati_gioco info_partita, int tentativo)
{
	return info_partita.info_cod_utente[tentativo].corretti;
}

int Leggere_presenti(dati_gioco info_partita, int tentativo)
{
	return info_partita.info_cod_utente[tentativo].sbagliati;
}

int Leggere_elemento_temp(codice codice_temp, int posizione)
{
	return codice_temp.codice_gioco[posizione];
}

