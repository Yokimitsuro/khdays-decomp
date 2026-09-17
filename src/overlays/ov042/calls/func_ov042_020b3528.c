/* Per-frame update of the ov042 enemy's two sub-objects (x4: ov042/061/081/098), the ov031
 * shape: (the node animation's frame is polled but unused,) each sub-object is fed the frame
 * delta and stepped; if either is idle, the local player raises bit 0x10000 of both attack-flag
 * words. The ready states 0x2f / 0x30 ring cue 0xc7 (variants 2 / 3) exactly at progress 0xf000
 * / 0x1b000, then the common actor step runs. */
extern int func_0202aee0(unsigned short *p, unsigned int idx);                  /* Anim_GetFrame */
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void func_ov022_020a4490(char *self, int nSound, int nVariant);
extern void func_ov022_020ad588(char *self);

void func_ov042_020b3528(char *self)
{
    int v;

    func_0202aee0((unsigned short *)(*(char **)(self + 0x20) + 4), 0);
    v = func_ov022_02083f90();
    func_ov022_0209145c(*(int *)(self + 0x2000 + 0x644), v);
    v = func_ov022_02083f90();
    func_ov022_0209145c(*(int *)(self + 0x2000 + 0x644) + 0x30, v);
    func_ov022_02091474(*(int *)(self + 0x2000 + 0x644));
    func_ov022_02091474(*(int *)(self + 0x2000 + 0x644) + 0x30);
    if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644)) == 0 ||
        func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644) + 0x30) == 0) {
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x46c) |= 0x10000;
        }
    }
    switch (*(int *)(self + 0x6bc)) {
    case 0x2f:
        if (*(int *)(self + 0x7b0) == 0xf000) {
            func_ov022_020a4490(self, 0xc7, 2);
        }
        break;
    case 0x30:
        if (*(int *)(self + 0x7b0) == 0x1b000) {
            func_ov022_020a4490(self, 0xc7, 3);
        }
        break;
    }
    func_ov022_020ad588(self);
}
