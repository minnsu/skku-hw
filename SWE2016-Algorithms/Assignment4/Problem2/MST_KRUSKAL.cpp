#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int find(int *parent, int V){
	while(parent[V] != V){
		V = parent[V];
	}
	return V;
}
void UNION(int *parent, int *height, int V1, int V2){
	V1 = find(parent, V1);
	V2 = find(parent, V2);
	if(V1 == V2){
		return;
	}
	if(height[V1] == height[V2]){
		parent[V2] = V1;
		height[V1]++;
	}
	else if(height[V2] < height[V1]){
		parent[V2] = V1;
	}
	else{
		parent[V1] = V2;
	}
}
struct compare{
	bool operator()(const pair<int, pair<int, int>> &v1, const pair<int, pair<int, int>> &v2) const {
		return v1.first < v2.first;
	}
};

long long MST_kruskal(vector<vector<pair<int, int>>> &graph, int &n){
	set<pair<int, pair<int, int>>, compare> edges;
	int *parent = new int[n];
	int *height = new int[n];
	for(int i = 0; i < n; i++){
		parent[i] = i;
		height[i] = 0;
		for(int j = 0; j < graph[i].size(); j++){
			if(i < graph[i][j].first){
				edges.insert(make_pair(graph[i][j].second, make_pair(i, graph[i][j].first)) );
			}
		}
	}
	
	long long sum = 0;
    int src, dest;
    long long cost;
	for(auto &it : edges){// int i = 0; i < size; i++){
		src = it.second.first;
		dest = it.second.second;
		cost = it.first;
		
		if(find(parent, src) != find(parent, dest)){
			sum += cost;
			UNION(parent, height, src, dest);
		}
	}
	return sum;
}

int main(int argc, char** argv){
	int n, m;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n, &m); // store input at inputstring	
	int v1, v2, cost;
	vector<vector<pair<int, int>>> graph(n);
	// {vertex, weight}
	for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &v1, &v2, &cost);
		graph[v1-1].push_back(make_pair(v2-1, cost));
		graph[v2-1].push_back(make_pair(v1-1, cost));
		// 숫자는 1부터 시작
	}
    fclose(fr);
	
	long long answer = MST_kruskal(graph, n);
    FILE *fw = fopen(argv[2], "w");
	fprintf(fw, "%lld", answer);
	fclose(fw);
	return 0;
}
