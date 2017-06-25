#include <bits/stdc++.h>
using namespace std;

template<typename T> class Quicksort{
//Referenced from Sedgewick
private:
	static const int INSERTION_SORT_CUTOFF = 8;
	static const int MEDIAN_CUTOFF = 40;
	T* arr;
	int N;
	//Comparison
	bool cmp(const T& a, const T& b){
		return a > b;
	}
	//Equal comparison
	bool eq(const T& a, const T& b){
		return a == b; //Make sure objects has equal comparable
	}
	//Swap function
	void swap(T& a, T& b){
		T c = a;
		a = b;
		b = c;
	}
	//Median function
	int med(int a, int b, int c){
		return cmp(arr[a], arr[b]) ? (cmp(arr[b], arr[c]) ? b : cmp(arr[a], arr[c]) ? c : a) : (cmp(arr[c], arr[b]) ? b : cmp(arr[c], arr[a]) ? c : a);
	}
	//Partition function
	void part(int lo, int hi, int& p, int& q){
		if(hi-lo+1 > MEDIAN_CUTOFF){
			//Tukey ninther pivot
			int eps = (hi-lo+1)/8;
			int m = (lo+hi)/2;
			int m1 = med(lo, lo+eps, lo+eps+eps);
			int m2 = med(m-eps, m, m+eps);
			int m3 = med(hi-eps-eps, hi-eps, hi);
			m = med(m1, m2, m3);
			swap(arr[lo], arr[m]);
		}else{
			//Median-of-three pivot
			int m = med(lo, (lo+hi)/2, hi);
			swap(arr[lo], arr[m]);
		}
		//Bentley-McIlroy 3-way partition
		p = lo, q = hi+1;
		int l = p, r = q;
		T pivot = arr[p];
		while(true){
			while(p < hi && cmp(arr[++p], pivot));
			while(q > lo && cmp(pivot, arr[--q]));
			if(p == q && eq(arr[p], pivot)) swap(arr[p], arr[++l]);
			if(p >= q) break;
			swap(arr[p], arr[q]);
			if(eq(arr[p], pivot)) swap(arr[p], arr[++l]);
			if(eq(arr[q], pivot)) swap(arr[q], arr[--r]);
		}
		p = q+1;
		for(int k = lo; k <= l; k++)
			swap(arr[k], arr[q--]);
		for(int k = hi; k >= r; k--)
			swap(arr[k], arr[p++]);
	}
	//Recursion function
	void quick_sort(int lo, int hi){
		//Optimized on tail-recursion for O(logN) space complexity
		//Not stable sort
		while(hi-lo+1 > INSERTION_SORT_CUTOFF){
			int p, q;
			part(lo, hi, p, q);
			if(q-lo < hi-p){
				quick_sort(lo, q);
				lo = p;
			}else{
				quick_sort(p, hi);
				hi = q;
			}
		}
		//Insertion sort for smaller arrays
		for(int i = lo+1; i <= hi; i++){
			int k = arr[i], j = i;
			while(j >= lo && cmp(k, arr[j-1]))
				arr[j] = arr[--j];
			arr[j] = k;
		}
	}

public:
	Quicksort(T* a, int n){
		arr = a;
		N = n;
		//Just a quick note:
		//GNU C++ Library sort() uses a hybrid of Introsort and Insertion Sort when partition size is smaller, resulting O(N*log(N)) as always.
		//Quick sort average: O(N*log(N))
		//Worst case: O(N^2) when array is sorted in such a manner that partition always give N-1 elements to recurse on.
	}
	void exec(){
		quick_sort(0, N-1);
	}
};

int main(){
	//Enter code here
	return 0;
}