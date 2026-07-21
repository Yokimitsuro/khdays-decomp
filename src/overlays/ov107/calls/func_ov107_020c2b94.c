/* Links a child into the owner's sorted child list (+0x44) and fires the child's attach callback. */

extern int *func_01fffca8(int list, int stride, int max);

void func_ov107_020c2b94(int owner, int child) {
    *(int *)(child + 4) = owner;
    *func_01fffca8(owner + 0x44, 4, 100) = child;
    if (*(void (**)(int, int))(child + 0x28) != 0) {
        (*(void (**)(int, int))(child + 0x28))(child, owner);
    }
}
