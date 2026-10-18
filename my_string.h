#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <stdio.h>

size_t my_strlen(const char* str){
    int i = 0;
    while (*(str+i) != '\0')
	i++;
    return (size_t)i;
}

size_t my_strlen_zero(const char* str){
    int i = 0;
    while (*(str+i) != '\0')
	i++;
    while (*(str+i) == '\0')
	i++;
    return (size_t)i;
}

char* my_strcat(char* str1, const char* str2){
    char *temp = str1;
    while(*temp != '\0')
	temp++;
    while(*(temp+1) == '\0')
	*temp++ = *str2++;
    return str1;
}

void print_string(char* str1, size_t n){
    for(int i = 0; i < n; i++)
	printf("[%c] ", str1[i]);
}

int my_strcmp(const char* str1, const char* str2){
    while(*str1 == *str2 && *str1 != '\0'){
	str1++;
	str2++;
    }
    if (*str1 == *str2) return 0;
    return (*str1 > *str2) ? 1 : -1;
}

char *my_strcpy(char *str1, const char *str2){
    char *temp = str1;
    if (my_strlen_zero(str1) >= my_strlen(str2)){
	while(*str2 != '\0')
	    *str1++ = *str2++;
	return temp;
    } 
    return NULL;
}
#endif
