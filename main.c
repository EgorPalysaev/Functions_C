#include "my_string.h"
#include <string.h>

int main(void){
    char my_str1[20] = "Bye";
    char my_str2[] = "Hello!"; 
    char str1[20] = "Bye";
    char str2[] = "Hello!"; 
    printf("%s\n", my_strcpy(my_str1, my_str2));   
    printf("%s\n", strcpy(str1, str2));   

    return 0;
}
    
