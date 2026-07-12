/* Seed the state (+0x88=0x900, clear +0x58/+0x68/+0x74/+0xac, +0x94 by the +0x4c mode). If +0xad
 * holds a queued sub-state apply it and reset, otherwise kick the +0x4c-selected anims and dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov259_020cd524(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov259_020ce400(int);
void func_ov259_020ce34c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x88) = 0x900;
    *(int *)(owner + 0x58) = 0;
    *(int *)(owner + 0x68) = 0;
    *(int *)(owner + 0x74) = 0;
    *(unsigned char *)(owner + 0xac) = 0;
    *(int *)(owner + 0x94) = *(int *)(owner + 0x4c) == 0 ? 0xb4 : 0x32;
    signed char ad = *(signed char *)(owner + 0xad);
    if (ad != -1) {
        *(unsigned char *)(*(int *)owner + 0x1c7) = ad;
        *(signed char *)(owner + 0xad) = -1;
        return;
    }
    func_ov107_020c9264(*(int *)owner, *(int *)(owner + 0x4c) == 0 ? 0 : 2, 1);
    func_ov259_020cd524(param_1, (signed char)(*(int *)(owner + 0x4c) == 0 ? 0 : 2), 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020ce400);
}
