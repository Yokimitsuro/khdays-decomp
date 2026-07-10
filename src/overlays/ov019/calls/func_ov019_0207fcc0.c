extern int func_02021980(void);
extern int func_020235e8(int query, int kind, int value);

/* Store the current party-slot index into stat key 0x2080 (kind 5). */
int func_ov019_0207fcc0(void) {
    int slot = func_02021980();
    func_020235e8(0x82 << 6, 5, (unsigned short)slot);
    return 0;
}
