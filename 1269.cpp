#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
 * https://leetcode.com/contest/weekly-contest-164/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
 * 这个题可以看成一个需要剪枝的dp问题，我的主要思路是：把一共的步数n分类，分成不动的移动的，于是总的方法数就等于 C_n^m + (n-m)/2对括号的卡特兰问题了，
 * 这个括号的卡特兰问题需要剪枝，因为有arrLen的限制，可以用dp解决。
 */
const int MAX = 1e+9+7;
const int max_steps = 500;

int numWays(int steps, int arrLen) {
    arrLen--;
    vector<vector<int>> dp(max_steps+1, vector<int>(max_steps+1,0));
    dp[0][0]=1;
    for(int i=1;i<=max_steps;i++)
        for(int j=0;j<=i;j++){
            if(j==0){
                dp[i][j]=1;
                continue;
            }
            dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]) % MAX;
        }
    vector<vector<int>> cat(max_steps+1, vector<int>(max_steps+1,0));
    cat[1][1] = 1;
    for(int i=1;i<=max_steps;i++)
        for(int j=i;j<=max_steps;j++){
            if(j-i>arrLen)
                cat[i][j]=0;
            else
                cat[i][j]=(cat[i][j]+cat[i][j-1]+cat[i-1][j])%MAX;
        }
    int res = 0;
    for(int cnt=0;cnt<=steps;cnt++){
        if((steps-cnt)%2==1)
            continue;
        int c=(steps-cnt)/2+1;
        res = (res+((long long)(dp[steps][cnt])*cat[c][c]))%MAX;
    }
    return res;
}

int main()
{
    cout<<numWays(27, 7)<<endl;
    return 0;
}