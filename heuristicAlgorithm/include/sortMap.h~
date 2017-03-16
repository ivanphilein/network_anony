#ifndef SORTMAP_H
#define SORTMAP_H
#include <algorithm>
#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////
//sort vectex vector part
class sort_map
{
  public:
	int key;
	int val;
	bool checked;
	bool sort;
	int group;
	vector<sort_map> :: iterator point;
	vector<sort_map> :: iterator unpoint;
	sort_map():checked(false),sort(false),point(NULL),unpoint(NULL){};

	sort_map * copy(){
		sort_map *newsm = new sort_map();
		newsm->key = key;
		newsm->val = val;
		newsm->checked = checked;
		newsm->sort = sort;
		newsm->group = group;
		newsm->point = point;
		newsm->unpoint = unpoint;
		return newsm;
	}

};

bool Sort_by(const sort_map& a ,const sort_map& b)
{
	/*if(a.sort==false&&b.sort==true)
		return true;
	else if(a.sort==true&&b.sort==false)
		return false;
	else*/
	return a.val > b.val;
}


//Function sortVectexBasedOnDegree
//Sort vectex based on degree
//return 
//
vector<sort_map> sortVectexBasedOnDegree(vector<sort_map> retVec)
{
	//sort_map sm;
	sort(retVec.begin(),retVec.end(),Sort_by);
	//qsort(retVec.begin(),retVec.size(),sizeof(sort_map),compare);
	return retVec;
}

//Function sortVectexBasedOnDegree
//Sort vectex based on degree
//return 
//
vector<sort_map> sortVectexBasedOnDegree(map < int, int > vecMap)
{
	sort_map sm;
	vector<sort_map> retVec;
	for (map < int, int > :: iterator it = vecMap.begin(); it != vecMap.end(); ++it)
	{
		sm.key = (*it).first; 
		sm.val = (*it).second;
		retVec.push_back(sm);
	}
	/*for (vector<sort_map> :: iterator itv = retVec.begin(); itv != retVec.end(); ++itv)
	{
		cout << (*itv).key << " : " << (*itv).val << endl;
	}*/
	sort(retVec.begin(),retVec.end(),Sort_by);
	/*cout << "sorted" << endl;
	for (vector<sort_map> :: iterator itv = retVec.begin(); itv != retVec.end(); ++itv)
	{
		cout << (*itv).key << " : " << (*itv).val << endl;
	}*/
	return retVec;
}

//end of sort vectex vector part
//////////////////////////////////////////////////////////////////////////
#endif // SORTMAP_H
