//Suffix Array Skew Algorithm Template
//[1] http://www.mi.fu-berlin.de/wiki/pub/ABI/SS13Lecture3Materials/script.pdf
//[2] http://www.cs.cmu.edu/~guyb/realworld/papersS04/KaSa03.pdf
//[3] https://pdfs.semanticscholar.org/8dfc/1a49894632a27a88490db18441180a215fe2.pdf
#include <bits/stdc++.h>
using namespace std;

template<typename T> class SuffixArray{
private:
	int* arr; //ranking of nodes
	int* SAf; //Suffix Array
	int* LCPf; // LCP Array
	size_t N; //Size of string

	//Change this for ranking of nodes, make sure it returns an int
	//Currently for ASCII if char
	//The ranking is the set of alphabets which directly correlates with the runtime of radix sort, a major function for step 1 and 2 of the algorithm
	int ranking(const T& c){
		return c+1;
	}
	//Comparison: Lexicographic, may be changed to descending order by changing radix pass in reverse and comparison objects below
	bool cmp(int a1, int a2, int b1, int b2){
		return a1 == b1 ? a2 <= b2 : a1 < b1;
	}
	bool cmp(int a1, int a2, int a3, int b1, int b2, int b3){
		return a1 == b1 ? cmp(a2, a3, b2, b3) : a1 < b1;
	}
	void radixPass(int* unsorted, int* sorted, int* rank, size_t size, size_t keycount){
		size_t freq[keycount + 1];
		memset(freq, 0, sizeof(freq)); //Reset frequency
		for(size_t i = 0; i < size; i++) //Increment frequency of alphabet
			freq[rank[unsorted[i]]]++;
		for(size_t i = 0, sum = 0; i <= keycount; i++){ //Exclusive prefix sums for labeling nodes
			size_t t = freq[i];
			freq[i] = sum;
			sum += t;
		}
		for(size_t i = 0; i < size; i++) //Stable sort
			sorted[freq[rank[unsorted[i]]]++] = unsorted[i];
	}

public:
	//Useful functions
	//Constructors: a - array, N - size of array
	SuffixArray(T* a, size_t n){
		//N > 1, strings of 1 will not work
		N = n;
		arr = new int[N+3];
		for(int i = 0; i < N; i++)
			arr[i] = ranking(a[i]);
		arr[N] = arr[N+1] = arr[N+2] = 0;
		SAf = new int[N];
		LCPf = new int[N];
	}
	//Destructor
	~SuffixArray(){
		delete[] SAf;
		delete[] LCPf;
		delete[] arr;
	}
	//Suffix Array accessor
	int& operator[](const size_t& i){
		return SAf[i];
	}

	//Skew Algorithm
	//Runtime: O(N), O(NlogN) if building LCP
	void skewAlgorithm(int* s, int* SA, int* LCP, bool buildLCP, size_t size, size_t keycount, int recur){
		printf("{Recursion: %d}\n\n", recur);
		size_t n0 = (size+2)/3; //Number of i%3 == 0 strings
		size_t n1 = (size+1)/3; //Number of i%3 == 1 strings
		size_t n2 = size/3; //Number of i%3 == 2 strings
		size_t n02 = n0+n2; //Total length of SA12
		//Name12 and SuffixArray12, may be used interchangeably for sorting to induce SA^-1,12 and SA12
		int s12[n02 + 3];
		s12[n02] = s12[n02 + 1] = s12[n02 + 2] = 0;
		int SA12[n02 + 3];
		SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = 0;
		//Name0 and SuffixArray0, which will be used to derive SA final
		int s0[n0];
		int SA0[n0];
		//LCP12, which will be used to calculate LCP
		//Using this segment tree will force the algorithm to run in O(NlogN) and may take up a lot of space
		//The described structure in [3] to preprocess RMQ in O(N) and query in O(1) is too difficult to understand
		struct LCPTree{
			size_t height;
			int* sgt;
			int maxSize;
			LCPTree(size_t n, size_t s){
				height = (size_t)ceil(log2(n));
				sgt = new int[1<<(height+1)]();
				maxSize = (int)s;
			}
			~LCPTree(){
				delete[] sgt;
			}
			int& operator[](size_t i){
				return sgt[i + (1<<height)];
			}
			void build(){
				for(size_t i = ((1<<height)-1); i > 0; i--)
					sgt[i] = sgt[i<<1] < sgt[i<<1|1] ? sgt[i<<1] : sgt[i<<1|1];
			}
			int query(size_t l, size_t r){
				if(!((l+1)^r)) return (*this)[l];
				int ans = maxSize;
				for(l += (1<<height), r += (1<<height); l < r; l >>= 1, r >>= 1){
					if(l&1){
						ans = ans < sgt[l] ? ans : sgt[l];
						l++;
					}
					if(r&1){
						--r;
						ans = sgt[r] < ans ? sgt[r] : ans;
					}
				}
				return ans;
			}
		}LCP12(n02, size);
		//Step 1a: Gather indices of i%3 != 0 string starting locations and radix sort for 3 passes due to %3
		//At the end of 3 passes, indices of string should be ranked lexicographically of string alphabet
		//Example: b o b o c e l will take o b c e $ and make
		//$ b c e o, which corresponds to 7 2 4 5 1 0 0 0
		printf("n0(n mod 3 == 1): %d, n1 (n mod 3 == 0): %d, n2 (n mod 3 == 2): %d, n02: %d\n\n", n0, n1, n2, n02);
		printf("Step 1a: Construct s12\n\n");
		for(size_t i = 0, j = 0; i < size + (n0 - n1); i++)
			if(i%3) s12[j++] = i;
		printf("s12 initial: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", s12[i]);
		printf("\n");
		radixPass(s12, SA12, s+2, n02, keycount);
		printf("After 1st pass:\n");
		printf("s12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", s12[i]);
		printf("\n");
		printf("SA12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", SA12[i]);
		printf("\n");
		radixPass(SA12, s12, s+1, n02, keycount);
		printf("After 2nd pass:\n");
		printf("s12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", s12[i]);
		printf("\n");
		printf("SA12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", SA12[i]);
		printf("\n");
		radixPass(s12, SA12, s, n02, keycount);
		printf("After 3rd pass:\n");
		printf("s12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", s12[i]);
		printf("\n");
		printf("SA12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", SA12[i]);
		printf("\n");
		printf("\n");
		//Step 1b: Construct T', rank i%3 suffixes with i%3 == 1 suffixes before i%3 == 2 suffixes
		//This allows the recursive sorting process sort a suffix array
		//For example:
		//7 2 4 5 1 0 0 0
		//$ b c e o
		//1 2 3 4 5
		//-> o c $ b e
		//-> 5 3 1 2 4
		printf("Step 1b: Constructing T'\n\n");
		int name = 0, c0 = -1, c1 = -1, c2 = -1;
		for(int i = 0; i < n02; i++){
			if(s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2){
				name++;
				c0 = s[SA12[i]];
				c1 = s[SA12[i]+1];
				c2 = s[SA12[i]+2];
			}
			if(SA12[i]%3 == 1)
				s12[SA12[i]/3] = name;
			else
				s12[SA12[i]/3 + n0] = name;
		}
		printf("s12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", s12[i]);
		printf("\n");
		printf("\n");
		//Step 1c: Construct the suffix array A' of T'
		//Recursively call the skew algorithm to construct the suffix array A' of T'
		printf("Step 1c: Constructing A'\n\n");
		if(name < n02){
			printf("Recursing due to repeated names:\n\n");
			//recursively construct SA12, suffix array of mod%3 == 1 and mod%3 == 2 suffixes
			int tempLCP12[n02];
			skewAlgorithm(s12, SA12, tempLCP12, true, n02, name, recur+1);
			//Compute SA^-1,12
			for(int i = 0; i < n02; i++){
				s12[SA12[i]] = i + 1;
				if(buildLCP) LCP12[i] = tempLCP12[i]; //Update LCP12 Tree
			}
			printf("After recursion:\n");
			printf("s12: ");
			for(int i = 0; i < n02; i++)
				printf("%d ", s12[i]);
			printf("\n");
			printf("SA12: ");
			for(int i = 0; i < n02; i++)
				printf("%d ", SA12[i]);
			printf("\n");
		}else{
			for(int i = 0; i < n02; i++){
				SA12[s12[i] - 1] = i; //Provided s12 naming is already ranked and distinct and that it's already the SA12 inverse, build SA12 from it
				if(buildLCP) LCP12[s12[i] - 1] = 0; //Update RMQ, all distinct thus all LCP12 should be 0
			}
			printf("No need recursion:\n");
			printf("s12: ");
			for(int i = 0; i < n02; i++)
				printf("%d ", s12[i]);
			printf("\n");
			printf("SA12: ");
			for(int i = 0; i < n02; i++)
				printf("%d ", SA12[i]);
			printf("\n");
		}
		if(buildLCP) LCP12.build();
		printf("\n");
		//Step 2: Derive A0 from A12
		//We had skipped step 1d, it will come later; this is simply deriving A0 from A12, which is the SA^-1,0, or SA0 inverse
		printf("Step 2: Constructing A0\n\n");
		for(size_t i = 0, j = 0; i < n02; i++)
			if(SA12[i] < n0)
				s0[j++] = 3*SA12[i]; //Interesting by the properties of i%3 == 1 that has already been sorted,
				//which simplifies the sorting process of SA0 to just the first character, and provide SA0
		printf("s0: ");
		for(int j = 0; j < n0; j++)
			printf("%d ", s0[j]);
		printf("\n");
		radixPass(s0, SA0, s, n0, keycount);
		printf("After Radix Pass:\n");
		printf("s0: ");
		for(int j = 0; j < n0; j++)
			printf("%d ", s0[j]);
		printf("\n");
		printf("SA0: ");
		for(int j = 0; j < n0; j++)
			printf("%d ", SA0[j]);
		printf("\n");
		printf("\n");
		//Step 3: Merge A12 and A0 into suffix A, we will first take step 1d to derive A12
		//t here skips the $ if there is one
		//p - SA0 traversal
		//t - SA12 traversal
		printf("Step 3 & 1d: Merge A12 and A0\n\n");
		printf("s0: ");
		for(int j = 0; j < n0; j++)
			printf("%d ", s0[j]);
		printf("\n");
		printf("SA0: ");
		for(int j = 0; j < n0; j++)
			printf("%d ", SA0[j]);
		printf("\n");
		printf("s12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", s12[i]);
		printf("\n");
		printf("SA12: ");
		for(int i = 0; i < n02; i++)
			printf("%d ", SA12[i]);
		printf("\n");
		for(size_t p = 0, t = n0 - n1, k = 0; k < size; k++){
			//Pick i of SA12 and j of SA0 and compare them, SA are the ranked positions of s
			int i = SA12[t] < n0 ? SA12[t]*3 + 1 : (SA12[t] - n0)*3 + 2;
			int j = SA0[p];
			//Merge, take earlier one and increment
			if(SA12[t] < n0 ?
				cmp(s[i], s12[SA12[t] + n0], s[j], s12[j/3]) : //i%3 == 1 comparison with i%3 == 0, based on first character and then names
				cmp(s[i], s[i+1], s12[SA12[t] - n0 + 1], s[j], s[j+1], s12[j/3 + n0])){ //i%3 == 2 comparison with i%3 == 0, based on first and second character and then names
				SA[k] = i;
				t++;
				//Left over n0
				if(t == n02)
					for(k++; p < n0; p++, k++)
						SA[k] = SA0[p];
			}else{
				SA[k] = j;
				p++;
				if(p == n0){
					//Left over n02
					for(k++; t < n02; t++, k++)
						SA[k] = SA12[t] < n0 ? SA12[t]*3 + 1 : (SA12[t] - n0)*3 + 2;
				}
			}
		}
		printf("After merge:\n");
		printf("SA: ");
		for(int i = 0; i < size; i++)
			printf("%d ", SA[i]);
		printf("\n");
		printf("\n");
		if(buildLCP){
			//Step 4: Building LCP Array from LCP12
			printf("Step 4: Building LCP from LCP12\n\n");
			LCP[size-1] = 0; //This LCP Array defines as LCP[i] = lcp(i, i+1) rather than LCP[i] = lcp(i-1, i)
			for(size_t i = 0; i < size-1; i++){
				//Two suffix positions
				int j = SA[i];
				int k = SA[i+1];
				//LCP12 requires two SA position that %3 == 1 || %3 == 2, thus search for those
				int c, t;
				for(t = 0; ((j+t)%3 == 0 || (k+t)%3 == 0); t++);
				for(c = 0; ((j+c)%3 == 0 || (k+c)%3 == 0) && j+c < size && k+c < size && s[j+c] == s[k+c]; c++);
				if(j+t >= size || k+t >= size) //Case extending beyond size of array
					LCP[i] = c;
				else
					if(c < t) //If character comparison is the max length of LCP, then LCP[i] = c
						LCP[i] = c;
					else{
						//Calculate j' and k' from j and k
						int jp, kp;
						if((j+t)%3 == 1) jp = (j + t - 1)/3;
						else jp = (j + t - 2)/3 + n0;
						if((k+t)%3 == 1) kp = (k + t - 1)/3;
						else kp = (k + t - 2)/3 + n0;
						//j+t and k+t may not be adjacent in SA, thus j' and k' may not be adjacent in SA12, and so may not in LCP12, however
						//lcp(j', k') = min(LCP[k], k between s12[j']-1 and s12[k']-1) based on LCP property, thus range min query is needed
						//Notice if t == 0 then j' and k' must be right next to each other in the SA12 and LCP12 and also SA array
						size_t p = s12[jp]-1, q = s12[kp]-1;
						//Swap positions if needed
						if(p > q){
							size_t temp = p;
							p = q;
							q = temp;
						}
						//Search for min
						int l = LCP12.query(p, q); //[p, q)
						//LCP[i] = c + 3*l + l'
						LCP[i] = c + 3*l;
						//Calculate l', which = lcp(j + 3*l, k + 3*l), and can be no more than 3 as well
						int lp = 0;
						for(int p = j+t+3*l, q = k+t+3*l; lp < 3 && p+lp < size && q+lp < size && s[p+lp] == s[q+lp]; lp++);
						LCP[i] += lp;
					}
			}
			printf("LCP12: ");
			for(int i = 0; i < n02; i++)
				printf("%d ", LCP12.query(i, i+1));
			printf("\n");
			printf("LCP: ");
			for(int i = 0; i < size; i++)
				printf("%d ", LCP[i]);
			printf("\n");
			printf("\n");
		}
		printf("{End of recursion %d}\n\n", recur);
	}
	//Skew Algorithm Execution
	void exec(bool buildLCP = true, size_t keycount = 255){
		printf("SKEW: ");
		for(int i = 0; i < N; i++)
			printf("%c", arr[i]-1);
		printf("\n\n");
		skewAlgorithm(arr, SAf, LCPf, buildLCP, N, keycount+1, 0); //keycount = 255+1 currently due to 255 ASCII chars, note this can be changed for other keys
		//This LCP Array defines as LCP[i] = lcp(i, i+1), thus we need to arrange it to LCP[i] = lcp(i-1, i);
		for(size_t i = N-1; i > 0; i--)
			LCPf[i] = LCPf[i-1];
		LCPf[0] = 0;
	}
	//To do
	//2.13 Difference Covers
};

int main(){
	//Enter code here
	return 0;
}