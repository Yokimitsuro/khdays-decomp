/* Post a 4-byte sprite request (template halfword-pair with the live tile id), kick anim 5,
 * then dispatch 020d09ac. */
extern int func_02031384(int, void *, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int data_ov277_020d36bc;
extern int func_ov277_020d09ac(int);
struct hpair { unsigned short a, b; };
void func_ov277_020d0944(int param_1) {
    int owner = *(int *)(param_1 + 4);
    struct hpair buf = *(struct hpair *)&data_ov277_020d36bc;
    buf.a = *(unsigned short *)(*(int *)owner + 2);
    func_02031384(4, &buf, 4);
    func_ov107_020c9264(*(int *)owner, 5, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov277_020d09ac);
}
