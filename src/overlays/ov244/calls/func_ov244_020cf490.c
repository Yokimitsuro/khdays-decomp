/* Spawn a size-0x24 registry entry (func_0203c5c0, cbs cf538/cf620) into *entry linking the
 * actor (entry[1]) and the given owner (entry[0]); when the actor's +0x50 kind is 1 the owner
 * gets the "DM002" joint handle (0203bdfc) at entry[3], the cf16c handler at +0x74 and a
 * back-link to the entry at +0x84. */
extern int func_0203c5c0(int list, int a, int b, void *cb2, void *cb1, int **out);
extern int func_0203bdfc(int owner, const char *name);
extern void func_ov244_020cf620(void);
extern void func_ov244_020cf538(void);
extern void func_ov244_020cf16c(void);
extern const char data_ov244_020d38a0[];

int func_ov244_020cf490(int actor, int owner) {
    int *entry;
    int spawn = func_0203c5c0(*(int *)(actor + 0x3c), 100, 0x24,
                              &func_ov244_020cf538, &func_ov244_020cf620, &entry);
    entry[1] = actor;
    entry[0] = owner;
    if (*(int *)(entry[1] + 0x50) == 1) {
        entry[3] = func_0203bdfc(entry[0], data_ov244_020d38a0);
        *(void **)(entry[0] + 0x74) = (void *)&func_ov244_020cf16c;
        *(int **)(entry[0] + 0x84) = entry;
    }
    return spawn;
}
