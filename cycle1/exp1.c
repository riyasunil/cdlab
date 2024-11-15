//find the epsilon closure of a dfa

//1.headers
#include <stdio.h>
#include <stdlib.h>

//2.data structures
struct node{
    int state;
    struct node *link; 
};

//3.global variables
static int set[20], buffer[20]; //to manage states during epsilon closure computation
static int num_of_states, num_of_alphabets, num_of_transisitons, s1, a ,s2;
char alphabets[20];
static int e_closure[20][20] = {0}; // 2d array to store the eclosure of each state
struct node *transition[20][20] = {NULL}; //transition table in the form of an array of linked lists

//4.declare the helper functions
void find_closure(int, int);
void insert_transitions(int, char, int);
int findindex(char); 
void print_eclosure(int);

//5.start main function
int main(){
    int i,j,k,l,m,n;
    struct node * temp;

    printf("Enter the number of alphabets\n");
    scanf("%d",&num_of_alphabets);
    getchar();
    printf("NOTE:- [ use letter e as epsilon]\n");
    printf("NOTE:- [e must be last character ,if it is present]\n");
    printf("\nEnter alphabets?\n");
    for(i=0;i<num_of_alphabets;i++)
    {
        alphabets[i]=getchar();
        getchar();
    }
     printf("\nEnter the number of states?\n");
    scanf("%d",&num_of_states);
    printf("\nEnter no of transition?\n");
    scanf("%d",&num_of_transisitons);
    printf("NOTE:- [Transition is in the form–> qno alphabet qno]\n",num_of_transisitons);
    printf("NOTE:- [States number must be greater than zero]\n");
    printf("\nEnter transition?\n");
    for(i=0;i<num_of_transisitons;i++)
    { 
        scanf("%d %c%d",&s1,&a,&s2);
        insert_transitions(s1,a,s2);
    }
    printf("\n");
    printf("e-closure of states\n");
    printf("____________________\n");
    for(i=1;i<=num_of_states;i++)
    {
        a = 0; //number of states added
        for(j=0;j<20;j++)
        {
            buffer[j]=0;
            e_closure[i][j]=0;
        }
        find_closure(i,i);
        printf("\ne-closure(q%d): ",i);
        print_eclosure(i);
        }
}

void find_closure(int x, int s)
{
    struct node * temp;
    int i;
    //if buffer is already visited ( this state has already been computed before ), return
    if (buffer[x])return;
    //add state `x` to the epsilon closure of `s` (starting state), increment a (number of states added)
    e_closure[s][a++] = x;
    //marking x as visited
    buffer[x] =1;
    //check for epsilon transitions from state x + make sure the last character of alphaters is e
    if (alphabets[num_of_alphabets - 1] == 'e' && transition[x][num_of_alphabets - 1] != NULL)
    {
        temp = transition[x][num_of_alphabets-1];
        while(temp != NULL){
            find_closure(temp->state, s);
            temp = temp->link;
        }
    }
}

void insert_transitions(int source_state, char c, int sink_state)
{
    int j;
    struct node* temp;
    //find index of c in alphabet array
    j = findindex(c);
    //if c isnt found, end the program
    if (j==999){
        printf("error\n");
        exit(0);
    }
    //create new node for sink_state ( new state to be aded )
    temp = (struct node*)malloc(sizeof(struct node));
    temp->state = sink_state;
    //link this new node to the exisitng list for state `source_state` on transitions on c
    temp->link = transition[source_state][j];
    transition[source_state][j] = temp;

}

int findindex(char c)
{
    int i;
    for(i=0;i<num_of_alphabets;i++)
        if(alphabets[i]==c)
            return i;
    return(999);
}

void print_eclosure(int i)
{
    int j;
    printf("{");
    for(j=0;e_closure[i][j]!=0;j++)
        printf("q%d,",e_closure[i][j]);
    printf("}");
}