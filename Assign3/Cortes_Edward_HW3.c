/**************************************************
 * Name: Edward Anthony Cortes
 * Serial: 12
 * Assign Number: 3
 * Due: 3 / 27 / 2019
 **************************************************/

#include<stdio.h>

/*
 * Create helper functions
 */

char ascii[94];
_Bool run = 1;


// Locate index of a char on the "new" ascii table 
int findIndexAscii(char c) {
  for (int x = 0; x < 94; x++) {
    if (c == ascii[x]) return x;
  }
  return -1;
}

// Flush the crypto array with \0 to clear after use
void cryptoFlush(char arr[2][200]) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 200; j++) {
      arr[i][j] = 0;
    }
  }
}

// Flush stdin
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

// generates the new ascii table according to gholoom's requirements
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

// menu input validation, returns -1 if no possible choice for input
int validate(char message[]) {
  const char encrypt[] = "encrypt";
  const char decrypt[] = "decrypt";
  const char exit[] = "exit";
  int x = 0;
 
  _Bool enc = 1;
  _Bool dec = 1;
  _Bool xit = 1;
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
_Bool encrypt(char crypto[2][200]) {
  int upper = 0;
  int lower = 0;
  int digit = 0;
  int symbol = 0;
  int chars = 0;
  int key = -1;
  char c;

  puts("\nEnter your message: ");

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

  if (crypto[0][0] == '\0') {
    puts("\nInvalid Message\n");
    return 0;
  }

  puts("\nEnter your Key (1-93)");
  scanf("%d", &key);
  stdinFlush();

  if (key < 1 || key > 93) {
    puts("\nInvalid key\n");
    return 0;
  }

  // do caesar encryption
  for (int i = 0; i < chars; i++) {
    char plaintxt = crypto[0][i];
    int plainIndex;

    if ((plainIndex = findIndexAscii(plaintxt)) == -1) {
      puts("ERROR finding index");
      cryptoFlush(crypto);
      return 0;
    }

    if ((plainIndex + key) > 93) {
      plainIndex -= 94;
    }
    crypto[1][i] = ascii[plainIndex + key];
  }

  printf("Number of Capital Letters: %d\n", upper);
  printf("Number of Lower Case Letters: %d\n", lower);
  printf("Number of digits: %d\n", digit);
  printf("Number of symbols: %d\n", symbol);
  printf("Number of characters in the message: %d\n", chars);
  printf("converting letters: ");

  index = 0;
  while ((c = crypto[0][index]) != '\0') {
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
  return 1;
}

// perform caesar decryption. Return -1 if fail
_Bool decrypt(char crypto[2][200]) {
  int upper = 0;
  int lower = 0;
  int digit = 0;
  int symbol = 0;
  int chars = 0;
  int key = -1;
  char c;

  puts("\nEnter your Key (1-93)");
  scanf("%d", &key);
  stdinFlush();
  if (key < 1 || key > 93) {
    puts("\nInvalid key\n");
    return 0;
  }

  puts("\nEnter your message: ");

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

  if (crypto[0][0] == '\0') {
    puts("\nInvalid Message\n");
    return 0;
  }
  // perform caesar decryption
  for (int i = 0; i < chars; i++) {
    char cipherText = crypto[0][i];
    int cipherIndex;

    if ((cipherIndex = findIndexAscii(cipherText)) == -1) {
      puts("Error finding index\n");
      cryptoFlush(crypto);
      return 0;
    }

    if ((cipherIndex - key) < 0) {
      cipherIndex += 94;
    }
    crypto[1][i] = ascii[cipherIndex - key];
  }

  printf("Number of Capital Letters: %d\n", upper);
  printf("Number of Lower Case Letters: %d\n", lower);
  printf("Number of digits: %d\n", digit);
  printf("Number of symbols: %d\n", symbol);
  printf("Number of characters in the message: %d\n", chars);
  printf("converting letters: ");

  index = 0;
  while ((c = crypto[0][index]) != '\0') {
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
  return 1;
}

int main() {
  char c, response[20], crypto[2][200], key[20];
  generateAscii(ascii);

  puts("Welcome to cryptography\n");
  
  while (run) {
     int i = 0;

    puts("What would you like to do to a message? (encrypt, decrypt, exit)");
    printf("Enter your choice: ");

    while ((c = getchar()) != '\n') {
      if (evalisupper(c)) {
        c += 32; // tolower()
      }
      response[i] = c;
      i++;
    }

    int choice = validate(response);
    if (choice == -1) {
      puts("Invalid choice, try again.\n");
      continue;
    }

    if (choice == 1) {
      if (!encrypt(crypto)) { continue; }
    }

    if (choice == 2) {
      if (!decrypt(crypto)) { continue; }
    }

    if (choice == 3) { break; }

  }
  puts("\nAnthony Security Systems \n3-27-2019\n");
}
