#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//Read
	int N;
	cin >> N;
	int arr[N+5];
	for(int i = 0; i < N; i++)
		cin >> arr[i];
	//Sparse Table
	int min_sparse_table[N+5][static_cast<int>(log2(N))+2];
	for(int i = 0; i < N; i++)
		min_sparse_table[i][0] = i;
	for(int j = 1; 1 << j <= N; j++)
		for(int i = 0; i + (1<<j) - 1 < N; i++)
			if(arr[min_sparse_table[i][j-1]] < arr[min_sparse_table[i+(1<<(j-1))][j-1]])
				min_sparse_table[i][j] = min_sparse_table[i][j-1];
			else
				min_sparse_table[i][j] = min_sparse_table[i+(1<<(j-1))][j-1];
	int max_sparse_table[N+5][static_cast<int>(log2(N))+2];
	for(int i = 0; i < N; i++)
		max_sparse_table[i][0] = i;
	for(int j = 1; 1 << j <= N; j++)
		for(int i = 0; i + (1<<j) - 1 < N; i++)
			if(arr[max_sparse_table[i][j-1]] > arr[max_sparse_table[i+(1<<(j-1))][j-1]])
				max_sparse_table[i][j] = max_sparse_table[i][j-1];
			else
				max_sparse_table[i][j] = max_sparse_table[i+(1<<(j-1))][j-1];
	//Query
	int Q, L, R;
	cin >> Q;
	while(Q--){
		cin >> L >> R;
		int k = log2(R-L+1);
		int inrange_min = arr[min_sparse_table[L][k]] < arr[min_sparse_table[R-(1<<k)+1][k]] ? arr[min_sparse_table[L][k]] : arr[min_sparse_table[R-(1<<k)+1][k]];
		int inrange_max = arr[max_sparse_table[L][k]] > arr[max_sparse_table[R-(1<<k)+1][k]] ? arr[max_sparse_table[L][k]] : arr[max_sparse_table[R-(1<<k)+1][k]];
		int left_max = 0;
		if(L){
			int kl = log2(L);
			left_max = arr[max_sparse_table[0][kl]] > arr[max_sparse_table[L-(1<<kl)][kl]] ? arr[max_sparse_table[0][kl]] : arr[max_sparse_table[L-(1<<kl)][kl]];
		}
		int right_max = 0;
		if(N-1 != R){
			int kr = log2(N-R-1);
			right_max = arr[max_sparse_table[R+1][kr]] > arr[max_sparse_table[N-(1<<kr)][kr]] ? arr[max_sparse_table[R+1][kr]] : arr[max_sparse_table[N-(1<<kr)][kr]];
		}
		int true_max = left_max > right_max ? left_max : right_max;
		double inrange_time = static_cast<double>(inrange_max-inrange_min)/2+inrange_min;
		double outrange_time = static_cast<double>(inrange_min+true_max);
		printf("%.1lf\n", inrange_time > outrange_time ? inrange_time : outrange_time);
	}
	return 0;
}