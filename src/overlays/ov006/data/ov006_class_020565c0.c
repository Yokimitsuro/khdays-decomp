/* ov006 class descriptor data_ov006_020565c0, 0x020565c0-0x020565e0 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the u16 class / group
 * ids, the constructor whose return is the first state function, the method slot, the size of
 * the zero-filled auxiliary block and the arena reference.  Constructor 020560cc, method
 * 02056118, 8-byte state.  The dsd symbol also covers the three zero words that pad the unit's
 * .data to its 32-byte end.
 */

typedef void (*GameClassFn)(void);

typedef struct GameClassDescriptor {
    unsigned short nClassId;  /* 0x00 */
    unsigned short nGroupId;  /* 0x02 */
    GameClassFn pfnCtor;      /* 0x04: returns the object's first state fn */
    GameClassFn pfnMethod;    /* 0x08 */
    int nAuxSize;             /* 0x0c: zero-filled state block */
    int *pArena;              /* 0x10 */
} GameClassDescriptor;

extern void func_ov006_020560cc(void);
extern void func_ov006_02056118(void);

struct {
    GameClassDescriptor desc;
    int reserved[3];
} data_ov006_020565c0 = {
    { 8, 14, func_ov006_020560cc, func_ov006_02056118, 8, 0 },
    { 0, 0, 0 },
};
