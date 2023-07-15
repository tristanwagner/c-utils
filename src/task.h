// https://www.geocities.ws/rand3289/MultiTasking.html
#ifndef _TASK_H_
#define _TASK_H_

#define TASK_INIT() static void* f; if(f) goto *f;
#define TASK_YIELD() { __label__ END; f=&&END; return; END: ; }
#define TASK_END() f=0;

#endif
/* void testingSub1(){
  TASK_INIT();
  printf("A");
  TASK_YIELD();
  printf("B");
  TASK_YIELD();
  printf("C");
  TASK_END();
}
void testingSub2(){
  TASK_INIT();
  printf("1");
  TASK_YIELD();
  printf("2");
  TASK_YIELD();
  printf("3");
  TASK_YIELD();
  printf("4");
  TASK_END();
}

void testingSub3(){
  TASK_INIT();
  while(1){
    printf("*");
    TASK_YIELD();
  }
  TASK_END();
}

void testing(){
  testingSub1();
  testingSub2();
  testingSub3();
  printf("|");
}


When testing() is called repeatedly, the output looks like this:

C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|B2*|C3*|A4*|B1*|C2*|A3*|B4*|C1*|A2*|B3*|C4*|A1*|
*/
