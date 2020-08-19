#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <utility>

using namespace std;
  
// QItem for current location and distance 
// from source location 
class QItem { 
public: 
    int row; 
    int col; 
    int dist; 
    
    QItem(int x, int y, int w) 
        : row(x), col(y), dist(w) 
    { 
    } 
}; 

class Visited {
public:
    bool visited;
    pair<int, int> prev;

    Visited() {
        visited = false;
        prev = pair<int, int> (-1, -1);
    }
};
  
int minDistance(vector<vector<char>>& grid, int fuel) 
{ 
    QItem source(0, 0, 0); 
    int rows = grid.size();
    int columns = grid[0].size();

    // To keep track of visited QItems. Marking 
    // blocked cells as visited. 
    vector<vector<Visited>> visited(rows, vector<Visited>(columns));
    for (int i = 0; i < rows; i++) { 
        for (int j = 0; j < columns; j++) 
        { 
            if (grid[i][j] == '#') 
                visited[i][j].visited = true; 
            else
                visited[i][j].visited = false; 
  
            // Finding source 
            if (grid[i][j] == 'R') 
            { 
               source.row = i; 
               source.col = j; 
            } 
        } 
    }
  
    // applying BFS on matrix cells starting from source 
    queue<QItem> q; 
    q.push(source); 
    visited[source.row][source.col].visited = true; 
    while (!q.empty()) { 
        QItem p = q.front(); 
        q.pop(); 
        // Fuel constraint
        // If p.distance = 45, do not add neighbors
        // Destination found; 
        if (grid[p.row][p.col] == 'G') {
            pair<int, int> path = visited[p.row][p.col].prev;            
            while (grid[path.first][path.second] != 'R') {
                grid[path.first][path.second] = 'O';
                path = visited[path.first][path.second].prev;
            }
            return p.dist; 
        }

        if (p.dist <= fuel) {
            // moving up 
            if (p.row - 1 >= 0 && 
                visited[p.row - 1][p.col].visited == false) { 
                if (grid[p.row][p.col] == '+') {
                    q.push(QItem(p.row - 1, p.col, 0)); 
                }
                else{
                    q.push(QItem(p.row - 1, p.col, p.dist + 1)); 
                }
                visited[p.row - 1][p.col].visited = true; 
                visited[p.row - 1][p.col].prev = pair<int, int> (p.row, p.col);
            } 
    
            // moving down 
            if (p.row + 1 < rows && 
                visited[p.row + 1][p.col].visited == false) { 
                if (grid[p.row][p.col] == '+') {
                    q.push(QItem(p.row + 1, p.col, 0)); 
                }
                else{
                    q.push(QItem(p.row + 1, p.col, p.dist + 1)); 
                }
                visited[p.row + 1][p.col].visited = true; 
                visited[p.row + 1][p.col].prev = pair<int, int> (p.row, p.col);
            } 
    
            // moving left 
            if (p.col - 1 >= 0 && 
                visited[p.row][p.col - 1].visited == false) { 
                if (grid[p.row][p.col] == '+') {
                    q.push(QItem(p.row, p.col - 1, 0)); 
                }
                else{
                    q.push(QItem(p.row, p.col - 1, p.dist + 1)); 
                }
                visited[p.row][p.col - 1].visited = true; 
                visited[p.row][p.col - 1].prev = pair<int, int> (p.row, p.col);
            } 
    
            // moving right 
            if (p.col + 1 < columns && 
                visited[p.row][p.col + 1].visited == false) { 
                if (grid[p.row][p.col] == '+') {
                    q.push(QItem(p.row, p.col + 1, 0)); 
                }
                else{
                    q.push(QItem(p.row, p.col + 1, p.dist + 1)); 
                }
                visited[p.row][p.col + 1].visited = true; 
                visited[p.row][p.col + 1].prev = pair<int, int> (p.row, p.col);
            }
        }
         
    } 
    return -1; 
} 

//returns fuel constraint
int read_in_grid(string file_name, vector<vector<char>> &grid) {
    int fuel;
    ifstream file;
    string line;
    file.open(file_name);
    if (file.is_open()) {
        getline(file, line);
        fuel = 25; //TODO
        while(getline(file, line)) {

            vector<char> row;
            for (auto i : line) {
                row.push_back(i);
            }
            grid.push_back(row);
        }
        file.close();
    }
    return fuel;
}

void print_grid(vector<vector<char>> &grid) {
    for (auto i : grid) {
        for (auto j : i) {
            cout << j;
        }
        cout << endl;
    }
}
  
// Driver code 
int main() 
{ 
    cout << stoi("45") << endl;
    vector<vector<char>> grid;
    int fuel;
    fuel = read_in_grid("test3.txt", grid);
    print_grid(grid);
  
    if (minDistance(grid, fuel) == -1) {
        cout << "NO SOLUTION";
    }
    else {
        cout << "SOLUTION GRID:\n";
        print_grid(grid);
    }
    return 0; 
} 
