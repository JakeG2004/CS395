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
//void PrintMatches(int matches[], int nMatches, int numV);
void RemoveEdge(QNodePtr* head, int q1, int q2);

int** MakeAdjMatrix(int dimension, char* argv[]);
int IsBipartite(int** matrix, int S, int dimension);
int* Neighbors(int v, int** arr, int dimension, int* neighborCount);

int main(int argc, char* argv[])
{
   if(argc < 2)
   {
      printf("Invalid usage!\n");
      exit(-1);
   }

   int dimension = atoi(argv[1]);

   int** adjMatrix = MakeAdjMatrix(dimension, argv);

   for(int i = 0; i < dimension; i++)
   {
      for(int j = 0; j < dimension; j++)
      {
         printf("%i ", adjMatrix[i][j]);
      }

      printf("\n");
   }

   int S = 0;
   for(int i = 0; i < dimension; i++)
   {
      if(adjMatrix[0][i] == 1)
      {
         S = i;
         break;
      }
   }

   if(IsBipartite(adjMatrix, S, dimension) == 1)
   {
      printf("Graph is Bipartite\n");
   }

   else
   {
      printf("Graph is NOT Bipartite\n");
   }
}

int IsBipartite(int** matrix, int S, int dimension)
{
   // Create empty queue
   QNodePtr r = NULL;

   // Array to keep track of colors
   int* colors = (int*)malloc(sizeof(int) * dimension);
   for(int i = 0; i < dimension; i++)
   {
      colors[i] = -1;
   }

   colors[S] = 1;

   // Put that thang in there
   Enqueue(&r, S);

   while(!IsEmpty(r))
   {
      int n1 = Dequeue(&r);
      
      int nNeighbors = 0;
      Neighbors(n1, matrix, dimension, &nNeighbors);

      for(int n2 = 0; n2 < nNeighbors; n2++)
      {
         if(matrix[n1][n2] != 1)
         {
            continue;
         }

         if(colors[n2] == -1)
         {
            if(colors[n1] == 1)
            {
               colors[n2] = 0;
            }

            else
            {
               colors[n2] = 1;
            }

            Enqueue(&r, n2);
         }

         else
         {
            if(colors[n2] == colors[n1])
            {
               return 0;
            }
         }
      }
   }

   return 1;
}

// Get the list of neighbors for a given node
int* Neighbors(int v, int** arr, int dimension, int* neighborCount)
{  
   int* neighbors = (int*)malloc(sizeof(int) * dimension);
   int count = 0;
   
   for(int i = 0; i < dimension; i++)
   {  
      if(arr[v][i] == 1)
      {  
         neighbors[count++] = i;
      }
   }
   
   *neighborCount = count;
   return neighbors;
}


int** MakeAdjMatrix(int dimension, char* argv[])
{
   int** matrix = (int**)malloc(sizeof(int*) * dimension);

   for(int i = 0; i < dimension; i++)
   {
      matrix[i] = (int*)malloc(sizeof(int) * dimension);
   }

   int curIndex = 2;
   for(int i = 0; i < dimension; i++)
   {
      for(int j = i; j < dimension; j++)
      {
         if(i == j)
         {
            matrix[i][j] = 0;
            continue;
         }

         matrix[i][j] = atoi(argv[curIndex]);
         matrix[j][i] = atoi(argv[curIndex]);

         curIndex++;
      }
   }

   return matrix;
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
    // Ensure the queue is not empty
    if (*head == NULL) return;
    
    QNodePtr p = *head;
    QNodePtr prev = NULL;  // To keep track of the previous node
    
    while (p != NULL && p->next != NULL)
    {
        // Check for q1, q2 pair
        if ((p->data == q1 && p->next->data == q2) || (p->data == q2 && p->next->data == q1))
        {
            // If removing the first two nodes
            if (prev == NULL) {
                *head = p->next->next; // Update head to the node after the next one
            } else {
                prev->next = p->next->next; // Skip the two nodes
            }

            // Free the memory of the two nodes being removed
            free(p->next);  // Free the second node in the pair
            free(p);        // Free the first node in the pair
            
            return;  // After removal, we exit the function
        }
        
        // Move to the next node in the queue
        prev = p;
        p = p->next;
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
      printf(" %i", head -> data);
      head = head -> next;
   }
}
