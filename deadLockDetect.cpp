/*
 * deadLockDetect.cpp
 *
 *  Created on: 2019年9月2日
 *      Author: wen
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;


//===============================================
//use TopSort to check whether the wfg has circles. If the wfg has circles, TopSort will fail.
//===============================================I
bool topSort(vector<vector<int>> &wfg, int n, vector<int> &inDegree) {
	int num = 0;
	//store all node that indegree is 0
	queue<int> zero_queue;
	for (int i = 0; i < n; i++)
		//push the node which indegree is 0
		if (inDegree[i] == 0)
			zero_queue.push(i);
	while (!zero_queue.empty()) {
		int u = zero_queue.front();
		zero_queue.pop();
		for (int i = 0; i < wfg[u].size(); i++) {
			int v = wfg[u][i];
			inDegree[v]--;
			if (inDegree[v] == 0)
				zero_queue.push(v);
		}
		wfg[u].clear();
		num++;
	}
	//if topsort success, it is non-circle, otherwise it has circles
	if (num == n)
		return true;
	else
		return false;
}

int main(){
	int len;
	map<int, vector<int> > resources;
	vector<vector<int> > wfg;
	vector<int> inDegree;


	//read input
	cin >> len;
	for(int i = 0; i<len; i++){
		int proc, res;
		cin >> proc >> res;
		resources[res].push_back(proc);
	}

	//loop the input and form the wfg and the node's indegree
	for(map<int, vector<int> >::iterator it = resources.begin(); it!=resources.end(); it++){
		vector<int>& procs = it->second;
		for(int i = 1; i<procs.size(); i++){
			if(wfg.size() <= procs[i]) wfg.resize(procs[i]+1);
			wfg[procs[i]].push_back(procs[i-1]);

			if(inDegree.size() <= procs[i-1])  inDegree.resize(procs[i-1]+1);
			++inDegree[procs[i-1]];
		}
	}

	//use TopSort to judge whether the wfg has circles. If so, we find a dead lock.
	if(topSort(wfg, wfg.size(), inDegree))
		cout << "well, thing seems ok.";
	else
		cout << "oops, find dead locks!!!";
	cout << endl;


}


