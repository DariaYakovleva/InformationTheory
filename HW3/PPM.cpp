#include <bits/stdc++.h>

using namespace std;

string to2(int a) {
	int pp = 1;
	int st = 0;
	while (pp <= a) {
		pp *= 2;
		st++;
	}
	string res = "";
	for (int i = st; i >= 0; i--) {
		if (a >= pp) {
			res += "1";
			a -= pp;
					
		} else {
			res += "0";
		}
		pp /= 2;
	}
	return res;
}

int getCnt(string a, string b) {
	int res = 0;
	for (char c: a) {
		if (c == b[0]) res++;
	}
	return res;
}

int dist(string a) {
	sort(a.begin(), a.end());
	char cur = a[0];
	int res = 1;
	for (char c: a) {
		if (c != cur) {
			res++;
			c = cur;
		}
	}
	return res;
}


map<string, string> dict;

int main() {
//	string s = "A_PENNY_SAVED_IS_A_PENNY_EARNED.";
	string s = "IF_WE_CANNOT_DO_AS_WE_WOULD_WE_SHOULD_DO_AS_WE_CAN";
	const int D = 5;
	int n = s.size();	
	dict["#"] = "";
	vector<string> conts;
	for (int step = 0; step < n; step++) {
		cout << step << "; " << s[step] << "; ";

		string curLetter = "";
		curLetter += s[step];
		conts.clear();
		for (int i = 0; i < step; i++) {
			string cont = "";
			for (int j = i; j < step; j++) {
				cont += s[j];
			}
			if (cont.size() > D) continue;
			if (dict.count(cont) == 1) {
				conts.push_back(cont);
				dict[cont] += curLetter;
			} else {
				dict[cont] = curLetter;
			}			
		}
		dict["#"] += curLetter;
		conts.push_back("#");

		cout << conts[0] << ";";

		for (int i = 0; i < conts.size(); i++) {
			string x = conts[i];
			cout << dict[x].size() - 1;
			if (i + 1 < conts.size()) cout << ",";
		}
		cout << "; ";
		for (int i = 0; i < conts.size(); i++) {
			if (dict.count(conts[0] + curLetter) > 0) break;
			if (conts.size() == 1 && dict.count(curLetter) > 0) break;
			string x = conts[i];
			int mm = 0;
			if (i > 0) mm = dist(dict[conts[i - 1]]) - 1;
			cout << "1/" << (dict[x].size() - mm);
			if (i + 1 < conts.size()) cout << "*";
		}
		cout << "; ";

		cout << getCnt(dict[conts[0]], curLetter) << "/" << (dict[conts[0]].size() + 1);

		cout << endl;

	}







	return 0;
}