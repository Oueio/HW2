#include "Set.h"

int main() {
    Set<int> set;
    int n;
    std::pair<int,int> a{0,1};
    std::pair<int,int> b{3,0};
    std::cout << (a < b);
    return 0;
}
