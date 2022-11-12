#define atbashCipher
#ifndef atbashCipher

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Atbash Cipher program by
 * @author Jan Michael Garot/Heischichou (https://github.com/heischichou)
*/

// The decryption method for the Atbash Cipher is the same as the encryption method, thus, we can use the same method for both.
char* atbashCipher(char* plaintext) {
    char* cipher_text = (char*) malloc(strlen(plaintext) + sizeof(char));
    int i;

    for(i = 0; plaintext[i] != '\0'; i++){
        if(isalpha(plaintext[i])){
            /* check if the letter is uppercase, if true, then subtract 65
               from its ASCII value, else, subtract 97 from its ASCII value
            */
            cipher_text[i] = (isupper(plaintext[i])) ? 
				(char )'Z' - (plaintext[i] - 'A') : 
				(char) 'z' - (plaintext[i] - 'a');
        } else {
            cipher_text[i] = plaintext[i];
        }
    }

    cipher_text[i] = '\0';
    return cipher_text;
}

#endif