/* ov054 class descriptor data_ov054_020b73f4, 0x020b73f4-0x020b7408 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 020b5a34, method 020b5a64, 0x2e1c-byte state.
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

extern void func_ov054_020b5a34(void);
extern void func_ov054_020b5a64(void);

GameClassDescriptor data_ov054_020b73f4 = {
    10,  /* nClassId */
    6,  /* nGroupId */
    func_ov054_020b5a34,  /* pfnCtor */
    func_ov054_020b5a64,  /* pfnMethod */
    11804,  /* nAuxSize */
    0,  /* pArena */
};
