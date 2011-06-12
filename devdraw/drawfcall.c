/* 2011 JGL (yiyus) */
#include <lib9.h>
#include <draw.h>
#include <memdraw.h>

#include "mouse.h"
#include "devdraw.h"
#include "drawfcall.h"

int lookupwin(Window*);

void
runmsg(Window *w, Wsysmsg *m, void *v)
{
	int i;
	Mousebuf *mouse;
	Tagbuf *mousetags;
	int havemin;

	i = lookupwin(w);
	if(i < 0)
		return;
	mouse = &w->mouse;
	mousetags = &w->mousetags;

	switch(m->type){
	case Tinit:
		w->r = xwinrectangle(m->label, m->winsize, &havemin);
		w->x = xcreatewin(m->label, m->winsize, w->r);
		w->r = xmapwin(w->x, havemin, w->r);
		w->img = xallocmemimage(w->x);
//		replymsg(w, m);
		break;

	case Trdmouse:
		mousetags->t[mousetags->wi] = m->tag;
		mousetags->r[mousetags->wi] = v;
		mousetags->wi++;
		if(mousetags->wi == nelem(mousetags->t))
			mousetags->wi = 0;
		if(mousetags->wi == mousetags->ri)
			sysfatal("too many queued mouse reads");
		// fprint(2, "mouse unstall\n");
		mouse->stall = 0;
		matchmouse(i);
		break;

/***
	case Trdkbd:
		kbdtags.t[kbdtags.wi++] = m->tag;
		if(kbdtags.wi == nelem(kbdtags.t))
			kbdtags.wi = 0;
		if(kbdtags.wi == kbdtags.ri)
			sysfatal("too many queued keyboard reads");
		kbd.stall = 0;
		matchkbd();
		break;

	case Tmoveto:
		_xmoveto(m->mouse.xy);
		replymsg(m);
		break;

	case Tcursor:
		if(m->arrowcursor)
			_xsetcursor(nil);
		else
			_xsetcursor(&m->cursor);
		replymsg(m);
		break;
			
	case Tbouncemouse:
		_xbouncemouse(&m->mouse);
		replymsg(m);
		break;

	case Tlabel:
		_xsetlabel(m->label);
		replymsg(m);
		break;

	case Trdsnarf:
		m->snarf = _xgetsnarf();
		replymsg(m);
		free(m->snarf);
		break;

	case Twrsnarf:
		_xputsnarf(m->snarf);
		replymsg(m);
		break;

	case Trddraw:
		n = m->count;
		if(n > sizeof buf)
			n = sizeof buf;
		n = _drawmsgread(buf, n);
		if(n < 0)
			replyerror(m);
		else{
			m->count = n;
			m->data = buf;
			replymsg(m);
		}
		break;

	case Twrdraw:
		if(_drawmsgwrite(m->data, m->count) < 0)
			replyerror(m);
		else
			replymsg(m);
		break;
	
	case Ttop:
		_xtopwindow();
		replymsg(m);
		break;
	
	case Tresize:
		_xresizewindow(m->rect);
		replymsg(m);
		break;
***/
	}
}

void
replymsg(Window *w, Wsysmsg *m)
{
	fs_reply(w, m);
}

int
lookupwin(Window *w)
{
	int i;

	for(i = 0; i < nwindow; i++){
		if(window[i] == w)
			return i;
	}
	return -1;
}