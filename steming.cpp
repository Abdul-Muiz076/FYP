#include <stdio.h>
#include <string.h>

char* stem_word(char* word) {
    int length = strlen(word);
    
    if (length > 2 && strcmp(word + length - 2, "ed") == 0) {
        word[length - 2] = '\0';
    } else if (length > 3 && strcmp(word + length - 3, "ing") == 0) {
        word[length - 3] = '\0';
    }
    
    return word;
}

int main() {
    char word[] = "running";
    printf("Original word: %s\n", word);
    printf("Stemmed word: %s\n", stem_word(word));
    
    return 0;
}

