/* utils.h */
#define TRUE		1
#define FALSE		0
#define BYTE_MAX 	0xFF
#define CHAR_MIN 	(-0x80)
#define CHAR_MAX	0x7F

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BOOL;

extern int rand();
extern void bubble_sort(int, int []);