#ifndef GENOME_H //use include guards to prevent multiple inclusions of this header file
#define GENOME_H 
#include <stddef.h>
#define MAX_DNA_LENGTH 10000 //defining max length of DNA sequence
#define MAX_NAME_LENGTH 64 //defining max length of DNA sequence name
typedef struct {
    char name[MAX_NAME_LENGTH]; //char array to hold the name of the DNA sequence
    char bases[MAX_DNA_LENGTH]; //char array to hold the DNA bases
    size_t length; // holds length of the DNA sequence
} DNASequence; //holds the name, bases and length of a DNA sequence
//Returns 1 if the sequence is valid, else 0.
int dna_is_valid(const char *sequence); //function to check if the DNA sequence is valid
#endif
