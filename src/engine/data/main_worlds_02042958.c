#include "nitro/types.h"

#include "game/class_descriptor.h"
/* main .data, 0x02042958-0x02042a70: a 16-colour text palette, three task descriptors, the sound
 * archive and message database paths and the two-letter world directory codes.
 */

extern void Session_Init(void);
extern void Session_Destroy(void);
extern void Session_Init_2(void);
extern void CloseDebugOverlay(void);
extern void MsgQueue_Init_2(void);
extern void Session_Shutdown(void);
extern int gMainHeap;   /* the main heap arena the three tasks allocate from */

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
    Session_Init,  /* pfnCtor */
    Session_Destroy,  /* pfnMethod */
    0x30,  /* nAuxSize */
    &gMainHeap,  /* pArena */
};

GameClassDescriptor data_02042990 = {
    0x3e,  /* nClassId */
    0xf,   /* nGroupId */
    Session_Init_2,  /* pfnCtor */
    CloseDebugOverlay,  /* pfnMethod */
    0x74,  /* nAuxSize */
    &gMainHeap,  /* pArena */
};

GameClassDescriptor data_020429a4 = {
    0x2,   /* nClassId */
    0xf,   /* nGroupId */
    MsgQueue_Init_2,  /* pfnCtor */
    Session_Shutdown,  /* pfnMethod */
    0x760, /* nAuxSize */
    &gMainHeap,  /* pArena */
};

/* Two small tables read by 02031600 / 02031618. */
int gSessionSetup[4] = { 1, 1, 0, 0 };
int data_020429c8[8] = { 1, 0, 0, 1, 0, 2, 0, 3 };

/* A flag 020329e8 tests. */
int data_020429e8 = 1;

char gSndSoundDataPath[24] = "/snd/sound_data.sdat";
char gDbDbPath[12] = "/db/db.p2";
char gDbDbPath_2[12] = "/db/db_&.p2";   /* '&' takes the language code */

/* A byte flag and a 3-byte record, 0xff when unset; ov002 / ov022 and 020352cc read them. */
u8 data_02042a1c[1] = { 0xff };   /* a lone byte; the array spelling keeps it out of the word-aligned run */
u8 data_02042a1d[3] = { 0xff, 0, 0 };

/* The two-letter world directory codes ("%s/%s/lv.b.z" of 02035730 takes one). */
char gDoName[4] = "do";
char gLuName[4] = "lu";
char gMaName[4] = "ma";
char gLeName[4] = "le";
char gDeName_2[4] = "de";
char gR2Name[4] = "r2";
char gXaName[4] = "xa";
char gVeName[4] = "ve";
char gXeName[4] = "xe";
char gXoName[4] = "xo";
char gZeName[4] = "ze";
char gMiName[4] = "mi";
char gRoName[4] = "ro";
char gRiName[4] = "ri";
char gGoName[4] = "go";
char gAxName[4] = "ax";
char gXiName[4] = "xi";
char gLaName[4] = "la";
char gSaName[4] = "sa";
char gSoName[4] = "so";
