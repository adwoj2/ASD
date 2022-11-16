#include <iostream>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);

std::cin.tie(NULL);
    int n;
    cin >> n;
    int k;
    cin >> k;
    string s;
    cin >> s;
    int connected[n + 1];
    for (int i = 0; i < n + 1; i++)
        connected[i] = i;
    int a, b;
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        connected[a] = b;
        connected[b] = a;
    }
    bool back = false;
    int index = 1;
    for (int i = 0; i < n; i++) {
        int new_index = connected[index];
        if (new_index < 0) {
            cout << s[index - 1];
            if (-new_index != index) 
                back = !back;
            index = -new_index;
            if (!back)
                index++;
            else 
                index--;
        } else {
            connected[index] = -connected[index];
            if (new_index != index) 
                back = !back;
            index = new_index;
            cout << s[index - 1];
            if (!back)
                index++;
            else 
                index--;
        }
    }
}