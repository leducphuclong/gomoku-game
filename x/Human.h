#include <utility>
#include "const.h"
using namespace std;
class Human {
    public:
        Human();
       ~Human();
        void get (pair<int, int> position);
        pair<int, int> put();
    private:
        pair<int, int> position;
};