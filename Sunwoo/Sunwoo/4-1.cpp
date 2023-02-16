#include <iostream>
#include <cstring>
using namespace std;

class Node
{
private:
    int value;
    Node* parent;
    Node* right;
    Node* left;
public:
    Node()
    {
        this->value = 0;
        this->parent = NULL;
        this->right = NULL;
        this->left = NULL;
    }
    void setValue(int value) { this->value = value; }
    int getValue() { return this->value; }

    void setParent(Node* parent) { this->parent = parent; }
    Node* getParent() { return this->parent; }

    void setLeftChild(Node* leftChild) { this->left = leftChild; }
    Node* getLeftChild() { return this->left; }

    void setRightChild(Node* rightChild) { this->right = rightChild; }
    Node* getRightChild() { return this->right; }
};


class Tree
{
private:
    Node* root;
    Node* parent;
    int size;
public:
    Tree()
    {
        this->root = NULL;
        this->parent = NULL;
        this->size = 0;
    }
    ~Tree()
    {

    }
    Node* getRoot() { return root; }
    void INSERT(Node* curNode, int integer);
    void DELETE(int integer);
    void PRINT_PREORDER(Node* curNode);
    void PRINT_INORDER(Node* curNode);
    void PRINT_POSTORDER(Node* curNode);
};

void Tree::INSERT(Node* curNode, int integer)
{
    if (root == NULL) // Root 노드가 없는 경우 추가
    {
        Node* newNode = new Node;
        newNode->setValue(integer);
        root = newNode;
        // curNode = root; 왜쓰는지?
        this->size++;
    }
    // Root 노드가 있고
    else if (curNode->getValue() > integer) // 입력값이 현재 노드에 저장된 값보다 작을 경우
    {
        if (curNode->getLeftChild() == NULL) // 현재 노드의 왼쪽에 저장된 노드가 없을 경우
        { // 새로운 노드에 입력값을 저장하고 현재 노드의 왼쪽노드로 삽입
            Node* newNode = new Node;
            newNode->setValue(integer);
            curNode->setLeftChild(newNode);
            this->size++;
        }
        else // 왼쪽에 저장된 노드가 있을 경우
        {
            if (curNode->getLeftChild()->getValue() == integer) // 입력값과 왼쪽 노드에 저장된 값이 같으면
                return; // 삽입하지 않고 종료
            INSERT(curNode->getLeftChild(), integer);
        }
    }
    else if (curNode->getValue() < integer) // 입력값이 현재 노드에 저장된 값보다 클 경우
    {
        if (curNode->getRightChild() == NULL) // 현재 노드의 오른쪽에 저장된 노드가 없을 경우
        { // 새로운 노드에 입력값을 저장하고 현재 노드의 오른쪽노드로 삽입
            Node* newNode = new Node;
            newNode->setValue(integer);
            curNode->setRightChild(newNode);
            this->size++;
        }
        else // 오른쪽에 저장된 노드가 있을 경우
        {
            if (curNode->getRightChild()->getValue() == integer) // 입력값고하 오른쪽 노드에 저장된 값이 같으면
                return; // 삽입하지 않고 종료
            INSERT(curNode->getRightChild(), integer);
        }
    }
}

void Tree::DELETE(int integer)
{
    Node* curNode = root;
    Node* delNode = NULL;
    Node* tempNode = NULL;
    this->size--;

    while (1) // 반복문을 돌리며 integer와 같은 value를 갖는 노드를 찾아서 curNode에 저장
    {
        if (curNode->getValue() < integer) // 기준 노드의 value보다 큰 값이면
        { // 기존 노드 parent 설정 후 오른쪽 노드로 curNode 이동
            parent = curNode;
            curNode = curNode->getRightChild();
        }
        else if (curNode->getValue() > integer) // 기준 노드의 value보다 작은 값이면
        { // 기존 노드 parent 설정 후 왼쪽 노드로 curNode 이동
            parent = curNode;
            curNode = curNode->getLeftChild();
        }
        else // 기준 노드의 value와 integer가 같으면 반복문 탈출
            break;
    }
    // 위 반복문을 통해 curNode가 삭제하려는 값을 가진 노드가 됨


    if (curNode->getLeftChild() == NULL && curNode->getRightChild() == NULL) // 자식노드가 없는 경우
    {
        if (curNode == root) // 자식노드가 없고, 삭제하려는 노드가 루트 노드인 경우
        {
            delete root;
            root = NULL;
            return;
        }
        else // 자식노드가 없고, 삭제하려는 노드가 루트 노드가 아닌 경우
        {
            delete curNode;
            curNode = NULL;
            return;
        }
    }

    else if (curNode->getLeftChild() == NULL || curNode->getRightChild() == NULL) // 자식노드가 한개만 있는 경우
    {
        if (curNode == root) // 삭제할 노드가 루트 노드인 경우
        {
            if (curNode->getLeftChild() != NULL) // 왼쪽 자식노드만 존재하는 경우
            {
                tempNode = curNode->getLeftChild();
                delete root;
                root = tempNode;
                return;
            }
            else if (curNode->getRightChild() != NULL) // 오른쪽 자식노드만 존재하는 경우
            {
                tempNode = curNode->getRightChild();
                delete root;
                root = tempNode;
                return;
            }
        }
        else // 삭제할 노드가 루트 노드가 아닌 경우
        {
            delNode = curNode;

            if (curNode == parent->getLeftChild()) // 삭제할 노드가 부모의 왼쪽 자식일 때
            {
                if (curNode->getLeftChild() != NULL) // 삭제할 노드의 왼쪽 자식이 있을 때
                {
                    parent->setLeftChild(curNode->getLeftChild());
                    delete delNode;
                    delNode = NULL;
                    return;
                }
                else if (curNode->getRightChild() != NULL) // 삭제할 노드의 오른쪽 자식이 있을 때
                {
                    parent->setRightChild(curNode->getRightChild());
                    delete delNode;
                    delNode = NULL;
                    return;
                }
            }
            else if (curNode == parent->getRightChild()) // 삭제할 노드가 부모의 오른쪽 자식일 때
            {
                if (curNode->getLeftChild() != NULL) // 삭제할 노드의 왼쪽 자식이 있을 때
                {
                    parent->setLeftChild(curNode->getLeftChild());
                    delete delNode;
                    delNode = NULL;
                    return;
                }
                else if (curNode->getRightChild() != NULL) // 삭제할 노드의 오른쪽 자식이 있을 때
                {
                    parent->setRightChild(curNode->getRightChild());
                    delete delNode;
                    delNode = NULL;
                    return;
                }
            }
        }
    }

    else if (curNode->getLeftChild() != NULL && curNode->getRightChild() != NULL) // 자식노드가 두개인 경우
    {
        Node* rightSmall = curNode->getRightChild();
        Node* rightSmallParent = rightSmall;

        if (rightSmall->getLeftChild() == NULL)
        {

        }
    }
}

void Tree::PRINT_PREORDER(Node* curNode)
{
    if (curNode == nullptr)
        return;
    cout << curNode->getValue() << " ";
    PRINT_PREORDER(curNode->getLeftChild());
    PRINT_PREORDER(curNode->getRightChild());
}

void Tree::PRINT_INORDER(Node* curNode)
{
    if (curNode == nullptr)
        return;
    PRINT_INORDER(curNode->getLeftChild());
    cout << curNode->getValue() << " ";
    PRINT_INORDER(curNode->getRightChild());
}

void Tree::PRINT_POSTORDER(Node* curNode)
{
    if (curNode == nullptr)
        return;
    PRINT_POSTORDER(curNode->getLeftChild());
    PRINT_POSTORDER(curNode->getRightChild());
    cout << curNode->getValue() << " ";
}


int main()
{
    Tree* tree = new Tree;
    int command = NULL, input;

    while (command != 8)
    {
        cout << "Enter Any Command(1:insert, 2:Delete, 3:Find, 4:Preorder, 5:Inorder, 6:Postorder, 7:Leaf node, 8:Exit): ";
        cin >> command;
        if (command == 1)
        {
            cin >> input;
            tree->INSERT(tree->getRoot(), input);
        }
        else if (command == 2)
        {
            cin >> input;
            tree->DELETE(input);
        }
        else if (command == 4)
        {
            tree->PRINT_PREORDER(tree->getRoot());
            cout << endl;
        }
        else if (command == 5)
        {
            tree->PRINT_INORDER(tree->getRoot());
            cout << endl;
        }
        else if (command == 6)
        {
            tree->PRINT_POSTORDER(tree->getRoot());
            cout << endl;
        }
        else if (command == 8)
            break;
    }
    return 0;
}