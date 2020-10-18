#include "merkle_tree.hh"

string open_file(string s) {
    ifstream inFile;
    string p, res = "";
    cout << s << endl;
    inFile.open("./docs/" + s);
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

vector<string> read_data(vector<string>& names) {
    vector<string> input;
	DIR *dir;
    struct dirent *entry;
    if(dir=opendir("./docs")){
        while(entry = readdir(dir)){
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                input.push_back(open_file(entry->d_name));
                names.push_back(entry->d_name);
            }
        }
        closedir(dir);
    }
    return input;
}

void create_doc(string name, string content) {
    ofstream myfile;
    ostringstream oss;
    oss << "./docs/" << name;
    myfile.open(oss.str());
    myfile << content;
    myfile.close();
}

int main() {
    MerkleTree tree;
    vector<string> data, hash, names;
    int i;
    string s, p, content = "";
    cout << "1 to compute tree" << endl;
    cout << "2 to add document" << endl;
    cout << "3 to proof membership (first compute tree)" << endl;
    cout << "Enter number: ";
    cin >> i;
    if (i == 1) {
        data = read_data(names);
        for (int i = 0; i < data.size(); ++i) 
            hash.push_back(tree.sha256_2(tree.header_doc + data[i]));

        tree.compute_tree(names, hash);
        tree.print_report();
    }
    else if (i == 2) {
        cout << "Filename: ";
        cin >> s;
        cout << "File content (stop input with Cntrl+D): ";
        while(cin >> p) {
            content.append(p);
        }
        create_doc(s,p);
        data = read_data(names);
        for (int i = 0; i < data.size(); ++i) 
            hash.push_back(tree.sha256_2(tree.header_doc + data[i]));

        tree.compute_tree(names, hash);
        tree.print_report();
    }
    else if (i == 3) {
        data = read_data(names);
        for (int i = 0; i < data.size(); ++i) 
            hash.push_back(tree.sha256_2(tree.header_doc + data[i]));

        tree.compute_tree(names, hash);
        tree.print_report();

        cout << "introdueix nom del fitxer: ";
        cin >> s;
        int a = -1;
        p = tree.sha256_2(tree.header_doc + open_file(s));
        Node* n = tree.find_doc(s, a);
        tree.proof_membership(p, a, n);
    }
    else cout << "wrong number" << endl;
}