#include "RedBlackTree.h"

int main() {
    RedBlackTree<double> RBT;
    std::vector<int> nums{ 1,4,3,6,9,7,2,5,8,10};
    for (auto num : nums)
        RBT.Insert(num);
    //RBT.Remove(10);
    RBT.Print();
    return 0;
}
