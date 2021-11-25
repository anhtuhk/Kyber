#include "../ref/kem.h"
#include "../ref/params.h"
#include "stdio.h"
#include "stdint.h"

int main() {
	int i;
	uint8_t pk[KYBER_PUBLICKEYBYTES];
	uint8_t sk[KYBER_SECRETKEYBYTES];
	printf("-------------kyber512--------------\n");
	
	crypto_kem_keypair(pk, sk);

	FILE *pk_file = fopen("../report/public_key.txt","w");
	fprintf(pk_file,"Public_key:\n");
	for (i=0; i< KYBER_PUBLICKEYBYTES; i++) {
		fprintf(pk_file,"%02X",pk[i]);
	}
	fclose(pk_file);

	FILE *sk_file = fopen("../report/secret_key.txt","w");
	fprintf(sk_file,"Secret_key:\n");
	for (i=0; i< KYBER_SECRETKEYBYTES; i++) {
		fprintf(sk_file,"%02X", sk[i]);
	}
	fclose(sk_file);

	printf("Done.\n");
}	
	
