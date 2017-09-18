#include <bits/stdc++.h>
#include <omp.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
};

struct node* newNode(int data) {
	struct node* Node = new node();

	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;
};

void nodeTraversal(struct node *root) {
	if(root == NULL){
		return;
	}
	// Print from top
	else {
		printf("%d\n",root->data);
		nodeTraversal(root->left);
		nodeTraversal(root->right);
	}
}

int main() {
	struct node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);

	root->left->left = newNode(4);
	root->left->right = newNode(5);

	nodeTraversal(root);

	return 0;
}