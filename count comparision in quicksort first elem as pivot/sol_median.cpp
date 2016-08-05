#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &a, int l, int r){
    int pivot = a[l];
    int i=l+1;
    for(int j=l+1; j <= r; j++){
    	if(a[j] < pivot){
    	    swap(a[i], a[j]);
    	    i++;
	    }
    }
    swap(a[i-1], a[l]);
    return (i-1);
}

void quicksortcount(vector<int> &v, long unsigned int &count, int l, int r){
    if(v.size() <= 1 || (l >= r) || l < 0 || r < 0){
    	return;
    }
    //cout << "l: " << l  << " r: " << r << " count: " << count << endl;
    if((r-l+1) >= 3){
        int first = l;
        int last = r;
        int mid;
        if((r-l+1)%2 == 0){
            mid = l + (r-l)/2;
        }else{
            mid = (r+l)/2;
        }
        vector<int> vec;
        vec.push_back(v[first]);
        vec.push_back(v[mid]);
        vec.push_back(v[last]);
        //cout << "BEFORE_SORT: first= " << vec[0] << " median= " << vec[1] << " last= " << vec[2] << endl;
        sort(vec.begin(), vec.end());
        int i;
        //cout << "AFTER_SORT: first= " << vec[0] << " median= " << vec[1] << " last= " << vec[2] << endl;
        for(i=l; i <= r; i++){
            if(v[i] == vec[1]){
                break;
            }
        }
        swap(v[l], v[i]);
    }else{
        swap(v[l], v[r]);
    }
    //partition around that pivot
    int loc = partition(v, l, r);
    //recursively sort left half
    if((loc-1-l) >= 0){
        count += (loc-1-l);
    }
    //cout << "count LEFT: " << count << endl;
    quicksortcount(v, count, l, loc-1);
    //recursively sort right half
    //cout << "count RIGHT: " << count << endl;
    if((r-loc-1) >= 0){
        count += (r-loc-1);
    }
    quicksortcount(v, count, loc+1, r);
}

int main() {
    int val;
    vector<int> v;

    for(int i=0; i< 10000; i++){
    	cin >> val;
	    v.push_back(val);
    }
    long unsigned int count = 0;
    quicksortcount(v, count, 0, v.size()-1);
    cout << count+9999 << endl;
    //for(int i : v){
    //    cout << i << " ";
    //}

    return 0;
}
