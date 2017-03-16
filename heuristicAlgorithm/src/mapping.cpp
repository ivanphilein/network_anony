/**
@file mapping.cpp
@anthor yifan hao
@function analysis the network graph, return results based on qeuries
*/

#include "../include/mapping.h"
#include <algorithm>

//Constructor
mapping::mapping():in_str("a"),nodeNum(0),edgeNum(0),labelNum(0){}

//Function getEdgeLableMap
//get degeLabelMap
//return: map from edgeId to vector of edgeLabel
map < int, vector< int > > mapping::getEdgeLabelMap()
{
	return this-> edgeLabelMap;
}

//////////////////////////////////////
//Hierachy tree part
//Function get Mapping of Hierachy tree
//parameter: fileLoc
//retunr map
bool mapping :: readHierachyTree(string hie_str)
{
	ifstream infile;
	infile.open(hie_str.c_str());
	int fir_num, sec_num;
	if(!infile)
	{
		cerr << "error: unable to open file: " << hie_str<< endl;
		return false;
	}
	else
	{
		string line;
		while (getline( infile, line))
		{
			//cout<<line<<endl;
			// if the line is blank, ignore it
			if (line=="") continue;
			// get the first integer off the line
			stringstream linestream( line );
			int n;
			if (line.find("%")==0)
				continue;
			else if(line.find("*")==0)
				break;
			else
			{
				linestream >>fir_num >> sec_num;
				hierachyMap[fir_num].push_back(sec_num); 
				//hierachyMap[sec_num].push_back(fir_num);
			}
		}



		
	}
	infile.close();
	return true;
}

//Hierachy tree part
//Function return Mapping of Hierachy tree
//parameter: fileLoc
//return map
map <int, vector<int> > mapping :: getHierachyTree()
{
	return this->hierachyMap;
}
//////////////////////////////////////

//Function writeEdgeLabelMap
//write degeLabelMap
//return bool
bool mapping::writeEdgeLabelMap()
{
	//open stream of file
	ifstream infile;
	infile.open(in_str.c_str());
	if(!infile)
	{
		cerr << "error: unable to open file: " << in_str << endl;
		return false;
	}
	infile >> this->nodeNum;
	infile >> this->edgeNum;
	infile >> this->labelNum;		
	int fir_num, sec_num;
	int eNum = 0;
	//vector <int> edgeVec[this->edgeNum];
	int temStr;
	while(infile >> fir_num >> sec_num)
	{	
		edgeLabelMap[eNum].push_back(fir_num);
		edgeLabelMap[eNum].push_back(sec_num);
		for(int i=0;i!=labelNum;i++)
		{
			infile >> temStr;
			edgeLabelMap[eNum].push_back(temStr);
		}
		/*edgeVec[eNum].push_back(fir_num);
		edgeVec[eNum].push_back(sec_num);
		for(int i=0;i!=labelNum;i++)
		{
			infile >> temStr;
			edgeVec[eNum].push_back(temStr);
		}
		edgeLabelMap[eNum] = edgeVec[eNum];*/
		eNum++;
	}
	infile.close();
	return true;
}

//Function writeStr
//Write deriction of graph to in_str		
//Parameter deriction
void mapping::writeStr(string c_str)
{
	this->in_str = c_str;
}

//Function readStr
//Read deriction of graph to in_str
string mapping::readStr()
{
	return in_str;
}

//Function getNodeVecMap
//Get nodeVecMap
//Return: Map of nodeVecMap
map < int,vector < int > > mapping::getNodeVecMap()
{
	return nodeVecMap;
}

//Function writeNodeVecMap
//Write nodeVecMap
//Return: bool
bool mapping::writeNodeVecMap()
{
	//open stream of file
	ifstream infile;
	infile.open(in_str.c_str());
	if(!infile)
	{
		cerr << "error: unable to open file: " << in_str << endl;
		return false;
	}
	infile >> this->nodeNum;
	infile >> this->edgeNum;
	infile >> this->labelNum;	
	//cout<<this->nodeNum<<" "<<this->labelNum<<endl;
	//vector <int> nodVector;
	//vector <int> nodVector[nodeNum+1];	
	int fir_num, sec_num;
	while(infile >> fir_num >> sec_num)
	{	
		this -> nodeVecMap[fir_num].push_back(sec_num);
		this -> nodeVecMap[sec_num].push_back(fir_num);
		/*nodVector[fir_num].push_back(sec_num);
		nodVector[sec_num].push_back(fir_num);
		this -> nodeVecMap[fir_num] = nodVector[fir_num];
		this -> nodeVecMap[sec_num] = nodVector[sec_num];*/
		for(int i=0;i!=labelNum;i++)
			infile >> fir_num;
	}
	infile.close();
	return true;
}

//Function getNodeDegMap
//Get nodeDegMap
//Return: Map of nodeDegMap
map < int,int > mapping::getNodeDegMap()
{
	return nodeDegMap;
}

//Function writeNodeDegMap
//Write nodeDegMap
//Return: bool
bool mapping::writeNodeDegMap()
{
	//open stream of file
	ifstream infile;
	infile.open(in_str.c_str());
	if(!infile)
	{
		cerr << "error: unable to open file: " << in_str << endl;
		return false;
	}
	
	infile >> this->nodeNum;
	infile >> this->edgeNum;
	infile >> this->labelNum;	
	int tmp_str;
	while(infile >> tmp_str)
	{	
		this-> nodeDegMap[tmp_str] += 1;
		infile >> tmp_str;
		this-> nodeDegMap[tmp_str] += 1;
		for(int i=0;i!=labelNum;i++)
			infile >> tmp_str;
	}
	infile.close();
	return true;
}

//Check whether there is a edge between two nodes or not
//return bool if there is edge, return true
bool mapping :: checkEdgeBetweenTwoNodes(int nodeFirst, int nodeSecond)
{
	if(nodeFirst==nodeSecond)
		return true;
	else
		return find(nodeVecMap[nodeFirst].begin(), nodeVecMap[nodeFirst].end(), nodeSecond)!=nodeVecMap[nodeFirst].end();
}
//Add edge to graph
//return bool
bool mapping :: addEdge(int nodeFirst, int nodeSecond)
{
	if(checkEdgeBetweenTwoNodes(nodeFirst,nodeSecond)){
            //cout<<nodeFirst<<" check "<<nodeSecond<<endl;
		return false;
	}
	else
	{
            /*if(nodeFirst == 3 || nodeSecond==3){
                cout<<"33333333333"<<endl;
            }*/
		edgeNum = edgeNum+1;
		nodeVecMap[nodeFirst].push_back(nodeSecond);
		nodeVecMap[nodeSecond].push_back(nodeFirst);
		nodeDegMap[nodeFirst]++;
		nodeDegMap[nodeSecond]++;
		vector<int> newEdge;
		newEdge.push_back(nodeFirst);
		newEdge.push_back(nodeSecond);
		for(int i=0;i!=labelNum;i++)
			newEdge.push_back(-100);
		edgeLabelMap[edgeLabelMap.size()] = newEdge;
		return true;
	}
	
}



bool mapping :: checkGraphDegree(int k)
{
	int num=0;
	map<int,int> record;
	for(map < int, int >::iterator iter=nodeDegMap.begin();iter!=nodeDegMap.end();iter++)
	{
		cout<<iter->first<<" ..... "<<iter->second<<endl;
		record[iter->second]++;
	}
	for(map < int, int >::iterator iter=record.begin();iter!=record.end();iter++)
	{
		
		cout<<iter->first<<" .. "<<iter->second<<endl;
		if(iter->second<k)
			return false;
	}
	return true;
}


///////////////////////////////////////////////////////////////////
//test
/*int main()
{
	mapping mapClass;
	mapClass.writeStr("../data/output_K4_2lab.txt");
	mapClass.writeNodeDegMap();
	mapClass.writeNodeVecMap();
	mapClass.writeEdgeLabelMap();
	
}*/
//end of test
///////////////////////////////////////////////////////////////////

