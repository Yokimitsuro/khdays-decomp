extern int func_ov002_0206eb40(void);
extern int func_ov002_02069554(void);
extern unsigned int func_ov002_0205f3a4(unsigned int handle);
/* Resolve the currently-selected panel's resource, or 0 if none is active. */
unsigned int func_ov002_0206d448(void) {
    unsigned int handle;
    if (func_ov002_0206eb40() != -1 && (handle = func_ov002_02069554()) != 0) {
        return func_ov002_0205f3a4(handle);
    }
    return 0;
}
