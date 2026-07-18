/* Same shape as ov202/ov203 020cd4a0: the 0x44 gate byte is read UNSIGNED (ldrb)
 * while the 0x20 selector stays SIGNED (ldrsb). The two byte reads in this function
 * have opposite signedness. */
extern void func_ov107_020c9264(int obj, int tag1, int tag_lsb);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov202_020cd2fc(void);
void func_ov202_020cd2b8(char *obj) {
    char *p = *(char **)(obj + 0x4);
    if (**(unsigned char **)(p + 0x44) != 0) return;
    func_ov107_020c9264(*(int *)(p + 0x0), 2, 1);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov202_020cd2fc);
}
