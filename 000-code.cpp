#include "splashkit.h"
using namespace std;

#define NUM_VALS 100
//The link to the screen cap: https://www.youtube.com/watch?v=37y2-h3f7Qg
void draw_values(const int values[], int size) 
{
    int x = 0;
    int y;
    int rect_height;
    int rect_width = screen_width() / size;

    for (int i = 0; i < size; i++)
    {
        rect_height = values[i];
        y = screen_height() - rect_height;
        fill_rectangle(COLOR_RED, x, y, rect_width, rect_height);
        draw_rectangle(COLOR_WHITE, x, y, rect_width, rect_height);
        
        x += rect_width;
    }
}
void swap(int &value1 , int &value2)
{
    int temp = 0;
    temp = value1; 
    value1 = value2; 
    value2 = temp; 
}

void draw_sort(int values[], int size)
{

    clear_screen(COLOR_WHITE);
    draw_values(values, size);
    refresh_screen(60);
}

void bubble_sort(int values[], int size)
{
    for(int j = 0 ; j < size ; j++)
    {
        for (int i = 0 ; i < size - 1 ; i++)
        {
            if(values[i] > values[i+1])
        {
            swap(values[i] , values[i+1]);
            draw_sort(values,size);
        }
    }
    }
}


/*This function recursively takes in the values array and recursively arranges the array*/
void heapify(int values[], int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && values[l] > values[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < n && values[r] > values[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
        swap(values[i], values[largest]);
 
        // Recursively heapify the affected sub-tree
        heapify(values, n, largest);
    }
}

/* The heapsort algorithm works by creating a heap of elements with each parent element
has a right and a left branch. The ultimate goal of heapsort is to rearrange the array
multiple times in a way that the parent element is always greater than the children elements.
Thus after each iteration the largest element is replaced with the last element in the array
and is pushed out of the heap in a sorted array.*/

void heap_sort(int values[], int size)
{
    // Build heap (rearrange array)
    for (int i = size - 1; i >= 0; i--)
    {    
        heapify(values, size, i);
        
    }
 
    // One by one extract an element from heap

    for (int i=size-1; i>=0; i--)
    {
        // Move current root to end
        swap(values[0], values[i]);
 
        // call max heapify on the reduced heap
        heapify(values, i, 0);
        draw_sort(values,size);
    }
}



void random_fill_array(int values[], int size)
{
    for (int i = 0; i < size; i++) 
    {
        values[i] = rnd(screen_height()) + 1;
    }
}

void handle_input(int values[], int size)
{
    if (key_typed(R_KEY))
    {
        random_fill_array(values, size);
    }
    else if(key_typed(S_KEY))
    {
        bubble_sort(values,size);
    }
    else if(key_typed(D_KEY))
    {
        heap_sort(values,size);
    }
}

int main()
{
    int values[NUM_VALS];

    open_window("Sort Visualiser", 800, 600);
   
    random_fill_array(values, NUM_VALS);

    while ( not quit_requested() )
    {
        process_events();
        handle_input(values, NUM_VALS);
        
        draw_sort(values, NUM_VALS);
    }

    return 0;
}