#ifndef NODE_HH
#define NODE_HH

#include <string.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <dirent.h>
using namespace std;

class Node {
    public: 
        string name;
        string hash;
        Node*  left;
        Node*  right;
        Node*  daddy;
        int    i;
        int    j;

        
        Node(string name, string hash);
        Node(string name, string hash, Node*  left, Node*  right, int i, int j);
};

#endif 