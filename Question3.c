/******************************************************************************
Question 3:

Implement a function able to calculate and return the average, maximum and minimum value of 
an array with “n” positions. This function must also return a copy of the input array containing only 
the even numbers of the original array, as well as the new array size. Implement this logic using 
the C language and share this code through a public repository on GitHub.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define LOG 1

typedef struct array_data
{
    int16_t min ;
    int16_t max ;
    float average ;
    int16_t *even_array;
    uint16_t even_array_size;
}array_data_t;

array_data_t ArrayDataCalculator(int16_t * array, uint16_t array_size)
{
    /* Local Variables */
    array_data_t local_result;
    
    /* Local Variables initialization */
    local_result.even_array_size = 0;
    local_result.average = 0;
    local_result.min = array[0];
    local_result.max = array[0];
    
    /* Logic */
    
    for(int i =0; i<array_size;i++)
    {
        local_result.average += array[i];
        
        local_result.max = MAX(local_result.max,array[i]);
        local_result.min = MIN(local_result.min,array[i]);
        
        if (array[i]%2==0)
        {
            local_result.even_array_size++;
            
            if(local_result.even_array_size==1)
            {
                local_result.even_array = malloc(sizeof(int16_t));
            }
            else
            {
                local_result.even_array = realloc(local_result.even_array,sizeof(int16_t));
            }
            
            local_result.even_array[local_result.even_array_size-1] = array[i];
        }
    }
    
    local_result.average = local_result.average/array_size;
    
    return local_result;
    
}

int main()
{
    /* Local Variables */
    array_data_t result;
    int16_t array[]={1,2,4,3,6};
    

    /* Logic */
    result = ArrayDataCalculator(array,(sizeof(array)/sizeof(int16_t)));
    

    /* Log */
#if(LOG == 1)
    printf("Even Array : ");
    for(int i=0; i<result.even_array_size;i++)
    {
        printf("%d  ",result.even_array[i]);
    }
    
    printf("\nMAX = %d",result.max);
    printf("\nMIN = %d",result.min);
    printf("\nAverage = %f",result.average);
    printf("\nNew Size = %d",result.even_array_size);
#endif
   

    return 0;
}
