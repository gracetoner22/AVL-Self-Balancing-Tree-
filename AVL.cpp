#include "AVL.h"
#include <iostream>
#include <string>
#include <cctype>
#include <queue>
using namespace std;

bool AVLTree::insert(const std::string &name, const std::string &ufid) {
    for (char c: name) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    if (ufid.length() != 8) {
       return false;
    }
    for (char k: ufid) {
        if (!std::isdigit(k)) {
           return false;
        }
    }
    if (!searchIDhelper(ufid).empty()) {
        return false;
    }
    root = insertHelper(root, name, ufid);
    return true;
}
int AVLTree::Height(Node* node) {
    if (node==nullptr) {
        return 0;
    }
    return 1 + std::max(Height(node->left), Height(node->right));
}
int AVLTree::leftHeight(Node* node) {
    if (node==nullptr) {
        return 0;
    }
    return Height(node->left);
}

int AVLTree::rightHeight(Node* node) {
    if (node==nullptr) {
        return 0;
    }
    return Height(node->right);
}

int AVLTree::balanceFactor(Node* node) {
    return leftHeight(node) - rightHeight(node);
}
Node* AVLTree::rightRotate(Node* y) {
    Node* x =y->left;
    Node* t2 =x->right;
    x->right =y;
    y->left =t2;
    return x;
}
Node* AVLTree::leftRotate(Node* x) {
    Node* y =x->right;
    Node* t2 =y->left;
    y->left =x;
    x->right =t2;
    return y;
}
Node* AVLTree::leftRightRotate(Node* y) {
    y->left = leftRotate(y->left);
    return rightRotate(y);
}

Node* AVLTree::rightLeftRotate(Node* y) {
    y->right = rightRotate(y->right);
    return leftRotate(y);
}
Node* AVLTree::whatBalanceFactor(Node* node) {
    if (balanceFactor(node) > 1) {
        if (balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        } else {
            return leftRightRotate(node);
        }
    }
    if (balanceFactor(node) < -1) {
        if (balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        } else {
            return rightLeftRotate(node);
        }
    }

    return node;
}

Node* AVLTree::insertHelper(Node* node, const std::string &name,  const std::string &ufid) {
    if (node==nullptr) {
        return new Node( name, ufid);
    }
    if (ufid == node->ufid) {
        return node;
    }
    if (ufid<node->ufid) {
        node->left = insertHelper(node->left, name, ufid);
    }
    else {
        node->right = insertHelper(node->right, name, ufid);
    }
    node=whatBalanceFactor(node);
return node;
}
Node* AVLTree::inorderSuc(Node* node) {
    while (node && node->left!=nullptr) {
        node = node->left;
    }
    return node;
}
std::string AVLTree::searchIDhelper(const std::string &ufid) const {
    const Node* result = searchID(root, ufid);
    if (result) {
        return result->name;
    }
    return "";
}
 Node* AVLTree::searchID(Node* node,const std::string &ufid)const {
    if (node==nullptr) {
        return nullptr;
    }
    if (ufid == node->ufid) {
        return node;
    }
    if (ufid > node->ufid) {
        return searchID(node->right, ufid);

}    else{
        return searchID(node->left, ufid);
    }
}
bool AVLTree::removeID(const std::string &ufid) {
    bool deleted = false;
    root = removeID(root, ufid, deleted);
    return deleted;
}
Node* AVLTree::removeID(Node* node,const std::string &ufid,bool &deleted) {
    if (node==nullptr) {
        return nullptr;
    }

    if (ufid < node->ufid) {
        node->left = removeID(node->left, ufid,deleted);
    }
    else if (ufid > node->ufid) {
        node->right = removeID(node->right, ufid,deleted);
    }
    else{
        deleted = true;
        if (node->left==nullptr && node->right==nullptr) {
            delete node;
            return nullptr;
        }
        if (node->left==nullptr && node->right!=nullptr) {
          Node* p = node->right;
          delete node;
          return p;
        }
        if (node->left!=nullptr && node->right==nullptr) {
            Node* p = node->left;
            delete node;
            return p;
        }
        if (node->left!=nullptr && node->right!=nullptr) {
            Node* p = inorderSuc(node->right);
            std::string p_ufid = p->ufid;
            std::string p_name = p->name;
            node->ufid = p_ufid;
            node->name =p_name;
            node->right = removeID(node->right,p_ufid,deleted);
        }
    }
    return node;
}

void AVLTree::searchNameHelper(Node* node,const std::string &name, std::vector<std::string>& matches) const {
    if (node==nullptr) {
        return;
    }
    if (node->name==name) {
        matches.push_back(node->ufid);
    }
    searchNameHelper(node->left, name,matches);
    searchNameHelper(node->right, name,matches);
}
void AVLTree::searchName(const std::string &name)const {
    std::vector<std::string> matches;
    searchNameHelper(root, name, matches);
    if (!matches.empty()) {
        for (const std::string &s : matches) {
            std::cout << s <<std::endl;
        }
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}
void AVLTree::printInorder(Node* node, bool &comma) {
    if (node==nullptr) {
        return;
    }
    printInorder(node->left, comma);
    if (!comma) std::cout << ", ";
    std::cout << node->name;
    comma = false;
    printInorder(node->right,comma);
}
void AVLTree::actualInorder() {
    bool comma = true;
    printInorder(root, comma);
    std::cout << std::endl;
}
void AVLTree::printPreorder(Node* node, bool &comma) {
    if (node==nullptr) {
        return;
    }
    if (!comma) std::cout << ", ";
    std::cout << node->name;
    comma = false;
    printPreorder(node->left,comma);
    printPreorder(node->right,comma);
}
void AVLTree::actualPreorder() {
    bool comma = true;
    printPreorder(root,comma);
    std::cout << std::endl;
}
void AVLTree::printPostorder(Node* node, bool &comma) {
    if (node==nullptr) {
        return;
    }
    printPostorder(node->left,comma);
    printPostorder(node->right,comma);
    if (!comma) std::cout << ", ";
    std::cout << node->name;
    comma = false;
}
void AVLTree::actualPostorder() {
    bool comma = true;
    printPostorder(root,comma);
    std::cout << std::endl;
}
void AVLTree::printLevelCount(Node*node) {
    std::queue<Node*> q;
    q.push(node);
    int counter =0;
    if (node==nullptr) {
        std::cout<<"0"<<std::endl;
    }
    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        for (int i = 0; i < levelSize; i++) {
            Node* p = q.front();
            q.pop();
            if (p->left!=nullptr) q.push(p->left);
            if (p->right!=nullptr) q.push(p->right);
        }
        counter++;
    }
 std::cout << counter << std::endl;
}
void AVLTree::actualLevelcount() {
    printLevelCount(root);
}

void AVLTree::inorderNodecounter(Node* node, int &counter, int n, bool &removed) {
    if (node == nullptr || removed) return;
    inorderNodecounter(node->left, counter, n, removed);
    if (counter == n) {
        removed = removeID(node->ufid);
        return;
    }
    counter++;
    inorderNodecounter(node->right, counter, n, removed);
}
void AVLTree::removeInorderN(int n) {
    int counter = 0;
    bool removed = false;
    inorderNodecounter(root, counter, n,removed);
    if (!removed) {
        std::cout << "unsuccessful" << std::endl;
    } else {
        std::cout << "successful" << std::endl;
    }
}
void AVLTree::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
AVLTree::~AVLTree() {
    destroyTree(root);
}
