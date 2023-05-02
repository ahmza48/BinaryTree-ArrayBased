#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

template <typename T>
class ArrayBinaryTree {
private:
	T * data;
	int maxHeight;
	int maxNodes; //This is actually Array capacity
	bool * nodeStatus;
	void VLR(int i) {
		
		if (nodeStatus[i]) {
			cout << data[i] << " ";
		}
		if (2 * i + 1 < maxNodes && nodeStatus[2 * i + 1] != false) {
			VLR(2 * i + 1);
		}
		if (2 * i + 2 < maxNodes && nodeStatus[2 * i + 2] != false) {
			VLR(2 * i + 2);
		}
	}
	int search(T key,int i) {
		int res = -1;
		if (data[i] == key) {
			res = i;
		}
		if (res == -1 && 2 * i + 1 < maxNodes && nodeStatus[2 * i + 1] != false) {
			res = search(key, 2 * i + 1);
		}
		if (res == -1 && 2 * i + 2 < maxNodes && nodeStatus[2 * i + 2] != false) {
			res = search(key, 2 * i + 2);
		}
		return res;

	}
public:
	ArrayBinaryTree();
	ArrayBinaryTree(int height) {
		maxHeight = height;
		maxNodes = pow(2, maxHeight) - 1;
		data = new T[maxNodes];
		nodeStatus = new bool[maxNodes];
		for (int i = 0; i < maxNodes; i++)
		{
			nodeStatus[i] = false;
		}
	}
	void setRoot(T root) {
		/*if (nodeStatus[0] == false)
		{
			data[0] = root;
			nodeStatus[0] = true;
			return;
		}*/

		//If there is already some root available it will over-write that
		data[0] = root;
		nodeStatus[0] = true;

	}
	void setLeftChild(T par, T ch) {
		int index = search(par, 0);
		if (index == -1) {
			return;
		}
		if (2 * index + 1 < maxNodes) {
			data[2 * index + 1] = ch;
			nodeStatus[2 * index + 1] = true;
		}
	}
	void setRightChild(T par, T ch) {
		int index = search(par, 0);
		if (index == -1) {
			return;
		}
		if (2 * index + 2 < maxNodes) {
			data[2 * index + 2] = ch;
			nodeStatus[2 * index + 2] = true;
		}
	}
	void preOrder() {
		VLR(0);
	}
	void displayDescendents(T node) {
		int ind = search(node, 0);
		if (ind == -1) {
			return;
		}
		if (2 * ind + 1 < maxNodes && nodeStatus[2 * ind + 1] != false)
		{
			VLR(2 * ind + 1);
		}
		if (2 * ind + 2 < maxNodes && nodeStatus[2 * ind + 2] != false)
		{
			VLR(2 * ind + 2);
		}
		else {
			cout << "NO Descendents!" << endl;
		}
	}
	int getHeight(int i) {
		if (i < maxNodes) {
			int leftHeight = 0, rightHeight = 0;
			if (2 * i + 1 < maxNodes && nodeStatus[2 * i + 1] != false) {
				leftHeight = getHeight(2 * i + 1);
			}
			if (2 * i + 2 < maxNodes && nodeStatus[2 * i + 2] != false) {
				rightHeight = getHeight(2 * i + 2);
			}
			if (leftHeight > rightHeight)
			{
				return leftHeight + 1;
			}
			else {
				return rightHeight + 1;
			}
		}
		else {
			return 0;
		}

	}

	T getParent(T ch) {
		int ind = search(ch, 0);
		cout << "CHILD INDEX: " << ind << endl;
		if (ind == -1) {
			cout << "Root Node Does Not have any Parent!" << endl;
			return '-1';
		}
		if (ind == 0) {
			return data[0];
		}
		if (ind % 2 != 0) {
			ind = (ind - 1) / 2;
			return data[ind];
		}
		if (ind % 2 == 0) {
			ind = (ind - 2) / 2;
			return data[ind];
		}
	}
	//This should also remove all its childs as well
	void remove(T node) {
		if (nodeStatus[0] == false) {
			return;
		}
		int ind = search(node, 0);
		if (ind == -1) {
			cout << "Root Node Does Not have any Child!" << endl;
			return;
		}
		removeWithDescendents(ind);

	}
	void removeWithDescendents(int i){
		
		if (nodeStatus[i] == true) {
			nodeStatus[i] = false;
		}
		if (2 * i + 1 < maxNodes && nodeStatus[2 * i + 1] != false) {
			removeWithDescendents(2 * i + 1);
		}
		if (2 * i + 2 < maxNodes && nodeStatus[2 * i + 2] != false) {
			removeWithDescendents(2 * i + 2);
		}
	}
	void levelOrderTraversal(int i) {
		queue<T> q;
		if (nodeStatus[i]) {
			q.push(data[i]);
		}
		while (!q.empty())
		{
			T val = q.front();
			q.pop();
			cout << val << " ";
			if (2 * i + 1 < maxNodes && nodeStatus[2 * i + 1] != false) {
				q.push(data[2 * i + 1]);
			}
			if (2 * i + 2 < maxNodes && nodeStatus[2 * i + 2] != false) {
				q.push(data[2 * i + 2]);
			}
			i++;

		}

	}
	void displayLevel(int levelNo) {
		if (levelNo == 0) {
			if (nodeStatus[0] != false) {
				cout << data[0] << endl;
				return;
			}
		}
		int index = (pow(2, levelNo)) - 1;
		
		if (nodeStatus[index] == true || nodeStatus[index] == false) {
			for (int i = 0; i < pow(2, levelNo); i++)
			{
				if (nodeStatus[index] != false) {
					cout << data[index] << " ";
					/*index += 1;*/
				}
				index += 1;
			}
		}
		else {
			cout << "LEVEL DOES NOT EXIST" << endl;
			return;
		}
		 
	}
	int getLevelOfNode(T node) {
		int index = search(node, 0);
		if (index == 0) {
			return 0;
		}
		if (index == -1) {
			cout << "Node Does Not Exist!" << endl;
			return -1;
		}
		int level;
		if (index % 2 == 0) {
			level = int(log2(index));
		}
		if (index % 2 != 0) {
			level = int(log2(index + 1));
		}
		return level;
	}

};


int main() {
	ArrayBinaryTree<char> t(3);
	t.setRoot('A');
	t.setLeftChild('A', 'X');
	t.setRightChild('A', 'Y');
	t.setLeftChild('Y', 'Z');
	//t.setRightChild('Y', 'W');
	cout << "Pre-Order:" << endl;
	t.preOrder();
	cout << endl;
	cout << "Level-Order:" << endl;
	t.levelOrderTraversal(0);
	cout << endl;
	cout << "Displaying Level 2: " << endl;
	t.displayLevel(2);
	cout << endl;
	cout << "Parent of A:" << endl;
	cout << t.getParent('A') << endl;
	cout << endl;
	cout << t.getHeight(0);
	cout << endl;
	cout << "LEVEL OF NODE IS: ";
	cout << t.getLevelOfNode('Y');
	return 0;
}