/* 2011 JGL (yiyus) */
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <lib9.h>
#include <draw.h>
#include <memdraw.h>

#include <ixp.h>

#include "keyboard.h"
#include "mouse.h"
#include "devwsys.h"

extern Ixp9Srv p9srv; /* ixp_fsys.c:/p9srv */

void endconnection(IxpConn*);
void eventfdready(IxpConn*);

int
ixpserve(char *address)
{
	char buf[512];
	int fd;
	IxpServer srv = {0};

	if(!address)
		address = getenv("IXP_ADDRESS");
	if(!address) {
		char *nsdir = ixp_namespace();
		if(mkdir(nsdir, 0700) == -1 && errno != EEXIST) {
			err(1, "mkdir: %s", nsdir);
		}
		snprint(buf, sizeof(buf), "unix!%s/wsys", nsdir);
		address = buf;
	}

	fd = ixp_announce(address);
	if(fd < 0) {
		err(1, "ixp_announce");
	}

	ixp_listen(&srv, fd, &p9srv, ixp_serve9conn, NULL);
	ixp_listen(&srv, xfd(), nil, eventfdready, endconnection);

	return ixp_serverloop(&srv);
}

void
endconnection(IxpConn *c)
{
	USED(c);
	xclose();
}

void
eventfdready(IxpConn *c)
{
	int closedwin;

	USED(c);
	closedwin = xnextevent();
	if(closedwin >= 0)
		deletewin(closedwin);
}