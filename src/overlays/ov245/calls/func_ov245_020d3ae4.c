/* Retunes the rig at +0x14 of the sub-object's block at +0x44c and then notifies, with the
 * notify flag forced to 0 while bit 1 of the halfword at +0x1ac is set. */
extern void func_ov107_020c5c54(char *self, void *p);
extern void func_ov107_020c6980(char *self, int flag);

void func_ov245_020d3ae4(char *self, int flag) {
    char *sub = *(char **)(self + 0x3b4);
    if (*(unsigned short *)(sub + 0x1ac) & 2) {
        flag = 0;
    }
    func_ov107_020c5c54(self, *(char **)(sub + 0x44c) + 0x14);
    func_ov107_020c6980(self, flag);
}
