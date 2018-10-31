#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
//Output: the file OutputFilename containing the sorted dataset.

int writeDataset(int DataSetSize, char *filename);
int loadDataset (int DataSetSize, char *filename);
void swap(int *xp, int *yp);
void selectionSort(int arr[], int n);
float generateRand(int rmax);

int i;


int main(int argc, char *argv[]) {
	 // load the dateset in the memory area addressed by ds
	 // ds = loadDataset(dataset,DataSetSize,Buffersize);
	 // compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	 //avg = average(ds)
	 // find the max value in the dataset
	 //max = maxvalue(ds)
	 // find the min value in the dataset
	 //min = minvalue(ds)
	 //sort the dataset and copy it into the memory area pointed by sds
	 //sds = sortDataset(ds,sortingAlgorithm);
	 //write the sorted array into a new file plus the valies of the average, min and max as the first three records.
	 //writeDataset(OutputFilename,sds,Buffersize, avg, min, max)
}

//this code is an example of how to read a file in C
int loadDataset (int DataSetSize, char *filename) {
	FILE *fp;
	float *v;

	fp = fopen( filename , "r" );

	for( i=1; i<=DataSetSize; i++){
		fread(v[i] , 1 , sizeof(float) , fp );
	}

	// TIP you can define you own buffer, buffer size and you can read blocks of data of size > 1
	fclose(fp);
}

int writeDataset (int DataSetSize, char *filename)
{
	FILE *fp;
	float *v;
	fp = fopen( filename , "w" );
	
	for( i=1; i<=DataSetSize; i++){
		fwrite(v[i] , 1 , sizeof(float) , fp );
	}
	
	// TIP you can define you own buffer, buffer size and you can write blocks of data of size > 1
	fclose(fp);
	return(0);
}

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;
				// Swap the found minimum element with the first element
				swap(&arr[min_idx], &arr[i]);
	}
}

float generateRand(int rmax) {
	//Generate a floating point random number between 0 and rmax
	srand((unsigned int)time(NULL)); //initialize the random number generator
	return ( (float)rand()/(float) RAND_MAX ) * rmax;
}


