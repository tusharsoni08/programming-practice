#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#define MAXV 875714 //total number of vertices
using namespace std;

struct Node{
	int finish_time = 0;
	bool explored = false;
	int num;
	vector<int> out;
	vector<int> in;
};

struct Order {
	int node_num;
	int finishTime;
};

vector<Node> G(MAXV);
vector<Order> v(MAXV);
vector<int> scc;
int t = 0;

void dfs_reverse(int m) {
	G[m].explored = true;
	for (int i = 0; i < G[m].in.size(); i++) {
		if (!G[G[m].in[i]-1].explored) {
			dfs_reverse(G[m].in[i]-1);
		}
	}
	t++;
	G[m].finish_time = t;
}

bool myCmpFun(Order a, Order b) {
	return (a.finishTime < b.finishTime);
}

void dfs(int m, int &count) {
	G[m].explored = true;
	for (int i = 0; i < G[m].out.size(); i++) {
		if (!G[G[m].out[i] - 1].explored) {
			count++;
			dfs(G[m].out[i] - 1, count);
		}
	}
}

int main(){	
	string line;

	while (getline(cin, line)){
		int a, b;
		istringstream iss(line);
		iss >> a;
		iss >> b;
		if (a != b) {
			G[a - 1].num = a;
			G[a - 1].out.push_back(b);
			G[b - 1].in.push_back(a);
		}
		cin.clear();
	}

	//set the node num of uninitialized node
	for (int i = 0; i < MAXV; i++) {
		if (G[i].num == 0) {
			G[i].num = i + 1;
		}
	}

	//compute finishing time
	for (int i = MAXV-1; i >= 0; i--) {
		if ((G[i].num != 0) && !G[i].explored) {
			dfs_reverse(i);
		}
	}

	//keep the relation b/w node_num and finish time
	for (int i = 0; i < MAXV; i++) {
		v[i].node_num = G[i].num;
		v[i].finishTime = G[i].finish_time;
		G[i].explored = false;
	}

	//sort with finishing time
	sort(v.begin(), v.end(), myCmpFun);

	//compute SCC using finishing time
	for (int i = MAXV - 1; i >= 0; i--) {
		if (!G[v[i].node_num - 1].explored) {
			int count = 1;
			dfs(v[i].node_num - 1, count);
			scc.push_back(count);
		}
	}

	/*for (int i = 0; i < G.size(); i++) {
		cout << "node num: " << G[i].num << endl;
		cout << "Out vertices: [";
		for (int j = 0; j < G[i].out.size(); j++) {
			cout << G[i].out[j] << ", ";
		}
		cout << "] " << endl;
		cout << "In vertices: [";
		for (int j = 0; j < G[i].in.size(); j++) {
			cout << G[i].in[j] << ", ";
		}
		cout << "] " << endl;
		cout << "Explored: " << G[i].explored << endl;
		cout << "Finish time: " << G[i].finish_time << endl;
		cout << endl;
	}

	for (auto i : v) {
		cout << "node num: " << i.node_num << endl;
		cout << "finishTime: " << i.finishTime << endl;
		cout << endl;
	}*/
	
	//5 largest SCCs in the graph, in decreasing order of sizes
	sort(scc.rbegin(), scc.rend());
	for (auto i = 0; i < 5; i++) {
		cout << scc[i] << ",";
	}
	cout << endl;

	return 0;
}