#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode
{
	int data;
	struct treeNode* left;
	struct treeNode* right;
} TREE_NODE;
typedef struct
{
	int count;
	TREE_NODE* root;
} BST_TREE;

BST_TREE* bstCreate();
void bstDestroy(BST_TREE* tree);
static void _bstDestroy(TREE_NODE* root);
bool bstInsert(BST_TREE* tree, int data);
static TREE_NODE* _bstInsert(TREE_NODE* root, TREE_NODE* newNode);
bool bstDelete(BST_TREE* tree, int key);
static TREE_NODE* _bstDelete(TREE_NODE* root, int key);
TREE_NODE* bstSearch(BST_TREE* tree, int key);
static TREE_NODE* _bstSearch(TREE_NODE* root, int key);
bool bstEmpty(BST_TREE* tree);
int bstCount(BST_TREE* tree);