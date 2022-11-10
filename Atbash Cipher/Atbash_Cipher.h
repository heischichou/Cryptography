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
char* atbashCipher(char* text) {
    char* cipher_text = (char*) malloc(strlen(text) + sizeof(char));
    int i = 0;

    for(i = 0; text[i] != '\0'; i++){
        if(isalpha(text[i])){
            // check if the letter is uppercase, if true, then subtract 65 from its ASCII value, else, subtract 97 from its ASCII value
            cipher_text[i] = (isupper(text[i])) ? 'Z' - (text[i] - 'A') : 'z' - (text[i] - 'a');
        } else {
            cipher_text[i] = text[i];
        }
    }

    cipher_text[i] = '\0';
    return cipher_text;
}

#endif