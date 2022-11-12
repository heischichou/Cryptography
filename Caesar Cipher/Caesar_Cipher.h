#define caesarCipher
#ifndef caesarCipher

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Shifting/Caesar Cipher program by
 * @author Jan Michael Garot/Heischichou (https://github.com/heischichou)
*/

char* encrypt(char* plaintext, int shift_n_times) {
    char* encrypted_text = (char*) malloc(strlen(plaintext) + sizeof(char));
    int i;

    for(i = 0; plaintext[i] != '\0'; i++){
    	// check if current character is an alphabet
        if(isalpha(plaintext[i])){
        	// check if the letter is uppercase
            encrypted_text[i] = (isupper(plaintext[i])) ? 
				(char) (((((plaintext[i] - 'A') + shift_n_times) % 26) + 26) % 26) + 'A' : 
				(char) (((((plaintext[i] - 'a') + shift_n_times) % 26) + 26) % 26) + 'a';
        } else {
            encrypted_text[i] = plaintext[i];
        }
    }

    encrypted_text[i] = '\0';
    return encrypted_text;
}

char* decrypt(char* plaintext, int shift_n_times) {
    char* decrypted_text = (char*) malloc(strlen(plaintext) + sizeof(char));
    int i = 0;

    for(i = 0; plaintext[i] != '\0'; i++){
    	// check if current character is an alphabet
        if(isalpha(plaintext[i])){
            // check if the letter is uppercase
            decrypted_text[i] = (isupper(plaintext[i])) ? 
			(char) (((((plaintext[i] - 'A') - shift_n_times) % 26) + 26) % 26) + 'A' : 
			(char) (((((plaintext[i] - 'a') - shift_n_times) % 26) + 26) % 26) + 'a';
        } else {
            decrypted_text[i] = plaintext[i];
        }
    }

    decrypted_text[i] = '\0';
    return decrypted_text;
}

#endif