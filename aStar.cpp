#include <bits/stdc++.h>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &v)
{
    os << "[";
    for (int i = 0; i < (int)v.size(); ++i)
    {
        os << "(" << v[i][0] << "," << v[i][1] << ")";
        if (i != (int)v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

struct Coordinate
{
    int x;
    int y;
    Coordinate(int a, int b) : x(a), y(b) {}
    bool operator<(const Coordinate &a) const
    {
        return (x < a.x || (x == a.x && y < a.y));
    }
    bool operator==(const Coordinate &a) const
    {
        return (x == a.x && y == a.y);
    }
};

struct NodeInfo
{
    Coordinate curPt;
    NodeInfo *prevNodeInfo;
    int startDist;
    int endDist;
    int totalDist;
    NodeInfo(Coordinate pt, NodeInfo *prev, int sd, int ed, int td) : curPt(pt), prevNodeInfo(prev), startDist(sd), endDist(ed), totalDist(td) {}
    bool operator<(const NodeInfo &n) const
    {
        return (totalDist <= n.totalDist);
    }
};

struct CompareTotalDist
{
    bool operator()(const NodeInfo *a, const NodeInfo *b) const
    {
        return a->totalDist > b->totalDist;
    }
};

vector<vector<int>> aStarAlgorithm(int startRow, int startCol, int endRow,
                                   int endCol, vector<vector<int>> graph)
{
    // Write your code here.
    int len = graph.size();
    int wid = graph[0].size();
    vector<vector<int>> path = {};
    vector<Coordinate> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<bool>> visited(len, vector<bool>(wid));

    auto isInside = [&](Coordinate pt)
    {
        return 0 <= pt.x && pt.x < len && 0 <= pt.y && pt.y < wid;
    };

    auto getNeighbours = [&](Coordinate pt)
    {
        vector<Coordinate> neighbours = {};
        for (auto dir : directions)
        {
            Coordinate newPt = {pt.x + dir.x, pt.y + dir.y};
            if (isInside(newPt) && graph[newPt.x][newPt.y] == 0)
            {
                neighbours.push_back(newPt);
            }
        }
        return neighbours;
    };

    Coordinate startPt = {startRow, startCol};
    Coordinate endPt = {endRow, endCol};
    priority_queue<NodeInfo *, vector<NodeInfo *>, CompareTotalDist> pQueue;

    int startToendDist = abs(startPt.x - endPt.x) + abs(startPt.y - endPt.y);
    NodeInfo startNodeInfo = {startPt, nullptr, 0, startToendDist, startToendDist};
    pQueue.push(&startNodeInfo);

    while (!pQueue.empty())
    {
        // assuming all coordinates in pQueue are unvisted
        NodeInfo *curNodeInfo = pQueue.top();
        pQueue.pop();
        // pQueue.pop();
        Coordinate curPt = curNodeInfo->curPt;
        // visited.insert(curPt);
        visited[curPt.x][curPt.y] = true;
        if (curPt == endPt)
        {
            path.push_back({endPt.x, endPt.y});
            while (true)
            {
                cout << path << endl;
                NodeInfo *prevNodeInfo = curNodeInfo->prevNodeInfo;
                if (prevNodeInfo == nullptr)
                {
                    break;
                }

                // TODO: a linked list style structure?
                path.push_back({prevNodeInfo->curPt.x, prevNodeInfo->curPt.y});
                curNodeInfo = prevNodeInfo;
            }
            break;
        }
        vector<Coordinate> neighbours = getNeighbours(curPt);
        for (auto neigh : neighbours)
        {
            if (!visited[neigh.x][neigh.y])
            {
                // not visited this neighbour;
                int endDist = abs(neigh.x - endPt.x) + abs(neigh.y - endPt.y);
                int startDist = abs(neigh.x - startPt.x) + abs(neigh.y - startPt.y);
                // NodeInfo nodeinfo = {};
                pQueue.push(new NodeInfo(neigh, curNodeInfo, startDist, endDist, startDist + endDist));
            }
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    auto startRow = 1;
    auto startCol = 1;
    auto endRow = 1;
    auto endCol = 1;
    vector<vector<int>> graph = {
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}};
    aStarAlgorithm(startRow, startCol, endRow, endCol, graph);
}