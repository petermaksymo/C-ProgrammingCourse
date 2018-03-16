#include <stdio.h>
#include <math.h>

int main(void)
{
    float numberOne, numberTwo, numberThree, mean, stdev;
	printf("Enter three numbers: ");
    scanf("%f%f%f",&numberOne, &numberTwo, &numberThree);
	
	//calculates the mean and then the standard deviation
    mean = (numberOne+numberTwo+numberThree)/3;
    stdev = sqrt((pow((numberOne-mean),2)+pow((numberTwo-mean),2)+pow((numberThree-mean),2))/2);
	
    printf("The mean is %.2lf and the standard deviation is %.2lf\n", mean,stdev);
	return 0;
}
