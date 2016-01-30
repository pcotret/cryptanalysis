/* The MIT License (MIT)
 * Copyright (c) 2016, Pascal Cotret
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Filename: main.c
 * Author: Pascal Cotret <pascal.cotret@protonmail.ch>
 * Description: a first attempt of a frequency analysis tool
 * It does not detect bigrams nor trigrams that helps the cryptanalysis.
 * Therefore, this tool should be efficient only if the input text is long enough
 * and if the letter distribution is similar to the input language reference.
 */

/* Libraries */
#include <stdio.h>
#include <stdlib.h>

/* Constants */
// Size of the default alphabet
#define ALPHA_SIZE 26
// Statistics for the English language (taken from "Understanding Cryptography" by Paar et al.)
const double FREQ_DOWN_EN[ALPHA_SIZE]={0.1270,0.0906,0.0817,0.0751,0.0697,0.0675,0.0633,0.0609,0.0599,0.0425,0.0403,0.0278,0.0276,0.0241,0.0236,0.0223,0.0202,0.0197,0.0193,0.0150,0.0098,0.0077,0.0015,0.0015,0.0010,0.0007};
const char ALPHA_DOWN_EN[ALPHA_SIZE]={'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};

/* Types declaration */
struct tuple{
    double freq;
    char letter;
};
typedef struct tuple Tuple;

/* Main program */
int main(int argc, char *argv[]){
    // Control of arguments
    if (argc!=3){
            printf("Two arguments are needed\n1. Name of the input file\n2. Name of the output file\nExample: ./freq_analysis inputfile outputfile");
        return (EXIT_FAILURE);
    }

    // Variables
    Tuple *sorted_down;
    sorted_down=malloc(ALPHA_SIZE*sizeof(Tuple));
    double tempf;
    double *freq_out;
    freq_out=malloc(ALPHA_SIZE*sizeof(double));
    char templ;
    int i,j,hits,index;
    FILE* inputFile;
    FILE* outputFile;

    // Init variables
    for(i=0;i<ALPHA_SIZE;i++){
        (*(sorted_down+i)).letter=97+i;
        (*(freq_out+i))=0;
        (*(sorted_down+i)).freq=0;
    }
    hits=0;
    index=0;
    tempf=0;templ='a';

    // Frequency analysis of the input file
    // in: ciphered text file
    // out: tuples sorted in descending order related to their frequency
    inputFile=fopen(argv[1],"rt");
    while(1){
        i=fgetc(inputFile);
        if(i==EOF)
            break;
        if('a'<=i&&i<='z'){
            (*(freq_out+i-97))++; // 97 = 'a' ASCII code
            hits++;
        }
        else if('A'<=i&&i<='Z'){
            (*(freq_out+i-65))++; // 65 = 'A' ASCII code
            hits++;
        }
    }
    fclose(inputFile);
    for(i=0;i<ALPHA_SIZE;i++){
        (*(freq_out+i))=(*(freq_out+i))/hits*100;
        (*(sorted_down+i)).freq=(*(freq_out+i));
    }
    free(freq_out);
    for(i=0;i<ALPHA_SIZE;i++){
        for(j=i;j<ALPHA_SIZE;j++){
            if((*(sorted_down+i)).freq<(*(sorted_down+j)).freq){
                tempf=(*(sorted_down+i)).freq;templ=(*(sorted_down+i)).letter;
                (*(sorted_down+i)).freq=(*(sorted_down+j)).freq;(*(sorted_down+i)).letter=(*(sorted_down+j)).letter;
                (*(sorted_down+j)).freq=tempf;(*(sorted_down+j)).letter=templ;
            }
        }
    }

    // Creation and writing of the output file
    inputFile=fopen(argv[1],"rt");
    outputFile=fopen(argv[2],"wt");
    while(1){
        i=fgetc(inputFile);
        if(i==EOF)
            break;
        if(i==' '){
            putc(i,outputFile);
        }
        else{
            for(j=0;j<ALPHA_SIZE;j++){
                if((*(sorted_down+j)).letter==i){
                    index=j;
                    break;
                }
            }
            putc(ALPHA_DOWN_EN[index],outputFile);
        }
    }
    free(sorted_down);
    fclose(inputFile);
    fclose(outputFile);
    // Finished !
    return 0;
}
