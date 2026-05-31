// Copyright 2021 NNTU-CS
#include "Train.h"

Train::Train() : countOp(0), first(nullptr) {};
void Train::addCar(bool light) {
  Car* newCar = new Car;
  newCar->light = light;
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  }
  else {
    newCar->next = first->next;
    newCar->prev = first;
    first->next->prev = newCar;
    first->next = newCar;
  }
};
int Train::getLength() {
  Car* cur = first;
  if (!cur->light) cur->light = true;
  countOp = 0;
  int count = 0;
  while (true) {
    cur = cur->next;
    count++;
    if (cur->light) {
      cur->light = false;
      countOp += count;
      for (int i = 0; i < count; i++) { cur = cur->prev; countOp++; }
      if (!cur->light) return count;
      else count = 0;
    }
  }
}
int  Train::getOpCount() {
  if (countOp == 0) getLength();
  return countOp;
};
Train::~Train() {
  if (!first) return;
  Car* current = first;
  do {
    Car* next = current->next;
    delete current;
    current = next;
  } while (current != first);
}
