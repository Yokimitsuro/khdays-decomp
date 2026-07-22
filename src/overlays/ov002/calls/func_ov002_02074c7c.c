/* Ask the link layer whether the request is addressed to us, then let the
 * session decide. Both booleans are materialised explicitly -- 1 and 0 on
 * separate branches -- which is what the ROM does at each step. */
extern int func_02021980(void *request);
extern int func_ov002_0206f6b4(int addressed);

int func_ov002_02074c7c(void *request) {
    int addressed;

    if (func_02021980(request) != 0) {
        addressed = 1;
    } else {
        addressed = 0;
    }

    if (func_ov002_0206f6b4(addressed) == 0) {
        return 0;
    }

    return 1;
}
