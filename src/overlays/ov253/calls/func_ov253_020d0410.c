/* Build the sprite request (mirroring the object's facing) and dispatch. */
extern void func_02031384(int a, void *req, int b);
extern int func_0203c634(int, int, void *);
extern int data_ov253_020d4964;
extern int func_ov253_020d0470(int);
struct hpair { unsigned short a, b; };
void func_ov253_020d0410(int param_1) {
    int owner = *(int *)(param_1 + 4);
    struct hpair buf = *(struct hpair *)((char *)&data_ov253_020d4964 + 0xc);
    buf.a = *(unsigned short *)(*(int *)owner + 2);
    func_02031384(4, &buf, 4);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d0470);
}
