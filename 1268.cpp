#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
 * https://leetcode.com/contest/weekly-contest-164/problems/search-suggestions-system/
 * 这题的意思就是给定一个字符串数组，然后给定一个target字符串，要求出以target字符串为前缀的前3个字典序最接近的字符串
 * 我一开始的想法是字典树，因为这是一个非常典型的字典树前缀问题，代码如下：字典树
 */

// C++ implementation of search and insert
// operations on Trie
//#include <bits/stdc++.h>
// 字典树构造的代码来自于https://www.geeksforgeeks.org/trie-insert-and-search/（主要是不想自己写。。。）
using namespace std;


//************************字典树的解法如下。。************************
const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (auto & i : pNode->children)
        i = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

void visit(struct TrieNode *root, string& s, int& cnt, vector<string>& tmp){
    if(root==NULL||cnt>3)
        return;
    if(root->isEndOfWord){
        tmp.push_back(s);
        cnt++;
    }
    for(int i=0;i<ALPHABET_SIZE;i++){
        s.push_back('a'+i);
        visit(root->children[i], s, cnt, tmp);
        s.pop_back();
    }
}

struct TrieNode *search_(struct TrieNode *root, string ch, vector<vector<string>>& res){
    if(root==NULL) {
        res.push_back(vector<string>());
        return NULL;
    }
    auto child = root->children[ch.back()-'a'];
    vector<string> tmp;
    int cnt=1;
    visit(child, ch, cnt,tmp);
    res.push_back(tmp);
    return child;
}

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
    struct TrieNode *root = getNode();
    for(auto& product: products){
        insert(root, product);
    }
    string s;
    vector<vector<string>> res;
    struct TrieNode *p = root;
    for(auto& ch:searchWord){
        s.push_back(ch);
        p = search_(p,s,res);
    }
    return res;
}

//*******************************************************************

// 其实还有一种简单解法：排序后二分查找。。

vector<vector<string>> suggestedProducts_(vector<string>& products, string searchWord) {
    const int k = 3, n = searchWord.size();
    string prefix;
    vector<vector<string>> res(n, vector<string>());
    sort(products.begin(), products.end());

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(products.begin(), products.end(), prefix += searchWord[i]);

        for (int j = 0; j < k && it != products.end(); j++, it++) {
            if (it->substr(0, i + 1) == prefix) {
                res[i].push_back(*it);
            }
        }
    }

    return res;
}

// Driver
int main()
{
    vector<string> products={"mobile","mouse","moneypot","monitor","mousepad"};
    string searchWord="mouse";
    auto res=suggestedProducts(products, searchWord);
    for(auto& v:res) {
        for (auto &s:v)
            cout << s << " ";
        cout << endl;
    }
    return 0;
}