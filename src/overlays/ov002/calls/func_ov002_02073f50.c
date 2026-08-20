typedef struct {
    int pObject;                    /* +0x00 */
    char pad04[0x10];
    signed char nId;                /* +0x14 */
    char pad15[3];
} Ov002Binding;                     /* 0x18 */

typedef struct {
    char pad00[0x44];
    Ov002Binding *pBindings;        /* +0x44 */
    char pad48;
    unsigned char nCount;           /* +0x49 */
} Ov002BindingTable;

extern Ov002BindingTable *data_ov002_0207fa14;

extern int func_ov107_020c1e24(int pObject, int nArg, int nExtra);
extern void func_ov107_020c1dac(int pObject, int nArg, int nValue);

/* Look up the binding registered under the given id and drive it. */
void func_ov002_02073f50(int nId, int nArg, int nExtra, int nMode)
{
    Ov002BindingTable *pTable;
    int i;
    int nFound;

    pTable = data_ov002_0207fa14;
    nFound = -1;

    for (i = 0; i < pTable->nCount; i++) {
        if (nId == pTable->pBindings[i].nId) {
            nFound = i;
            break;
        }
    }

    if (nFound >= 0) {
        func_ov107_020c1dac(pTable->pBindings[nFound].pObject, nArg,
                            func_ov107_020c1e24(pTable->pBindings[nFound].pObject,
                                                nMode, nExtra));
    }
}
