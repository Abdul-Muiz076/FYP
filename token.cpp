#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function for tokenization
void tokenizeText(char *text, const char *delimiter) {
    // Pointer to store the token
    char *token;

    // Get the first token
    token = strtok(text, delimiter);

    // Process tokens
    while (token != NULL) {
        printf("Token: %s\n", token);
        // Get the next token
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

    // Call the tokenizeText function
    const char delimiter[] = " "; // Specify the delimiter
    tokenizeText(text, delimiter);

    // Free allocated memory
    free(text);

    return 0;
}

