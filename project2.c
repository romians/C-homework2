#include <stdio.h>
#include <stdlib.h>
#define size 100

// 재귀적 함수를 이용한 반복적 순회 링크 트리 구현

// 트리 구조체 정의
typedef struct Node {
    int data;
    struct Node* left, * right;
} treenode;

// 스택 선언
treenode* stack[size];
int top = -1;

// 스택에 트리 노드를 넣기
void push(treenode* node) {
    if (top < size - 1)
        stack[++top] = node;
}

// 스택에서 트리 노드를 가져오기
treenode* pop() {
    if (top >= 0)
        return stack[top--];
    return NULL;
}

// 이진 트리 노드 생성 함수
treenode* createnode(int data) {
    treenode* newnode = (treenode*)malloc(sizeof(treenode));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

// 전위 순회 함수
void preorder(treenode* root) {
    if (root == NULL)
        return;

    push(root);

    while (top >= 0) {
        treenode* node = pop();
        printf("%d ", node->data); // 노드 데이터 출력

        // 오른쪽 자식부터 스택에 넣어야 함
        if (node->right)
            push(node->right);

        // 왼쪽 자식 스택에 넣기
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
    // 이진 트리 생성
    treenode* root = createnode(1);
    root->left = createnode(2);
    root->right = createnode(7);
    // root의 왼쪽 노드 부터 차례대로
    root->left->left = createnode(3);
    root->left->right = createnode(6);
    root->left->left->left = createnode(4);
    root->left->left->right = createnode(5);
    // root의 오른쪽 노드 부터 차례대로
    root->right->left = createnode(8);
    root->right->right = createnode(9);
    root->right->right->left = createnode(10);
    root->right->right->right = createnode(11);

    printf("<Traversal with Stack>\n");
    printf("1. 전위 순회\n");
    preorder(root);
    printf("\n");
    printf("\n");

    printf("2. 중위 순회\n");
    inorder(root);
    printf("\n");
    printf("\n");

    printf("3. 후위 순회\n");
    postorder(root);
    printf("\n");

    free(root);

    return 0;
}