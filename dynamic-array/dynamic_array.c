#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct
{
    int len; // current usage of the array
    int capacity; // actual capacity
    int *arr;
}
array;

// define prototypes of the functions
array init(int len);
int size(array arr);
bool is_empty(array arr);
int get(array arr, int index);
void set(array *arr, int index, int num);
void clear(array arr);
void add(array *arr, int num);
int rm_at(array *arr, int index);
bool rm(array *arr, int num);
int index_of(array arr, int num);
int contains(array arr, int num);

int main(void)
{
    array arr = init(2);
    arr.arr[0] = 5;
    arr.arr[1] = 3;

    printf("%d\n", arr.arr[0]);
    printf("size: %d\n", size(arr));
    printf("is empty: %d\n", is_empty(arr));
    printf("get: %d\n", get(arr, 1));
    set(&arr, 1, 8);
    printf("set: %d\n", arr.arr[1]);
    add(&arr, 9);
    printf("add: %d, capacity: %d, len: %d\n", arr.arr[2], arr.capacity, arr.len);
    add(&arr, 2365);
    printf("add: %d, capacity: %d, len: %d\n", arr.arr[3], arr.capacity, arr.len);
    add(&arr, 1000);
    printf("add: %d, capacity: %d, len: %d\n", arr.arr[4], arr.capacity, arr.len);
    for (int i = 0; i < arr.len; i++)
    {
        printf("%d\n", arr.arr[i]);
    }

    printf("rm_at: %d\n", rm_at(&arr, 3));
    printf("rm: %d\n", rm(&arr, 9));

    add(&arr, 6256);
    add(&arr, 26);
    add(&arr, 85);
    add(&arr, 95);
    rm(&arr, 85);

    for (int i = 0; i < arr.len; i++)
    {
        printf("%d\n", arr.arr[i]);
    }

    printf("index of: %d\n", index_of(arr, 95));
    printf("index of: %d\n", index_of(arr, 6));
    printf("contains: %d\n", contains(arr, 6256));
    printf("contains: %d\n", contains(arr, 6));

    clear(arr);
}

/* initialize the array with given capacity*/
array init(int capacity)
{
    array arr;
    arr.capacity = capacity;
    arr.len = capacity;
    arr.arr = malloc(sizeof(int) * arr.capacity);
    return arr;
}

/* Return the lenght of the array*/
int size(array arr)
{
    if (arr.len > 0)
    {
        return arr.len;
    }
    else
    {
        return -1;
    }
}

// return true or false
bool is_empty(array arr)
{
    if (size(arr) != -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// return the number in the given index
int get(array arr, int index)
{
    return arr.arr[index];
}

// set element in the given index
void set(array *arr, int index, int num)
{
    arr->arr[index] = num;
}

// free the array
void clear(array arr)
{
    free(arr.arr);
}

// add new value to end of the array
void add(array *arr, int num)
{
    // if there is enough capacity for new number
    if (arr->len+1 < arr->capacity+1)
    {
        arr->arr[arr->len] = num;
        arr->len++;
    }
    // if capacity is not enough
    else
    {
        // multiply capacity with two
        arr->capacity *= 2;

        // realloced memory for array
        arr->arr = realloc(arr->arr, sizeof(int) * arr->capacity);

        // add new number to the array
        arr->arr[arr->len] = num;

        // increment the length of the array
        arr->len++;
    }

}

/* Remove the number at the given index */
int rm_at(array *arr, int index)
{
    // get the number that want to be deleted
    int data = arr->arr[index];

    // create temp array
    array temp = init(arr->len - 1);

    // copy all number to the temp array except the number that is gonna be removed
    for (int i = 0, j = 0; i < arr->len; i++)
    {
        if (i != index)
        {
            temp.arr[j] = arr->arr[i];
            j++;
        }
    }

    // free the old array
    free(arr->arr);

    *arr = temp;
    return data;
}

/* Remove the given number if exist */
bool rm(array *arr, int num)
{
    for (int i = 0; i < arr->len; i++)
    {
        // find the index of the element that gonna be removed
        if (arr->arr[i] == num)
        {
            rm_at(arr, i);
            // if number is in the array remove it and return true
            return true;
        }
    }
    // if number is not in the array return false
    return false;
}

/* Return the index of the given number */
int index_of(array arr, int num)
{
    for (int i = 0; i < arr.len; i++)
    {
        // if num is in the array return the index
        if (num == arr.arr[i])
        {
            return i;
        }
    }
    // return -1 if num is not in the array
    return -1;
}

int contains(array arr, int num)
{
    return index_of(arr, num) != -1;
}
