typedef unsigned char u8;

extern char *data_ov002_0207fa00;
/* Boot mode flags; bit 2 marks a run that came up without the front end. */
extern u8 data_0204c240;

/* Non-zero while the scene is already suspended for something else. */
extern int func_ov002_0206b828(void);
extern int func_02023588(int nCue);
extern void func_02023a44(int nHandle, void (*pfnStep)(void));
extern void func_020208d0(int nValue);
extern void func_02020878(int nValue);
extern void func_ov002_02068118(void);

/* Put the mission scene into its paused state.
 *
 * A scene that is already stopping or stopped (either of the low two bits of
 * the state word) is left alone.  Otherwise the pause cue is offered first --
 * only for a run that came up through the front end, and only while nothing
 * else holds the scene -- and taking it hands the scene over to the pause
 * step.  Whether or not the cue was taken, the scene is marked paused and both
 * the sound and the input side are told to go quiet.
 */
void func_ov002_0206d8a0(void)
{
    char *pCtx;

    pCtx = data_ov002_0207fa00;
    if ((*(int *)(pCtx + 0x8b64) & 3) != 0) {
        return;
    }

    if ((data_0204c240 & 4) == 0 && func_ov002_0206b828() != 0
        && func_02023588(0x20ef) != 0) {
        *(u8 *)(pCtx + 0x8b68) = 0x10;
        func_02023a44(*(int *)pCtx, func_ov002_02068118);
    }

    if (func_ov002_0206b828() != 0) {
        return;
    }

    *(int *)(pCtx + 0x8b64) |= 1;
    *(u8 *)(pCtx + 0x8b68) |= 0x10;
    if ((data_0204c240 & 4) != 0) {
        func_020208d0(0);
    }
    func_02020878(0);
}
