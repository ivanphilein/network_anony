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
             //if(iter->checked==false&&!myGraph.checkEdgeBetweenTwoNodes(nodeID,iter->key) && iter->val<primary)
		if(iter->checked==false&&!myGraph.checkEdgeBetweenTwoNodes(nodeID,iter->key))
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


int getGroupIDAndRemove(int key, int group,map<int, vector< sort_map > > groupMap, mapping& graph){
    while(group>0){
        group--;
        vector<sort_map> tempMap = groupMap.find(group)->second;
        for(vector< sort_map > ::iterator itermap = tempMap.begin(); itermap!=tempMap.end();itermap++){
            if(!graph.addEdge(key,itermap->key)){
                cout<<"add edge "<<itermap->key<<" "<<key<<endl;
                itermap->val++;
                return group;
            }
        }
    }
    return -1;
}

void exchangeIter(vector<sort_map> :: iterator first, vector<sort_map> :: iterator second){
    vector<sort_map> :: iterator temp;
    temp->checked = first->checked;
    temp->group = first->group;
    temp->key = first->key;
    temp->val = temp->val;
    
    first->checked = second->checked;
    first->group = second->group;
    first->key = second->key;
    first->val = second->val;
    
    second->checked = temp->checked;
    second->group = temp->group;
    second->key = temp->key;
    second->val = temp->val;
    
}

void showMap(map<int, vector< sort_map > > groupMap){
    cout<<"start==============================="<<endl;
    for(map<int, vector< sort_map > > :: iterator iter=groupMap.begin(); iter!=groupMap.end();++iter)
    {
        cout<<iter->first<<endl;
        for(vector< sort_map > ::iterator itermap = iter->second.begin(); itermap!=iter->second.end();itermap++){
            sort_map tempVectex = *itermap;
            cout<<tempVectex.key<<" "<<tempVectex.val<<" "<<tempVectex.group<<endl;
        }
    }
    cout<<"end==============================="<<endl;
}

//Function achieve_k_anonymity
//Input: graph class, int k
//Output a graph with degree anonymized
bool heuristic :: achieve_k_anonymity(mapping& graph,int& k,int method)
{cout<<"start"<<endl;
    map<int, vector< sort_map> > groupMap;
	vector<sort_map> vectexListSorted = sortVectexBasedOnDegree(graph.getNodeDegMap());
	vector<sort_map> unAnonymityList;
	for(vector<sort_map> :: iterator iter=vectexListSorted.begin(); iter <vectexListSorted.end();++iter)
	{
		//iter->point = new sort_map;
                //iter->point = iter;
		sort_map *newsm = iter->copy();
		//unAnonymityList.push_back(*newsm);
//cout<<"!!!!!!!!!!!!!!!! "<<newsm->key<<" "<<newsm->val<<endl;
		unAnonymityList.push_back(*iter);
	}
	int group = 0;
	int stop = 0;
	//vector<sort_map> candiateSet;
	//vector<sort_map> readyVec = unAnonymityList;

	
        vector<sort_map> :: iterator iterbegin = unAnonymityList.begin();

	while(!unAnonymityList.empty())
	{
                iterbegin = unAnonymityList.begin();
		numWhile++;
		group++;
		//if(group ==6)
		//	break;
		sort_map seedVectex = *iterbegin;
		seedVectex.group = group;
                map<int, vector< sort_map> >::iterator itermap = groupMap.find(group);
                if(itermap == groupMap.end()){
                    vector< sort_map > tempMap;
                    groupMap.insert(pair<int, vector<sort_map> > ( group, tempMap ));
                    itermap = groupMap.find(group);
                }
                itermap->second.push_back(seedVectex);
                //itervector->push_back(&seedVectex);
                //showMap(groupMap);
		//seedVectex.point->group = group;
                seedVectex.checked = true;;
		//seedVectex.point->checked = true;
//cout<<seedVectex.key<<endl;
//cout<<"begin %%%%%%%%%%%% "<<iterbegin->key<<" "<<iterbegin->val<<endl;
		unAnonymityList.erase(iterbegin);
//cout<<seedVectex.key<<endl;
		if(unAnonymityList.size() > 2*k-1)
		{
			stop = k-1;
		}
		else
		{
			stop = unAnonymityList.size();
		}
		int candiateSize = unAnonymityList.size();
                if(candiateSize%1000==0){//Huiping Cao added the if condition
	                cout<<"stop and k-1= "<<stop <<" unanonymized_node_num= "<< unAnonymityList.size()<<endl;
		}
                vector<sort_map> :: iterator iterfrom;// = unAnonymityList.begin();
                
                bool done = true;
		for(int i=0;i<stop;i++)		
		{
                    iterfrom = unAnonymityList.begin();
			//cout<< "i="<<i<< endl;
			//bool againBool = false;
			//iterfrom = unAnonymityList.begin();;
			//vector<sort_map> :: iterator iter=unAnonymityList.begin();
			int loop = seedVectex.val-iterfrom->val;
		//cout<< "numWhile="<<numWhile <<",group="<<group<<" size "<<candiateSize<<" "<<loop<< endl;
			
                        if(loop==0)
			{
				iterfrom->group=group;
                                groupMap.find(group)->second.push_back(*iterfrom->copy());
				iterfrom->checked=true;
                                iterfrom++;
                                unAnonymityList.erase(iterfrom-1);
                                
			}
			else
			{
				for(int timeNum=0;timeNum<loop;timeNum++)
				{	
					//bool checked = false;
					int random_integer = rand()%(candiateSize);
					vector<sort_map> :: iterator iterUse=iterfrom+random_integer;
					if(anonymizeAvailable(iterfrom->key,unAnonymityList,0,seedVectex.val,graph))
					{
						while(iterUse->checked==true||!graph.addEdge(iterfrom->key,iterUse->key))
						{

							random_integer = rand()%(candiateSize);
							iterUse=unAnonymityList.begin()+random_integer;
						}
						
						iterfrom->val++;
						iterUse->val++;
					
						/*if(iterUse->group!=0 && nextIter->val<iterUse->val)
						{
							exchangeIter(nextIter ,iterUse);
						}*/
					}
					else
					{
						num++;
                                                int remGroup = getGroupIDAndRemove(iterfrom->key, group, groupMap, graph);
                                                iterfrom->val++;
                                                cout<<" go back to AnonymityList: "<<remGroup<<" and "<<group<<" is re-insert to un-anonymityList"<<endl;
                                                if(remGroup!=-1){
							int temp = remGroup;
                                                        vector<sort_map> tempVector = groupMap.find(temp)->second;
                                                        while(tempVector.size()!=0)
                                                        {
                                                                sort_map * tempsort = &tempVector.back();
                                                                tempsort->sort = false;
								tempsort->checked = false;
								tempsort->group=0;
								unAnonymityList.push_back(*(tempsort));
                                                                tempVector.pop_back();
							}
                                                        groupMap.erase(temp);
                                                        tempVector = groupMap.find(group)->second;
                                                        while(tempVector.size()!=0)
                                                        {
                                                                sort_map * tempsort = &tempVector.back();
                                                                tempsort->sort = false;
								tempsort->checked = false;
								tempsort->group=0;
								unAnonymityList.push_back(*(tempsort));
                                                                tempVector.pop_back();
							}
                                                        groupMap.erase(group);
                                                        group--;
                                                        timeNum=stop;
                                                        done = false;
                                                        break;
						}
                                                else{
                                                    cout<<"error"<<endl;
                                                    exit(0);
                                                }
					}
				}//end of for with loop
				if(done==true){
                                    iterfrom->checked = true;
                                    iterfrom->group = group;
                                    groupMap.find(group)->second.push_back(*iterfrom->copy());
                                }
                                
                                if(done==true){               
                                    unAnonymityList.erase(iterfrom);
                                }
                                unAnonymityList = sortVectexBasedOnDegree(unAnonymityList);
			}//end of else
		}//end for with stop
                
                //showMap(groupMap);
                iterbegin = iterfrom;
                iterfrom++;
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
	cout << "Read graph file: " << graphLoc << endl;
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
	/*if(mapClass.checkGraphDegree(k))
		cout<<"DONE"<<endl;
	else
		cout<<"NOT DONE"<<endl;*/
	return 0;
}
