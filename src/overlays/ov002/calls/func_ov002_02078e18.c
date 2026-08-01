/*
 * Ov002_EnsureSceneManager - lazy-singleton initializer for the ov002 scene manager held at
 * data_ov002_0207fa28[1] (scene-root + 4). Dep of the gameplay constructor func_ov002_020679d4.
 *
 * If the manager already exists it returns the requested scene id unchanged. Otherwise it
 * allocates the manager (func_ov002_020769b0, tag 0x26a8), allocates and fills(-1) its 0x18-byte
 * sub-buffer at mgr+0x5c, runs func_02025668(buf, 0xa0), initialises the 0x18 sub-objects laid
 * out at mgr+0xb8 with stride 0x184 (func_0202c594), writes the header record at mgr+0x2518
 * ({ scene id, 0x5d588b65, 0x269ec3 }), clears mgr+0x58 and kicks the manager via
 * func_ov002_0207643c(0x1f, mgr).
 *
 * THUMB. The scene-root global is volatile so mgr (root+4) is re-read on every access, matching
 * the original (which re-materialises the pool address and reloads root+4 rather than caching the
 * freshly stored pointer across the intervening allocator calls). The function returns the scene
 * id on the "already initialised" path; the caller ignores the result on the create path, so no
 * value is produced there (returning one would add a redundant load). Returning sceneId on the
 * early path is also what keeps it live in r0 across the null check, so the compiler leaves the
 * manager pointer in r1 and folds the parameter spill into the load-delay slot.
 */

extern volatile int data_ov002_0207fa28[];
extern int  func_ov002_020769b0(int tag, int count, int elemSize);
extern int  NNSi_FndAllocFromDefaultExpHeap(int size);
extern void INITi_CpuClear32_0x01ff86fc(int value, int dest, int numBytes);
extern void func_02025668(int buf, int size);
extern void func_0202c594(int entry);
extern void func_ov002_0207643c(int cmd, int mgr);

int func_ov002_02078e18(int sceneId)
{
    int i;

    if (data_ov002_0207fa28[1] != 0) return sceneId;

    data_ov002_0207fa28[1] = func_ov002_020769b0(0x26a8, 0x5c, 0xa0);
    *(int *)(data_ov002_0207fa28[1] + 0x5c) = NNSi_FndAllocFromDefaultExpHeap(0x18);
    INITi_CpuClear32_0x01ff86fc(-1, *(int *)(data_ov002_0207fa28[1] + 0x5c), 0x18);
    func_02025668(*(int *)(data_ov002_0207fa28[1] + 0x5c), 0xa0);
    for (i = 0; i < 0x18; i++) {
        func_0202c594(data_ov002_0207fa28[1] + 0xb8 + i * 0x184);
    }
    {
        int *rec = (int *)(data_ov002_0207fa28[1] + 0x2518);
        rec[0] = sceneId;
        rec[1] = 0x5d588b65;
        rec[2] = 0x269ec3;
    }
    *(int *)(data_ov002_0207fa28[1] + 0x58) = 0;
    func_ov002_0207643c(0x1f, data_ov002_0207fa28[1]);
}
