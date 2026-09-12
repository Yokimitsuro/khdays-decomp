/* Ov011_StartTitleExit -- leave the title: scene mode 4, the exit window
 * opens at the current cursor timer and closes 30 frames later, both
 * engines switch to display mode 1 with BG1/BG3 (main) and BG1 (sub), and
 * the fade table entry 0 is kicked for 30 frames.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Ov011ExitWindow */
struct ExitWindow {
    u16 nStart;                  /* 0x00 */
    u16 nEnd;                    /* 0x02 */
};

/* Ov011Scene */
struct Scene {
    u8 pad00000[4];
    int nMode;                   /* 0x00004 */
    u8 pad00008[0x2cf44];
    struct ExitWindow exit;      /* 0x2cf4c */
};

/* Ov011Globals */
struct Globals {
    int nCursor;                 /* 0x00 */
    struct Scene *pScene;        /* 0x04 */
};

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)
#define DISPCNT_BG_MASK 0x1f00
#define DISPCNT_MAIN_BGS 0x1500
#define DISPCNT_SUB_BGS 0x1100
#define MODE_EXIT 4
#define EXIT_FRAMES 0x1e

extern struct Globals data_ov011_0205e960;

extern void func_02033fec(int nEntry, int nFrames);                             /* Table_TailCallWithEntry */

void func_ov011_0205c2fc(void)
{
    struct ExitWindow *pExit;

    data_ov011_0205e960.pScene->nMode = MODE_EXIT;
    pExit = &data_ov011_0205e960.pScene->exit;
    pExit->nStart = data_ov011_0205e960.nCursor;
    pExit->nEnd = data_ov011_0205e960.nCursor + EXIT_FRAMES;
    REG_DISPCNT = (REG_DISPCNT & ~DISPCNT_BG_MASK) | DISPCNT_MAIN_BGS;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~DISPCNT_BG_MASK) | DISPCNT_SUB_BGS;
    func_02033fec(0, EXIT_FRAMES);
}
