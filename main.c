#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h" 
#include "morse.h"
#include "text.h"
// #include <windows.h> // Loại bỏ dòng này nếu không cần thiết

void run();
int showHandMenu()
{
    int option;
    printf("Choose the option which you want..\n");
    printf("1) Text to Morse\n");
    printf("2) Morse to Text\n");

    // Kiểm tra đầu vào của người dùng
    while (1) {
        if (scanf("%d", &option) != 1) {
            printf("Invalid input! Please enter a valid option: ");
            // Xóa bộ đệm để tránh lỗi vô hạn nếu người dùng nhập không hợp lệ
            while(getchar() != '\n'); 
        } else if (option == 1 || option == 2) {
            break; // Thoát vòng lặp nếu lựa chọn hợp lệ
        } else {
            printf("Invalid choice! Please choose 1 or 2: ");
        }
    }
    
    return option;
}

void run(){
    Node *root;
    root = fillTree();  // Đảm bảo rằng fillTree() đã được định nghĩa đúng
    if (root == NULL) {
        printf("Error initializing Morse tree!\n");
        return;
    }
    
    int handling = showHandMenu();

    if(handling == 1)
        textToMorsecodeFileReading();
    else
        morseToTextFileReading(root);  // Đảm bảo morseToTextFileReading() đã được định nghĩa
}

int main() {
    run();
    return 0;
}
