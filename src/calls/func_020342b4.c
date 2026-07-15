/* MsgDb_IsLoaded: true if the message-db table is allocated and db `param_1`'s
 * entry[0] (its loaded .p2 buffer) is non-null. Table = data_0204c238, 0x14/entry. */
extern int data_0204c238;
int func_020342b4(int param_1) {
    int r = 0;
    if (data_0204c238 != 0 && *(int *)(data_0204c238 + param_1 * 0x14) != 0) {
        r = 1;
    }
    return r;
}
