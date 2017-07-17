//Shortest Path Faster algorithm template
#include <bits/stdc++.h>
using namespace std;

template<typename T> class Dijkstra{
private:
	T* result;
	//size_t* prev; //Useful for path reconstruction
	size_t V;
	vector<pair<size_t, T> >* G;

public:
	//Constructor, n = number of vertices
	Dijkstra(size_t n){
		V = n;
		result = new T[V]();
		//prev = new size_t[V]();
		G = new vector<pair<size_t, T> >[V];
	}
	//Destructor
	~Dijkstra(){
		delete[] result;
		//delete[] prev;
		delete[] G;
	}
	//For adding edges
	void add(size_t from, size_t to, const T& dist){
		G[from].push_back(pair<size_t, T>(to, dist));
	}
	//Comparison objects
	class cmp{
		public:
		bool operator()(const pair<size_t, T>& a, const pair<size_t, T>& b){
			//Change this if not shortest-path
			return a.second > b.second;
		}
	};
	bool check(const T& a, const T& b){
		//Change this opposite to the above if not shortest-path
		return a < b;
	}

	//Dijkstra's Shortest Path algorithm execution
	//V, E <= 300,000, best on weighted graph, overkill on small graph
	//(no negative cycle (cannot detect), undirected/directed graph)
	//Time complexity: O((|E| + |V|)log|V|)
	void exec(size_t s){
		size_t u, v;
		T w, cur;
		bool checked[V];
		memset(checked, 0, sizeof(checked));
		//Unless you want previous, this is not needed
		//fill_n(prev, V, -1);
		priority_queue<pair<size_t, T>, vector<pair<size_t, T> >, cmp> q;
		q.push(pair<size_t, T>(s, 0));
		result[s] = 0;
		checked[s] = true;
		while(!q.empty()){
			pair<size_t, T> p = q.top(); q.pop();
			u = p.first;
			cur = p.second;
			if(check(result[u], cur)) continue;
			size_t len = G[u].size();
			for(size_t i = 0; i < len; i++){
				v = G[u][i].first;
				w = G[u][i].second;
				if(!checked[v] || check(cur + w, result[v])){
					//prev[v] = u;
					checked[v] = true;
					q.push(pair<size_t, T>(v, (result[v] = cur + w)));
				}
			}
		}
	}
	
	//Access shortest path, -1 if not accessible
	T operator[](size_t i){
		return result[i]; 
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

long long h(char *str){
	long long hash = 0;
	int size = strlen(str);
	for(int i = 0; i < size; i++)
		hash = hash*27 + str[i] - 'a' + 1;
	return hash;
}

void FastIO::solve(){
	int T, V, E, v, Q;
	long long hash, w;
	char s[15];
	readInt(T);
	while(T--){
		readInt(V);
		Dijkstra<long long> dijkstra(V+1);
		unordered_map<long long, int> cities;
		for(int i = 1; i <= V; i++){
			readStr(s);
			hash = h(s);
			cities[hash] = i;
			readInt(E);
			for(int j = 0; j < E; j++){
				readInt(v);
				readLL(w);
				dijkstra.add(i, v, w);
			}
		}
		readInt(Q);
		while(Q--){
			readStr(s);
			hash = h(s);
			dijkstra.exec(cities[hash]);
			readStr(s);
			hash = h(s);
			printf("%lld\n", dijkstra[cities[hash]]);
		}
	}
}