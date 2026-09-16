/* ov008 class descriptor data_ov008_020900d8, 0x020900d8-0x020900ec (.data).
 *
 * InstantiateClass (02023930 / 02023960) builds a task object from it: the
 * u16 class / group ids, the constructor whose return is the first state
 * function, the method slot, the size of the zero-filled auxiliary block and
 * the arena reference.  This one is the tag tracker helper class (Ov008_Set_5d98, 8-byte state).
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

extern void func_ov008_02055d98(void);
extern void func_ov008_02055db8(void);

GameClassDescriptor data_ov008_020900d8 = {
    0,  /* nClassId */
    14,  /* nGroupId */
    func_ov008_02055d98,  /* pfnCtor */
    func_ov008_02055db8,  /* pfnMethod */
    8,  /* nAuxSize */
    0,  /* pArena */
};
