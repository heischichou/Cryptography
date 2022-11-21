#define transpositonCipher
#ifndef transpositonCipher

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Columnar Transposition Cipher program by
 * @author Jan Michael Garot/Heischichou (https://github.com/heischichou)
*/

// Returns the number of rows for the encryption matrix
int nrows(char text[], char key[]){
	int length = strlen(text), key_length = strlen(key);
    return (length % key_length == 0) ? (length / key_length) + 1: (length / key_length) + 2;
}

// Initializes the array of encryption key headers
void initVisited(int visited[], int key_length){
    int x;
    
    for(x = 0; x < key_length; x++){
        visited[x] = 0;
    }
}

void print_matrix(int rows, int cols, char matrix[rows][cols]){
    int x, y;

    printf("\n");
    for(x = 0; x < rows; x++){
        for(y = 0; y < key_length && matrix[x][y] != '\0'; y++){
            printf("%c ", matrix[x][y]);
        }
        printf("\n");
    }
}

// Encrypts the text using the key
char* encrypt(char* plaintext, char *key) {
    int length = strlen(plaintext),
		key_length = strlen(key),
		rows = nrows(plaintext, key),
		visited[key_length],
		x, y, z, lowest;

    char matrix[rows][key_length + 1],
		*encrypted_text = (char*) calloc(strlen(plaintext) + 1, sizeof(char));
	
    // initialize the matrix
    for(y = 0; y < key_length; y++){
      for(x = 0; x < rows; x++){
      	matrix[x][y] = (x == 0) ? key[y] : '\0';
	  }
    }

    // initialize the visited array
    initVisited(visited, key_length);
    
    /* insert max ASCII value to compare against later
    	in the columnar sequencing
    */
    matrix[0][y] = '~';
    
    // insert the plaintext letters into the matrix
    for(x = 1, z = 0; x < rows && plaintext[z] != '\0'; x++){
        for(y = 0; y < key_length; y++){
            matrix[x][y] = plaintext[z++];
        }
    }
    
    /* determine the alphabetic sequence of the cipher key
		letters and start inserting the columnar sequences
		into the encrypted text sequence container
	*/
    length = 0;
	for(z = 0; z < key_length; z++){
		lowest = key_length;
		
    	for(x = 0; x < key_length; x++){
    		if(matrix[0][lowest] > matrix[0][x]){
    			if(visited[x] == 0){
    				lowest = x;
				}
			}
		}
      
	    if(visited[lowest] == 0){
            visited[lowest] = 1;
            
            for(y = 1, x = 0; y < rows && matrix[y][lowest] != '\0'; y++, x++){
                encrypted_text[length++] = matrix[y][lowest];
            }
        }
    }

    // print the matrix for testing
    print_matrix(rows, key_length, matrix);
    
    return encrypted_text;
}

// Decrypts the ciphertext using the key
char* decrypt(char* encrypted_text, char *key) {
    int length = strlen(encrypted_text),
		key_length = strlen(key),
		rows = nrows(encrypted_text, key),
		visited[key_length],
		v, w = 0, x, y, z, lowest;

    char temp[rows][key_length + 1],
		matrix[rows][key_length + 1],
		*decrypted_text = (char*) calloc(strlen(encrypted_text) + 1, sizeof(char));
	
    // initialize the matrix
    for(y = 0; y < key_length; y++){
    	for(x = 0; x < rows; x++){
      		matrix[x][y] = (x == 0) ? key[y] : '\0';
      		temp[x][y] = '\0';
		}
    }
    
    // initialize the visited array
    initVisited(visited, key_length);
    
    /* insert max ASCII value to compare against later
    	in the columnar sequencing
    */
    matrix[0][y] = '~';
    
    // insert the plaintext letters into the matrix
    for(x = 1, z = 0; x < rows; x++){
        for(y = 0; y < key_length && z < length; y++){
            matrix[x][y] = encrypted_text[z++];
        }
    }
    
    /* determine the alphabetic sequence of the cipher key
		letters and start inserting the columnar sequences
		into the encrypted text sequence container
	*/
	for(z = 0, y = 0; z < key_length; z++){
		lowest = key_length;
		
    	for(x = 0; x < key_length; x++){
    		if(matrix[0][lowest] > matrix[0][x]){
    			if(visited[x] == 0){
    				lowest = x;
				}
			}
		}
      
	    if(visited[lowest] == 0){
            visited[lowest] = 1;
            
			temp[0][y++] = matrix[0][lowest];
        }
    }
    
    // reset the visited array
    initVisited(visited, key_length);
    
    /* insert all the encrypted key letters into the
		temporary matrix based on columnar sequence
	*/
    for(z = 0, y = 0; z < key_length; z++){
        lowest = key_length;
        
        for(x = 0; x < key_length; x++){
            if(matrix[0][lowest] > matrix[0][x]){
                if(visited[x] == 0){
                    lowest = x;
                }
            }
        }
      
        if(visited[lowest] == 0){
            visited[lowest] = 1;
            
            // Get number of characters in a columnar sequence
            for(x = 1; x < rows && matrix[x][lowest] != '\0'; x++){}

			// Find position of key letter of columnar sequence in the temp array
            for(v = 0; v < key_length && temp[0][v] != matrix[0][lowest]; v++){}
            
            // Insert letters in columnar sequence into the temp array column
            for(y = 1; y < x; y++){
              temp[y][v] = encrypted_text[w++];
            }
        }
    }
	
	// print the temporary matrix
	print_matrix(rows, key_length, temp);
    
	// reset the visited array
    initVisited(visited, key_length);
	
	/* inserting all the columnar sequences into the
		matrix in proper alphabetical order
	*/
	for(z = 0, y = 0; z < key_length; z++){
		lowest = key_length;
		
    	for(x = 0; x < key_length; x++){
    		if(matrix[0][lowest] > matrix[0][x]){
    			if(visited[x] == 0){
    			lowest = x;
				}
			}
		}
      
	  	if(visited[lowest] == 0){
			visited[lowest] = 1;
            
            for(y = 1, x = 0; y < rows && matrix[y][lowest] != '\0'; y++, x++){
                matrix[y][lowest] = temp[y][z];
            }
        }
    }

    // print the matrix for testing
    print_matrix(rows, key_length, matrix);
    
     // reconstruct the plaintext
    for(x = 1, z = 0; x < rows; x++){
        for(y = 0; y < key_length && matrix[x][y] != '\0'; y++){
        	decrypted_text[z++] = matrix[x][y];
        }
    }
    
    return decrypted_text;
}

#endif