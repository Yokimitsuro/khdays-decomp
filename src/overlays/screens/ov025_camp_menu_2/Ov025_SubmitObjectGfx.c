/* If the object is active (bit0 of +0), push a 3-word fill command (the value at *(+0x28)+0x1c)
 * then the cached command block; palette-swap when bit6 of +4 is set; finally push the 12-word
 * matrix command at +0x10c and submit the object's queued gfx. */
extern void GX_SendFifoWords(int cmd, const void *words, int count);
extern void NNS_G3dGlbFlush(void);
extern void MaterialColorScale_SetRgb555(unsigned int pal);
extern void NNS_G3dDraw(void *cmdList);

void Ov025_SubmitObjectGfx(int param_1) {
    if (*(unsigned char *)param_1 & 1) {
        unsigned int buf[3];
        unsigned int value = *(unsigned int *)(*(int *)(param_1 + 0x28) + 0x1c);
        buf[0] = value;
        buf[1] = value;
        buf[2] = value;
        GX_SendFifoWords(0x1b, buf, 3);
        NNS_G3dGlbFlush();
        if (*(unsigned short *)(param_1 + 4) & 0x40) {
            MaterialColorScale_SetRgb555(*(unsigned short *)(param_1 + 0x108));
        }
        GX_SendFifoWords(0x17, (void *)(param_1 + 0x10c), 0xc);
        NNS_G3dDraw((void *)(param_1 + 0x24));
    }
}
