#include <bits/stdc++.h>
using namespace std;

class TeamBuilder{
public:
    vector<int> specialLocations(vector<string> paths){
        int size = paths.size();
        int dp[size][size];
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
            	dp[i][j] = paths[i][j]-'0';
        for(int k = 0; k < size; k++)
            for(int i = 0; i < size; i++)
            	for(int j = 0; j < size; j++)
            		if(!dp[i][j] && (dp[i][k] & dp[k][j]))
            			dp[i][j] = 1;
        vector<int> ans;
        int from = 0, to = 0;
        for(int i = 0; i < size; i++){
            bool connected = true;
            for(int j = 0; j < size && connected; j++)
                if(j != i && !dp[i][j])
                	connected = false;
            if(connected) from++;
        }
        ans.push_back(from);
        for(int i = 0; i < size; i++){
            bool connected = true;
            for(int j = 0; j < size && connected; j++)
                if(j != i && !dp[j][i])
                	connected = false;
            if(connected) to++;
        }
        ans.push_back(to);
        return ans;
    }
};