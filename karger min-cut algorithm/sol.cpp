#include <random>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

int selectRandomNum1(int n){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n);
    return dis(gen);
}

int selectRandomNum2(int n){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, n);
	return dis(gen);
}

int main(){
    int n=200;
    vector<vector<int> > graph;
    for(int i=0; i < n; i++){
        int a;
        vector<int> adj;
        string line;
        getline(cin, line);
        istringstream iss(line);
        while(iss >> a){
            adj.push_back(a);
        }
        graph.push_back(adj);
        cin.clear();
    }
    
    while(n>2){
		//random vertex index in graph
		int v1_index = selectRandomNum1(n - 1);
		int v2_index = selectRandomNum2(graph[v1_index].size() - 1);
		
		//edge b/w adj v1 & v2
		int v1 = graph[v1_index][0]; //cout << "v1= " << v1 << endl;
		int v2 = graph[v1_index][v2_index]; //cout << "v2= " << v2 << endl;

		if (v1 < v2){
			//rename that vertex to min/max of them
			int minnum = min(v1, v2);
			int maxnum = max(v1, v2);

			//edge contraction
			for (auto i = 0; i < graph.size(); i++){
				if (graph[i][0] == minnum){
					for (auto j = 1; j < graph[i].size(); j++){
						if (graph[i][j] == maxnum){
							graph[i].erase(graph[i].begin() + j);
							if (graph[i][j] == maxnum){
								--j;
							}
						}
					}
				}
				else if (graph[i][0] == maxnum){
					for (auto j = 1; j < graph[i].size(); j++){
						if (graph[i][j] != minnum){
							graph[v1_index].push_back(graph[i][j]);
						}
					}
					graph.erase(graph.begin() + i);
					--i;
				}
				else{
					for (auto j = 1; j < graph[i].size(); j++){
						if (graph[i][j] == maxnum){
							graph[i][j] = minnum;
						}
					}
				}
			}
		}
		else{
			//rename that vertex to min/max of them
			int minnum = min(v1, v2);
			int maxnum = max(v1, v2);

			//edge contraction
			for (auto i = 0; i < graph.size(); i++){
				if (graph[i][0] == minnum){
					v2_index = i;
					for (auto j = 1; j < graph[i].size(); j++){
						if (graph[i][j] == maxnum){
							graph[i].erase(graph[i].begin() + j);
							if (graph[i][j] == maxnum){
								--j;
							}
						}
					}
				}
				else if (graph[i][0] == maxnum){
					for (auto j = 1; j < graph[i].size(); j++){
						if (graph[i][j] != minnum){
							graph[v2_index].push_back(graph[i][j]);
						}
					}
					graph.erase(graph.begin() + i);
					--i;
				}
				else{
					for (auto j = 1; j < graph[i].size(); j++){
						if (graph[i][j] == maxnum){
							graph[i][j] = minnum;
						}
					}
				}
			}
		}
		/*
		cout << "Iterations" << endl;
		for (auto i = 0; i < graph.size(); i++){
		for (auto j = 0; j < graph[i].size(); j++){
		cout << graph[i][j] << " ";
		}
		cout << endl;
		}
		cout << endl;
		*/
		
		n--;
	}
    
	cout << "Karger min cut is " << graph[0].size() << endl;

    return 0;
}
