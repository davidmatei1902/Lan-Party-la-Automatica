#include "lanPartyLib.h"

//apelata o singura data, gaseste cate echipe se afla in fisierul d.in
int findNumberOfTeams(FILE **f, char* filename)
{
    int numberOfTeams;
    *f=fopen(filename,"r");
    if(*f==NULL)
    {
        printf("error opening file :/");
        return 0;
    }
    fscanf(*f,"%d",&numberOfTeams);
    return numberOfTeams;
}

//presupunem ca in main deja am trecut de findNumberOfTeams
//f-ul e deja deschis, de acum citim doar nume, de forma
////////////////////////////////////////////////////////
//Popa Ana-Maria 6
//Popescu Alexandru 10
//Pop Mihaela 6
//Radu Andreea 2
//...
/////////////////////////////////////////////////
// trimit cati oameni sunt in echipa si numele echipei
TTeam* createTeam(FILE **f,int numberOfPlayers, char* teamName)
{
    //alocam spatiu pentru intreaga echipa
    TTeam* newTeam = (TTeam*) malloc(sizeof(TTeam));
    newTeam->next=NULL;
    newTeam->numberOfPlayers=numberOfPlayers;
    

    newTeam->teamName = (char*) malloc((strlen(teamName)+1)*sizeof(char));
    strcpy(newTeam->teamName,teamName);

    //alocam spatiu pentru toti jucatorii din cadrul echipei
    newTeam->players = (TNode*) malloc(numberOfPlayers * sizeof(TNode));

    char firstNameBuffer[100],lastNameBuffer[100];
    int i,points;

    float sum = 0;
    for(i=0; i < numberOfPlayers ; i++)
    {
        fscanf(*f,"%s",firstNameBuffer);
        fscanf(*f,"%s",lastNameBuffer);
        fscanf(*f,"%d",&points);

        newTeam->players[i].firstName = (char*) malloc((strlen(firstNameBuffer) + 1) *sizeof(char));
        strcpy(newTeam->players[i].firstName,firstNameBuffer);
        newTeam->players[i].lastName = (char*) malloc((strlen(lastNameBuffer) + 1) * sizeof(char));
        strcpy(newTeam->players[i].lastName,lastNameBuffer);

        sum+=points;
        newTeam->players[i].points = points;
    }

    newTeam->teamAverage = (float) sum/numberOfPlayers;
    return newTeam;
}

TTeam* createBlankList()
{
    TTeam* newNode = (TTeam*) malloc(sizeof(TTeam));
    if(newNode==NULL)
    {
        printf("\nerror allocating team");
        return NULL;
    }
    newNode->next=NULL;
    return newNode;
}

void printList(TTeam *h)
{
    if(h==NULL)
    {
        printf("\nerror, blank head");
        return;
    }

    printf("\nEchipele sunt:\n");
    while(h!=NULL)
    {
        printf("Numele echipei %s cu media %.2f\n",h->teamName,h->teamAverage);
        h=h->next;
    }
}

void addToListOfTeams(TTeam *d, TTeam *team)
{
    team->next = d->next;
    d->next=team;
}

//gasim cati membri are o echipa
int getNumberOfTeamMembers(FILE **f)
{
    int numberOfTeamMembers;
    fscanf(*f,"%d",&numberOfTeamMembers);
    return numberOfTeamMembers;
}

//deja e deschis
char* findTeamName(FILE **f)
{
    //200 predefinit
    char *buffer = (char*) malloc(100 * sizeof(char));
    if(buffer==NULL)
    {
        printf("\nerror allocating mem for team");
        return NULL;
    }
    fgetc(*f); //primul caracter, spatiu
    fgets(buffer,100,*f);
    return buffer;
}

// void openFileForRead(FILE **f, char* name)
void printTeam(TTeam *x)
{
    if(x==NULL)
    {
        printf("\nerror printing team, null head");
        return;
    }

    printf("\nEchipa din primul nod este formata din %d jucatori, cu numele %s si media de echipa %.2f astfel:\n",x->numberOfPlayers,x->teamName,x->teamAverage);
    for(int i=0; i<(x->numberOfPlayers); i++)
    {
        printf("%s %s %d\n",x->players[i].firstName,x->players[i].lastName,x->players[i].points);
    }
}

void printListNameAndAverage(TTeam* h)
{
    if(h==NULL)
    {
        printf("\nerror, list null");
        return ;
    }
    while(h!=NULL)
    {
        printf("Nume echipa: %s \n punctaj mediu:%.2f\n\n",h->teamName,h->teamAverage);
        h=h->next;
    }
}

void printTeamsNames(FILE **out, TTeam *h)
{
    if(h==NULL)
    {
        printf("\nerror, teams null");
        return;
    }
    while(h!=NULL)
    {
        fprintf(*out,"%s\n",h->teamName);
        h=h->next;
    }
}

// calculeaza ce cerinte sa faca testul respectiv, reprezentat printr un id
int calculateCheckerId(char *fileName)
{
    int number,s=0;
    FILE *f=fopen(fileName,"r");
    while(!feof(f))
    {
        fscanf(f,"%d",&number);
        s+=number;
    }
    return s;
}

float calculateMinValue(TTeam* h)
{
    float min = 1000000.0;
    if(h==NULL)
    {
        printf("\nerror calculating min value");
        return 0;
    }
    while(h!=NULL)
    {
        if((h->teamAverage)<min)
        {
            min=(h->teamAverage);
        }
        h=h->next;
    }
    return min;
}

int max(int a , int b)
{
    if(a>=b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
int sizeOfStack(TTeam* stackTop)
{
    int counter=0;
    if(stackTop==NULL)
    {
        printf("\nerror printing size of stack, null head");
        return 0;
    }
    while(stackTop)
    {
        counter++;
        stackTop=stackTop->next;
    }
    return counter;
}

int lowestPowerOfTwo(int x)
{
    int n=1;
    int ant;
    while(n<x)
    {
        ant=n;
        n*=2;
    }
    if(n>x)
    {
        n=ant;
    }
    return n;
}

void eliminateTeamsToLowestMed(TTeam *d, int* numberOfTeams)
{
    if(d->next==NULL)
    {
        printf("\nerror, first elem null");
        return ;
    }
    int lowestPowerOftwo = lowestPowerOfTwo(*numberOfTeams);
 
    // d->next primul element efectiv
    //cat timp nr de echipe a ramas mai mare sau egal decat cel mai mic nr, maxim, putere de a lui 2
    while((*numberOfTeams)>lowestPowerOftwo)
    {
        float min = calculateMinValue(d->next);

        TTeam *prev=d;
        TTeam *iter=d->next;

        //min not found
        int ok=0;

        while(iter!=NULL)
       {
            if(iter->teamAverage==min)
            {
                // la final de if, prev->next arata la urmatorul element dupa minim
                // prev ramane pe pozitia dinainte de minim
                ok=1;
                TTeam *tmp = iter;
                prev->next = iter->next;
                iter=iter->next;
                freeTeam(tmp);
                break;
            }
            
            //daca min nu a fost gasit
            if(ok==0)
            {
                // parcurgem lista in mod normal;
                prev=prev->next;
                iter=iter->next;
            }
       }
        (*numberOfTeams)--;
    }
    return;
}

//functie care creste valoarea unui float cu unu
void increaseFloatValueByOne(float *value)
{
    (*value) += 1;
}

//NU UITA
//trimite in functie elemente consecutive, adica deQueue(q) si deQueue(q) , in ordinea asta
//functia intoarce castigatorul dintre t1 si t2
//aparent daca sunt egale, trebuie intors al 2 lea bagat in coada de mai nainte
TTeam* fightToWinner(TTeam* t1, TTeam *t2)
{
    if(t1==NULL || t2==NULL)
    {
        printf("\nerror, one of team is null");
        return NULL;
    }

    if((t1->teamAverage)==(t2->teamAverage))
    {
        increaseFloatValueByOne(&(t2->teamAverage));
        return t2;
    }
    else
    {
        if((t1->teamAverage) > (t2->teamAverage))
        {
            increaseFloatValueByOne(&(t1->teamAverage));
            return t1;
        }
        if((t1->teamAverage) < (t2->teamAverage))
        {
            increaseFloatValueByOne(&(t2->teamAverage));
            return t2;
        }
    }
    return NULL;
}

//trimite in functie elemente consecutive, adica deQueue(q) si deQueue(q) , in ordinea asta
TTeam* fightToLooser(TTeam* t1, TTeam *t2)
{
    if(t1==NULL || t2==NULL)
    {
        printf("\nerror, one of team is null");
        return NULL;
    }

    if((t1->teamAverage)==(t2->teamAverage))
    {
        return t1;
    }
    else
    {
        if((t1->teamAverage) > (t2->teamAverage))
        {
            return t2;
        }
        if((t1->teamAverage) < (t2->teamAverage))
        {
            return t1;
        }
    }
    return NULL;
}


// h e prima echipa din lista
// q e coada
void insertTeamsOnQueue(TQueue *q, TTeam *h)
{
    TTeam* aux;
    if(q == NULL || h == NULL)
    {
        printf("\nerror, invalid args");
        return;
    }
    while(h!=NULL)
    {
        aux = h;
        enQueue(q,h);
        h=h->next;
        //freeTeam(aux);
    }
}

void printAllTeamsOnRoundAndFillStacks(FILE **out,TQueue* q, int *numberOfTeams,TTeam **winStackTop,TTeam **looseStackTop)
{
    int spaceBeforeDash = 33;
    int spaceAfterDash = 33;

    int i,j;
    for(i=0;i<(*numberOfTeams)/2;i++)
        {

            TTeam *x = deQueue(q);
            TTeam *y = deQueue(q);

            //stabilim cine a castigat, cine a pierdut
            TTeam *winner = fightToWinner(x,y);
            TTeam *looser = fightToLooser(x,y);

            push(winStackTop,winner);
            push(looseStackTop,looser);

            //freeTeam(winner);
            //freeTeam(looser);

            fprintf(*out,"%s",x->teamName);
            for(j=0;j<spaceBeforeDash-strlen(x->teamName);j++)
            {
                fprintf(*out," ");
            }
            fprintf(*out,"-");
            for(j=0;j<spaceAfterDash-strlen(y->teamName);j++)
            {
                fprintf(*out," ");
            }
            fprintf(*out,"%s",y->teamName);
            fprintf(*out,"\n");

            //freeTeam(x);
            //freeTeam(y);
            // x=NULL;
            // y=NULL;
        }
}

void addTeamToQueue(TQueue *q, TTeam *h)
{
    if(h==NULL)
    {
        printf("\nerror, null head while adding teams to queue");
        return;
    }

    TTeam *aux;
    while(h!=NULL)
    {
        aux=h;
        h=h->next;
        enQueue(q,aux);
        //freeTeam(aux);
    }
}

void printCurrentWinnersFromStack(FILE **out,TTeam *winnersStackTop, int* numberOfCurrentWinners)
{
    if(winnersStackTop==NULL)
    {
        printf("\nerror printing winners, stack is empty");
    }
    int i,j;
    int spaceBeforeDash = 34;
    TTeam *aux;

    for(i=0;i<(*numberOfCurrentWinners);i++)
    {
        aux = pop(&winnersStackTop);
        fprintf(*out,"%s",aux->teamName);
        for(j=0;j<spaceBeforeDash-strlen(aux->teamName);j++)
        {
            fprintf(*out," ");
        }
        fprintf(*out,"-");
        fprintf(*out,"  ");
        fprintf(*out,"%.2f\n",aux->teamAverage);
        free(aux);
    }
}

//TURNEU
//out e deja deschis, incepem cu prima runda
void printRounds(FILE **out, TQueue *q, int numberOfTeams, int id, TTeam **bestEightWinners)
{
    int numberOfRounds = (int) log2(numberOfTeams); 
    int BestOfEight = 8;
    int i,j;
    fprintf(*out,"\n");

    //creem stivele de castigatori si invingatori
    TTeam *winStack = NULL;
    TTeam *looseStack = NULL;
    
    //atribuim un pointer la coada noastra, si lucram cu ea
    TQueue *auxQueue = q;

    //salvam cate echipe curente raman dupa le tot punem si scoatem de pe coada
    int numberOfCurrentWinners = numberOfTeams;

    for(i=1;i<=numberOfRounds;i++)
    {
        fprintf(*out,"--- ROUND NO:%d\n",i);


        //descarcam coada si umplem winStackul si looseStackul
        printAllTeamsOnRoundAndFillStacks(out,auxQueue,&numberOfCurrentWinners,&winStack,&looseStack);

        //daca in stiva de castigatori avem 8 playeri, ii salvam intr o alta lista
        if(sizeOfStack(winStack)==BestOfEight && (id>=4))
        {
            //initializam stiva in care o sa punem cei mai buni 8 jucatori cu null
            *bestEightWinners=NULL;

            // salvam capul de lista de unde incepem sa dam push la elemente
            TTeam *iterator = winStack;

            for(int j=0;j<BestOfEight;j++)
            {
                //dam push in noua stiva 
                push(bestEightWinners,iterator);
                iterator=iterator->next;
            }
        }
        //umplem coada cu castigatorii rundei respective
        addTeamToQueue(auxQueue,winStack);

        numberOfCurrentWinners /=2;

        //stergem coada cu pierzatori
        deleteStack(&looseStack);

        fprintf(*out,"\n");
        fprintf(*out,"WINNERS OF ROUND NO:%d\n",i);

        printCurrentWinnersFromStack(out,winStack,&numberOfCurrentWinners);

        //reinitializam stack ul cu null pentru a putea fi umplut ulterior
        winStack=NULL;
        looseStack=NULL;

        //daca nu am ajuns la final de turneu, inca pune spatiu
        if(numberOfCurrentWinners!=1)
        {
            fprintf(*out,"\n");
        }

    }
    //freeQueue(auxQueue);
}

void printBestEightTeams(FILE **out,TTree *root)
{
    fprintf(*out,"\n");
    fprintf(*out,"TOP 8 TEAMS:");
    fprintf(*out,"\n");
    InverseInorderPrint(out,root);
}
void InverseInorderPrint(FILE **out,TTree *root)
{
    int spaceBeforeDash = 34;
    int j;
    if(root)
    {
        InverseInorderPrint(out,root->right);

        fprintf(*out,"%s",root->team.teamName);
        for(j=0;j<spaceBeforeDash-strlen(root->team.teamName);j++)
        {
            fprintf(*out," ");
        }
        fprintf(*out,"-");
        fprintf(*out,"  ");
        fprintf(*out,"%.2f\n",root->team.teamAverage);

        InverseInorderPrint(out,root->left);
    }
}


/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

int nodeHeight(TAVLTree *root)
{
    if(root==NULL)
    {
        return -1;
    }
    else
    {
        return root->height;
    }
}
TAVLTree *rightRotation(TAVLTree *z)
{
    TAVLTree *y = z->left;
    TAVLTree *T3 = y ->right;

    //rotatie
    y->right = z;
    z->left = T3;

    //updatam inaltimile
    z->height = max(nodeHeight(z->left),nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right)) + 1;

    return y;
}

TAVLTree *leftRotation(TAVLTree *z)
{
    TAVLTree *y = z->right;
    TAVLTree *T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = max(nodeHeight(z->left),nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right)) + 1;

    return y;
}

TAVLTree* LRRotation(TAVLTree *z)
{
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

TAVLTree* RLRotation(TAVLTree *z)
{
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

TAVLTree* avlInsert(TAVLTree *node, TTeam *x)
{
    if(node==NULL)
    {
        node = (TAVLTree*) malloc(sizeof(TAVLTree));
        node->team.teamName = (char*) malloc((strlen(x->teamName) + 1) * sizeof(char));
        if(node->team.teamName == NULL)
        {
            printf("\nerror allocating mem.");
            return NULL;
        }
        strcpy(node->team.teamName,x->teamName);
        node->team.teamAverage = x->teamAverage;
        node->height = 0;
        node->left = node->right = NULL;

        return node;
    }

    if(x->teamAverage < (node->team).teamAverage)
    {
        node->left = avlInsert(node->left,x);
    }
    else
    {
        if(x->teamAverage == (node->team).teamAverage)
        {
            if(strcmp(x->teamName,(node->team).teamName)>0)
            {
                node->right = avlInsert(node->right,x);
            }
            else
            {
                node->left = avlInsert(node->left,x);
            }
        }
        else
        {
            node->right = avlInsert(node->right,x);
        }
    }

    node->height = 1 + max(nodeHeight(node->left),nodeHeight(node->right));
    int k = nodeHeight(node->left) - nodeHeight(node->right);
    
    //LL            6 < 7                                          sau                                       7a==7b             si 
    if(k > 1 && ((x->teamAverage < (node->left->team).teamAverage) ||  ((x->teamAverage == (node->left->team).teamAverage) &&
    //              a<b
                (strcmp(x->teamName,(node->left->team).teamName)<0) )))
    {
        return rightRotation(node);
    }
    if(k > 1 && ((x->teamAverage < (node->left->team).teamAverage) ||  ((x->teamAverage == (node->left->team).teamAverage) &&
    //              a<b
                (strcmp(x->teamName,(node->left->team).teamName)>0) )))
    {
        return LRRotation(node);
    }

    //RR
    if(k < -1 && ((x->teamAverage > (node->right->team).teamAverage) ||  ((x->teamAverage == (node->right->team).teamAverage) &&
    //              a<b
                (strcmp(x->teamName,(node->right->team).teamName)>0) )))
    {
        return leftRotation(node);
    }

    //RL
    if(k < -1 && ((x->teamAverage < (node->right->team).teamAverage) ||  ((x->teamAverage == (node->right->team).teamAverage) &&
    //              a<b
                (strcmp(x->teamName,(node->right->team).teamName)<0) )))
    {
        return RLRotation(node);
    }
    return node;
}


//k ia valoarea inaltimii radacinei inainte de functie
void repairPostOrderAvl(TAVLTree* root, int *k)
{ 
    if(root)
    {
        (*k)--;
        repairPostOrderAvl(root->right,k);
        repairPostOrderAvl(root->left,k);
        (*k)++;
        root->height = *k;
    }
}

void postOrderAvl(FILE **out,TAVLTree *root,int level)
{
    if(root)
    {
        postOrderAvl(out,root->right,level);
        postOrderAvl(out,root->left,level);
        if(root->height==level)
        {
            fprintf(*out,"%s\n",root->team.teamName);
        }
    }
}

//level - nivelul numarat de sus in jos, de la radacina la frunze
void printTeamsOnLevel(FILE **out, TAVLTree* root, int level)
{
    //nivelul actual al nodului arborelui de afisat
    int actualLevel = nodeHeight(root) - level;

    fprintf(*out,"\n");
    fprintf(*out,"THE LEVEL 2 TEAMS ARE: ");
    fprintf(*out,"\n");
    postOrderAvl(out,root,actualLevel);
}

void freeBSTNode(TTree* root)
{
    freeTeam(&(root->team));
    free(root->left);
    free(root->right);
}

void getFromBSTandInsertInAvl(TTree* bstRoot,TAVLTree** avlRoot)
{
    if(bstRoot)
    {
        getFromBSTandInsertInAvl(bstRoot->right,avlRoot);
        *avlRoot = avlInsert(*avlRoot,&(bstRoot->team));
        //freeBSTNode(bstRoot);
        //freeTeam(&bstRoot->team);
        getFromBSTandInsertInAvl(bstRoot->left,avlRoot);
    }
}

void freeTree(TTree* root)
{
    if(root)
    {
        freeTree(root->right);
        freeTree(root->left);

        freeBSTNode(root);
    }
}
/////////////////////////////////
//////////////BST////////////////
/////////////////////////////////

//functia creeaza un nou nod care contine o echipa cu nume si teamAverage
//functia returneaza noul nod creat
TTree* newNode(TTeam *x)
{
    TTree *node = (TTree*) malloc(sizeof(TTree));
    if(node==NULL)
    {
        printf("\nerror, out of memory allocating newNode for tree");
        return NULL;
    }

    node->team.teamName = (char*) malloc((strlen(x->teamName)+1) * sizeof(char));
    if(node->team.teamName == NULL)
    {
        printf("\nerror, out of memory allocating teamname for newNode.");
        return NULL;
    }
    strcpy(node->team.teamName,x->teamName);
    node->team.teamAverage = x->teamAverage;

    node->left = NULL;
    node->right = NULL;
    return node;
}

TTree* insert(TTree* node,TTeam *x)
{
    if(node==NULL)
    {
        return newNode(x);
    }
    if(x->teamAverage < node->team.teamAverage)
    {
        node->left = insert(node->left,x);
    }
    else
    {
        if(x->teamAverage == node->team.teamAverage)
        {
            if(strcmp(x->teamName,node->team.teamName)>0)
            {
                node->right = insert(node->right,x);
            }
            else
            {
                node->left = insert(node->left,x);
            }
        }
        else
        {
            node->right = insert(node->right,x);
        }
    }
    return node;
}

/////////////////////////////////
//////////////QUEUE//////////////
/////////////////////////////////

TQueue* createQueue()
{
    TQueue* q = (TQueue*) malloc(sizeof(TQueue));
    if(q==NULL)
    {
        printf("\nerror allocating queue");
        return NULL;
    }
    q->front=NULL;
    q->rear=NULL;
}

int isEmptyQueue(TQueue *q)
{
    return (q->rear==NULL);
}

// adauga echipa x in coada q
void enQueue(TQueue* q, TTeam *x)
{
    TTeam* newTeam = (TTeam*) malloc(sizeof(TTeam));
    if(newTeam==NULL)
    {
        printf("\nerror creating team for queue");
        return;
    }
    newTeam->teamName = (char*) malloc((strlen(x->teamName)+1)*sizeof(char));
    if(newTeam->teamName==NULL)
    {
        printf("\nerror allocating mem for team name");
    }

    strcpy(newTeam->teamName,x->teamName);
    newTeam->teamAverage = x->teamAverage;
    newTeam->next=NULL;

    if(q->rear==NULL)
    {
        q->rear=newTeam;
    }
    else
    {
        q->rear->next=newTeam;
        q->rear=newTeam;
    }
    if(q->front==NULL)
    {
        q->front=q->rear;
    }
}

TTeam* deQueue(TQueue *q)
{   
    TTeam* aux, *info;
    if(isEmptyQueue(q))
    {
        printf("\nerror, queue empty");
        return NULL;
    }

    aux=q->front;
    info = (TTeam*) malloc(sizeof(TTeam));
    info->teamName = (char*) malloc((strlen(aux->teamName)+1) * sizeof(char));

    strcpy(info->teamName,aux->teamName);
    info->teamAverage=aux->teamAverage;

    q->front=q->front->next;
    free(aux);

    if(q->front==NULL)
    {
        q->rear=NULL;
    }
    return info;
}


void freeQueue(TQueue* q)
{
    while(q->front!=NULL)
    {
        TTeam *curr = q->front;
        q->front = q->front->next;
        freeTeam(curr);
    }
    q->front = NULL;
    q->rear = NULL;
}




/////////////////////////////////
//////////////STACK//////////////
/////////////////////////////////

void push (TTeam **top, TTeam* x)
{
    TTeam* newTeam = (TTeam*) malloc(sizeof(TTeam));
    if(newTeam==NULL)
    {
        printf("\nerror pushing team on stack");
        return;
    }
    if(x==NULL)
    {
        printf("\nerror, no team to push on stack");
        return;
    }

    newTeam->teamName = (char*) malloc((strlen(x->teamName)+1) * sizeof(char));
    if(newTeam->teamName==NULL)
    {
        printf("\nerror allocating mem for teamName");
        return;
    }
    strcpy(newTeam->teamName,x->teamName);
    newTeam->teamAverage = x->teamAverage;

    newTeam->next=*top;
    *top=newTeam;
}

int isEmptyStack(TTeam *top)
{
    return (top==NULL);
}

TTeam* pop(TTeam **top)
{
    TTeam* newTeam = (TTeam*) malloc(sizeof(TTeam));
    TTeam* tmp = *top;
    if(newTeam==NULL)
    {
        printf("\nerror allocating mem for newTeam for stack");
        return NULL;
    }
    if(*top==NULL)
    {
        printf("\nerror, top null");
        return NULL;
    }

    newTeam->teamName = (char*) malloc(((strlen((*top)->teamName) + 1) * sizeof(char)));
    if(newTeam->teamName==NULL)
    {
        printf("\nerror allocating me for teamName for stack");
        return NULL;
    }

    strcpy(newTeam->teamName,(*top)->teamName);
    newTeam->teamAverage = (*top)->teamAverage;

    *top = (*top)->next;

    free(tmp->teamName);
    free(tmp);
    return newTeam;
}

void deleteStack(TTeam **top)
{
    TTeam *aux;
    while(*top)
    {
        aux = *top;
        *top = (*top)->next;
        free(aux);
    }
}

///////////////////////////////////
///////////////FREE////////////////
///////////////////////////////////

void freeTeam(TTeam *team)
{
    if(team==NULL)
    {
        return;
    }
    int sizeOfTeam = team->numberOfPlayers;
    for(int i = 0 ; i<sizeOfTeam;i++)
    {
        free(team->players[i].firstName);
        free(team->players[i].lastName);
    }
    free(team->players);
    free(team->teamName);
    free(team);
}

void freeList(TTeam *head)
{   
    TTeam* aux;
    while(head)
    {
        aux = head;
        head=head->next;
        freeTeam(aux);
    }
}

void freeNode(TNode *player)
{
    free(player->firstName);
    free(player->lastName);
    free(player);
}

void freeAVLTree(TAVLTree *root) {
    if (root == NULL) {
        return;
    }
    freeAVLTree(root->left);
    freeAVLTree(root->right);

    free(root->team.teamName);
    for (int i = 0; i < root->team.numberOfPlayers; i++) {
        free(root->team.players[i].firstName);
        free(root->team.players[i].lastName);
    }
    free(root->team.players);
    free(root);
}