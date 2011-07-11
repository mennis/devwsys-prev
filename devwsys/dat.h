/* Pixmap undefined */
enum
{
	PMundef = ~0
};

/* Runes */
enum {
	KF=	0xF000,	/* Beginning of private space */
	/* KF|1, KF|2, ..., KF|0xC is F1, F2, ..., F12 */
	Khome=	KF|0x0D,
	Kup=	KF|0x0E,
	Kpgup=	KF|0x0F,
	Kprint=	KF|0x10,
	Kleft=	KF|0x11,
	Kright=	KF|0x12,
	Kdown=	0x80,
	Kview=	0x80,
	Kpgdown=KF|0x13,
	Kins=	KF|0x14,
	Kend=	KF|0x18,

	Kalt=	KF|0x15,
	Kshift=	KF|0x16,
	Kctl=		KF|0x17,
	
	Kcmd=	0xF100	/* Beginning of Cmd+'a', Cmd+'A', etc on Mac */
};

/* biggest cursor size */
enum {
	CursorSize=	32
};

/* Datatypes: */
typedef struct Client Client;
typedef struct DImage DImage;
typedef struct DName DName;
typedef struct Draw Draw;
typedef struct CScreen CScreen;
typedef struct DScreen DScreen;
typedef struct FChar FChar;
typedef struct Kbdbuf Kbdbuf;
typedef struct Refresh Refresh;
typedef struct Refx Refx;
typedef struct Cursor Cursor;
typedef struct Window Window;

/* Drawing device */
#define	NHASH		(1<<5)
#define	HASHMASK	(NHASH-1)

struct Draw
{
	Window*		window;
	Memimage*	screenimage;
	DImage*		screendimage;
	char*		screenname;
	Rectangle		flushrect;
	int			waste;
	DScreen*		dscreen;
};

struct Client
{
	int		r;	// Ref
	DImage*	dimage[NHASH];
	CScreen*	cscreen;
	Refresh*	refresh;
//	Rendez	refrend;
	Draw	*draw;
	uchar*	readdata;
	int		nreaddata;
	int		busy;
	int		clientid;
	int		slot;
	int		refreshme;
	int		infoid;
	int		op;
};

struct Refresh
{
	DImage*		dimage;
	Rectangle	r;
	Refresh*	next;
};

struct Refx
{
	Client*		client;
	DImage*		dimage;
};

struct FChar
{
	int		minx;	/* left edge of bits */
	int		maxx;	/* right edge of bits */
	uchar	miny;	/* first non-zero scan-line */
	uchar	maxy;	/* last non-zero scan-line + 1 */
	schar	left;		/* offset of baseline */
	uchar	width;	/* width of baseline */
};

struct DImage
{
	int		id;
	int		ref;
	char		*name;
	int		vers;
	Memimage*	image;
	int		ascent;
	int		nfchar;
	FChar*	fchar;
	DScreen*	dscreen;		/* 0 if not a window */
	DImage*	fromname;	/* image this one is derived from, by name */
	DImage*	next;
};

struct DName
{
	char		*name;
	Client	*client;
	DImage*	dimage;
	int		vers;
};

struct CScreen
{
	DScreen*	dscreen;
	CScreen*	next;
};

struct DScreen
{
	int		id;
	int		public;
	int		ref;
	DImage	*dimage;
	DImage	*dfill;
	Memscreen*	screen;
	Client*	owner;
	DScreen*	next;
};

/* Used by kbdputc */
struct Kbdbuf
{
	uchar k[5*UTFmax];
	int	alting, nk;
};

/* Pointer */
struct  Mouse
{
	int		buttons;	/* bit array: LMR=124 */
	Point	xy;
	ulong	msec;
};

struct Cursor {
	int	hotx;
	int	hoty;
	int	w;
	int	h;
	uchar	src[(CursorSize/8)*CursorSize];	/* image and mask bitmaps */
	uchar	mask[(CursorSize/8)*CursorSize];
};

/* Window system */
struct Window
{
	int			id;
	int			fullscreen;
	int			deleted;
	int			mouseopen;
	int			mousebuttons;
	int			resized;
	char			*label;
	Draw		draw;
	Kbdbuf		kbd;
	void*		kbdp;
	void*		mousep;
	Cursor		cursor;
	Point		orig;
	Rectangle		screenr;
	Rectangle		newscreenr;
	void			*x;
};

/* Global Vars */
int		debuglevel;
int		nwindow;
Window	**window;
int		nclient;
Client	**client;

