#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    int n=grid.size(),m=grid[0].size();
    vector<vector<int>> res(n,vector<int>(m,0));
    k = k%(n*m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            int ni=(i+(j+k)/m)%n;
            int nj=(j+k)%m;
            res[ni][nj]=grid[i][j];
        }
    return res;
}

int main() {
    vector<vector<int>> grid={{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> res = shiftGrid(grid, 1);
    return 0;
}