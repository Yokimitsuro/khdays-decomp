/* Reset the request record: invalidate both handles (+0x130/+0x134 = -1), clear the pending byte
 * (+0x138) and the result word (+0x12c); returns state 3. */
int func_0202214c(int req) {
    *(int *)(req + 0x134) = -1;
    *(int *)(req + 0x130) = *(int *)(req + 0x134);
    *(unsigned char *)(req + 0x138) = 0;
    *(int *)(req + 0x12c) = 0;
    return 3;
}
