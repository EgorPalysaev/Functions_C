#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 128
#define MAX_WORD_LENGTH 63

enum ERR { OK = 0, ERROR = 1 };

// #define WIDHT (M + 1)            // #define WIDHT (M - 1) => "(M - 1)". Because macro does not have a subtraction
//
// #define STR_IMPL(x) #x           //STR_IMPL(x) => "x"
// #define STR(x) STR_IMPL(x)       //STR(x) => (x becomes 63) => STR_IMPL(63)
// #define SCAN_FORMAT "%" STR(M) "s" //becomes "%63s"  //SCAN_FORMAT "%"STR_IMPL(M)"s" => "%Ms"

static int count_digits(char *string, int length){
    int count = 0;
    for (int i = 0; i < length; i++){
	if ('0' <= string[i] && string[i] <= '9') count++;
    }
    return count;
}
//static means that this function can be used only in this .c file
static bool split_words(const char *input, char words[MAX_WORDS][MAX_WORD_LENGTH + 1], int *word_count, int digits_in_words[MAX_WORDS]) {
    const unsigned char *p = (const unsigned char *)input;
    int count = 0;

    while (*p != '\0') {
        while (*p != '\0' && isspace(*p)) {      //isspace() checks if the symbol are " \t\n\r\f\v" and return nonzero if it is otherwise 0 
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

        memcpy(words[count], start, length);  //memcpy(destination, source, number_of_bytes) writes to the first argument pointer from second argument pointer by size_t third argumert len
	digits_in_words[count] = count_digits(words[count], length);
        words[count][length] = '\0';
        count++;
    }

    *word_count = count;
    return true;
}

int main(void) {
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
    return OK;
}
    
