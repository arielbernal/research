#include <stdio.h>
#include <math.h>
#include <stdlib.h>



float avg(float a[3]) {
	return (a[0] + a[1] + a[2]) / 3;
}




int main() {
	// create array
	float myArray[3]; 

	// fill with values
	myArray[0] = 232;
	myArray[1] = 332;
	myArray[2] = 532;

	// calculate avg
	float x = avg(myArray);

	// print avg
	printf("avg of myArray = %f\n", x);

	return 0;
}
