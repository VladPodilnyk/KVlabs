#include "TreeNode.h"

CTreeNode::CTreeNode(const CTreeNode *obj) {
	m_TrainNumber = obj->m_TrainNumber;
	m_TrainDestination = obj->m_TrainDestination;
	m_TrainDepartureTime = obj->m_TrainDepartureTime;
}

CTreeNode& CTreeNode::operator=(const CTreeNode &obj) {
	if (this != &obj) {
		m_TrainNumber = obj.m_TrainNumber;
		m_TrainDestination = obj.m_TrainDestination;
		m_TrainDepartureTime = obj.m_TrainDepartureTime;
	}
	return *this;
}