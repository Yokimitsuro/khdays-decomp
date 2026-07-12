/* Register the ov211 object factory (type 0x2b) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov211_020d1998(int);
int func_ov211_020d1980(void) {
    return func_ov107_020c2f7c(0x2b, (void *)&func_ov211_020d1998);
}
