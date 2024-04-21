#include "lanPartyLib.h"

int main(int argc, char* argv[])
{
    //argv[1] = c.in
    //argv[2] = d.in
    //argv[3] = outI.out
    
    // printf("Number of input files: %d\n", argc);
    // printf("Exec name: %s\n", argv[0]);
    // printf("argv[1]: %s\n", argv[1]);
    // printf("argv[2]: %s\n", argv[2]);
    // printf("argv[3]: %s\n", argv[3]);
    

    FILE *out = fopen(argv[3],"w");
    FILE *f;


    int id = calculateCheckerId(argv[1]);
    

    int i;
    int teamSize;
    char *teamName;

    
    TTeam *d = createBlankList();
    int numberOfTeams = findNumberOfTeams(&f,argv[2]);

    for(i=0; i<numberOfTeams;i++)
        {

        //aflam cati oameni sunt in echipa
        int teamSize=getNumberOfTeamMembers(&f);

        //aflam care este numele echipei
        char *teamName = findTeamName(&f);

        //daca are spatiu pe ultima pozitie, il dam trimm la ' ' , \n si \0
        //daca nu are spatiu pe ultima pozitie, ii dam trimm doar la \n si la \0
        if(teamName[strlen(teamName)-3]==' ')
        {
            teamName[strlen(teamName)-3] = 0;
        }
        else
        {
            teamName[strlen(teamName)-2] = 0;
        }

        TTeam *newTeam = createTeam(&f,teamSize,teamName);
        free(teamName);
        //teamName = NULL;

        addToListOfTeams(d,newTeam);

        //freeTeam(newTeam);
        //newTeam = NULL;
    }


    TQueue* q = NULL;
    TTeam* bestEightTeams = NULL;
    TTeam* copyBestEightTeams = NULL;

    TTree* bstRoot;
    TTeam *x;
    TTeam *y;

    TAVLTree *avlRoot;

    switch (id)
    {
        case 1:
            printTeamsNames(&out,d->next);
            break;
        case 2:
            eliminateTeamsToLowestMed(d,&numberOfTeams);
            printTeamsNames(&out,d->next);
            break;
        case 3:
            //eliminam echipele pana cand ajungem la 2^n, unde n e maxim si 2^n < nr de echipe vechi
            eliminateTeamsToLowestMed(d,&numberOfTeams);
            printTeamsNames(&out,d->next);

            q = createQueue();

            // aici punem toate elementele in coada
            insertTeamsOnQueue(q,d->next);

            //afisam efectiv rundele in fisier
            printRounds(&out,q,numberOfTeams,id,&bestEightTeams);
            break;
        case 4:
            eliminateTeamsToLowestMed(d,&numberOfTeams);
            printTeamsNames(&out,d->next);

            q = createQueue();
            insertTeamsOnQueue(q,d->next);
            printRounds(&out,q,numberOfTeams,id,&bestEightTeams);

            bstRoot = NULL;
            while(!isEmptyStack(bestEightTeams))
            {
                x = pop(&bestEightTeams);
                bstRoot = insert(bstRoot,x);
            }
            printBestEightTeams(&out,bstRoot);
            break;
        case 5:
            eliminateTeamsToLowestMed(d,&numberOfTeams);
            printTeamsNames(&out,d->next);

            q = createQueue();
            insertTeamsOnQueue(q,d->next);

            printRounds(&out,q,numberOfTeams,id,&bestEightTeams);
            
            bstRoot = NULL;
            avlRoot = NULL;
            while(!isEmptyStack(bestEightTeams))
            {
                x = pop(&bestEightTeams);
                bstRoot = insert(bstRoot,x);
            }
            printBestEightTeams(&out,bstRoot);
            
            getFromBSTandInsertInAvl(bstRoot,&avlRoot);

            //reparam inaltimea nodurilor dupa inserare
            int h= nodeHeight(avlRoot);
            repairPostOrderAvl(avlRoot,&h);

            printTeamsOnLevel(&out,avlRoot,2);
            break;
    }
    freeList(d);
    fclose(f);
    fclose(out);
    return 0;
}