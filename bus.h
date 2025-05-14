/* File: bus.h
   Author: Douglas Jones, Dept. of Comp. Sci., U. of Iowa, Iowa City, IA 52242.
   Date: July 26, 1995
   Language: C (UNIX)
   Purpose: Declarations of bus lines shared by PDP8/E and peripherals.
            This is not, strictly speaking, either an omnibus or a positive
            I/O bus, but rather, it is a set of declarations driven by the
	    needs of system emulation.
   Constraints: When included in the main program, MAIN must be defined.
            When included elsewhere, MAIN must not be defined.
		
   Based on the description in the PDP-8/E Small Computer Handbook,
   Digital Equipment Corporation, 1971.
*/


/* The following trick puts extern on definitions if not in the main program
*/
#ifdef MAIN
#define EXTERN
#else
#define EXTERN extern
#endif


/******************************************/
/* Utility information needed by emulator */
/******************************************/

/* absolute path name of file where emulator object code is to be stored
*/
/*#define PDP8NAME "pdp8e"*/

/* maximum length of a sensible file name
*/
#define NAME_LENGTH 120



/*****************************************************/
/* Globals that really aren't really part of the bus */
/*****************************************************/

EXTERN char corename[NAME_LENGTH]; /* name of core image file, if any */
EXTERN char * progname; /* name of program itself (argv[0]) */


/**********/
/* Memory */
/**********/

/* This emulator does not allow for non-contiguous memory fields.
   Checking of memory addressing errors is not done, so all addressable
   memory must be available.  Thus, the memory size depends on whether
   the KM8E option is present.
*/

#ifdef KM8E
#define MAXMEM 32768
#else
#define MAXMEM 4096
#endif

EXTERN int memory[MAXMEM];


/*******************************/
/* Generally visible registers */
/*******************************/

/* All of the following are visible outside the CPU in some context or
   another, either to some I/O device or to the front panel.
*/
EXTERN int ac;  /* the accumulator, 12 bits */
EXTERN int pc;  /* the program counter, 12 bits */
EXTERN int mq;  /* the multiplier quotient, 12 bits */
EXTERN int sr;  /* the switch register */
EXTERN int cpma;/* the memory address register */
EXTERN int mb;  /* the memory buffer register */

EXTERN int link;/* the link bit, 1 bit, in position 010000 of the word */
EXTERN int run; /* the run flipflop, 0 = halt, 1 = running */

EXTERN int enab;/* interrupt enable bit, 0 = disable, 1=enable */
EXTERN int enab_rtf; /* secodary enable needed for RTF deferred enable */
EXTERN int irq; /* the interrupt request line, 0 = no request, >0 = request */

EXTERN int sw;  /* the switch, 1 bit */

/* Note that any positive value of irq indicates a request!  Requests are
   posted by incrementing irq, and withdrawn by decrementing irq.
*/

#ifdef KM8E

/* 3 bit fields stored 12 places left so they can be ORed onto 12 addresses.
*/
EXTERN int ifr; /* the instruction field register */
EXTERN int dfr; /* the data field register */
EXTERN int ib; /* the instruction field buffer (copy to if on branch, jsr) */

/* 7 bits, exactly as documented in the small computer handbook
*/
EXTERN int sf; /* the save field register (save ir, if, df on interrupt) */

/* 1 bit, where ub is copied to uf on branch, jsr
*/
EXTERN int uf; /* the user mode flag */
EXTERN int ub; /* the user mode buffer */

/* 1 bit, reset on branch, jsr
*/
EXTERN int km8e_uif; /* user interrupt flag (local to KM8E but used in KK8E) */

#include <stdio.h>

EXTERN int ttygetc(void);
EXTERN int ttypoll(void);
EXTERN void (* ttybreak) (void);
EXTERN void accumulate_debug(int p,int m);
EXTERN void clearflags(void);
EXTERN void close_devices(void);
EXTERN void cr8fdev3(int op);
EXTERN void cr8fdev7(int op);
EXTERN void cr8finit(void);
EXTERN void cr8fpower(void);
EXTERN void dk8edev(int op);
EXTERN void dk8einit(void );
EXTERN void dk8epower(void);
EXTERN void dump(void);
EXTERN void dump_devices( FILE *f );
EXTERN void dumpcore(void);
EXTERN void getargs(int argc, char *argv[]);
EXTERN void init_conversions(void);
EXTERN void kc8halt(void);
EXTERN void kc8init(void);
EXTERN void kc8power(int argc, char **argv);
EXTERN void kc8power(int argc,char** argv);
EXTERN void kl8edev3(int op);
EXTERN void kl8edev4(int op);
EXTERN void kl8einit(void);
EXTERN void kl8epower(void);
EXTERN void km8edev(int op);
EXTERN void km8einit(void);
EXTERN void km8epower(void);
EXTERN void mount_device( char * n, char * f );
EXTERN void output_debug(void);
EXTERN void pc8edev1(int op);
EXTERN void pc8edev2(int op);
EXTERN void pc8einit(void);
EXTERN void pc8epower(void);
EXTERN void powerdown(void);
EXTERN void powerup(int argc,char** argv);
EXTERN void readcore(void);
EXTERN void register_device(int (* m)(int u, char * f), void (* d)(int u), int u, char * n, char * l, char * f);
EXTERN void reset_debug(void);
EXTERN void rim(void);
EXTERN void rx8edev(int op);
EXTERN void rx8einit(void);
EXTERN void rx8epower(void);
EXTERN void set_file_name(char * f, char * s);
EXTERN void startwindow(int argc,char **argv);
EXTERN void ttygets(char * buf,int len);
EXTERN void ttyoctal( int num, int digits, char * suffix );
EXTERN void ttyputc(char ch);
EXTERN void ttyputs(char * buf);
EXTERN void ttyraw(void);
EXTERN void ttyrestore(void);
EXTERN void ttystuff(char ch);
EXTERN void vc8edev5(int op);
EXTERN void vc8einit(void);
EXTERN void vc8epower(void);

#endif
