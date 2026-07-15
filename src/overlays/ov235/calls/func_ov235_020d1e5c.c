/* func_ov235_020d1e5c -- mark both child nodes dirty, ov235. Follows obj->owner (+4)
 * to its two children (+4, +8) and sets the dirty bit (2) in each child's flags (+0x5c). */
void func_ov235_020d1e5c(char *obj) {
    char *owner = *(char **)(obj + 4);
    *(int *)(*(char **)(owner + 4) + 0x5c) |= 2;
    *(int *)(*(char **)(owner + 8) + 0x5c) |= 2;
}
