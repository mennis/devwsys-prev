/* Constants */
enum {
	/* Dirs */

	/* Qroot is #defined in ninepserver.h */
	Qdraw = 1,
	Qwsys,

	/* Files */

	/*	Keyboard */
	Qcons,
	Qconsctl,
	Qkeyboard,
	/*	Mouse */
	Qcursor,
	Qmouse,
	Qpointer,
	Qsnarf,
	/*	Window */
	Qkill,
	Qlabel,
	Qwctl,
	Qwinid,
	Qwinname,
	/*	draw/ */
	Qnew,

	/*	draw/n/ */
	Qdrawn,
	Qctl,
	Qdata,
	Qcolormap,
	Qrefresh,
};

/* Error messages */
extern char
	Edeleted[],
	Einterrupted[],
	Einuse[],
	Enofile[],
	Enodrawimage[],
	Enoperm[],
	Eshortread[];

/* Macros */
#define PATH(s, t)	((Path)((s)<<8)|((t)&0xFF))
#define QSLOT(p)	((p)>>8)
#define QTYPE(p)	((p)&0xFF)
#define incref(r)	((*r) = ++(*r))
#define decref(r)	((*r) = --(*r))

void fsinit(Ninepserver*);
Window* qwindow(Qid*);

Ninepops ops;
Ninepserver *server;

/* Devdraw */
DClient* drawnewclient(Draw*);
char* drawopen(Qid *qid, int mode);
char* drawread(Qid qid, char *buf, ulong *n, vlong offset);
char* drawwrite(Qid qid, char *buf, ulong *n, vlong offset);
char* drawclose(Qid qid, int mode);
int drawpath(DClient *cl);
Window* drawwindow(DClient *cl);
