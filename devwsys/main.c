/* 2011 JGL (yiyus) */
#include <lib9.h>
#include <draw.h>
#include <memdraw.h>
#include <cursor.h>
#include "dat.h"
#include "fns.h"

#define GETARG() (cp-*argv == strlen(*argv)-1) ? *++argv : cp+1

int debug = 0;
int drawdebug; /* used by libmemdraw */
int nwindow;
Window **window;

/* used by libmemdraw */
int
iprint(char* fmt, ...)
{
	int n;
	va_list args;

	va_start(args, fmt);
	n = vfprint(2, fmt, args);
	va_end(args);
	return n;
}

int
main(int argc, char **argv)
{
	int xfd;
	char *address, *cp, *err;
	char *argv0;

	address = nil;
	/* XXX TODO: use ARGBEGIN, ... from <ixp_local.h> */
	argv0 = argv[0];
	while(*++argv) {
		if(strcmp(*argv, "--") == 0 || !(**argv == '-')) {
			break;
		}
		for(cp=*argv+1; cp<*argv+strlen(*argv); ++cp) {
			switch(*cp){
			case 'd':
				debug |= Debug9p;
				break;
			case 'D':
				debug |= Debugdraw;
				break;
			case 'E':
				debug |= Debugevent;
				break;
			case 'a':
				address = GETARG();
				break;
			default:
				fprint(1, "usage: %s [-d] [ -a address ]", argv0);
				exit(1);
			}
		}
	}

	/* Init memdraw */
	drawdebug = debug&Debugdraw;
	memimageinit();

	/* Connect to X */
	xfd = xinit();
	if(xfd < 0)
		fatal("unable to connect to X server");

	/* 9p server loop */
	err = fsloop(address, xfd);

	xclose();
	if(err != nil)
		fatal("%s", err);
	return 0;
}

void
_assert(char *fmt)
{
	fatal("assert failed: %s", fmt);
}
