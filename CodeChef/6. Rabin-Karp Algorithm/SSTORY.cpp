#include <bits/stdc++.h>
using namespace std;

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

#define MOD (1999999999981LL)
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
	//This problem does not relate to Rabin-Karp string search at all, but it does use its idea of rolling string hash
	//There's a way to do this problem using Suffix Automaton, but I'll learn that on Codechef 19, so this problem will be solved using Binary Search + String Hash O(NlogN)
	char S1[250005], S2[250005];
	readStr(S1);
	readStr(S2);
	int len1 = strlen(S1), len2 = strlen(S2);
	//Binary search for length
	int lo = 0, hi = len2+1, index = -1, mid, loc, best = 0;
	long long hash, mul;
	bool found;
	while(lo < hi){
		mid = (lo + hi)/2;
		if(!mid) break;
		//Build hashes
		unordered_set<long long> hashes; //C++11 required for O(1) hashing
		hash = 0;
		for(int i = 0; i < mid; i++)
			hash = (hash*27 + S1[i]-'a'+1)%MOD;
		hashes.insert(hash);
		mul = fexp(27, mid-1);
		for(int i = mid; i < len1; i++){
			hash = ((hash-(mul*(S1[i-mid]-'a'+1))%MOD+MOD)*27 + S1[i]-'a'+1)%MOD;
			hashes.insert(hash); //Low collision chance I hope
		}
		//Check hashes
		hash = 0;
		for(loc = 0; loc < mid; loc++)
			hash = (hash*27 + S2[loc]-'a'+1)%MOD;
		found = hashes.count(hash);
		for(loc = mid; loc < len2 && !found; loc++){
			hash = ((hash-(mul*(S2[loc-mid]-'a'+1))%MOD+MOD)*27 + S2[loc]-'a'+1)%MOD;
			found = hashes.count(hash);
		}
		loc--;
		if(found){
			index = loc-mid+1;
			best = mid;
			lo = mid+1;
		}else
			hi = mid;
	}
	if(best){
		for(int i = 0; i < best; i++)
			printf("%c", S2[i+index]);
		printf("\n%d\n", best);
	}else
		printf("%d\n", best);
}