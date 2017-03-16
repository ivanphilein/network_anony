#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class sort_map
{
  public:
	string key;
	int val;
};

bool Sort_by(const sort_map& a ,const sort_map& b)
{
	return a.val > b.val;
}
	
int main()
{
	map<string,int> d;
	map<string,int>::iterator it;
	vector< sort_map > v;
	vector< sort_map >::iterator itv;
	sort_map sm;
	
	d["a"] = 5; d["b"] = 3; d["c"] = 9; d["d"] = 7; d["e"] = 1; d["f"] = 13; d["g"] = 11;
	
	for (it = d.begin(); it != d.end(); ++it)
	{
		sm.key = (*it).first; sm.val = (*it).second;
		v.push_back(sm);
	}
	for (itv = v.begin(); itv != v.end(); ++itv)
	{
		cout << (*itv).key << " : " << (*itv).val << endl;
	}
	
	sort(v.begin(),v.end(),Sort_by);
	
	cout << "sorted" << endl;
	for (itv = v.begin(); itv != v.end(); ++itv)
	{
		cout << (*itv).key << " : " << (*itv).val << endl;
	}
	
	return 0;
}
