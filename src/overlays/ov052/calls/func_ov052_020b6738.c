/* Effect tick of the ov032 enemy (and its byte-identical twins): drives and places the +0x2e78
 * effect block, then, while bit 0 of the +0x694 flags is set in modes 0x1b/0x1c, winds the two
 * +0x2c34 animation blocks to the model's track-0 frame minus 2.0 (only inside the track's
 * length), refreshes the matrix stack from the +0x528 matrices and submits the +0x2c54 objects. */
extern void func_ov052_020b73e4(int self, char *block, int rate);
extern void func_ov052_020b74b0(int self, char *block);
extern int func_0202aee0(void *anim, int track);                                 /* Anim_GetFrame */
extern int func_0202aef8(void *anim, int track);
extern void func_01fff774(void *anim, int channel, int frame);
extern void func_0201571c(void);
extern void func_01ff9f00(unsigned int cmd, const void *src, unsigned int words);
extern void func_020279e0(void *obj);

struct b1 { unsigned char b0 : 1; };

void func_ov052_020b6738(int self)
{
    int i;
    int frame;
    int len;
    char *anim;
    char *mtx;
    char *obj;

    func_ov052_020b73e4(self, (char *)(self + 0x2e78), *(short *)(self + 0x2aba));
    func_ov052_020b74b0(self, (char *)(self + 0x2e78));
    if (((struct b1 *)(self + 0x694))->b0 == 0) {
        return;
    }
    if ((unsigned int)(*(int *)(self + 0x6bc) - 0x1b) > 1) {
        return;
    }
    anim = (char *)(self + 0x2c34);
    mtx = (char *)(self + 0x528);
    obj = (char *)(self + 0x2c54);
    for (i = 0; i < 2; i++) {
        frame = func_0202aee0((void *)(*(int *)(self + 0x20) + 4), 0) - 0x2000;
        len = func_0202aef8((void *)(*(int *)(self + 0x20) + 4), 0);
        if (frame > 0 && frame < len) {
            func_01fff774(anim, 2, frame);
            func_01fff774(anim, 0, frame);
            func_0201571c();
            func_01ff9f00(0x17, mtx, 0xc);
            func_020279e0(obj);
        }
        anim += 0x108;
        mtx += 0x30;
        obj += 0x108;
    }
}
