#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 128
#define MAX_WORD_LENGTH 63

enum ERR { OK = 0, ERROR = 1 };

static int count_digits(char *string, int length){
    int count = 0;
    for (int i = 0; i < length; i++){
	if ('0' <= string[i] && string[i] <= '9') count++;
    }
    return count;
}
static bool split_words(const char *input, char words[MAX_WORDS][MAX_WORD_LENGTH + 1], int *word_count, int digits_in_words[MAX_WORDS]) {
    const unsigned char *p = (const unsigned char *)input;
    int count = 0;

    while (*p != '\0') {
        while (*p != '\0' && isspace(*p)) {
	    p++;
        }

        if (*p == '\0') {
            break;
        }

        const unsigned char *start = p;
        while (*p != '\0' && !isspace(*p)) {
            p++;
        }

        size_t length = (size_t)(p - start) * sizeof (char);

        if (length > MAX_WORD_LENGTH) {
            fprintf(stderr, "Error: a word exceeds %d characters.\n",
                    MAX_WORD_LENGTH);
            return false;
        }

        if (count >= MAX_WORDS) {
            fprintf(stderr, "Error: more than %d words.\n", MAX_WORDS);
            return false;
        }

        memcpy(words[count], start, length);
	digits_in_words[count] = count_digits(words[count], length);
        words[count][length] = '\0';
        count++;
    }

    *word_count = count;
    return true;
}

int main(void) {
    printf("[A]rray, [M]atrix\n");
    printf("> ");
    char input = getchar();
    while(getchar() != '\n')
	;
    switch (input){
	case 'A': case 'a':
	    char input[MAX_WORDS * (MAX_WORD_LENGTH+1)];
	    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
	    int digits_in_words[MAX_WORDS];
	    int word_count = 0;

	    printf("Enter text: ");

	    if (fgets(input, sizeof input, stdin) == NULL) {
		fprintf(stderr, "Error: could not read input.\n");
		return ERROR;
	    }

	    if (strchr(input, '\n') == NULL) {
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		fprintf(stderr, "Error: input line is incorrect.\n");
		return ERROR;
	    }

	    if (!split_words(input, words, &word_count, digits_in_words)) {
		return ERROR;
	    }

	    double max = 0.0;
	    char *max_digit = NULL;
	    for (int i = 0; i < word_count; i++) {
		printf("%d.)Word: %s. Has %d digits and percentage of digits is %2.2f\n",(i+1), words[i], digits_in_words[i], (double)digits_in_words[i]/(double)strlen(words[i]) * 100);
		if (max < (double)digits_in_words[i]/(double)strlen(words[i])){
		    max = (double)digits_in_words[i]/(double)strlen(words[i]);
		    max_digit = words[i];
		}
	    }
	    if (max_digit != NULL) printf("Word that has maximum percentage of digits: %s\n", max_digit);
	    else printf("Nothing to analyze\n");
	    break;
	case 'M': case 'm':
	    srand((unsigned)time(NULL));
	    int n, sum = 0;
	    printf("Enter a period: ");
	    scanf("%d", &n);
	    int **period = (int**)malloc(n * sizeof(int *));
	    for (int i = 0; i < n; i++){
		printf("\n");
		*(period+i) = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++){
		    *(*(period + i) + j) = rand() % 100;
		    printf("%-3d ", *(*(period + i) + j));
		}
	    }
	    printf("\n>----------------------------------------------<");
	    for (int i = 0; i < n; i++){
		if (n % 2 == 1){
		    if (i == n/2){
			sum += *(*(period + i) + i); 
			continue;
		    }
		}
		int temp = *(*(period + i) + i);
		*(*(period + i) + i) = *(*(period + i) + (n-1-i)); 
		*(*(period + i) + (n-1-i)) = temp;
		sum += *(*(period + i) + i) + *(*(period + i) + (n-1-i));
	    }
	    for (int i = 0; i < n; i++){
		printf("\n");
		for (int j = 0; j < n; j++){
		    printf("%-3d ", *(*(period + i) + j));
		}
	    }
	    printf("\nSum is %d", sum);
	    break;
	default: printf("Quit\n");
    }
    return OK;
}
    
