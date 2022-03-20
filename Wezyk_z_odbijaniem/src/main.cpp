#include <util/delay.h>
#include <avr/io.h>
#define MASK_RIGHT_WALL 0x01
#define MASK_LEFT_WALL 0x80
#define DIODE_SKIP_SPEED 50

#define ACCES_TO_THE_RIGTH_WALL \
  while((PORTD & MASK_RIGHT_WALL) != MASK_RIGHT_WALL){ \
    PORTD >>= 0x01; \
    _delay_ms(DIODE_SKIP_SPEED); \
  } 

#define ACCES_TO_THE_LEFT_WALL \
  while((PORTD & MASK_LEFT_WALL) != MASK_LEFT_WALL){ \
    PORTD <<= 0x01; \
    _delay_ms(DIODE_SKIP_SPEED); \
  } 

#define SHIFTING_8_BITS_RIGTH \
  if((PORTD & MASK_LEFT_WALL) == MASK_LEFT_WALL){ \
    ACCES_TO_THE_RIGTH_WALL \
  }  

#define SHIFTING_8_BITS_LEFT \
  if((PORTD & MASK_RIGHT_WALL) == MASK_RIGHT_WALL){ \
    ACCES_TO_THE_LEFT_WALL \
  }    

int main(void)
{
  DDRD=0xFF;
  PORTD = 0x80;

  while(1){
    SHIFTING_8_BITS_RIGTH
    SHIFTING_8_BITS_LEFT
  }
  return 0;
}