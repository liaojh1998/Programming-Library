//Suffix Array Counting Sort Template
//http://www.cnblogs.com/staginner/archive/2012/02/02/2335600.html
//Refer to CP3 for algorithm as well
#include <bits/stdc++.h>
using namespace std;

//Builds an increasing ASCII number order sorted array of string suffix
//Of course, it can build a sorted array of any list suffix
//Improved by radix sort
template<typename T> class SuffixArray{
private:
	int* arr; //Array of objects, ranked with int
	int* SA; //Suffix Array
	size_t N; //Size of string

	//Change this for ranking of nodes, make sure it returns an int
	//Currently for ASCII
	int rank(const T& c){
		return c+1;
	}
	//Improved sorting, based on radix sort, or called counting sort
	void countingSort(size_t concatenateLength, size_t keycount){
		size_t maxRange = keycount > N ? keycount : N;
		int tempSA[N], count[maxRange];
		memset(count, 0, sizeof(count));
		for(size_t i = 0; i < N; i++)
			count[i + concatenateLength < N ? arr[i + concatenateLength] : 0]++;
		int sum = 0;
		for(size_t i = 0; i < maxRange; i++){
			int t = count[i];
			count[i] = sum;
			sum += t; //Exclusive prefix sums
		}
		for(size_t i = 0; i < N; i++) //Rearrange and sort
			tempSA[count[SA[i] + concatenateLength < N ? arr[SA[i] + concatenateLength] : 0]++] = SA[i];
		for(size_t i = 0; i < N; i++)
			SA[i] = tempSA[i]; //Return sorted SA
	}

public:
	//Useful functions
	//Constructors: a - array, N - size of array
	SuffixArray(T* a, size_t n){
		N = n+1;
		arr = new int[N+1];
		for(int i = 0; i < N; i++)
			arr[i] = rank(a[i]);
		arr[n] = 0;
		SA = new int[N+1]; //1 based indexing due to extra 0 at the end to correctly sort out suffix arrays
	}
	//Destructor
	~SuffixArray(){
		delete[] arr;
		delete[] SA;
	}
	//Suffix Array accessor
	int& operator[](const size_t& i){
		return SA[i+1];
	}
	//Suffix Array address accessor
	int* getSA(){
		return SA; //Remember that it's 1 based indexing
	}

	//Constructing Suffix Array algorithm
	//Runs in O(NlogN)
	//Keycount for radix sort if more than 255 ASCII characters
	void exec(int keycount = 255){
		for(size_t i = 0; i < N; i++)
			SA[i] = i;
		int tempRank[N];
		for(size_t k = 1; k < N; k <<= 1){
			countingSort(k, keycount+1);
			countingSort(0, keycount+1); //Similar to the sorting done in N log^2 N, sort based by k before 0
			int Rank;
			tempRank[SA[0]] = Rank = 0;
			for(size_t i = 1; i < N; i++) //Rerank
				tempRank[SA[i]] = (arr[SA[i-1]] == arr[SA[i]] && (SA[i-1]+k < N ? arr[SA[i-1]+k] : -1) == (SA[i]+k < N ? arr[SA[i]+k] : -1)) ? Rank : ++Rank;
			for(size_t i = 0; i < N; i++) //Return sorted rank
				arr[i] = tempRank[i];
			if(arr[SA[N-1]] == N-1) //If no string character is distinct, rank should already sorted and suffix array should be the same
				break;
		}
	}
};

int main(){
	//Enter code here
	return 0;
}