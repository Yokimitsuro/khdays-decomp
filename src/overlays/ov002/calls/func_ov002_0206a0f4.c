extern void func_02020cf8(int arg);
extern char *data_ov002_0207fa00;
/* Drop the link session: cancel it, clear the state byte and the id halfword, and mark the slot
 * free (-1). */
void func_ov002_0206a0f4(void) {
    char *e = (char *)((int)data_ov002_0207fa00 + 0x8d0c);
    func_02020cf8(-1);
    e[0] = 0;
    *(unsigned short *)(e + 2) = 0;
    e[1] = -1;
}
