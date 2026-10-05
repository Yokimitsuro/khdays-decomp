/* Effect tick of the ov032 enemy (and its byte-identical twins): drives and places the +0x2e78
 * effect block, then, while bit 0 of the +0x694 flags is set in modes 0x1b/0x1c, winds the two
 * +0x2c34 animation blocks to the model's track-0 frame minus 2.0 (only inside the track's
 * length), refreshes the matrix stack from the +0x528 matrices and submits the +0x2c54 objects. */
extern void Ov072_EffectBlockTick(int self, char *block, int rate);
extern void Ov072_EffectBlockPlace(int self, char *block);
extern int Anim_GetFrame(void *anim, int track);                                 /* Anim_GetFrame */
extern int Anim_GetLengthQ12(void *anim, int track);
extern void Anim_SetFrameWrapped(void *anim, int channel, int frame);
extern void NNS_G3dGlbFlush(void);
extern void GX_SendFifoWords(unsigned int cmd, const void *src, unsigned int words);
extern void NNS_G3dDraw(void *obj);

struct b1 { unsigned char b0 : 1; };

void Ov072_EffectTick(int self)
{
    int i;
    int frame;
    int len;
    char *anim;
    char *mtx;
    char *obj;

    Ov072_EffectBlockTick(self, (char *)(self + 0x2e78), *(short *)(self + 0x2aba));
    Ov072_EffectBlockPlace(self, (char *)(self + 0x2e78));
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
        frame = Anim_GetFrame((void *)(*(int *)(self + 0x20) + 4), 0) - 0x2000;
        len = Anim_GetLengthQ12((void *)(*(int *)(self + 0x20) + 4), 0);
        if (frame > 0 && frame < len) {
            Anim_SetFrameWrapped(anim, 2, frame);
            Anim_SetFrameWrapped(anim, 0, frame);
            NNS_G3dGlbFlush();
            GX_SendFifoWords(0x17, mtx, 0xc);
            NNS_G3dDraw(obj);
        }
        anim += 0x108;
        mtx += 0x30;
        obj += 0x108;
    }
}
