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

char* encrypt(char* text, int shift_n_times) {
    char* encrypted_text = (char*) malloc(strlen(text) + sizeof(char));
    int i;

    for(i = 0; text[i] != '\0'; i++){
        if(isalpha(text[i])){
            // check if the letter is uppercase, if true, then add 65 to its ASCII value after the modulo operation, else, add 97 to its ASCII value
            encrypted_text[i] = (isupper(text[i])) ? (((((text[i] - 'A') + shift_n_times) % 26) + 26) % 26) + 'A' : (((((text[i] - 'a') + shift_n_times) % 26) + 26) % 26) + 'a';
        } else {
            encrypted_text[i] = text[i];
        }
    }

    encrypted_text[i] = '\0';
    return encrypted_text;
}

char* decrypt(char* text, int shift_n_times) {
    char* decrypted_text = (char*) malloc(strlen(text) + sizeof(char));
    int i = 0;

    for(i = 0; text[i] != '\0'; i++){
        if(isalpha(text[i])){
            // check if the letter is uppercase, if true, then subtract 65 from its ASCII value after the modulo operation, else, subtract 97 from its ASCII value
            decrypted_text[i] = (isupper(text[i])) ? (((((text[i] - 'A') - shift_n_times) % 26) + 26) % 26) + 'A' : (((((text[i] - 'a') - shift_n_times) % 26) + 26) % 26) + 'a';
        } else {
            decrypted_text[i] = text[i];
        }
    }

    decrypted_text[i] = '\0';
    return decrypted_text;
}

#endif