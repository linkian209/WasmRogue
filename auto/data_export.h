/* Generated file - do not edit */
#define arg0()
#define arg1(a) ,(long)a
#define arg2(a,b) ,(long)a,(long)b
#define arg3(a,b,c) ,(long)a,(long)b,(long)c
#define arg4(a,b,c,d) ,(long)a,(long)b,(long)c,(long)d
#define arg5(a,b,c,d,e) ,(long)a,(long)b,(long)c,(long)d,(long)e
// This file may contain ONLY prototypes for functions in the data file.
// It will be used to generate an interface to the data file for the main
// program.

#define distribute_attributes() call_generic(0, 0 arg0())
#define awardXP(a) call_generic(1, 1 arg1(a))
#define plr_regenerate(a) call_generic(2, 1 arg1(a))
#define plr_takedamage(a,b) call_generic(3, 2 arg2(a,b))
#define begin_game() call_generic(4, 0 arg0())

