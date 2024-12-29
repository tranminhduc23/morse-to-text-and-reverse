#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Hàm chuyển kí tự sang mã Morse
void charToMorse(char ch, FILE *outputFile)
{
    switch (ch)
    {
    case 'a':
    case 'A':
        fprintf(outputFile, ".- ");
        break;
    case 'b':
    case 'B':
        fprintf(outputFile, "-... ");
        break;
    case 'c':
    case 'C':
        fprintf(outputFile, "-.-. ");
        break;
    case 'd':
    case 'D':
        fprintf(outputFile, "-.. ");
        break;
    case 'e':
    case 'E':
        fprintf(outputFile, ". ");
        break;
    case 'f':
    case 'F':
        fprintf(outputFile, "..-. ");
        break;
    case 'g':
    case 'G':
        fprintf(outputFile, "--. ");
        break;
    case 'h':
    case 'H':
        fprintf(outputFile, ".... ");
        break;
    case 'i':
    case 'I':
        fprintf(outputFile, ".. ");
        break;
    case 'j':
    case 'J':
        fprintf(outputFile, ".--- ");
        break;
    case 'k':
    case 'K':
        fprintf(outputFile, "-.- ");
        break;
    case 'l':
    case 'L':
        fprintf(outputFile, ".-.. ");
        break;
    case 'm':
    case 'M':
        fprintf(outputFile, "-- ");
        break;
    case 'n':
    case 'N':
        fprintf(outputFile, "-. ");
        break;
    case 'o':
    case 'O':
        fprintf(outputFile, "--- ");
        break;
    case 'p':
    case 'P':
        fprintf(outputFile, ".--. ");
        break;
    case 'q':
    case 'Q':
        fprintf(outputFile, "--.- ");
        break;
    case 'r':
    case 'R':
        fprintf(outputFile, ".-. ");
        break;
    case 's':
    case 'S':
        fprintf(outputFile, "... ");
        break;
    case 't':
    case 'T':
        fprintf(outputFile, "- ");
        break;
    case 'u':
    case 'U':
        fprintf(outputFile, "..- ");
        break;
    case 'v':
    case 'V':
        fprintf(outputFile, "...- ");
        break;
    case 'w':
    case 'W':
        fprintf(outputFile, ".-- ");
        break;
    case 'x':
    case 'X':
        fprintf(outputFile, "-..- ");
        break;
    case 'y':
    case 'Y':
        fprintf(outputFile, "-.-- ");
        break;
    case 'z':
    case 'Z':
        fprintf(outputFile, "--.. ");
        break;
    case '1':
        fprintf(outputFile, ".---- ");
        break;
    case '2':
        fprintf(outputFile, "..--- ");
        break;
    case '3':
        fprintf(outputFile, "...-- ");
        break;
    case '4':
        fprintf(outputFile, "....- ");
        break;
    case '5':
        fprintf(outputFile, "..... ");
        break;
    case '6':
        fprintf(outputFile, "-.... ");
        break;
    case '7':
        fprintf(outputFile, "--... ");
        break;
    case '8':
        fprintf(outputFile, "---.. ");
        break;
    case '9':
        fprintf(outputFile, "----. ");
        break;
    case '0':
        fprintf(outputFile, "----- ");
        break;
    case '.':
        fprintf(outputFile, ".-.-.- ");
        break;
    case ',':
        fprintf(outputFile, "--..-- ");
        break;
    case '?':
        fprintf(outputFile, "..--.. ");
        break;
    case ':':
        fprintf(outputFile, "---... ");
        break;
    case '-':
        fprintf(outputFile, "-....- ");
        break;
    case ' ':
        fprintf(outputFile, "/ ");
        break;
    case '\n':
        fprintf(outputFile, "\n");
        break;
    default:
        fprintf(outputFile, "* ");
    }
}

// Kiểm tra xem file văn bản có hợp lệ không
int isValidTextFile(char *filename)
{
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("FILENAME could not be opened.\n");
        return 0;
    }

    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        if (!isprint(ch) && ch != '\n' && ch != '\t' && ch != ' ') {
            fclose(inputFile);
            return 0; // Chứa kí tự không hợp lệ
        }
    }

    fclose(inputFile);
    return 1; // Hợp lệ
}

// Hàm chuyển từ văn bản sang mã Morse và ghi ra file
void textToMorsecodeFileReading()
{
    char inputFileName[50], outputFileName[50];
    printf("Enter input file name (Text): ");
    scanf("%s", inputFileName);

    printf("Enter output file name (Morse code): ");
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
    if (!isValidTextFile(inputFileName)) {
        printf("Invalid input file!\n");
        return;
    }

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return;
    }

    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        charToMorse(ch, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Conversion completed. Check the output file.\n");
}

#endif // TEXT_H_INCLUDED