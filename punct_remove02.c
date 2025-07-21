#include <stdio.h>

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
        while (*ptr == ' ' || *ptr == ',' || *ptr == '.' || *ptr == '?' ||  *ptr == '}' ||  *ptr == '/' ||   *ptr == '\n' ) {
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
    char Text[] = "Hello, this is a sample text / ? : data for testing. He is another sentence.";
    readText(Text);
    return 0;
}