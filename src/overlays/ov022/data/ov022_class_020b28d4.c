/* ov022 class descriptor data_ov022_020b28d4, 0x020b28d4-0x020b28e8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 02084048, method 020840c8, 0x234-byte state.
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

extern void func_ov022_02084048(void);
extern void func_ov022_020840c8(void);

GameClassDescriptor data_ov022_020b28d4 = {
    12,  /* nClassId */
    15,  /* nGroupId */
    func_ov022_02084048,  /* pfnCtor */
    func_ov022_020840c8,  /* pfnMethod */
    564,  /* nAuxSize */
    0,  /* pArena */
};
