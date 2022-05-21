#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include "conio.h"
#include "kbhit.h"
using namespace std;

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22

char field[FIELD_HEIGHT][FIELD_WIDTH];
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH];

enum
{
  MINO_TYPE_I,
  MINO_TYPE_O,
  MINO_TYPE_S,
  MINO_TYPE_Z,
  MINO_TYPE_J,
  MINO_TYPE_L,
  MINO_TYPE_T,
  MINO_TYPE_MAX
};

enum
{
  MINO_ANGLE_0,
  MINO_ANGLE_90,
  MINO_ANGLE_180,
  MINO_ANGLE_270,
  MINO_ANGLE_MAX
};

#define MINO_WIDTH 4
#define MINO_HEIGHT 4
char minoShapes[MINO_TYPE_MAX][MINO_TYPE_MAX][MINO_HEIGHT][MINO_WIDTH] = {
    // MINO_TYPE_I
    {
        // MINO_ANGLE_0
        {
          0, 1, 0, 0,
          0, 1, 0, 0,
          0, 1, 0, 0,
          0, 1, 0, 0,
        },
        // MINO_ANGLE_90
        {
          0, 0, 0, 0,
          0, 0, 0, 0,
          1, 1, 1, 1,
          0, 0, 0, 0,
        },
        // MINO_ANGLE_180
        {
          0, 0, 1, 0,
          0, 0, 1, 0,
          0, 0, 1, 0,
          0, 0, 1, 0,
        },
        // MINO_ANGLE_270
        {
          0, 0, 0, 0,
          1, 1, 1, 1,
          0, 0, 0, 0,
          0, 0, 0, 0,
        },
    },
    // MINO_TYPE_O
    {
      //MINO_ANGLE_0
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_90
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_180
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_270
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
    },
    // MINO_TYPE_S
    {
      //MINO_ANGLE_0
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_90
      {
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_180
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        1, 1, 0, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_270
      {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
      },
    },
    
    // MINO_TYPE_Z
    {
      //MINO_ANGLE_0
      {
        0, 0, 0, 0,
        1, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_90
      {
        0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
      },
      //MINO_ANGLE_180
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 1,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_270
      {
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
      },
    },
    // MINO_TYPE_J
    {
      //MINO_ANGLE_0
      {
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_90
      {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_180
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
      },
      //MINO_ANGLE_270
      {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 1,
        0, 0, 0, 0,
      },
    },
    // MINO_TYPE_L
    {
      //MINO_ANGLE_0
      {
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_90
      {
        0, 0, 0, 0,
        0, 0, 1, 0,
        1, 1, 1, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_180
      {
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0,
      },
      //MINO_ANGLE_270
      {
        0, 0, 0, 0,
        0, 1, 1, 1,
        0, 1, 0, 0,
        0, 0, 0, 0,
      },
    },
    // MINO_TYPE_T
    {
      //MINO_ANGLE_0
      {
        0, 0, 0, 0,
        1, 1, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_90
      {
        0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 1, 0, 0,
      },
      //MINO_ANGLE_180
      {
        0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 1, 1,
        0, 0, 0, 0,
      },
      //MINO_ANGLE_270
      {
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 0, 1, 0,
        0, 0, 0, 0,
      },
    },
};

int minoType, minoAngle ;
int minoX, minoY ;

void display(){
  memcpy(displayBuffer, field, sizeof(field));

      for (int i = 0; i < MINO_HEIGHT; i++)
        for (int j = 0; j < MINO_WIDTH; j++)
          displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];

      system("clear");

      for (int i = 0; i < FIELD_HEIGHT; i++)
      {
        for (int j = 0; j < FIELD_WIDTH; j++)
          printf(displayBuffer[i][j] ? "⬜️" : "　");
        printf("\n");
      }

}

bool is_Hit(int _minoX, int _minoY, int _minoType, int _minoAngle){
  for(int i = 0; i < MINO_HEIGHT; i++)
    for(int j = 0; j < MINO_WIDTH; j++)
      if(minoShapes[_minoType][_minoAngle][i][j] && field[_minoY+i][_minoX+j])
        return true;
  return false;
}

void resetMino(){
  minoX = 5;
  minoY = 0;
  minoType = rand() % MINO_TYPE_MAX;
  minoAngle = rand() % MINO_ANGLE_MAX;
}

int main()
{
  srand(time(NULL));
  memset(field, 0, sizeof(field));
  for (int i = 0; i < FIELD_HEIGHT; i++)
    field[i][0] = field[i][FIELD_WIDTH - 1] = 1;
  for (int i = 0; i < FIELD_WIDTH; i++)
    field[FIELD_HEIGHT - 1][i] = 1;
    
  resetMino();
  time_t t = time(NULL);

  while (1)
  {
    if(kbhit()){
      switch(getch()){
        //case 'w':
        case 's':
          if(!is_Hit(
              minoX,      //int _minoX
              minoY + 1,        //int _minoY
              minoType,     //int _minoType
              minoAngle))   //in
          minoY++; break;
        case 'a':
          if(!is_Hit(
            minoX - 1,      //int _minoX
            minoY,        //int _minoY
            minoType,     //int _minoType
            minoAngle))   //int _minoAngle))
          minoX--; break;
        case 'd':
          if(!is_Hit(
            minoX + 1,      //int _minoX
            minoY,        //int _minoY
            minoType,     //int _minoType
            minoAngle))   //int _minoAngle))
          minoX++; break;
        case 'm':
          if(!is_Hit(
            minoX,      //int _minoX
            minoY,        //int _minoY
            minoType,     //int _minoType
            (minoAngle+1) % MINO_ANGLE_MAX ))   //int _minoAngle))
          minoAngle = (minoAngle+1) % MINO_ANGLE_MAX; break;
      }
      display();
    }
    if (t != time(NULL))
    {
      t = time(NULL);

      if(is_Hit(
         minoX,          //int _minoX
         minoY+1,        //int _minoY
         minoType,       //int _minoType
         minoAngle)){    //int _minoAngle
         for(int i = 0; i < MINO_HEIGHT; i++)
            for(int j = 0; j < MINO_WIDTH; j++)
                field[minoY+i][minoX+j] |= minoShapes[minoType][minoAngle][i][j];

          for(int i = 0; i < FIELD_HEIGHT-1; i++){
              bool lineFill = true;
              for(int j = 1; j < FIELD_WIDTH-1; j++){
                if(!field[i][j])
                 lineFill = false;
              }
              if(lineFill){
                //for(int j =  1; j<FIELD_WIDTH-1; j++)
                    //field[i][j] = 0;
                
                for(int j = i ; j > 0; j--)
                  memcpy(field[j], field[j-1], FIELD_WIDTH);
              }
          }

          resetMino();
         }
         else
          minoY++;

      display();

    }
  }

  getch();
}
