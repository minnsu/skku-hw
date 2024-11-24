#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>

using namespace std;

long getCost(int s, int d, int T){
	int sum = s - d;
	if(sum < 0){
		sum = -sum;
	}
	if(sum > T){
		return -1;
	}
	else{
		if(s >= d){
			return 1;
		}
		else{
			return sum * sum;
		}
	}
}

bool locValid(pair<int, int> loc, pair<int, int> dir, int M, int N){
	if(loc.second + dir.second < 0 || loc.first + dir.first < 0 || loc.second + dir.second >= M || loc.first + dir.first >= N){
		return false;
	}
	return true;
}

void dfs(int **Hmap, set<unsigned int> &endheight, bool **visit, pair<int, int> *dir, pair<int, int> loc, pair<int, int> befloc, int currentCost, int &T, int &S, int &M, int &N){
	visit[loc.second][loc.first] = true;
	long tmp;
	long backtmp;
	int nextx, nexty;
	endheight.insert(Hmap[loc.first][loc.second]);
	//printf("before : (%d, %d) present : (%d, %d) now height : %d now cost : %d max : %d\n", befloc.second + 1, befloc.first + 1, loc.second + 1, loc.first + 1, Hmap[loc.first][loc.second], currentCost, *endheight.rbegin());
	for(int i = 0; i < 4; i++){
		nextx = loc.second + dir[i].second;
		nexty = loc.first + dir[i].first;
		if(!locValid(loc, dir[i], M, N) || visit[nexty][nextx] || (nextx == befloc.second && nexty == befloc.first)){ continue;}
		tmp = getCost(Hmap[loc.first][loc.second], Hmap[nexty][nextx], T);
		backtmp = getCost(Hmap[nexty][nextx], Hmap[loc.first][loc.second], T);
		
		if(tmp != -1 && backtmp != -1 && currentCost + tmp <= S){
			dfs(Hmap, endheight, visit, dir, make_pair(nexty, nextx), loc, currentCost + backtmp + tmp, T, S, M, N);
		}
	}
}

unsigned int Return(int **Hmap, int N, int M, int T, int S){
	set<unsigned int> endheight;
	bool **visit = new bool*[N];
	pair<int, int> dir[4];
	dir[0].first = 1; dir[0].second = 0;
	dir[1].first = 0; dir[1].second = 1;
	dir[2].first = 0; dir[2].second = -1;
	dir[3].first = -1; dir[3].second = 0;
	int i;
	for(i = 0; i < N; i++){
		visit[i] = new bool[M];
		for(int j = 0; j < M; j++){
			visit[i][j] = false;
		}
	}
	dfs(Hmap, endheight, visit, dir, make_pair(0, 0), make_pair(0, 0), Hmap[0][0], T, S, M, N); // loc == x, y
	return *endheight.rbegin();
}


int main(int argc, char** argv){
	int N, M, T, S;
	// file read
	FILE * fr = fopen(argv[1], "r");
	fscanf(fr, "%d %d", &N, &M);
	fscanf(fr, "%d %d", &T, &S);
	
	int i, j;
	int **Hmap = new int*[N];

	for(i = 0; i < N; i++){
		Hmap[i] = new int[M];
		for(j = 0; j < M; j++){
			fscanf(fr, "%d", &Hmap[i][j]);
		}
	}
	fclose(fr);
	// file read close

	// **********
	unsigned long answer = Return(Hmap, N, M, T, S);
	// **********

	// file write
	FILE * fw = fopen(argv[2], "w");
	fprintf(fw, "%lu", answer);
	fclose(fw);
	// file write close
	return 0;
}

