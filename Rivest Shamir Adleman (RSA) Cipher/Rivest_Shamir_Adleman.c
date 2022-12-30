#define RSACipher
#ifndef RSACipher

#include "../common.c"

/*
 * Rivest Shamir Adleman (RSA) Cipher program by
 * @author Jan Michael Garot/Heischichou (https://github.com/heischichou)
 * @brief The RSA Cipher formula for encrypting uppercase letters is 
		E(k) = de(mod N) == 1
		
		Where
		  k is the current letter to encrypt
		  d is the chosen decryption key
		  e is the chosen encryption key
		  N is the modulo of prime numbers p and q
*/

typedef struct {
	char* text;
	int64 modulus;
	int64 public_key;
	int64 private_key;
} RSA_Sig;

// Check if the given number is prime
int isPrime(int n) {
	int x;

	for (x = 2; x < n; x++) {
		if (n % x == 0) {
			return 0;
		}
	}

	return 1;
}

// Get totient of two prime numbers
int64 getTotient(int64 p, int64 q) {
	return (p - 1) * (q - 1);
}

// Get exponent value of a number
int64 power(int64 base, int64 exp, int64 mod){
	int x;
 	int64 result = 1;
 	
 	for(x = 0; x < exp; x++){
 		result = (result * base) % mod;
 	}
 	
 	return result;
}

// Get alphabet index of the character provided
char getAlphabetIndex(char c){
	c-= (isupper(c)) ? 'A' : 'a';
	return c + 1;
}

// Print the RSA Signature for Testing
void printSignature(RSA_Sig signature){
	printf("RSA Signature Text\n%s\n\nModulus: %lld\nEncryption Key: %lld\nDecryption Key: %lld\n\n", 
		signature.text, signature.modulus, signature.public_key, signature.private_key);
}

// RSA Encryption
RSA_Sig* encrypt(char *plaintext){
	int64 e, // encryption key
		d, // decryption key
		n = 2 * 13, // modulus
		totient = getTotient(2, 13), // totient
		x, length = strlen(plaintext);
	
	RSA_Sig *signature = NULL;

	// Generate Encryption Key
	for(e = 2; e < totient; e++){
		if(isPrime(e) && n % e != 0 && totient % e != 0){
			break;
		}
	}

	// Generate Decryption Key
	for(d = e + 1; (d * e) % totient != 1; d++){}

	// Initialize and set RSA structure
	signature = (RSA_Sig*) calloc(1, sizeof(RSA_Sig));
	signature->text = (char*) calloc(length + 1, sizeof(char));
	signature->modulus = n;
	signature->public_key = e;
	signature->private_key = d;

	puts("\nCiphertext");
	for(x = 0; x < length; x++){
		if(isalpha(plaintext[x])){
			signature->text[x] = (int64) (power(getAlphabetIndex(plaintext[x]), e, n)) - 1;
			printf("%lld ", signature->text[x] + 1);
			signature->text[x] += isupper(plaintext[x]) ? 'A' : 'a';
		} else {
			signature->text[x] = plaintext[x];
		}
	}
	
	puts("");
	
	return signature;
}

// RSA Decryption
RSA_Sig* decrypt(char *encrypted_text, int64 d, int64 mod){
	int64 e, // encryption key
		x, length = strlen(encrypted_text);
	
	RSA_Sig *signature = NULL;

	// Initialize and set RSA structure
	signature = (RSA_Sig*) calloc(1, sizeof(RSA_Sig));
	signature->text = (char*) calloc(length + 1, sizeof(char));
	signature->modulus = mod;

	// Decrypt message
	puts("\nPlaintext");
	for(x = 0; x < length; x++){
		if(isalpha(encrypted_text[x])){
			signature->text[x] = (power(getAlphabetIndex(encrypted_text[x]), d, mod)) - 1;
			printf("%lld ", signature->text[x] + 1);
			signature->text[x] += isupper(encrypted_text[x]) ? 'A' : 'a';
		} else {
			signature->text[x] = encrypted_text[x];
		}
	}

	puts("");

	return signature;
}

#endif
