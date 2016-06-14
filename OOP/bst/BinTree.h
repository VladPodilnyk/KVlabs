#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "TreeNode.h"

using namespace std;

class CBinTree {
	CTreeNode *root;
	CTreeNode* insert(CTreeNode *root, CTreeNode *obj);
	CTreeNode* search(CTreeNode *root, int id);
	void print(CTreeNode *root, std::string station_name);
	CTreeNode* delete_node(CTreeNode *root, int id);
	CTreeNode* search_min(CTreeNode *root);
	void print(CTreeNode *root);
public:
	CBinTree() { root = NULL; };
	bool load_from_file(const std::string &file_name);
	void print();
	void train_info(int id);
	void station_info(std::string station_name);
	void delete_route(int id);
};

