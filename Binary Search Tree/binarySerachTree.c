#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binarySearchTree.h"

BST_TREE* bstCreate() {
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));

	if (tree == NULL) {
		return NULL;
	}

	tree->count = -1;
	tree->root = NULL;

	return tree;
}

void bstDestroy(BST_TREE* tree) {

	if (tree->root != NULL) {
		_bstDestroy(tree->root);
	}

	free(tree);

}
static void _bstDestroy(TREE_NODE* root) {

	if (root != NULL) {
		_bstDestroy(root->left);
		_bstDestroy(root->right);
	}

	free(root);
}
bool bstInsert(BST_TREE* tree, int data) {

	TREE_NODE* newPtr = NULL;

	newPtr = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	if (!newPtr) {
		return false;
	}
	newPtr->right = newPtr->left = NULL;
	newPtr->data = data;

	if (tree->count == -1) {
		tree->root = newPtr;
	}
	else {
		_bstInsert(tree->root, newPtr);
	}

	tree->count++;
	return true;
}

static TREE_NODE* _bstInsert(TREE_NODE* root, TREE_NODE* newNode) {
	if (!root) {
		return newNode;
	}

	if (root->data < newNode->data) {
		root->right = _bstInsert(root->right, newNode);
		return root;
	}
	else {
		root->left = _bstInsert(root->left, newNode);
		return root;
	}

	return root;
}

bool bstDelete(BST_TREE* tree, int key) {
	if (!tree->root) {
		return false;
	}

	_bstDelete(tree->root, key);
	return true;
}

static TREE_NODE* _bstDelete(TREE_NODE* root, int key) {
	if (!root) {
		return root;
	}

	TREE_NODE* delPtr = NULL;

	if (root->data < key) {
		root->left = _bstDelete(root->left, key);
	}
	else if (root->data > key) {
		root->right = _bstDelete(root->right, key);
	}
	else {
		if (!root->right) {
			delPtr = root;
			root = root->left;
			free(delPtr);
			return root;
		}
		else if (!root->left) {
			delPtr = root;
			root = root->right;
			free(delPtr);
			return root;
		}
		else {
			for (delPtr = root->left; delPtr->right != NULL; delPtr = delPtr->right);
			root->data = delPtr->data;
			root->left = _bstDelete(root->left, delPtr->data);
		}
	}

	return root;

}
TREE_NODE* bstSearch(BST_TREE* tree, int key) {
	if (!tree) {
		return NULL;
	}

	TREE_NODE* root = tree->root;

	return _bstSearch(root, key);
}

static TREE_NODE* _bstSearch(TREE_NODE* root, int key) {

	if (!root) {
		return NULL;
	}

	if (key < root->data) {
		return _bstSearch(root->left, key);
	}
	else if (key > root->data) {
		return _bstSearch(root->right, key);
	}
	else return root;
}
bool bstEmpty(BST_TREE* tree) {
	return tree->count == -1 ? true : false;
}
int bstCount(BST_TREE* tree) {
	return tree->count;
}