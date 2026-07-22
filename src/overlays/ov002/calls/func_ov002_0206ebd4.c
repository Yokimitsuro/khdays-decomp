/* Request link slot 3 for this machine's own player index and, when the link
 * layer hands back anything other than the unassigned marker 0xffff, mark the
 * session dirty (flag 8 in the halfword at +0). Reports 1 unless the request
 * came back unassigned. Sibling of func_ov002_0206eb64 over slot 2. */
extern int func_02030788(void);
extern int func_ov002_0206fb84(int slot, void *request);

extern char *data_ov002_0207fa04;

int func_ov002_0206ebd4(void) {
    char *ctx = data_ov002_0207fa04;
    unsigned char request[4];

    request[1] = (unsigned char)func_02030788();

    if (func_ov002_0206fb84(3, request) == 0xffff) {
        return 0;
    }

    *(unsigned short *)ctx |= 8;
    return 1;
}
