#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 99


void s1(char input_string[],int i){

     if (input_string[i - 1] == '1')
            {
                printf("OK\n");
            }
}


void s2(char input_string[],int i){
    
            if (input_string[i - 1] == 'b' && input_string[i + 1] == '#' && input_string[i + 2] == ';')
            {
                printf("Found SPECIAL\n");
            }
}

void s3(char input_string[],int i, char invalid_char[],char current_char){

    for (int j = 0; j < 5; j++)
        {
            char current_invalid_char = invalid_char[j];
            
            if (current_char == current_invalid_char)
            {
                printf("ERROR in i/p\n");
                break;
            }
        }
}
int main(){

    char input_string[SIZE];

    char invalid_char[5] = {'!', '@', '$', '%', '&'};

    printf("Enter the input String :\n");
    scanf("%s",input_string);

    char current_char ;
    char current_invalid_char;

    for (int i = 0; i < strlen(input_string); i++)
    {
        char current_char = input_string[i];

        if (current_char == '1')
        {
           s1(input_string,i);
        }

        if (current_char == '.')
        {
            printf("Halt!!\n");
            exit(0);
        }

        
        if (current_char == 'b')
        {
            s2(input_string,i);
        }

        s3(input_string,i,invalid_char,current_char);

        
  
    }

    return 0;
}