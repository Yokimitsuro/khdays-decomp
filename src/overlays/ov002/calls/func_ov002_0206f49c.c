/* Report whether input is currently blocked: yes while the session is not ready,
 * and yes while either of bits 1 and 7 of the context's flag word is set.
 * Otherwise func_ov002_0206f1fc decides. The flag word is read ONCE and both
 * bits tested against the same register. */
extern int func_02030694(void);
extern int func_ov002_0206f1fc(void);

extern int *data_ov002_0207fa08;

int func_ov002_0206f49c(void) {
    int *ctx = data_ov002_0207fa08;
    int flags;

    if (func_02030694() == 0) {
        return 1;
    }

    flags = *ctx;
    if (flags & 2) {
        return 1;
    }
    if (flags & 0x80) {
        return 1;
    }
    return func_ov002_0206f1fc();
}
