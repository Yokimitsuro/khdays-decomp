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

B = {}

# b1: typed table-of-pointers view of the base block
B["b1_typedbase"] = """typedef struct {
    char *pad0;
    Ov002PoseEntry *pEntries;
} Ov002PoseTable;

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    Ov002PoseTable *tbl = (Ov002PoseTable *)(data_ov002_0207fa00 + 0x8bcc);
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)((char *)tbl->pEntries + off);
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

# b2: for-loop form
B["b2_forloop"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i;

    for (i = 0; i < 4; i++) {
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
        off += 0x44;
    }
}
"""

# b3: entry is a char* cursor, all accesses cast off it
B["b3_charcursor"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        char *entry = *(char **)(base + 4) + off;
        Ov002Vec3 *from;

        if (src == 0) {
            from = (Ov002Vec3 *)entry;
        } else {
            from = src;
        }
        *(Ov002Vec3 *)(entry + 0x34) = *from;
        if (value == -1) {
            *(int *)(entry + 0x40) = *(int *)(entry + 0x0c);
        } else {
            *(int *)(entry + 0x40) = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# b4: source cursor named, destination expression a member of a nested struct
B["b4_nested"] = """typedef struct {
    Ov002Vec3 vec;
    int nValue;
} Ov002PoseOut;

typedef struct {
    Ov002Vec3 vecIn;
    int nField0c;
    char pad0010[0x24];
    Ov002PoseOut out;
} Ov002PoseEntry2;

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry2 *entry = (Ov002PoseEntry2 *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        entry->out.vec = *from;
        if (value == -1) {
            entry->out.nValue = entry->nField0c;
        } else {
            entry->out.nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# b5: const-qualified source parameter
B["b5_constsrc"] = """void func_ov002_0206ba78(const Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        const Ov002Vec3 *from;

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

# b6: off declared after i
B["b6_offlast"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int i = 0;
    int off = 0;

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

# b7: the value decision reads through a second named pointer to the same entry
B["b7_secondview"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
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
        entry->nValue = (value == -1) ? entry->nField0c : value;
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# b8: base kept as the raw global, offset folded into every access
B["b8_nobase"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)
            (*(char **)(data_ov002_0207fa00 + 0x8bcc + 4) + off);
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

# b9: the copy source is dereferenced into the destination via an explicit
#     pointer-to-pointer chain so the destination is materialised first
B["b9_dstfirstexpr"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from = src;

        if (from == 0) {
            from = &entry->vecIn;
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

# b10: entry recomputed for the value decision (two separate temps)
B["b10_recompute"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        *(Ov002Vec3 *)&entry->vecOut = *from;
        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        off += 0x44;
        i++;
    } while (i < 4);
}
"""

out = os.path.join("build", "try", "ba78")
if not os.path.isdir(out):
    os.makedirs(out)
for name, body in B.items():
    with open(os.path.join(out, name + ".c"), "w") as f:
        f.write(HEAD + body)
print("wrote %d" % len(B))
