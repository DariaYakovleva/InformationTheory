#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

string inputData = "";
map<string, int> counts;
vector<pair<string, double>> probability;
int main() {
	freopen("xargs.1", "r", stdin);
	freopen("out.out", "w", stdout);    	
	string cur = "";
	while (getline(cin, cur)) {
		inputData += cur;
	}
	cout << "count = " << inputData.size() << endl;
	for (int n = 1; n <= 200; n++) {
		int len = inputData.size() - n;
		counts.clear();
		probability.clear();
		for (int i = 0; i < len; i++) {
			cur = "";
			for (int j = 0; j < n; j++) {
				cur += inputData[i + j];
			}		
			counts[cur]++;
		}       	
		double sum = 0.0;
//		cout << "n = " << n << endl;
		for (pair<string, int> elem: counts) {
//			cout << sum / len << "; ";
			sum += (double)elem.second;
			probability.push_back(make_pair(elem.first, (double)elem.second / len));
		}
		cout << sum / len << endl;
		// entropy
		double entropy = 0.0;
		int uniqueN = probability.size();
		for (int i = 0; i < uniqueN; i++) {
			double curProb = probability[i].second;
//			cout << curProb << " " << log2(curProb) << endl;
			entropy -= curProb * log2(curProb);
		}
//		cout << "n = " << n << ", entropy = " << entropy << " expected size = " << entropy * len  << " bits" << endl;
		cout << n << " & " << entropy / n << " & " << entropy * (inputData.size() / n) << "\\\\\n\\hline" << endl;
	}

	return 0;
}