#include "zlib-ng/zlib-ng.h"

int zlibng_deflate(
	unsigned char *dest,
	unsigned long *destLen,
	const unsigned char *source,
	unsigned long sourceLen,
	int level
){
#ifdef FEOS
	return -1;
#else
	zng_stream z;
	int status;
	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;

	if((status=zng_deflateInit2(
		&z, level , Z_DEFLATED, -MAX_WBITS, level, Z_DEFAULT_STRATEGY
	)) != Z_OK){
		return status;
	}

	z.next_in = source;
	z.avail_in = sourceLen;
	z.next_out = dest;
	z.avail_out = *destLen;

	status = zng_deflate(&z, Z_FINISH); //Z_FULL_FLUSH
	if(status != Z_STREAM_END && status != Z_OK){
		//fprintf(stderr,"deflate: %s\n", (z.msg) ? z.msg : "???");
		return status;
	}
	*destLen-=z.avail_out;

	return zng_deflateEnd(&z);
#endif
}
