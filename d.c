#define F_CPU 960000UL

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define SBI(B,V) B|= _BV(V)
#define CBI(B,V) B&=~_BV(V)
#define SBIS(B,V) (uint8_t) (B&_BV(V))
#define SBIC(B,V) (uint8_t)!(B&_BV(V))
#define CLK PB3
#define DATA PB4
#define OK 1
#define NG 0

uint8_t clock(void)
{
  CBI(DDRB, CLK);
  if (bit_is_clear(PINB, CLK)) return NG;
  SBI(DDRB, CLK);
  CBI(PORTB, CLK);
  _delay_us(30);
  SBI(PORTB, CLK);
  _delay_us(30);
  return OK;
}

uint8_t send_DATA(uint8_t o)
{
  SBI(DDRB, DATA);
  if(o){SBI(PORTB, DATA);}
  else {CBI(PORTB, DATA);}
  return clock();
}

uint8_t send_ps2(uint8_t data)
{
  uint8_t i, x, parity;
  CBI(DDRB, CLK);
  if (bit_is_clear(PINB, CLK)) return NG;
  CBI(DDRB, DATA);
  if (bit_is_clear(PINB, DATA)) return NG;
  SBI(DDRB, DATA);
  if (!send_DATA(0)) return NG;
  parity = 0;
  for (i = 0; i < 8; i++) {
    x = (data>>i)&1;
    parity += x;
    if (!send_DATA(x)) return NG;
  }
  if (!send_DATA(!(parity&1))) return NG;
  if (!send_DATA(1)) return NG;
  _delay_ms(10);
  return OK;
}

void send_cmd(uint8_t data)
{
  uint16_t j;
  for (j = 0; j < 250; j++) {
    if (send_ps2(data) == OK) break;
  }
}

static const uint8_t key[] PROGMEM = {
  0xE0, 0x1F, 0xF1, // 'cmd'
  0x29, 0xF0, 0x29, 0xF1, // space
  0xE0, 0xF0, 0x1F, 0xF1, // break cmd

  0xf1, 0xf1,
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x24, 0xf0, 0x24, 0xf1,  // 'e'
  0x2d, 0xf0, 0x2d, 0xf1,  // 'r'
  0x3a, 0xf0, 0x3a, 0xf1,  // 'm'
  0x43, 0xf0, 0x43, 0xf1,  // 'i'
  0x31, 0xf0, 0x31, 0xf1,  // 'n'
  0x1c, 0xf0, 0x1c, 0xf1,  // 'a'
  0x4b, 0xf0, 0x4b, 0xf1,  // 'l'
  0x49, 0xf0, 0x49, 0xf1,  // '.'
  0x1c, 0xf0, 0x1c, 0xf1,  // 'a'
  0x4d, 0xf0, 0x4d, 0xf1,  // 'p'
  0x4d, 0xf0, 0x4d, 0xf1,  // 'p'
  0x5a, 0xf0, 0x5a, 0xf1,  // '\n'

  // clone gist
  0xf1, 0xf1,
  0x34, 0xf0, 0x34, 0xf1,  // 'g'
  0x43, 0xf0, 0x43, 0xf1,  // 'i'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x29, 0xf0, 0x29, 0xf1,  // ' '
  0x21, 0xf0, 0x21, 0xf1,  // 'c'
  0x4b, 0xf0, 0x4b, 0xf1,  // 'l'
  0x44, 0xf0, 0x44, 0xf1,  // 'o'
  0x31, 0xf0, 0x31, 0xf1,  // 'n'
  0x24, 0xf0, 0x24, 0xf1,  // 'e'
  0x29, 0xf0, 0x29, 0xf1,  // ' '
  0x33, 0xf0, 0x33, 0xf1,  // 'h'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x4d, 0xf0, 0x4d, 0xf1,  // 'p'
  0x1b, 0xf0, 0x1b, 0xf1,  // 's'
  0x52, 0xf0, 0x52, 0xf1,  // ':'
  0x4a, 0xf0, 0x4a, 0xf1,  // '/'
  0x4a, 0xf0, 0x4a, 0xf1,  // '/'
  0x34, 0xf0, 0x34, 0xf1,  // 'g'
  0x43, 0xf0, 0x43, 0xf1,  // 'i'
  0x1b, 0xf0, 0x1b, 0xf1,  // 's'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x49, 0xf0, 0x49, 0xf1,  // '.'
  0x34, 0xf0, 0x34, 0xf1,  // 'g'
  0x43, 0xf0, 0x43, 0xf1,  // 'i'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x33, 0xf0, 0x33, 0xf1,  // 'h'
  0x3c, 0xf0, 0x3c, 0xf1,  // 'u'
  0x32, 0xf0, 0x32, 0xf1,  // 'b'
  0x49, 0xf0, 0x49, 0xf1,  // '.'
  0x21, 0xf0, 0x21, 0xf1,  // 'c'
  0x44, 0xf0, 0x44, 0xf1,  // 'o'
  0x3a, 0xf0, 0x3a, 0xf1,  // 'm'
  0x4a, 0xf0, 0x4a, 0xf1,  // '/'
  0x4b, 0xf0, 0x4b, 0xf1,  // 'l'
  0x1c, 0xf0, 0x1c, 0xf1,  // 'a'
  0x4d, 0xf0, 0x4d, 0xf1,  // 'p'
  0x43, 0xf0, 0x43, 0xf1,  // 'i'
  0x1b, 0xf0, 0x1b, 0xf1,  // 's'
  0x4e, 0xf0, 0x4e, 0xf1,  // '-'
  0x1a, 0xf0, 0x1a, 0xf1,  // 'z'
  0x24, 0xf0, 0x24, 0xf1,  // 'e'
  0x2d, 0xf0, 0x2d, 0xf1,  // 'r'
  0x44, 0xf0, 0x44, 0xf1,  // 'o'
  0x45, 0xf0, 0x45, 0xf1,  // '0'
  0x46, 0xf0, 0x46, 0xf1,  // '9'
  0x4a, 0xf0, 0x4a, 0xf1,  // '/'
  // gist idが入る
  0x5a, 0xf0, 0x5a, 0xf1,  // '\n'

  // submit gist
  0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1,
  0x4d, 0xf0, 0x4d, 0xf1,  // 'p'
  0x35, 0xf0, 0x35, 0xf1,  // 'y'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x33, 0xf0, 0x33, 0xf1,  // 'h'
  0x44, 0xf0, 0x44, 0xf1,  // 'o'
  0x31, 0xf0, 0x31, 0xf1,  // 'n'
  0x29, 0xf0, 0x29, 0xf1,  // ' '
  // gist idが入る
  0x34, 0xf0, 0x34, 0xf1,  // 'g'
  0x43, 0xf0, 0x43, 0xf1,  // 'i'
  0x1b, 0xf0, 0x1b, 0xf1,  // 's'
  0x2c, 0xf0, 0x2c, 0xf1,  // 't'
  0x49, 0xf0, 0x49, 0xf1,  // '.'
  0x4d, 0xf0, 0x4d, 0xf1,  // 'p'
  0x35, 0xf0, 0x35, 0xf1,  // 'y'
  0x5a, 0xf0, 0x5a, 0xf1,  // '\n'

  0x00
};

int main(void)
{
  _delay_ms(2000);
  send_cmd(0xAA);
  _delay_ms(2000);
  // while (1) {
    uint16_t j;
    for (j = 0; j < sizeof(key); j++) {
      uint8_t x = pgm_read_byte(&key[j]);
      switch (x) {
      case 0xF1: // Wait
        _delay_ms(40);
        continue;
      case 0xFE: // End
        return 1;
      default:
        send_cmd(x);
      }
    }
  // }
  return 1;
}
