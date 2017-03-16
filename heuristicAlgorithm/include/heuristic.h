#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "../include/mapping.h"
#include "../include/sortMap.h"
class heuristic
{
	private:
		
	public:
		//////////////////////////////////////////////
		//Function achieve_k_anonymity
		//Input: graph class, int k
		//Output a graph with degree anonymized
		bool achieve_k_anonymity(mapping& graph,int& k);
		bool achieve_k_anonymity(mapping& graph,int& k,int method);
		//////////////////////////////////////////////
		bool heuristicAnonymizeDegree(sort_map& seedVectex, vector<sort_map>& unAnonymityList, vector<sort_map>& candiateSet, vector<sort_map>& vectexListSorted,mapping& graph,int group);
		//////////////////////////////////////////////
		bool anonymizeAvailable(int nodeID, vector<sort_map>& readyVec, mapping& myGraph);
		bool anonymizeAvailable(int nodeID, vector<sort_map>& readyVec, int star,int,mapping& myGraph);


		bool writeVecIntoFile(mapping myGraph, string outLoc);

		bool writeLogFile(map<string,string> logMap,string logLoc);

		//bool Sort_by(const sort_map& a ,const sort_map& b);

};


#endif // HEURISTIC_H
