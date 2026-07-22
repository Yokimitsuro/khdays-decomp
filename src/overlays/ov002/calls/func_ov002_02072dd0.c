/* Tick one cooldown down by a frame, stopping at the 0xff "never" marker, and if
 * the resulting state is 0xc hand off to the ov021 finisher. The record is the
 * slot's object at +8, its counters starting four bytes in and striding 4. */
extern int func_ov002_0207690c(void);
extern void func_ov021_02080c40(int a);

extern char *data_ov002_0207fa14;

void func_ov002_02072dd0(int slot, int index) {
    unsigned char *counter =
        (unsigned char *)(*(int *)(*(int *)(data_ov002_0207fa14 + 4) + slot * 4 + 8) + 4 + index * 4);

    if (counter[1] != 0xff) {
        counter[1]--;
    }

    if (func_ov002_0207690c() == 0xc) {
        func_ov021_02080c40(0);
    }
}
