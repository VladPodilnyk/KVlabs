#include "BinTree.h"

CTreeNode* CBinTree::insert(CTreeNode *node, CTreeNode *obj) {
	if (node == NULL) {
		node = obj;
		return node;
	}

	if (obj->Get_id() < node->Get_id())
		node->set_node_left(insert(node->node_left(), obj));
	else if (obj->Get_id() > node->Get_id())
		node->set_node_right(insert(node->node_right(), obj));

	return node;
}

bool CBinTree::load_from_file(const std::string &file_name) {
	std::ifstream flow(file_name);
	std::vector<std::string> data;
	std::string item;
	CTreeNode *newNode;
	if (flow.is_open()) {
		while (std::getline(flow, item, ';')) {
			data.push_back(item);
			std::getline(flow, item, ';');
			data.push_back(item);
			std::getline(flow, item);
			data.push_back(item);
			newNode = new CTreeNode(stoi(data[0]), data[1], data[2]);
			data.clear();
			root = insert(root, newNode);
		}
		flow.close();
		return 1;
	}
	else
		flow.close();
		return 0;
}

void CBinTree::print(CTreeNode *root) {
	if (root != NULL) {
		print(root->node_left());
		std::cout << "Train number: " << root->Get_id() << std::endl;
		std::cout << "Destination: " << root->Get_destination() << std::endl;
		std::cout << "Departure time: " << root->Get_time() << "\n\n\n";
		print(root->node_right());
	}
}


void CBinTree::print() {
	print(root);
}


CTreeNode* CBinTree::search(CTreeNode *node, int id) {
	if (node == NULL)
		return NULL;
	else if (node->Get_id() == id)
		return node;

	if (id < node->Get_id())
		return search(node->node_left(), id);
	return search(node->node_right(), id);
}


void CBinTree::train_info(int id) {
	CTreeNode *train;
	train = search(root, id);
	if (train == NULL) {
		std::cout << "Train with entered id does not exist.\n" << std::endl;
		return;
	}
	std::cout << "Train number: " << train->Get_id() << std::endl;
	std::cout << "Destination: " << train->Get_destination() << std::endl;
	std::cout << "Departure time: " << train->Get_time() << "\n\n\n";
	return;
}


void CBinTree::print(CTreeNode *root, std::string station_name) {
	if (root != NULL) {
		print(root->node_left(), station_name);
		if (root->Get_destination() == station_name) {
			std::cout << "Train number: " << root->Get_id() << std::endl;
			std::cout << "Destination: " << root->Get_destination() << std::endl;
			std::cout << "Departure time: " << root->Get_time() << "\n\n\n";
		}
		print(root->node_right(), station_name);
	}
}

void CBinTree::station_info(std::string station_name) {
	print(root, station_name);
}


CTreeNode* CBinTree::search_min(CTreeNode *root) {
	CTreeNode *min = root;
	while (min->node_left() != NULL)
		min = min->node_left();
	return min;

}

CTreeNode* CBinTree::delete_node(CTreeNode *root, int id) {
	CTreeNode *temporary;
	if (root == NULL) return root;

	if (id < root->Get_id())
		root->set_node_left(delete_node(root->node_left(), id));
	else if (id > root->Get_id())
		root->set_node_right(delete_node(root->node_right(), id));

	else {
		if (root->node_left() == NULL) {
			temporary = root->node_right();
			free(root);
			return temporary;
		}

		if (root->node_right() == NULL) {
			temporary = root->node_left();
			free(root);
			return temporary;
		}

		temporary = search_min(root->node_right());
		root->set_id(temporary->Get_id());
		root->set_destination(temporary->Get_destination());
		root->set_time(temporary->Get_time());

		root->set_node_right(delete_node(root->node_right(), temporary->Get_id()));

	}
	return root;
}

void CBinTree::delete_route(int id) {
	root = delete_node(root, id);
}