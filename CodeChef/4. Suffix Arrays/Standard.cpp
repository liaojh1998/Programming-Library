//Suffix Array Template
//https://discuss.codechef.com/questions/21385/a-tutorial-on-suffix-arrays
//http://stackoverflow.com/questions/34402080/suffix-array-construction-on-logn-competitive-programming-3-steven-halim
#include <bits/stdc++.h>
using namespace std;

//Builds an increasing ASCII number order sorted array of string suffix
//Of course, it can build a sorted array of any list suffix
//The trick is to use itself in the process to optimize string sort in powers of 2
template<typename T> class SuffixArray{
private:
	int* arr; //Array of objects
	int* P; //Position array for suffixes, suffix starting at i should be the P(i)th string in the sorted order, this is also the SA^-1
	int* SA; //Actual Suffix Array
	size_t N, k; //Size of string, steps required for algorithm

	//Change this for ranking of nodes, make sure it returns an int
	//Currently for ASCII
	int rank(const T& c){
		return c+1;
	}
	//Structure to concatenate suffix arraries for comparison
	struct comb{
		int a, b;
		size_t p;
		//Comparison function for suffix arraries, currently in increasing order, may be changed for decreasing order
		bool operator<(const comb& c) const{
			return a == c.a ? b < c.b : a < c.a;
		}
	};

public:
	//Useful functions
	//Constructors: a - array, N - size of array
	SuffixArray(T* a, size_t n){
		N = n;
		k = (size_t)ceil(log2(N));
		arr = new int[N];
		for(int i = 0; i < N; i++)
			arr[i] = rank(a[i]);
		P = new int[(k+1)*N];
		SA = new int[N];
	}
	//Destructor
	~SuffixArray(){
		delete[] arr;
		delete[] P;
		delete[] SA;
	}
	//Suffix Array accessor
	int& operator[](const size_t& i){
		return SA[i];
	}

	//Constructing Suffix Array algorithm
	//Runs in O(N lg^2 N)
	//May be improved to O(N lg N) by using radix sort
	void exec(){
		for(size_t i = 0; i < N; i++)
			P[i] = arr[i];
		comb L[N];
		for(size_t step = 1, concatenateLength = 1; concatenateLength < N; step++, concatenateLength <<= 1){
			for(size_t i = 0; i < N; i++){
				L[i].a = P[(step-1)*N + i];
				L[i].b = i + concatenateLength < N ? P[(step-1)*N + i + concatenateLength] : -1;
				L[i].p = i;
			}
			sort(L, L+N); //May be improved with radix, but radix is based fully on digit amount, giving O(kN) where k is max digit, notice that O(kN lg N) can be > O(N lg^2 N)
			for(size_t i = 0; i < N; i++)
				P[step*N + L[i].p] = i > 0 && L[i].a == L[i-1].a && L[i].b == L[i-1].b ? P[step*N + L[i-1].p] : i;
		}
		for(size_t i = 0; i < N; i++)
			SA[P[k*N + i]] = i;
	}
};

int main(){
	//Enter code here
	return 0;
}