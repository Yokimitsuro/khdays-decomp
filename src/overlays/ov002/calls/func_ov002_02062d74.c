/*
 * Ov002_StepCaptionScreen - the caption screen's per-frame step.
 *
 * The state word picks one of four handlers out of a table copied to the stack.
 * Once the screen reports it is settled, a sound is played from whichever table
 * the current line calls for, indexed by the player the other overlay names.
 * The progress bar is stepped last, and only while it is wanted.
 *
 * The scene slot is reached as an element of the caption screen's slot table
 * rather than through a cast onto the symbol's address. The two spell the same
 * word, but only the array form makes the compiler materialise the table base
 * ahead of the stack copy and displace it afterwards, which is what the original
 * does; an address plus a constant gets folded into a single pinned operand, and
 * a sized array folds the same way. The size has to stay unknown here.
 *
 * ARM.
 */

typedef unsigned short u16;

typedef struct {
    void (*aStep[4])(void);
} Ov002StepTable;

typedef struct {
    char pad000[8];
    int nState;
    int nLine;
    char pad010[0x98];
    int nBar;
} Ov002CaptionScene;

extern Ov002CaptionScene *data_ov002_0207f62c[];
extern const Ov002StepTable data_ov002_0207e378;
extern const int data_ov002_0207e3c4[];
extern const int data_ov002_0207e368[];

extern int func_02030670(void);
extern int func_ov105_020bd7c4(void);

extern void func_ov002_02053558(int nSound);
extern void func_ov002_020535a4(void);
extern void func_ov002_02062214(void);

int func_ov002_02062d74(void)
{
    Ov002StepTable steps = data_ov002_0207e378;
    Ov002CaptionScene *s = data_ov002_0207f62c[1];
    const int *pTable;

    steps.aStep[s->nState]();

    if (func_02030670() != 0) {
        if (s->nLine == 0) {
            pTable = &data_ov002_0207e3c4[s->nLine * 4];
        } else {
            pTable = data_ov002_0207e368;
        }
        func_ov002_02053558((u16)pTable[func_ov105_020bd7c4()]);
        func_ov002_020535a4();
    }

    if (s->nBar != 0) {
        func_ov002_02062214();
    }
    return 0;
}
