#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

// 894_AllPossibleFullBinaryTrees

class TreeNode {
public:
    int value;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(): value(0), left(nullptr), right(nullptr) {}
    TreeNode(int v): value(v), left(nullptr), right(nullptr) {}
    TreeNode(int v, TreeNode* l, TreeNode* r): value(v), left(l), right(r) {}
};


map<int, vector<TreeNode*>> m;
vector<TreeNode*> dfs(int n) {
    if (n % 2 != 1) return {};
    if (n == 1) return { new TreeNode(0) };
    
    if(m.find(n) != m.end()) {
        return m[n];
    }
    
    vector<TreeNode*> ret;
    int l, r;
    for(l = 0; l < n; l++) {
        r = n - l - 1;
        auto leftTrees = dfs(l);
        auto rightTrees = dfs(r);
        if(leftTrees.size() == 0) {
            for(auto rightTree:rightTrees) {
                TreeNode *root = new TreeNode(0, nullptr, rightTree);
                ret.push_back(root);
            }
        }
        if(rightTrees.size() == 0) {
            for(auto leftTree:leftTrees) {
                TreeNode *root = new TreeNode(0, leftTree, nullptr);
                ret.push_back(root);
            }
        }
        for(auto leftTree:leftTrees) {
            for(auto rightTree:rightTrees) {
                TreeNode *root = new TreeNode(0, leftTree, rightTree);
                ret.push_back(root);
            }
        }
    }
    
    m[n] = ret;
    return ret;
}

int main() {
    vector<TreeNode*> ts;
    ts = dfs(7); // 5
    printf("possible size=%zu\n", ts.size());
    
    return 0;
}
