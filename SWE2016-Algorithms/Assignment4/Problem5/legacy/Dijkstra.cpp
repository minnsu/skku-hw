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
	
	vector<pair<int, int>> xindex(1000001); // xindex[i].first = i가 graph에서 시작하는 index, .second = i가 그래프에서 끝나는 index 바로 다음, second는 다음 수의 시작 위치	
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
	for(auto &it : graph){
		i = it.x < 2 ? 2-it.x : 0;
		for(; i < 5; i++){
			tmp.x = it.x + dirx[i];
			j = it.y < 2 ? 2-it.y : 0;
			for(; j < 5; j++){
				tmp.y = it.y + diry[j];
				find = BS(graph, xindex[tmp.x].first, xindex[tmp.x].second, tmp);
				if(find != -1){
					while(graph[find].x == tmp.x && graph[find].y - it.y < 3){
						it.adj_list.push_back(&graph[find]);
						find++; j++;
					}
				}
			}
		}
	}
}
struct compare{
	bool operator()(node* loc1, node* loc2){
		return loc1->dist_from > loc2->dist_from;
	}
};
void function(vector<node> &graph, int &n){
	priority_queue<node*, vector<node*>, compare> pq;
	pq.push(&graph[0]);
	for(auto &it : graph[0].adj_list){
		it->dist_from = dist(graph[0], *it);
		pq.push(it);
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
		for(auto &it : tmp->adj_list){
			if(it->visit){
				continue;
			}
			tmp_dist = tmp->dist_from + dist(*tmp, *it);
			if(tmp_dist < it->dist_from){
				it->dist_from = tmp_dist;
				pq.push(it);
			}
		}
		pq.pop();

		esc_key = 0;
		for(auto &it : graph){
			if(it.visit){
				esc_key++;
			}
		}
		if(esc_key == n + 1){
			break;
		}
	}

}

int main(int argc, char** argv){
	int n, Goal_high;
    FILE* fr = fopen(argv[1], "r"); // open input file
    
	int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%d %d", &n, &Goal_high); // store input at inputstring
	// file scan
	int x, y;
	vector<node> graph;
	graph.push_back(node(0, 0));
	graph[0].dist_from = 0;
	double tmp_dist; 
	for(int i = 0; i < n; i++){
		fscanf(fr, "%d %d", &x, &y);
		graph.push_back(node(x, y));
	}
    fclose(fr); // file close

	connect(graph, n);
	function(graph, n);
	double answer = 1000001;
	for(auto &it : graph){
		if(it.visit && it.y >= Goal_high){
			if(answer > it.dist_from){
				answer = it.dist_from;
			}
		}
	}
	// file write
	FILE* fw = fopen(argv[2], "w"); // open output file
	fprintf(fw, "%d", (int)(answer + 0.5));
	fclose(fw); // file close		
	return 0;
}