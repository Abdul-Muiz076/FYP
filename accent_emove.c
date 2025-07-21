#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

// Function to remove accents
void removeAccents(wchar_t *text) {
    int i;
    for (i = 0; text[i] != L'\0'; i++) {
        switch (text[i]) {
            case L'á': case L'à': case L'ä': case L'â':
                text[i] = L'a'; break;
            case L'é': case L'è': case L'ë': case L'ê':
                text[i] = L'e'; break;
            case L'í': case L'ì': case L'ï': case L'î':
                text[i] = L'i'; break;
            case L'ó': case L'ò': case L'ö': case L'ô':
                text[i] = L'o'; break;
            case L'ú': case L'ù': case L'ü': case L'û':
                text[i] = L'u'; break;
            case L'ç':
                text[i] = L'c'; break;
            case L'ñ':
                text[i] = L'n'; break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");  // Set locale for handling wide characters

    FILE *file;
    char *Allocate;
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
    Allocate = (char *)malloc(fileSize + 1);
    if (Allocate == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    fread(Allocate, 1, fileSize, file);  // Read file contents into memory
    Allocate[fileSize] = '\0';  // Null-terminate the string
    fclose(file);

    // Convert the string to wide character format
    wchar_t *wideText = (wchar_t *)malloc((fileSize + 1) * sizeof(wchar_t));
    if (wideText == NULL) {
        printf("Error: Memory allocation failed for wideText.\n");
        free(Allocate);
        return 1;
    }

    mbstowcs(wideText, Allocate, fileSize);  // Convert multi-byte string to wide-character string

    printf("Original text: %ls\n", wideText);

    // Remove accents from the text
    removeAccents(wideText);

    printf("Text after removing accents: %ls\n", wideText);

    free(Allocate);   // Free the memory for the original text
    free(wideText);   // Free the memory for the wide text

    return 0;
}
