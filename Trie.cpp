#include <bits/stdc++.h>

using namespace std;

class TrieNode {
  public:
    TrieNode(char key_char) : key_char_(key_char), is_end_(false) {}
    
    TrieNode(TrieNode *node) : key_char_(node->key_char_), is_end_(node->is_end_), children_(node->children_)   {}
    
    virtual ~TrieNode() = default;
    
    bool hasChild(char key_char) { return children_.find(key_char) != children_.end(); }
    
    bool hasChildren() { return !children_.empty(); }
    
    bool isEndNode() { return is_end_; }
    
    char getKeyChar() { return key_char_; }
    
    void setEndNode(bool is_end) { is_end_ = is_end; }
    
    void insertChildNode(char key_char) {
        if(hasChild(key_char)) return;
        children_[key_char] = new TrieNode(key_char);
        return;    
    }
    
    void removeChildNode(char key_char) {
        if(!hasChild(key_char)) return;
        children_.erase(key_char);
        return;
    }
    
    TrieNode* getChildNode(char key_char) {
        if(!hasChild(key_char)) return nullptr;
        return children_[key_char];
    }
    
    void resetChildNode(TrieNode *node) {
        children_[node->getKeyChar()] = node;
        return;
    }
    
  protected:
    char key_char_;
    bool is_end_{false};
    unordered_map<char,TrieNode*> children_;  
};

class TrieNodeWithValue : public TrieNode {
    public:
        TrieNodeWithValue(TrieNode *node, int value) : TrieNode(node) {
            setEndNode(true);
            value_ = value;
        }
        
        int getValue() { return value_; }
        
    private:
        int value_;
};

class Trie {
    public:
        Trie() : root_(new TrieNode('\0')) {}
        
        bool insert(string key, int value) {
            if(key.empty()) return false;
            TrieNode *current = root_, *parent = NULL;
            for(char ch:key) {
                bool hasChild = current -> hasChild(ch);
                if(!hasChild) { current -> insertChildNode(ch); }
                parent = current;
                current = current -> getChildNode(ch);
            }
            if(current -> isEndNode()) return false;
            TrieNodeWithValue *nodeWithValue = new TrieNodeWithValue(current, value);
            
            parent->resetChildNode(nodeWithValue);
            return true;
        }
        
        bool removeRecursively(TrieNode *current, string key, int depth) {
            int n = key.length();
            if(n == 0) return false;
            if(n == depth) {
                current -> setEndNode(false);
                return !current -> hasChildren();
            }     
            char ch = key[depth];
            TrieNode *child = current -> getChildNode(ch);
            bool flag = removeRecursively(child, key, depth+1);
            if(flag) current -> removeChildNode(ch);
            return flag && !current->hasChildren() && !current -> isEndNode();
        }
        
        void remove(string key) {
            TrieNode *current = root_;
            removeRecursively(current,key,0);
            return;
        }
        
        bool getValue(string key, int *result) {
            if(key.empty()) return false;
            
            TrieNode *current = root_;
            for(char ch : key) {
                bool hasChild = current -> hasChild(ch);
                if(!hasChild) return false;
                current = current -> getChildNode(ch);
            }
            if(!current -> isEndNode()) { return false; }
            
            *result = dynamic_cast<TrieNodeWithValue *>(current) -> getValue();
            return true;
        }
     
    private:
        TrieNode* root_;    
};

int main() {
    Trie *trie = new Trie();
    trie -> insert("abc", 3);
    trie -> insert("ab", 2);
    trie -> insert("a", 1);
    int result;
    cout<<trie -> getValue("a",&result)<<endl;  
    cout<<result<<endl;
    cout<<"-------"<<endl;
    cout<<trie -> getValue("ab",&result)<<endl;  
    cout<<result<<endl;
    cout<<"-------"<<endl;
    cout<<trie -> getValue("abc",&result)<<endl;  
    cout<<result<<endl;
    cout<<"-------"<<endl;
    trie -> remove("abc");
    trie -> remove("ab");
    cout<<trie -> getValue("ab",&result)<<endl;  
    cout<<result<<endl;
    cout<<"-------"<<endl;
    cout<<trie -> getValue("abc",&result)<<endl;  
    cout<<result<<endl;
    cout<<"-------"<<endl;
    return 0;
}
