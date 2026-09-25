/* ov009 class descriptor data_ov009_02056220, 0x02056220-0x02056234 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 0204cac0, method 0204caec, 0x4-byte state.
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

extern void func_ov009_0204cac0(void);
extern void func_ov009_0204caec(void);

GameClassDescriptor data_ov009_02056220 = {
    8,  /* nClassId */
    14,  /* nGroupId */
    func_ov009_0204cac0,  /* pfnCtor */
    func_ov009_0204caec,  /* pfnMethod */
    4,  /* nAuxSize */
    0,  /* pArena */
};
