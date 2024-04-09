#include <stdlib.h>

long fixedMap(long x, long in_min, long in_max, long out_min, long out_max) {
  long in_size = in_max - in_min;
  long out_size = out_max - out_min;
  if( abs(in_size) > abs(out_size) )
  {
    if( in_size < 0 ) in_size--; else in_size++;
    if( out_size < 0 ) out_size--; else out_size++;
  }
  return ((x - in_min) * (out_size) / (in_size) + out_min);
}
