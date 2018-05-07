/* 
 * File:   main.c
 * Author: Khalid
 * SN: 1147299
 * MACID: asadk
 * Created on October 15, 2012, 4:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int shift = 99; // create global variable for key (last 2 digits of SN)
double ocurrence_sum = 0;
/*
 * 
 */
typedef struct ciphertext_analysis_t{ // structure
    double ascii_sum;
    double mean;
    double standard_deviation;// define all variables as doubles
    double frequency[26];
    double relative_frequency[];
};// don't declare a structure here

double average(double sum, double count);// calculate average
double std_dev(double n, double sum1, double sum2);// standard deviation
char encrypt(char plaintext);// encryption function
char decrypt(char ciphertext);// decryption function
void printer(struct ciphertext_analysis_t cat); // function to print values

int main(int argc, char** argv) {
    FILE *input, *output; // declare pointers for file accessing
    int option = 4, check=0;
    double i=0, sum1=0;
    char cipher, final;
    
    struct ciphertext_analysis_t cat; // create a structure to be used
    
    int k;
    for (k=0; k<26; k++){// set all values inside the array to 0
        cat.frequency[k]=0;
    }

    printf("ENCRYPTION AND DECRYPTION PROGRAM BY KHALID ASAD\n");
    
    while (option == 4){ // goes on until user chooses to encrypt or decrypt
        printf("What would you like to do?\n1.Encrypt a code\n2.Decrypt a code\n");
        scanf("%d",&option);
        if (option == 1){// encryption
            check = 1;
            input = fopen("plaintext.txt","r");
            output = fopen("ciphertext.txt","w");            
        }
        else if (option == 2){// decryption
            check = 2;
            input = fopen("ciphertext.txt","r");
            output = fopen("messagetext.txt","w");
        }
        else{
            option = 4; // error message
            printf("INCORRECT OPTION! PLEASE TRY AGAIN!\n");
        }
        
        if (check ==1 || check ==2){ // for encryption/decryption
            fscanf(input, "%c", &cipher);// read the next character
            while(!feof(input)){// until end of the file being read
                printf("%c is changed to ",cipher);
                if ((cipher < 'A') || (cipher > 'Z') ){// for non-capital-letter
                    final = cipher; // leave character the same
                }
                else{ // if char is between A and Z
                    cat.frequency[cipher-65]++;// add the frequency of this char
                    ocurrence_sum++;// counter for occurrences
                    if (check==1){// send to encryption function
                        final = encrypt(cipher);
                    }
                    else if (check==2){// send to decryption function
                        final = decrypt(cipher);
                    }
                    cat.ascii_sum+=final;// add character to sum
                    i++;
                    sum1 += pow(final,2);// add square character
                }
                fprintf(output, "%c", final);
                printf("%c\n", final); // print letters that are being changed
                fscanf(input, "%c", &cipher);
            }
            fclose(input);
            fclose(output);// close files
            cat.mean = average(cat.ascii_sum,i);// calculate average
            cat.standard_deviation = std_dev(i,sum1,pow(cat.ascii_sum,2));
            printer(cat);// send the structure to print out all variables
        }
        
    }
    return (EXIT_SUCCESS);
}

double average(double sum, double count){// calculates average
    return sum/count;
}

double std_dev(double n, double sum1, double sum2){// standard deviation
    return(sqrt ( (n*sum1 - sum2)/pow(n,2) ) );
}

char encrypt(char plaintext){// encryption
    return (plaintext - 65 + shift)%26 + 65;
}

char decrypt(char ciphertext){// decryption
    return ((26 - (shift-(ciphertext - 65))%26)%26) + 65;
}

void printer(struct ciphertext_analysis_t cat){// print all values
    printf("\nThe ASCII sum is: %.0f\n", cat.ascii_sum);
    printf("The Mean is: %.3f\n", cat.mean);
    printf("The Standard Deviation is: %.3f\n", cat.standard_deviation);
    printf("Letter:Frequency:Relative Frequency\n");
    int i;
    for (i =0; i<26; i++){// print both types of frequencies
        cat.relative_frequency[i]= (cat.frequency[i]/ocurrence_sum)*100;
        printf("%c:%.0f:%.2f%%\n",i+65,cat.frequency[i],cat.relative_frequency[i]);
    }
}
