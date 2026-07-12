/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x2c; once it passes 0x700,
 * snapshot the pose vector (+0x54 -> +0x14) and step the height (+0x58 -= 0x80). Then, unless
 * the gate byte at *(child+0xc) is set, play the anim (ov107 mode 0x16,1), reset the timer and dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov282_020d31ec(int);
struct Vec3_020d3158 { int x, y, z; };
void func_ov282_020d316c(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x2c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x2c) = t;
    if (t >= 0x700) {
        *(struct Vec3_020d3158 *)(child + 0x14) = *(struct Vec3_020d3158 *)(child + 0x54);
        *(int *)(child + 0x58) -= 0x80;
    }
    if (*(unsigned char *)*(int *)(child + 0xc) != 0) return;
    func_ov107_020c9264(*(int *)child, 0x16, 1);
    *(int *)(child + 0x2c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov282_020d31ec);
}
