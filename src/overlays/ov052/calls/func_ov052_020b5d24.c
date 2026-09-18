/* Scene setup of the ov032 mission (and its byte-identical twins): opens layers 0 and 1 of
 * the mission root (fb60/fb98) and marks their +0xda8/+0xf0c bytes when the neighbouring flag
 * is set, builds the layout (43dc), instantiates the ov022 class 0x020b2930 from the overlay's
 * parameter set (its first word packed from the actor's +0x2bd0 heading, the class bit and the +0x918
 * slot plus 0x28, its last word offset by the actor's +9 id) into the root's +0x2c2c, and binds
 * the two +0x2c34 animation blocks to the packed heading (with the +0x92b slot plus 0x78) on
 * channels 0/2 from their own +0xe0 tables. */
extern void func_ov022_0209fb60(int root, int layer, int a);
extern void func_ov022_0209fb98(int root, int layer, int a);
extern void func_ov052_020b6bdc(int root);
extern int func_02023930(void *desc, void *arg);                               /* InstantiateClass */
extern void func_0202a634(void *p, int packed, int a, int id);
extern void func_0202accc(void *p, int channel, void *table, int b);
extern char data_ov022_020b2930[];
extern int data_ov052_020b80c0;

typedef struct { int w[5]; } Params;
extern Params data_ov052_020b7f10;

void func_ov052_020b5d24(char *self)
{
    int root = *(int *)&data_ov052_020b80c0;
    char *slot = self + 0x918;
    Params p;
    int i;
    int packed;
    int sub;
    char *anim;

    func_ov022_0209fb60(root, 0, 1);
    func_ov022_0209fb98(root, 0, 1);
    if (*(signed char *)(root + 0xda9) != 0) {
        *(unsigned char *)(root + 0xda8) |= 1;
    }
    func_ov022_0209fb60(root, 1, 2);
    func_ov022_0209fb98(root, 1, 1);
    if (*(signed char *)(root + 0xf0d) != 0) {
        *(unsigned char *)(root + 0xf0c) |= 1;
    }
    sub = *(unsigned char *)(slot + 0x13);
    func_ov052_020b6bdc(root);
    p = data_ov052_020b7f10;
    p.w[0] = (((*(int *)(self + 0x2bd0) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | ((*(unsigned char *)slot + 0x28) & 0x1ff);
    p.w[4] += *(unsigned char *)(self + 9);
    *(int *)(root + 0x2c2c) = func_02023930(data_ov022_020b2930, &p);
    i = 0;
    anim = (char *)(root + 0x2c34);
    sub = (sub + 0x78) & 0x1ff;
    for (; i < 2; i++) {
        func_0202a634(anim, (((*(int *)(self + 0x2bd0) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | sub, 1, *(unsigned char *)(self + 9) + 7);
        func_0202accc(anim, 0, anim + 0xe0, 0);
        func_0202accc(anim, 2, anim + 0xe0, 0);
        anim += 0x108;
    }
}
