/* NONMATCHING: dead-&0 flag term (same class as func_ov022_020ad1d0). The
 * original ANDs field@+4 with a 0-valued build constant `(field4 & FLAG)==0`;
 * mwcc folds any literal & 0 away (24B short). Clean equivalent omits it.
 * Semantics: if flag 0x200 clear and bits 2&0 of byte@+0x694 both set, call
 * func_ov022_0209c9fc; then clear bit2 of that byte. */
extern void func_ov022_0209c9fc(int arg0);
void func_ov022_020a06bc(unsigned int *arg0) {
    if ((*arg0 & 0x200) == 0) {
        unsigned char *b = (unsigned char *)((char *)arg0 + 0x694);
        if ((int)((unsigned int)*b << 0x1d) < 0 && (int)((unsigned int)*b << 0x1f) < 0)
            func_ov022_0209c9fc((int)arg0);
        *b &= 0xfb;
    }
}
