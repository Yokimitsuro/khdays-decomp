/* NONMATCHING: the original was compiled with a dead flag term the source still
 * had — `(field@+0x468 & FLAG) == 0` where FLAG is a build-time constant equal
 * to 0 (a disabled feature). mwcc emits `ldr; and #0; cmp #0` for it, but any
 * literal `& 0` we write gets constant-folded away (even through volatile), so
 * the load can't be reproduced without the original header's 0-valued macro.
 * The clean equivalent below omits the always-true term. */
int func_ov022_020ad1d0(int arg0) {
    int r = -1;
    if (*(unsigned char *)(arg0 + 0x4f0) == 2 &&
        (*(unsigned int *)(arg0 + 0x464) & 0x10) == 0) {
        r = *(unsigned char *)(*(int *)(arg0 + 0x4f8) + 0x17);
    }
    return r;
}
