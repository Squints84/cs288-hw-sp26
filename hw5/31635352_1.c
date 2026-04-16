#include <stdio.h>
#define MAX 100

// radix sort from class
void radix_sort(unsigned int A[], unsigned int n)
{
	unsigned int bucket0[MAX], bucket1[MAX];
	unsigned int mask, count0, count1;
	for (int d=0; d < 32; d++){ //  iterating thru the bits from least to most
		mask = 1 << d;
		count0 = count1 = 0;
		for (int i =0; i<n;i++) {// iterating thru the arr A
			if ((A[i] & mask) == 0)
			{
				bucket0[count0++] = A[i];
			}
			else
			{
				bucket1[count1++] = A[i];
			}
		}

		for (int i = 0; i < count0; i++)
		{
			A[i] = bucket0[i];
		}
		
		for (int i = 0; i < count1; i++)
		{
			A[i+count0] = bucket1[i];
		}
	}
	
}

void combine_arrays(float A[], unsigned int n)
{
    unsigned int positive[MAX], negative[MAX];
    unsigned int positive_count = 0, negative_count = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int *p = (unsigned int *)&A[i];
        if (A[i] >= 0)
        {
            positive[positive_count++] = *p;
        }
        else
        {
            unsigned int negative_value = *p ^ 0xFFFFFFFF;
            negative[negative_count++] = negative_value;
        }
    }

    radix_sort(positive, positive_count);
    radix_sort(negative, negative_count);

    for (unsigned int i = 0; i < negative_count; i++)
    {
        unsigned int negative_value = negative[i] ^ 0xFFFFFFFF;
        float *f = (float *)&negative_value;
        A[i] = *f;
    }
    for (unsigned int i = 0; i < positive_count; i++)
    {
        float *f = (float *)&positive[i];
        A[i+negative_count] = *f;
    }
}



int main() {
    unsigned int elements, i = 0;
    printf("Enter the number of floats to be sorted:");
    if (scanf("%u", &elements) != 1 || elements > 100 || elements <= 0) {
        printf("Invalid input, must be between 1 and 100 \n");
        return 1;
    }
    float arr[elements];
    while (i < elements){
    	printf("Enter your number: ");
        if (scanf("%f", &arr[i]) != 1) {
            printf("Invalid input\n");
            return 1;
        }
        i++;
    }

    printf("Before:\n");
    for (unsigned int i = 0; i < elements; i++) {
        printf("%f\n", arr[i]);
    }

    printf("After:\n");
    combine_arrays(arr, elements);
    for (unsigned int i = 0; i < elements; i++) {
        printf("%f\n", arr[i]);
    }
    
    return 0;
}