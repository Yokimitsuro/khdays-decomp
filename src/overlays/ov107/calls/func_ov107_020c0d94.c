extern void func_02031258(int a, unsigned short *b, unsigned short c);
/* Copy the u16 id at obj+2 into *out, then tail-call func_02031258(1, out, (u16)arg). */
void func_ov107_020c0d94(int obj, unsigned short *out, int arg) {
    *out = *(unsigned short *)(obj + 2);
    func_02031258(1, out, (unsigned short)arg);
}
