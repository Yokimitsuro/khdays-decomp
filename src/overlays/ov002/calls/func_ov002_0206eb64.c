/* Request link slot 2 for the given id and, when the link layer hands back
 * anything other than the unassigned marker 0xffff, mark the session dirty
 * (flag 8 in the halfword at +0, bit 0 of the byte at +0xa). Reports 1 unless
 * the request came back unassigned. A session that is not ready reports 1
 * without asking. */
extern int func_02030694(void);
extern int func_ov002_0206fb84(int slot, void *request);

extern char *data_ov002_0207fa04;

int func_ov002_0206eb64(int id) {
    char *ctx = data_ov002_0207fa04;
    int request[2];

    if (func_02030694() != 0) {
        request[1] = id;

        if (func_ov002_0206fb84(2, request) == 0xffff) {
            return 0;
        }

        *(unsigned short *)ctx |= 8;
        *(unsigned char *)(ctx + 0xa) |= 1;
    }

    return 1;
}
