//convert eNFA to NFA
//1.headers
#include <stdio.h>
#include<stdlib.h>

//2.data strcutres
struct node{
    int state;
    struct node * link;
}; //represents a state in the transition table

//3.variables
static int set[20], buffer[20];
static int num_of_alphabets, num_of_states, num_of_transitions, num_of_final_states, final_state[20], start, r, c, s;
//row -> row in transition table represents state: r=0 => q0, r=1 -> q1
//col -> represents the alphabet in the transition table: c=0 => a, c=1 => b, etc.
//eg:
//-----------------------
//      |   a   |   e   |
//-----------------------
//  q0  |   _   |   q1  |
//-----------------------
//  q1  |   q1  |   q1  |
//-----------------------
//  HOW THIS WORKS:
// assume epsilon closure of q0 : {q0,q2}, inputs are a and b
// for each input :
//  a =>
//      q0 ->(a) q1
//      q2 ->(a) q2
//      reachable states => {q1,q2}
//      result => q0 ->(a) {q1,q2}
//  b=>
//      q0 ->(b) NULL
//      q2 ->(b) NULL
//      reachable states => NULL
//      result => NULL
//  create a transition table based on these values.
char alphabets[20];
static int e_closure[20][20] = {0}; //stores eclosure of each state
struct node * transitions[20][20] = {NULL}; //array of linked lists

//4.declare helper functions

void findclosure(int,int);
void insert_transitions(int ,char, int);
int findindex(char);
void finds(void);
void unionclosure(int);
void print_e_closure(int);

int main(){
    int i,j,k,m,t,n; // all loop control variables + t a temp var
    struct node *temp;
    //inputting 
    printf("enter the number of alphabets?\n");
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
        printf("Enter the number of states?\n");
        scanf("%d",&num_of_states);
        printf("Enter the start state?\n");
        scanf("%d",&start);
        printf("Enter the number of final states?\n");
        scanf("%d",&num_of_final_states);
        printf("Enter the final states?\n");
        for(i=0;i<num_of_final_states;i++)
                scanf("%d",&final_state[i]);
         printf("Enter no of transition?\n");
        scanf("%d",&num_of_transitions);
        printf("NOTE:- [Transition is in the form--> qno   alphabet   qno]\n",num_of_transitions);
        printf("NOTE:- [States number must be greater than zero]\n");
        printf("\nEnter transition?\n");
        for(i=0;i<num_of_transitions;i++)
        {

 
                scanf("%d %c%d",&r,&c,&s);
                insert_transitions(r,c,s);

        }

        printf("\n");

        //find eclosure like last cycle1 exp1
        for(i=1;i<=num_of_states;i++)
        {
                c=0;
                //reset the buffers before each computation
                for(j=0;j<20;j++)
                {
                    buffer[j]=0;
                    e_closure[i][j]=0;
                }
                findclosure(i,i);
        }

        printf("Equivalent NFA without epsilon\n");
        printf("-----------------------------------\n");
        printf("start state:");
        print_e_closure(start);


        printf("\nAlphabets:");
        for(i=0;i<num_of_alphabets;i++)
                  printf("%c ",alphabets[i]);

        printf("\nStates :" );
        for(i=1;i<=num_of_states;i++)
                  print_e_closure(i);

        printf("\nTransitions are...:\n");

        // finding the NFA, explained in HOW THIS WORKS
        //set => holds the reachable states temporarily for each state
        for(i=1;i<=num_of_states;i++) //for each state
        {
                  for(j=0;j<num_of_alphabets-1;j++) // for each input symbol (a,b,c etc) represented by j
                 {
                          for(m=1;m<=num_of_states;m++)set[m]=0; // clear reachable states
                          for(k=0;e_closure[i][k]!=0;k++) //for all states in e closure of state {i}
                          {
                                t=e_closure[i][k]; //get each state in the eclosure
                                temp=transitions[t][j]; //get the transitions on this state on input symbol {j}
                                while(temp!=NULL)
                                {
                                    unionclosure(temp->state); // add rechable state to the set
                                    temp=temp->link;
                                }
                         }
                        printf("\n");
                        print_e_closure(i);
                        printf("%c\t",alphabets[j]  );
                        printf("{");
                        for(n=1;n<=num_of_states;n++)
                        {
                                     if(set[n]!=0)
                                             printf("q%d,",n);
                        }
                         printf("}");
                }
        }
        printf("\nFinal states:");
        finds();

}



void findclosure(int x,int sta)
{
            struct node *temp;
            int i;
           if(buffer[x])
                     return;
             e_closure[sta][c++]=x;
            buffer[x]=1;
            //recursively find all states reachable via epsilon transition and add it to the initial states epsilon closure
             if(alphabets[num_of_alphabets-1]=='e' && transitions[x][num_of_alphabets-1]!=NULL)
                {
                             temp=transitions[x][num_of_alphabets-1];
                             while(temp!=NULL)
                            {
                                         findclosure(temp->state,sta);
                                         temp=temp->link;
                             }
                }
  }

void insert_transitions(int r,char c,int s)
{
           int j;
           struct node *temp;
            j=findindex(c);
          if(j==999)
          {
                     printf("error\n");
                    exit(0);
          }
         temp=(struct node *) malloc(sizeof(struct node));
         temp->state=s;
         temp->link=transitions[r][j];
         transitions[r][j]=temp;
}

int findindex(char c)
{
            int i;
            for(i=0;i<num_of_alphabets;i++)
                   if(alphabets[i]==c)
                          return i;

                return(999);


}

void unionclosure(int i)
{
            int j=0,k;
             while(e_closure[i][j]!=0)
             {
                      k=e_closure[i][j];
                      set[k]=1;
                      j++;
             }
}
void finds()
{
            int i,j,k,t;
            for(i=0;i<num_of_final_states;i++)
           {
                      for(j=1;j<=num_of_states;j++)
                      {
                              for(k=0;e_closure[j][k]!=0;k++)
                                {
                                         if(e_closure[j][k]==final_state[i])
                                        {

                                                 print_e_closure(j);
                                        }
                               }
                      }
             }


  }

void print_e_closure(int i)
{
        int j=0;
        printf("{");
       if(e_closure[i][j]!=0)
                        printf("q%d,",e_closure[i][0]);
         printf("}\t");
}