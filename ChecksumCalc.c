/*=============================================================================
| Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Language: c
|
| gcc -o pa02 pa02.c
|
| or c -> ./pa02 inputFile.txt 8

| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
+=============================================================================*/



// liabaries 
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

unsigned long int bit_calc_ei(char *bit_size); // ei = eight (8)
unsigned long int bit_calc_st(char *bit_size); // st = sixteen(16)
unsigned long int bit_calc_tt(char *bit_size); // tt = thirty-two(32)
void charlim(char *conv); // sets a limit on the char to 80

int main(int argc, char **argv){
  
  // name of file variable
  FILE *cheksumfile;
  
  // if nothing is entered in the command line or just run it 
  if (argc != 3){
    fprintf(stderr, "Please run the program as the following format (./pa02 inputFile.txt 8)\n");
    return -1;
  }
  
  // char variables 
  char *bit_size; // user iuput 
  char x = 'x'; 

  // int variables 
  int i = 0;
  int cheksum_bit = 0;
  
  // long signed int variables, used to reset to 0 
  unsigned long int reset_eBit = 0;
  unsigned long int reset_stBit = 0;
  unsigned long int reset_ttBit = 0;

  cheksum_bit = atoi(argv[2]);

  // if user enters invalid file 
    if (!(cheksumfile = fopen(argv[1],"r"))){
      fprintf(stderr, " file not opening \"%s\"\n", argv[1]);
      return -1;
    }

  // 1024 character limit  
  bit_size = malloc(sizeof(char) * 1024);

  // Reads file 
  while (fscanf(cheksumfile, "%c", &x) != EOF && i < 1024){
    bit_size[i] = x;
    i++;
  }
  
  bit_size[i] = '\0';
  
  // Closes file
  fclose(cheksumfile);
  
  // for checksum entered 8
  if (cheksum_bit == 8){

    reset_eBit = bit_calc_ei(bit_size);
    charlim(bit_size);
    
    printf("\n");

    printf("%2d bit checksum is %8lx for all %4d chars\n", cheksum_bit, reset_eBit & 0xff, (int)strlen(bit_size));
  }
  // bitsize input = 16 
  else if (cheksum_bit == 16){ 
    // Padding 
    if (strlen(bit_size) % 2){

      strcat(bit_size,"X");

    }
   // bitsize and *conv are the similar but *conv, conv = convertion 
    charlim(bit_size);
    printf("\n");

    reset_stBit = bit_calc_st(bit_size);

    printf("%2d bit checksum is %8lx for all %4d chars\n", cheksum_bit, reset_stBit & 0xffff, (int)strlen(bit_size));
  }
  // for when user intput 32 in command line
  else if (cheksum_bit == 32){ 
    // Padding
    while (strlen(bit_size) % 4){

      strcat(bit_size,"X");

    }
    // checks user input for the correct but size and runs it to convertion 
    charlim (bit_size);
    printf("\n");
    reset_ttBit = bit_calc_tt(bit_size);

    printf("%2d bit checksum is %8lx for all %4d chars\n", cheksum_bit, reset_ttBit & 0xffffffff, (int)strlen(bit_size));
  }

  else{
        fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
        return -1;
      }
  
  return 0;
  
}



// check sum for 32bit  
unsigned long int bit_calc_tt(char *bit_size){

  unsigned long int reset_ttBit = 0;

  for (int i = 0; i < strlen(bit_size);){

    reset_ttBit += bit_size[i] << 24;
    reset_ttBit += (bit_size[i + 1]) << 16;
    reset_ttBit += (bit_size[i + 2]) << 8;
    reset_ttBit += (bit_size[i + 3]);
    i+=4;

  }
  
  return reset_ttBit;
}

// check sum for 16bit  
unsigned long int bit_calc_st(char *bit_size){

  int reset_stBit = 0;

  for (int i = 0; i < strlen(bit_size);){

    reset_stBit += bit_size[i] << 8;
    reset_stBit += (bit_size[i + 1]);
    i+=2;

  }

  return reset_stBit;
}

// check sum for 8bit  
unsigned long int bit_calc_ei(char *bit_size){

  int cheksum = 0;

  for (int i = 0; i < strlen(bit_size); i++){

    cheksum += bit_size[i];

  }

  return cheksum;

}

// character limit 
void charlim(char *conv){

// amount of text divided in to lines 
  for (int i = 0; i < strlen(conv); i++){
    // divides number lines to have 80 characters a line 
    if (i % 80 == 0){ 

      printf("\n");// prints new line 

    }

    printf("%c",conv[i]);

  }
}
