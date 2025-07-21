#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to remove URLs starting with "https://" or "www"
void removeURLs(char *text) {
    char *start, *end;
    int in_tag = 0;  // Track if we're inside HTML tags
    int i = 0, j = 0;  // Indices for text processing
    size_t len, text_len, temp_len;
    char *temp;

    // Get the initial length of the text
    text_len = strlen(text);
    
    // Allocate memory for temp dynamically (initially same size as the text)
    temp = (char *)malloc(text_len + 1);
    if (temp == NULL) {
        printf("Error: Memory allocation for temp failed.\n");
        return;
    }

    // Remove "https://" URLs
    while ((start = strstr(text, "https://")) != NULL) {
        // Find the end of the URL
        end = start;
        while (*end && !isspace(*end) && *end != '\0') {
            end++;
        }

        // Copy the part before the URL and the part after the URL
        len = start - text;
        strncpy(temp, text, len);
        temp[len] = '\0';

        // Append the part after the URL
        strcat(temp, end);

        // Copy the modified string back into the original text
        strcpy(text, temp);
    }

    // Remove "www" URLs (starting with "www" and ending with a space or end of string)
    while ((start = strstr(text, "www")) != NULL) {
        // Check if "www" is a valid URL (i.e., not part of a word)
        if (start == text || !isalnum(*(start - 1))) {
            // Find the end of the URL
            end = start;
            while (*end && !isspace(*end) && *end != '\0' && *end != '.') {
                end++;
            }

            // Copy the part before the URL and the part after the URL
            len = start - text;
            strncpy(temp, text, len);
            temp[len] = '\0';

            // Append the part after the URL
            strcat(temp, end);

            // Copy the modified string back into the original text
            strcpy(text, temp);
        } else {
            // If "www" is part of a word (not a URL), break out of the loop
            break;
        }
    }

    // Remove HTML tags and keep the content
    i = 0;
    j = 0;
    while (text[i] != '\0') {
        // Check if we are inside a tag
        if (text[i] == '<') {
            in_tag = 1;
        } else if (text[i] == '>') {
            in_tag = 0;
        } else if (!in_tag) {
            // If not inside a tag, copy the character to temp
            temp[j++] = text[i];
        }
        i++;
    }
    temp[j] = '\0';  // Null-terminate the result string

    // Resize temp if necessary
    temp_len = strlen(temp);
    temp = (char *)realloc(temp, temp_len + 1);
    if (temp == NULL) {
        printf("Error: Memory reallocation for temp failed.\n");
        return;
    }

    // Copy the cleaned text back to the original text
    strcpy(text, temp);

    // Free the dynamically allocated temp memory
    free(temp);
}

int main() {
    FILE *file;
    char *Allocate;
    long filesize;

    // Open the file in read mode
    file = fopen("file.txt", "r");

    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    rewind(file);

    // Allocate memory to store the file content
    Allocate = (char *)malloc(filesize + 1);
    if (Allocate == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    // Read the content of the file into memory
    fread(Allocate, 1, filesize, file);
    Allocate[filesize] = '\0';  // Null-terminate the string
    fclose(file);

    // Remove URLs and HTML tags from the text
    removeURLs(Allocate);

    // Print the text after removing URLs and HTML tags
    printf("Text after removing URLs: %s\n", Allocate);

    // Free the allocated memory
    free(Allocate);

    return 0;
}
