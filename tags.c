#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to remove HTML tags
void remove_html_tags(char *text) {
    int i = 0, j = 0;
    int in_tag = 0;
    char *result;

    // Allocate memory for the cleaned text
    result = (char *)malloc(strlen(text) + 1); // Safe allocation based on input text length
    if (result == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    while (text[i] != '\0') {
        // Check if we are inside a tag
        if (text[i] == '<') {
            in_tag = 1;
        } else if (text[i] == '>') {
            in_tag = 0;
        } else if (!in_tag) {
            // If not inside a tag, keep the character
            result[j++] = text[i];
        }
        i++;
    }

    result[j] = '\0';  // Null-terminate the result string

    // Copy cleaned text back to the original text
    strcpy(text, result);

    // Free the temporary result memory
    free(result);
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

    // Read file contents into memory
    fread(text, 1, fileSize, file);
    text[fileSize] = '\0';  // Null-terminate the string
    fclose(file);

    printf("Original Text:\n%s\n", text);

    // Process the text to remove HTML tags
    remove_html_tags(text);

    printf("\nCleaned Text:\n%s\n", text);

    // Free allocated memory
    free(text);

    return 0;
}
