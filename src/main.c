#include "globali.h"
#include "interfaccia.h"

int main()
{
	settings impostazioni_partita;
	int tentativi = 9;
	int lunghezza = 4;
	int doppioni = 1;
	Scrivere_max_tentativi(&impostazioni_partita, tentativi);
	Scrivere_lunghezza(&impostazioni_partita, lunghezza);
	Scrivere_doppioni(&impostazioni_partita, doppioni);
	Pagina_principale(&impostazioni_partita);
    return 0;
}
