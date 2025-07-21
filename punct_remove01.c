#include <stdio.h>
#include <stdlib.h>

struct Result {
    int space;
    int stop;
};

struct Result detect(const char *text) {
    struct Result s1 = {0, 0};  
    const char *ptr = text;

    while (*ptr != '\0') {
        if (*ptr == ' ') {
            s1.space++;
        }
        if (*ptr == '.') {
            s1.stop++;
        }
        ptr++;
    }
    return s1;  
}

void readText(const char *text) {
    const char *ptr = text;
    struct Result s1 = detect(text);

    while (*ptr != '\0') {
        while (*ptr == ' ' || *ptr == ',' || *ptr == '.' || *ptr == '\n') {
            ptr++;
        }
        while (*ptr != ' ' && *ptr != ',' && *ptr != '.' && *ptr != '\n' && *ptr != '\0') {
            putchar(*ptr); 
            ptr++;
        }
        if (*ptr != '\0') {
            putchar(' ');  
        }
    }
    printf("\nTotal spaces: %d\n", s1.space);
    printf("Total full stops: %d\n", s1.stop);
}

int main() {
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

    fread(Allocate, 1, fileSize, file);
    Allocate[fileSize] = '\0';  // Null-terminate the string
    fclose(file);

    // Process the text
    readText(Allocate);

    free(Allocate);  // Free allocated memory
    return 0;
}
