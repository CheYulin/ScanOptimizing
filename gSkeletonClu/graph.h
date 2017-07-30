#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include "windows.h"
#include "time.h"
#include "fibheap.h"

using namespace std;

class Node;
class Graph;
class Cluster;

bool compare(long,vector<Node*> &);

class Edge
{          //ÿ���߶�Ӧһ��Edge����
     public:
         Edge( long src,  long dest, double w);
         long getSrc() ;
         long  getDest()  ;
         float getWeight() ;
         void setSim(float f);
         float getSim();
         float CCS;                  //����ͨ���ƶ�
         float CS;                  //�ṹ���ƶ�
         float weight;             // ��Ȩ
         long n1,n2;
};

class cmp
{
    public:
        bool operator()(  Edge*  n1,  Edge* n2)
        {
            return n1->CCS < n2->CCS;
        }
 };
class cmp1
{
         public:
        bool operator()(  Edge*  n1,  Edge* n2)
        {
            return n1->CS < n2->CS;
        }
};
class Node
{
    public:
        Node(long no);
        Node();
        long getSn();
        void mapIns(long n,Edge *r);       //�����ڵ���ڽӽڵ���ߵ�ӳ��
        map <long, float> distance;        //floyd�㷨�����������
        void adjNodesIns(long n);          //�����ڵ��ڽӱ������в���Ԫ��
        set <long> adjNodes;               //������������ڵ����ƶ��Լ���������ϲ�ʱ�Ĳ�������
        map <long, Edge *> adjEdges;       //�ڽӽڵ�ţ��ڽӱ�
        Cluster* link;                     //ָ�򱾽ڵ����ڵľ���
    private:
        long sn;   //ԭʼ�ڵ��
};

class Graph
{
    friend class network_info;
    public:
        bool type;
        float TS;
        void DSSim();
        list <Cluster*> alonelist;                  //�洢����ʱ�Ĺ����ڵ� �����ž�������𲽼���
        list <Cluster*> resultlist;               //�洢���࣬���ž�����̲�������
        float mergeQs(vector<Edge*> &etemp,float Qs,float &cQs,
                     vector<long> &result,float &epsilon,int mu,FibHeap &hp,float &time1,float &time2);    //����ϲ��ڶ��׶�
        void mergeQs(vector<Edge*> &etemp,float &cQs,int mu,long &k,FibHeap &hp,float &time1);                     //����ϲ���һ�׶�
        vector <Node *> nodeIndex;               //ͼ�ڵ��������ʴ洢�ṹ����vectorӳ�䵽ÿ���ڵ����
        vector <long> dependNode;
        Graph (char* f);
        long verNum();                           //����ͼ�нڵ���Ŀ
        long edgeNum();                          //����ͼ�б���Ŀ
        Graph();
        bool readGraph();                        //���ļ��ж���ͼ
        void print();                            //��������ͼ��Ϣ
        void coreSim(int,FibHeap&);                       //��������ƶȡ�����ͨ���ƶ�
        Edge* returnEdge(long n1, long n2);      //������n1��n2Ϊʼ���սڵ�ı�
        void JaccardSim();                       //���ƶȼ��㣬����Q���и���ֵ
        void CosSim();                           //���ƶȼ��㣬����Q���и���ֵ
        void MinSim();
        list <Edge *> edgelist;                  //�ߵ�˳����ʴ洢�ṹ����˫��������ָ�봮����������Աߵ����ƶȼ����ɾ��
    private:
        char* filename;                            //ͼ�ļ���

};

class Cluster
{
     public:
         Cluster(long sn);
         Cluster();
         set<long> nodeSet;                       //�洢�������еĽڵ���
         float IS,DS;
         float Qs;                              //�洢�������Qsֵ�����о���Qs���Ϊ�ܵ�Qsֵ
};
