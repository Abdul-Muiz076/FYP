#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List of stop words
const char *stopWords[] = {
    "the", "and", "a", "an", "is", "are", "was", "were", "to", "of", "in", "on", "for", "with", "at", "by", "from", "this", "that", "it", "as", "but"
};
const int stopWordsCount = sizeof(stopWords) / sizeof(stopWords[0]);

// Function to check if a word is a stop word
int isStopWord(const char *word) {
    for (int i = 0; i < stopWordsCount; i++) {
        if (strcmp(word, stopWords[i]) == 0) {
            return 1; // It is a stop word
        }
    }
    return 0; // It is not a stop word
}

// Function to tokenize and process the text
void removeStopWords(char *text) {
    const char *delimiters = " ,.\n"; // Delimiters for tokenizing
    char *token = strtok(text, delimiters);

    printf("Processed text without stop words:\n");

    while (token != NULL) {
        if (!isStopWord(token)) {
            printf("%s ", token);
        }
        token = strtok(NULL, delimiters);
    }
    printf("\n");
}

int main() {
    FILE *file;
    char *text;
    long fileSize;

    // Open the file in read mode
    file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    // Allocate memory to read file contents
    text = (char *)malloc(fileSize + 1);
    if (text == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    fread(text, 1, fileSize, file);
    text[fileSize] = '\0';  // Null-terminate the string
    fclose(file);

    // Process the text for stop word removal
    removeStopWords(text);

    free(text); // Free allocated memory
    return 0;
}
