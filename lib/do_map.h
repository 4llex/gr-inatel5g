#ifdef __cplusplus
	typedef std::complex<float> cfloat;
	extern "C" {
#else
	typedef float _Complex cfloat;
#endif

#ifndef _DO_MAP_H_
#define _DO_MAP_H_

#include <complex.h>
#include <inttypes.h>
#include <stdlib.h>
//#include "ofmod.h"

typedef enum {
	BPSK   = 0,	// 1 bit per symbol
	QPSK   = 1,	// 2 bit per symbol
	QAM16  = 2,	// 4 bit per symbol
	QAM32  = 3,	// 5 bit per symbol
	QAM64  = 4,	// 6 bit per symbol
	QAM128 = 5,	// 7 bit per symbol
	QAM256 = 6	// 8 bit per symbol
} modname_t;

#define data_t cfloat

void do_map(modname_t, uint8_t*, data_t *, size_t);
void init_constelation(int DACMAX, int HEADROOM, int NFFT);

#endif /* SRC_DO_MAP_H_ */

#ifdef __cplusplus
} // closing brace for extern "C"

#endif
