#include "../include/heuristic.h"
#include <cstdlib>
#include <sys/time.h>
#include <ctime>

int num;
int numWhile;
int loop;
int k;
int method;
unsigned int seed;

//write vector into file
//Function writeVecIntoFile
//return bool
bool heuristic :: writeVecIntoFile(mapping myGraph, string outLoc)
{
	ofstream outfile;
	int overWrite = 0;
	if(overWrite == 0)
		outfile.open(outLoc.c_str());
	else if(overWrite == 1)
		outfile.open(outLoc.c_str(), ofstream::app);
	else 
		return false;
	outfile<<myGraph.nodeNum<<endl;
	outfile<<myGraph.edgeNum<<endl;
	outfile<<myGraph.labelNum<<endl;
	map < int, vector< int > > tempMap = myGraph.getEdgeLabelMap();
	for(map < int, vector< int > > :: iterator iter=tempMap.begin(); iter!=tempMap.end();iter++)
	{
		outfile<<*iter->second.begin();
		for(vector<int>::iterator iterVec=iter->second.begin()+1;iterVec!=iter->second.end();++iterVec)
		{
			outfile<<"	"<<*iterVec;
		}
		outfile<<endl;
	}
	
	outfile.close();
	return true;
}


//Function HeuristicAvailable
//checked whether a node can be anonymize from a vector or not
//return: if node has edges to all the node in vector, return false else return true
bool heuristic :: anonymizeAvailable(int nodeID, vector<sort_map>& readyVec, int star,int primary,mapping& myGraph)
{
	for(vector<sort_map> :: iterator iter=readyVec.begin()+star; iter != readyVec.end();++iter)
	{
		if(iter->checked==false&&!myGraph.checkEdgeBetweenTwoNodes(nodeID,iter->key)&&iter->val<primary)
		{
			return true;
		}
	}
	return false;
}
//Function HeuristicAvailable
//checked whether a node can be anonymize from a vector or not
//return: if node has edges to all the node in vector, return false else return true
bool heuristic :: anonymizeAvailable(int nodeID, vector<sort_map>& readyVec, mapping& myGraph)
{
	for(vector<sort_map> :: iterator iter=readyVec.begin(); iter != readyVec.end();++iter)
	{
		if(!myGraph.checkEdgeBetweenTwoNodes(nodeID,iter->key))
			return true;
	}
	return false;
}



//Function achieve_k_anonymity
//Input: graph class, int k
//Output a graph with degree anonymized
bool heuristic :: achieve_k_anonymity(mapping& graph,int& k,int method)
{
	vector<sort_map> vectexListSorted = sortVectexBasedOnDegree(graph.getNodeDegMap());
	vector<sort_map> unAnonymityList;
	for(vector<sort_map> :: iterator iter=vectexListSorted.begin(); iter <vectexListSorted.end();++iter)
	{
		iter->point = iter;
		sort_map *newsm = iter->copy();
		unAnonymityList.push_back(*newsm);
		//unAnonymityList.push_back(*iter);
	}
	int group = 0;
	int stop = 0;
	vector<sort_map> candiateSet;
	vector<sort_map> readyVec = unAnonymityList;
	//cout << "a1" << endl;
	while(!unAnonymityList.empty())
	{
		numWhile++;
		group++;
		sort_map* seedVectexPoint = &unAnonymityList.front();
		
		//cout<<seedVectexPoint->key<<" "<<seedVectexPoint->val<<endl;
		sort_map seedVectex = unAnonymityList.front();
		seedVectex.point = unAnonymityList.begin()->point;
		seedVectex.group=group;
		seedVectexPoint->group = group;
		seedVectexPoint->point->group = group;
		seedVectex.checked=true;
		seedVectexPoint->checked = true;
		seedVectexPoint->point->checked = true;
		unAnonymityList.erase(unAnonymityList.begin());
		if(unAnonymityList.size() > 2*k-1)
		{
			stop = k-1;
		}
		else
		{
			stop = unAnonymityList.size();
		}
		int candiateSize;
		for(int i=0;i<stop;i++)		
		{
			//cout<< "i="<<i<< endl;
			bool againBool = false;
			vector<sort_map> :: iterator iter=unAnonymityList.begin();
			candiateSize = unAnonymityList.size();
		//cout<< "numWhile="<<numWhile <<",group="<<group<<" size "<<candiateSize<< endl;
			int loop = seedVectex.val-iter->val;
			if(loop==0)
			{
				iter->group=group;
				iter->point->group=group;
				iter->checked=true;
				iter->point->checked=true;
			}
			else
			{
				for(int timeNum=0;timeNum<loop;timeNum++)
				{	
					bool checked = false;
					int random_integer = rand()%(candiateSize);
					vector<sort_map> :: iterator iterUse=unAnonymityList.begin()+random_integer;
					if(anonymizeAvailable(iter->key,unAnonymityList,0,seedVectex.val,graph))
					{
						while(iterUse->checked==true||!graph.addEdge(iter->key,iterUse->key))
						{
							random_integer = rand()%(candiateSize);
							iterUse=unAnonymityList.begin()+random_integer;
						}
					
					}
					else
					{
						num++;
						candiateSize = vectexListSorted.size();
						while(!graph.addEdge(iter->key,iterUse->key))
						{
							random_integer = rand()%(candiateSize);
							iterUse=vectexListSorted.begin()+random_integer;
						}
					}
					iter->val++;
					iter->point->val++;
					if(iterUse!=iterUse->point)
						iterUse->point->val++;
					iterUse->val++;
				
				
					iter->checked = true;
					iter->group = group;
					iter->point->checked = true;
					iter->point->group = group;
					if(iterUse->group!=0)
					{
						switch(method)
						{
						case 1: //please add comment, continue, anonymize 
						if(iterUse->group == iter->group)
						{
							//cout << "case 1 if" << endl;
							int temp = iterUse->group;
							unAnonymityList.clear();
							for(vector<sort_map> :: iterator iterTemp=vectexListSorted.begin(); iterTemp != vectexListSorted.end();++iterTemp)
							{
								if(iterTemp->group == temp||iterTemp->group==0)
								{
									iter->sort = false;
									iter->checked = false;
									iterTemp->group=0;
									sort_map *newsm = iterTemp->copy();
									//cout<<"copied"<< endl;
                                                                        unAnonymityList.push_back(*newsm);
									//unAnonymityList.push_back(*iterTemp);
								}
							}
							unAnonymityList = sortVectexBasedOnDegree(unAnonymityList);
							i=stop;
							againBool = true;
							group--;
						}
						else
						{
							//cout << "case 1 else" << endl;
							int temp = iterUse->group;
							for(vector<sort_map> :: iterator iterTemp=vectexListSorted.begin(); iterTemp != vectexListSorted.end();++iterTemp)
							{
								if(iterTemp->group == temp)
								{
									if(iterTemp==iterUse)
										iterTemp->checked=true;
									else
										iterTemp->checked=false;
									iterTemp->sort=true;
									iterTemp->group=0;
									sort_map *newsm = iterTemp->copy();
									//cout<<"copied [2]"<< endl;
                                                                        unAnonymityList.push_back(*newsm);
									//unAnonymityList.push_back(*iterTemp);
								}
							}
						}
						break;
						case 2: //please add comment: break and go to anonymize the group again
							int temp = iter->group;
							int tempUse = iterUse->group;
							unAnonymityList.clear();
							//cout << "case 2" << endl;
							for(vector<sort_map> :: iterator iterTemp=vectexListSorted.begin(); iterTemp != vectexListSorted.end();++iterTemp)
							{
								if(iterTemp->group == temp||iterTemp->group==tempUse||iterTemp->group==0)
								{
									iterTemp->checked = false;
									iterTemp->sort = false;
									iterTemp->group=0;
									sort_map *newsm = iterTemp->copy();
									//cout<<"copied[3]"<< endl;
                							unAnonymityList.push_back(*newsm);
									//unAnonymityList.push_back(*iterTemp);
								}
							}
							unAnonymityList = sortVectexBasedOnDegree(unAnonymityList);
							i=stop;
							againBool = true;
							break;
						}
					}
				}//end of for with loop
			}//end of else
			//cout << "a2" << endl;
			if(againBool==false)
			{	
				//cout << "again bool = false" << endl;
				unAnonymityList.erase(iter);
				seedVectex.point->checked=true;
				seedVectex.point->point->checked=true;
			}
			unAnonymityList = sortVectexBasedOnDegree(unAnonymityList);
		}//end for with stop
		//cout << "a3" << endl;
		for(vector<sort_map> :: iterator iterTemp=unAnonymityList.begin(); iterTemp != unAnonymityList.end();++iterTemp)
		{
			iterTemp->sort=false;
			iterTemp->checked=false;
		}
		//cout << "a4" << endl;
		unAnonymityList = sortVectexBasedOnDegree(unAnonymityList);
		//cout << "a5" << endl;
	}
	return true;
}

bool heuristic :: writeLogFile(map<string,string> logMap,string logLoc)
{
	ofstream outfile;
	//int overWrite = 0;
	//if(overWrite == 0)
	//	outfile.open(logLoc.c_str());
	//else if(overWrite == 1)
		outfile.open(logLoc.c_str(), ofstream::app);
	//else 
	//	return false;
	
	outfile<<"loop:"<<loop<<"	num:"<<num<<"	k:"<<k<<"	while:"<<numWhile<<"	method:"<<method<<endl;
	outfile<<"#Node_Number	Original_Edge_Number	New_Edge_Number	EdgeAdded	Time"<<endl;
	outfile<<logMap["nodeNum"]<<"	"<<logMap["originalEdgeNum"]<<"	"<<logMap["newEdgeNum"]<<"	"<<logMap["addEdge"]<<"	"<<logMap["time"]<<endl;
	outfile.close();
	return true;
}

int main(int argc, char *argv[])
{
	num=0;
	numWhile=0;
	loop=0;
	k=0;
        //cout << "[0]" << endl;
	struct timeval nowTime;
  	gettimeofday(&nowTime,NULL);
  	long long total_start = nowTime.tv_sec * 1000000 + nowTime.tv_usec;

	clock_t t1,t2;
        //cout << "[0.1]" << endl;
	/*if(argc!=5)
	{
		cout<<"please input two parameters <1> graph file location <2> number of k <3> method <4> seed value"<<endl;
		return 0;
	}*/
	if(argc!=4)
	{
		cout<<"please input two parameters <1> graph file location <2> number of k <3> method <4>seed"<<endl;
		return 0;
	}
	/*if(argc!=4)
	{
		cout<<"please input two parameters <1> graph file location <2> number of k <3> method"<<endl;
		return 0;
	}*/
	//cout << "[1]" << endl;
    	//code goes here
	string graphLoc = argv[1];
	k = (int)strtoul(argv[2], 0, 0);
	method = (int)strtoul(argv[3], 0, 0);
	//seed = (int)strtoul(argv[4], 0, 0);
	//srand(seed);
	mapping mapClass;
	mapClass.writeStr(graphLoc);
	mapClass.writeNodeDegMap();
	mapClass.writeNodeVecMap();
	mapClass.writeEdgeLabelMap();
	map<string, string> logMap;
	stringstream ss;//create a stringstream
	int edgeNum1 = mapClass.edgeNum;
	ss<<mapClass.nodeNum;
	logMap["nodeNum"]=ss.str();
	ss.str("");	
	ss<<edgeNum1;
        //cout << "[2]" << endl;
	logMap["originalEdgeNum"]=ss.str();
	ss.str("");
    	t1=clock();
	heuristic heurClass;
	//cout << "[2.1]" << endl;
	heurClass.achieve_k_anonymity(mapClass,k,method);
	//cout << "[3]" << endl;
	ss<<k;
	stringstream ssMethod;
	ssMethod<<method;
	string output = graphLoc+"_k="+ss.str()+"_output_M"+ssMethod.str()+".txt";
	string logfile = graphLoc+"_log.txt";	
	//string logfile = graphLoc+"_k="+ss.str()+"_log_M"+ssMethod.str()+".txt";
	//string output = "data/data11.03/enrons1_LabelGraph2lab.txt_k="+ss.str()+"_output_M"+ssMethod.str()+".txt";
	//string logfile = "data/data11.03/enrons1_LabelGraph2lab.txt_k="+ss.str()+"_log_M"+ssMethod.str()+".txt";
	ss.str("");
	heurClass.writeVecIntoFile(mapClass,output);
	gettimeofday(&nowTime,NULL);
	int edgeNum2 = mapClass.edgeNum;
	ss<<edgeNum2;
	logMap["newEdgeNum"]=ss.str();
	ss.str("");
	edgeNum2=edgeNum2-edgeNum1;
	ss<<edgeNum2;
	//cout << "[4]" << endl;
	logMap["addEdge"]=ss.str();
	ss.str("");	
    	long long total_end = nowTime.tv_sec * 1000000 + nowTime.tv_usec;
  	long long total_time_us = total_end - total_start;
	ss<<total_time_us/1000;
 	ss<<".";
	ss<<total_time_us%1000;
	logMap["time"] = ss.str();
        //cout << "[5]" << endl;
	heurClass.writeLogFile(logMap,logfile);
  	cout<<"Total time taken by degree anonymous : "<<total_time_us/1000<<" ms "<<total_time_us%1000<<" us"<<endl;	
	if(mapClass.checkGraphDegree(k))
		cout<<"DONE"<<endl;
	else
		cout<<"NOT DONE"<<endl;
	return 0;
}
