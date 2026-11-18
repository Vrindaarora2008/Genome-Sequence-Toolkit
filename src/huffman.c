#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "greedy.h"
typedef struct HuffmanNode {
    unsigned char character;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;
static HuffmanNode *create_node(
    unsigned char character,
    int frequency)
{
    HuffmanNode *node = malloc(sizeof(HuffmanNode));
    if (node == NULL) {
        return NULL;
    }
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}
static void generate_codes(HuffmanNode *root, char code[], int depth)
{
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        if (depth == 0) {
            code[depth++] = '0';
        }
        code[depth] = '\0';
        printf("Character: %c | Code: %s\n", root->character, code);
        return;
    }
    code[depth] = '0';
    generate_codes(root->left, code, depth + 1);
    code[depth] = '1';
    generate_codes(root->right, code, depth + 1);
}
static void free_tree(HuffmanNode *root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
void huffman_coding(const char text[])
{
    if (text == NULL || text[0] == '\0') {
        printf("Empty input.\n");
        return;
    }
    int frequency[256] = {0};
    for (int i = 0; text[i] != '\0'; i++) {
        frequency[(unsigned char)text[i]]++;
    }
    HuffmanNode *nodes[512];
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            nodes[count] = create_node( (unsigned char)i, frequency[i]);
            if (nodes[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free_tree(nodes[j]);
                }
                printf("Memory allocation failed.\n");
                return;
            }
            count++;
        }
    }
    while (count > 1) {
        int first = 0, second = 1;
        if (nodes[first]->frequency > nodes[second]->frequency) {
            int temp = first;
            first = second;
            second = temp;
        }
        for (int i = 2; i < count; i++) {
            if (nodes[i]->frequency < nodes[first]->frequency) {
                second = first;
                first = i;
            } else if (nodes[i]->frequency < nodes[second]->frequency) {
                second = i;
            }
        }
        HuffmanNode *left = nodes[first];
        HuffmanNode *right = nodes[second];
        HuffmanNode *parent = create_node('\0', left->frequency + right->frequency);
        if (parent == NULL) {
            for (int i = 0; i < count; i++) {
                if (i != first && i != second) {
                    free_tree(nodes[i]);
                }
            }
            free_tree(left);
            free_tree(right);
            printf("Memory allocation failed.\n");
            return;
        }
        parent->left = left;
        parent->right = right;
        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }
        nodes[first] = parent;
        for (int i = second; i < count - 1; i++) {
            nodes[i] = nodes[i + 1];
        }
        count--;
    }
    char code[257];
    printf("\nHUFFMAN CODES\n");
    generate_codes(nodes[0], code, 0);
    free_tree(nodes[0]);
}