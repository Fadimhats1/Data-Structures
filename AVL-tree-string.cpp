#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char str[255];
    int height;
    node *left, *right;
};

node *createNode(char str[]){
    node *temp = (node*)malloc(sizeof(node));
    strcpy(temp->str, str);
    temp->height = 1;
    temp->right = temp->left = NULL;
    return temp;
}

int max(int a, int b){
    return a > b ? a : b;
}

int getHeight(node *root){
    return root ? root->height : 0;
}

int bFactor(node *root){
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

node *rightRotate(node *root){
    node *temp = root->left, *pivot = temp->right;
    
    temp->right = root;
    root->left = pivot;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    temp->height = 1 + max(getHeight(temp->left), getHeight(root->right));

    return temp;
}

node *leftRotate(node *root){
    node *temp = root->right, *pivot = temp->left;

    temp->left = root;
    root->right = pivot;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
    
    return temp;
}

node *rotation(node *root){
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = bFactor(root);

    if(balance > 1){
        if(bFactor(root->left) < 0){
            root->left = leftRotate(root->left);
        }
        return rightRotate(root);
    }else if(balance < -1){
        if(bFactor(root->right) > 0){
            root->right = rightRotate(root->right);
        }
        return leftRotate(root);
    }
    return root;
}

node *insertNode(node *root, char str[]){
    if(!root){
        return createNode(str);
    }else if(strcmp(root->str, str) > 0){
        root->left = insertNode(root->left, str);
    }else if(strcmp(root->str, str) < 0){
        root->right = insertNode(root->right, str);
    }
    return rotation(root);
}

node *traverse(node *root){
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
                temp = traverse(root->left);
                strcpy(root->str, temp->str);
                root->left = deleteNode(root->left, temp->str);
            }
        }
        return rotation(root);
    }else{
        return root;
    }
}


void print(node *root){
    if(root){
        print(root->left);
        print(root->right);
        printf("%s -> ", root->str);
    }
}

int main(){
    node *root = NULL;

    root = insertNode(root, "D");
    root = insertNode(root, "A");
    root = insertNode(root, "V");
    root = insertNode(root, "R");
    root = insertNode(root, "T");
    root = insertNode(root, "C");
    root = insertNode(root, "I");
    root = insertNode(root, "O");
    root = insertNode(root, "F");
    root = insertNode(root, "B");
    root = insertNode(root, "G");

    root = deleteNode(root, "A");
    root = deleteNode(root, "B");
    root = deleteNode(root, "V");
    root = deleteNode(root, "R");

    print(root);
}