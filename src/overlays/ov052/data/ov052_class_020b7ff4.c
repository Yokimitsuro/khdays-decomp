/* ov052 class descriptor data_ov052_020b7ff4, 0x020b7ff4-0x020b8008 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020b5a34, method 020b5a8c, 0x3020-byte state.
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

extern void func_ov052_020b5a34(void);
extern void func_ov052_020b5a8c(void);

GameClassDescriptor data_ov052_020b7ff4 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov052_020b5a34,  /* pfnCtor */
    func_ov052_020b5a8c,  /* pfnMethod */
    12320,  /* nAuxSize */
    0,  /* pArena */
};
