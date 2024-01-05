#include <utility>
#include "const.h"

using namespace std;
class Game {
    public:
        Game(int turn = GUEST);
        ~Game();
        int** status;
        int result;
        int turn;
        void update(pair<int,int> position);
    private:
        int moves;
};