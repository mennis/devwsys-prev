enum {
	KF=	0xF000,	/* Rune: beginning of private Unicode space */
	/* KF|1, KF|2, ..., KF|0xC is F1, F2, ..., F12 */
	Khome=	KF|0x0D,
	Kup=	KF|0x0E,
	Kpgup=	KF|0x0F,
	Kprint=	KF|0x10,
	Kleft=	KF|0x11,
	Kright=	KF|0x12,
	Kdown=	0x80,
	Kview=	0x80,
	Kpgdown=	KF|0x13,
	Kins=	KF|0x14,
	Kend=	KF|0x18,

	Kalt=		KF|0x15,
	Kshift=	KF|0x16,
	Kctl=		KF|0x17,
	
	Kcmd=	0xF100	/* Rune: beginning of Cmd+'a', Cmd+'A', etc on Mac */
};

typedef struct Kbdbuf Kbdbuf;

struct Kbdbuf
{
	Rune r[32];
	int ri;
	int wi;
	int stall;
};

void addkbd(int, Rune);
void matchkbd(int);