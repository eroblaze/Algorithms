#include "bits/stdc++.h"

#define db1(x) cout<< #x <<" = "<< x <<'\n'
#define db2(x,y) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<'\n'
#define db3(x,y,z) cout<< #x <<" = "<< x <<", "<< #y <<" = "<< y <<", "<< #z <<" = "<< z <<'\n'

using namespace std;
using ll = long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VPII = vector<PII>;

// Reads N input into V
template <typename T>
void create_vector(T&, int);

template <typename T>
void display_contents(const T&);

struct Node {
    int m_val{0};
    Node* m_next;
    Node(int val, Node* next = nullptr): m_val(val), m_next(next) {}
    bool operator == (Node* b) {return m_val == b->m_val;}
};

Node* Floyd_tortoise_hare(Node* list) {
    auto getNext = [&](Node* n){return n->m_next;};
    Node* a = getNext(list); // slow pointer
    Node* b = getNext(getNext(list)); // fast pointer

    while ((a != nullptr && b != nullptr) && (a != b)) {
        a = getNext(a);
        b = getNext(getNext(b));
    }
    // find the node starting the cycle
    a = list;
    while ((a != nullptr && b != nullptr) && (a != b)) {
        a = getNext(a);
        b = getNext(b);
    }

    if (a == b) {
        // a is the node starting the cycle;
        cout<<"Found the node -> "<<a->m_val<<"\n";
    }
    // Find the length of the cycle
    int cycle_length = 1;
    b = getNext(b);
    while ((a != nullptr && b != nullptr) && (a != b)) {
        b = getNext(b);
        ++cycle_length;
    }
    db1(cycle_length);

    return a;
}

void solve() {
    Node arr[] = {{1},{2},{3},{4},{5},{6}};

    for (int i = 0; i < 5; ++i) {
        arr[i].m_next = &arr[i+1];
    }
    arr[5].m_next = &arr[3];

    Node* head = &arr[0];

    Node* cycle_node = Floyd_tortoise_hare(head);
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
      solve();
    }

    return 0;
}

template <typename T>
void create_vector(T& V, int N) {
    V.resize(N);
    for (int i = 0; i < N; ++i)    
        cin>>V[i];
}

template <typename T>
void display_contents(const T& ds) {
    for (auto& el: ds) {
        cout<<el<<", ";
    }
    cout<<"\n";
}