/* ov022 class descriptor data_ov022_020b2894, 0x020b2894-0x020b28a8 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 02082a40, method 02082b84, 0x40-byte state.
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

extern void func_ov022_02082a40(void);
extern void func_ov022_02082b84(void);

GameClassDescriptor data_ov022_020b2894 = {
    8,  /* nClassId */
    15,  /* nGroupId */
    func_ov022_02082a40,  /* pfnCtor */
    func_ov022_02082b84,  /* pfnMethod */
    64,  /* nAuxSize */
    0,  /* pArena */
};
