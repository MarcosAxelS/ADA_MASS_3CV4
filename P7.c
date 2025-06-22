#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_CHARS 27

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node* nodes[NUM_CHARS];
    int size;
} PriorityQueue;

char* codes[NUM_CHARS];
char buffer[10000];

int char_a_indice(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c == ' ') return 26;
    return -1;
}

char indice_a_char(int i) {
    return (i == 26) ? ' ' : 'A' + i;
}

void pq_push(PriorityQueue *pq, Node* node) {
    pq->nodes[pq->size++] = node;
    for (int i = pq->size - 1; i > 0 && pq->nodes[i]->freq < pq->nodes[i - 1]->freq; --i) {
        Node* tmp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[i - 1];
        pq->nodes[i - 1] = tmp;
    }
}

Node* pq_pop(PriorityQueue *pq) {
    return pq->nodes[--pq->size];
}

Node* create_node(char ch, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

Node* build_huffman_tree(int freq[]) {
    PriorityQueue pq = { .size = 0 };
    for (int i = 0; i < NUM_CHARS; i++) {
        if (freq[i]) {
            pq_push(&pq, create_node(indice_a_char(i), freq[i]));
        }
    }
    while (pq.size > 1) {
        Node *left = pq_pop(&pq), *right = pq_pop(&pq);
        Node *parent = create_node(0, left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq_push(&pq, parent);
    }
    return pq_pop(&pq);
}

void generate_codes(Node* root, char* code, int depth) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        codes[char_a_indice(root->ch)] = strdup(code);
        return;
    }
    code[depth] = '0';
    generate_codes(root->left, code, depth + 1);
    code[depth] = '1';
    generate_codes(root->right, code, depth + 1);
}

void guardar_diccionario() {
    FILE* dic = fopen("diccionario.txt", "w");
    for (int i = 0; i < NUM_CHARS; i++) {
        if (codes[i]) {
            fprintf(dic, "%c %s\n", indice_a_char(i), codes[i]);
        }
    }
    fclose(dic);
}

void compress_text(const char* text, FILE* out, int* original_bits, int* compressed_bits) {
    for (int i = 0; text[i]; i++) {
        char c = text[i];
        if (islower(c)) c = toupper(c);
        int idx = char_a_indice(c);
        if (idx != -1) {
            char* code = codes[idx];
            fprintf(out, "%s", code);
            *original_bits += 8;
            *compressed_bits += strlen(code);
        }
    }
}

void decode_text(FILE* in, FILE* out, Node* root) {
    Node* current = root;
    char bit;
    while ((bit = fgetc(in)) != EOF) {
        if (bit == '0') current = current->left;
        else if (bit == '1') current = current->right;
        if (!current->left && !current->right) {
            fputc(current->ch, out);
            current = root;
        }
    }
}

void free_tree(Node* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    FILE *in = fopen("entrada.txt", "r");
    if (!in) return 1;

    int freq[NUM_CHARS] = {0};
    char ch;
    int index = 0;

    while ((ch = fgetc(in)) != EOF) {
        if (islower(ch)) ch = toupper(ch);
        int idx = char_a_indice(ch);
        if (idx != -1) {
            buffer[index++] = ch;
            freq[idx]++;
        }
    }
    buffer[index] = '\0';
    fclose(in);

    Node* root = build_huffman_tree(freq);
    char temp_code[100];
    generate_codes(root, temp_code, 0);
    guardar_diccionario();

    int original_bits = 0, compressed_bits = 0;
    FILE* out = fopen("codificado.txt", "w");
    compress_text(buffer, out, &original_bits, &compressed_bits);
    fclose(out);

    printf("Tamaño original: %d bits\n", original_bits);
    printf("Tamaño codificado: %d bits\n", compressed_bits);
    printf("Tasa de compresión: %.2f%%\n", (100.0 * compressed_bits) / original_bits);

    FILE* encoded = fopen("codificado.txt", "r");
    FILE* decoded = fopen("decodificado.txt", "w");
    decode_text(encoded, decoded, root);
    fclose(encoded);
    fclose(decoded);

    for (int i = 0; i < NUM_CHARS; i++) {
        free(codes[i]);
    }
    free_tree(root);
    return 0;
}
