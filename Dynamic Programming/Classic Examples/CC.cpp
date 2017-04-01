//Coin Change template
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template<int N, int V> struct CC{
	//Arrays
	int coins[N], size, represent[V], variants[V];
	#define INF (1<<28)
	//Constructor
	CC(){
		fill_n(represent, V, INF);
		size = 0;
	}
	//Add method
	void add(int value){
		coins[size++] = value;
	}

	//CC Minimum representation
	//Time complexity: O(N(V)) where V is value state required to search
	//Top-down (recursive) solution (faster)
	//Notice that INF may be replaced with boolean check for more accurate solution
	//Value at 1<<28 or above is definitely not feasible thus accuracy above that isn't even considered
	int minrep(int value){
		if(value == 0) return 0;
		if(value < 0) return INF;
		for(int i = 0; i < size; i++){
			represent[value] = min(represent[value], 1 + minrep(value - coins[i]));
		}
		return represent[value];
	}

	//CC Minimum representation
	//Time complexity: O(N(V)) where V is value state required to search
	//Bottom-up solution (true DP, slower)
	int minrepdp(int value){
		represent[0] = 0;
		for(int i = 1; i <= value; i++)
			for(int j = 0; j < size; j++)
				if(i - coins[j] >= 0)
					represent[i] = min(represent[i], 1 + represent[i-coins[j]]);
		return represent[value];
	}

	//CC Variants representation
	//Number of ways to represent a value
	//Time complexity: O(N(V)) where V is value state required to search
	//Top-down (recursive) solution (faster)
	int varrep(int coin, int value){
		if(!value) return variants[value] = 1;
		if(value < 0 || coin == size) return 0;
		return variants[value] = varrep(coin + 1, value) + varrep(coin, value - coins[coin]);
	}

	//CC Variants representation
	//Time complexity: O(N(V)) where V is value state required to search
	//Bottom-up solution (true DP, slower)
	int varrepdp(int value){
		memset(variants, 0, sizeof(variants));
		variants[0] = 1;
		for(int i = 0; i < size; i++)
			for(int j = 1; j <= value; j++)
				if(j - coins[i] >= 0)
					variants[j] += variants[j - coins[i]];
		//variants[0] = 0; //If that is the case
		return variants[value];
	}
};

int main(){
	//Enter code here
	return 0;
}