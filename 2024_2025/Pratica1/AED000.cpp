#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a = 0;
    for (int i = 0; i < n; i++){
        int l;
        cin >> l;
        
        if (l == 42) {
            a++;
        }
    }
    cout << a;
    return 0;
}
