#include <bits/stdc++.h>
using namespace std;

template<typename T> class BinarySearch{
private:
	T* arr;
	int N, log;
	//Function for the binary search
	T f(int x){
		//This is just an example of a binary search in a sorted array.
		//If data through a function f() can also be sorted, binary search can find the answer as well.
		return arr[x];
	}

public:
	BinarySearch(T* a, int n){
		arr = a;
		N = n;
		log = 0;
		while((1 << (log+1)) <= N) log++;
	}
	//Standard Binary Search
	int binary_search(const T& value){
		//Returns an index, not an element of the function or array
		//Input lo and hi to be negative if needed
		int lo = 0, hi = N, mid;
		while(lo < hi){ //Change to <= if find last index of element
			mid = lo + (hi - lo)/2; //Rounds down
			if(f(mid) < value) //Finds first index of element greater or equal to value in a less first array, lower_bound
				// <= for element greater than value in a less first array, upper_bound
				// > for element less or equal to value in a greater first array
				// >= for element less to value in a greater first array
				lo = mid+1;
			else
				hi = mid;
		}
		return lo; //Can return N, which is outside of array
	}
	//Meta Binary Search
	int meta_search(const T& value){
		int pos = 0, t = log, posp;
		while(t >= 0){
			posp = pos | (1 << t--);
			if(posp <= N && f(posp-1) < value) //Same rules as above
				pos = posp;
		}
		return pos; //Can return N, which is outside of array
	}
};

int main(){
	//Enter code here
	return 0;
}