/*  Bahman Ashtari, Section 2                          */
/*  Lab 5 using pointers and arrays                    */
/*  A simple driver for testing your sub function      */

#include <stdio.h>
#include <stdlib.h>

/*  a function prototype */
void do_average(int x[], int npts, double *average, int *gtr);

/*--------------------------------------------------------------------*/					 
int main(void)
{
	int c, greater;
	int stuff[]  = {6, 1, 35, 58, 46, 7, 70, 2, 9, 19, 21, 83, 10};
		  /* preset values so focus is on the pointers  */
	int npts = 13;
	double average;


	printf("\n\nBahman Ashtari, Lab 5 output.\n");

	printf("\nThe numbers are:  \n");
	for(c = 0; c < npts;  c++)
	{
		printf("%4i", stuff[c]);
	}
	printf("\n\n");

	do_average(stuff, npts, &average, &greater);
			 /* in     in    output    output   */

	printf("The average is:  %5.2f\n\n", average);
	printf("The number of values > average is:  %2i\n\n",  greater);

	return EXIT_SUCCESS;
}
/*--------------------------------------------------------------------*/
/*                                                                    */
/*  This function returns via pointers, the double average value of a */              
/*  one-dimensional integer array, and number of values in the array  */
/*  that are greater than the average.                                */
void do_average(int x[], int npts, double *average, int *gtr)
{
    int sum = 0, i;
    *gtr = 0;

    for(i=0; i<npts; i++)
	sum += x[i];

    *average = sum /(double) npts;

    for(i=0; i<npts; i++)
	if(x[i] > *average)
	    *gtr += 1;
}
/*--------------------------------------------------------------------*/
