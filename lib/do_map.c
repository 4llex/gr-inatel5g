/*
 ============================================================================
 Name        : do_qammap.c
 Author      : Wheberth Damascena Dias <wheberth@gmail.com>
 Version     : 0.0
 Copyright   : Copyright(c)2018 Wheberth - All rights reserved
 Description : Read bytes (unpacked) from stdin and map to QAM
 History     : v0.0 - 27/03/2018: File created
 History     : v0.1 - 31/03/2018: Added constellation initialization
 ============================================================================
 */

#include "do_map.h"
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h>
#include <math.h>
#include <inttypes.h>

#define N_MODULATIONS 7
#define MOD_MAX_BPSK   1		// Mask BPSK symbol bits
#define MOD_MAX_QPSK   3		// Mask QPSK symbol bits
#define MOD_MAX_16QAM  15		// Mask 16QAM symbol bits
#define MOD_MAX_32QAM  31		// Mask 32QAM symbol bits
#define MOD_MAX_64QAM  63		// Mask 64QAM symbol bits
#define MOD_MAX_128QAM 127		// Mask 128QAM symbol bits
#define MOD_MAX_256QAM 255		// Mask 256QAM symbol bits


//#define DACNBITS 16			// integer Range to make output signal comply with
//#define DACMAX +(pow(2,DACNBITS-1)-1)
//#define DACMIN -(pow(2,DACNBITS-1)-0)
//#define HEADROOM 3.0f  		// Ratio between full scale and Signal standard deviation



static data_t MAP_BPSK[] = { // gray mapping generated by Juliano
	( -1.0 ),( 1.0 )};
static data_t MAP_QPSK[] = { // gray mapping generated by Juliano
	(-1 -1*I), (-1 +1*I), (1 -1*I), (+1 +1*I),   //       0,    1,    2,    3
	
};

//========  16QAM  ========
static  data_t MAP_16QAM[] = { // gray mapping generated by Juliano
	(-3 -3*I), (-3 -1*I), (-3 +3*I), (-3 +1*I),  //       0,    1,    2,    3
	(-1 -3*I), (-1 -1*I), (-1 +3*I), (-1 +1*I),  //       4,    5,    6,    7
	(+3 -3*I), (+3 -1*I), (+3 +3*I), (+3 +1*I),  //       8,    9,   10,   11
	(+1 -3*I), (+1 -1*I), (+1 +3*I), (+1 +1*I),  //      12,   13,   14,   15
};

//========  32QAM  ======== 
static data_t MAP_32QAM[] = { // gray mapping matlab compatible
	( -3.0  +5.0*I),( -1.0  +5.0*I),( -3.0  -5.0*I),( -1.0  -5.0*I),   //       0,    1,    2,    3
	( -5.0  +3.0*I),( -5.0  +1.0*I),( -5.0  -3.0*I),( -5.0  -1.0*I),   //       4,    5,    6,    7
	( -1.0  +3.0*I),( -1.0  +1.0*I),( -1.0  -3.0*I),( -1.0  -1.0*I),   //       8,    9,   10,   11
	( -3.0  +3.0*I),( -3.0  +1.0*I),( -3.0  -3.0*I),( -3.0  -1.0*I),   //      12,   13,   14,   15
	( +3.0  +5.0*I),( +1.0  +5.0*I),( +3.0  -5.0*I),( +1.0  -5.0*I),   //      16,   17,   18,   19
	( +5.0  +3.0*I),( +5.0  +1.0*I),( +5.0  -3.0*I),( +5.0  -1.0*I),   //      20,   21,   22,   23
	( +1.0  +3.0*I),( +1.0  +1.0*I),( +1.0  -3.0*I),( +1.0  -1.0*I),   //      24,   25,   26,   27
	( +3.0  +3.0*I),( +3.0  +1.0*I),( +3.0  -3.0*I),( +3.0  -1.0*I),   //      28,   29,   30,   31
};

//========  64QAM  ========
static data_t MAP_64QAM[] = { // gray mapping matlab compatible
	(-7 -7*I), (-7 -5*I), (-7 -1*I), (-7 -3*I),   //       0,    1,    2,    3
	(-7 +7*I), (-7 +5*I), (-7 +1*I), (-7+ 3*I),   //       4,    5,    6,    7
	(-5 -7*I), (-5 -5*I), (-5 -1*I), (-5 -3*I),   //       8,    9,   10,   11
	(-5 +7*I), (-5 +5*I), (-5 +1*I), (-5 +3*I),   //      12,   13,   14,   15
	(-1 -7*I), (-1 -5*I), (-1 -1*I), (-1 -3*I),   //      16,   17,   18,   19
	(-1 +7*I), (-1 +5*I), (-1 +1*I), (-1 +3*I),   //      20,   21,   22,   23
	(-3 -7*I), (-3 -5*I), (-3 -1*I), (-3 -3*I),   //      24,   25,   26,   27
	(-3 +7*I), (-3 +5*I), (-3 +1*I), (-3 +3*I),   //      28,   29,   30,   31
	( 7 -7*I), ( 7 -5*I), ( 7 -1*I), ( 7 -3*I),   //      32,   33,   34,   35
	( 7 +7*I), ( 7 +5*I), ( 7 +1*I), ( 7 +3*I),   //      36,   37,   38,   39
	( 5 -7*I), ( 5 -5*I), ( 5 -1*I), ( 5 -3*I),   //      40,   41,   42,   43
	( 5 +7*I), ( 5 +5*I), ( 5 +1*I), ( 5 +3*I),   //      44,   45,   46,   47
	( 1 -7*I), ( 1 -5*I), ( 1 -1*I), ( 1 -3*I),   //      48,   49,   50,   51
	( 1 +7*I), ( 1 +5*I), ( 1 +1*I), ( 1 +3*I),   //      52,   53,   54,   55
	( 3 -7*I), ( 3 -5*I), ( 3 -1*I), ( 3 -3*I),   //      56,   57,   58,   59
	( 3 +7*I), ( 3 +5*I), ( 3 +1*I), ( 3 +3*I),   //      60,   61,   62,   63	
};

//========  128QAM  ========
static data_t MAP_128QAM[] = { // gray mapping matlab compatible
	( -7.0  +9.0*I),( -7.0 +11.0*I),( -1.0  +9.0*I),( -1.0 +11.0*I),   //       0,    1,    2,    3
	( -7.0  -9.0*I),( -7.0 -11.0*I),( -1.0  -9.0*I),( -1.0 -11.0*I),   //       4,    5,    6,    7
	( -5.0  +9.0*I),( -5.0 +11.0*I),( -3.0  +9.0*I),( -3.0 +11.0*I),   //       8,    9,   10,   11
	( -5.0  -9.0*I),( -5.0 -11.0*I),( -3.0  -9.0*I),( -3.0 -11.0*I),   //      12,   13,   14,   15
	( -9.0  +7.0*I),( -9.0  +5.0*I),( -9.0  +1.0*I),( -9.0  +3.0*I),   //      16,   17,   18,   19
	( -9.0  -7.0*I),( -9.0  -5.0*I),( -9.0  -1.0*I),( -9.0  -3.0*I),   //      20,   21,   22,   23
	(-11.0  +7.0*I),(-11.0  +5.0*I),(-11.0  +1.0*I),(-11.0  +3.0*I),   //      24,   25,   26,   27
	(-11.0  -7.0*I),(-11.0  -5.0*I),(-11.0  -1.0*I),(-11.0  -3.0*I),   //      28,   29,   30,   31
	( -1.0  +7.0*I),( -1.0  +5.0*I),( -1.0  +1.0*I),( -1.0  +3.0*I),   //      32,   33,   34,   35
	( -1.0  -7.0*I),( -1.0  -5.0*I),( -1.0  -1.0*I),( -1.0  -3.0*I),   //      36,   37,   38,   39
	( -3.0  +7.0*I),( -3.0  +5.0*I),( -3.0  +1.0*I),( -3.0  +3.0*I),   //      40,   41,   42,   43
	( -3.0  -7.0*I),( -3.0  -5.0*I),( -3.0  -1.0*I),( -3.0  -3.0*I),   //      44,   45,   46,   47
	( -7.0  +7.0*I),( -7.0  +5.0*I),( -7.0  +1.0*I),( -7.0  +3.0*I),   //      48,   49,   50,   51
	( -7.0  -7.0*I),( -7.0  -5.0*I),( -7.0  -1.0*I),( -7.0  -3.0*I),   //      52,   53,   54,   55
	( -5.0  +7.0*I),( -5.0  +5.0*I),( -5.0  +1.0*I),( -5.0  +3.0*I),   //      56,   57,   58,   59
	( -5.0  -7.0*I),( -5.0  -5.0*I),( -5.0  -1.0*I),( -5.0  -3.0*I),   //      60,   61,   62,   63
	( +7.0  +9.0*I),( +7.0 +11.0*I),( +1.0  +9.0*I),( +1.0 +11.0*I),   //      64,   65,   66,   67
	( +7.0  -9.0*I),( +7.0 -11.0*I),( +1.0  -9.0*I),( +1.0 -11.0*I),   //      68,   69,   70,   71
	( +5.0  +9.0*I),( +5.0 +11.0*I),( +3.0  +9.0*I),( +3.0 +11.0*I),   //      72,   73,   74,   75
	( +5.0  -9.0*I),( +5.0 -11.0*I),( +3.0  -9.0*I),( +3.0 -11.0*I),   //      76,   77,   78,   79
	( +9.0  +7.0*I),( +9.0  +5.0*I),( +9.0  +1.0*I),( +9.0  +3.0*I),   //      80,   81,   82,   83
	( +9.0  -7.0*I),( +9.0  -5.0*I),( +9.0  -1.0*I),( +9.0  -3.0*I),   //      84,   85,   86,   87
	(+11.0  +7.0*I),(+11.0  +5.0*I),(+11.0  +1.0*I),(+11.0  +3.0*I),   //      88,   89,   90,   91
	(+11.0  -7.0*I),(+11.0  -5.0*I),(+11.0  -1.0*I),(+11.0  -3.0*I),   //      92,   93,   94,   95
	( +1.0  +7.0*I),( +1.0  +5.0*I),( +1.0  +1.0*I),( +1.0  +3.0*I),   //      96,   97,   98,   99
	( +1.0  -7.0*I),( +1.0  -5.0*I),( +1.0  -1.0*I),( +1.0  -3.0*I),   //     100,  101,  102,  103
	( +3.0  +7.0*I),( +3.0  +5.0*I),( +3.0  +1.0*I),( +3.0  +3.0*I),   //     104,  105,  106,  107
	( +3.0  -7.0*I),( +3.0  -5.0*I),( +3.0  -1.0*I),( +3.0  -3.0*I),   //     108,  109,  110,  111
	( +7.0  +7.0*I),( +7.0  +5.0*I),( +7.0  +1.0*I),( +7.0  +3.0*I),   //     112,  113,  114,  115
	( +7.0  -7.0*I),( +7.0  -5.0*I),( +7.0  -1.0*I),( +7.0  -3.0*I),   //     116,  117,  118,  119
	( +5.0  +7.0*I),( +5.0  +5.0*I),( +5.0  +1.0*I),( +5.0  +3.0*I),   //     120,  121,  122,  123
	( +5.0  -7.0*I),( +5.0  -5.0*I),( +5.0  -1.0*I),( +5.0  -3.0*I),   //     124,  125,  126,  127
};

//========  256QAM  ========
static data_t MAP_256QAM[] = { // gray mapping matlab compatible
	(-15 -15*I), (-15 -13*I), (-15 -9*I), (-15 -11*I),   //       0,    1,    2,    3
	(-15 -1*I),  (-15 -3*I),  (-15 -7*I), (-15 -5*I),    //       4,    5,    6,    7
	(-15 +15*I), (-15 +13*I), (-15 +9*I), (-15 +11*I),   //       8,    9,   10,   11
	(-15 +1*I),  (-15 +3*I),  (-15 +7*I), (-15 +5*I),    //      12,   13,   14,   15
	(-13 -15*I), (-13 -13*I), (-13 -9*I), (-13 -11*I),   //      16,   17,   18,   19
	(-13 -1*I),  (-13 -3*I),  (-13 -7*I), (-13 -5*I),    //      20,   21,   22,   23
	(-13 +15*I), (-13 +13*I), (-13 +9*I), (-13 +11*I),   //      24,   25,   26,   27
	(-13 +1*I),  (-13 +3*I),  (-13 +7*I), (-13 +5*I),    //      28,   29,   30,   31
	(-9 -15*I),  (-9 -13*I),  (-9 -9*I),  (-9 -11*I),    //      32,   33,   34,   35
	(-9 -1*I),   (-9 -3*I),   (-9 -7*I),  (-9 -5*I),     //      36,   37,   38,   39
	(-9 +15*I),  (-9 +13*I),  (-9 +9*I),  (-9 +11*I),    //      40,   41,   42,   43
	(-9 +1*I),   (-9 +3*I),   (-9 +7*I),  (-9 +5*I),     //      44,   45,   46,   47
	(-11 -15*I), (-11 -13*I), (-11 -9*I), (-11 -11*I),   //      48,   49,   50,   51
	(-11 -1*I),  (-11 -3*I),  (-11 -7*I), (-11 -5*I),    //      52,   53,   54,   55
	(-11 +15*I), (-11 +13*I), (-11 +9*I), (-11 +11*I),   //      56,   57,   58,   59
	(-11 +1*I),  (-11 +3*I),  (-11 +7*I), (-11 +5*I),    //      60,   61,   62,   63
	(-1 -15*I),  (-1 -13*I),  (-1 -9*I),  (-1 -11*I),    //      64,   65,   66,   67
	(-1 -1*I),   (-1 -3*I),   (-1 -7*I),  (-1 -5*I),     //      68,   69,   70,   71
	(-1 +15*I),  (-1 +13*I),  (-1 +9*I),  (-1 +11*I),    //      72,   73,   74,   75
	(-1 +1*I),   (-1 +3*I),   (-1 +7*I),  (-1 +5*I),     //      76,   77,   78,   79
	(-3 -15*I),  (-3 -13*I),  (-3 -9*I),  (-3 -11*I),    //      80,   81,   82,   83
	(-3 -1*I),   (-3 -3*I),   (-3 -7*I),  (-3 -5*I),     //      84,   85,   86,   87
	(-3 +15*I),  (-3 +13*I),  (-3 +9*I),  (-3 +11*I),    //      88,   89,   90,   91
	(-3 +1*I),   (-3 +3*I),   (-3 +7*I),  (-3 +5*I),     //      92,   93,   94,   95
	(-7 -15*I),  (-7 -13*I),  (-7 -9*I),  (-7 -11*I),    //      96,   97,   98,   99
	(-7 -1*I),   (-7 -3*I),   (-7 -7*I),  (-7 -5*I),     //     100,  101,  102,  103
	(-7 +15*I),  (-7 +13*I),  (-7 +9*I),  (-7 +11*I),    //     104,  105,  106,  107
	(-7 +1*I),   (-7 +3*I),   (-7 +7*I),  (-7 +5*I),     //     108,  109,  110,  111
	(-5 -15*I),  (-5 -13*I),  (-5 -9*I),  (-5 -11*I),    //     112,  113,  114,  115
	(-5 -1*I),   (-5 -3*I),   (-5 -7*I),  (-5 -5*I),     //     116,  117,  118,  119
	(-5 +15*I),  (-5 +13*I),  (-5 +9*I),  (-5 +11*I),    //     120,  121,  122,  123
	(-5 +1*I),   (-5 +3*I),   (-5 +7*I),  (-5 +5*I),     //     124,  125,  126,  127
	(15 -15*I),  (15 -13*I),  (15 -9*I),  (15 -11*I),    //     128,  129,  130,  131
	(15 -1*I),   (15 -3*I),   (15 -7*I),  (15 -5*I),     //     132,  133,  134,  135
	(15 +15*I),  (15 +13*I),  (15 +9*I),  (15 +11*I),    //     136,  137,  138,  139
	(15 +1*I),   (15 +3*I),   (15 +7*I),  (15 +5*I),     //     140,  141,  142,  143
	(13 -15*I),  (13 -13*I),  (13 -9*I),  (13 -11*I),    //     144,  145,  146,  147
	(13 -1*I),   (13 -3*I),   (13 -7*I),  (13 -5*I),     //     148,  149,  150,  151
	(13 +15*I),  (13 +13*I),  (13 +9*I),  (13 +11*I),    //     152,  153,  154,  155
	(13 +1*I),   (13 +3*I),   (13 +7*I),  (13 +5*I),     //     156,  157,  158,  159
	(9 -15*I),   (9 -13*I),   (9 -9*I),   (9 -11*I),     //     160,  161,  162,  163
	(9 -1*I),    (9 -3*I),    (9 -7*I),   (9 -5*I),      //     164,  165,  166,  167
	(9 +15*I),   (9 +13*I),   (9 +9*I),   (9 +11*I),     //     168,  169,  170,  171
	(9 +1*I),    (9 +3*I),    (9 +7*I),   (9 +5*I),      //     172,  173,  174,  175
	(11 -15*I),  (11 -13*I),  (11 -9*I),  (11 -11*I),    //     176,  177,  178,  179
	(11 -1*I),   (11 -3*I),   (11 -7*I),  (11 -5*I),     //     180,  181,  182,  183
	(11 +15*I),  (11 +13*I),  (11 +9*I),  (11 +11*I),    //     184,  185,  186,  187
	(11 +1*I),   (11 +3*I),   (11 +7*I),  (11 +5*I),     //     188,  189,  190,  191
	(1 -15*I),   (1 -13*I),   (1 -9*I),   (1 -11*I),     //     192,  193,  194,  195
	(1 -1*I),    (1 -3*I),    (1 -7*I),   (1 -5*I),      //     196,  197,  198,  199
	(1 +15*I),   (1 +13*I),   (1 +9*I),   (1 +11*I),     //     200,  201,  202,  203
	(1 +1*I),    (1 +3*I),    (1 +7*I),   (1 +5*I),      //     204,  205,  206,  207
	(3 -15*I),   (3 -13*I),   (3 -9*I),   (3 -11*I),     //     208,  209,  210,  211
	(3 -1*I),    (3 -3*I),    (3 -7*I),   (3 -5*I),      //     212,  213,  214,  215
	(3 +15*I),   (3 +13*I),   (3 +9*I),   (3 +11*I),     //     216,  217,  218,  219
	(3 +1*I),    (3 +3*I),    (3 +7*I),   (3 +5*I),      //     220,  221,  222,  223
	(7 -15*I),   (7 -13*I),   (7 -9*I),   (7 -11*I),     //     224,  225,  226,  227
	(7 -1*I),    (7 -3*I),    (7 -7*I),   (7 -5*I),      //     228,  229,  230,  231
	(7 +15*I),   (7 +13*I),   (7 +9*I),   (7 +11*I),     //     232,  233,  234,  235
	(7 +1*I),    (7 +3*I),    (7 +7*I),   (7 +5*I),      //     236,  237,  238,  239
	(5 -15*I),   (5 -13*I),   (5 -9*I),   (5 -11*I),     //     240,  241,  242,  243
	(5 -1*I),    (5 -3*I),    (5 -7*I),   (5 -5*I),      //     244,  245,  246,  247
	(5 +15*I),   (5 +13*I),   (5 +9*I),   (5 +11*I),     //     248,  249,  250,  251
	(5 +1*I),    (5 +3*I),    (5 +7*I),   (5 +5*I),      //     252,  253,  254,  255
};



static data_t *map[]  = {    MAP_BPSK, 	   MAP_QPSK,     MAP_16QAM,     MAP_32QAM,     MAP_64QAM,     MAP_128QAM,     MAP_256QAM};
static uint8_t	max[]  = {MOD_MAX_BPSK, MOD_MAX_QPSK, MOD_MAX_16QAM, MOD_MAX_32QAM, MOD_MAX_64QAM, MOD_MAX_128QAM, MOD_MAX_256QAM};
static double energy[]= {        1.0f,         2.0f,         10.0f,         20.0f,         42.0f,          82.0f,         170.0f};



void init_constelation(int DACMAX, int HEADROOM, int NFFT){
	// Make amplitude normalization of the constellation symbols to allow better
	// exploit of DAC range without the need of scaling running on the loop. This
	// is done only once at initialization, do not call more than once.
	static bool already_called = false;
	if (!already_called){
		for (size_t mod=0;mod<N_MODULATIONS;mod++){
			double norm=((DACMAX)/(HEADROOM*(sqrt(energy[mod]*NFFT))));
			for(size_t sym=0;sym<=max[mod];sym++){
				(map[mod])[sym]=(map[mod])[sym]*norm;
			}
		}
		already_called=true;
	}
}
#pragma omp declare simd
void do_map(modname_t mod, uint8_t* in, data_t *out, size_t nbytes) {
	for (size_t byte=0;byte<nbytes;byte++){
		out[byte] = (map[mod])[(in[byte] & (max[mod]))];
	}
}

