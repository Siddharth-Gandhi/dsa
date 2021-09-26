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
    void print()
    {
        printf("(%d, %d)", x, y);
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

vector<vector<int>> aStarEnhanced(int startRow, int startCol, int endRow,
                                  int endCol, vector<vector<char>> graph, bool toTarget = false)
{
    // Write your code here.
    int len = graph.size();
    int wid = graph[0].size();
    vector<vector<int>> path = {};
    vector<Coordinate> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
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
            if (isInside(newPt) && graph[newPt.x][newPt.y] != '#')
            {
                neighbours.push_back(newPt);
            }
        }
        return neighbours;
    };

    auto getParallelNeighbours = [&](Coordinate pt)
    {
        vector<Coordinate> neighbours = {};
        for (int i = 0; i < 4; i += 2)
        {
            Coordinate newPt = {pt.x + directions[i].x, pt.y + directions[i].y};
            Coordinate oppPt = {pt.x + directions[i + 1].x, pt.y + directions[i + 1].y};
            if (isInside(newPt) && graph[newPt.x][newPt.y] != '#' && isInside(oppPt) && graph[oppPt.x][oppPt.y] != '#')
            {
                neighbours.push_back(newPt);
                neighbours.push_back(oppPt);
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
        Coordinate curPt = curNodeInfo->curPt;
        visited[curPt.x][curPt.y] = true;
        if (curPt == endPt)
        {
            path.push_back({endPt.x, endPt.y});
            while (true)
            {
                // cout << path << endl;
                NodeInfo *prevNodeInfo = curNodeInfo->prevNodeInfo;
                if (prevNodeInfo == nullptr)
                {
                    break;
                }

                // TODO: a linked list style structure [x]
                path.push_back({prevNodeInfo->curPt.x, prevNodeInfo->curPt.y});
                curNodeInfo = prevNodeInfo;
            }
            break;
        }
        vector<Coordinate> neighbours = toTarget ? getParallelNeighbours(curPt) : getNeighbours(curPt);
        for (auto neigh : neighbours)
        {

            if (!visited[neigh.x][neigh.y])
            {
                // not visited this neighbour;
                int endDist = abs(neigh.x - endPt.x) + abs(neigh.y - endPt.y);
                int startDist = abs(neigh.x - startPt.x) + abs(neigh.y - startPt.y);
                pQueue.push(new NodeInfo(neigh, curNodeInfo, startDist, endDist, startDist + endDist));
            }
        }
    }
    reverse(path.begin(), path.end());
    return path;
}
int minPushBox(vector<vector<char>> &grid)
{
    int startX, startY, endX, endY, boxX, boxY;
    int len = grid.size();
    int wid = grid[0].size();
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < wid; ++j)
        {
            if (grid[i][j] == 'S')
            {
                startX = i;
                startY = j;
            }
            if (grid[i][j] == 'B')
            {
                boxX = i;
                boxY = j;
            }
            if (grid[i][j] == 'T')
            {
                endX = i;
                endY = j;
            }
        }
    }
    vector<Coordinate> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<int>> pathToBox = aStarEnhanced(startX, startY, boxX, boxY, grid);
    Coordinate personPt = pathToBox[(int)pathToBox.size() - 2];
    if (pathToBox.size() == 0)
    {
        return -1;
    }
    vector<vector<int>> pathToTarget = aStarEnhanced(boxX, boxY, endX, endY, grid, true);
    return pathToTarget.size() - 1;
}

int main()
{
    vector<vector<char>> graph = {{'#', '.', '.', '#', '#', '#', '#', '#'},
                                  {'#', '.', '.', 'T', '#', '.', '.', '#'},
                                  {'#', '.', '.', '.', '#', 'B', '.', '#'},
                                  {'#', '.', '.', '.', '.', '.', '.', '#'},
                                  {'#', '.', '.', '.', '#', '.', 'S', '#'},
                                  {'#', '.', '.', '#', '#', '#', '#', '#'}};
    cout << minPushBox(graph);
}
