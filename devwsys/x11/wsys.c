#include <lib9.h>
#include <kern.h>
#include <draw.h>
#include <memdraw.h>
#include <memlayer.h>
#include <cursor.h>
#include "dat.h"
#include "fns.h"
#include "inc.h"
#include "x.h"

void
xbottomwindow(Window *w)
{
	Xwin *xw;

	xw = w->x;
	XLowerWindow(xconn.display, xw->drawable);
	XFlush(xconn.display);
}

void
xtopwindow(Window *w)
{
	Xwin *xw;

	xw = w->x;
	XMapRaised(xconn.display, xw->drawable);
	XFlush(xconn.display);
}

void
xcurrentwindow(Window *w)
{
	Xwin *xw;

	xw = w->x;
	XMapRaised(xconn.display, xw->drawable);
	XSetInputFocus(xconn.display, xw->drawable, RevertToPointerRoot,
		CurrentTime);
	XFlush(xconn.display);
}

void
xresizewindow(Window *w, Rectangle r)
{
	XWindowChanges e;
	int value_mask;
	Xwin *xw;

	xw = w->x;
	memset(&e, 0, sizeof e);
	value_mask = CWX|CWY|CWWidth|CWHeight;
	e.x = r.min.x;
	e.y = r.min.y;
	e.width = Dx(r);
	e.height = Dy(r);
	XConfigureWindow(xconn.display, xw->drawable, value_mask, &e);
	if(w->visible)
		XMapWindow(xconn.display, xw->drawable);
	else
		XUnmapWindow(xconn.display, xw->drawable);
	XFlush(xconn.display);
}

void
xmovewindow(Window *w, Rectangle r)
{
	XWindowChanges e;
	int value_mask;
	Xwin *xw;

	xw = w->x;
	memset(&e, 0, sizeof e);
	value_mask = CWX|CWY|CWWidth|CWHeight;
	e.x = r.min.x;
	e.y = r.min.y;
	e.width = Dx(r);
	e.height = Dy(r);
	XConfigureWindow(xconn.display, xw->drawable, value_mask, &e);
	XFlush(xconn.display);
}
