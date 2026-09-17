/* ov025 class descriptor data_ov025_020b4aec, 0x020b4aec-0x020b4b00 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  This one is the tag tracker helper class (class 0 / group 0xe, 020899a8 / 020899c8, 8-byte state), instantiated by Ov025_SetupContext 02083e84.
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

extern void func_ov025_020899a8(void);
extern void func_ov025_020899c8(void);

GameClassDescriptor data_ov025_020b4aec = {
    0,  /* nClassId */
    14,  /* nGroupId */
    func_ov025_020899a8,  /* pfnCtor */
    func_ov025_020899c8,  /* pfnMethod */
    8,  /* nAuxSize */
    0,  /* pArena */
};
