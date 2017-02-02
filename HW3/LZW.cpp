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

vector<string> dict;


int have(string x) {
	for (int i = 0; i < dict.size(); i++) {
		if (dict[i] == x) return i;
	}
	return -1;
}

int main() {
	string s = "A_PENNY_SAVED_IS_A_PENNY_EARNED.";
//	string s = "IF_WE_CANNOT_DO_AS_WE_WOULD_WE_SHOULD_DO_AS_WE_CAN";
	int n = s.size();	
	int i = 0;
	int step = 1;
	while (i < n) {
		int j = 0;
		string cur = "";
		cur += s[i + j];
		int pos = have(cur);
		while (i + j < n && have(cur) != -1) {
			pos = have(cur);
			j++;
			cur += s[i + j];
		}
		dict.push_back(cur);
		i += j;
		if (j == 0) i++;
		string kk = to2(pos + 1);
		int ll = kk.size();
		if (j == 0) {
			kk += "bin(" + cur + ")";
			ll += 8;
	   	}
		cout << step << ";" << cur << ";" << pos + 1 << ";" << kk << ";" << ll << endl;
		step++;			
	}

	return 0;
}