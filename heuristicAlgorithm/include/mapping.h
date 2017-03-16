/**
@file mapping.h
@anthor yifan hao
@function analysis the network graph, return results based on qeuries
*/

#ifndef MAPPING_H
#define MAPPING_H

#include<map>
#include<vector>
#include<string.h>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
using namespace std;
class mapping
{
	public:
		//class sort_map;
		//deriction of graph file
		string in_str;
		//node number
		int nodeNum;
		//edge number
		int edgeNum;
		//lable number
		int labelNum;
		map < int,vector < int > > nodeVecMap; 
		//Map from node Id to node degree
		map < int, int > nodeDegMap;
		//the hierachy tree
		map<int, vector<int> > hierachyMap;
		
		//Map from edgeId to vector of edgeLabel
		map < int, vector< int > > edgeLabelMap;
			
	public:
		//////////////////////////////////////
		bool checkEdgeBetweenTwoNodes(int nodeFirst, int nodeSecond);

		//////////////////////////////////////
		//Add edge to graph
		//return bool
		bool addEdge(int nodeFirst, int nodeSecond);

		//////////////////////////////////////
		//Hierachy tree part
		//Function read Mapping of Hierachy tree
		//parameter: fileLoc
		//return map
		bool readHierachyTree(string fileLoc);
		
		//Hierachy tree part
		//Function return Mapping of Hierachy tree
		//parameter: fileLoc
		//return map
		map <int, vector<int> > getHierachyTree();
		//////////////////////////////////////
		//myGraph part
		//Function getEdgeLabelMap
		//get degeLabelMap
		//return: map from edgeId to vector of edgeLabel
		map < int, vector< int > > getEdgeLabelMap();
		
		//Function writeEdgeLabelMap
		//write degeLabelMap
		//return bool
		bool writeEdgeLabelMap();
		// end of myGraph part
		//////////////////////////////////////


		//Constructor		
		mapping();
		
		//////////////////////////////////////
		//Function writeStr
		//Write deriction of graph to in_str
		//Parameter deriction
		void writeStr(string);

		//////////////////////////////////////
		//Function readStr
		//Read deriction of graph to in_str
		string readStr();
		

		//////////////////////////////////////
		//Function getNodeVecMap
		//Get nodeVecMap
		//Return: Map of nodeVecMap
		map < int,vector < int > > getNodeVecMap();

		//////////////////////////////////////
		//Function writeNodeVecMap
		//Write nodeVecMap
		//Return: bool
		bool writeNodeVecMap();
		
		//////////////////////////////////////
		//Function getNodeDegMap
		//Get nodeDegMap
		//Return: Map of nodeDegMap
		map < int,int > getNodeDegMap();

		//////////////////////////////////////
		//Function writeNodeDegMap
		//Write nodeDegMap
		//Return: bool
		bool writeNodeDegMap();
		
		//////////////////////////////////////
		//Function sortVectexBasedOnDegree
		//Sort vectex based on degree
		//return 
		//
		//vector<sort_map> mapping :: sortVectexBasedOnDegree(map < int,vector < int > > vecMap);
		bool checkGraphDegree(int k);

};

#endif // MAPPING_H
