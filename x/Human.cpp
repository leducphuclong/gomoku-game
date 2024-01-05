#include "Human.h"
Human::Human() {

}
Human::~Human() {

}
void Human::get(pair<int, int> position) {
    this->position = position;
}
pair<int,int> Human::put() {
    return position;
}