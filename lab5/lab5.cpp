#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include<map>
#include <stack>
#define COUNT 10
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printTree(TreeNode* root, int space = 0)
{
    if (root == NULL)
        return;

    space += COUNT;

    printTree(root->right, space);

    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->val << "\n";

    printTree(root->left, space);
}

bool task1(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) return true;
    if (p == nullptr || q == nullptr) return false;

    if (p->val != q->val) return false;

    return task1(p->left, q->left) && task1(p->right, q->right);
}

bool symmetric(TreeNode* leftNode, TreeNode* rightNode) {

    if (leftNode == nullptr && rightNode == nullptr) {
        return true;
    }
    if (leftNode == nullptr || rightNode == nullptr || leftNode->val != rightNode->val) {
        return false;
    }
    return symmetric(leftNode->left, rightNode->right) && symmetric(leftNode->right, rightNode->left);
}

bool task2(TreeNode* root) {
    if (root == nullptr) {
        return true; 
    }
    return symmetric(root->left, root->right);
}

TreeNode* task3(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    TreeNode* temp = root->left;
    root->left = task3(root->right);
    root->right = task3(temp);

    return root; 
}

void task4sup(TreeNode* node, int k, int& count, int& kthSmallest) {
    if (node == nullptr) {
        return;
    }

    task4sup(node->left, k, count, kthSmallest);

    count++;
    if (count == k) {
        kthSmallest = node->val;
        return;
    }

    task4sup(node->right, k, count, kthSmallest);
}

int task4(TreeNode* root, int k) {
    int kthSmallest = 0;
    int count = 0;

    task4sup(root, k, count, kthSmallest);
    return kthSmallest;
}

string task5_Serialization(TreeNode* node)
{
    stringstream ss;
    if (node != nullptr) {
        ss << node->val;
        ss << " ";
        if (node->left == NULL)
            ss << "n ";
        else ss << task5_Serialization(node->left);
        if (node->right == NULL)
            ss << "n ";
        else ss << task5_Serialization(node->right);
    }
    return ss.str();
}

TreeNode* task5D(const string& values, int& index)
{
    if (index >= values.length() || values[index] == 'n') {
        index += 2;
        return nullptr;
    }

    int num = 0;
    bool negative = false;

    if (values[index] == '-') {
        negative = true;
        ++index;
    }

    while (index < values.length() && values[index] != ' ') {
        num = num * 10 + (values[index] - '0');
        ++index;
    }

    if (negative) num = -num;

    TreeNode* root = new TreeNode(num);
    ++index; 

    root->left = task5D(values, index);
    root->right = task5D(values, index);

    return root;
}

TreeNode* task5Deserialization(const string& str) {
    int index = 0;
    return task5D(str, index);
}

int task6H(TreeNode* root, int& max_sum) {
    if (!root) return 0;

    int left_sum = std::max(0, task6H(root->left, max_sum));
    int right_sum = std::max(0, task6H(root->right, max_sum));

    int current_sum = root->val + left_sum + right_sum;
    max_sum = std::max(max_sum, current_sum);

    return root->val + std::max(left_sum, right_sum);
}

int task6(TreeNode* root) {
    int max_sum = INT_MIN;
    task6H(root, max_sum);
    return max_sum;
}

class task7{
private:
    int COVERED = 0, PLEASE_COVER = 1, HAS_CAMERA = 2;
    int camera = 0;

    int postorder(TreeNode* root) {
        if (root == nullptr)
            return COVERED;

        int left = postorder(root->left);
        int right = postorder(root->right);

        if (left == PLEASE_COVER || right == PLEASE_COVER) {
            camera++;
            return HAS_CAMERA;
        }
        else if (left == HAS_CAMERA || right == HAS_CAMERA) {
            return COVERED;
        }
        else {
            return PLEASE_COVER;
        }
    }
public:
    int minCameraCover(TreeNode* root) {
        camera = 0;
        return postorder(root) == PLEASE_COVER ? ++camera : camera;
    }

};

void helpTask8(TreeNode* rt, int h, map<int, vector<int> >& mp)
{
    if (rt == NULL)
        return;
    mp[h].push_back(rt->val);
    helpTask8(rt->left, h - 1, mp);
    helpTask8(rt->right, h + 1, mp);
}
void task8(TreeNode* rt)
{
    map<int, vector<int> > mp;
    map<int, vector<int> >::iterator it;
    int h = 0;
    helpTask8(rt, h, mp);
    for (it = mp.begin(); it != mp.end(); it++)
    {
        cout << it->first << " -> [";
        for (int i = 0; i < it->second.size(); i++)
        {
            cout << it->second[i] << ", ";
        }
        cout << "\b\b]" << endl;
    }
}

TreeNode* task9(string traversal) {
    stack<TreeNode*> nodeStack;
    int i = 0;

    while (i < traversal.length()) {
        int depth = 0;
        while (i < traversal.length() && traversal[i] == '-') {
            ++depth;
            ++i;
        }

        int value = 0;
        while (i < traversal.length() && traversal[i] != '-') {
            value = value * 10 + (traversal[i] - '0');
            ++i;
        }

        TreeNode* node = new TreeNode(value);

        if (depth == nodeStack.size()) {
            if (!nodeStack.empty()) {
                nodeStack.top()->left = node;
            }
        }
        else {
            while (depth < nodeStack.size()) {
                nodeStack.pop();
            }
            if (!nodeStack.empty()) {
                nodeStack.top()->right = node;
            }
        }

        nodeStack.push(node);
    }

    while (nodeStack.size() > 1) {
        nodeStack.pop();
    }

    return nodeStack.top();
}

int main()
{
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(2);

    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    printTree(p);
    printTree(q);

    if (task1(p, q)) 
        cout << "True\n";
    else 
        cout << "False\n";

    if (task2(p))
        cout << "True\n";
    else
        cout << "False\n";

    TreeNode* root1 = new TreeNode(4);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(3);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(9);
    printTree(root1);
    printTree(task3(root1));

    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(NULL);
    root2->right->right = new TreeNode(2);
    cout << task4(root2, 1);

    TreeNode* root3 = new TreeNode(4);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(7);
    root3->left->left = new TreeNode(1);
    root3->left->right = new TreeNode(3);
    root3->right->left = new TreeNode(6);
    root3->right->right = new TreeNode(9);
    root3->right->right->left = new TreeNode(7);
    root3->left->right->right = new TreeNode(8);
    printTree(root3);
    cout << "\n" << task5_Serialization(root3) << "\n";
    printTree(task5Deserialization(task5_Serialization(root3)));

    TreeNode* root4 = new TreeNode(-10);
    root4->left = new TreeNode(9);
    root4->right = new TreeNode(20);
    root4->right->left = new TreeNode(15);
    root4->right->right = new TreeNode(7);

    cout << "\n" << task6(root4);

    task7 t;
    cout << "\n" << t.minCameraCover(root4)<<"\n";
    task8(root4);
    string traversal = "1-2--3--4-5--6--7";
    printTree(task9(traversal));
    delete p;
    delete q;
}

