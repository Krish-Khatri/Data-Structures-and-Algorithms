#include <iostream>
using namespace std;
template <typename T>
class CircularDynamicArray{
    private:
        int array_size;
        int array_capacity;
        int arrFront;
        int arrBack;
        T *array;
        T error;
    
    public:
        CircularDynamicArray();
        CircularDynamicArray(int s);
        ~CircularDynamicArray();
        T &operator[](int i);
        CircularDynamicArray &operator=(const CircularDynamicArray &a);
        CircularDynamicArray(const CircularDynamicArray &a);

        void resize(int newCap);
        void addEnd(T v);
        void addFront(T v);
        void delEnd();
        void delFront();
        void clear();
        int length();
        int capacity();

        void radixSort(int i);
        void radsort(T arr[], int size, int bits);
        void countingSort(T arr[], int size, int bits);
       
        int linearSearch(T e);
        int binSearch(T e);
        int binarySearch(T arr[], int l, int r, T x) ;
        
        T QuickSelect(int k);
        T kthSmallest(T arr[], int l, int r, int k);
        int partition(T arr[], int l, int r);

        T WCSelect(int k);
        T wckthSmallest(T arr[], int l, int r, int k);
        void wcswap(T *a, T *b);
        int wcpartition(T arr[], int l, int r, T x);
        T findMedian(T arr[], int n);

        void insertionSort(T arr[], int n);
        void stableSort();
        void mergeSort(T arr[], int l, int r);
        void merge(T arr[], int l, int m, int r);
       
};  

template <typename T>
CircularDynamicArray<T>::CircularDynamicArray(){
    array = new T[2];
    array_capacity = 2;
    for(int i = 0; i < array_capacity; i ++)
    {
        array[i] = 0;
    }
    arrFront = 0;
    arrBack = 1;
    array_size = 0;
}

template <typename T>
CircularDynamicArray<T>::CircularDynamicArray(int s){
    array_capacity = s;
    array = new T[array_capacity];
    for(int i = 0; i < array_capacity; i ++)
    {
        array[i] = 0;
    }
    arrFront = 0;
    arrBack = array_capacity -1;
    array_size = s;
}

template <typename T>
CircularDynamicArray<T>::CircularDynamicArray(const CircularDynamicArray &a)
{
    array = new T[a.array_capacity];
    for(int i = 0; i < array_capacity; i++){
        array[i] = a.array[i];
    }
    array_size = a.array_size;
    array_capacity = a.array_capacity;
    arrFront = a.arrFront;
    arrBack = a.arrBack;
}

template <typename T>
CircularDynamicArray<T>& CircularDynamicArray<T>::operator=(const CircularDynamicArray &a){
    if(this == &a)
        return *this;
    
    if(a.array_size == 0)
        clear();
    
    
    this -> array = new T[a.array_capacity];
    for(int i = 0; i < a.array_capacity; i++){
       this -> array[i] = a.array[i];
    }
    this -> array_size = a.array_size;
    this -> array_capacity = a.array_capacity;
    this -> arrFront = a.arrFront;
    this -> arrBack = a.arrBack;

    return *this;
}
template <typename T>
CircularDynamicArray<T>::~CircularDynamicArray(){
    delete [] array;
}

template <typename T>
T &CircularDynamicArray<T>::operator[](int index){
    if((index < 0) || (index > array_size - 1))
    {
        std::cout << "Out of Bounds Reference: " << index << endl;
        return error;
    }
    else
    {
        int i = (arrFront + index)%array_capacity;
        return array[i];
    }
}

template <typename T>
void CircularDynamicArray<T>::addFront(T v){
    if(array_capacity == 0)
        array_capacity = 2;

    if(array_size >= array_capacity)
    {
        resize(array_capacity * 2);
    }

    arrFront--;
    if(arrFront < 0)
    {
        arrFront = array_capacity - 1;
    }

    array[arrFront] = v;
    array_size++;
}

template <typename T>
void CircularDynamicArray<T>::addEnd(T v){
    //cout << "cap:" << array_capacity << " size: " << array_size << endl;
    if(array_capacity == 0)
        array_capacity = 2;

    if(array_size >= array_capacity)
    {
        resize(array_capacity * 2);
    }

    arrBack++;
        
    if(arrBack > array_capacity -1) //Check if Loop around is required
        arrBack = 0;
        
    array[arrBack] = v;
    array_size++;
}

template <typename T>
void CircularDynamicArray<T>::delEnd(){
    arrBack--; //Decrement iback to 'pop' the value at its previous index
    if(arrBack < 0) //Check if loop around is required
            arrBack = array_capacity-1;
        
    array_size--;
        
    if(array_size <= (array_capacity / 4))
        resize((array_capacity/2));
        
    if(array_capacity == 0)
        array_capacity = 2;
}

template <typename T>
void CircularDynamicArray<T>::delFront(){
     arrFront++; //Increment arrFront to 'pop' the value at its previous index
        if(arrFront > array_capacity - 1) //Check if loop around is required
            arrFront = 0;
        
        array_size--;
    
        //Check if array capacity needs to be halved
        if(array_size <= (array_capacity/4) )
            resize(array_capacity/2);

        if(array_capacity == 0)
            array_capacity = 2;
}

template <typename T>
void CircularDynamicArray<T>::resize(int newCap){
    T *copyArray = new T[newCap];
    int current = arrFront;

    for(int i = 0; i < array_size; i++)
    {
        copyArray[i] = array[current];
        current = (current + 1) % array_capacity;
    }

    array_capacity = newCap;
    delete [] array;
    arrFront = 0;
    array = copyArray;
    arrBack = array_size - 1;
}

template <typename T>
void CircularDynamicArray<T>::clear(){
    delete [] array;
    array = new T[2];
    for(int i = 0; i < array_capacity; i ++)
    {
        array[i] = 0;
    }
    arrFront = 0;
    arrBack = 1;
    array_size = 0;
    array_capacity = 2;
}

template <typename T>
int CircularDynamicArray<T>::length(){
    return array_size;
}

template <typename T>
int CircularDynamicArray<T>::capacity(){
    return array_capacity;
}

template <typename T>
int CircularDynamicArray<T>::linearSearch(T e){ 
    
    T *tempArray = new T[length()];
    for(int i = 0; i < length(); i++){
        int j = (arrFront + i)%array_capacity;
        tempArray[i] = array[j];
    }
 
    for (int i = 0; i < length(); i++) 
        if (tempArray[i] == e) 
            return i; 
    return -1; 

    delete [] tempArray;
}

template <typename T>
int CircularDynamicArray<T>::binSearch(T e){
    T *tempArray = new T[length()];
    for(int i = 0; i < length(); i++){
        int j = (arrFront + i)%array_capacity;
        tempArray[i] = array[j];
    }
    
    int indx = binarySearch(tempArray, 0, length()-1, e);
    return indx ;
    delete [] tempArray;
}

template <typename  T>
int CircularDynamicArray<T>:: binarySearch(T arr[], int l, int r, T x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(arr, mid + 1, r, x); 
    } 
  
    // We reach here when element is not 
    // present in array 
    return -1; 
} 

template <typename T>
void CircularDynamicArray<T>::stableSort(){
    T *tempArray = new T[length()];
    for(int i = 0; i < length(); i++){
        int j = (arrFront + i)%array_capacity;
        tempArray[i] = array[j];
    }

    mergeSort(tempArray,0,length()-1);
    for(int i = 0 ; i < length(); i++)
    {
        int j = (arrFront + i)%array_capacity;
        array[j] = tempArray[i];
    }

    delete [] tempArray;

}
template <typename T>
void CircularDynamicArray<T>:: merge(T arr[], int left, int mid, int right) {

	int i, j, k;
	int size1 = mid - left + 1;
	int size2 = right - mid;

	T* tmpLeft = new T[size1];
	T* tmpRight = new T[size2];

	for (i = 0; i < size1; ++i)
		tmpLeft[i] = arr[left + i];
	for (j = 0; j < size2; ++j)
		tmpRight[j] = arr[mid + 1 + j];

	i = 0; j = 0;
	k = left;

	while (i < size1 && j < size2) {
		if (tmpLeft[i] <= tmpRight[j])
			arr[k++] = tmpLeft[i++];
		else
			arr[k++] = tmpRight[j++];
	}

	while (i < size1)
		arr[k++] = tmpLeft[i++];
	while (j < size2)
		arr[k++] = tmpRight[j++];

}

template <typename T>
void CircularDynamicArray<T>:: mergeSort(T arr[], int left, int right) {

	if (left < right) {
		int mid = ( (unsigned int)left + (unsigned int)right ) >> 1;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

template <typename T>
T CircularDynamicArray<T>::QuickSelect(int k){

    T *tempArray = new T[length()];
    for(int i = 0; i < length(); i++){
        int j = (arrFront + i)%array_capacity;
        tempArray[i] = array[j];
    }

    T val = kthSmallest(tempArray, 0, length()-1,k);
    delete [] tempArray;
    return val;
}
template <typename T>
int CircularDynamicArray<T>::partition(T arr[], int l, int r)
{
    T x = arr[r];
    int i = l; 
    for (int j = l; j <= r - 1; j++) { 
        if (arr[j] <= x) { 
            swap(arr[i], arr[j]); 
            i++; 
        } 
    } 
    swap(arr[i], arr[r]); 
    return i; 
}

template <typename T>
T CircularDynamicArray<T>::kthSmallest(T arr[], int l, int r, int k)
{
    // If k is smaller than number of  
    // elements in array 
    if (k > 0 && k <= r - l + 1) { 
  
        // Partition the array around last  
        // element and get position of pivot  
        // element in sorted array 
        int index = partition(arr, l, r); 
  
        // If position is same as k 
        if (index - l == k - 1) 
            return arr[index]; 
  
        // If position is more, recur  
        // for left subarray 
        if (index - l > k - 1)  
            return kthSmallest(arr, l, index - 1, k); 
  
        // Else recur for right subarray 
        return kthSmallest(arr, index + 1, r,  
                            k - index + l - 1); 
    }

    return array_capacity;     
}

template <typename T>
void CircularDynamicArray<T>::insertionSort(T arr[], int n){
    int i,j;
    T key;

    for(i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j = j -1;
        }

        arr[j+1] = key;
    }
}

template <typename T>
T CircularDynamicArray<T>::WCSelect(int k){
     T *tempArray = new T[length()];
    for(int i = 0; i < length(); i++){
        int j = (arrFront + i)%array_capacity;
        tempArray[i] = array[j];
    }

    T val = wckthSmallest(tempArray, 0, length()-1,k);
    delete [] tempArray;
    return val;    
}
template <typename T>
T CircularDynamicArray<T>::findMedian(T arr[], int n){
    insertionSort(arr,n);
    return arr[n/2];
}

template <typename T>
T CircularDynamicArray<T>::wckthSmallest(T arr[], int l, int r, int k){
    // If k is smaller than number of elements in array 
    if (k > 0 && k <= r - l + 1) 
    { 
        int n = r-l+1; // Number of elements in arr[l..r] 
  
        // Divide arr[] in groups of size 5, calculate median 
        // of every group and store it in median[] array. 
        int i;
        T median[(n+4)/5]; // There will be floor((n+4)/5) groups; 
        for (i=0; i<n/5; i++) 
            median[i] = findMedian(arr+l+i*5, 5); 
        if (i*5 < n) //For last group with less than 5 elements 
        { 
            median[i] = findMedian(arr+l+i*5, n%5);  
            i++; 
        }     
  
        // Find median of all medians using recursive call. 
        // If median[] has only one element, then no need 
        // of recursive call 
        T medOfMed = (i == 1)? median[i-1]: 
                                 wckthSmallest(median, 0, i-1, i/2); 
  
        // Partition the array around a random element and 
        // get position of pivot element in sorted array 
        int pos = wcpartition(arr, l, r, medOfMed); 
  
        // If position is same as k 
        if (pos-l == k-1) 
            return arr[pos]; 
        if (pos-l > k-1)  // If position is more, recur for left 
            return wckthSmallest(arr, l, pos-1, k); 
  
        // Else recur for right subarray 
        return wckthSmallest(arr, pos+1, r, k-pos+l-1); 
    } 
    return array_capacity;
}

template <typename T>
void CircularDynamicArray<T>::wcswap(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T>
int CircularDynamicArray<T>::wcpartition(T arr[], int l, int r, T x){
    int i; 
    for (i=l; i<r; i++) 
        if (arr[i] == x) 
           break; 
    wcswap(&arr[i], &arr[r]); 
  
    // Standard partition algorithm 
    i = l; 
    for (int j = l; j <= r - 1; j++) 
    { 
        if (arr[j] <= x) 
        { 
            wcswap(&arr[i], &arr[j]); 
            i++; 
        } 
    } 
    wcswap(&arr[i], &arr[r]); 
    return i;


}
template <typename T>
void CircularDynamicArray<T>::countingSort(T arr[], int size, int bits){
    T *output = new T[size];
    int countArray[2] = {0};

    for(int i = 0; i < size; i++)
    {
        countArray[arr[i] >> bits & 1]++;
    }

    countArray[1] = countArray[0] + countArray[1];

    for(int i = size- 1; i >=0; i--)
    {
        output[countArray[arr[i] >> bits & 1] - 1 ] = arr[i];
        --countArray[arr[i] >> bits & 1];
    }

    for(int i = 0; i < size; i++)
    {
        arr[i] = output[i];
    }
}
template <typename T>
void CircularDynamicArray<T>::radsort(T arr[], int size, int bits){
    for(int i = 0; i < bits; i++)
    {
        countingSort(arr, size, i);
    }
}

template <typename T>
void CircularDynamicArray<T>::radixSort(int i){
    T *tempArray = new T[length()];
    for(int i = 0; i < length(); i++){
        int j = (arrFront + i)%array_capacity;
        tempArray[i] = array[j];
    }

    radsort(tempArray, length(), i);

    for(int i = 0 ; i < length(); i++)
    {
        int j = (arrFront + i)%array_capacity;
        array[j] = tempArray[i];
    }

    delete [] tempArray;
}