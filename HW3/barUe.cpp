#include <bits/stdc++.h>

using namespace std;

vector<string> arr;

int main() {

	string s = "A_PENNY_SAVED_IS_A_PENNY_EARNED.";
//	string s = "IF_WE_CANNOT_DO_AS_WE_WOULD_WE_SHOULD_DO_AS_WE_CAN";

	string end = "";
	int n = s.size();
	for (int i = 0; i < n; i++) {
		string cur = "";
		for (int j = 0; j < n; j++) {
			cur += s[(j + i) % n];
		}
		arr.push_back(cur);
	
	}
	sort(arr.begin(), arr.end());
	for (int i = 0; i < n; i++) {
		end += arr[i][n - 1];
		cout << i + 1 << "; " << arr[i] << endl;
	}
	cout << end << endl;
	bool have[1000];
	bool hh[1000];
	for (int i = 0; i < 1000; i++) have[i] = false;
	for (int i = 0; i < n; i++) {
		int c = end[i];
		if (!have[c]) {
			cout << "esc ";
			have[c] = true;
		} else {
			for (int j = 0; j < 1000; j++) hh[j] = false;
			int cur = i - 1;
			int cnt = 0;
			while (cur >= 0) {
				if (end[cur] == c) break;
				if (!hh[end[cur]]) {
					hh[end[cur]] = true;
					cnt++;
				}
				cur--;
			}			
		    cout << cnt << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < 1000; i++) have[i] = false;
	bool ok[1000];
	for (int i = 0; i < end.size(); i++) {
		if (!have[end[i]]) {
			ok[i] = true;
			have[end[i]] = true;
		} else {
			ok[i] = false;
		}
	}

	int cur = 0;
	int step = 0;
	while (cur < end.size()) {
		int st = cur;		
		int sn = cur + 1;			
		while (sn < end.size() && end[sn] == end[st]) sn++;
		int st2 = sn;
		while (sn < end.size() && end[sn] != end[st]) sn++;
		int cnt = 0;
		if (sn != end.size()) {			
			for (int i = st2; i <= sn; i++) {
				if (!ok[i]) cnt++;
			}
		}
		cur = st2;
		int q = 0;
		for (int i = st2; i < end.size(); i++) {
			if (!ok[i]) q++;
		}
		cout << step << "; ";
		for (int j = 0; j < end.size(); j++) {
			if (j == st) cout << "|";
			if (ok[j]) cout << end[j];
			else cout << "?";
			if (j == sn) cout << "|";
		}
		cout << "; " << cnt << " ";
		if (cnt == 0) cout << endl;
		else cout << "(" << q << ")" << endl;			
		ok[sn] = true;
		for (int i = st + 1; i < st2; i++) {
			ok[i] = true;
		}
		step++;

	}

	return 0;
}