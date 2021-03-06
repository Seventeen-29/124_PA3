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
#include <stdlib.h> 

#define KARMAKAR_KARP 0
#define S_REPEATED_RANDOM 1
#define S_HILL_CLIMBING 2
#define S_SIMULATED_ANNEALING 3
#define P_REPEATED_RANDOM 11
#define P_HILL_CLIMBING 12
#define P_SIMULATED_ANNEALING 13

using namespace std;

unsigned long long KK(vector<unsigned long long> a);

class partitions_soln {
    protected:
        vector<int> vals; //current solution
        vector<unsigned long long> nums; // A
        vector<int> annealing_vals; //S'' in simulated annealing algorithm
        unsigned long long annealing_residue; 
        unsigned long long old_residue;
        int algorithm;

    public:
        partitions_soln(vector<unsigned long long> A, int algorithm_id) {
            nums = A;
            vals = get_random_vector(A.size());
            annealing_vals = vals;
            old_residue = get_residue(vals, nums);
            annealing_residue = old_residue;
            algorithm = algorithm_id;
        }

        vector<int> get_random_vector(int length) {
            vector<int> rand_vector(length, 1);
            for(int i = 0; i < rand_vector.size(); i++){
                rand_vector[i] = 1 + (rand() % nums.size());
            }
            return rand_vector;
        }
        
        void hill_climb_step() {
            // change vals
            int index = rand() % nums.size();
            int oldval = vals[index];
            int newval = 1 + (rand() % nums.size());
            while (newval == oldval){
                newval = 1 + (rand() % nums.size());
            }
            vals[index] = newval;

            unsigned long long new_residue = get_residue(vals, nums);
            if(old_residue < new_residue) {
                vals[index] = oldval;
            } else {
                old_residue = new_residue;
            }
        }

        void repeated_random_step() {
            vector<int> rand_vector = get_random_vector(nums.size());
            unsigned long long new_residue = get_residue(rand_vector, nums);
            if(new_residue <= old_residue){
                vals = rand_vector;
                old_residue = new_residue;
            }
        }
        
        void simulated_annealing_step(int iter) {
            int index = rand() % nums.size();
            int oldval = vals[index];
            int newval = 1 + (rand() % nums.size());
            while (newval == oldval){
                newval = 1 + (rand() % nums.size());
            }
            vals[index] = newval;

            unsigned long long new_residue = get_residue(vals, nums);
            // https://stackoverflow.com/questions/686353/random-float-number-generation
            float p = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float t_iter = pow(10, 10) * pow(0.8, floor (iter / 300.));
            float probability_threshold = exp(-(new_residue - old_residue) / t_iter);

            if((old_residue <= new_residue) && (p > probability_threshold)){
                vals[index] = oldval;
            } else { // if we change S
                old_residue = new_residue;
                if(new_residue < annealing_residue) {
                    annealing_residue = new_residue;
                    annealing_vals = vals;
                }
            }
        }

        static unsigned long long get_residue(vector<int> v, vector<unsigned long long> a) {
            vector<unsigned long long> new_nums(a.size(), 0);
            for(int i = 0; i < v.size(); i++) {
                new_nums[v[i] - 1] += a[i];
            }
            return KK(new_nums);
        }

        void step(int iter) {
            if(algorithm == P_REPEATED_RANDOM) {
                repeated_random_step();
            } else if(algorithm == P_HILL_CLIMBING) {
                hill_climb_step();
            } else if(algorithm == P_SIMULATED_ANNEALING) {
                simulated_annealing_step(iter);
            }
        }

        vector<int> get_soln(){
            return vals;
        }

        unsigned long long get_final_residue(){
            return algorithm == P_SIMULATED_ANNEALING ? annealing_residue : old_residue;
        }
};

/****************************PARTITION SOLUTION ABOVE HERE****************************/

class signs_soln {
    protected:
        vector<int> vals; //current solution
        vector<unsigned long long> nums; // A
        vector<int> annealing_vals; //S'' in simulated annealing algorithm
        unsigned long long annealing_residue; 
        unsigned long long old_residue;
        int algorithm;

    public:
        signs_soln(vector<unsigned long long> A, int algorithm_id) {
            nums = A;
            vals = get_random_vector(A.size());
            annealing_vals = vals;
            old_residue = get_residue(vals, nums);
            annealing_residue = old_residue;
            algorithm = algorithm_id;
        }

        vector<int> get_random_vector(int length) {
            vector<int> rand_vector(length, 1);
            for(int i = 0; i < rand_vector.size(); i++){
                rand_vector[i] = 2 * (rand() % 2) - 1;
            }
            return rand_vector;
        }
        
        void flip_vals(int i1, int i2, bool flip_i2) {
            vals[i1] *= -1;
            if(flip_i2) {
                vals[i2] *= -1;
            }
        }

        void hill_climb_step() {
            // change vals
            int i1 = rand() % nums.size();
            int i2 = rand() % nums.size();
            while (i2 == i1) {
                i2 = rand() % nums.size();
            }

            int flip_i2 = (rand() % 2) == 0;
            flip_vals(i1, i2, flip_i2);

            unsigned long long new_residue = get_residue(vals, nums);
            if(old_residue < new_residue) {
                flip_vals(i1, i2, flip_i2);
            } else {
                old_residue = new_residue;
            }
        }

        void repeated_random_step() {
            vector<int> rand_vector = get_random_vector(nums.size());
            unsigned long long new_residue = get_residue(rand_vector, nums);
            if(new_residue <= old_residue){
                vals = rand_vector;
                old_residue = new_residue;
            }
        }
        
        void simulated_annealing_step(int iter) {
            int i1 = rand() % nums.size();
            int i2 = rand() % nums.size();
            while (i2 == i1) {
                i2 = rand() % nums.size();
            }

            int flip_i2 = (rand() % 2) == 0;
            flip_vals(i1, i2, flip_i2);

            unsigned long long new_residue = get_residue(vals, nums);
            // https://stackoverflow.com/questions/686353/random-float-number-generation
            float p = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float t_iter = pow(10, 10) * pow(0.8, floor (iter / 1000.));
            float probability_threshold = exp(-(new_residue - old_residue) / t_iter);

            if((old_residue <= new_residue) && (p > probability_threshold)){
                flip_vals(i1, i2, flip_i2);
            } else { // if we change S
                old_residue = new_residue;
                if(new_residue < annealing_residue) {
                    annealing_residue = new_residue;
                    annealing_vals = vals;
                }
            }
        }

        static unsigned long long get_residue(vector<int> v, vector<unsigned long long> a) {
            long long residue = 0;
            for(int i = 0; i < v.size(); i++) {
                residue += v[i] * a[i];
            }
            return llabs(residue);
        }

        void step(int iter) {
            if(algorithm == S_REPEATED_RANDOM) {
                repeated_random_step();
            } else if(algorithm == S_HILL_CLIMBING) {
                hill_climb_step();
            } else if(algorithm == S_SIMULATED_ANNEALING) {
                simulated_annealing_step(iter);
            }
        }

        vector<int> get_soln(){
            return vals;
        }

        unsigned long long get_final_residue(){
            return algorithm == S_SIMULATED_ANNEALING ? annealing_residue : old_residue;
        }
};

struct max_heap {
    vector<unsigned long long> a;
    
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
            unsigned long long tmp = a[i];
            a[i] = a[largest];
            a[largest] = tmp;
            max_heapify(largest);
        }
    }

    void build_max_heap() {
        for(int i = a.size() / 2; i >= 0; i--) {
            max_heapify(i);
        }
    }

    void insert(unsigned long long v) {
        a.push_back(v);
        int n = a.size() - 1;
        while(n > 0 && a[parent(n)] < a[n]) {
            unsigned long long tmp = a[n];
            a[n] = a[parent(n)];
            a[parent(n)] = tmp;
            n = parent(n);
        }
    }

    unsigned long long delete_max() {
        unsigned long long tmp = a[0];
        a[0] = a.back();
        a.pop_back();
        max_heapify(0);
        return tmp;
    }

    int size() {
        return a.size();
    }

    vector<unsigned long long> contents(){
        return a;
    }
};

void print_vector(vector<unsigned long long> v) {
    for(int i = 0; i < v.size(); i++) {
        printf("%lld ", v[i]);
    }
    printf("\n");
}

unsigned long long KK(vector<unsigned long long> A) {
    max_heap h = {A};
    h.build_max_heap();
    // print_vector(h.contents());

    while(h.size() > 1) {
        unsigned long long first = h.delete_max();
        unsigned long long second = h.delete_max();
        // printf("    first: %lld, second: %lld\n", first, second);
        h.insert(first - second);
        //print_vector(h.contents());
    }
    return h.delete_max();
}

int main(int argc, char *argv[]){
    srand((unsigned)time(NULL));
    
    int flag = stoi(argv[1]);
    int algorithm = stoi(argv[2]);
    string file_name = argv[3];
    fstream file;
    file.open(file_name.c_str());

    unsigned long long curr = 0;
    vector<unsigned long long> init;

    for(int i = 0; i < 100; i++){
        if(file.eof()){
            break;
        }
        file >> curr;
        init.push_back(curr);
    }

    file.close();

    auto start = chrono::high_resolution_clock::now();

    if(algorithm == KARMAKAR_KARP) {
        cout << KK(init);     
    } else if(algorithm < 10){
        signs_soln soln = signs_soln(init, algorithm);
        for(int i = 0; i < 25000; i++) {
            soln.step(i);
        }
        cout << soln.get_final_residue();     
    } else {
        partitions_soln soln = partitions_soln(init, algorithm);
        for(int i = 0; i < 25000; i++) {
            soln.step(i);
        }
        cout << soln.get_final_residue();     
    }

    auto stop = chrono::high_resolution_clock::now(); 
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 

    if(flag > 0){
        cout << "," << duration.count() << endl;
    }
    else{
        cout << endl;
    }

    // signs_soln hill_soln = signs_soln(init);
    // signs_soln rep_soln = signs_soln(init);
    // signs_soln anneal_soln = signs_soln(init);

    // for(int i = 0; i < 25000; i++) {
    //     hill_soln.hill_climb_step();
    //     rep_soln.repeated_random_step();
    //     anneal_soln.simulated_annealing_step(i);
    // }

    // cout << "Repeated random residue     = " << log10(rep_soln.get_final_residue()) << endl;
    // cout << "Hill climb residue          = " <<  log10(hill_soln.get_final_residue()) << endl;
    // cout << "Simulated annealing residue = " << log10(anneal_soln.get_annealing_residue()) << endl;
    // cout << "KK residue                  = " << log10(KK(init)) << endl;

}