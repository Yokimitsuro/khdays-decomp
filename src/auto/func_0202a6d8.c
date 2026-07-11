/* Detach tree node `obj`: unlink it from its parent's (+0xbc) child list
 * (first child at +0xc0, next-sibling link at +0xc4), then orphan every one
 * of obj's own children by clearing their parent pointer. */
void func_0202a6d8(int obj) {
    int cur, prev;
    if (*(int *)(obj + 0xbc) != 0) {
        prev = 0;
        cur = *(int *)(*(int *)(obj + 0xbc) + 0xc0);
        while (cur != 0) {
            if (cur == obj) {
                if (prev != 0) {
                    *(int *)(prev + 0xc4) = *(int *)(cur + 0xc4);
                } else {
                    *(int *)(*(int *)(obj + 0xbc) + 0xc0) = *(int *)(cur + 0xc4);
                }
            }
            prev = cur;
            cur = *(int *)(cur + 0xc4);
        }
        *(int *)(obj + 0xbc) = 0;
    }
    {
        int c = *(int *)(obj + 0xc0);
        if (c != 0) {
            while (c != 0) {
                *(int *)(c + 0xbc) = 0;
                c = *(int *)(c + 0xc4);
            }
            *(int *)(obj + 0xc0) = 0;
        }
    }
}
