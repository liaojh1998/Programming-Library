#include <bits/stdc++.h>
using namespace std;

bool f(const long long& dist, long long *arr, int C, int N){
	int loc = 0;
	while(--C && loc < N){
		int lo = loc+1, hi = N, mid;
		long long val = arr[loc] + dist;
		while(lo < hi){
			mid = lo + (hi-lo)/2;
			if(arr[mid] < val) //Index of first element greater or equal to new val
				lo = mid + 1;
			else
				hi = mid;
		}
		loc = lo;
	}
	return (C == 0 && loc < N);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int T;
	cin >> T;
	while(T--){
		int N, C;
		long long maxi = 0;
		cin >> N >> C;
		long long arr[N+5];
		for(int i = 0; i < N; i++){
			cin >> arr[i];
			if(arr[i] > maxi)
				maxi = arr[i];
		}
		//Sort data: O(N*log(N))
		sort(arr, arr+N);
		//Binary Search: O(N*log(max(xi)))
		long long lo = 0, hi = maxi, mid;
		while(lo < hi){
			mid = lo + (hi-lo)/2;
			if(f(mid, arr, C, N))
				lo = mid + 1;
			else
				hi = mid;
		}
		cout << lo-1 << endl;
	}
	return 0;
}