#include <bits/stdc++.h>
using namespace std;

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    out << "{";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "}";
    return out;
}

// A[parent] <= A[child]
class MinHeap {
   public:
    vector<int> heap;
    MinHeap() {}
    MinHeap(vector<int> vector) { heap = buildHeap(vector); }

    bool verifyMinHeap(vector<int> &arr, bool printRes = false) {
        if (arr.size() == 0) {
            cout << "Warning: Heap is empty\n";
            return true;
        }
        int n = arr.size();
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            int curIdx = i;
            int leftChildIdx = getLeftChildIdx(curIdx);
            int rightChildIdx = getRightChildIdx(curIdx);
            if (leftChildIdx < n && arr[curIdx] > arr[leftChildIdx]) {
                valid = false;
                break;
            }
            if (rightChildIdx < n && arr[curIdx] > arr[rightChildIdx]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            if (printRes) {
                cout << "IS a heap\n";
            }
            return true;
        }
        if (printRes) {
            cout << "NOT a heap\n";
        }
        return false;
    }

    int getParentIdx(int idx) {
        return (idx - 1) / 2;
    }

    int getLeftChildIdx(int idx) {
        return 2 * idx + 1;
    }

    int getRightChildIdx(int idx) {
        return 2 * idx + 2;
    }

    vector<int> buildHeap(vector<int> &vector) {
        verifyMinHeap(vector, true);
        int n = vector.size();
        int firstNonLeaf = n / 2 - 1;
        for (int i = firstNonLeaf; i >= 0; --i) {
            siftDown(i, n - 1, vector);
        }
        cout << endl;
        cout << vector << endl;
        verifyMinHeap(vector, true);
        return vector;
    }

    void siftDown(int currentIdx, int endIdx, vector<int> &arr) {
        int leftChild = getLeftChildIdx(currentIdx);
        int rightChid = getRightChildIdx(currentIdx);
        int smallestIdx = currentIdx;
        int n = arr.size();
        if (leftChild < n && arr[currentIdx] > arr[leftChild]) {
            smallestIdx = leftChild;
        }
        if (rightChid < n && arr[smallestIdx] > arr[rightChid]) {
            smallestIdx = rightChid;
        }
        if (smallestIdx != currentIdx) {
            // min-heap property not satisfied
            swap(arr[currentIdx], arr[smallestIdx]);
            siftDown(smallestIdx, arr.size() - 1, arr);
        }
    }

    void siftUp(int currentIdx, vector<int> &arr) {
        int parentIdx = getParentIdx(currentIdx);
        if (parentIdx >= 0 && arr[currentIdx] < arr[parentIdx]) {
            swap(arr[currentIdx], arr[parentIdx]);
            siftUp(parentIdx, arr);
        }
    }

    int peek() {
        if (heap.empty())
            return -1;
        return heap[0];
    }

    int remove() {
        if (heap.empty()) return -1;
        int n = heap.size();
        int root = heap[0];
        swap(heap[0], heap[n - 1]);

        heap.resize(n - 1);
        siftDown(0, heap.size() - 1, heap);
        return root;
    }

    void insert(int value) {
        heap.push_back(value);
        int n = heap.size();
        siftUp(n - 1, heap);
    }

    void showHeap() {
        cout << heap << " ";
        verifyMinHeap(heap, true);
        cout << endl;
    }
};

int main() {
    vector<int> arr = {48, 12, 24, 7, 8, -5, 24, 391, 24, 56, 2, 6, 8, 41};
    MinHeap heap = MinHeap(arr);
    heap.insert(76);
    heap.showHeap();
    cout << heap.peek() << endl;
}