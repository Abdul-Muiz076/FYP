#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to check if a string ends with a specific suffix
bool endsWith(const char *word, const char *suffix) {
    size_t wordLen = strlen(word);
    size_t suffixLen = strlen(suffix);

    if (suffixLen > wordLen) {
        return false;
    }
    return strcmp(word + wordLen - suffixLen, suffix) == 0;
}

// Function to remove a suffix from a word
void removeSuffix(char *word, const char *suffix) {
    size_t wordLen = strlen(word);
    size_t suffixLen = strlen(suffix);

    if (endsWith(word, suffix)) {
        word[wordLen - suffixLen] = '\0';
    }
}

// Lemmatization function
void lemmatize(char *word) {
    if (endsWith(word, "ing")) {
        removeSuffix(word, "ing");
    } else if (endsWith(word, "ed")) {
        removeSuffix(word, "ed");
    } else if (endsWith(word, "es")) {
        removeSuffix(word, "es");
    } else if (endsWith(word, "s")) {
        removeSuffix(word, "s");
    }
}

// Function to tokenize text and apply lemmatization
void tokenizeText(char *text, const char *delimiter) {
    printf("Original Words -> Lemmatized Words\n");
    printf("----------------------------------\n");

    char *token = strtok(text, delimiter);
    while (token != NULL) {
        char *word = strdup(token);  // Duplicate the word for modification
        lemmatize(word);
        printf("%s -> %s\n", token, word);
        free(word);  // Free the duplicated word memory
        token = strtok(NULL, delimiter);
    }
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

    // Read the file contents
    fread(text, 1, fileSize, file);
    text[fileSize] = '\0';  // Null-terminate the string
    fclose(file);

    // Tokenize and lemmatize the text
    const char delimiter[] = " \n";  // Delimiters: space and newline
    tokenizeText(text, delimiter);

    // Free allocated memory
    free(text);

    return 0;
}
