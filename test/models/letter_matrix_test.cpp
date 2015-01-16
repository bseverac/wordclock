
#include "../../models/letter_matrix.h"
#include <limits.h>
#include "gtest/gtest.h"

TEST(LetterMatrix, InitializeLetterMatrixWithZero) {
  LetterMatrix letter_matrix;
  for(int i=0;i<CLOCK_H;i++){
    EXPECT_EQ(0, letter_matrix.matrix[i]);
  }
}

TEST(LetterMatrix, LightMatrixWithOne) {
  LetterMatrix letter_matrix;
  int value[2] = {0,1};
  letter_matrix.light(value);
  EXPECT_EQ(1, letter_matrix.matrix[0]);
}

TEST(LetterMatrix, LightOff) {
  LetterMatrix letter_matrix;
  int value[2] = {0,1};
  letter_matrix.light(value);
  letter_matrix.off();
  for(int i=0;i<CLOCK_H;i++){
    EXPECT_EQ(0, letter_matrix.matrix[i]);
  }
}

TEST(LetterMatrix, LigthMatrixWithTime_Midnight) {
  Time time;
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]); //IL_EST
  EXPECT_EQ(0b111111000000000, letter_matrix.matrix[2]); //MINUIT
}

TEST(LetterMatrix, LigthMatrixWithTime_3h20) {
  Time time(3,20,0,0);
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]);  //IL_EST
  EXPECT_EQ(0b000111110000000, letter_matrix.matrix[1]);  //TROIS
  EXPECT_EQ(0b111111001100000, letter_matrix.matrix[4]);  //HEURES_ET
  EXPECT_EQ(0b000000000011111, letter_matrix.matrix[5]);  //VINGT
  EXPECT_EQ(0b000000011111110, letter_matrix.matrix[12]); //MINUTES
}

TEST(LetterMatrix, LigthMatrixWithTime_1h1) {
  Time time(1,1,0,0);
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]);  //IL_EST
  EXPECT_EQ(0b111000000000000, letter_matrix.matrix[3]);  //UNE
  EXPECT_EQ(0b111110001100000, letter_matrix.matrix[4]);  //HEURE_ET
  EXPECT_EQ(0b111000000000000, letter_matrix.matrix[11]); //UNE
  EXPECT_EQ(0b000000011111100, letter_matrix.matrix[12]); //MINUTE
}

TEST(LetterMatrix, LigthMatrixWithTime_12h15) {
  Time time(12,15,0,0);
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]);  //IL_EST
  EXPECT_EQ(0b000000000011110, letter_matrix.matrix[1]);  //MIDI
  EXPECT_EQ(0b000000001100000, letter_matrix.matrix[4]);  //ET
  EXPECT_EQ(0b000011111000000, letter_matrix.matrix[10]); //QUART
}

TEST(LetterMatrix, LigthMatrixWithTime_23h30) {
  Time time(23,30,0,0);
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]);  //IL_EST
  EXPECT_EQ(0b000000011110000, letter_matrix.matrix[3]);  //ONZE
  EXPECT_EQ(0b111111001100000, letter_matrix.matrix[4]);  //HEURES_ET
  EXPECT_EQ(0b000000111100000, letter_matrix.matrix[7]);  //DEMI
}

TEST(LetterMatrix, LigthMatrixWithTime_23h40) {
  Time time(23,40,0,0);
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]);  //IL_EST
  EXPECT_EQ(0b000000011110000, letter_matrix.matrix[3]);  //ONZE
  EXPECT_EQ(0b111111000011111, letter_matrix.matrix[4]);  //HEURES_MOINS
  EXPECT_EQ(0b000000000011111, letter_matrix.matrix[5]);  //VINGT
  EXPECT_EQ(0b000000011111110, letter_matrix.matrix[12]); //MINUTES
}

TEST(LetterMatrix, LigthMatrixWithTime_23h31) {
  Time time(23,31,0,0);
  LetterMatrix letter_matrix;
  letter_matrix.matrix_for_time(&time);

  EXPECT_EQ(0b011011100000000, letter_matrix.matrix[0]);  //IL_EST
  EXPECT_EQ(0b000000011110000, letter_matrix.matrix[3]);  //ONZE
  EXPECT_EQ(0b111111001100000, letter_matrix.matrix[4]);  //HEURES_ET
  EXPECT_EQ(0b000000000111111, letter_matrix.matrix[6]);  //TRENTE
  EXPECT_EQ(0b000011000000000, letter_matrix.matrix[7]);  //ET
  EXPECT_EQ(0b111000000000000, letter_matrix.matrix[11]); //UNE
  EXPECT_EQ(0b000000011111110, letter_matrix.matrix[12]); //MINUTES
}
