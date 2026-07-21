/* If the object is active (bit0 of +0), push a 3-word fill command (the value at *(+0x28)+0x1c)
 * then the cached command block; palette-swap when bit6 of +4 is set; finally push the 12-word
 * matrix command at +0x10c and submit the object's queued gfx. */
extern void func_01ff9f00(int cmd, const void *words, int count);
extern void func_0201571c(void);
extern void func_01ffcec0(unsigned int pal);
extern void func_020279e0(void *cmdList);

void func_ov008_02059e0c(int param_1) {
    if (*(unsigned char *)param_1 & 1) {
        unsigned int buf[3];
        unsigned int value = *(unsigned int *)(*(int *)(param_1 + 0x28) + 0x1c);
        buf[0] = value;
        buf[1] = value;
        buf[2] = value;
        func_01ff9f00(0x1b, buf, 3);
        func_0201571c();
        if (*(unsigned short *)(param_1 + 4) & 0x40) {
            func_01ffcec0(*(unsigned short *)(param_1 + 0x108));
        }
        func_01ff9f00(0x17, (void *)(param_1 + 0x10c), 0xc);
        func_020279e0((void *)(param_1 + 0x24));
    }
}
