/* func_ov025_020a3f0c -- Ov008_TickMenuState (268 B, 20 relocs).
 * Per-frame step of a menu sub-state machine, dispatched on p->state (0..6) and advanced by one
 * each call. Returns 1 only from the terminal step (state 6), 0 otherwise.
 *   0: first-time setup -- init the object list at p+0x1cc, clear the tween at p+0x1c, mark
 *      p->field0c, ref up message DBs 0x15/0x13/0x1c and the dynamic one from func_ov025_020a0f28,
 *      build the menu screen, then func_ov025_020a16e4(p);
 *   1: raise the ready flag (data_ov025_020b575c = 1) and run the open animation;
 *   2/3: intermediate transition steps;
 *   6: allocate the code node (stored at p+0x23c), apply control value 1, and return 1.
 * Several helpers here (e.g. func_ov025_02084ea4, func_ov025_020a3410) are invoked with only the
 * arguments this state actually sets; the trailing register args they also read are left as the
 * caller's residue, matching the ROM. */
typedef unsigned char u8;

typedef struct Ov008State {
    u8  pad_0000[0x18];
    int state;          /* 0x18: dispatcher step (0..6) */
} Ov008State;

extern int   data_ov025_020b575c;
extern void  func_ov025_020a1478(void);
extern void  NNS_FndInitList(void *list, int size);
extern void  func_02035f84(void *tween);
extern int   func_ov025_02084ea4(int id);
extern int   func_ov025_020a0f28(void);
extern void  func_ov025_020a1528(int screen);
extern void  func_ov025_020a16e4(Ov008State *p);
extern void  func_ov025_020a2534(Ov008State *p, int *flag, int a3, int a4);
extern void  func_ov025_020a3410(Ov008State *p);
extern void  func_ov025_020a3890(void);
extern void  func_ov025_020a2518(Ov008State *p);
extern void  func_ov025_020a13d8(Ov008State *p, int newSel, int a3);
extern void  func_ov025_020a1fa0(Ov008State *p, int a, int b, int c);
extern int   func_ov025_02084b2c(void *fn);
extern void  func_ov025_0208488c(int v);
extern void  func_ov025_020a0f4c(void);

int func_ov025_020a3f0c(Ov008State *p, int a2, int a3, int a4)
{
    int result = 0;

    switch (p->state) {
    case 0:
        func_ov025_020a1478();
        NNS_FndInitList((char *)p + 0x1cc, 0x24);
        func_02035f84((char *)p + 0x1c);
        *(int *)((char *)p + 0xc) = 1;
        func_ov025_02084ea4(0x15);
        func_ov025_02084ea4(0x13);
        func_ov025_02084ea4(0x1c);
        func_ov025_020a1528(func_ov025_02084ea4(func_ov025_020a0f28()));
        func_ov025_020a16e4(p);
        break;
    case 1:
        data_ov025_020b575c = 1;
        func_ov025_020a2534(p, &data_ov025_020b575c, 1, a4);
        func_ov025_020a3410(p);
        break;
    case 2:
        func_ov025_020a3890();
        func_ov025_020a2518(p);
        break;
    case 3:
        func_ov025_020a13d8(p, 1, 0);
        func_ov025_020a1fa0(p, 0, 0, 1);
        break;
    case 6:
        *(int *)((char *)p + 0x23c) = func_ov025_02084b2c(func_ov025_020a0f4c);
        func_ov025_0208488c(1);
        result = 1;
        break;
    }
    p->state += 1;
    return result;
}
