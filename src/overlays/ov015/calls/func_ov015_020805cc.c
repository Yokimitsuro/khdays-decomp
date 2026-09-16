/* func_ov015_020805cc -- Ov015_CreateTriggerClass: build the class table (0x58 bytes)
 * that owns the 0x5c-byte trigger pieces, install its four handlers in the slots every
 * piece class uses (arm 02080408, update 020804a4, 0208041c, hit test 02080424) and tag
 * it as class kind 0xd. */
typedef unsigned short u16;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern void func_ov015_02080408(void);
extern void func_ov015_020804a4(void);
extern void func_ov015_0208041c(void);
extern void func_ov015_02080424(void);

void *func_ov015_020805cc(void *pCtx)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x58, 0x5c, pCtx);
    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = (int)func_ov015_02080408;
    *(int *)(pTable + 0x0c) = 0;
    *(int *)(pTable + 0x10) = 0;
    *(int *)(pTable + 0x14) = 0;
    *(int *)(pTable + 0x18) = 0;
    *(int *)(pTable + 0x1c) = (int)func_ov015_020804a4;
    *(int *)(pTable + 0x20) = 0;
    *(int *)(pTable + 0x24) = 0;
    *(int *)(pTable + 0x28) = 0;
    *(int *)(pTable + 0x2c) = (int)func_ov015_0208041c;
    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = (int)func_ov015_02080424;
    *(int *)(pTable + 0x3c) = 0;
    *(u16 *)(pTable + 0x4c) = 0xd;
    return pTable;
}
