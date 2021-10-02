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

template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &v) {
    out << "{";
    // size_t last = v.size() - 1;
    out << v.first;
    out << ",";
    out << v.second;
    out << "}";
    return out;
}

class Yeet {
   public:
    int x;
    int y;
    Yeet() {}
    Yeet(int a, int b) : x(a), y(b) {}
};

ostream &operator<<(ostream &out, const Yeet &yeet) {
    out << "(" << yeet.x << " | " << yeet.y << ")";
    return out;
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    cout << arr << endl;
    arr.resize(3);
    cout << arr << endl;
}