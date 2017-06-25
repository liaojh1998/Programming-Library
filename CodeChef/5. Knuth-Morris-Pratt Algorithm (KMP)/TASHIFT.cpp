#include <bits/stdc++.h>
using namespace std;

template<typename T> class KMPModified{
private:
	T *str, *search;
	int N, M;
	int *pre;

public:
	KMPModified(T *st, int n, T *se, int m, int *p){
		str = st;
		N = n;
		search = se;
		M = m;
		pre = p;
	}
	//Longest proper suffix that is also a prefix of current suffix
	void computeLPS(int p[]){
		p[0] = 0;
		int len = 0;
		for(int i = 1; i < M; i++){
			//Search for all j < i-1 instances of arr[i-1] in previous proper suffixes such that arr[j+1] == arr[i]
			while(len && search[len] != search[i])
				len = p[len-1];
			if(search[len] == search[i]) len++;
			p[i] = len;
		}
	}
	void exec(){
		int lps[M], prefix = 0;
		computeLPS(lps); //The "internal rules" of the automaton
		for(int i = 0; i < N; i++){
			//Input a character into previous state for the automaton, automaton decides which state to go to
			while(prefix && search[prefix] != str[i])
				prefix = lps[prefix-1];
			if(search[prefix] == str[i]){
				prefix++;
				pre[i-prefix+1] = prefix;
			}
			if(prefix == M)
				prefix = lps[prefix-1];
		}
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
	FastIO fio;
	fio.solve();
	return 0;
}

void FastIO::solve(){
	int N;
	readInt(N);
	char a[N+5], b[N*2+5];
	readStr(a);
	readStr(b);
	for(int i = 0; i < N; i++)
		b[i+N] = b[i];
	b[N*2] = '\0';
	int prefix[N*2+5];
	memset(prefix, 0, sizeof(prefix));
	KMPModified<char> kmp(b, N*2, a, N, prefix);
	kmp.exec();
	int max = 0, index = 0;
	for(int i = 0; i < N*2; i++){
		//printf("%d%s", prefix[i], i == N*2-1 ? "\n" : " ");
		if(prefix[i] > max){
			index = i;
			max = prefix[i];
		}
	}
	printf("%d\n", index);
}