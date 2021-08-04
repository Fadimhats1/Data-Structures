#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct subNode{
    char str[255];
    int height;
    subNode *left, *right;
};

struct node{
    char str[255];
    int height;
    subNode *root;
    node *left, *right;
};

int max(int a, int b){
    return a > b ? a : b;
}

// SUB NODE

int getHeightSubNode(subNode *root){
    return root ? root->height : 0;
}

int bFactorSubNode(subNode *root){
    return root ? getHeightSubNode(root->left) - getHeightSubNode(root->right) : 0;
}

subNode *createSubNode(char str[]){
    subNode *temp = (subNode*)malloc(sizeof(subNode));
    strcpy(temp->str, str);
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

subNode *rightRotateSubNode(subNode *root){
    subNode *temp = root->left, *pivot = temp->right;

    temp->right = root;
    root->left = pivot;

    root->height = 1 + max(getHeightSubNode(root->left), getHeightSubNode(root->right));
    temp->height = 1 + max(getHeightSubNode(temp->left), getHeightSubNode(temp->right));

    return temp;
}

subNode *leftRotateSubNode(subNode *root){
    subNode *temp = root->right, *pivot = temp->left;
    
    temp->left = root;
    root->right = pivot;

    root->height = 1 + max(getHeightSubNode(root->left), getHeightSubNode(root->right));
    temp->height = 1 + max(getHeightSubNode(temp->left), getHeightSubNode(temp->right));

    return temp;
}

subNode *rotationSubNode(subNode *root){
    root->height = 1 + max(getHeightSubNode(root->left), getHeightSubNode(root->right));
    int balance = bFactorSubNode(root);

    if(balance > 1){
        if(bFactorSubNode(root->left) < 0){
            root->left = leftRotateSubNode(root->left);
        }
        return rightRotateSubNode(root);
    }else if(balance < -1){
        if(bFactorSubNode(root->right) > 0){
            root->right = rightRotateSubNode(root->right);
        }
        return leftRotateSubNode(root);
    }
    return root;
}

subNode *insertSubNode(subNode *root, char str[]){
    if(!root){
        return createSubNode(str);
    }else if(strcmp(root->str, str) > 0){
        root->left = insertSubNode(root->left, str);
    }else if(strcmp(root->str, str) < 0){
        root->right = insertSubNode(root->right, str);
    }
    return rotationSubNode(root);
}

subNode *travSubNode(subNode *root){
    subNode *curr = root;
    while(curr && curr->right){
        curr = curr->right;
    }
    return curr;
}

subNode *deleteSubNode(subNode *root, char str[]){
    if(root){
        if(strcmp(root->str, str) > 0){
            root->left = deleteSubNode(root->left, str);
        }else if(strcmp(root->str, str) < 0){
            root->right = deleteSubNode(root->right, str);
        }else{
            subNode *temp = NULL;
            if(!(root->left)){
                temp = root->right;
                root->right = NULL;
                free(root);
                return temp;
            }else if(!(root->right)){
                temp = root->left;
                root->left = NULL;
                free(root);
                return temp;
            }else{
                temp = travSubNode(root->left);
                strcpy(root->str, temp->str);
                root->left = deleteSubNode(root->left, temp->str);
            }
        }
        return rotationSubNode(root);
    }
}

// MAIN NODE

int getHeightNode(node *root){
    return root ? root->height : 0;
}

int bFactorNode(node *root){
    return root ? getHeightNode(root->left) - getHeightNode(root->right) : 0;
}

node *createNode(char str[]){
    node *temp = (node*)malloc(sizeof(node));
    strcpy(temp->str, str);
    temp->root = NULL;
    temp->height = 1;
    temp->right = temp->left = NULL;
    return temp;
}

node *rightRotateNode(node *root){
    node *temp = root->left, *pivot = temp->right;
    
    temp->right = root;
    root->left = pivot;

    root->height = 1 + max(getHeightNode(root->left), getHeightNode(root->right));
    temp->height = 1 + max(getHeightNode(temp->left), getHeightNode(root->right));

    return temp;
}

node *leftRotateNode(node *root){
    node *temp = root->right, *pivot = temp->left;

    temp->left = root;
    root->right = pivot;

    root->height = 1 + max(getHeightNode(root->left), getHeightNode(root->right));
    temp->height = 1 + max(getHeightNode(temp->left), getHeightNode(temp->right));
    
    return temp;
}

node *rotationNode(node *root){
    root->height = 1 + max(getHeightNode(root->left), getHeightNode(root->right));
    int balance = bFactorNode(root);

    if(balance > 1){
        if(bFactorNode(root->left) < 0){
            root->left = leftRotateNode(root->left);
        }
        return rightRotateNode(root);
    }else if(balance < -1){
        if(bFactorNode(root->right) > 0){
            root->right = rightRotateNode(root->right);
        }
        return leftRotateNode(root);
    }
    return root;
}

// MAIN NODE

node *insertNode(node *root, char str1[], char str2[]){
    if(!root){
        node *temp = createNode(str1);
        temp->root = insertSubNode(temp->root, str2);
        return temp;
    }else if(strcmp(root->str, str1) > 0){
        root->left = insertNode(root->left, str1, str2);
    }else if(strcmp(root->str, str1) < 0){
        root->right = insertNode(root->right, str1, str2);
    }else if(strcmp(root->str, str1) == 0){
        root->root = insertSubNode(root->root, str2);
        return root;
    }
    return rotationNode(root);
}

node *travNode(node *root){
    node *curr = root;
    while(curr && curr->right){
        curr = curr->right;
    }
    return curr;
}

node *deleteNode(node *root, char str[]){
    if(root){
        if(strcmp(root->str, str) > 0){
            root->left = deleteNode(root->left, str);
        }else if(strcmp(root->str, str) < 0){
            root->right = deleteNode(root->right, str);
        }else{
            node *temp = NULL;
            if(!(root->left)){
                temp = root->right;
                root->right = NULL;
                free(root);
                return temp;
            }else if(!(root->right)){
                temp = root->left;
                root->left = NULL;
                free(root);
                return temp;
            }else{
                temp = travNode(root->left);
                strcpy(root->str, temp->str);
                root->root = temp->root;
                root->left = deleteNode(root->left, temp->str);
            }
        }
        return rotationNode(root);
    }else{
        return root;
    }
}

void printSubNode(subNode *root){
    if(root){
        printSubNode(root->left);
        printSubNode(root->right);
        printf("%s -> ", root->str);
    }
}

void printNode(node *root){
    if(root){
        printNode(root->left);
        printNode(root->right);
        printf("Node: ");
        printf("%s -> ", root->str);
        printf("SubNode: ");
        printSubNode(root->root);
        printf("\n");
    }
}

int main(){
    node *root = NULL;

    root = insertNode(root, "D", "Ayam");
    root = insertNode(root, "A", "Bebek");
    root = insertNode(root, "V", "Ikan");
    root = insertNode(root, "R", "Sapi");
    root = insertNode(root, "T", "Harimau");
    root = insertNode(root, "C", "Ular");
    root = insertNode(root, "I", "Monyet");
    root = insertNode(root, "O", "Kura-kura");
    root = insertNode(root, "F", "Kepiting");
    root = insertNode(root, "B", "Kucing");
    root = insertNode(root, "G", "Anjing");
    root = insertNode(root, "D", "Ikan");
    root = insertNode(root, "D", "Banteng");
    root = insertNode(root, "D", "Naga");
    root = insertNode(root, "C", "Kamu");
    root = insertNode(root, "C", "Dia");
    root = insertNode(root, "C", "Aku");
    
    printNode(root);
    puts("");

    root = deleteNode(root, "D");
    // root = deleteNode(root, "B");
    // root = deleteNode(root, "V");
    // root = deleteNode(root, "R");

    printNode(root);
}