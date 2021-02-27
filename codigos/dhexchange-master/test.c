#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include "dhexchange.h"

/*--------------------------------------------------------------------------*/
static void
_print_key(const char* name, const DH_KEY key) {
	int i;

	printf("%s=\t", name);
	for (i = DH_KEY_LENGTH-1; i>=0; i--) {
		printf("%02x", key[i]);
	}
	printf("\n");
}

/*--------------------------------------------------------------------------*/
int 
main(int argc, char* argv[])
{
	DH_KEY alice_private, bob_private;
	DH_KEY alice_public, bob_public;
	DH_KEY alice_secret, bob_secret;

	time_t seed;
	time(&seed);
	srand((unsigned int)seed);

	/*generamos llave privada y publica  para Alice  */
	DH_generate_key_pair(alice_public, alice_private);

	/*generamos llave privada y publica Bob  */
	DH_generate_key_pair(bob_public, bob_private);

	/*Bob envia su clave publica a Alice, Alice genera la llave privada*/
	DH_generate_key_secret(alice_secret, alice_private, bob_public);

	/*Alice envia su clave publica aBob, Bob genera la llave privada */
	DH_generate_key_secret(bob_secret, bob_private, alice_public);

	_print_key("alice_kprivada", alice_private);
	_print_key("alice_kpublica", alice_public);
	_print_key("bob_kprivada", bob_private);
	_print_key("bob_kpublica", bob_public);
	_print_key("alice_textocifrado", alice_secret);
	_print_key("bob_textocifrado", bob_secret);

	if (memcmp(alice_secret, bob_secret, DH_KEY_LENGTH) != 0) {
		printf("ERROR!\n");
		return 1;
	}

	return 0;
}