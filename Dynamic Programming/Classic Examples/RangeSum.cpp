//Range Sum template
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template<int N> struct oneDRS{
	//Arrays
	long long arr[N];
	//Constructor
	oneDRS(){
		memset(arr, 0, sizeof(arr));
	}
	//Add methods
	void add(int index, long long value){
		arr[index] += value;
	}
	//Kadane's Algorithm
	//Time Comeplexity: O(N)
	//Can be designed to keep the range locations, but currently just return value
	//This is for 1D range sum
	long long kadane(int lim){
		long long maxsum = arr[0], tempsum = arr[0];
		for(int i = 1; i < lim; i++){
			tempsum = -arr[i] >= tempsum || tempsum < 0 ? arr[i] : arr[i] + tempsum;
			maxsum = max(tempsum, maxsum);
		}
		return maxsum;
	}
};

template<int row, int col> struct twoDRS{
	//Arrays
	long long arr[row][col];
	//Constructor
	twoDRS(){
		memset(arr, 0, sizeof(arr));
	}
	//Add methods
	void add(int r, int c, long long value){
		arr[r][c] += value;
	}
	//Designed for 2D range sum also using Kadane's Algorithm
	//Time Complexity: O(N^3)
	//Can also be designed to include matrix locations, currently just return value
	long long exec(int rlim, int clim){
		long long maxsum = arr[0][0];
		for(int i = 0; i < clim; i++){
			oneDRS<row> temp;
			for(int j = i; j < clim; j++){
				for(int k = 0; k < rlim; k++)
					temp.add(k, arr[k][j]);
				maxsum = max(maxsum, temp.kadane(rlim));
			}
		}
		return maxsum;
	}
};

template<int x, int y, int z> struct threeDRS{
	//And this never ends!
	//Arrays
	long long arr[x][y][z];
	//Constructor
	threeDRS(){
		memset(arr, 0, sizeof(arr));
	}
	//Add methods
	void add(int a, int b, int c, long long value){
		arr[a][b][c] += value;
	}
	//Designed for 3D range sum ALSO using Kadane's Algorithm
	//Time Complexity: O(N^5)
	//Can also be designed to include 3D locations, currently just return value
	long long exec(int xlim, int ylim, int zlim){
		long long maxsum = arr[0][0][0];
		for(int i = 0; i < zlim; i++){
			twoDRS<x, y> temp;
			for(int j = i; j < zlim; j++){
				for(int xi = 0; xi < xlim; xi++)
					for(int yi = 0; yi < ylim; yi++)
						temp.add(xi, yi, arr[xi][yi][j]);
				maxsum = max(maxsum, temp.exec(xlim, ylim));
			}
		}
		return maxsum;
	}
};

int main(){
	//Enter code here
	return 0;
}