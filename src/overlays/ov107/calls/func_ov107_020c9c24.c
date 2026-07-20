/* Look a resource up by name in the cache list at +0x4c, and open it on a miss.
 * On a hit the cached handle is returned. On a miss a new entry is inserted, the
 * name is duplicated into a fresh allocation, and func_02024ee8 opens the
 * resource with mode 0xb. Returns 0 when the cache itself does not exist. */
extern int data_ov107_020cbf1c;

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern int *func_01fffca8(void *list, int a, int b);
extern int func_0201fabc(char *a, char *b);
extern unsigned int strlen(const char *s);
extern void *func_0203d15c(unsigned int size);
extern void func_0201f924(void *dst, const char *src);
extern int func_02024ee8(char *name, int mode);

int func_ov107_020c9c24(char *name) {
    char *cache = *(char **)&data_ov107_020cbf1c;
    int *entry;

    if (cache != 0) {
        entry = func_01fffd70(cache + 0x4c);
        while (entry != 0) {
            if (func_0201fabc((char *)entry[1], name) == 0) {
                return entry[0];
            }
            entry = func_01fffd8c(cache + 0x4c);
        }

        entry = func_01fffca8(cache + 0x4c, 8, 100);
        entry[1] = (int)func_0203d15c(strlen(name) + 1);
        func_0201f924((void *)entry[1], name);
        entry[0] = func_02024ee8(name, 0xb);
        return entry[0];
    }

    return 0;
}
