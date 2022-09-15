#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <fstream> 
using namespace std;

long long microseconds;
auto start = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::high_resolution_clock::now() - start;

// HEAP SORT *********************************************
void heapify(int* arr, int n, int i){
    int max_=i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l] > arr[max_]) max_ = l;
    if (r < n && arr[r] > arr[max_])  max_ = r;
 
    if (max_ != i) {
        swap(arr[i], arr[max_]);
        heapify(arr, n, max_);
    }
}

void heapSort(int* arr, int begin, int end){
    int n = end-begin+1;
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// QUICK SORT ********************************************
int partition(int* arr, int low, int high){
    int i = low-1;
    for (int j = low; j < high; j++){
        if (arr[j] < arr[high]) swap(arr[j], arr[++i]);
    }
    swap(arr[++i], arr[high]);
    return  i;
}

void quickSort(int* arr, int low, int high){
    if (low >= high) return;
    int p = partition(arr, low, high);
    quickSort(arr, low, p-1);
    quickSort(arr, p+1, high);
}

// MERGE SORT ********************************************
void merge(int* arr, int begin, int mid, int end){
    int *aux = new int[end-begin+1];
    int i = begin, j = mid+1, k = 0;
    while (i <= mid && j <= end){
        if (arr[i] < arr[j]) aux[k++] = arr[i++];
        else aux[k++] = arr[j++];
    }

    while (i <= mid) aux[k++] = arr[i++];
    while (j <= end) aux[k++] = arr[j++];

    k = 0;
    for (i = begin; i <= end; i++) arr[i] = aux[k++];
    delete aux;
}

void mergeSort(int* arr, int begin, int end){
    if (begin >= end) return;
    int mid = (int) (begin+end) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, begin, mid, end);
}

// SHELL SORT ********************************************
void shellSort(int* arr, int begin, int end){
    int j, gap = (int) (end - begin + 1)/2;
    while (gap > 0){
        for(int i = begin; i+gap <= end; i++){
            for (j = i; j >= begin && arr[j] > arr[j+gap]; j-=gap) {
            	swap(arr[j], arr[j+gap]);
			}
        }
        gap = (int) gap/2;
    }
}

// RADIX SORT ********************************************
void count(int *arr, int* result, int n, int exp){
    int counter[10] = {};
    int i;

    for (i = 0; i < n; i++) counter[int(arr[i]/exp) % 10] ++;
    for (i = 1; i < 10; i++) counter[i] += counter[i-1];
    for (i = n - 1; i >= 0; i--) result[--counter[int(arr[i]/exp) % 10]] = arr[i];
    for (i = 0; i < n; i ++) arr[i] = result[i];
}

void radixSort(int* arr, int begin, int end){ // Just for positive integers
    int n = end-begin+1, max_ = arr[0];
    int* result = new int[n];

    for (int i = 1; i < n; i++){ // Max number
        if (max_ < arr[i]) max_ = arr[i];
    }
    for (int exp = 1; int(max_/exp) > 0; exp*=10) count(arr, result, n, exp);
    delete result;
}

// BUCKET SORT *******************************************
void bucketSort(int* arr, int begin, int end){ // Just for positive numbers
    int n = end-begin+1, max_ = arr[0];
    vector<int>* bucket = new vector<int>[n];
    for (int i = 1; i < n; i++){
        if (max_ < arr[i]) max_ = arr[i];
    }

    // long long bcause (n-1)*arr[i] may cause overflow
    for (int i = 0; i < n; i ++) bucket[(long long) (n-1)*arr[i] / max_].push_back(arr[i]); 
    for (int i = 0; i < n; i ++) sort(bucket[i].begin(), bucket[i].end()); // quickSort
    
    max_ = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < bucket[i].size(); j++) arr[max_++] = bucket[i][j];
    }
    // delete bucket; // This line crash :(
}

// AUX FUNCTIONS *****************************************
int random(){
	int r = 0;
	for (int i = 0; i < 30; i++) r = (r | (rand() & 1)) << 1;
	return r;
}

void init_arr(int* a, int* back_up, int n){
	srand(time(0)+rand());
    for (int i = 0; i < n; i++) {
    	a[i] = random();
    	back_up[i] = a[i];
	}
}

void restore_arr(int* a, int* back_up, int n){
	for (int i = 0; i < n; i++) a[i] = back_up[i];
}

void print_arr(int *a, int n){
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

bool check_sort(int *a, int n){
    if (n <= 1) return true;
    for (int i = 1; i < n; i++){
        if (a[i-1] > a[i]) {
        	cout << "SOMETHING WENT REALLY WRONG\n";
			return false;
		}
    }
    return true;
}

void start_time(){
	start = std::chrono::high_resolution_clock::now();
}

long long finish_time(){
	elapsed = std::chrono::high_resolution_clock::now() - start;
	microseconds =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	if (microseconds < 10000000ll) cout << microseconds << "\t\t";
	else cout << microseconds << "\t";
	return microseconds;
}

int main(){
	
	const int test = 36;
	string txt = "";
	long long times_mat[test][6];
    int *arr = new int[20000000];
    int *back_up = new int[20000000];
	int arr_size[test] { 5000, 10000, 20000, 40000, 60000, 80000,  // 6
					   100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, // 9
					   1000000, 1250000, 1500000, 1750000, 2000000, 2250000, 2500000, 2750000, // 8
					   3000000, 3250000, 3500000, 3750000, 4000000, 4250000, 4500000, 4750000, // 8
					   5000000, 5250000, 5500000, 5750000, 6000000}; // 5
	
	cout << "\n\t\t*** Sorting Algorithms Time (Microseconds) ***\n\n";
	
	cout << "N\tSHELL SORT\tHEAP SORT\tBUCKET SORT\tMERGE SORT\tQUICK SORT\tRADIX SORT\n";
	for (int i = 0; i < test; i++){
		
		if (arr_size[i] < 1000) cout << arr_size[i];
		else if (arr_size[i] < 1000000) cout << (float) arr_size[i]/1000 << " K";
		else cout << (float) arr_size[i]/1000000 << " M";
		cout << " \t";
		
		init_arr(arr, back_up, arr_size[i]);

		start_time(); shellSort(arr, 0, arr_size[i]-1); times_mat[i][0] = finish_time();
		check_sort(arr, arr_size[i]);
		restore_arr(arr, back_up, arr_size[i]);
		
		start_time(); heapSort(arr, 0, arr_size[i]-1); times_mat[i][1] = finish_time();
		check_sort(arr, arr_size[i]);
		restore_arr(arr, back_up, arr_size[i]);
		
		start_time(); bucketSort(arr, 0, arr_size[i]-1); times_mat[i][2] = finish_time();
		check_sort(arr, arr_size[i]);
		restore_arr(arr, back_up, arr_size[i]);
		
		start_time(); mergeSort(arr, 0, arr_size[i]-1); times_mat[i][3] = finish_time();
		check_sort(arr, arr_size[i]);
		restore_arr(arr, back_up, arr_size[i]);
		
		start_time(); quickSort(arr, 0, arr_size[i]-1); times_mat[i][4] = finish_time();
		check_sort(arr, arr_size[i]);
		restore_arr(arr, back_up, arr_size[i]);
		
		start_time(); radixSort(arr, 0, arr_size[i]-1); times_mat[i][5] = finish_time();
		check_sort(arr, arr_size[i]);
		restore_arr(arr, back_up, arr_size[i]);

		cout << endl;
	}	
	
	for (int i = 0; i < test; i++) txt += to_string(arr_size[i]) + " ";
	txt+= "\n";
	for (int i = 0 ; i < test; i ++){
		for (int j = 0; j < 6; j++) txt += to_string(times_mat[i][j]) + " ";
		txt +="\n";
	}
	
	ofstream TimesFile("times.txt");
	TimesFile << txt;
	TimesFile.close();
	
    delete arr;
    delete back_up;
    return 0;
}
