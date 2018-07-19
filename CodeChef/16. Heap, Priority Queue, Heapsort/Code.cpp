//https://en.wikipedia.org/wiki/Binary_heap
//Just building my own heap for future references :P
#include <bits/stdc++.h>
using namespace std;

template <class T>
class heap{
private:
	int N, s;
	T* arr; //We can make this dynamically sizeable with vectors

	//Comparison function, for now make it min, change as needed
	//Returns true if take the first one, or false if take the second one
	bool cmp(const T& a, const T& b){
		return a < b;
	}
	//Return the one with the higher priority
	int prioritize(const int& a, const int& b){
		if(b > s)
			return a;
		return cmp(arr[a], arr[b]) ? a : b;
	}
	//Swap
	void swap(const int& a, const int& b){
		T tmp = arr[a];
		arr[a] = arr[b];
		arr[b] = tmp;
	}
	//Push upward if heap properties are broken by a node at index
	void up(int index){
		while(index > 1 && cmp(arr[index], arr[index>>1])){
			swap(index, index>>1);
			index >>= 1;
		}
	}
	//Percolate downward if heap properties are broken by a node at index
	void down(int index){
		int p;
		while(index<<1 <= s && cmp(arr[(p = prioritize(index<<1, index<<1|1))], arr[index])){
			swap(index, p);
			index = p;
		}
	}

public:
	heap(int n){
		N = n; //Give a maximum size
		arr = new T[N+5];
		s = 0;
	}
	~heap(){
		delete[] arr;
	}
	int size(){
		return s+1;
	}
	bool empty(){
		return !s;
	}
	void push(const T& E){
		arr[++s] = E;
		up(s);
	}
	//Assuming not empty
	T top(){
		return arr[1];
	}
	void pop(){
		arr[1] = arr[s--];
		down(1);
	}
	//Build heap in O(N) time, assuming the array size is less than what's allocated.
	//This will replace the entire heap with the contents of the array.
	//New array should have 0-based indexing.
	void build(T* A, int n){
		s = n;
		//Percolate down as new nodes are added
		for(int i = s; i >= 1; i--){
			arr[i] = A[i-1];
			down(i); //Maybe seperate the leaves from the parents if need a strictly better runtime
		}
	}
	//Heapsort, O(N*log(N))
	void sort(T* A, int n){
		build(A, n);
		//Basically, sorted by extracting from the heap
		for(int i = 0; i < n; i++){
			A[i] = top();
			pop();
		}
	}
};

int main(){
	//Enter code here
	return 0;
}