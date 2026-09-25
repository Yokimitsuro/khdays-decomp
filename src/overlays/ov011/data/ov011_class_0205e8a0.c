/* ov011 class descriptor data_ov011_0205e8a0, 0x0205e8a0-0x0205e8b4 (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  Constructor 0205ac40, method 0205b034, 0x2cf84-byte state.
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

extern void func_ov011_0205ac40(void);
extern void func_ov011_0205b034(void);

GameClassDescriptor data_ov011_0205e8a0 = {
    8,  /* nClassId */
    15,  /* nGroupId */
    func_ov011_0205ac40,  /* pfnCtor */
    func_ov011_0205b034,  /* pfnMethod */
    184196,  /* nAuxSize */
    0,  /* pArena */
};
