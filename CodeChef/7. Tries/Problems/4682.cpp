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

class Trie{
private:
	struct node{
		node *l, *r;
		node(){
			l = r = NULL;
		}
		~node(){
			if(l != NULL) delete l;
			if(r != NULL) delete r;
		}
		//Customize insert, query for different needs
		void insert(bool i){
			//Make sure allocate before insert
			if(i && r == NULL) r = new node;
			else if(!i && l == NULL) l = new node;
		}
	};
	node *root;

public:
	Trie(){
		root = new node;
	}
	~Trie(){
		delete root;
	}
	//Customize insert and query for different needs
	void insert(int n){
		node *cur = root;
		for(int i = 31; i >= 0; i--){
			bool j = n & (1 << i);
			cur->insert(j);
			cur = j ? cur->r : cur->l;
		}
	}
	int query(int n){
		int ans = 0;
		node *cur = root;
		for(int i = 31; i >= 0; i--){
			bool p = n & (1 << i);
			if(p)
				if(cur->l != NULL){
					ans |= (1 << i);
					cur = cur->l;
				}else
					cur = cur->r;
			else
				if(cur->r != NULL){
					ans |= (1 << i);
					cur = cur->r;
				}else
					cur = cur->l;
		}
		return ans;
	}
};

void FastIO::solve(){
	int T, N;
	readInt(T);
	while(T--){
		readInt(N);
		Trie trie;
		int max = 0, newmax;
		int t, tempxor = 0;
		for(int i = 0; i < N; i++){
			trie.insert(tempxor);
			readInt(t);
			tempxor ^= t;
			newmax = trie.query(tempxor); //Query in such a manner that numbers^tempxor become maximum
			if(newmax > max)
				max = newmax;
		}
		printf("%d\n", max);
	}
}