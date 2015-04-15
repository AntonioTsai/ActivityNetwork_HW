//
//  ActivityNetwork.h
//  ActivityNetwork
//
//  Created by Antonio Tsai on 2015/4/14.
//  Copyright (c) 2015年 Antonio. All rights reserved.
//

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    int dur;
    nodePointer link;
} node;
typedef struct {
    int count;
    nodePointer link;
} hdnodes;

void resetArray(hdnodes g[], int size);
void Insert(hdnodes graph[], int vertices);
void topSort(hdnodes graph[], int earliest[], int order[], int n);
void unreachable(int earliest[], int n);
void latestTime(hdnodes graph[], int latest[], int earliest[], int order[], int n);
void printHdnode(hdnodes g[], int size);
void printResult(hdnodes g[], int latest[], int earliest[], int order[], int n);
void traversalCritical(int critical[], hdnodes g[], int latest[], int earliest[], int times, int now, int end);