#ifndef MORSE_H_INCLUDED
#define MORSE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DOT_SEQUENCE 8

// Định nghĩa cấu trúc Node, chứa kí tự và 2 con trỏ để trỏ tới cây con trái, phải
typedef struct node {
    char c;
    struct node *left;
    struct node *right;
} Node;

// Kiểm tra có phải kí tự Morse không
int isValidMorseCharacter(char ch) {
    return (ch == '.' || ch == '-' || ch == ' ' || ch == '/' || ch == '\n');
}

// Kiểm tra xem file Morse có hợp lệ không
int isValidMorseFile(char *filename) {
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error: File '%s' could not be opened.\n", filename);
        return 0;
    }

    char ch;
    int position = 0;
    while ((ch = fgetc(inputFile)) != EOF) {
        position++;
        if (!isValidMorseCharacter(ch)) {
            printf("Error: Invalid character '%c' at position %d.\n", ch, position);
            fclose(inputFile);
            return 0; // Chứa ký tự không hợp lệ
        }
    }

    fclose(inputFile);
    return 1; // Hợp lệ
}

// Hàm bỏ qua các ký tự không hợp lệ
void skipInvalidSequence(FILE *inputFile) {
    char ch;
    while ((ch = fgetc(inputFile)) != ' ' && ch != EOF) {
        // Bỏ qua các ký tự
    }
}

// Hàm chuyển từ Morse code thành văn bản
void morseToTextFileReading(Node *root) {
    if (root == NULL) {
        printf("Error: Morse tree is empty.\n");
        return;
    }

    char inputFileName[50], outputFileName[50];
    printf("Enter input file name (Morse code): ");
    scanf("%s", inputFileName);

    printf("Enter output file name (Text): ");
    scanf("%s", outputFileName);

    // Kiểm tra nếu file output đã tồn tại
    FILE *testFile = fopen(outputFileName, "r");
    if (testFile != NULL) {
        fclose(testFile);
        char overwrite;
        printf("Output file already exists. Overwrite? (y/n): ");
        scanf(" %c", &overwrite);
        if (overwrite != 'y' && overwrite != 'Y') {
            printf("Operation cancelled.\n");
            return;
        }
    }

    // Kiểm tra file đầu vào có hợp lệ không
    if (!isValidMorseFile(inputFileName)) {
        printf("Invalid input file!\n");
        return;
    }

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL) {
        printf("Error: Could not open input file '%s'.\n", inputFileName);
        return;
    }
    if (outputFile == NULL) {
        printf("Error: Could not create output file '%s'.\n", outputFileName);
        fclose(inputFile);
        return;
    }

    Node *temp = root; // Con trỏ tạm bắt đầu từ gốc cây
    char ch;
    int dotCount = 0;

    while ((ch = fgetc(inputFile)) != EOF) {
        // Nếu kí tự là '.' thì rẽ nhánh trái
        if (ch == '.') {
            dotCount++;
            if (dotCount >= MAX_DOT_SEQUENCE) {
                fprintf(outputFile, "#");
                skipInvalidSequence(inputFile);
                temp = root;
                dotCount = 0;
            } else if (temp->left != NULL) {
                temp = temp->left;
            }
        }
        // Nếu kí tự là '-' thì rẽ nhánh phải
        else if (ch == '-') {
            if (temp->right != NULL) {
                temp = temp->right;
            } else {
                fprintf(outputFile, "*");
                skipInvalidSequence(inputFile);
                temp = root;
            }
        }
        // Nếu kí tự là dấu cách thì in ra kí tự hiện tại
        else if (ch == ' ') {
            if (temp != root) {
                fprintf(outputFile, "%c", temp->c);
            }
            temp = root;
        }
        // Nếu kí tự là '/' thì ghi dấu cách
        else if (ch == '/') {
            fprintf(outputFile, " ");
            skipInvalidSequence(inputFile);
        }
        // Nếu kí tự là xuống dòng thì ghi xuống dòng
        else if (ch == '\n') {
            fprintf(outputFile, "\n");
            temp = root;
        } else {
            if (temp == root) {
                fprintf(outputFile, "*");
                skipInvalidSequence(inputFile);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Conversion completed. Check the output file.\n");
}

#endif // MORSE_H_INCLUDED