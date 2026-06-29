#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;
//1948_DeleteDuplicateFoldersInSystem

struct TrieNode {
    string name;
    string serial;
    map<string, TrieNode*> children;
    TrieNode(string n): name(n) {}
};

unordered_map<string, int> m; //name,cnt

void recur(TrieNode* node, vector<string>& currPath, vector<vector<string>>& ans) {
    if(!node) return;
    string treeStr = node->serial;
    if(treeStr.size() && m[treeStr] > 1) return;

    if(node->name != "/") {
        currPath.push_back(node->name);
        ans.push_back(currPath);
    }

    for(auto& [name, n]: node->children) {
        recur(n, currPath, ans);
    }
    
    if(node->name != "/") {
        currPath.pop_back();
    }
}

string serialize(TrieNode* node) {
    if(!node) return "";
    string treeStr;
    for(auto& [name,n]:node->children) {
        treeStr += name + "(" + serialize(n) + ")";
    }
    if(treeStr.size()) {
        node->serial = treeStr;
        m[treeStr]++;
    }
    return treeStr;
}

vector<vector<string>> solution(vector<vector<string>> paths) {
    m.clear();
    TrieNode* root = new TrieNode("/");
    for(auto& path:paths) {
        TrieNode* curr = root;
        for(auto& folder:path) {
            if(curr->children.count(folder) == 0) {
                curr->children[folder] = new TrieNode(folder);
            }
            curr = curr->children[folder];
        }
    }
    
    string str = serialize(root);

    vector<vector<string>> ans;
    vector<string> currPath;
    recur(root, currPath, ans);
    return ans;
}

int main() {
    vector<vector<string>> ret;

    ret = solution({{"a"},{"c"},{"d"},{"a","b"},{"c","b"},{"d","a"}});
    for(auto& a:ret) {
        printf("{");
        for(auto& b:a) {
            printf("%s ", b.c_str());
        }
        printf("} ");
    } printf("\n");
    //{{"d"},{"d","a"}}
    
    ret = solution({{"a"},{"c"},{"a","b"},{"c","b"},{"a","b","x"},{"a","b","x","y"},{"w"},{"w","y"}});
    for(auto& a:ret) {
        printf("{");
        for(auto& b:a) {
            printf("%s ", b.c_str());
        }
        printf("} ");
    } printf("\n");
    //{{"c"},{"c","b"},{"a"},{"a","b"}}
    
    ret = solution({{"a","b"},{"c","d"},{"c"},{"a"}});
    for(auto& a:ret) {
        printf("{");
        for(auto& b:a) {
            printf("%s ", b.c_str());
        }
        printf("} ");
    } printf("\n");
    //{{"a","b"},{"c","d"},{"c"},{"a"}}

    return 0;
}
