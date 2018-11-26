#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

/*
	WE ASSUME THAT LINES ARE SORTED BY SLOPE
	IN *DESCENDING* ORDER
	TYPE MUST BE CHANGED IF DOUBLES, INTS OR SOMETHING ELSE
	IS DESIRED
*/
struct line {
	ll a, b;
	ll eval(ll x) {
		return a*x + b;
	}
};

struct convex_hull_opt {
	vector< line > hull;
	
	convex_hull_opt() {
		hull = vector< line >();
	}

	bool compatible() {
		line cand = hull[hull.size() - 1];
		line top  = hull[hull.size() - 2];
		line stop = hull[hull.size() - 3];
		ll cand_top  = (cand.a - stop.a)*(top.b  - cand.b);
		ll cand_stop = (cand.a -  top.a)*(stop.b - cand.b);
		return cand_stop > cand_top;
	}

	void add_line(line a) {
		hull.push_back(a);
		while(hull.size() > 2 && !compatible()) {
			hull[hull.size() - 2] = hull.back();
			hull.pop_back();
		}
	}

	pair<ll, int> query(ll x) {
		if(hull.size() == 1) return {hull[0].eval(x), 0ll};
		int l = 0, r = int(hull.size() - 1);
		pair<ll, int> ret(0, 0);
		for(int i=0; i < 30; ++i) {
			int h = (l + r) / 2;
			ll fh  = hull[h].eval(x);
			ll fh1 = hull[h + 1].eval(x);
			if(fh <= fh1) {
        l = h;
      }
			else {
        r = h;
      }
			ret = max(ret, {fh, h});
			ret = max(ret, {fh1, h + 1});
		}
		return ret;
	}

	~convex_hull_opt() {
		hull.clear();
	}

};



int main() {

}
