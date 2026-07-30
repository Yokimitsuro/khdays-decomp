/* func_ov008_0206e878 -- Ov008_TickMenuState (268 B, 20 relocs).
 * Per-frame step of a menu sub-state machine, dispatched on p->state (0..6) and advanced by one
 * each call. Returns 1 only from the terminal step (state 6), 0 otherwise.
 *   0: first-time setup -- init the object list at p+0x1cc, clear the tween at p+0x1c, mark
 *      p->field0c, ref up message DBs 0x15/0x13/0x1c and the dynamic one from func_ov008_0206b6e4,
 *      build the menu screen, then func_ov008_0206bfac(p);
 *   1: raise the ready flag (data_ov008_02090f20 = 1) and run the open animation;
 *   2/3: intermediate transition steps;
 *   6: allocate the code node (stored at p+0x23c), apply control value 1, and return 1.
 * Several helpers here (e.g. func_ov008_02051094, func_ov008_0206dd7c) are invoked with only the
 * arguments this state actually sets; the trailing register args they also read are left as the
 * caller's residue, matching the ROM. */
typedef unsigned char u8;

typedef struct Ov008State {
    u8  pad_0000[0x18];
    int state;          /* 0x18: dispatcher step (0..6) */
} Ov008State;

extern int   data_ov008_02090f20;
extern void  func_ov008_0206bd40(void);
extern void  NNS_FndInitList(void *list, int size);
extern void  func_02035f84(void *tween);
extern int   func_ov008_02051094(int id);
extern int   func_ov008_0206b6e4(void);
extern void  func_ov008_0206bdf0(int screen);
extern void  func_ov008_0206bfac(Ov008State *p);
extern void  func_ov008_0206cea0(Ov008State *p, int *flag, int a3, int a4);
extern void  func_ov008_0206dd7c(Ov008State *p);
extern void  func_ov008_0206e1fc(void);
extern void  func_ov008_0206ce84(Ov008State *p);
extern void  func_ov008_0206bca0(Ov008State *p, int newSel, int a3);
extern void  func_ov008_0206c90c(Ov008State *p, int a, int b, int c);
extern int   func_ov008_02050d04(void *fn);
extern void  func_ov008_02050a64(int v);
extern void  func_ov008_0206b814(void);

int func_ov008_0206e878(Ov008State *p, int a2, int a3, int a4)
{
    int result = 0;

    switch (p->state) {
    case 0:
        func_ov008_0206bd40();
        NNS_FndInitList((char *)p + 0x1cc, 0x24);
        func_02035f84((char *)p + 0x1c);
        *(int *)((char *)p + 0xc) = 1;
        func_ov008_02051094(0x15);
        func_ov008_02051094(0x13);
        func_ov008_02051094(0x1c);
        func_ov008_0206bdf0(func_ov008_02051094(func_ov008_0206b6e4()));
        func_ov008_0206bfac(p);
        break;
    case 1:
        data_ov008_02090f20 = 1;
        func_ov008_0206cea0(p, &data_ov008_02090f20, 1, a4);
        func_ov008_0206dd7c(p);
        break;
    case 2:
        func_ov008_0206e1fc();
        func_ov008_0206ce84(p);
        break;
    case 3:
        func_ov008_0206bca0(p, 1, 0);
        func_ov008_0206c90c(p, 0, 0, 1);
        break;
    case 6:
        *(int *)((char *)p + 0x23c) = func_ov008_02050d04(func_ov008_0206b814);
        func_ov008_02050a64(1);
        result = 1;
        break;
    }
    p->state += 1;
    return result;
}
