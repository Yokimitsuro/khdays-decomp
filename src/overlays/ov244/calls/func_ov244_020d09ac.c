/* Build the sprite request (mirroring facing), kick anim 5, then dispatch. */
extern void func_02031384(int a, void *req, int b);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int data_ov244_020d3724;
extern int func_ov244_020d0a14(int);
struct hpair { unsigned short a, b; };
void func_ov244_020d09ac(int param_1) {
    int owner = *(int *)(param_1 + 4);
    struct hpair buf = *(struct hpair *)&data_ov244_020d3724;
    buf.a = *(unsigned short *)(*(int *)owner + 2);
    func_02031384(4, &buf, 4);
    func_ov107_020c9264(*(int *)owner, 5, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov244_020d0a14);
}
