#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <deque>
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

void dump(TreeNode *t) {
    if(t == nullptr) {
        printf("n (root)\n");
        return;
    }
    
    printf("%d (root)\n", t->value);
    
    deque<TreeNode*> q;
    q.push_back(t->left);
    q.push_back(t->right);
    
    int valid_count = 1;
    while(!q.empty() && valid_count > 0) {
        int size = q.size();
        valid_count = 0;
        for(int i = 0; i < size; i++) {
            TreeNode *tmp = q.front();
            q.pop_front();
            if(tmp == nullptr) {
                printf("n ");
                q.push_back(nullptr);
                q.push_back(nullptr);
                continue;
            }
            printf("%d ", tmp->value);
            q.push_back(tmp->left);
            q.push_back(tmp->right);
            if(tmp->left) valid_count++;
            if(tmp->right) valid_count++;
        }
        printf("\n");
    }
}

void dump(vector<TreeNode*> ts) {
    printf("size=%d\n", ts.size());
    
    for(auto t:ts) {
        dump(t);
    }
}

map<int, vector<TreeNode*>> m;
vector<TreeNode*> dfs(int n) {
    if (n % 2 != 1) return { nullptr };
    if (n == 0) return { nullptr };
    if (n == 1) return { new TreeNode(0) };
    
    if(m.find(n) != m.end()) {
        return m[n];
    }
    
    vector<TreeNode*> ret;
    int l, r;
    for(l = 1; l < n; l+=2) {
        r = n - l - 1;
        auto leftTrees = dfs(l);
        auto rightTrees = dfs(r);
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
    dump(ts);
    /*
    size=5
    0 (root)
    0 0 
    n n 0 0 
    n n n n n n 0 0 
    0 (root)
    0 0 
    n n 0 0 
    n n n n 0 0 n n 
    0 (root)
    0 0 
    0 0 0 0 
    0 (root)
    0 0 
    0 0 n n 
    n n 0 0 n n n n 
    0 (root)
    0 0 
    0 0 n n 
    0 0 n n n n n n 
    */
    return 0;
}
