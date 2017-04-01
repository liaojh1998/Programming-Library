//Fenwick's Tree template
//https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
#include <bits/stdc++.h>
using namespace std;

//T - storage data type for the fenwick's tree
template<typename T> class FenTree{
private:
	//Set array to static if using C++11
	T* fwt;
	size_t N;
	//N is useful if possibility of querying out of range

	//Functions that relates child to parent in the segment tree
	//This example apply sum
	T applyfunc(const T& a, const T& b){
		return a + b;
	}
	T queryfunc(const T& a, const T& b){
		return a + b;
	}
	T reversefunc(const T& a, const T& b){
		//For the access, reverse of queryfunc
		return a - b;
	}

public:
	//Useful functions
	//Constructor, n - size of the array
	FenTree(size_t n){
		N = n + 1;
		fwt = new T[N]();
	}
	//Destructor
	~FenTree(){
		delete[] fwt;
	}

	//All access, update, return functions begins at original index of 0, but fenwick tree index start at 1
	//Example calculates prefix sum from 0 to i

	//Read the actual number at position i
	//Runtime: O(c*logN) where c < 1
	//This is better than Query twice
	T operator[](size_t i){
		T ans = fwt[i+1];
		for(size_t next = i & (i + 1); i > next; i &= (i - 1))
			ans = reversefunc(ans, fwt[i]);
		return ans;
	}
	//Runtime: O(logN)
	void update(size_t i, T value){
		//value -= (*this)[i]; //If update is based on assignment
		for(i++; i < N; i += (i & -i))
			fwt[i] = applyfunc(fwt[i], value);
	}
	//Runtime: O(logN)
	T query(size_t i){
		T ans = 0;
		for(i++; i; i &= (i - 1))
			ans = queryfunc(ans, fwt[i]);
		return ans;
	}
	//Multiply number at position i by value
	void multiply(size_t i, const T& value){
		update(i, (value-1)*(*this)[i]);
	}
	//Divide number at position i by value
	//Ceiling
	void cdivide(size_t i, const T& value){
		update(i, -(value-1)*(*this)[i]/value);
	}
	//Floor
	void fdivide(size_t i, const T& value){
		update(i, -(1 + (((value-1)*(*this)[i])-1)/value));
	}
	//Multiply/Scale whole tree by factor value
	//Because tree itself is a linear composition of addition, simply multiply/divide all
	//Runtime: O(N)
	void operator*=(const T& value){
		for(size_t i = 1; i < N; i++)
			fwt[i] *= value;
	}
	//This division does not guarantee correct ceiling or flooring of individual values
	//Correct individually requires O(NlogN)
	void operator/=(const T& value){
		for(size_t i = 1; i < N; i++)
			fwt[i] /= value;
	}
	//Find greatest index of given prefix sum value
	//Runtime: O(logN)
	//Does not work if negative numbers are present, this uses the idea of binary search
	//Returns -1 if prefix sum does not exist
	size_t find(T value){
		size_t maxbit, i;
		for(maxbit = N-1; maxbit & (maxbit - 1); maxbit &= (maxbit - 1));
		for(i = 0; maxbit; maxbit >>= 1)
			if((i|maxbit) < N && value >= fwt[i|maxbit])
				value -= fwt[i |= maxbit];
		if(value) //Given prefix sum does not exist; may also just return i-1 if need to arrive at greatest prefix sum index closest to value
			return -1;
		return i-1;
	}
};

int main(){
	//Enter code here
	return 0;
}