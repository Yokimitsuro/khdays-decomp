typedef struct { int x, y, z; } Vec3;

/* Stores the caller's vector into the slot and records the mode; mode 0 also clears the owner's
 * pending-target field. */
int func_ov218_020ce3fc(char *self, int mode, char *src) {
    char *slot = *(char **)(self + 0x214);
    if (mode == 0) {
        *(int *)(*(int *)slot + 0x394) = 0;
    }
    *(Vec3 *)(slot + 0x1c) = *(Vec3 *)(src + 4);
    *(int *)(slot + 0xc) = mode;
    return 1;
}
