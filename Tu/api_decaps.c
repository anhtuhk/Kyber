#include "../ref/api.h"
#include "../ref/params.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"

int main() {
	int i;
	uint8_t sk[KYBER_SECRETKEYBYTES];
	uint8_t ct[KYBER_CIPHERTEXTBYTES];
	uint8_t ss[KYBER_SSBYTES];
	unsigned int a;
	char buffer[100];
	char hex[2];
	char name[64];

	printf("-------------kyber512--------------\n");
	printf("Decapsulating...\n");

	FILE* fp = fopen("../report/public_key.txt","r");
	if (fp==NULL)
	{
		printf("Catching errors with secret_key.txt\n");
		return(-1);
	}

	while(feof(fp) == 0)
	{ /*read some data, lets process it.*/
		/*extract individual values from the buffer*/
		fgets(buffer, 100, fp);
		sscanf(buffer, "%s", name);
		if (strcmp(name, "Secret_key:") == 0) {
			for (i = 0; i < KYBER_SECRETKEYBYTES; i++) {
				fgets(hex, 3, fp);
				sscanf(hex, "%02X", &a);
				pk[i] = (uint8_t)a;
			}
			break;
		}
	}

	fclose(fp);

	FILE* ct_file_en = fopen("../report/ciphertext_after_encaps.txt","r");
	if (ct_file_en==NULL)
	{
		printf("Catching errors with ciphertext_after_encaps.txt\n");
		return(-1);
	}

	while(feof(ct_file_en) == 0)
	{ /*read some data, lets process it.*/
		/*extract individual values from the buffer*/
		fgets(buffer, 100, ct_file_en);
		sscanf(buffer, "%s", name);
		if (strcmp(name, "Ciphertext:") == 0) {
			for (i = 0; i < KYBER_CIPHERTEXTBYTES; i++) {
				fgets(hex, 3, fp);
				sscanf(hex, "%02X", &a);
				pk[i] = (uint8_t)a;
			}
			break;
		}
	}

	fclose(ct_file_en);

	pqcrystals_kyber512_ref_dec(ss, ct, sk);

	FILE *ct_file_de = fopen("../report/ciphertext_after_decaps.txt","w");
	fprintf(pk_file,"Secret_key:\n");
	for (i=0; i< KYBER_SECRETKEYBYTES; i++) {
		fprintf(ct_file_de,"%02X",sk[i]);
	}
	fprintf(ct_file_de,"\n______________________________________\n\n");
	fprintf(ct_file_de,"Ciphertext:\n");
	for (i = 0; i < KYBER_CIPHERTEXTBYTES; i++){
		fprintf(ct_file_de,"%02X", ct[i]);
	}
	fclose(pk_file_de);

	FILE *shk_file = fopen("../report/shared_key_after_decaps.txt", "w");
	fprintf(shk_file,"Shared_key:\n");
	for (i=0; i< KYBER_SSBYTES; i++) {
		fprintf(shk_file,"%02X", ss[i]);
	}
	fprintf(shk_file,"\n");
	fclose(shk_file);

	printf("Done.\n");
}	
