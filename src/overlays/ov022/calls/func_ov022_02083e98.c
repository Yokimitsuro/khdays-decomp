extern int func_02020a9c(void);
extern void func_ov022_020829f4(void);
extern void func_ov022_02083cfc(void);
extern void func_ov022_02082960(void);
extern void func_ov022_02083ce4(void);
extern void func_ov022_02083d14(void);
extern void func_ov022_02083d24(void);
extern void func_ov022_02083d54(void);
extern void func_ov022_02083da8(void);
extern void func_ov022_02083d78(void);
extern void func_ov022_02083dcc(void);
extern void func_ov022_02083e08(void);
extern void func_ov022_02083e54(void);

/* Fills in the scene vtable; language 0x2a swaps the first two entries for its own pair. */
void func_ov022_02083e98(void **vt) {
    void *tick;
    if (func_02020a9c() == 0x2a) {
        vt[0] = (void *)&func_ov022_020829f4;
        tick = (void *)&func_ov022_02083cfc;
    } else {
        vt[0] = (void *)&func_ov022_02082960;
        tick = (void *)&func_ov022_02083ce4;
    }
    vt[1] = tick;
    vt[2] = (void *)&func_ov022_02083d14;
    vt[3] = (void *)&func_ov022_02083d24;
    vt[4] = (void *)&func_ov022_02083d54;
    vt[5] = (void *)&func_ov022_02083da8;
    vt[6] = (void *)&func_ov022_02083d78;
    vt[7] = (void *)&func_ov022_02083dcc;
    vt[8] = (void *)&func_ov022_02083e08;
    vt[9] = 0;
    vt[10] = (void *)&func_ov022_02083e54;
}
