#include <stdio.h>
#include <stdlib.h>

// Queue functions
struct QNode
{
   int data;
   struct QNode* next;
};
typedef struct QNode QNode;
typedef struct QNode* QNodePtr;

QNodePtr CreateQueue();
void Enqueue(QNodePtr* head, int data);
int Dequeue(QNodePtr* head);
void PrintQueue(QNodePtr head);
int IsInQueue(QNodePtr head, int query);
int IsEmpty(QNodePtr head);
int SizeOfQueue(QNodePtr head);

void EnqueueEdge(QNodePtr* head, int d1, int d2);
int ContainsEdge(QNodePtr head, int q1, int q2);
void PrintMatches(QNodePtr head);
void RemoveEdge(QNodePtr* head, int q1, int q2);

QNodePtr MaximumBipartiteMatching(QNodePtr* adjLists, int numV, int numU);

int main(int argc, char* argv[])
{
   if(argc < 3)
   {
      printf("Invalid usage!\n");
      exit(-1);
   }

   int numV = atoi(argv[1]);
   int numU = atoi(argv[2]);

   QNodePtr* adjLists = (QNodePtr*)malloc(sizeof(QNodePtr) * numV);
   int curIndex = 0;

   // Assign the adjacency lists
   for(int i = 3; i < argc && curIndex < numV; )
   {
      if(argv[i][0] == 'X') 
      {
         i++;
         continue;
      }

      QNodePtr head = NULL;
      QNodePtr* tail = &head;

      while(i < argc && argv[i][0] != 'X')
      {
         QNodePtr newNode = (QNodePtr)malloc(sizeof(QNode));
         newNode->data = atoi(argv[i++]);
         newNode->next = NULL;
         *tail = newNode;
         tail = &newNode->next;
      }

      adjLists[curIndex++] = head;
   }

   // Print the lists
   for(int i = 0; i < numV; i++)
   {
      printf("%i -> ", i);
      PrintQueue(adjLists[i]);
      printf("\n");
   }

   MaximumBipartiteMatching(adjLists, numV, numU);
}

QNodePtr MaximumBipartiteMatching(QNodePtr* adjLists, int numV, int numU)
{
   //Initialize empty edge set
   QNodePtr M = NULL;

   // Initialize queue of nodes in V
   QNodePtr Q = NULL;

   // Set up array to keep track of matches with U. -1 indicates free
   int* matches = (int*)malloc(sizeof(int) * (numU + numV));
   for(int i = 0; i < numU + numV; i++)
   {
      matches[i] = -1;
   }

   int* labels = (int*)malloc(sizeof(int) * (numU + numV));
   for(int i = 0; i < (numU + numV); i++)
   {
      labels[i] = -1;
   }

   for(int i = 0; i < numV; i++)
   {
      Enqueue(&Q, i);
   }

   while(!IsEmpty(Q))
   {
      printf("Queue: ");
      PrintQueue(Q);
      printf("\n");

      int w = Dequeue(&Q);

      if(w < numV)
      {
         // For each vertex adjacent to w
         QNodePtr p = adjLists[w];
         while(p != NULL)
         {
            int u = p -> data;
            if(matches[u] == -1)
            {
               // Augment
               matches[w] = u;
               matches[u] = w;
               EnqueueEdge(&M, w, u);
               int v = w;
               while(labels[v] != -1)
               {
                  u = labels[v];
                  RemoveEdge(&M, v, u);
                  v = labels[u];
                  EnqueueEdge(&M, v, u);
               }

               // Remove all vertex labels
               for(int i = 0; i < numV + numU; i++)
               {
                  labels[i] = -1;
               }

               // Empty Q
               while(Q != NULL)
               {
                  Dequeue(&Q);
               }

               printf("%i\n", SizeOfQueue(Q));

               // Reinit Q with all free vertices in V
               for(int i = 0; i < numV; i++)
               {
                  if(matches[i] == -1)
                  {
                     Enqueue(&Q, i);
                  }
               }

               break;
            }

            else // U is matched
            {
               if(!ContainsEdge(M, w, u) && labels[u] == -1)
               {
                  labels[u] = w;
                  Enqueue(&Q, u);
               }
            }
            p = p -> next;
         }         
      }

      else // W is an element of u and matched
      {
         int v = matches[w];
         labels[v] = w;
         Enqueue(&Q, v);
      }

      // Print them thangs
      PrintMatches(M);
   }

   // Return M
}

void PrintMatches(QNodePtr head)
{
   QNodePtr vs = NULL;
   QNodePtr us = NULL;

   while(head != NULL)
   {
      Enqueue(&vs, head -> data);
      head = head -> next;
      Enqueue(&us, head -> data);
      head = head -> next;
   }

   QNodePtr v = vs;
   QNodePtr s = us;
   while(v != NULL)
   {
      printf("\tV%d", v -> data);
      v = v -> next;
   }
   
   printf("\n");

   v = vs;
   while(v != NULL)
   {
      printf("\t|");
      v = v -> next;
   }

   printf("\n");

   while(s != NULL)
   {
      printf("\tU%d", s -> data);
      s = s -> next;
   }

   printf("\n");
}

QNodePtr CreateQueue(int val)
{
   QNodePtr head = (QNodePtr)malloc(sizeof(QNode));
   head -> next = NULL;
   head -> data = val;
   return head;
}

int SizeOfQueue(QNodePtr head)
{
   int retVal = 0;
   while(head != NULL)
   {
      retVal++;
      head = head -> next;
   }

   return retVal;
}

int IsInQueue(QNodePtr head, int query)
{
   while(head != NULL)
   {
      if(head -> data == query)
      {
         return 1;
      }

      head = head -> next;
   }

   return 0;
}

int ContainsEdge(QNodePtr head, int q1, int q2)
{
   while(head != NULL)
   {
      if(head -> data == q1 && head -> next != NULL && head -> next -> data == q2)
      {
         return 1;
      }

      head = head -> next;
      if(head != NULL)
      {
         head = head -> next;
      }
   }

   return 0;
}

void EnqueueEdge(QNodePtr* head, int d1, int d2)
{
   Enqueue(head, d1);
   Enqueue(head, d2);
}

void Enqueue(QNodePtr* head, int data)
{

   QNodePtr newNode = (QNodePtr)malloc(sizeof(QNode));
   newNode -> data = data;
   newNode -> next = NULL;
   if(*head == NULL)
   {
      *head = newNode; 
      return;
   }

   QNodePtr p = (*head);
   while(p -> next != NULL)
   {
      p = p -> next;
   }
   p -> next = newNode;
}

int Dequeue(QNodePtr* head)
{
   if(head == NULL || *head == NULL)
   {
      printf("Invalid head in dequeue\n");
      return -1;
   }

   int retVal = (*head) -> data;
   QNodePtr p = (*head);

   // Move head
   (*head) = p -> next;

   // Break link and free
   p -> next = NULL;
   free(p);

   return retVal;
}

void RemoveEdge(QNodePtr* head, int q1, int q2)
{
   QNodePtr p = (*head);
   QNodePtr q = p -> next;
   while(p != NULL)
   {
      if(p -> data == q1 && q -> data == q2)
      {
         Dequeue(head);
         Dequeue(head);
         return;
      }
      p = p -> next;
   }
}

int IsEmpty(QNodePtr head)
{
   return (head == NULL);
}

void PrintQueue(QNodePtr head)
{
   while(head != NULL)
   {
      printf("%i ", head -> data);
      head = head -> next;
   }
}
