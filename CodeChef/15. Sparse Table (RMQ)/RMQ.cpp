//Sparse table template, including a tutorial on the RMQ
//using different offline techniques of DP, sqrt buckets, and sparse table itself
//For online refer to segment trees
//https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/#Trivial_algorithms_for_RMQ
#include <bits/stdc++.h>
using namespace std;

template<typename T> class RMQ{
private:
	T *arr;
	int **dptable, *sqrttable, **sttable;
	int N, bucket_size, height;

	bool cmp(const int& a, const int& b){
		return arr[a] < arr[b];
	}

public:
	RMQ(T *a, const int& n){
		//Processed from left to right, so the smaller index come first for equality cases
		N = n;
		arr = a;
		dptable = NULL;
		sqrttable = NULL;
		sttable = NULL;
	}
	~RMQ(){
		if(dptable != NULL){
			for(int i = 0; i < N; i++)
				delete[] dptable[i];
			delete[] dptable;
		}
		if(sqrttable != NULL)
			delete[] sqrttable;
		if(sttable != NULL){
			for(int i = 0; i < N; i++)
				delete[] sttable[i];
			delete[] sttable;
		}
	}
	//<f(n), g(n)> where f(n) = processing time complexity, g(n) = querying time complexity
	//All queries are: [a, b]
	//Naive: <None, O(N)>
	int query(int a, int b){
		int k = a;
		for(int i = a+1; i <= b; i++)
			if(cmp(i, k))
				k = i;
		return k;
	}
	//DP technique: <O(N^2), O(1)>
	void dpprocess(){
		//Dynamic allowcation, don't do this in competitions, make it global
		dptable = new int*[N];
		for(int i = 0; i < N; i++)
			dptable[i] = new int[N+5];
		//DP
		for(int i = 0; i < N; i++)
			dptable[i][i] = i;
		for(int i = 0; i < N; i++)
			for(int j = i+1; j < N; j++)
				if(cmp(dptable[i][j-1], j))
					dptable[i][j] = dptable[i][j-1];
				else
					dptable[i][j] = j;
	}
	int dpquery(int a, int b){
		return dptable[a][b];
	}
	//Sqrt buckets technique: <O(N), O(sqrt(N))>, 0-based indexing
	void sqrtprocess(){
		bucket_size = sqrt(N); //Or some specific size, if preferred
		int size = N/bucket_size + (N % bucket_size ? 1 : 0);
		sqrttable = new int[size+5];
		for(int i = 0; i < size; i++){
			int k = i*bucket_size, limit = (i+1)*bucket_size;
			for(int j = k+1; j < N && j < limit; j++)
				if(cmp(j, k))
					k = j;
			sqrttable[i] = k;
		}
	}
	int sqrtquery(int a, int b){
		int k = a;
		//Base case
		if(b-a+1 <= bucket_size){
			for(int i = a; i <= b; i++)
				if(cmp(i, k))
					k = i;
			return k;
		}
		//First section
		if(a%bucket_size){
			int limit = (a/bucket_size+1)*bucket_size;
			for(int i = a+1; i < limit; i++)
				if(cmp(i, k))
					k = i;
		}else{
			k = sqrttable[a/bucket_size];
		}
		//Second section
		int limit = b/bucket_size;
		for(int i = a/bucket_size+1; i < limit; i++)
			if(cmp(sqrttable[i], k))
				k = sqrttable[i];
		//Third section
		if((b+1)%bucket_size){
			for(int i = (b/bucket_size)*bucket_size; i <= b; i++)
				if(cmp(i, k))
					k = i;
		}else{
			if(cmp(sqrttable[b/bucket_size], k))
				k = sqrttable[b/bucket_size];
		}
		return k;
	}
	//Sparse table technique: <O(N*log(N)), O(1)>
	void stprocess(){
		height = static_cast<int>(log2(N))+2;
		//Dynamic allowcation, don't do this in competitions, make it global
		sttable = new int*[N];
		for(int i = 0; i < N; i++){
			sttable[i] = new int[height+5];
			sttable[i][0] = i; //Initiation, needed for the sparse table
		}
		//Sparse Table
		for(int j = 1; (1<<j) <= N; j++)
			for(int i = 0; (i+(1<<j)-1) < N; i++)
				if(cmp(sttable[i][j-1], sttable[i+(1<<(j-1))][j-1]))
					sttable[i][j] = sttable[i][j-1];
				else
					sttable[i][j] = sttable[i+(1<<(j-1))][j-1];
	}
	int stquery(int a, int b){
		int k = log2(b-a+1); //special cases may arise, be careful, especially for length 0 cases
		return cmp(sttable[b-(1<<k)+1][k], sttable[a][k]) ? sttable[b-(1<<k)+1][k] : sttable[a][k];
	}
};

int main(){
	//Enter code here
	return 0;
}