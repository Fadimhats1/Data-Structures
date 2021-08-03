#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    int num, height;
    node *left, *right;
};

node *createNode(int num){
    node *temp = (node*)malloc(sizeof(node));
    temp->num = num;
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

node *insertNode(node *root, int num){
    if(!root){
        return createNode(num);
    }else if(root->num > num){
        root->left = insertNode(root->left, num);
    }else if(root->num < num){
        root->right = insertNode(root->right, num);
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


node *deleteNode(node *root, int num){
    if(root){
        if(root->num > num){
            root->left = deleteNode(root->left, num);
        }else if(root->num < num){
            root->right = deleteNode(root->right, num);
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
                root->num = temp->num;
                root->left = deleteNode(root->left, temp->num);
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
        printf("%d -> ", root->num);
    }
}

int main(){
    node *root = NULL;

    root = insertNode(root, 9);
    root = insertNode(root, 23);
    root = insertNode(root, 18);
    root = insertNode(root, 48);
    root = insertNode(root, 20);
    root = insertNode(root, 50);
    root = insertNode(root, 19);
    root = insertNode(root, 80);
    root = insertNode(root, 1000);
    root = insertNode(root, 1);
    root = insertNode(root, 34);

    root = deleteNode(root, 18);
    root = deleteNode(root,1000);
    root = deleteNode(root,9);
    root = deleteNode(root,1);
    root = deleteNode(root,19);
    root = deleteNode(root,20);
    root = deleteNode(root,23);
    root = deleteNode(root,34);
    root = deleteNode(root,48);
    root = deleteNode(root,50);
    root = deleteNode(root,80);

    print(root);
}