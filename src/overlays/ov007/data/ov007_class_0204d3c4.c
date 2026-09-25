/* ov007 class descriptor data_ov007_0204d3c4, 0x0204d3c4-0x0204d3d8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 0204cb80, method 0204ce30, 0x5ac4-byte state.
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

extern void func_ov007_0204cb80(void);
extern void func_ov007_0204ce30(void);

GameClassDescriptor data_ov007_0204d3c4 = {
    8,  /* nClassId */
    13,  /* nGroupId */
    func_ov007_0204cb80,  /* pfnCtor */
    func_ov007_0204ce30,  /* pfnMethod */
    23236,  /* nAuxSize */
    0,  /* pArena */
};
