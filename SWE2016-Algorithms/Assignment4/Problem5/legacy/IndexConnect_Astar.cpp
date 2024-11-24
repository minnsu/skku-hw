#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class node{
	public:
		bool visit;
		int x;
		int y;
		int myindex;
		double dist_from;
		vector<node*> adj_list;
		// vector<double> dist_list;
		
		node(){this->x = 0, this->y = 0;}
		node(int x, int y){
			this->visit = false;
			this->dist_from = 1000000000001;
			this->x = x;
			this->y = y;
			this->myindex = 0;
		}
};
bool graphcomp(node loc1, node loc2){
	if(loc1.x == loc2.x){
		return loc1.y < loc2.y;
	}
	return loc1.x < loc2.x;
}
double dist(node loc1, node loc2){
	double tmpx = pow(loc1.x - loc2.x, 2);
	double tmpy = pow(loc1.y - loc2.y, 2);
	return sqrt(tmpx + tmpy);
}
void connect(vector<node> &graph){
	sort(graph.begin(), graph.end(), graphcomp);
	vector<pair<int, int>> xindex(1000001); // xindex[i].first = i가 graph에서 시작하는 index, .second = i가 그래프에서 끝나는 index 바로 다음, second는 다음 수의 시작 위치
	
	double tmp_dist;
	int tmpx;
	
	int size = graph.size();
	for(int i = 0; i < size;){
		tmpx = graph[i].x;
		graph[i].myindex = i;
		xindex[tmpx].first = i;
		while(tmpx == graph[i].x){
			graph[i].myindex = i;
			i++;
		}
		xindex[tmpx].second = i;
	}
	int xm2, xm2e, xm1, xm1e, x0, x0e, xp1, xp1e, xp2, xp2e; // x-2, x-2end ...
	int tmpiter;
	for(int i = 0; i < size; i++){
		if(graph[i].x > 1){ // 2이상인 경우에만 -2, -1 가능
			xm2 = xindex[graph[i].x-2].first; xm2e = xindex[graph[i].x-2].second;
			xm1 = xindex[graph[i].x-1].first; xm1e = xindex[graph[i].x-1].second;
		}
		else{
			if(graph[i].x == 1){
				xm1 = xindex[0].first; xm1e = xindex[0].second;
			}
			else{
				xm1 = 0; xm1e = 0;
			}
			xm2 = 0; xm2e = 0;
		}
		x0 = xindex[graph[i].x].first; x0e = xindex[graph[i].x].second;
		xp1 = xindex[graph[i].x+1].first; xp1e = xindex[graph[i].x+1].second;
		xp2 = xindex[graph[i].x+2].first; xp2e = xindex[graph[i].x+2].second;
		
		while(xm2 < xm2e && graph[xm2].y - graph[i].y < 3){
			tmp_dist = dist(graph[i], graph[xm2]);
			if(tmp_dist < 3){
				graph[i].adj_list.push_back(&graph[xm2]);
			}
			xm2++;
		}
		while(xm1 < xm1e && graph[xm1].y - graph[i].y < 3){
			tmp_dist = dist(graph[i], graph[xm1]);
			if(tmp_dist < 3){
				graph[i].adj_list.push_back(&graph[xm1]);
			}
			xm1++;
		}
		while(x0 < x0e && graph[x0].y - graph[i].y < 3){
			tmp_dist = dist(graph[i], graph[x0]);
			if(tmp_dist < 3){
				if(graph[x0].y == graph[i].y){
					x0++;
					continue;
				}
				graph[i].adj_list.push_back(&graph[x0]);
			}
			x0++;
		}
		while(xp1 < xp1e && graph[xp1].y - graph[i].y < 3){
			tmp_dist = dist(graph[i], graph[xp1]);
			if(tmp_dist < 3){
				graph[i].adj_list.push_back(&graph[xp1]);
			}
			xp1++;
		}
		while(xp2 < xp2e && graph[xp2].y - graph[i].y < 3){
			tmp_dist = dist(graph[i], graph[xp2]);
			if(tmp_dist < 3){
				graph[i].adj_list.push_back(&graph[xp2]);
			}
			xp2++;
		}
	}
	for(int i = 0; i < size; i++){
		printf("(%d, %d) ->", graph[i].x, graph[i].y);
		for(auto &it : graph[i].adj_list){
			printf(" (%d, %d)", it->x, it->y);
		}
		printf("\n");
	}
}
struct compare{
	bool operator()(node *loc1, node *loc2){
		return loc1->dist_from > loc2->dist_from;
	}
};

double JUMP(vector<node> &graph, node tmpGoal, int &n){
	priority_queue<node*, vector<node*>, compare> pq;
	//pq.push(&graph[0]);
	for(auto &it : graph[0].adj_list){
		if(it->visit){
			continue;
		}
		it->dist_from = dist(graph[0], *it) + dist(*it, tmpGoal);
		pq.push(it);
		printf("graph[0] push -> (%d, %d)\n", it->x, it->y);
	}
	graph[0].visit = true;
	//pq.pop();

	node* tmp;
	double tmp_dist;
	while(!pq.empty()){
		while(pq.top()->visit){
			pq.pop();
		}
		tmp = pq.top();
		tmp->visit = true;
		printf("visited : (%d, %d) : %lf\n", tmp->x, tmp->y, tmp->dist_from);
		if(tmp->x == tmpGoal.x && tmp->y == tmpGoal.y){
			printf("Answer in this goal : %lf\n", tmp->dist_from);
			tmp_dist = tmp->dist_from;
			for(int i = 0; i < n; i++){
				graph[i].visit = false;
				graph[i].dist_from = 1000000000001;
			}
			return tmp_dist;
		}
		for(auto &it : tmp->adj_list){
			if(it->visit){
				continue;
			}
			tmp_dist = tmp->dist_from - dist(*tmp, tmpGoal) + dist(*tmp, *it) + dist(*it, tmpGoal);
			if(it->dist_from > tmp_dist){
				it->dist_from = tmp_dist;
			}
			pq.push(it);
		}
		pq.pop();
	}
	return -1;
}

int main(int argc, char** argv){
	int n, Goal_high;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n, &Goal_high); // store input at inputstring
	// file scan
	int x, y;
	//vector<node> graph;
	vector<node> graph;
	//graph.push_back(node(0, 0));
	graph.push_back(node(0,0));
	vector<node> goal;
	graph[0].dist_from = 0;
	double tmp_dist;
	
	for(int i = 0; i < n; i++){
		fscanf(fr, "%d %d", &x, &y);
		if(y >= Goal_high){
			goal.push_back(node(x, y));
		}
		graph.push_back(node(x, y));	
	}
    fclose(fr); // file close

	connect(graph);
	sort(goal.begin(), goal.end(), graphcomp);
	double answer = 1000000000001;
	double tmpAnswer;
	for(auto &it : goal){
		printf("Goal location : (%d, %d)\n", it.x, it.y);
		tmpAnswer = JUMP(graph, it, n);
		answer = answer > tmpAnswer ? tmpAnswer : answer;
	}
	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	fprintf(fw, "%d", (int)(answer + 0.5));
	fclose(fw); // file close		
	return 0;
}
