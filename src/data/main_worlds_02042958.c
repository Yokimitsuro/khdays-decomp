/* main .data, 0x02042958-0x02042a70: a 16-colour text palette, three task descriptors, the sound
 * archive and message database paths and the two-letter world directory codes.
 */
typedef unsigned short u16;
typedef unsigned char u8;
typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
} GameClassDescriptor;

extern void func_02030478(void);
extern void func_02030550(void);
extern void func_02030988(void);
extern void func_020309f0(void);
extern void func_02030e7c(void);
extern void func_02030f58(void);
extern int data_0204c024;   /* the main heap arena the three tasks allocate from */

/* A 16-colour BGR555 palette (black, white, black, red, green, blue, yellow, magenta, cyan, ...)
 * loaded by ov000 0204d358 and ov027 02083ccc. */
u16 data_02042958[16] = {
    0x0000, 0x7fff, 0x0000, 0x001f, 0x03e0, 0x7c00, 0x7fe0, 0x7c1f, 0x03ff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2108
};

/* -1 when idle; 020305d8 / 02030610 read and set it. */
int data_02042978 = -1;

GameClassDescriptor data_0204297c = {
    0x3e,  /* nClassId */
    0xf,   /* nGroupId */
    func_02030478,  /* pfnCtor */
    func_02030550,  /* pfnMethod */
    0x30,  /* nAuxSize */
    &data_0204c024,  /* pArena */
};

GameClassDescriptor data_02042990 = {
    0x3e,  /* nClassId */
    0xf,   /* nGroupId */
    func_02030988,  /* pfnCtor */
    func_020309f0,  /* pfnMethod */
    0x74,  /* nAuxSize */
    &data_0204c024,  /* pArena */
};

GameClassDescriptor data_020429a4 = {
    0x2,   /* nClassId */
    0xf,   /* nGroupId */
    func_02030e7c,  /* pfnCtor */
    func_02030f58,  /* pfnMethod */
    0x760, /* nAuxSize */
    &data_0204c024,  /* pArena */
};

/* Two small tables read by 02031600 / 02031618. */
int data_020429b8[4] = { 1, 1, 0, 0 };
int data_020429c8[8] = { 1, 0, 0, 1, 0, 2, 0, 3 };

/* A flag 020329e8 tests. */
int data_020429e8 = 1;

char data_020429ec[24] = "/snd/sound_data.sdat";
char data_02042a04[12] = "/db/db.p2";
char data_02042a10[12] = "/db/db_&.p2";   /* '&' takes the language code */

/* A byte flag and a 3-byte record, 0xff when unset; ov002 / ov022 and 020352cc read them. */
u8 data_02042a1c[1] = { 0xff };   /* a lone byte; the array spelling keeps it out of the word-aligned run */
u8 data_02042a1d[3] = { 0xff, 0, 0 };

/* The two-letter world directory codes ("%s/%s/lv.b.z" of 02035730 takes one). */
char data_02042a20[4] = "do";
char data_02042a24[4] = "lu";
char data_02042a28[4] = "ma";
char data_02042a2c[4] = "le";
char data_02042a30[4] = "de";
char data_02042a34[4] = "r2";
char data_02042a38[4] = "xa";
char data_02042a3c[4] = "ve";
char data_02042a40[4] = "xe";
char data_02042a44[4] = "xo";
char data_02042a48[4] = "ze";
char data_02042a4c[4] = "mi";
char data_02042a50[4] = "ro";
char data_02042a54[4] = "ri";
char data_02042a58[4] = "go";
char data_02042a5c[4] = "ax";
char data_02042a60[4] = "xi";
char data_02042a64[4] = "la";
char data_02042a68[4] = "sa";
char data_02042a6c[4] = "so";
