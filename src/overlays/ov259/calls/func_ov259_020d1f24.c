/* Point +8 at obj+0xb0, set sub-state +0x1c6=1 and +0x1c7=-1, clear bit0 of the hw60 hi byte and
 * +0x1ae, then hand off across the 020d1fd0 / 020d21ac / 020d20c0 trio. */
extern int func_0203c634(int, int, void *);
extern int func_ov259_020d1fd0(int);
extern int func_ov259_020d21ac(int);
extern int func_ov259_020d20c0(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov259_020d1f24(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 8) = *(int *)owner + 0xb0;
    *(unsigned char *)(*(int *)owner + 0x1c6) = 1;
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~1;
    *(unsigned short *)(*(int *)owner + 0x1ae) &= ~1;
    func_0203c634(param_1, 0, (void *)&func_ov259_020d1fd0);
    func_0203c634(param_1, 1, (void *)&func_ov259_020d21ac);
    func_0203c634(param_1, 2, (void *)&func_ov259_020d20c0);
}
