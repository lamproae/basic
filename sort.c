/*
 * =====================================================================================
 *
 *       Filename:  sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/25/16 16:11:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <memory.h>

#define ARRAY_SIZE 200000

#define LLOG_DATE_LEN  32

unsigned int data[ARRAY_SIZE] = { 0 };

int lRandom(int max) {
    return rand() % max;
}

static void initilize() {
    srand(time(0));
    
}

static int Random(int n) {
    int i = 0;
    char *buf = (char *)malloc(n+1);
    int result = 0;
    memset(buf, '\0', n+1);

    for (i; i < n; i++) {
        itoa(rand() % 10, &buf[i], 10);
    }

    result = atoi(buf);
    free(buf);
    return result; 
}

static void generateData() {
    int i = 0;
    for (i; i < ARRAY_SIZE; i++) {
        data[i] = Random(7);
    }
}

static void showData(int *data, int n) {
    int i = 0;
    for (i; i < n; i++) {
        printf("%6d ", data[i]);
        if ((i+1) % 10 == 0 && i != 0)
            printf("\n");
    }
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

static void selectSort() {
    int i = 0;
    int j = 0;
    int tmp = 0;

    for (i; i < ARRAY_SIZE; i++) {
        for (j = i + 1; j < ARRAY_SIZE; j++) {
            if (data[j] < data[i]) {
                tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
    }
}

static void bubbleSort() {
    int i = 0;
    int j = 0;
    int tmp = 0;
    for (i = ARRAY_SIZE - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (data[j+1] > data[j]) {
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }
}

static void insertSort() {
    int i = 0;
    int j = 0;
    int tmp = 0;

    for (i = 1; i < ARRAY_SIZE; i++) {
        tmp = data[i];
        for (j = i; j - 1>= 0 && tmp < data[j-1]; j--) {
            data[j] = data[j-1];
        }
        data[j] = tmp;
    }
}

void Merge(unsigned int srcArr[], unsigned int tmpArr[], int startIndex, int midIndex, int endIndex) {
    int i = startIndex;
    int j = midIndex+1;
    int k = 0;

    while(i <= midIndex && j <= endIndex) {
        if (srcArr[i] < srcArr[j])
            tmpArr[k++] = srcArr[i++];
        else
            tmpArr[k++] = srcArr[j++];
    }

    while(i <= midIndex)
        tmpArr[k++] = srcArr[i++];
    while(j <= endIndex)
        tmpArr[k++] = srcArr[j++];
    for (i = startIndex, k = 0; k < (endIndex - startIndex + 1); i++, k++)
        srcArr[i] = tmpArr[k];
}

void Merge1(unsigned int arr[], int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int p = 0;

    unsigned int *newArr = (unsigned int *)malloc((high-low+1) * sizeof(int));
    assert(newArr != NULL);

    while (i <= mid && j <= high) {
        if (arr[i] < arr[j])
            newArr[p++] = arr[i++];
        else
            newArr[p++] = arr[j++];
    }

    while (i <= mid)
            newArr[p++] = arr[i++];

    while (j <= high)
            newArr[p++] = arr[j++];

    for (i = low, p = 0; p < (high - low + 1); i++, p++)
        arr[i] = newArr[p];
    free(newArr);
}

static int* mergeSort(unsigned int srcArr[], unsigned int tmpArr[], int startIndex, int endIndex) {
    int midIndex;

    if (startIndex == endIndex)
        return;

    if (startIndex < endIndex) {
        midIndex = (startIndex + endIndex) / 2;
        mergeSort(srcArr, tmpArr, startIndex, midIndex);
        mergeSort(srcArr, tmpArr, midIndex+1, endIndex);
        Merge(srcArr, tmpArr, startIndex, midIndex, endIndex);
        //Merge1(srcArr, startIndex, midIndex, endIndex);
    }
}

static int partion(unsigned int unsorted[], int low, int high) {
    int pivot = unsorted[low];
    while(low < high) {
        while(low < high && unsorted[high] > pivot) high--;
        unsorted[low] = unsorted[high];
        while(low < high && unsorted[low] <= pivot) low++;
        unsorted[high] = unsorted[low];
    }

    unsorted[low] = pivot;
    return low;
}

static void quickSort(unsigned int unsorted[], int low, int high) {
    int loc = 0;
    if (low < high) {
        loc = partion(unsorted, low, high);
        quickSort(unsorted, low, loc -1);
        quickSort(unsorted, loc+1, high);
    }
}

static void heapSort() {

}

int main(int argc, char **argv) {
    char buf[LLOG_DATE_LEN] = {0};
    unsigned int tmp[ARRAY_SIZE] = { 0 };
    time_t timer;
    struct tm *tblock;

    initilize();
    generateData();
    showData(data, ARRAY_SIZE);
    timer=time(NULL);
    tblock = localtime(&timer);
    printf("-------------------start: %s-------------------\n", asctime(tblock));
    //bubbleSort();
    quickSort(data, 0, ARRAY_SIZE -1);
    //selectSort();
    //showData(data, ARRAY_SIZE);
    //mergeSort(data, tmp, 0, ARRAY_SIZE - 1);
    //insertSort();
    //showData(data, ARRAY_SIZE);
    timer=time(NULL);
    tblock = localtime(&timer);
    printf("---------------------end: %s-------------------\n", asctime(tblock));
    //quickSort(data, 0, ARRAY_SIZE -1);
    //showData(data, ARRAY_SIZE);
}
