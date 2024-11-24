#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
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
bool equals(node &tmp1, node &tmp2){
	if(tmp1.x == tmp2.x && tmp1.y == tmp2.y){
		return true;
	}
	return false;
}
int BS(vector<node> &graph, int p, int q, node &target){
	int r;
	while(p <= q){
		r = (p + q) / 2;
		if(equals(graph[r], target)) return r;
		if(!graphcomp(graph[r], target)) q = r - 1;
		else p = r + 1;
	}
	return -1;
}
double dist(node loc1, node loc2){
	double tmpx = pow(loc1.x - loc2.x, 2);
	double tmpy = pow(loc1.y - loc2.y, 2);
	return sqrt(tmpx + tmpy);
}
void connect(vector<node> &graph, int &n){
	sort(graph.begin(), graph.end(), graphcomp);	
	
	vector<pair<int, int> > xindex(1000001); // xindex[i].first = i가 graph에서 시작하는 index, .second = i가 그래프에서 끝나는 index 바로 다음, second는 다음 수의 시작 위치	
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

	int dirx[5] = {-2, -1, 0, 1, 2};
	int diry[5] = {-2, -1, 0, 1, 2};
	node tmp;
	int i, j;
	int find;
	//for(auto &it : graph){
	for(int k = 0; k < graph.size(); k++){
		i = graph[k].x < 2 ? 2-graph[k].x : 0;
		for(; i < 5; i++){
			tmp.x = graph[k].x + dirx[i];
			j = graph[k].y < 2 ? 2-graph[k].y : 0;
			for(; j < 5; j++){
				tmp.y = graph[k].y + diry[j];
				find = BS(graph, xindex[tmp.x].first, xindex[tmp.x].second, tmp);
				if(find != -1){
					while(graph[find].x == tmp.x && graph[find].y - graph[k].y < 3){
						graph[k].adj_list.push_back(&graph[find]);
						find++; j++;
					}
				}
			}
		}
	}
}
struct compare{
	bool operator()(node *loc1, node *loc2){
		return loc1->dist_from > loc2->dist_from;
	}
};

double Astar(vector<node> &graph, node tmpGoal, int &n, double &nowbest){
	priority_queue<node*, vector<node*>, compare> pq;
	for(int i = 0; i < graph[0].adj_list.size(); i++){
		if(graph[0].adj_list[i]->visit){
			continue;
		}
		graph[0].adj_list[i]->dist_from = dist(graph[0], *graph[0].adj_list[i]) + dist(*graph[0].adj_list[i], tmpGoal);
		pq.push(graph[0].adj_list[i]);
	}
	graph[0].visit = true;

	node* tmp;
	double tmp_dist;
	while(!pq.empty()){
		while(pq.top()->visit){
			pq.pop();
		}
		tmp = pq.top();
		if(tmp->dist_from > nowbest){
			return 1000000000001;
		}
		tmp->visit = true;
		if(tmp->x == tmpGoal.x && tmp->y == tmpGoal.y){
			tmp_dist = tmp->dist_from;
			for(int i = 0; i < n; i++){
				graph[i].visit = false;
				graph[i].dist_from = 1000000000001;
			}
			return tmp_dist;
		}
		for(int i = 0; i < tmp->adj_list.size(); i++){
			if(tmp->adj_list[i]->visit){
				continue;
			}
			tmp_dist = tmp->dist_from - dist(*tmp, tmpGoal) + dist(*tmp, *tmp->adj_list[i]) + dist(*tmp->adj_list[i], tmpGoal);
			if(tmp->adj_list[i]->dist_from > tmp_dist){
				tmp->adj_list[i]->dist_from = tmp_dist;
			}
			pq.push(tmp->adj_list[i]);
		}
		pq.pop();
	}
	return -1;
}
double Dijkstra(vector<node> &graph, node tmpGoal, int &n){
	priority_queue<node*, vector<node*>, compare> pq;
	pq.push(&graph[0]);
	for(int i = 0; i < graph[0].adj_list.size(); i++){
		graph[0].adj_list[i]->dist_from = dist(graph[0], *graph[0].adj_list[i]);
		pq.push(graph[0].adj_list[i]);
	}
	graph[0].visit = true;
	pq.pop();

	int esc_key;
	node* tmp;
	double tmp_dist;
	while(!pq.empty()){
		while(pq.top()->visit){
			pq.pop();
		}
		tmp = pq.top();
		tmp->visit = true;
        if(tmp->x == tmpGoal.x && tmp->y == tmpGoal.y){
			return tmp->dist_from;
		}
		for(int i = 0; i < tmp->adj_list.size(); i++){
			if(tmp->adj_list[i]->visit){
				continue;
			}
			tmp_dist = tmp->dist_from + dist(*tmp, *tmp->adj_list[i]);
			if(tmp_dist < tmp->adj_list[i]->dist_from){
				tmp->adj_list[i]->dist_from = tmp_dist;
				pq.push(tmp->adj_list[i]);
			}
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
	vector<node> graph;
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

	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	
    connect(graph, n);
	sort(goal.begin(), goal.end(), graphcomp);
	double answer = 1000000000001;
    double tmpAnswer;
    if(goal.size() == 1){
        answer = Dijkstra(graph, goal[0], n);
    }
    else{
		for(int i = 0; i < goal.size(); i++){
            tmpAnswer = Astar(graph, goal[i], n, answer);
            answer = answer > tmpAnswer ? tmpAnswer : answer;
        }
    }
	fprintf(fw, "%d", (int)(answer + 0.5));
	fclose(fw); // file close		
	return 0;
}
