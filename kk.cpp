/**
*Programming Assignment 3, Source Code
*Kalyan Palepu, Chris Zhu
**/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
#include <time.h>
#include <chrono>

using namespace std;

struct max_heap {
    vector<int> a;
    
    int left(int i) {
        return i * 2 + 1;
    }
    
    int right(int i){
        return i * 2 + 2;
    }

    int parent(int i){
        return (i - 1) / 2;
    }

    void max_heapify(int i){
        int left_child = left(i);
        int right_child = right(i);
        int largest = i;
        if(left_child < a.size() && a[left_child] > a[largest]){
            largest = left_child;
        }

        if(right_child < a.size() && a[right_child] > a[largest]){
            largest = right_child;
        }

        if(largest != i) {
            int tmp = a[i];
            a[i] = a[largest];
            a[largest] = tmp;
            max_heapify(largest);
        }
    }

    void build_max_heap() {
        for(int i = a.size() / 2; i > 0; i--) {
            max_heapify(i);
        }
    }

    void insert(int v) {
        a.push_back(v);
        int n = a.size() - 1;
        while(n > 0 && a[parent(n)] < a[n]) {
            int tmp = a[n];
            a[n] = a[parent(n)];
            a[parent(n)] = tmp;
            n = parent(n);
        }
    }

    int delete_max() {
        int tmp = a[0];
        a[0] = a.back();
        a.pop_back();
        max_heapify(0);
        return tmp;
    }

    int size() {
        return a.size();
    }

    vector<int> contents(){
        return a;
    }
};

void print_vector(vector<int> v) {
    for(int i = 0; i < v.size(); i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int KK(vector<int> A) {
    print_vector(A);
    max_heap h = {A};
    h.build_max_heap();
    print_vector(h.contents());
    while(h.size() > 1) {
        int first = h.delete_max();
        int second = h.delete_max();
        printf("    first: %d, second: %d\n", first, second);
        h.insert(first - second);
        print_vector(h.contents());
    }
    return h.delete_max();
}

int main(int argc, char *argv[]){
    string file_name = argv[1];
    fstream file;
    file.open(file_name.c_str());

    int curr = 0;
    vector<int> init;

    for(int i = 0; i < 100; i++){
        if(file.eof()){
            break;
        }
        file >> curr;
        init.push_back(curr);
    }

    file.close();

    cout << KK(init) << endl;
}