/* Message handler of the ov123 enemy (and its byte-identical twins): a kind-5 / sub-0 message attaches the
 * two +0x398 sub-items (slots 0 and 2, handles into slots 1 and 3) to the actor's +0x3c model
 * with mode 0x17 at the +0x39c anchor; everything then falls through to the ov107 base handler. */
extern int func_ov107_020c09a0(int resource, int item, int mode, int anchor, int e, int f);
extern void func_ov107_020c7500(int self, int msg, int size);

void func_ov123_020cc2a0(int self, int msg, int size)
{
    if (*(unsigned char *)(msg + 2) == 5) {
        switch (*(unsigned char *)(msg + 3)) {
        case 0:
            *(int *)(*(int *)(self + 0x398) + 4) =
                func_ov107_020c09a0(*(int *)(self + 0x3c), **(int **)(self + 0x398), 0x17,
                                    self + 0x39c, 0, 0);
            *(int *)(*(int *)(self + 0x398) + 0xc) =
                func_ov107_020c09a0(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x398) + 8),
                                    0x17, self + 0x39c, 0, 0);
            break;
        }
    }
    func_ov107_020c7500(self, msg, size);
}
