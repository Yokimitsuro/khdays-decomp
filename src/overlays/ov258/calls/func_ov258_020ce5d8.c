/* Reset the launch block: notify 020cd028, clear +0x30/+0x34/+0x44/+0x3c, set +0x50=6, force the
 * +0x53 low nibble to 3, kick anim 3 and dispatch. */
extern int func_ov258_020cd028(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov258_020ce63c(int);
struct nib { unsigned char lo : 4, hi : 4; };
void func_ov258_020ce5d8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov258_020cd028(param_1, 1);
    *(int *)(owner + 0x30) = 0;
    *(int *)(owner + 0x34) = 0;
    *(int *)(owner + 0x44) = 0;
    *(unsigned short *)(owner + 0x50) = 6;
    ((struct nib *)(owner + 0x53))->lo = 3;
    *(int *)(owner + 0x3c) = 0;
    func_ov107_020c9264(*(int *)owner, 3, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov258_020ce63c);
}
