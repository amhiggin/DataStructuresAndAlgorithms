/*
*	@author Amber Higgins, 13327954
*	Assignment 2: Sorting Algorithms
*	MergeSort and QuickSort are implemented and compared in terms of probes and time taken.
*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//globals
#define SIZE 100
int mergeArray[SIZE], quickArray[SIZE];	
int mergeProbe=0, quickProbe=0;
//mergesort functions
void mergeSort(int array[], int temp[], int left, int right);
void merge(int a[], int tmp_list[], int left, int mid, int right);
//quicksort functions
void swap(int *x, int *y); //to swap two values
void quickSort(int array[], int m, int n);
//print the array once sorted
void printSortedArray(int sorted_array[], int probe, double time);

int main(){
	srand(time(NULL));
	int array[SIZE];
	printf("\n--------\nOriginal array:\n");
	for(int i=0; i<SIZE;i++){
		//randomly generate integer elements and assign to the array
		array[i] = rand()%100000; //something like this
		//make a unique version of the array for each function
		mergeArray[i] = array[i];
		quickArray[i] = array[i];
		printf("%i ", array[i]);
	}
	//sort the array using both sorting functions
	int time=clock();//start the timer
	mergeSort(array, mergeArray, 0, SIZE-1);
	time=clock()-time; //stop the timer
	double seconds=((double)time)/CLOCKS_PER_SEC;
	printf("\n\n-------\nMergeSorted array is:\n");
	printSortedArray(mergeArray, mergeProbe, seconds);

	time=clock();
	quickSort(quickArray, 0, SIZE-1);
	time=clock() -time;
	seconds=((double)time)/CLOCKS_PER_SEC;
	printf("\n-------\nQuickSorted array is:\n");
	printSortedArray(quickArray, quickProbe, seconds);

	//getchar();
	return 0;
}

//mergesort function
void mergeSort(int array[], int temp[], int left, int right){
	int pivot;
	if(right>left){
		//get the midpoint of the current array
		pivot = (right+left)/2;
		//call mergesort for the left sublist
		mergeSort(array, temp, left, pivot);
		//call mergesort for the right sublist
		mergeSort(array, temp, pivot+1, right);
		//merge the final two sorted arrays
		merge(array, temp, left, pivot+1, right);
	}
}

//given two sublists, and the leftmost and rightmost nodes and pivot, sort the two lists andmerge them
void merge(int a[], int tmp_list[], int left, int pivot, int right){
	//last element of left sublist
	int left_endpoint=pivot-1;
	int tmp=left;
	int count=right-left+1;//num of elements we are dealing with
	
	//divide and conquer
	while((left<=left_endpoint)&&(pivot<=right)){
		if (a[left] <= a[pivot]){ 
			//then store the value at left index of array at the current position of the temp array
			tmp_list[tmp] = a[left];
			tmp++;
			left++;
		} else {
			//store rightmost value at current position of temp array
			tmp_list[tmp] = a[pivot];
			tmp++;
			pivot++;
		}
	} 
	//while we still have elements in the left sublist
	while(left<=left_endpoint){
		//store leftmost value at the current pos of temp array
		tmp_list[tmp]=a[left];
		left++;
		tmp++;
		mergeProbe++;
	} 
	//while we still have elements in the right sublist
	while(pivot<=right){
		//store rightmost value at the current pos of temp array
		tmp_list[tmp] = a[pivot];
		pivot++;
		tmp++;
		mergeProbe++;
	}
	
	//copy the sorted array back into the original array
	for(int i=0;i<=count;i++){
		a[right]=tmp_list[right];
		right--;
	}
}

//simple function to swap two elements
void swap(int* x, int* y){
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

//quicksort function
void quickSort(int array[], int left, int right){
	int key, i, j, pivot;
	if(left<right){//while we still have a valid list to sort, DIVIDE AND CONQUER!
		pivot = (left+right)/2;
		//swap the leftmost element in the sublist with the value at the pivot position
		swap(&array[left],&array[pivot]);
		key=array[left];
		i=left+1;//start going from lhs
		j=right;//start going on the other side from rhs
		while(i<=j){//while still haven't gone through whole sublist
			//so long as the current element is <= the pivot, keep going through from left
			while((i<=right)&&(array[i]<=key)){
				i++;
				quickProbe++;
			}
			//so long as the current element is > the pivot, keep going through from right
			while((j>=left)&&(array[j]>key)){
					j--;
					quickProbe++;
				}
				if(i<j)//not in order - swap!
					swap(&array[i], &array[j]);
			}
			//swap pivot ith array[j]
			swap(&array[left], &array[j]);
			//keep sorting the sublists
			quickSort(array, left, j-1);
			quickSort(array, j+1, right);
		}	
	}
//prints out the array passed in
void printSortedArray(int sorted_array[], int probe, double time){
		for(int i=0; i<SIZE; i++){
			printf("%i ", sorted_array[i]);
		}
		//print a newline
		printf("\nNumber of probes was: %i \n", probe);
		printf("It took %lf s\n", time);
	}
