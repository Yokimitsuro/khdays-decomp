import os

HEAD = """typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    Ov002Vec3 vecIn;            /* +0x00 */
    int nField0c;               /* +0x0c */
    char pad0010[0x24];
    Ov002Vec3 vecOut;           /* +0x34 */
    int nValue;                 /* +0x40 */
} Ov002PoseEntry;

extern char *data_ov002_0207fa00;

"""

LOOP = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
%s        i++;
        off += 0x44;
    } while (i < 4);
}
"""

B = {}

# c1: destination computed straight from the table, not from entry
B["c1_indepdst"] = LOOP % """        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;
        Ov002Vec3 *dst;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        dst = (Ov002Vec3 *)(*(char **)(base + 4) + off + 0x34);
        *dst = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c2: register hint on the entry pointer
B["c2_regentry"] = LOOP % """        register Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c3: register hint on the source pointer instead
B["c3_regfrom"] = LOOP % """        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        register Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c4: entry const-qualified
B["c4_constentry"] = LOOP % """        Ov002PoseEntry *const entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c5: the fallback source arm reached through a cast of the entry pointer
B["c5_castarm"] = LOOP % """        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = (Ov002Vec3 *)entry;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c6: destination member is a distinct struct type from the source
B["c6_distincttype"] = """typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    int x;
    int y;
    int z;
} Ov002VecOut;

typedef struct {
    Ov002Vec3 vecIn;
    int nField0c;
    char pad0010[0x24];
    Ov002VecOut vecOut;
    int nValue;
} Ov002PoseEntry;

extern char *data_ov002_0207fa00;

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002VecOut *from;

        if (src == 0) {
            from = (Ov002VecOut *)&entry->vecIn;
        } else {
            from = (Ov002VecOut *)src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# c7: the whole entry reached through a union view
B["c7_unionview"] = """typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    Ov002Vec3 vecIn;
    int nField0c;
    char pad0010[0x24];
    Ov002Vec3 vecOut;
    int nValue;
} Ov002PoseEntry;

extern char *data_ov002_0207fa00;

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry;
        Ov002Vec3 *from;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# c8: value written through the entry before the copy is spelled, but sequenced after
B["c8_valuefirstdecl"] = LOOP % """        Ov002PoseEntry *entry;
        Ov002Vec3 *from;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        from = src;
        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c9: entry declared volatile-free but the table pointer read through a typed array
B["c9_arrayview"] = LOOP % """        Ov002PoseEntry *entry = &(*(Ov002PoseEntry **)(base + 4))[0];
        Ov002Vec3 *from;

        entry = (Ov002PoseEntry *)((char *)entry + off);
        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c10: register hint on both loop pointers
B["c10_regboth"] = LOOP % """        register Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        register Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
"""

# c11: register hint on the loop offset
B["c11_regoff"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    register int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

out = os.path.join("build", "try", "ba78")
if not os.path.isdir(out):
    os.makedirs(out)
for name, body in B.items():
    src = body if body.lstrip().startswith("typedef") else HEAD + body
    with open(os.path.join(out, name + ".c"), "w") as f:
        f.write(src)
print("wrote %d" % len(B))
