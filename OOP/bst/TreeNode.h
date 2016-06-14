#pragma once
#include <iostream>
#include <stdio.h>

using namespace std;

class CTreeNode {
	int m_TrainNumber;
	std::string m_TrainDestination;
	std::string m_TrainDepartureTime;
	CTreeNode *left;
	CTreeNode *right;
public:
	CTreeNode() {};
	CTreeNode(int num, std::string dest, std::string time) : m_TrainNumber(num),
		m_TrainDestination(dest), m_TrainDepartureTime(time) { left = NULL; right = NULL; };
	CTreeNode(const CTreeNode *obj);
	CTreeNode& operator=(const CTreeNode &obj);
	int Get_id() { return m_TrainNumber; };
	std::string Get_destination() { return m_TrainDestination; };
	std::string Get_time() { return m_TrainDepartureTime; };
	CTreeNode* node_left() { return left; };
	CTreeNode* node_right() { return right; };
	void set_node_left(CTreeNode *node) { left = node; };
	void set_node_right(CTreeNode *node) { right = node; };
	void set_id(int train_number) { m_TrainNumber = train_number; };
	void set_destination(std::string destination) { m_TrainDestination = destination; };
	void set_time(std::string time) { m_TrainDepartureTime = time; };
};

