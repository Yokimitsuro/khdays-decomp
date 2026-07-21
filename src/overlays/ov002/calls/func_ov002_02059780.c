extern unsigned int *data_ov002_0207f61c;
extern unsigned int func_0201ef9c(char *name, int type, int c, int d);
extern void func_020119d4(unsigned int handle, unsigned int *out);
/* Load archive file `name` as type 0xe, store the handle into the global slot, and resolve its
 * CHAR2 sub-block into slot+8. */
void func_ov002_02059780(char *name, int b, int c, int d) {
    unsigned int *dst = data_ov002_0207f61c;
    unsigned int handle = func_0201ef9c(name, 0xe, c, d);
    *dst = handle;
    func_020119d4(handle, dst + 2);
}
