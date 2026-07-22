/* Reads the two status bits (8 and 4) of the value func_0200ce0c returns through its
 * out-parameter into the optional int flags.  Forwards the callee's error code. */
extern int func_0200ce0c(int a, unsigned short *out);

int func_0200d0dc(int *outA, int *outB) {
    unsigned short st;
    int rc = func_0200ce0c(0, &st);
    if (rc != 0) {
        return rc;
    }
    if (outA != 0) {
        *outA = (st & 8) != 0;
    }
    if (outB != 0) {
        *outB = (st & 4) != 0;
    }
    return rc;
}
