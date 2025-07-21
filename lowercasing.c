#include <ctype.h> // For tolower()
#include <stdio.h>
#include <stdlib.h>

// Function to convert text to lowercase
void toLowerCase(char *text) {
    for (int i = 0; text[i]; i++) {
        text[i] = tolower((unsigned char)text[i]);
        putchar(text[i]);
    }
}


int main() {
    FILE *file;
    char *text;
    long fileSize;

    file = fopen("file.txt", "r");  // Open the file in read mode
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

    // Convert the text to lowercase
    toLowerCase(text);
    free(text);  // Free allocated memory
    return 0;
}
