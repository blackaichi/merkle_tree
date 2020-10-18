#include "node.hh"

Node::Node(string name, string hash){
    this->name = name;
    this->hash = hash;
    this->i = -1;
    this->j = -1;
    this->left = NULL;
    this->right = NULL;
    this->daddy = NULL;
}

Node::Node(string name, string hash, Node* left, Node* right, int i, int j) {
    this->name = name;
    this->hash = hash;
    this->i = i;
    this->j = j;
    this->left = left;
    this->right = right;
    this->daddy = NULL;
}