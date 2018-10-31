#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define SOURCE_FILE "sourceList.data"
#define DESTINATION_FILE "sortedList.data"
#define WRITE "wb"
#define READ "rb"
#define APPEND "ab"
#define QUICKSORT 1
#define INSERTIONSORT 2
#define GENERATE 1
#define FROMFILE 2


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
void readOptions(int *argc, char **argv);
void printlist(float *dataset);
void swap(float *a, float *b);
void printHelpText();
void blankline();

int i, SIZE = 102400, ALG = 2, DATA_SOURCE = 1, PRINT_LIST = 1;

int main(int argc, char *argv[]) {
	readOptions(&argc, argv);

	float dataset[SIZE];

	blankline();

	if(DATA_SOURCE == GENERATE){
		printf(">* Creating dataset\n");
		generateDataset(dataset, SIZE, 100);
	}else{
		printf(">* Loading dataset from file\n");
		loadDataFromFileToMemory(dataset, SOURCE_FILE,SIZE);
	}

	blankline();

	printlist(dataset);
	
	printf("** Average value is \t%lf\n", getAverage(dataset, SIZE));
	printf("** Minimum value is \t%lf\n", getMinValue(dataset, SIZE));
	printf("** Maximum value is \t%lf\n", getMaxValue(dataset, SIZE));

	blankline();
	
	if(ALG==QUICKSORT){
		printf(">* Performing quick sort\n");
		quickSort(dataset, 0, SIZE);
	}else{
		printf(">* Performing insertion sort\n");
		insertionSort(dataset, SIZE);
	}

	blankline();
	
	printlist(dataset);

	printf(">* Writing back dataset to file\n");
	writeDatasetToFile(SIZE, dataset, DESTINATION_FILE);

	blankline();
	return 0;
}

void readOptions(int *argc, char **argv){
	int option;

	while ((option = getopt (*argc, argv, "hn:a:d:p:")) != -1){
		switch(option){
			case 'h':
				printHelpText();
				break;
			case 'n':
				SIZE = atoi(optarg);
				break;
			case 'a':
				ALG = atoi(optarg);
				break;
			case 'd':
				DATA_SOURCE = atoi(optarg);
			case 'p':
				PRINT_LIST = atoi(optarg);
				break;
			default:
				break;
		}
	}
}

void printHelpText(){
	printf("\n");
	printf("Welcome to ReSoW\n");
	printf("Options include:\n");
	printf("  -h 			 Get instructions.\n");
	printf("  -d [ 1 | 2 ]	\t Set data source for the operation. Options include [1 = generate new dataset, 2 = load dataset from file]. Default is 1\n");
	printf("  -p [ 1 | 2 ]	\t Prints the list. Options include [1 = print list, 2 = do not print list]. Default is 1\n");
	printf("  -a [ 1 | 2 ]	\t Define the sorting algorithm to use. Options include [1 = QUICKSORT, 2 = INSERTIONSORT]. Default is 2\n");
	printf("  -n <size>		 Indicates the size of the dataset to be used. Default is 102400\n");
	printf("\n");
	exit(3);
}

float getAverage(float *dataset, int size){
	float total = 0.0;

	for (i = 0; i < size; i++)
	{
		total+=dataset[i];
	}

	return total/size;
}

float getMinValue(float *dataset, int size){
	float min = dataset [0];

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

	for (i = 1; i < size; ++i)
	{
		if(dataset[i]>max){
			max = dataset[i];
		}
	}

	return max;
}


void generateDataset(float *dataset, int datasetSize, int maxNumber){
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
	int j;

	i = (low-1);

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
		int pivot = partition(dataset, low, high);
		quickSort(dataset, low, pivot-1);
		quickSort(dataset, pivot+1, high);
	}
}

void insertionSort(float *dataset, int noOfItems){
	float key;
	int j;

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

void blankline(){
	printf("\n");
}

void printlist(float *dataset){
	if(PRINT_LIST==1){
		for(i=0; i<SIZE; i++){
			printf("%lf\t", dataset[i]);
		}

		blankline();
		blankline();
	}
}