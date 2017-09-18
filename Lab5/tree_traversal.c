#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>

typedef struct {
    long node_count;
	float data;
	void *left;
	void *right;
} binary_tree;

binary_tree* tree;
static double Pi = 3.14159265358979;
long number_of_nodes = 10000000;

long _time (void) {
  struct timeval t;

  gettimeofday(&t,NULL);
  return t.tv_sec*1000000+t.tv_usec;
}

// Recursive tree traversal
float SerialTreeTraversal (binary_tree* root) {
    float result = root->data;
    if (root->left)
        result += SerialTreeTraversal (root->left);
    if (root->right)
        result += SerialTreeTraversal (root->right);
    return result;
}

float RecursiveTreeTraversal (binary_tree* root) {
//    float result = root->data;
	float result1 = 0, result2 = 0;
	if  (root->node_count < 1000)
		return SerialTreeTraversal(root);

    if (root->left) {
		#pragma omp task shared(result1,root)
	        result1 =  RecursiveTreeTraversal (root->left);
	}

    if (root->right) {
		#pragma omp task shared(result2,root)
	        result2 = RecursiveTreeTraversal (root->right);
	}

	#pragma omp taskwait

    return root->data + (result1 + result2);
}



binary_tree* CreateASubTree (long number_of_nodes) {
	if (number_of_nodes == 0) {
        return NULL;
    } 
    else {
        binary_tree *node = (binary_tree* ) malloc(sizeof(binary_tree));
        node->node_count = number_of_nodes;
        node->data  = (float)Pi*number_of_nodes;
        
        --number_of_nodes;
        node->left  = CreateASubTree (number_of_nodes/2);
        node->right = CreateASubTree (number_of_nodes - number_of_nodes/2);
        return node;
    }
}

void DeleteATree (binary_tree* node) {
	//
}


void original () {
    float sum;
	long before = _time();
	sum = SerialTreeTraversal (tree);
	long after = _time();

	printf("Serial tree traversal: %f seconds , sum equals %lf\n" , (double) (after-before) / 1000000, sum);
}

void improved () {
    float sum;
	long before = _time();
	sum = RecursiveTreeTraversal (tree);
	long after = _time();
	printf("Parallel tree traversal: %f seconds , sum equals %lf\n" , (double) (after-before) / 1000000, sum);
}

int main (void) {
	tree = (binary_tree* ) malloc(sizeof(binary_tree));
    tree->node_count = number_of_nodes;
    tree->data = (float)Pi*number_of_nodes;

    --number_of_nodes;
	
	tree->left = (binary_tree*) CreateASubTree (number_of_nodes/2);
	tree->right = (binary_tree*)  CreateASubTree (number_of_nodes - number_of_nodes/2);

	original ();
	#pragma omp parallel
		#pragma omp single
		{
		improved ();
		}

	DeleteATree (tree);
	return 0;
}
