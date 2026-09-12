extern void func_ov105_020be4ac(unsigned int id);
extern int func_ov105_020be8b0(void);
extern void func_ov105_020bf90c(void);

/* If the request carries a target id, apply it and finish; otherwise try the fallback and only
 * finish when it declines. */
void func_ov105_020be880(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_ov105_020be4ac(*(unsigned short *)(req + 2));
        func_ov105_020bf90c();
        return;
    }
    if (func_ov105_020be8b0() != 0) {
        return;
    }
    func_ov105_020bf90c();
}
