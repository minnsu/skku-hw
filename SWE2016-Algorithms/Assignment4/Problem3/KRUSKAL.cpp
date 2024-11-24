#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>

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
	bool operator()(const pair<pair<int, int>, int> &v1, const pair<pair<int, int>, int> &v2) const {
		return v1.second < v2.second;
	}
};

unsigned long long MST_kruskal(multiset<pair<pair<int, int>, int>, compare> &edges, int &n, set<pair<pair<int, int>, int>, compare> &unused, vector<vector<pair<int, int>>> &mst){
	int *parent = new int[n];
	int *height = new int[n];
	for(int i = 0; i < n; i++){
		parent[i] = i;
		height[i] = 0;
	}
	unsigned long long sum = 0;
    int src, dest;
    unsigned long long cost;
	for(auto &it : edges){// int i = 0; i < size; i++){
		src = it.first.first;
		dest = it.first.second;
		cost = it.second;
		
		if(find(parent, src) != find(parent, dest)){
			sum += cost;
			UNION(parent, height, src, dest);
			mst[src].push_back(make_pair(dest, cost));
			mst[dest].push_back(make_pair(src, cost));
		}
		else{
			unused.insert(it);
		}
	}

	int find0 = find(parent, 0);
	int err_key = 1;
	for(int i = 1; i < n; i++){
		if(find0 == find(parent, i)){
			err_key++;
		}
	}
	if(err_key != n){
		return 0;
	}
	return sum;
}

void dfs(vector<vector<pair<int, int>>> &mst, vector<pair<int ,pair<int, int>>> &PH, int curr, bool *visit){
	for(auto &it : mst[curr]){
		if(visit[it.first]){
			continue;
		}
		else{
			visit[it.first] = true;
		}
		PH[it.first].first = it.second; // cost
		PH[it.first].second.first = curr; // parent
		PH[it.first].second.second = PH[curr].second.second + 1; // height
		dfs(mst, PH, it.first, visit);
	}
}

int main(int argc, char** argv){
	int n, m;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	unsigned long long tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n, &m); // store input at inputstring	
	int v1, v2, cost;
	multiset<pair<pair<int, int>, int>, compare> edges; // { {src, dest}, cost }
	// {vertex, weight}
	for(int i = 0; i < m; i++){
		fscanf(fr, "%d %d %d", &v1, &v2, &cost);
		edges.insert(make_pair(make_pair(v1-1, v2-1), cost));
		edges.insert(make_pair(make_pair(v2-1, v1-1), cost));
		// 숫자는 1부터 시작
	}
    fclose(fr);
	
	FILE *fw = fopen(argv[2], "w");
	
	set<pair<pair<int, int>, int>, compare> unused;
	vector<vector<pair<int, int>>> mst(n);
	unsigned long long answer = MST_kruskal(edges, n, unused, mst);
	for(auto &it : unused){
		printf("(%d, %d) : %d\n", it.first.first + 1, it.first.second + 1, it.second);
	}
	printf("--- unused \n");
	for(int i = 0; i < mst.size(); i++){
		for(int j = 0; j < mst[i].size(); j++){
			printf("(%d, %d) : %d\n", i+1, mst[i][j].first + 1, mst[i][j].second);
		}
	}
	printf("--- mst \n");
	if(answer == 0){
		fprintf(fw, "-1");
		return 0;
	}
	unsigned long long second_min = 2147483647;
	bool *visit = new bool[n];	
	memset(visit, false, sizeof(visit));
	visit[0] = true;
	vector<pair<int, pair<int, int>>> PH(n); // {cost, {parentNum, height}}
	dfs(mst, PH, 0, visit);
	
	int tmpMax1 = 0, tmpMax2 = 0;
	int diff;
	for(auto &it : unused){
		v1 = it.first.first;
		v2 = it.first.second;
		cost = it.second;
		
		tmpMax1 = 0, tmpMax2 = 0;
		diff = PH[v1].second.second - PH[v2].second.second;
		if(diff > 0){
			while(diff != 0){
				if(PH[v1].first < cost){
					tmpMax1 = tmpMax1 > PH[v1].first ? tmpMax1 : PH[v1].first;
				}
				v1 = PH[v1].second.first;
				diff--;
			}
		}
		else if(diff < 0){
			while(diff != 0){
				if(PH[v2].first < cost){
					tmpMax2 = tmpMax2 > PH[v2].first ? tmpMax2 : PH[v2].first;
				}
				v2 = PH[v2].second.first;
				diff++;
			}
		}
		while(true){
			if(v1 == v2){
				// 탈출
				tmpMax1 = tmpMax1 > tmpMax2 ? tmpMax1 : tmpMax2; // 둘 중 큰 것을 tmpMax1에 저장
				break;
			}
			if(PH[v1].first < cost){
				tmpMax1 = tmpMax1 > PH[v1].first ? tmpMax1 : PH[v1].first;
			}
			if(PH[v2].first < cost){
				tmpMax2 = tmpMax2 > PH[v2].first ? tmpMax2 : PH[v2].first;
			}
			v1 = PH[v1].second.first;
			v2 = PH[v2].second.first;
		}
		if(tmpMax1 < cost && tmpMax1 != 0){
			tmpMax2 = answer + cost - tmpMax1;
			second_min = second_min > tmpMax2 ? tmpMax2 : second_min;
		}
	}

	for(int i = 0; i < n; i++){
		printf("%d's cost : %d parent : %d height(depth) : %d\n", i + 1, PH[i].first, PH[i].second.first + 1, PH[i].second.second);
	}	

	if(second_min == answer || second_min == 2147483647) {
		fprintf(fw, "%d", -1);
	}
	else{
		fprintf(fw, "%llu", second_min);
	}
	fclose(fw);
	return 0;
}
