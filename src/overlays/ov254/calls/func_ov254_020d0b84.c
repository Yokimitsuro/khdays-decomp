/* Unless busy, tick +0x40; on reaching 5 kick anim 0x15, retire the +0x468 node and advance to
 * 020d0bf4, otherwise just kick anim 0x14. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov254_020d4180(int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d0bf4(int);
void func_ov254_020d0b84(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(int *)(owner + 0x40) += 1;
    if (*(int *)(owner + 0x40) >= 5) {
        func_ov107_020c9264(*(int *)owner, 0x15, 0);
        func_ov254_020d4180(*(int *)(*(int *)owner + 0x468));
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d0bf4);
    } else {
        func_ov107_020c9264(*(int *)owner, 0x14, 0);
    }
}
