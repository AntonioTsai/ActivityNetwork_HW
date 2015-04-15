//
//  ActivityNetwork.c
//  ActivityNetwork
//
//  Created by Antonio Tsai on 2015/4/14.
//  Copyright (c) 2015年 Antonio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ActivityNetwork.h"

void resetArray(hdnodes g[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        g[i].count = 0;
        g[i].link = NULL;
    }
}

void Insert(hdnodes graph[], int vertices) {
    int i, v1, v2, d;
    nodePointer ptr, curPtr;
    
    for (i = 0; i < vertices; i++) {
        scanf("%d %d %d", &v1, &v2, &d);
        if (graph[v1].link == NULL) {
            ptr = malloc(sizeof(node));
            ptr->vertex = v2;
            ptr->dur = d;
            ptr->link = NULL;
            graph[v1].link = ptr;
        }
        else {
            curPtr = graph[v1].link;
            while (curPtr != NULL) {
                if (curPtr->link == NULL) {
                    ptr = malloc(sizeof(node));
                    ptr->vertex = v2;
                    ptr->dur = d;
                    ptr->link = NULL;
                    curPtr->link = ptr;
                    break;
                }
                curPtr = curPtr->link;
            }
        }
        graph[v2].count++;
    }
}

void topSort(hdnodes graph[], int earliest[], int order[], int n) {
    int i, j, k, top;
    nodePointer ptr = NULL;
    int counts[n];
    for (i = 0; i < n; i++) {
        counts[i] = graph[i].count;
    }
    /*create a stack of vertices with no predecessors*/
    top = -1;
    for (i = 0; i < n; i++) {
        if (!counts[i]) {
            counts[i] = top;
            top = i;
        }
    }
    for (i = 0; i < n; i++) {
        if (top == -1) {
            fprintf(stderr, "\nNetwork has a cycle. Sort terminated. \n");
            exit(EXIT_FAILURE);
        }
        else{
            order[i] = j = top;
            top = counts[top];
            //printf("v%d", j);
            for (ptr = graph[j].link; ptr; ptr = ptr->link) {
                /* decrease the count of the successor vertices of j */
                k = ptr->vertex;
                if (earliest[k] < earliest[j] + ptr->dur) {
                    earliest[k] = earliest[j] + ptr->dur;
                }
                counts[k]--;
                if (!counts[k]) {
                    /* add vertex k to the stack */
                    counts[k] = top;
                    top = k;
                }
            }
        }
    }
    
}

void unreachable(int earliest[], int n){
    int i;
    for(i = 1; i < n; i++){
        if(!earliest[i]){
            fprintf(stderr, "\nNetwork has Unreacheable. Terminated.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void latestTime(hdnodes graph[], int latest[], int earliest[], int order[], int n) {
    int i, tmp, nextCount;
    nodePointer ptr;
    for (i = n-1, tmp = 0; i >= 0; i--, tmp = 0) {
        for (nextCount = 0, ptr = graph[order[i]].link; ptr; ptr = ptr->link) {
            nextCount++;
        }
        //printf("(%d, %d) ", order[i], nextCount);
        if (!(n-i-1)) {
            latest[order[i]] = earliest[order[i]];
        }
        else {
            for (ptr = graph[order[i]].link; ptr; ptr = ptr->link) {
                tmp = latest[ptr->vertex] - ptr->dur;
                if (tmp < latest[order[i]]) {
                    latest[order[i]] = tmp;
                }
                nextCount--;
                if (!nextCount) {
                    break;
                }
            }
        }
    }
}

void printHdnode(hdnodes g[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (g[i].link == NULL) {
            printf("v%d is EMPTY count %d\n", i, g[i].count);
        }
        else {
            nodePointer ptr;
            printf("v%d count %d has ", i, g[i].count);
            for (ptr = g[i].link; ptr; ptr = ptr->link) {
                
                printf("v(%d, %d)  ", ptr->vertex, ptr->dur);
                
            }
            printf("\n");
        }
    }
}

void printResult(hdnodes g[], int latest[], int earliest[], int order[], int n) {
    int i, j, e;
    nodePointer ptr;
    printf("activity\te\tl\tl-e\tcritical\n");
    for (i = 0, j = 0, e = 0, ptr = g[i].link; i < n-1; j++) {
        if (ptr) {
            e = latest[ptr->vertex] - ptr->dur - earliest[i];
            printf("a%-3d\t\t%-4d\t%-4d\t%-4d\t%s\n", j, earliest[i], latest[ptr->vertex] - ptr->dur, e,
                   e ? "NO" : "YES");
            ptr = ptr->link;
        }
        else {
            i++;
            ptr = g[i].link;
        }
    }
}

void traversalCritical(int critical[], hdnodes g[], int latest[], int earliest[], int times, int now, int end) {
    int i, check;
    nodePointer ptr;
    if (now == end) {
        critical[times] = end;
        for (i = 0; critical[i] != -1; i++) {
            printf("%d ", critical[i]);
        }
        printf("\n");
    }
    else {
        
        for (ptr = g[now].link; ptr; ptr = ptr->link) {
            check = latest[ptr->vertex] - ptr->dur - earliest[now];
            if (!check) {
                critical[times] = now;
                traversalCritical(critical, g, latest, earliest, times+1, ptr->vertex, end);
            }
            
        
        }
    }
}




