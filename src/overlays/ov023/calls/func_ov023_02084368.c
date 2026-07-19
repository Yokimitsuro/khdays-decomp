extern int func_02021980(int ctx, void *arg);
extern int func_02020d10(int ctx, int arg);
extern void func_020219b4(int ctx, int args);

/* The script VM entity table: ctx->world->entities + id * sizeof(Entity). */

extern void func_ov023_02088954(void *entity);
extern void SNDi_ProcessEntryAlt(int id);

/* Script command: stops the entity's running sound, if it has one. */
int func_ov023_02084368(int ctx, int args) {
    int id = func_02020d10(ctx, func_02021980(ctx, (void *)args));
    char *tbl = *(char **)(*(char **)(ctx + 0x128) + 0x440);
    if (tbl != 0) {
        char *entity = tbl + id * 0x1a64;
        if (*(int *)(entity + 0x15e0) != 0) {
            func_ov023_02088954(entity);
        }
    }
    SNDi_ProcessEntryAlt((unsigned short)id);
    return 1;
}
