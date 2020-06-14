#define BUF_SIZE 1
#define OUT_SIZE 256
#define DEFAULT_ENC "IBM437"
#define DEFAULT_TARGET_ENC "UTF-8"
#include <stdio.h>
#include <unistd.h>
#include <iconv.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char **argv)
{
  char buffer[BUF_SIZE+1];
  char outbuf[OUT_SIZE+1];
  char *inptr = buffer;
  char *outptr = outbuf;
  size_t i;
  size_t in;
  size_t out;
  size_t outlen;
  size_t avail=OUT_SIZE;
  iconv_t converter;
  char lang[1024];
  char *chrset;
  char *fromchrset=DEFAULT_ENC;
  if (argc >= 2) {
	fromchrset=argv[1];
  }
  strcpy(lang,getenv("LANG"));
  chrset=strchr(lang,'.');
  if (chrset==NULL) {
	chrset=lang;
  } else {
	chrset++;
  }
  if (strcmp(chrset,"en_US") == 0) {
	chrset=DEFAULT_ENC;
  }
  if (strlen(chrset)<1) {
        chrset=DEFAULT_TARGET_ENC;
  }
  // fprintf(stderr,"chrset=%s\n",chrset);
  converter=iconv_open(chrset, fromchrset);
  if (converter == (iconv_t) -1) {
  	// fprintf(stderr,"Trapped error.\n");
	if (errno == EINVAL) {
        	chrset=DEFAULT_TARGET_ENC;
  		converter=iconv_open(chrset, fromchrset);
  		if (converter == (iconv_t) -1) {
			fprintf(stderr,"Fatal error, encoding not supported.\nTried %s and UTF-8 for the target.\nSource encoding=%s.\n",lang,fromchrset);
			fprintf(stderr,"To get a list of supported encodings, try: iconv -l\n");
			exit(1);
		}
	} else {
		fprintf(stderr,"Error setting up conversion, target character encoding was %s.\n", chrset);
	}
  }
  do
  {
    in=fread(buffer, sizeof(char), BUF_SIZE, stdin);
    i=in;
    avail=OUT_SIZE;
    inptr=buffer;
    outptr=outbuf;
    out=iconv(converter, &inptr, &i, &outptr, &avail); 
    *outptr=L'\0';
    outlen=strlen(outbuf);
    fwrite(outbuf, sizeof(char), outlen, stdout);
    fflush(stdout);
  }
  while (in == BUF_SIZE);
  iconv_close(converter);
}
