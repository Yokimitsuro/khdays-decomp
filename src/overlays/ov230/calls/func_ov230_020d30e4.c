/* Init the multi-part reaction: reset the sub-state bytes (+0x1c6=0, +0x1c7=-1), point
 * (child)+0xc at (*child)+0xb0, raise flag 6 in the high byte at (*child)+0x60, then
 * register the three phase handlers on slots 1, 0 and 2. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov230_020d34f4(int);
extern void func_ov230_020d3174(int);
extern void func_ov230_020d3360(int);
void func_ov230_020d30e4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(signed char *)(*(int *)child + 0x1c6) = 0;
    *(signed char *)(*(int *)child + 0x1c7) = -1;
    *(int *)(child + 0xc) = *(int *)child + 0xb0;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 6;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    func_0203c634(param_1, 1, (void *)&func_ov230_020d34f4);
    func_0203c634(param_1, 0, (void *)&func_ov230_020d3174);
    func_0203c634(param_1, 2, (void *)&func_ov230_020d3360);
}
