#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include "morse.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>

// Hàm tạo mới một node với ký tự 'c'
static Node* createNode(char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for node '%c'\n", c);
        return NULL;
    }
    newNode->c = c;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm xây dựng cây Morse từ một danh sách các ký tự
Node* fillTree() {
    // Cấu trúc cây Morse được xác định sẵn trong mảng, mỗi phần tử là một ký tự tương ứng với mã Morse
    char morseTree[] = {
        ' ', 'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O',
        'H', 'V', 'F', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '5', '4', '3', '2', 
        '1', '6', '7', '8', '9', '0', '?', '.', '-', ',', ':'
    };
    
    // Tạo node gốc cây
    Node* root = createNode(morseTree[0]);
    if (!root) return NULL;

    // Dùng biến index để duyệt qua mảng morseTree
    int index = 1;
    Node* queue[100]; // Hàng đợi để duyệt cây
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (index < sizeof(morseTree) / sizeof(morseTree[0])) {
        Node* current = queue[front++];
        if (index < sizeof(morseTree) / sizeof(morseTree[0])) {
            current->left = createNode(morseTree[index++]);  // Tạo nhánh trái
            queue[rear++] = current->left;
        }
        if (index < sizeof(morseTree) / sizeof(morseTree[0])) {
            current->right = createNode(morseTree[index++]); // Tạo nhánh phải
            queue[rear++] = current->right;
        }
    }
    
    return root;
}

// Hàm hủy bộ nhớ của cây Morse
void destroyTree(Node *root) {
    if (root == NULL) return;
    
    destroyTree(root->left);  // Hủy nhánh trái
    destroyTree(root->right); // Hủy nhánh phải
    free(root);               // Giải phóng bộ nhớ node hiện tại
}

#endif // STRUCTURES_H_INCLUDED