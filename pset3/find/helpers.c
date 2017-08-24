#include <cs50.h>
#include "helpers.h"
bool search(int value, int values[], int n)
{

    int start = 0;
    int end = n -1;
   
    while(end >= start)
    {
        int mid = (end + start) /2;
        if (values[mid] == value)
            return true;
        if (start == end && values[start] != value)
            return false;
        else if (values[mid] < value)
            start = mid + 1;
        else
            end = mid - 1;
    }
    
    return false;
}


void sort(int values[], int n)
{
    
    for (int i = 0; i < n - 1; i++)
    {
        int index = i;  
        
        for (int j = i + 1; j < n; j++)
        {   
            if (values[index] > values[j])
                index = j; 
        }
    int temp = values[i];
    values[i] = values[index];
    values[index] = temp; 
    }
    return;
}