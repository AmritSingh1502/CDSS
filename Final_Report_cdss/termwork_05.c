#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048


bool is_substring(char *check , char *string)
{
        int slen = strlen(string);
        int clen = strlen(check);  

        int end = slen - clen;

        for(int i =0 ; i< end ; i++)
        {
            bool check_found = true;

            for(int j =0 ; j < clen ; j++)
            {
                if(check[j] != string[i+j])
                {
                    check_found = false;
                    break;
                }
            }

            if(check_found == true) return true;
        }

        return false;
}


void string_replace(char* source , size_t sourceSize, char* substring, char* with)
{
    char* substring_source = strstr(source,substring);
    if(substring_source == NULL )
    {
        return ;
    }

    if(sourceSize < strlen(source) + (strlen(with)- strlen(substring))){
        printf("buffer size is small\n");
        return  ;
    }

    memmove(
        substring_source + strlen(with),
        substring_source + strlen(substring),
        strlen(substring_source) - strlen(substring) + 1
    );

    memcpy(substring_source,with,strlen(with));
}


int main()
{

   FILE *file , *temp;

    char filename[FILENAME_MAX];
    char temp_filename[FILENAME_MAX];
    char buffer[MAX_LINE];

    printf("FILE:");
    scanf("%s",filename);

    strcpy(temp_filename,"temp____");
    strcat(temp_filename, filename);

    file = fopen(filename , "r");
    temp = fopen(temp_filename , "w");

    

    if( file == NULL || temp == NULL )
    {
        printf("error opening file\n");
        exit(0);
    }

    bool keep_reading = true;
    char macro[] = "#define";
    char special[50];
    // char newString[10][10];
    // int i , j ,next;

    char define[20] ={ 0 };
    char keyword[20] = { 0 };
    char value[20] = { 0 };


      do
    {
        fgets(buffer , MAX_LINE , file);

        if(feof(file))
        {
            keep_reading = false;

        }else if(is_substring(macro,buffer)){

                strcpy(special,buffer);
                // printf("special value : %s",special);

                sscanf(special,"%s%s%s",define,keyword,value);    
                // printf("macro is %s and keyword is %s and value is %s\n", define,keyword,value);

                fputs(buffer,temp);
                
        }else if(is_substring(keyword,buffer)){

                     string_replace(buffer,100,keyword,value);

                    fputs(buffer,temp);

                
        }else{
            fputs(buffer, temp);
        }

    } while(keep_reading);

rewind(file);
rewind(temp);
fclose(file);
fclose(temp);

remove(filename);
rename(temp_filename, filename);

    return 0;

}