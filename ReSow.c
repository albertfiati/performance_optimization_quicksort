#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SOURCE_FILE "sourceList.data"
#define DESTINATION_FILE "sortedList.data"
#define WRITE "wb"
#define READ "rb"
#define APPEND "ab"


//Input: DataSetSize, BufferSize, DatasetFilename, OutputFilename
//Output: the file OutputFilename containing the sorted dataset.

void loadDataFromFileToMemory(float *buffer, char *filename, int noOfItems);
int writeDatasetToFile(int datasetSize, float *dataset, char *filename);
void generateDataset(float *dataset, int datasetSize, int maxNumber);
void quickSort(float *dataset, int low, int high);
void insertionSort(float *dataset, int noOfItems);
int partition(float *dataset, int low, int high);
float getMinValue(float *dataset, int size);
float getMaxValue(float *dataset, int size);
float getAverage(float *dataset, int size);
void swap(float *a, float *b);


int main(int argc, char *argv[]) {
	printf("%s\n", "Creating dataset");
	int i, SIZE = 5;

	float dataset[SIZE];
	generateDataset(dataset, SIZE, 100);

	printf("\n%s\n", "Loading dataset from file");
	loadDataFromFileToMemory(dataset, SOURCE_FILE,SIZE);
	printf("\n");
	printf("%s\n", "Unsorted dataset");

	for(i=0; i<SIZE; i++){
		printf("%lf\t", dataset[i]);
	}

	printf("\n");
	printf("\n");
	
	printf("** Average value is \t%lf\n", getAverage(dataset, SIZE));
	printf("** Minimum value is \t%lf\n", getMinValue(dataset, SIZE));
	printf("** Maximum value is \t%lf\n", getMaxValue(dataset, SIZE));

	printf("\n");
	printf("\n%s\n", "Sorted dataset");
	//quickSort(dataset, 0, SIZE-1);
	insertionSort(dataset, SIZE);
	
	for(i=0; i<SIZE; i++){
		printf("%lf\t", dataset[i]);
	}
	
	printf("\n");
	printf("%s\n", "Writing back dataset to file");
	writeDatasetToFile(SIZE, dataset, DESTINATION_FILE);

	printf("\n");
	return 0;
}

float getAverage(float *dataset, int size){
	float total = 0.0;
	int i;

	for (i = 0; i < size; i++)
	{
		total+=dataset[i];
	}

	return total/size;
}

float getMinValue(float *dataset, int size){
	float min = dataset [0];
	int i;

	for (i = 1; i < size; ++i)
	{
		if(dataset[i]<min){
			min = dataset[i];
		}
	}

	return min;
}

float getMaxValue(float *dataset, int size){
	float max = dataset [0];
	int i;

	for (i = 1; i < size; ++i)
	{
		if(dataset[i]>max){
			max = dataset[i];
		}
	}

	return max;
}


void generateDataset(float *dataset, int datasetSize, int maxNumber){
	int i;
	time_t t;

	srand((unsigned int)time(&t));

	for(i=0; i<datasetSize; i++){
		dataset[i] = ((float)rand()/(float)RAND_MAX) * maxNumber;
	}

	writeDatasetToFile(datasetSize, dataset, SOURCE_FILE);
}

int writeDatasetToFile(int datasetSize, float *dataset, char *filename){
	FILE *fp = NULL;
	fp = fopen(filename, WRITE);
	
	if(fp==NULL){
		printf("\nFailed to open file\n");
		exit(0);
	}
	
	fwrite(dataset, sizeof(float), datasetSize, fp);
	fclose(fp);

	return 0;
}

void loadDataFromFileToMemory(float *buffer, char *filename, int noOfItems){
	FILE *fp = NULL;
	fp = fopen(filename, READ);

	if(fp==NULL){
		printf("\nFailed to open file: %s\n", filename);
		exit(0);
	}

	fseek(fp, 0, SEEK_SET);
	fread(buffer, sizeof(float), noOfItems, fp);
	fclose(fp);
}

void swap(float *a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

int partition(float *dataset, int low, int high){
	int pivot = dataset[high];
	int i = (low-1);
	int j;

	for(j = low; j <= high-1; j++){
		if(dataset[j] <= pivot){
			i++;
			swap(&dataset[i],&dataset[j]);
		}
	}

	swap(&dataset[i + 1],&dataset[high]);
	return (i + 1);
}

void quickSort(float *dataset, int low, int high){
	if(low < high){
		int pivot = partition(dataset, 0, high);
		quickSort(dataset, low, pivot-1);
		quickSort(dataset, pivot+1, high);
	}
}

void insertionSort(float *dataset, int noOfItems){
	int i, key, j;

	for(i = 1; i<noOfItems; i++){
		key = dataset[i];
		j = i-1;

		while(j>=0 && dataset[j]>key ){
			dataset[j+1] = dataset[j];
			j = j-1;
		}

		dataset[j+1] = key;
	}
}
