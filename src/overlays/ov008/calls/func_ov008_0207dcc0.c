/* func_ov008_0207dcc0 -- Ov008_PollMenuBusyState (108 B, 6 relocs).
 * Returns a small status code describing whether the menu is mid-transition. Returns 0 when the
 * menu-state object data_ov008_02090fa0 is not allocated. Returns 1 when its field2c is set and
 * func_ov008_0207be38() reports active. Returns 2 when the current scene id (func_ov008_020816c0)
 * is 9 and func_ov008_0207bb78() reports active. Otherwise returns whether the scene id is 7.
 * The `data_ov008_02090fa0 != 0` re-test in the second condition is deliberate: it matches the
 * ROM, which reuses the null-check flags to predicate the field2c load (ldrne/cmpne). */
typedef unsigned char u8;

typedef struct Ov008MenuState {
    u8  pad_0000[0x2c];
    int field2c;   /* 0x2c */
} Ov008MenuState;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern Ov008MenuState *data_ov008_02090fa0;
extern int func_ov008_0207be38(void);
extern int func_ov008_020816c0(void);
extern int func_ov008_0207bb78(void);

int func_ov008_0207dcc0(void)
{
    NNSi_FndGetCurrentRootHeap();
    if (data_ov008_02090fa0 == 0) {
        return 0;
    }
    if (data_ov008_02090fa0 != 0 && data_ov008_02090fa0->field2c != 0 &&
        func_ov008_0207be38() != 0) {
        return 1;
    }
    if (func_ov008_020816c0() == 9 && func_ov008_0207bb78() != 0) {
        return 2;
    }
    return func_ov008_020816c0() == 7;
}
