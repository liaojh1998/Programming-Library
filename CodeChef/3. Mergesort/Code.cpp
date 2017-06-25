#include <bits/stdc++.h>
using namespace std;

template<typename T> class Mergesort{
private:
	T* arr;
	int N;
	//Comparison
	bool cmp(const T& a, const T& b){
		return a < b;
	}
	//Recursion function
	void merge_sort(int* a, int lo, int hi){
		if(lo == hi)
			a[0] = arr[lo];
		else{
			int mid = (lo+hi)/2, len1 = mid-lo+1, len2 = hi-mid;
			int arr1[len1], arr2[len2];
			merge_sort(arr1, lo, mid);
			merge_sort(arr2, mid+1, hi);
			int i = 0, j = 0;
			while(i < len1 && j < len2) a[i+j] = cmp(arr1[i], arr2[j]) ? arr1[i++] : arr2[j++];
			while(i < len1) a[i+j] = arr1[i++];
			while(j < len2) a[i+j] = arr2[j++];
		}
	}

public:
	Mergesort(T* a, int n){
		arr = a;
		N = n;
	}
	void exec(){
		merge_sort(arr, 0, N-1);
	}
};

int main(){
	//Enter code here
	return 0;
}