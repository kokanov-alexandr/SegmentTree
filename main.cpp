#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SegmentTree {
    vector<long long> Tree;
    int Size;

    SegmentTree(vector<int> &Array) {
        Size = 1;
        while (Size < Array.size()) {
            Size *= 2;
        }
        Tree.assign(2 * Size - 1, 0);
        Build(Array, 0, 0, Size);
    }

    void Build(vector<int> &Array, int NumberNode, int LeftNode, int RightNode) {
        if (RightNode - LeftNode == 1) {
            if (LeftNode < Array.size()) {
                Tree[NumberNode] = Array[LeftNode];
            }
        }
        else {
            int Middle = (LeftNode + RightNode) / 2;
            Build(Array, 2 * NumberNode + 1, LeftNode, Middle);
            Build(Array, 2 * NumberNode + 2, Middle, RightNode);
            Tree[NumberNode] = Tree[2 * NumberNode + 1] + Tree[2 * NumberNode + 2];
        }
    }

    void Set(int Index, int Value, int NumberNode, int LeftNode, int RightNode) {
        if (RightNode - LeftNode == 1) {
            Tree[NumberNode] = Value;
            return;
        }
        int Middle = (LeftNode + RightNode) / 2;
        if (Index < Middle) {
            Set(Index, Value, 2 * NumberNode + 1, LeftNode, Middle);
        }
        else {
            Set(Index, Value, 2 * NumberNode + 2, Middle, RightNode);
        }
        Tree[NumberNode] = Tree[2 * NumberNode + 1] + Tree[2 * NumberNode + 2];

    }

    void Set(int Index, int Value) {
        Set(Index, Value, 0, 0, Size);
    }

    long long Sum(int Left, int Right, int NumberNode, int LeftNode, int RightNode) {
        if (Left >= RightNode || Right <= LeftNode) {
            return 0;
        }
        if (Left <= LeftNode && Right >= RightNode) {
            return Tree[NumberNode];
        }
        int Middle = (LeftNode + RightNode) / 2;
        return Sum(Left, Right, 2 * NumberNode + 1, LeftNode, Middle) + Sum(Left, Right, 2 * NumberNode + 2, Middle, RightNode);
    }

    long long Sum(int Left, int Right) {
        return Sum(Left, Right, 0, 0, Size);
    }
};
