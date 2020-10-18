#include "merkle_tree.hh"

MerkleTree::MerkleTree(){}

void MerkleTree::compute_middle_tree(vector<Node*> Nodes, int height) {
    //cout << "height: " << height << ", size:" << Nodes.size() << endl;
    if (height == this->height) {
        this->nodes.push_back(Nodes[0]);
        this->root = Nodes[0];
    }
    else {
        int size;
        if (Nodes.size()%2 == 0) size = Nodes.size()/2;
        else size = (Nodes.size()/2)+1;
        vector<Node*> NodesAux;
        for (int j = 0; j < Nodes.size(); j+=2) {
            //cout << "i: " << Nodes[j]->i << ", j: " << Nodes[j]->j << ", iteracio: " << j << ", size: " << Nodes.size() << endl;
            if (j+1 == Nodes.size()) {
                string to_hash = header_nod + Nodes[j]->hash;
                Node* n = new Node("NULL", sha256_2(to_hash), Nodes[j], NULL, height, j/2);
                Nodes[j]->daddy = n;
                NodesAux.push_back(n);
                this->nodes.push_back(Nodes[j]);
            }
            else {
                //string s = Nodes[j]->hash;
                //s.append(Nodes[j+1]->hash);
                //cout << "sha: " << sha256_2(s) << endl;
                //cout << "Node: " << height << j/2 << ", fills: " << Nodes[j]->i << Nodes[j]->j << " i " << Nodes[j+1]->i << Nodes[j+1]->j << endl;
                string to_hash = header_nod + Nodes[j]->hash + Nodes[j+1]->hash;
                Node* n = new Node("NULL", sha256_2(to_hash),Nodes[j], Nodes[j+1], height, j/2);
                Nodes[j]->daddy = n;
                Nodes[j+1]->daddy = n;
                NodesAux.push_back(n);
                this->nodes.push_back(Nodes[j]);
                this->nodes.push_back(Nodes[j+1]);
            }
        }
        this->compute_middle_tree(NodesAux, height+1);
    }
}

void MerkleTree::compute_tree(vector<string>& names, vector<string>& hash) {
    int i = hash.size();
    int height=1;
    while (i > 1) { 
        if (i%2 == 0) i = i/2;
        else i = (i/2)+1;
        ++height;
    }
    this->height = height;
    cout << "height: " << height << endl;
    
    for (int j = 0; j < hash.size(); ++j) {
        Node* n = new Node(names[j], hash[j], NULL, NULL, 0, j);
        this->leaves.push_back(n);
    }

    this->compute_middle_tree(this->leaves, 1);
}

void MerkleTree::print_tree(Node* node) {
    if (node != NULL) {
        ofstream myfile;
        ostringstream oss;
        cout << "Writing node: " << node->i << "." << node->j /*<< ", daddy: " << node->daddy->i << "." << node->daddy->j*/ << endl;
        oss << "./nodes/node" << node->i << '.' << node->j;
        myfile.open(oss.str());
        myfile << node->hash;
        myfile.close();
    }
}

void MerkleTree::print_report() {
    ofstream myfile;
    myfile.open("./report");
    myfile << "MerkleTree:sha256:ABCDEF:FEDCBA:" << this->nodes.size() << ":" << this->leaves.size() << ":" << sha256_2(root->hash) << endl;
    for (int i = 0; i < nodes.size(); ++i) {
        print_tree(nodes[i]);
        myfile << nodes[i]->i << ":" << nodes[i]->j << ":" << nodes[i]->hash << endl;
    }
    myfile.close();
}

void MerkleTree::proof_membership(string& hash, int j, Node* n) {
    Node* aux;
    Node* aux2;
    bool left = false;

    for (int i = 1; i < height; ++i) {
        aux = n->daddy;

        if (j%2 == 0) {
            if (aux->right != NULL)
                cout << "height: " << i << endl << "computed: " << sha256_2(header_nod + n->hash + aux->right->hash) << endl << "real: " << read_node(aux->i, aux->j) << endl;
            else 
                cout << "height: " << i << endl << "computed: " << sha256_2(header_nod + n->hash) << endl << "real: " << read_node(aux->i, aux->j) << endl;
        }
        else 
            cout << "height: " << i << endl << "computed: " << sha256_2(header_nod + aux->left->hash + n->hash) << endl << "real: " << read_node(aux->i, aux->j) << endl;
        j = aux->j;
        n = aux;
    }
}

string MerkleTree::read_node(int i, int j) {
    ifstream inFile;
    string p, res = "";
    ostringstream oss;
    oss << "./nodes/node" << i << '.' << j;
    inFile.open(oss.str());
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }
    
    while (inFile >> p) {
        res.append(p);
    }
    
    inFile.close();
    return res;
}

Node* MerkleTree::find_doc(string& name, int& j) {
    cout << this->leaves.size()<<endl;
    for (int l = 0; l < this->leaves.size(); ++l) {
        if (this->leaves[l]->name == name) {
            j = this->leaves[l]->j;
            return this->leaves[l];
        }
    }
    return NULL;
}

string MerkleTree::transform_hex(unsigned char s) {
    stringstream ss;
    ss << hex << (int) s;
    return ss.str();
}   

string MerkleTree::sha256_2(const string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    string output = "";    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        output += transform_hex(hash[i]);
    }
    return output;
}