/* Relocation fixup: make obj[4]'s pointer array absolute — add the object base
 * to obj[4] itself, then to each of obj[0] (u16 count) entries. */
void func_02011ae8(int *obj) {
    unsigned int i = 0;
    obj[1] = obj[1] + (int)obj;
    while (*(unsigned short *)obj > i) {
        int *arr = (int *)obj[1];
        arr[i] = (int)((char *)obj + arr[i]);
        i = (unsigned short)(i + 1);
    }
}
