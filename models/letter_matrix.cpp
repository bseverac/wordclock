#include "letter_matrix.h"
//

LetterMatrix::LetterMatrix(){
  off();
}

void LetterMatrix::off(){
  for(iterator_y=0 ; iterator_y < CLOCK_H ; iterator_y++){
    matrix[iterator_y] = 0;
  }
}

void LetterMatrix::light(int * array){
  iterator_y = array[0];
  matrix[iterator_y] |= array[1];
}

void LetterMatrix::light(int x, int y){
  matrix[y] |= (1 << x);
}

void LetterMatrix::off(int x, int y){
  matrix[y] &= ~(1 << x);
}

bool LetterMatrix::status(int x, int y){
  return matrix[y] & (1 << x);
}
