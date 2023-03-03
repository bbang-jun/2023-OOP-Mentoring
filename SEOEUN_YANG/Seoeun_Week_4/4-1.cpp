#include <iostream>
using namespace std;

class Node {//��� Ŭ���� ����
private:
	int data;//�����Ͱ�
	Node* leftChild;
	Node* rightChild;
	Node* parent;

public:
	Node() {//�ڵ�������
		this->data = 0;//�ʱ�ȭ
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}

	void setData(int data) { this->data = data; }//������
	int getData() { return this->data; }
	void setParent(Node* nextNode) { this->parent = nextNode; }//�θ� ��� //currentNode, parent�� ����
	Node* getParent() { return this->parent; }
	void setLeftChild(Node* leftChild) { this->leftChild = leftChild; }//�ڽ� ���
	Node* getLeftChild() { return this->leftChild; }
	void setRightChild(Node* rightChild) { this->rightChild = rightChild; }
	Node* getRightChild() { return this->rightChild; }
};

class Tree {//tree Ŭ���� ����
private:
	Node* root;//�ֻ� ���
	Node* parent;//�θ� ���
	int size;//tree ����
public:
	Tree() {//�ڵ�������
		this->root = NULL;//�ʱ�ȭ
		this->parent = NULL;
		this->size = 0;
	}
	~Tree() {//���� �Ҵ� ���� (��� ����)
		deallocate(root);
	}
	
	Node* getRoot() { return root; }//***
	void INSERT(Node* curNode, int data);//���
	void DELETE(int data);
	void FIND(Node* curNode, int data);//����ϸ鼭 ��� (������ȸ ���)//��� root ������ ����
	void PRINT_PRE(Node* curNode);
	void PRINT_IN(Node* curNode);
	void PRINT_POST(Node* curNode);
	void PRINT_LEAF(Node* curNode);//����Ʈ �ϳ� �����鼭 �ڽ� ��� ���� ���� ���
	void deallocate(Node* curNode);//������ȸ ���
};

void Tree::INSERT(Node* curNode, int data) {//����//�ϴ� curNode = root
	if (root == NULL) {//��Ʈ ��尡 ���� ��� (ù ���� (���� �ߺ� ���ɼ� ����))
		Node* newNode = new Node;
		newNode->setData(data);//����� ������ ����
		root = newNode; //���� ��� = root
		this->size++;
	}
	else if (curNode->getData() > data) {//���� �̵�
		if (curNode->getLeftChild() == NULL) {//���� ���� X -> ���ʿ� ����
			Node* newNode = new Node;
			newNode->setData(data);
			curNode->setLeftChild(newNode);
			this->size++;
		}
		else {//���� ���� O -> curNode ���� �ڽ����� �̵��� INSERT �Լ� �ٽ� ���� //**���
			if (curNode->getLeftChild()->getData() == data)
				return;//�ߺ� ����
			INSERT(curNode->getLeftChild(), data);//INSERT �Լ� �ٽ� ����
		}
	}
	else if (curNode->getData() < data) {//������ �̵�
		if (curNode->getRightChild() == NULL) {//������ ���� X -> �����ʿ� ����
			Node* newNode = new Node;
			newNode->setData(data);
			curNode->setRightChild(newNode);
			this->size++;
		}
		else {//������ ���� 0 -> curNode ������ �ڽ����� �̵��� INSERT �Լ� �ٽ� ����
			if (curNode->getRightChild()->getData() == data)
				return;//�ߺ� ����
			INSERT(curNode->getRightChild(), data);
		}
	}
}

void Tree::DELETE(int data) {
	Node* curNode = root;
	Node* delNode = NULL;
	Node* tempNode = NULL;

	while (1) {//��� Ž��
		if (curNode->getData() < data) {//������
			parent = curNode;
			curNode = curNode->getRightChild();
		}
		else if (curNode->getData() > data) {//����
			parent = curNode;
			curNode = curNode->getLeftChild();
		}
		else//�����Ͱ� ���� (��� Ž�� ��)
			break;//�����Ͱ� ���� ��� curNode�� �����ؼ� while�� ��������
	}

	//child�� 0���� node�� ������ ���(leaf node�� ������ ���)
	if (curNode->getLeftChild() == NULL && curNode->getRightChild() == NULL) {
		if (curNode == root) {//������ ��� = root
			delete root;
			root = NULL;//�����Ⱚ ����
			return;
		}
		else {//�� leaf ���
			if (parent->getLeftChild() == curNode) {//Ž���ϸ鼭 parent �� �����ϱ� ������ �ٷ� ��� ����
				delete curNode;
				curNode = NULL;//�����Ⱚ ����
				parent->setLeftChild(NULL);//�θ� ������ ���� ����
				return;
			}
			else if (parent->getRightChild() == curNode) {
				delete curNode;
				curNode = NULL;//�����Ⱚ ����
				parent->setRightChild(NULL);
				return;
			}
		}
	}

	//child�� 1���� node�� ������ ���
	else if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL) {//child 2���� ���⼭ ���ư��� ���� (0���� �̹� ���� if���� �� ���ư�)
		if (curNode == root) {//������ ��� = root
			if (root->getLeftChild() != NULL) {//���� �ڽĸ� ����
				tempNode = root->getLeftChild();
				delete root;
				root = tempNode;//���� root �����ϰ� ���ο� root ����
				return;
			}
			else if (root->getRightChild() != NULL) {//������ �ڽĸ� ����
				tempNode = root->getRightChild();
				delete root;
				root = tempNode;
				return;
			}
		}
		else {//������� ����
			delNode = curNode;

			if (parent->getLeftChild() == curNode) {//curNode�� ���� �ڽ��� ��
				if (curNode->getLeftChild() != NULL) {//curNode���� ���� �ڽĸ� ���� ��
					parent->setLeftChild(curNode->getLeftChild());//parent�� ���ο� left child�� curNode�� left child�� ����
					delete delNode;
					delNode = NULL;//�߿�!!!!!
					return;
				}
				else if (curNode->getRightChild() != NULL) {//curNode���� ������ �ڽĸ� ���� ��
					parent->setLeftChild(curNode->getRightChild());//parent�� ���ο� left child�� curNode�� right child�� ����
					delete delNode;
					delNode = NULL;
					return;
				}
			}
			else if (parent->getRightChild() == curNode) {//curNode�� ������ �ڽ��� ��
				if (curNode->getLeftChild() != NULL) {//curNode���� ���� �ڽĸ� ���� ��
					parent->setRightChild(curNode->getLeftChild()); // parent�� ���ο� right child�� curNode�� left child�� ����
					delete delNode;
					delNode = NULL;
					return;
				}
				else if (curNode->getRightChild() != NULL) {//curNode���� ������ �ڽĸ� ���� ��
					parent->setRightChild(curNode->getRightChild());//parent�� ���ο� right child�� curNode�� right child�� ����
					delete delNode;
					delNode = NULL;
					return;
				}
			}
		}
	}

	//child�� 2���� node�� ������ ���
	else if (curNode->getLeftChild() != NULL && curNode->getRightChild() != NULL) {
		Node* rightSmall = curNode->getRightChild();//****
		Node* rightSmallParent = curNode;

		if (rightSmall->getLeftChild() == NULL) {//rightSmall�� left child�� ���� ���
			curNode->setData(rightSmall->getData());//rightsmall�� �������� subtree �� ���� ����
			if (rightSmall->getRightChild() != NULL)//rightSmall ������ ������ ��
				curNode->setRightChild(rightSmall->getRightChild());//����
			else//rightSmall, leaf node�� ��
				curNode->setRightChild(NULL);//�� ĭ�� ���� ����ö󰡴ϱ� ������ NULL�� ����� ��
			delete rightSmall;
			rightSmall = NULL;
			return;
		}
		else {//rightSmall�� left child�� �ִ� ���
			while (rightSmall->getLeftChild() != NULL) {//������  sub tree�� ���� ���� data�� ���� node�� �̵� (sub tree ���� ��)
				rightSmallParent = rightSmall;
				rightSmall = rightSmall->getLeftChild();
			}
			//curNode�� ������ tree���� ���� �������� rightSmall, �׿� �´� rightSmallParent ����

			curNode->setData(rightSmall->getData());//������ ����� data�� ���� sub tree�� ���� ���� data�� �ٲ�
			rightSmallParent->setLeftChild(NULL);
			delete rightSmall; // ���� sub tree�� ���� ���� node ����
			rightSmall = NULL;

			return;
		}
	}
}

void Tree::FIND(Node* curNode,int data) {//������ȸ
	if (curNode == nullptr)
		return;

	cout << curNode->getData();//���� ���
	if (curNode->getLeftChild() != NULL || curNode->getRightChild() != NULL) {//leaf node �ƴ϶��
		if (curNode->getData() == data)//Ž�� ��
			return;
		else if (curNode->getData() > data) {//����
			cout << " -> ";
			FIND(curNode->getLeftChild(), data);
		}
		else if (curNode->getData() < data) {//������
			cout << " -> ";
			FIND(curNode->getRightChild(), data);
		}
	}
}

void Tree::PRINT_PRE(Node* curNode) { // ������ȸ
	if (curNode == nullptr)
		return;
	cout << curNode->getData() << " ";
	PRINT_PRE(curNode->getLeftChild());
	PRINT_PRE(curNode->getRightChild());
}

void Tree::PRINT_IN(Node* curNode) { // ������ȸ
	if (curNode == nullptr)
		return;
	PRINT_IN(curNode->getLeftChild());
	cout << curNode->getData() << " ";
	PRINT_IN(curNode->getRightChild());
}

void Tree::PRINT_POST(Node* curNode) { // ������ȸ
	if (curNode == nullptr)
		return;
	PRINT_POST(curNode->getLeftChild());
	PRINT_POST(curNode->getRightChild());
	cout << curNode->getData() << " ";
}

void Tree::PRINT_LEAF(Node* curNode) {//leaf node ���//������ȸ
	if (curNode == nullptr)
		return;
	PRINT_LEAF(curNode->getLeftChild());
	if(curNode->getLeftChild()==NULL&&curNode->getRightChild()==NULL)//�ڽĳ�� �������� ���� ��
		cout << curNode->getData() << " ";
	PRINT_LEAF(curNode->getRightChild());
}

void Tree::deallocate(Node* curNode) {//������ȸ
	if (curNode == nullptr)
		return;
	deallocate(curNode->getLeftChild());
	deallocate(curNode->getRightChild());
	Node* delNode = curNode;
	delete delNode;
}

int main(void) {
	int command = 0;
	int data = 0;
	Tree* tree = new Tree;

	while (1) {
		cout << "Enter Any Command(1:Insert, 2:Delete, 3:Find, 4:Preorder, 5:Inorder, 6:Postorder, 7:Leaf node, 8:Exit): ";
		cin >> command;

		if (command == 1) {
			cin >> data;
			tree->INSERT(tree->getRoot(), data);
		}

		else if (command == 2) {//delete
			cin >> data;
			tree->DELETE(data);
		}

		else if (command == 3) {//find
			cin >> data;
			cout << "Path : ";
			tree->FIND(tree->getRoot(), data);
			cout << endl;
		}

		else if (command == 4) {
			tree->PRINT_PRE(tree->getRoot());
			cout << endl;
		}

		else if (command == 5) {
			tree->PRINT_IN(tree->getRoot());
			cout << endl;
		}

		else if (command == 6) {
			tree->PRINT_POST(tree->getRoot());
			cout << endl;
		}

		else if (command == 7) {
			tree->PRINT_LEAF(tree->getRoot());
			cout << endl;
		}

		else if (command == 8)
			break;

		else
			continue;
	}

	delete tree;
	return 0;
}