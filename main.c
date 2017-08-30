#include <stdio.h>

/*
Because lcd and serial don't support printf, and its very costly, and all we need
is simple formating with a certain number of digits and precision, this ftoa is enough.
*/

//avoid needed stdlib.h by defining abs as a macro
#define absq(amt) ((amt)<0?0-(amt):(amt))
//avoid needing math.h by defining powers of 10 as an array
long pow10[10] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

int puts_int( //send positive integers to STDOUT via putchar(char)
   unsigned int num	//positive integer to display
  ,char digits	//count of digits, negative and '0' pad for trailing zeros
  ,char pad		//character to pad with, or null 
  ) {
unsigned int i;
char c;
unsigned char d;
  d = absq(digits);
  while (0 < d) {
    i = num/pow10[--d]; //pre-increment
    if (d && !i) { //no digits found yet. d && for leading zero
      if (pad) putchar(pad); else digits--; //track digits (not) used
      }
    else { //found something
      c = i%10; //only want the lowest digit
      //Optional: Don't continue after fraction done
      if ('0'==pad && 0<digits && 0==c) return digits-d; 
      putchar(c+'0'); //convert to ASCII and send
      }
    }
  return absq(digits)-d;
  }

int puts_float( //send floating point numbers to STDOUT
    float f  	//number to display
  , char digits	//digits, negative to pad with spaces
  , char precision	//precision, negative to keep trailing zeros
  ) {
unsigned int a;
char i=0;

  if(digits>=10) {return 0;};
// check for negative float
  if(f<0.0) { //is it negative?
    putchar('-');i++; //indicate
    f*=-1; //make it positive
    if (0>digits) digits++; //optional, steal digit for sign, keep length
    }

  a=(int)f;	// extract whole number
  i+=puts_int(a,digits,digits>0?0:' ');
  if (precision) {
    putchar('.');i++;
    f-=(float)a; //remove whole part
    f*=pow10[absq(precision)]; // promote to precision
    f+=0.5; // round
    a=(int)f; // extract whole number
    i+=puts_int(a,precision,'0');
    }
  return i; //count of characters
  }


int main(void) {
float f;
  //puts_int(12345,6,' ');puts("");
  for (f=0.0001;f<0.00091;f+=0.0001) { puts_float(f, 5, -4); putchar(' '); }; puts("");
  for (f=0.001;f<0.0091;f+=0.001) { puts_float(f, 5, -4); putchar(' '); }; puts("");
  for (f=0.01;f<0.091;f+=0.01) { puts_float(f, 5, -4); putchar(' '); }; puts("");
  for (f=0.1;f<0.91;f+=0.1) { puts_float(f, 5, -4); putchar(' '); }; puts("");
  //also puts_int the return value of puts_float, which is the character used count.
  puts_int(puts_float(123406.789, -8, 3),4,' ');putchar(',');putchar(' ');
  puts_int(puts_float(123456, 8, -3),4,' ');putchar(',');putchar(' ');
  puts_int(puts_float(123450.789, 8, 0),4,' ');putchar('\r');
  puts_int(puts_float(-4.4, 8, 4),4,' ');putchar(',');putchar(' ');
  puts_int(puts_float(-4.4, -8, -4),4,' ');putchar('\r');
  return 0;
}
