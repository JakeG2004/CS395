#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point
{
   int x;
   int y;
};

typedef struct Point Point;

void PrintPoints(Point* points, int numPoints);
void BubbleSort(Point** points, int numPoints, int swaps);
int FindSide(Point p1, Point p2, Point p3);
void Quickhull(Point* points, int numPoints, Point p1, Point p2, int side, Point** convexHull, int* convexHullIdx);
int LineDist(Point p1, Point p2, Point p3);
void InsertIntoHull(Point** convexHull, int* convexHullIdx, Point point);
void SortCCWFromLeftmost(Point* points, int numPoints);
int CrossProduct(Point a, Point b, Point c);
void BubbleSortAngle(Point* points, int numPoints);
void ReverseArray(Point* points, int numPoints);
Point referencePoint;

int main(int argc, char* argv[])
{
   if((argc - 1) % 2 != 0)
   {
      printf("Invalid number of entries!\n");
      exit(-1);
   }

   int numPoints = (argc - 1) / 2;

   Point* points = (Point*)malloc(sizeof(Point) * numPoints);

   int curPoint = 0;
   for(int i = 1; i < argc; i += 2)
   {
      Point newPoint;
      newPoint.x = atoi(argv[i]);
      newPoint.y = atoi(argv[i + 1]);
      points[curPoint] = newPoint;
      curPoint++;
   }

   BubbleSort(&points, numPoints, 0);

   //PrintPoints(points, numPoints);
   
   Point* convexHull = (Point*)malloc(sizeof(Point) * numPoints);
   int convexHullIdx = 0;
   Quickhull(points, numPoints, points[0], points[numPoints - 1], 1, &convexHull, &convexHullIdx);
   Quickhull(points, numPoints, points[0], points[numPoints - 1], -1, &convexHull, &convexHullIdx);
   
   SortCCWFromLeftmost(convexHull, convexHullIdx);
   ReverseArray(convexHull, convexHullIdx);
   PrintPoints(convexHull, convexHullIdx);
}





void InsertIntoHull(Point** convexHull, int* convexHullIdx, Point point)
{
   for(int i = 0; i < (*convexHullIdx); i++)
   {
      if(((*convexHull)[i].x == point.x) && ((*convexHull)[i].y == point.y))
      {
         return;
      }
   }

   (*convexHull)[*convexHullIdx] = point;
   (*convexHullIdx)++;
}

void Quickhull(Point* points, int numPoints, Point p1, Point p2, int side, Point** convexHull, int* convexHullIdx)
{
   int ind = -1;
   int maxDist = 0;

   for(int i = 0; i < numPoints; i++)
   {
      int tmp = LineDist(p1, p2, points[i]);
      if(FindSide(p1, p2, points[i]) == side && tmp > maxDist)
      {
         ind = i;
         maxDist = tmp;
      }
   }

   if(ind == -1)
   {
      InsertIntoHull(convexHull, convexHullIdx, p1);
      InsertIntoHull(convexHull, convexHullIdx, p2);
      return;
   }

   Quickhull(points, numPoints, points[ind], p1, -1 * FindSide(points[ind], p1, p2), convexHull, convexHullIdx);
   Quickhull(points, numPoints, points[ind], p2, -1 * FindSide(points[ind], p2, p1), convexHull, convexHullIdx);
}

int LineDist(Point p1, Point p2, Point p3)
{
   return abs((p1.y - p2.y) * (p3.x - p2.x) - (p3.y - p2.y) * (p1.x - p2.x));
}

int FindSide(Point p1, Point p2, Point p3)
{
   int val = (p1.y - p2.y) * (p3.x  - p2.x) - (p3.y - p2.y) * (p1.x - p2.x);
   if(val > 0)
   {
      return 1;
   }

   if(val < 0)
   {
      return - 1;
   }

   return 0;
}

void BubbleSort(Point** points, int numPoints, int swaps)
{
   for(int i = 0; i < numPoints - 1; i++)
   {
      if((*points)[i].x > (*points)[i + 1].x)
      {
         Point tmp = (*points)[i + 1];
         (*points)[i + 1] = (*points)[i];
         (*points)[i] = tmp;

         swaps++;
      }

      if((*points)[i].x == (*points)[i + 1].x)
      {
         if((*points)[i].y > (*points)[i+1].y)
         {
            Point tmp = (*points)[i + 1];
            (*points)[i + 1] = (*points)[i];
            (*points)[i] = tmp;

            swaps++;
         }
      }
   }

   if(swaps > 0)
   {
      BubbleSort(points, numPoints, 0);
   }
}

int CrossProduct(Point a, Point b, Point c) {
    // Computes the z-component of the cross product of vectors ab × ac
    int abx = b.x - a.x;
    int aby = b.y - a.y;
    int acx = c.x - a.x;
    int acy = c.y - a.y;
    return abx * acy - aby * acx;
}

void BubbleSortAngle(Point* points, int numPoints) {
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = 1; i < numPoints - 1; i++) {
            int cp = CrossProduct(referencePoint, points[i], points[i + 1]);
            if (cp < 0 || (cp == 0 &&
                (points[i].x - referencePoint.x) * (points[i].x - referencePoint.x) +
                (points[i].y - referencePoint.y) * (points[i].y - referencePoint.y) >
                (points[i+1].x - referencePoint.x) * (points[i+1].x - referencePoint.x) +
                (points[i+1].y - referencePoint.y) * (points[i+1].y - referencePoint.y))) {
                // Swap
                Point temp = points[i];
                points[i] = points[i + 1];
                points[i + 1] = temp;
                swapped = 1;
            }
        }
    }
}

void SortCCWFromLeftmost(Point* points, int numPoints) {
    // Find leftmost (and lowest if tie) point
    int leftmostIdx = 0;
    for (int i = 1; i < numPoints; i++) {
        if (points[i].x < points[leftmostIdx].x ||
           (points[i].x == points[leftmostIdx].x && points[i].y < points[leftmostIdx].y)) {
            leftmostIdx = i;
        }
    }

    // Swap leftmost to index 0
    Point temp = points[0];
    points[0] = points[leftmostIdx];
    points[leftmostIdx] = temp;

    referencePoint = points[0];

    // Sort remaining points counterclockwise
    BubbleSortAngle(points, numPoints);
}

void ReverseArray(Point* points, int numPoints)
{
   Point* tmp = (Point*)malloc(sizeof(Point) * numPoints);
   for(int i = 0; i < numPoints; i++)
   {
      tmp[i] = points[numPoints - 1 - i];
   }

   for(int i = 0; i < numPoints; i++)
   {
      points[i] = tmp[i];
   }
}

void PrintPoints(Point* points, int numPoints)
{
   printf("The points in Convex Hull are:\n");
   
   printf("(%i, %i) ", points[numPoints - 1].x, points[numPoints - 1].y);
   for(int i = 0; i < numPoints; i++)
   {
      printf("(%i, %i) ", points[i].x, points[i].y);
   }

   printf("\n");
}
