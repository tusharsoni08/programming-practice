#include <iostream>
#include <vector>

using namespace std;

void countSort(vector<int> &v, long unsigned int &count){
    if(v.size() <= 1){
        return;
    }
    vector<int> left(v.begin(), v.begin()+v.size()/2);
    vector<int> right(v.begin()+v.size()/2, v.end());

    //sort the halves
    countSort(left, count);
    countSort(right, count);

    //merge halves
    int i1 = 0;
    int i2 = 0;

    for(int i=0; i < v.size(); i++){
        if(i2 >= right.size() || (i1 < left.size() && left[i1] < right[i2])){
            v[i] = left[i1];
            i1++;
        }else{
            v[i] = right[i2];
            count += (left.size()-i1);
            i2++;
        }
    }
}

int main(){
    int val;
    vector<int> v;

    for(int i=0; i < 100000; i++){
        cin >> val;
        v.push_back(val);
    }
    long unsigned int count = 0;
    countSort(v, count);

    cout << count << endl;

}
