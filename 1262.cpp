#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
 * https://leetcode.com/contest/weekly-contest-163/problems/greatest-sum-divisible-by-three/
 * 这题主要说给一个正整数数组，找出其中最大和使其是3的倍数，主要是动态规划求解
 */

int maxSumDivThree(vector<int>& nums) {
    int mod0=0,mod1=0,mod2=0;
    int a,b,c;
    for(int num:nums){
        if(num%3==0){
            a = mod0?mod0+num:num;
            b = mod1?mod1+num:0;
            c = mod2?mod2+num:0;

        }
        if(num%3==1){
            a = mod2?max(mod0, mod2+num):mod0;
            b = mod0?max(mod1, mod0+num):max(mod1,num);
            c = mod1?max(mod2, mod1+num):mod2;
        }
        if(num%3==2){
            a = mod1?max(mod0, mod1+num):mod0;
            b = mod2?max(mod1, mod2+num):mod1;
            c = mod0?max(mod2, mod0+num):max(mod2,num);
        }
        mod0=a;mod1=b;mod2=c;
    }
    return mod0;
}

int main() {
    vector<int> nums={1,2,3,4,4};
    cout<<maxSumDivThree(nums)<<endl;
}