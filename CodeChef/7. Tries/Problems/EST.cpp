#include <bits/stdc++.h>
using namespace std;

template<typename T> class SuffixArray{
private:
	int* arr;
	int* SAf;
	size_t N;

	int ranking(const T& c){
		return c-'a'+1;
	}
	bool cmp(int a1, int a2, int b1, int b2){
		return a1 == b1 ? a2 <= b2 : a1 < b1;
	}
	bool cmp(int a1, int a2, int a3, int b1, int b2, int b3){
		return a1 == b1 ? cmp(a2, a3, b2, b3) : a1 < b1;
	}
	void radixPass(int* unsorted, int* sorted, int* rank, size_t size, size_t keycount){
		size_t freq[keycount + 1];
		memset(freq, 0, sizeof(freq));
		for(size_t i = 0; i < size; i++)
			freq[rank[unsorted[i]]]++;
		for(size_t i = 0, sum = 0; i <= keycount; i++){
			size_t t = freq[i];
			freq[i] = sum;
			sum += t;
		}
		for(size_t i = 0; i < size; i++)
			sorted[freq[rank[unsorted[i]]]++] = unsorted[i];
	}

public:
	SuffixArray(T* a, size_t n){
		N = n;
		arr = new int[N+3];
		for(int i = 0; i < N; i++)
			arr[i] = ranking(a[i]);
		arr[N] = arr[N+1] = arr[N+2] = 0;
		SAf = new int[N+5];
	}
	~SuffixArray(){
		delete[] SAf;
		delete[] arr;
	}
	int& operator[](const size_t& i){
		return SAf[i];
	}
	int* getArr(){
		return arr;
	}
	int* getSA(){
		return SAf;
	}

	void skewAlgorithm(int* s, int* SA, size_t size, size_t keycount){
		size_t n0 = (size+2)/3, n1 = (size+1)/3, n2 = size/3;
		size_t n02 = n0+n2;
		int s12[n02 + 3];
		s12[n02] = s12[n02 + 1] = s12[n02 + 2] = 0;
		int SA12[n02 + 3];
		SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = 0;
		int s0[n0];
		int SA0[n0];

		for(size_t i = 0, j = 0; i < size + (n0 - n1); i++)
			if(i%3) s12[j++] = i;

		radixPass(s12, SA12, s+2, n02, keycount);
		radixPass(SA12, s12, s+1, n02, keycount);
		radixPass(s12, SA12, s, n02, keycount);

		int name = 0, c0 = -1, c1 = -1, c2 = -1;
		for(int i = 0; i < n02; i++){
			if(s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2){
				name++;
				c0 = s[SA12[i]], c1 = s[SA12[i]+1], c2 = s[SA12[i]+2];
			}
			if(SA12[i]%3 == 1) s12[SA12[i]/3] = name;
			else s12[SA12[i]/3 + n0] = name;
		}

		if(name < n02){
			skewAlgorithm(s12, SA12, n02, name);
			for(int i = 0; i < n02; i++)
				s12[SA12[i]] = i + 1;
		}else
			for(int i = 0; i < n02; i++)
				SA12[s12[i] - 1] = i;
		
		for(size_t i = 0, j = 0; i < n02; i++)
			if(SA12[i] < n0)
				s0[j++] = 3*SA12[i];
		radixPass(s0, SA0, s, n0, keycount);

		for(size_t p = 0, t = n0 - n1, k = 0; k < size; k++){
			int i = SA12[t] < n0 ? SA12[t]*3 + 1 : (SA12[t] - n0)*3 + 2;
			int j = SA0[p];
			if(SA12[t] < n0 ?
			cmp(s[i], s12[SA12[t] + n0], s[j], s12[j/3]) :
			cmp(s[i], s[i+1], s12[SA12[t] - n0 + 1], s[j], s[j+1], s12[j/3 + n0])){
				SA[k] = i;
				t++;
				if(t == n02)
					for(k++; p < n0; p++, k++)
						SA[k] = SA0[p];
			}else{
				SA[k] = j;
				p++;
				if(p == n0)
					for(k++; t < n02; t++, k++)
						SA[k] = SA12[t] < n0 ? SA12[t]*3 + 1 : (SA12[t] - n0)*3 + 2;
			}
		}
	}

	void exec(){
		skewAlgorithm(arr, SAf, N, 27);
	}
};

class LongestCommonPrefix{
private:
	int* arr;
	int* LCP;
	int* SA;
	size_t N;

public:
	LongestCommonPrefix(int* a, int* sa, size_t n){
		N = n;
		arr = a;
		SA = sa;
		LCP = new int[N+5];
	}
	~LongestCommonPrefix(){
		delete[] LCP;
	}
	int& operator[](const size_t& i){
		return LCP[i];
	}

	void exec(){
		int s[N];
		for(size_t i = 0; i < N; i++)
			s[SA[i]] = i;
		int lcp = 0;
		for(size_t i = 0; i < N; i++)
			if(s[i] > 0){
				size_t j = SA[s[i]-1];
				while(i + lcp < N && j + lcp < N && arr[i + lcp] == arr[j + lcp]) lcp++;
				LCP[s[i]] = lcp;
				if(lcp > 0) lcp--;
			}
		LCP[0] = 0;
	}
};

class FastIO{
//#define getchar() (getchar_unlocked()) //For hackerrank
private:
	//inline if read speed is needed, huge compilation time required though
	//safe no fread implementation
	int readInt(int &n){
		register int c;
		n = 0;
		bool neg = false;
		c = getchar();
		if(!(~c)) return -1;
		for(; ((c < 48 || c > 57)) && c != '-' && ~c; c = getchar());
		if(c == '-') neg = true, c = getchar();
		for(; c > 47 && c < 58 && ~c; c = getchar()){n = (n<<1)+(n<<3)+c-48;}
		if(neg) n = -n;
		return 1;
	}
	int readLL(long long &n){
		register int c;
		n = 0;
		bool neg = false;
		c = getchar();
		if(!(~c)) return -1;
		for(; ((c < 48 || c > 57)) && c != '-' && ~c; c = getchar());
		if(c == '-') neg = true, c = getchar();
		for(; c > 47 && c < 58 && ~c; c = getchar()){n = (n<<1)+(n<<3)+c-48;}
		if(neg) n = -n;
		return 1;
	}
	int readDouble(double &n){
		register int c;
		n = 0;
		bool neg = false;
		c = getchar();
		if(!(~c)) return -1;
		for(; ((c < 48 || c > 57)) && c != '-' && ~c; c = getchar());
		if(c == '-') neg = true, c = getchar();
		for(; c > 47 && c < 58 && ~c; c = getchar()){n = n*10+c-48;}
		if(c != '.'){
			if(neg) n = -n;
			return 1;
		}
		double div = 1;
		for(c = getchar(); c > 47 && c < 58 && ~c; c = getchar()){div *= 10, n = n*10+c-48;}
		n /= div;
		if(neg) n = -n;
		return 1;
	}
	int readStr(char *str){
		register char c = getchar();
		register int len = 0;
		if(!(~c)) return -1;
		while(c < 33 && ~c) c = getchar(); //32 if space should be included
		//32 if stop at space, 10 if stop at next line
		while(c != 10 && c != 32 && ~c){
			str[len] = c;
			c = getchar();
			len++;
		}
		str[len] = '\0';
		//Just in case if needs to return arriving at end of line
		//if(c == 10) return 10;
		return 1;
	}
	int readStr(char *str, int len){
		//Reading string of size len
		for(int i = 0; i < len; i++){
			str[i] = getchar();
			if(!(~str[i])){
				str[i] = '\0';
				return -1;
			}
			//Remove this if str can't go to next line
			/*if(str[i] == 10){
				str[i] = '\0';
				return 10;
			}*/
		}
		str[len] = '\0';
		return 1;
	}

public:
	//Constructor, true if using file input/output, defaulted false
	FastIO(bool useFile = false){
		if(useFile){
			freopen("input.txt", "r", stdin);
			freopen("output.txt", "w", stdout);
		}
	}

	void solve();
};

int main(){
	FastIO fio(true);
	fio.solve();
	return 0;
}

#define MOD (42424242)
long long fexp(long long b, long long e){
	long long ans = 1;
	b %= MOD;
	while(e){
		if(e&1) ans = (ans*b)%MOD;
		e >>= 1;
		b = (b*b)%MOD;
	}
	return ans;
}

void FastIO::solve(){
	int T, len, count;
	long long ans, distinct, permute[27];
	bool has[26];
	permute[0] = 1;
	for(int i = 26; i >= 1; i--)
		permute[26-i+1] = (permute[26-i]*i)%MOD;
	readInt(T);
	char str[100005];
	while(T--){
		readStr(str);
		len = strlen(str);
		count = 0;
		SuffixArray<char> sa(str, len);
		sa.exec();
		LongestCommonPrefix lcp(sa.getArr(), sa.getSA(), len);
		lcp.exec();
		int L = 0;
		for(int i = 1; i < len; i++)
			if(lcp[i] == len-sa[i-1] && lcp[i] > L)
				L = lcp[i];
		memset(has, 0, sizeof(has));
		for(int i = 0; i < len-L; i++)
			if(!has[str[i]-'a']){
				has[str[i]-'a'] = true;
				count++;
			}
		if(L){
			unordered_set<long long> hashes;
			long long hash = 0, expo = fexp(27, L-1);
			for(int i = 0; i < L; i++)
				hash = (hash*27 + str[i]-'a'+1)%MOD;
			hashes.insert(hash);
			for(int i = L; i < len-1; i++){
				hash = (((hash-((str[i-L]-'a'+1)*expo)%MOD+MOD)%MOD)*27 + str[i]-'a'+1)%MOD;
				hashes.insert(hash);
			}
			distinct = hashes.size();
		}else
			distinct = 1;
		printf("%lld\n", (distinct*permute[count])%MOD);
	}
}