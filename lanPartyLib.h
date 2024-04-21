#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct node {
    char* firstName;
    char* lastName;
    int points;
}TNode;

typedef struct team {
    char *teamName;
    int numberOfPlayers;
    float teamAverage;
    TNode *players;
    struct team* next;
}TTeam;

typedef struct queue {
    TTeam *front, *rear;
}TQueue;

typedef struct Tree {
    TTeam team;
    struct Tree *left, *right;
}TTree;


typedef struct AVLTree {
    int height;
    TTeam team;
    struct AVLTree *left, *right;
}TAVLTree;


int calculateCheckerId(char *fileName);

TTeam* createBlankList();
void printList(TTeam *h);


int findNumberOfTeams(FILE **f, char* filename);
int getNumberOfTeamMembers(FILE **f);
char* findTeamName(FILE **f);
TTeam* createTeam(FILE **f,int numberOfPlayers, char* teamName);
void printTeam(TTeam *x);
void addToListOfTeams(TTeam *d, TTeam *team);
void printTeamsNames(FILE **out, TTeam *h);
void InverseInorderPrint(FILE **out,TTree *root);
void printBestEightTeams(FILE **out,TTree *root);
void freeList(TTeam *head);
void freeTeam(TTeam* team);
void copyTeam(TTeam* dest, TTeam* org);

void printListNameAndAverage(TTeam* h);

TTeam* createFullTeams(FILE **f,char *input);

float calculateMinValue(TTeam* h);
int lowestPowerOfTwo(int x);
int max(int a , int b);

void eliminateTeamsToLowestMed(TTeam *d, int* numberOfTeams);

//queue
TQueue* createQueue();
int isEmptyQueue(TQueue *q);
void enQueue(TQueue* q, TTeam *x);
TTeam* deQueue(TQueue *q);
void addTeamToQueue(TQueue *q, TTeam *h);
void freeQueue(TQueue* q);

//bst
TTree* insert(TTree* node,TTeam *x);
void InversInorder(TTree *root);
TTree* newNode(TTeam *x);
void freeTree(TTree* root);

//avl
TAVLTree* avlInsert(TAVLTree *node, TTeam *x);
int nodeHeight(TAVLTree *root);
TAVLTree *rightRotation(TAVLTree *z);
TAVLTree *leftRotation(TAVLTree *z);
TAVLTree* LRRotation(TAVLTree *z);
TAVLTree* RLRotation(TAVLTree *z);
void AVLInorder(TAVLTree *root, FILE * out);
void printAVLonLevel(TAVLTree *root,int k);
void getFromBSTandInsertInAvl(TTree* bstRoot,TAVLTree** avlRoot);
void freeBSTNode(TTree* root);
void repairPostOrderAvl(TAVLTree* root, int *k);
void postOrderAvl(FILE **out,TAVLTree *root,int level);
void freeAVLTree(TAVLTree *root);

void printTeamsOnLevel(FILE **out, TAVLTree* root, int level);
void postOrderAvl(FILE **out, TAVLTree* root,int );

void insertTeamsOnQueue(TQueue *q, TTeam *h);

//stack
void push (TTeam **top, TTeam* x);
int isEmptyStack(TTeam *top);
TTeam* pop(TTeam **top);
void deleteStack(TTeam **top);
void freeStack(TTeam** stackTop);
void freeNode(TNode *player);
int sizeOfStack(TTeam* stackTop);

TTeam* fightToWinner(TTeam* t1, TTeam *t2);
TTeam* fightToLooser(TTeam* t1, TTeam *t2);
void printAllTeamsOnRoundAndFillStacks(FILE **out,TQueue* q, int *numberOfTeams,TTeam **winStackTop,TTeam **looseStackTop);

void insertTeamsOnQueue(TQueue *q, TTeam *h);
void printRounds(FILE **out, TQueue *q, int numberOfTeams, int, TTeam**);

double log2(double);