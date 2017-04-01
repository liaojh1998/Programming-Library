//Longest Increasing Subsequence (LIS) template
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

template<int N> struct LIS{
	//Note that the increasing subsequence can be strings, but this is implemented with int
	int arr[N], lis[N];
	void add(int index, int value){
		arr[index] = value;
	}
	//Comparison object, change this if LDS or anything at all to fit desired solution
	bool dpcheck(int a, int b){
		//By default, strictly increasing LIS
		return a < b;
	}
	bool gdpcheck(int a, int b){
		//Match the above, but with the equal if strictly increasing LIS
		return a <= b;
	}

	//DP O(N^2) Solution, can be implemented with output in the if statement
	int dplis(int lim){
		int maxlis = 0;
		memset(lis, 0, sizeof(lis));
		lis[0] = 1;
		for(int i = 1; i < lim; i++)
			for(int j = 0; j < i; j++){
				if(dpcheck(arr[j], arr[i]) && lis[i] < lis[j] + 1){
					lis[i] = lis[j] + 1;
				}
				if(!lis[i])
					lis[i] = 1;
				maxlis = max(maxlis, lis[i]);
			}
		return maxlis;
	}

	//DP-Greedy solution binary search
	int loc[N], len; //Location of lis and print
	vector<int> sub; //LIS subsequence
	int search(int lo, int hi, int index){
		if(lo == hi)
			return lo;
		int mid = (lo + hi)/2;
		if(gdpcheck(arr[index], arr[lis[mid]]))
			return search(lo, mid, index);
		else
			return search(mid+1, hi, index);
	}
	//This gets the output-sensitive subsequence
	void output(int i){
		if(loc[i] == -1)
			return sub.push_back(arr[i]);
		output(loc[i]);
		sub.push_back(arr[i]);
	}
	//Greedy-DP O(NlogN) execution, note that this is an output-sensitive (only print the last LIS in the sequence) solution
	int gdplis(int lim){
		if(!lim)
			return 0;
		len = 1;
		memset(lis, 0, sizeof(lis));
		loc[0] = -1;
		for(int i = 1; i < lim; i++){
			int index = search(0, len, i);
			if(index == len){
				loc[i] = lis[len-1];
				lis[len++] = i;
			}else{
				loc[i] = !index ? -1 : lis[index-1];
				lis[index] = i;
			}
		}
		//Comment this out if output is not needed
		output(lis[len-1]);
		return len;
	}
};

int main(){
	//Enter code here
	return 0;
}