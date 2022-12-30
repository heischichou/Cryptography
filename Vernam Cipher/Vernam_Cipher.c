#define vernamCipher
#ifndef vernamCipher

#include "../common.c"

/*
 * Vernam Cipher program by
 * @author Jan Michael Garot/Heischichou (https://github.com/heischichou)
*/

// helper functions
char* gen_key(char plaintext[]){
	int x, length = strlen(plaintext);
	char *key = (char*) calloc(length + 1, sizeof(char));
	
	srand(time(NULL));
	for(x = 0; x < length; x++){
		if(isalpha(plaintext[x])){
			key[x] = (isupper(plaintext[x])) ? (rand() % 26) + 'A' : (rand() % 26) + 'a';
		} else {
			key[x] = plaintext[x];
		}
	}
	
	return key;
}

void print_matrix(int rows, int cols, char matrix[rows][cols]){
	int x, y;
	
	for(x = 0; x < rows; x++){
		for(y = 0; y < cols; y++){
			printf("%-2c ", matrix[x][y]);
		}
		
		printf("\n");
	}
}

/* Encrypt and Decrypt
   The Vernam Cipher is a symmetrical cipher that uses the same OTP key
   for both encryption and decryption, thus the same function is used.
*/
char* vernamCipher(char *plaintext, char *key){
    int x, length = strlen(plaintext) - 1;
    char *encrypted_text = (char*) calloc(length + 1, sizeof(char));
    
    for(x = 0; x < length; x++){
    	encrypted_text[x] = (isupper(plaintext[x])) ?
			((plaintext[x] - 'A') ^ (key[x] - 'A')) + 'A' :
			((plaintext[x] - 'a') ^ (key[x] - 'a')) + 'a' ;
	}
	
	printf("\nOne-time Pad:\n");
	for(x = 0; x < length; x++){
    	printf("%d ", key[x]);
	}
	
	puts("");

    return encrypted_text;
}

#endif
