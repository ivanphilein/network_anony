/include contains head files
/src contains source files
/input: input files
/output: output files

There are three parameters of main function, first one is the location of graph file(example: "../input/nRawGraph.txt"REQUEST); second one is the location of queries file(example: "../input/queries.txt"REQUEST); third one is the output file(example: "../output/output.txt" OPTIMAL, DEFAULT:"../output/output.txt")

In the input files, at now, format of queries.txt file:
two integers at the first row: first is type of result, -1 means intersection of all labels, 1 means union of all labels.
second is whether over write the output.txt or not: 0 means no over write; 1 means need to over write. 


output files example:

Edge:144 Labels:7 10 pa:0.00166667

144 is the edge ID, 7 and 10 are the labels, 0.00166667 is the probability
