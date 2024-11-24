#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <set>

using namespace std;
struct compare{
	bool operator()(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b){
		// {int, {int, int}} == {vertex_num, {adj_vertex_num, cost}}, 마지막 cost 기준 정렬
		return a.first > b.first;
	}
};
struct compare2{
	bool operator()(const pair<pair<int, int>, int> &v1, const pair<pair<int, int>, int> &v2) const {
		return v1.second < v2.second;
	}
};
long long function(vector<vector<pair<int, int>>> &graph, int &n, multiset<pair<pair<int, int>, int>, compare2> &unused, vector<vector<pair<int, int>>> &mst){
	bool *visit = new bool[n];
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,compare> index; // min priority queue
	for(int i = 0; i < n; i++){
		visit[i] = false;
	}

	visit[0] = true;
	for(auto it = graph[0].begin(); it < graph[0].end(); it++){
		if(!visit[it->first]){
			index.push(make_pair(it->second, make_pair(0, it->first)));
		}
	}
	long long sum_cost = 0;
	int esc_key = 0;
	int src, dest;
	long long cost;
	while(!index.empty()){
		while(!index.empty() && visit[index.top().second.second]){
			unused.insert(make_pair(make_pair(index.top().second.first, index.top().second.second), index.top().first));
			index.pop();
		}
		if(index.empty()){
			break;
		}
		src = index.top().second.first;
		dest = index.top().second.second;
		cost = index.top().first;
		index.pop();

		mst[src].push_back(make_pair(dest, cost));
		mst[dest].push_back(make_pair(src, cost));
		
		sum_cost += cost;
		visit[dest] = true;
		for(auto it = graph[dest].begin(); it < graph[dest].end(); it++){
			if(!visit[it->first]){
				index.push(make_pair(it->second, make_pair(dest, it->first)));
			}
		}
	}
	return sum_cost;
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
    scanf("%d %d", &n, &m); // store input at inputstring	
	
	int v1, v2, cost;
	// int **graph = new int*[n];
	vector<vector<pair<int, int>>> graph(n);
	// {vertex, weight}

	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &v1, &v2, &cost);
		graph[v1-1].push_back(make_pair(v2-1, cost));
		graph[v2-1].push_back(make_pair(v1-1, cost));
		// 숫자는 1부터 시작
	}

	multiset<pair<pair<int, int>, int>, compare2> unused;
	vector<vector<pair<int, int>>> mst(n);
	long long answer = function(graph, n, unused, mst);

	if(answer == 0){
		printf("-1");
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
	bool zerokey;
	for(auto &it : unused){
		v1 = it.first.first;
		v2 = it.first.second;
		cost = it.second;
		
		tmpMax1 = 0, tmpMax2 = 0;
		diff = PH[v1].second.second - PH[v2].second.second;
		zerokey = false;
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
		while(v1 != v2){
			if(PH[v1].first < cost){
				tmpMax1 = tmpMax1 > PH[v1].first ? tmpMax1 : PH[v1].first;
				if(tmpMax1 == 0) zerokey = true;
			}
			if(PH[v2].first < cost){
				tmpMax2 = tmpMax2 > PH[v2].first ? tmpMax2 : PH[v2].first;
				if(tmpMax2 == 0) zerokey = true;
			}
			v1 = PH[v1].second.first;
			v2 = PH[v2].second.first;
		}
		tmpMax1 = tmpMax1 > tmpMax2 ? tmpMax1 : tmpMax2; // 둘 중 큰 것을 tmpMax1에 저장
		if(tmpMax1 < cost && (tmpMax1 != 0 || (tmpMax1 == 0 && zerokey))){
			tmpMax2 = answer + cost - tmpMax1;
			second_min = second_min > tmpMax2 ? tmpMax2 : second_min;
		}
	}
	if(second_min == answer || second_min == 2147483647) {
		printf("%d", -1);
	}
	else{
		printf("%llu", second_min);
	}
	return 0;
}
