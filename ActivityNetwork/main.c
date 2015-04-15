//
//  main.c
//  ActivityNetwork
//
//  Created by Antonio Tsai on 2015/4/13.
//  Copyright (c) 2015年 Antonio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ActivityNetwork.h"

int main(int argc, const char * argv[]) {
    int vertices, edge;
    int i;
    
    scanf("%d %d", &vertices, &edge);
    hdnodes graph[edge];
    int earliest[vertices];
    int latest[vertices];
    int order[vertices];
    int critical[vertices];
    
    resetArray(graph, vertices);
    for (i = 0; i < vertices; i++) {
        earliest[i] = 0;
        order[i] = 0;
        latest[i] = 10000000;
        critical[i] = -1;
    }
    //printHdnode(graph, vertices); //check
    Insert(graph, edge);
    //printHdnode(graph, vertices); //check
    topSort(graph, earliest, order, vertices);
    unreachable(earliest, vertices);
    latestTime(graph, latest, earliest, order, vertices);
    printResult(graph, latest, earliest, order, edge);
    traversalCritical(critical, graph, latest, earliest, 0, order[0], order[vertices-1]);
        return 0;
}
