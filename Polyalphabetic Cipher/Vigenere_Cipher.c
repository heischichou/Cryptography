#define vigenereCipher
#ifndef vigenereCipher

#include "../common.c"

/*
 * Vigenere Cipher program by
 * @author Jan Michael Garot/Heischichou (https://github.com/heischichou)
*/

// generates the padded key based on plaintext length
char* padKey(char *plaintext, char *key){
	int x, y, length = strlen(plaintext), key_length = strlen(key);
	char *padded_key = (char*) calloc(length + 1, sizeof(char));
	
	for(x = 0, y = 0; x < length; x++){
        // resets the key counter once it meets the key length
		if(y == key_length){
			y = 0;
		}
		
        // check if the current character is a letter
		if(isalpha(plaintext[x])){
            /* adjust the case of the padded key letter based on the
                casing of the plaintext letter
            */
			padded_key[x] = isupper(plaintext[x]) ? 
				toupper(key[y++]) : 
				tolower(key[y++]);
		} else {
			padded_key[x] = plaintext[x];
		}
	}
	
	return padded_key;
}

// encrypts the plaintext with the padded key
char* encrypt(char *plaintext, char *key){
    int i, length = strlen(plaintext);
    char *encrypted_text = (char*) calloc(length + 1, sizeof(char));

    for(i = 0; i < length; i++){
        // check if the current character is a letter
        if(isalpha(plaintext[i])){
            // check if letter is uppercase
            encrypted_text[i] = (isupper(plaintext[i])) ? 
                (((plaintext[i] - 'A') + (key[i] - 'A')) % 26) + 'A' : 
                (((plaintext[i] - 'a') + (key[i] - 'a')) % 26) + 'a';
        } else {
            encrypted_text[i] = plaintext[i];
        }
    }

    return encrypted_text;
}

// decrypts the plaintext with the padded key
char* decrypt(char *encrypted_text, char *key){
    int i, length = strlen(encrypted_text);
    char *decrypted_text = (char*) calloc(length + 1, sizeof(char));

    for(i = 0; i < length; i++){
        // check if the current character is a letter
        if(isalpha(encrypted_text[i])){
            // check if letter is uppercase
            decrypted_text[i] = (isupper(encrypted_text[i])) ? 
                ((((((encrypted_text[i] - 'A') + 26) - (key[i] - 'A')) % 26) + 26) % 26) + 'A' :
                ((((((encrypted_text[i] - 'a') + 26) - (key[i] - 'a')) % 26) + 26) % 26) + 'a';
        } else {
            decrypted_text[i] = encrypted_text[i];
        }
    }
    
    return decrypted_text;
}

#endif
