/*
	Secure key/salt generator
	Written in nano by Zyantos ;)
	zzzyantos made it! (sorry Benjamin)
	special shoutout to Zella, even tho you went ghost on me cx

	Compile the script with this command please:
	~# gcc genKey.c -o zkey -lcrypto
*/

#include <stdio.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include "commandHandler.h"
#include <string.h>

int genKeyPair() {

	int ret = 0;
	EVP_PKEY *pkey = NULL;
	EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

	if (!ctx || EVP_PKEY_keygen_init(ctx) <= 0
		|| EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 4096) <= 0
		|| EVP_PKEY_keygen(ctx, &pkey) <= 0) {

		EVP_PKEY_CTX_free(ctx);
		return -1;

	}

	// Write private key
	FILE *pk_file = fopen("private.pem", "wb");
	if (pk_file == NULL || PEM_write_PrivateKey(pk_file, pkey, NULL, NULL, 0 , NULL, NULL) != 1) {

		EVP_PKEY_free(pkey);
		EVP_PKEY_CTX_free(ctx);
		return -1;
	}
	fclose(pk_file); // Close the private key file :P
	printf("private.pem written\n"); // Communication is key in any relationship <3

	// Write public key
	FILE *pub_key_file = fopen("public.pem", "wb");
	if (pub_key_file == NULL || PEM_write_PUBKEY(pub_key_file, pkey) != 1) {

		EVP_PKEY_free(pkey);
		EVP_PKEY_CTX_free(ctx);
		return -1;
	}
	fclose(pub_key_file); // Close the public key file :)
	printf("public.pem written\n"); // Let the user know it worked :3

	// Remember gotta clean up the mess afterwards ;)
	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(ctx);
	return 0;
}

int secret256() {

	unsigned char key[32]; // 256 bits = 32 bytes

        // Generate 256-bit cryptographically secure random key
        if (RAND_bytes(key, sizeof(key)) != 1) {

                fprintf(stderr, "Error generating random key\n");
                return -1;
        }

        // Print the key
        for (int i = 0; i < sizeof(key); i++) {
                printf("%02x", key[i]);
        }
}

int main(int argc, char *argv[]) {

	int ret = 0; // Might as well ~\(o_o/~

	char *key_type = NULL;
	handle_command(argc, argv, &key_type);

	if (strcmp(key_type, "rsa4096") == 0) {
		ret = 0;
		genKeyPair();
	}
	else if (strcmp(key_type, "secret256") == 0) {
		ret = 0;
		secret256();
		printf("\n");
	} else {
		fprintf(stderr, "Invalid key type.\nSupport keys:\nrsa4096\nsecret256\n");
		ret = -1;
	}

	return ret;

}
