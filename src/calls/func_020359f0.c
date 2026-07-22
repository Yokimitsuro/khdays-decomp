/* Clears the first entry of record `a` whose {id, value} pair equals *key.  The id half is
 * compared unsigned (ldrh) and the value half signed (ldrsh). */
extern int func_0203595c(int a);
extern unsigned char data_0204c678[];

void func_020359f0(int a, short *key) {
    int n = func_0203595c(a);
    int i = 0;
    short *e;
    if (n > 0) {
        e = (short *)(data_0204c678 + a * 260 + 0xba);
        do {
            if (*(unsigned short *)e == *(unsigned short *)key && e[1] == key[1]) {
                *e = 0;
                return;
            }
            i = i + 1;
            e = e + 2;
        } while (i < n);
    }
}
