#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Node {
    uint64_t value;
    uint64_t frequency;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(uint64_t value, uint64_t frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void generateHuffmanCodes(Node* root, uint64_t code, uint64_t depth) {
    static uint64_t codes[64]; // Assuming maximum depth of the Huffman tree is 64
    if (root == NULL) return;

    // If leaf node, print the code
    if (!root->left && !root->right) {
        printf("Value: %llu, Code: ", (unsigned long long)root->value);
        for (uint64_t i = 0; i < depth; i++) {
            printf("%llu", (unsigned long long)codes[i]);
        }
        printf("\n");
    }

    // Recursive calls for left and right sub-trees
    codes[depth] = 0;
    generateHuffmanCodes(root->left, code, depth + 1);
    codes[depth] = 1;
    generateHuffmanCodes(root->right, code, depth + 1);
}

int main() {
    // Example input data (uint64_t integers)
    uint64_t data[] = {10, 20, 30, 40, 50, 60};
    uint64_t frequencies[] = {2, 3, 4, 2, 1, 2}; // Example frequencies

    // Create nodes for each integer with their frequencies
    Node* nodes[6];
    for (int i = 0; i < 6; i++) {
        nodes[i] = createNode(data[i], frequencies[i]);
    }

    // Construct the Huffman tree (You need to implement this part)
    // For simplicity, let's assume a pre-built Huffman tree
    Node* root = createNode(0, 0);
    root->left = createNode(0, 0);
    root->right = createNode(0, 0);
    root->left->left = createNode(10, 0);
    root->left->right = createNode(20, 0);
    root->right->left = createNode(30, 0);
    root->right->right = createNode(40, 0);
    printf("\%\n\")
    // Generate Huffman codes
    generateHuffmanCodes(root, 0, 0);

    // Free memory allocated for nodes
    for (int i = 0; i < 6; i++) {
        free(nodes[i]);
    }

    return 0;
}
