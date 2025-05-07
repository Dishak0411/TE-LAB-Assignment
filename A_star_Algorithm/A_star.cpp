#include <bits/stdc++.h>
using namespace std;

const int N = 3;

struct PuzzleState
{
    vector<vector<int>> board;
    int x, y;             // position of the blank tile (0)
    int g, h;             // g = cost so far, h = heuristic cost
    vector<string> moves; // move sequence to reach this state

    PuzzleState(vector<vector<int>> b, int gx, int gy, int cost, vector<string> m)
        : board(b), x(gx), y(gy), g(cost), moves(m)
    {
        h = calculateHeuristic();
    }

    int calculateHeuristic()
    {
        int dist = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                int val = board[i][j];
                if (val != 0)
                {
                    int targetX = (val - 1) / N;
                    int targetY = (val - 1) % N;
                    dist += abs(i - targetX) + abs(j - targetY);
                }
            }
        }
        return dist;
    }

    int f() const
    {
        return g + h;
    }
};

struct ComparePuzzleState
{
    bool operator()(const PuzzleState &a, const PuzzleState &b) const
    {
        return a.f() > b.f(); // min-heap
    }
};

string serialize(vector<vector<int>> &board)
{
    string key;
    for (auto &row : board)
        for (int val : row)
            key += to_string(val);
    return key;
}

bool isGoal(vector<vector<int>> &board)
{
    int target = 1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i == 2 && j == 2)
            {
                if (board[i][j] != 0)
                    return false;
            }
            else if (board[i][j] != target++)
            {
                return false;
            }
    return true;
}

void printBoard(vector<vector<int>> &board)
{
    for (auto &row : board)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

void solvePuzzle(vector<vector<int>> startBoard)
{
    int x, y;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (startBoard[i][j] == 0)
            {
                x = i, y = j;
                break;
            }

    priority_queue<PuzzleState, vector<PuzzleState>, ComparePuzzleState> pq;
    set<string> visited;

    pq.emplace(startBoard, x, y, 0, vector<string>());

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    string dir[] = {"UP", "DOWN", "LEFT", "RIGHT"};

    while (!pq.empty())
    {
        auto state = pq.top();
        pq.pop();
        string key = serialize(state.board);

        if (visited.count(key))
            continue;
        visited.insert(key);

        if (isGoal(state.board))
        {
            cout << "Solved in " << state.g << " moves:\n";
            for (string &m : state.moves)
                cout << m << " ";
            cout << "\nFinal board:\n";
            printBoard(state.board);
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            int newX = state.x + dx[i];
            int newY = state.y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N)
            {
                vector<vector<int>> newBoard = state.board;
                swap(newBoard[state.x][state.y], newBoard[newX][newY]);

                vector<string> newMoves = state.moves;
                newMoves.push_back(dir[i]);

                pq.emplace(newBoard, newX, newY, state.g + 1, newMoves);
            }
        }
    }

    cout << "No solution found!\n";
}

int main()
{
    vector<vector<int>> initial = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}};

    solvePuzzle(initial);
    return 0;
}
