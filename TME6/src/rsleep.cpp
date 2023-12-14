#include <ctime>
#include <cstdlib>
#include "rsleep.h"

void randsleep() {
  int r = rand();
  double ratio = (double)r / (double) RAND_MAX;
  struct timespec tosleep;
  tosleep.tv_sec =0;
  // 300 millions de ns = 0.3 secondes
  tosleep.tv_nsec = 300000000 + ratio*700000000;
  struct timespec remain;
  /*Q4 
  a l'aide du man, on sait que si on se fait signaler alors on cause un EINTR et en stock le temps
  restant dans le remain, on veut ce faire signaler pendant qu'on dort, au moins en attaque, donc il faut
  faire une boucle
  */
  /*Q5
  On pose une graine basé sur time(0) avec srand
  */
  /*Q6
  Non, On attend le signal, donc defense infini
  */
  while ( nanosleep(&tosleep, &remain) != 0) {
    tosleep = remain;
  }
}
