#ifndef MERKLE_TREE_HH
#define MERKLE_TREE_HH

#include "node.hh"
#include <fstream>
#include <openssl/sha.h>
#include <vector>
#include <string>

class MerkleTree { 
    public:
        Node*          root;
        int            height;
        vector<Node*>  leaves;
        vector<Node*>  nodes;
        string         header_doc = "ABCDEF";
        string         header_nod = "FEDCBA";

        MerkleTree();
        void compute_tree(vector<string>& names, vector<string>& hash);
        void compute_middle_tree(vector<Node*> nodes, int height);
        void print_tree(Node* node);
        void print_report();
        void proof_membership(string& name, int j, Node* n);
        Node* find_doc(string& name, int& j);
        string read_node(int i, int j);

        string transform_hex(unsigned char s);
        string sha256_2(const string str);
};

#endif 