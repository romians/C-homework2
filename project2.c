#include <stdio.h>
#include <stdlib.h>
#define size 100

// ����� �Լ��� �̿��� �ݺ��� ��ȸ ��ũ Ʈ�� ����

// Ʈ�� ����ü ����
typedef struct Node {
    int data;
    struct Node* left, * right;
} treenode;

// ���� ����
treenode* stack[size];
int top = -1;

// ���ÿ� Ʈ�� ��带 �ֱ�
void push(treenode* node) {
    if (top < size - 1)
        stack[++top] = node;
}

// ���ÿ��� Ʈ�� ��带 ��������
treenode* pop() {
    if (top >= 0)
        return stack[top--];
    return NULL;
}

// ���� Ʈ�� ��� ���� �Լ�
treenode* createnode(int data) {
    treenode* newnode = (treenode*)malloc(sizeof(treenode));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

// ���� ��ȸ �Լ�
void preorder(treenode* root) {
    if (root == NULL)
        return;

    push(root);

    while (top >= 0) {
        treenode* node = pop();
        printf("%d ", node->data); // ��� ������ ���

        // ������ �ڽĺ��� ���ÿ� �־�� ��
        if (node->right)
            push(node->right);

        // ���� �ڽ� ���ÿ� �ֱ�
        if (node->left)
            push(node->left);
    }
}

void inorder(treenode* root) {
    if (root == NULL)
        return;
    while (root != NULL || top >= 0)
    {
        while (root != NULL)
        {
            push(root);
            root = root->left;
        }
        root = pop();
        printf("%d ", root->data);
        root = root->right;
    }
}

void postorder(treenode* root) {
    if (root == NULL)
        return;
    treenode* prev = NULL;
    do {
        while (root != NULL)
        {
            push(root);
            root = root->left;
        }
        while (root == NULL && top >= 0)
        {
            root = stack[top];
            if (root->right == NULL || root->right == prev) {
                printf("%d ", root->data);
                pop();
                prev = root;
                root = NULL;
            }
            else {
                root = root->right;
            }
        }
    } while (top >= 0);
}

int main() {
    // ���� Ʈ�� ����
    treenode* root = createnode(1);
    root->left = createnode(2);
    root->right = createnode(7);
    // root�� ���� ��� ���� ���ʴ��
    root->left->left = createnode(3);
    root->left->right = createnode(6);
    root->left->left->left = createnode(4);
    root->left->left->right = createnode(5);
    // root�� ������ ��� ���� ���ʴ��
    root->right->left = createnode(8);
    root->right->right = createnode(9);
    root->right->right->left = createnode(10);
    root->right->right->right = createnode(11);

    printf("<Traversal with Stack>\n");
    printf("1. ���� ��ȸ\n");
    preorder(root);
    printf("\n");
    printf("\n");

    printf("2. ���� ��ȸ\n");
    inorder(root);
    printf("\n");
    printf("\n");

    printf("3. ���� ��ȸ\n");
    postorder(root);
    printf("\n");

    free(root);

    return 0;
}