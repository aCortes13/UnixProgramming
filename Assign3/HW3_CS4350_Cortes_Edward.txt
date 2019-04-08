/**************************************************
 * Name: Edward Anthony Cortes
 * Serial: 12
 * Assign Number: 3
 * Due: 3 / 27 / 2019
 **************************************************/

#include<stdio.h>

/*
 * Creating helper functions
 */

char ascii[94];
int upper = 0;
int lower = 0;
int digit = 0;
int symbol = 0;
int chars = 0;

// Locates the index of a character on the "new" ascii table 
int findIndexAscii(char c) {
  for (int x = 0; x < 94; x++) {
    if (c == ascii[x]) return x;
  }
  return -1;
}

// Clears out the array
void cryptoFlush(char arr[2][200]) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 200; j++) {
      arr[i][j] = 0;
    }
  }
}

// Flush stdin
//  When using scan() the characters and \n characters are left on the buffer
//  Use this to get rid of those characters and avoid unwanted input 
void stdinFlush() {
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

// return true if char is a digit
_Bool evalisdigit(char input) {
  if (input < 58  && input > 47) return 1;
  return 0;
}

// return true if char is upper case
_Bool evalisupper(char input) {
  if (input < 91  && input > 64) return 1;
  return 0;
}

// return true is char is lower case
_Bool evalislower(char input) {
  if (input < 123  && input > 96) return 1;
  return 0;
}

// Return true if char is not upper, lower, or digit
_Bool evalissymbol(char input) {
  if (!evalisdigit(input) && !evalisupper(input) && !evalislower(input)) {
    return 1;
  }
  return 0;
}

// generates the ascii array according to gholoom's requirements
void generateAscii(char ascii[]) {
  char c = 'A';
  int index = 0;

  while (evalisupper(c)) {   
    ascii[index] = c++;
    index++;
  } 
  c = 'a';

  while (evalislower(c)) {
    ascii[index] = c++;
    index++;
  }
  c = '0';

  while (evalisdigit(c)) {
    ascii[index] = c++;
    index++;
  }
  c = '!';

  while (c < 48) {
    ascii[index] = c++;
    index++;
  }
  c = ':';

  while (c < 65) {
    ascii[index] = c++;
    index++;
  }
  
  c = '[';

  while (c < 97) {
    ascii[index] = c++;
    index++;
  }

  c = '{';

  while (c < 127) {
    ascii[index] = c++;
    index++;
  }
}

// input validation
//    returns -1 if no possible choice for input
//    used to verify a user's menu choices
int validate(char message[]) {
  const char encrypt[] = "encrypt";
  const char decrypt[] = "decrypt";
  const char exit[] = "exit";
  int x = 0;
 
  _Bool enc = 1;
  _Bool dec = 1;
  _Bool xit = 1;

  if (evalisupper(message[x])) message[x] += 32;

  while (message[x] != '\n' && x < 4) {
    if (message[x] != encrypt[x]) { 
      enc = 0;
    }
    if (message[x] != decrypt[x]) {
      dec = 0;
    }
    if (message[x] != exit[x]) {
      xit = 0;
    }
    x++;
  }
  if (enc && x > 0) return 1;
  if (dec && x > 0) return 2;
  if (xit && x > 0) return 3;
  return -1;
}

// performs caesear encryption. Return -1 if failed
_Bool encrypt(char crypto[2][200], int key) {
  char c;

  // do caesar encryption
  for (int i = 0; i < chars; i++) {
    char plaintxt = crypto[0][i];
    int plainIndex;
    
    // error thrown if character is not in the created ascii table
    // I.E. NO SPACES ARE ALLOWED IN THE MESSAGE
    if ((plainIndex = findIndexAscii(plaintxt)) == -1) {
      puts("ERROR finding index");
      cryptoFlush(crypto);
      return 0;
    }
    
    // Don't encrypt symbols
    if (evalissymbol(plaintxt)) {
      crypto[1][i] = ascii[plainIndex];
      continue;
    }
    
    // Make sure we dont exceed array bounds
    if ((plainIndex + key) > 93) {
      plainIndex -= 94;
    }

    // Store encrypted text
    crypto[1][i] = ascii[plainIndex + key];
  }
  return 1;
}

// perform caesar decryption. Return -1 if fail
_Bool decrypt(char crypto[2][200], int key) {
  char c;

  // perform caesar decryption
  for (int i = 0; i < chars; i++) {
    char cipherText = crypto[0][i];
    int cipherIndex;

    // error thrown if character is not in the created ascii table
    // I.E. NO SPACES ARE ALLOWED IN THE MESSAGE
    if ((cipherIndex = findIndexAscii(cipherText)) == -1) {
      puts("Error finding index\n");
      cryptoFlush(crypto);
      return 0;
    }

    // Dont encrypt symbols 
    if (evalissymbol(cipherText)) {
      crypto[1][i] = ascii[cipherIndex];
      continue;
    }

    // Make sure we dont exceed array bounds
    if ((cipherIndex - key) < 0) {
      cipherIndex += 94;
    }
    // Store decrypted text 
    crypto[1][i] = ascii[cipherIndex - key];
  }
  return 1;
}

int main() {
  char c, response[20], key[20], crypto[2][200];
  generateAscii(ascii);

  puts("Welcome to cryptography\n");
  
  while (1) {
    int i = 0;

    puts("What would you like to do to a message? (encrypt, decrypt, exit)");
    printf("Enter your choice: ");

    // Read user choice char by char and change to lowercase 
    while ((c = getchar()) != '\n') {
      if (evalisupper(c)) {
        c += 32; // this is tolower()
      }
      response[i] = c;
      i++;
    }

    // Verify that user's choice is valid 
    int choice = validate(response);

    if (choice == -1) {
      puts("Invalid choice, try again.\n");
      continue;
    }

    // Encrypt chosen
    if (choice == 1) {
      int key = -1;
      int index = 0;

      puts("\nEnter your message: ");

      // Perform analysys of user message while reading message
      while ((c = getchar()) != '\n') {
        if (evalisdigit(c)) ++digit;
        else if (evalisupper(c)) ++upper;
        else if (evalislower(c)) ++lower;
        else ++symbol;
        ++chars;
        crypto[0][index] = c;
        index++;
      }

      crypto[0][index] = '\0';

      if (crypto[0][0] == '\0') { // If message empty
        puts("\nInvalid Message\n");
        continue;
      }

      puts("\nEnter your Key (1-93)");
      scanf("%d", &key);
      stdinFlush();

      // Check key values 
      if (key < 1 || key > 93) {
        puts("\nInvalid key\n");
        return 0;
      }

      if (!encrypt(crypto, key)) { continue; }

      // Print statistics 
      printf("\nNumber of Capital Letters: %d\n", upper);
      printf("Number of Lower Case Letters: %d\n", lower);
      printf("Number of digits: %d\n", digit);
      printf("Number of symbols: %d\n", symbol);
      printf("Number of characters in the message: %d\n", chars);
      printf("converting letters: ");

      index = 0;
      while ((c = crypto[0][index]) != '\0') {
        if (evalisupper(c))
          printf("%c", c + 32);
        else if (evalislower(c))
          printf("%c", c - 32);
        else 
          printf("%c", c);
        index++;
      } 
      printf("\n");

      printf("\nYour encrypted message is: ");
      index = 0;
      while ((c = crypto[1][index]) != '\0') {
        printf("%c", c);
        index++;
      } 
      printf("\n\n");

      printf("Concatenation of original and encrypted text: ");
      index = 0;
      while ((c = crypto[0][index]) != '\0') {
        printf("%c", c);
        index++;
      } 
      index = 0;
      while ((c = crypto[1][index]) != '\0') {
        printf("%c", c);
        index++;
      } 
      printf("\n\n");

      cryptoFlush(crypto);
    }

    // Decrypt chosen 
    if (choice == 2) {
      int key = -1;

      puts("\nEnter your Key (1-93)");
      scanf("%d", &key);
      stdinFlush();
      if (key < 1 || key > 93) {
        puts("\nInvalid key\n");
        continue;
      }

      puts("\nEnter your message: ");
      
      // get char information while reading in chars 
      int index = 0;
      while ((c = getchar()) != '\n') {
        if (evalisdigit(c)) ++digit;
        else if (evalisupper(c)) ++upper;
        else if (evalislower(c)) ++lower;
        else ++symbol;
        ++chars;
        crypto[0][index] = c;
        index++;
      }

      crypto[0][index] = '\0';

      // if message empty
      if (crypto[0][0] == '\0') {
        puts("\nInvalid Message\n");
        continue;
      }

      if (!decrypt(crypto, key)) { continue; }

      // show statistics
      printf("\nNumber of Capital Letters: %d\n", upper);
      printf("Number of Lower Case Letters: %d\n", lower);
      printf("Number of digits: %d\n", digit);
      printf("Number of symbols: %d\n", symbol);
      printf("Number of characters in the message: %d\n", chars);
      printf("converting letters: ");

      index = 0;
      while ((c = crypto[0][index]) != '\0') {
        if (evalisupper(c))
          printf("%c", c + 32);
        else if (evalislower(c))
          printf("%c", c - 32);
        else 
          printf("%c", c);
        index++;
      }

      printf("\n");

      printf("\nYour decrypted message is: ");
      index = 0;
      while ((c = crypto[1][index]) != '\0') {
        printf("%c", c);
        index++;
      } 
      printf("\n\n");

      printf("Concatenation of original and encrypted text: ");
      index = 0;
      while ((c = crypto[0][index]) != '\0') {
        printf("%c", c);
        index++;
      } 
      index = 0;
      while ((c = crypto[1][index]) != '\0') {
        printf("%c", c);
        index++;
      } 
      printf("\n\n");
      cryptoFlush(crypto);
    }

    // exit
    if (choice == 3) { break; }

  }
  puts("\nAnthony Security Systems \n3-27-2019\n");
}
