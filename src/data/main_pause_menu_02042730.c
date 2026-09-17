/* main .data, 0x02042730-0x020427d4: the pause menu task's descriptor and resource names.
 *
 * The task class (0x12 / group 0xf, constructor 02022708, method 020227c0, 0xec-byte state) is
 * instantiated by 02022eb0; the screen files are the pause background (one per language, '&'
 * replaced by the two-letter code below), the icon and message tilemaps and the misc icons.
 */
typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
} GameClassDescriptor;

extern void func_02022708(void);
extern void func_020227c0(void);

/* Set once the pause menu resources are ready (02022eb0 tests and clears it). */
int data_02042730 = 1;

GameClassDescriptor data_02042734 = {
    0x12,  /* nClassId */
    0xf,   /* nGroupId */
    func_02022708,  /* pfnCtor */
    func_020227c0,  /* pfnMethod */
    0xec,  /* nAuxSize */
    0,     /* pArena */
};

char data_02042748[16] = "pause_refresh";
char data_02042758[24] = "pause/pausebg_&.pbg.z";
char data_02042770[24] = "pause/pauseicon.NSCR.z";
char data_02042788[24] = "pause/pausemsg.NSCR.z";
char data_020427a0[24] = "pause/etcicon.NSCR.z";

/* The language suffixes of the pause background, in the game's language-id order. */
char data_020427b8[4] = "zh";
char data_020427bc[4] = "en";
char data_020427c0[4] = "it";
char data_020427c4[4] = "de";
char data_020427c8[4] = "fr";
char data_020427cc[4] = "es";
char data_020427d0[4] = "ja";
