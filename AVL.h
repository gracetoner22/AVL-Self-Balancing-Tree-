

#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
struct Node {
    std::string name;
    std::string ufid;
    Node* left;
    Node* right;
    Node* next;


    Node(std::string name , std:: string ufid) {
        this->name = name;
        this->ufid = ufid;
        this->left = nullptr;
        this->right = nullptr;
        this->next = nullptr;
    }
};
class  AVLTree {
        private:
        Node* root = nullptr;
        Node* insertHelper(Node* node,const std::string &name, const std::string &ufid);
        void destroyTree(Node* node);
        public:
        bool insert(const std::string &name,const std::string &ufid);
        Node* removeID(Node* node,const std::string &ufid,bool &deleted);
        Node* searchID(Node* node,const std::string &ufid)const ;
        void printInorder(Node* node, bool &comma);
        void printPreorder(Node* node, bool &comma);
        void printPostorder(Node* node, bool &comma);
        void printLevelCount(Node*node);
        int balanceFactor(Node* node);
        std::vector<char> actualOutput;
        std::vector<char> expectedOutput;
        std::vector<std::string> studentIDsameName;
        int Height(Node* node);
        int leftHeight(Node* node);
        int rightHeight(Node* node);
        Node* whatBalanceFactor(Node* node);
        Node* rightRotate(Node* y);
        Node* leftRotate(Node* x);
        Node* leftRightRotate(Node* y);
        Node* rightLeftRotate(Node* y);
        Node* inorderSuc(Node* node);
        bool removeID(const std::string &ufid);
        std::string searchIDhelper(const std::string &ufid) const;
        void searchNameHelper(Node* node, const std::string &name,std::vector<std::string>& matches)const;
        void searchName(const std::string &name)const;
        void inorderNodecounter(Node* node, int &counter, int n, bool &removed);
        void removeInorderN( int n);
        void actualInorder();
        void actualPreorder();
        void actualPostorder();
        void actualLevelcount();

        ~AVLTree();
    };

#endif //PROJECT1_AVL_H