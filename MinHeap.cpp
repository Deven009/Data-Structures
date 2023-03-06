#include <bits/stdc++.h>

using namespace std;

class MinHeap {
    private: 
        vector<int> tree; 
        
        int getParentIndex(int ind) { return ((ind+1)>>1) - 1; }
        int getLeftChildIndex(int ind) { return (2*ind)+1; }
        int getRightChildIndex(int ind) { return (2*ind)+2; }
        
        bool hasParent(int ind) { return getParentIndex(ind) >= 0; }
        bool hasLeftChild(int ind) { return getLeftChildIndex(ind) < tree.size(); }
        bool hasRightChild(int ind) { return getRightChildIndex(ind) < tree.size(); } 
        
        int getParent(int ind) { return tree[getParentIndex(ind)]; }
        int getLeftChild(int ind) { return tree[getLeftChildIndex(ind)]; }
        int getRightChild(int ind) { return tree[getRightChildIndex(ind)]; }
        
        void heapifyUp(int ind) {
            int parent = hasParent(ind) ? getParent(ind) : INT_MIN; 
            int current = tree[ind];
            if(current < parent) {
                int parentIndex = getParentIndex(ind);
                swap(tree[ind],tree[parentIndex]);
                heapifyUp(parentIndex);
            }   
            return;
        }
        
        void heapifyDown(int ind) {
            int leftChild = hasLeftChild(ind) ? getLeftChild(ind) : INT_MAX;
            int rightChild = hasRightChild(ind) ? getRightChild(ind) : INT_MAX;
            int current = tree[ind];
            
            if(leftChild == INT_MAX && rightChild == INT_MAX) return;
            if(current <= leftChild && current <= rightChild) return;
            
            int smallerChildIndex = getLeftChildIndex(ind);
            if(leftChild > rightChild) {
                smallerChildIndex = getRightChildIndex(ind);
            }
            
            swap(tree[ind],tree[smallerChildIndex]);
            heapifyDown(smallerChildIndex);
            return;
        }
        
    public:
        void insert(int val) {
            tree.push_back(val);
            int ind = tree.size() - 1;
            heapifyUp(ind);
            return;
        } 
          
        int top() {
            return tree.size() >=0 ? tree[0] : -1;
        }
        
        void pop() {
            if(tree.size() == 0) return;
            int currentSize = tree.size();
            tree[0] = tree[currentSize-1];
            tree.pop_back();
            heapifyDown(0);
            return;
        }
};

int main() {
    MinHeap *heap = new MinHeap();
    heap -> insert(2);
    heap -> insert(1);
    heap -> insert(3);
    heap -> insert(2);
    cout<<heap->top()<<endl;
    heap -> pop();
    cout<<heap->top()<<endl;
    heap -> pop();
    cout<<heap->top()<<endl;
    heap -> pop();
    cout<<heap->top()<<endl;
    return 0;
}
