# Lan Party la Automatica
Facultatea de Automatica si Calculatoare prin LSAC organizează in fiecare semestru un LAN Party la care participă toți studenții care vor sa își testeze abilitățile la un anumit joc. Se doreste automatizarea procesului de prelucrare a echipelor, a meciurilor, prin:

* aflarea echipei castigatoare dintr-o serie de n echipe
* realizarea unui clasament a celor mai bune 8 echipe
* afisarea unui nivel din bracket-uri

## Fisiere necesare 
```
date/tX/c.in
date/tX/d.in
out/outX.out
```
* x -> numarul testului aferent

## Structuri necesare
```c
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
```

## Date de intrare
Fisierul de mai jos contine informatii aferente echipelor:

```
date/tX/d.in
````

Fisierul contine:
* **Numarul de echipe** pe prima linie
* **Echipele** care se citesc prin numarul de jucatori, numele echipei si jucatorii propriu-zisi:  

Fisierul de mai jos contine **task-urile** aferente Lan Party ului:

````
date/tX/c.in
````

Fisierul contine o secventa de cinci **0** cu **1** de forma

````
1 0 0 0 0
1 1 1 1 0
etc...
````


## Mod de lucru
Initial, in pool-ul de echipe, exista un numar foarte mare de echipe, numarul fiind citit din fisierul:
>       date/tX/d.in

Initial deschidem fisierul **date/tX/c.in** pentru a afla ce cerinta se cere pentru fiecare test, calculand intr-o functie codul asociat testului respectiv. Practic functia numara cati 1 se gasesc in fisier.

```c
    int calculateCheckerId(char *fileName)
 ```

Se creeaza **o lista simplu inlantuita cu santinela** in care se vor salva toate echipele ce vor juca. Echipele cu punctajul minim vor fi eliminate din lista, pana cand in lista vor ramane 2^n, unde 2^n este **mai mic** decat **numarul echipelor initiale**. Acest lucru se va realiza prin functia:

```c
 void eliminateTeamsToLowestMed(TTeam *d, int* numberOfTeams)
```

care ia ca parametru lista d si numarul de echipe , folosindu-se functia:

```c
int lowestPowerOfTwo(int n)
```
pentru a calcula cea mai mica putere a lui 2, mai mica decat numarul dat.  
  
Astfel, echipele ramase se vor pune **intr-o coada** unde vor avea loc "meciurile".

```c
void insertTeamsOnQueue(TQueue *q, TTeam *h)
```
q -> coada  
h -> capul de lista care itereaza prin toata lista de echipe

Meciurile care se vor juca intre echipele din coada se vor realiza si totodata **afisa** in functia:

```c
void printRounds(FILE **out, TQueue *q, int numberOfTeams, int, TTeam**)
```
Meciurile se vor juca astfel:
* echipele se scot din coada **doua cate doua**, exact asa cum au fost introduse, prin intermediul **functiilor specifice cozii** (deQueue, enQueue, ...) dar si prin:
```c
void printAllTeamsOnRoundAndFillStacks(FILE **out,TQueue* q, int *numberOfTeams,TTeam **winStackTop,TTeam **looseStackTop)
```
* in cadrul unui meci, se determina castigatorul si pierzatorul, unde functiile:
```c
...
TTeam* fightToWinner(TTeam* t1, TTeam *t2)
TTeam* fightToLooser(TTeam* t1, TTeam *t2)
...
```
determina **castigatorul**, respectiv **pierzatorul** rundei curente.

Castigatorul si pierzatorul este salvat astfel

```c
    TTeam *winner = fightToWinner(x,y);
    TTeam *looser = fightToLooser(x,y);
```

x, y -> echipele scoase din coada

Echipele sunt introduse in **2 stive**  
* **una de castigatori**
* **una de pierzatori**  

```c
    push(winStackTop,winner);
    push(looseStackTop,looser);
```
Apoi echipele sunt afisate in fisierul output din runda curenta.  
* Echipele castigatoare din runda curenta sunt introduse din stiva castigatoare in coada din nou, reluand procesul.
* Echipele pierzatoare sunt adaugate in stiva pierzatorilor, stiva **care se elibereaza** dupa fiecare runda.

```c
    void addTeamToQueue(TQueue *q, TTeam *h)
    {
        ...
    }

    .
    .
    .

    void deleteStack(TTeam **top)
    {
        ...
    }

    .
    .
    .

    //in functia printRounds
    addTeamToQueue(q,winStack);
    deleteStack(&looseStack);
```
Totodata, afisam si echipele castigatoare dupa fiecare runda din stiva castigatorilor.

```c
void printCurrentWinnersFromStack(FILE **out,TTeam *winnersStackTop, int* numberOfCurrentWinners)
```
* out -> fisierul de iesire
* winnersStackTop -> capul stack-ului castigatorilor
* numberOfCurrentWinners -> numarul castigatorilor curenti, modificat **dinamic**  

Dupa golirea stivelor, nu uitam sa le marcam ca fiind NULL, pentru a putea fi umplute cu alte echipe, din rundele viitoare.

```c
        winStack=NULL;
        looseStack=NULL;
```

Totodata, pe parcursul functiei **printRounds()**, tinem evidenta faptului daca nu cumva in stiva au ramas 8 jucatori, pentru a putea transmite in main **cele mai bune 8 echipe**.Exact asta facem 

```c
    void printRounds(FILE **out, TQueue *q, int numberOfTeams, int id, TTeam **bestEightWinners)
    {

    .   .   .   .   .   .   .   .   .   .   .   .   .
    .   .   .   .   .   .   .   .   .   .   .   .   .
    .   .   .   .   .   .   .   .   .   .   .   .   .

    // BestOfEight = o constanta definita anterior, cu valoare 8
    // id ul este cel trimis din main, daca cumva suntem pe cazul 
    //                 testelor 10 11 12
    if(sizeOfStack(winStack)==BestOfEight && (id>=4))
        {
            *bestEightWinners=NULL;
            TTeam *iterator = winStack;

            for(int j=0;j<BestOfEight;j++)
            {
                //dam push in noua stiva 
                push(bestEightWinners,iterator);
                iterator=iterator->next;
            }
    
        }

    .   .   .   .   .   .   .   .   .   .   .   .   .
    .   .   .   .   .   .   .   .   .   .   .   .   .
    .   .   .   .   .   .   .   .   .   .   .   .   .

    }
```

In cazul ultimelor teste, se implementeaza *un arbore BST* si *unul AVL* pentru **afisarea echipelor in ordine descrescatoare** (dupa punctajul de echipa sau, daca acesta este egal, dupa numele echipei), respectiv **afisarea unui anumit nivel din arbore**, in acest caz, **nivelul 2**.
* Din stiva castigatorilor transmisa in main, se introduc in arborele BST unul cate unul.

```c
    bstRoot = NULL;
    while(!isEmptyStack(bestEightTeams))
    {
        x = pop(&bestEightTeams);
        bstRoot = insert(bstRoot,x);
    }
```

* Functia de **inserare** in BST:

```c
    TTree* insert(TTree* node,TTeam *x)
```
* Introduce in arbore toate echipele din stiva dupa criteriul mediei generale sau al numelui de echipa, ulterior afisand intreg arborele intr-o maniera DRS (Inverse Inorder).

**Arborele AVL** este creat prin parcurgerea BST-ului intr o maniera DRS (Inverse Inorder), extragerea elementului de pe acea pozitie si introducerea in AVL. Acest lucru se realizeaza prin intermediul functiei:

```c
void getFromBSTandInsertInAvl(TTree* bstRoot,TAVLTree** avlRoot)
{
    if(bstRoot)
    {
        getFromBSTandInsertInAvl(bstRoot->right,avlRoot);
        *avlRoot = avlInsert(*avlRoot,&(bstRoot->team));
        getFromBSTandInsertInAvl(bstRoot->left,avlRoot);
    }
}
```

* avlRoot -> root-ul arborelui AVL trimis din main
* bstRoot -> root-ul arborelui BST din care scoatem elemente

Functia de inserare in AVL:

```c
TAVLTree* avlInsert(TAVLTree *node, TTeam *x)
```
este implementata recursiv, si introduce rand pe rand echipa x in arbore. Dupa o introduce a unui element, se reactualizeaza si inaltimile nodurilor de la elementul introdus pana la root.

Inaltimile nodurilor se modifica relativ la subarborele in care se gasesc, nu raportat la tot arborelee, asa ca am introdus functia:

```c
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
```

* Functia primeste ca parametru root-ul AVL ului si inaltimea root ului, dat prin **acel k**, care **descreste pe masura ce coboram in adancimea arborelui** si care **creste pe masura ce urcam**.
* Apoi intereaza prin tot arborele AVL intr-o maniera DSR (Inverse Postorder), modificand si "reparand" inaltimile fiecarui nod.
* Astfel, fiecare nod are inaltimea corecta raportat la intreg arborele.

Intr-un final, functia afiseaza in fisierul out un nivel dat ca parametru din AVL-ul anterior creat, tot prin **Inverse Postorder**:

```c
void printTeamsOnLevel(FILE **out, TAVLTree* root, int level)
{
    int actualLevel = nodeHeight(root) - level;
    fprintf(*out,"\n");
    fprintf(*out,"THE LEVEL 2 TEAMS ARE: ");
    fprintf(*out,"\n");
    postOrderAvl(out,root,actualLevel);
}
```

care se foloseste de subfunctia:

```c
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
```

