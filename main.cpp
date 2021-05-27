#include<iostream>
#include<fstream>
#include<climits>
using namespace std;

void swap(int *x, int *y);

// A class for Min Heap
class MinHeap
{
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);

    MinHeap(const MinHeap& h)
    {

        this->heap_size=h.heap_size;
        this->capacity=h.capacity;
        this->harr = new int[h.capacity];
        for(int i=0; i<h.capacity; i++)
            this->harr[i]=h.harr[i];
    }

    // to heapify a subtree with the root at given index
    void MinHeapify(int );

    int parent(int i)
    {
        return (i-1)/2;
    }

    // to get index of left child of node at index i
    int left(int i)
    {
        return (2*i + 1);
    }

    // to get index of right child of node at index i
    int right(int i)
    {
        return (2*i + 2);
    }

    // to extract the root which is the minimum element
    int extractMin();
    int predecesor(int x);
    int succesor(int x);

    int kElement(int k)
    {
        MinHeap a(*this);
        while(k>1)
        {
            a.extractMin();
            k--;
        }
        return a.getMin();
    }
    int cardinal()
    {
        return heap_size;
    }
    bool esteInS(int x);



    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    // Returns the minimum key (key at root) from min heap
    int getMin()
    {
        return harr[0];    ///3
    }
    int getMax();///4

    // Deletes key i
    void deleteKey(int i);///2

    void clear()
    {
        this->heap_size=0;
    }

    // Inserts a new key 'k'
    void insertKey(int k);///1
    ~MinHeap()
    {
        if(this->harr!=NULL)
            delete[] harr;
    }
};


bool MinHeap::esteInS(int x)
{
    for(int i=0;i<this->heap_size;i++){
        if(harr[i]==x)
            return 1;
    }
    return 0;

}

int MinHeap::succesor(int x)
{
    int succ=INT_MAX;
    for(int i=0; i<heap_size; i++)
        if(harr[i]<succ && harr[i]>x )
            succ=harr[i];
    return succ;
}

int MinHeap::predecesor(int x)
{
    int prec=INT_MIN;
    for(int i=0; i<heap_size; i++)
        if(harr[i]>prec && harr[i]<x )
            prec=harr[i];
    return prec;
}


int MinHeap::getMax()
{
    int max=INT_MIN;
    for(int i=0; i<heap_size; i++)
        if(harr[i]>max)
            max=harr[i];
    return max;


}

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int x)
{
    int i;
    for(i=0; i<heap_size; i++)
        if(harr[i]==x)
            break;
    decreaseKey(i, INT_MIN);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}



// Driver program to test above functions
int main()
{
    MinHeap h(10000);

        char nume_fisier[9]="date1.in";
        char out_fisier[10]="date1.out";
        for(int i=1;i<6;i++)
        {
            int x;
            nume_fisier[4]='0'+i;
            out_fisier[4]='0'+i;
            ifstream f(nume_fisier);
            ofstream g(out_fisier);

            while(f>>x)
                h.insertKey(x);
   g<<"Numarul de elemente este:"<<h.cardinal()<<'\n';
   g<<"Testul numarul:"<<i<<'\n';
   g<<"Minimul este:"<<h.getMin()<<'\n';
   g<<"Stergem minimul"<<'\n';
   h.deleteKey(h.getMin());
   g<<"Minimul este:"<<h.getMin()<<'\n';
   g<<"Maximul este:"<<h.getMax()<<'\n';
   g<<"Succesorul minimului este:"<<h.succesor(h.getMin())<<'\n';
   g<<"Predecesorul maximului este:"<<h.predecesor(h.getMax())<<'\n';
   g<<"Al 5-lea element in ordine crescatoare este:"<<h.kElement(5)<<'\n';
   if(i==3)
   {
       g<<"Elementul numarul 488 in ordine crescatoare"<<h.kElement(488);
   }
   g<<"Este 7 in heap?";
   if(h.esteInS(7))
    g<<"Da";
   else
   g<<"Nu";
  g<<'\n';
   g<<"Dar 44?";
    if(h.esteInS(44))
    g<<"Da";
   else
   g<<"Nu";
   g<<'\n';
   g<<'\n';
   g<<'\n';
   h.clear();
}






    return 0;
}
