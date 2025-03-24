#include <stdio.h>
#include <string.h>

int length(const char *str) {
    int count = 0;
    while (*str) {
        if ((*str & 0xC0) != 0x80) {
            count++;
        }
        str++;
    }
    return count;
}

int words(const char *str) {
    int count = 0;
    char *temp = strdup(str);
    char *ptr = temp;
    const char *delimiters = " ";
    
    while (*ptr) {
        ptr += strspn(ptr, delimiters);
        if (*ptr) {
            count++;
            ptr += strcspn(ptr, delimiters);
        }
    }
    free(temp);
    return count;
}

void tokenize(const char *str) {
    char *temp = strdup(str);
    char *token;
    const char *delimiters = " \t\n.,!?;:\"'";
    
    token = strtok(temp, delimiters);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, delimiters);
    }
    free(temp);
}

int main(int argc, char *argv[]) {
    const char *command = argv[1];
    const char *text = argv[2];
    
    if (strcmp(command, "bytes") == 0) {
        printf("Długość w bajtach: %lu\n", strlen(text));
    }
    else if (strcmp(command, "length") == 0) {
        int chars = length(text);
        printf("Długość w znakach UTF-8: %d\n", chars);
    }
    else if (strcmp(command, "words") == 0) {
        int words_count = words(text);
        printf("Liczba wyrazów: %d\n", words_count);
    }
    else if (strcmp(command, "tokenize") == 0) {
        printf("Tokeny:\n");
        tokenize(text);
    }
    
    return 0;
}
