typedef unsigned char u8;
typedef unsigned short u16;

extern int func_02030670(void);
extern void func_ov002_0206f788(int nSlot, int nValue);
extern u16 func_ov002_0206fb84(int nKind, void *pOut);

/* Advance the phase. With no session active the local handler runs and the
 * phase proceeds; otherwise a kind-7 request is submitted and the phase waits
 * while the returned handle is still unallocated. */
int func_ov002_0206f1fc(void)
{
    u8 stk[8];

    stk[1] = 0;
    *(int *)(stk + 4) = 0;

    if (func_02030670() == 0) {
        func_ov002_0206f788(stk[1], *(int *)(stk + 4));
    } else if (func_ov002_0206fb84(7, stk) == 0xffff) {
        return 0;
    }

    return 1;
}
