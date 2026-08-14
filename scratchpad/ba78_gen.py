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

BODIES = {}

# v1: explicit destination local
BODIES["v1_dstlocal"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;
        Ov002Vec3 *dst;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        dst = &entry->vecOut;
        *dst = *from;
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

# v2: destination local declared before from
BODIES["v2_dstfirst"] = BODIES["v1_dstlocal"].replace(
    "        Ov002Vec3 *from;\n        Ov002Vec3 *dst;\n",
    "        Ov002Vec3 *dst;\n        Ov002Vec3 *from;\n")

# v3: entry declared last
BODIES["v3_entrylast"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002Vec3 *from;
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);

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

# v4: copy through a cast of the entry base
BODIES["v4_castcopy"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
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
        *(Ov002Vec3 *)((char *)entry + 0x34) = *from;
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

# v5: entry inline everywhere, dst local holds the destination
BODIES["v5_inline_dst"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002Vec3 *from;
        Ov002Vec3 *dst;

        if (src == 0) {
            from = &((Ov002PoseEntry *)(*(char **)(base + 4) + off))->vecIn;
        } else {
            from = src;
        }
        dst = &((Ov002PoseEntry *)(*(char **)(base + 4) + off))->vecOut;
        *dst = *from;
        if (value == -1) {
            ((Ov002PoseEntry *)(*(char **)(base + 4) + off))->nValue =
                ((Ov002PoseEntry *)(*(char **)(base + 4) + off))->nField0c;
        } else {
            ((Ov002PoseEntry *)(*(char **)(base + 4) + off))->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# v6: from declared inside the if/else scope's enclosing block, entry const
BODIES["v6_dst_before_from"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *dst = &entry->vecOut;
        Ov002Vec3 *from;

        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
        *dst = *from;
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

# v7: table pointer read into a local each iteration
BODIES["v7_tbllocal"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        char *tbl = *(char **)(base + 4);
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(tbl + off);
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

# v8: copy written as an assignment of the whole struct through two named pointers,
#     with the destination pointer reused as the value-writing cursor
BODIES["v8_dst_used_after"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
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
        if (value != -1) {
            entry->nValue = value;
        } else {
            entry->nValue = entry->nField0c;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

out = os.path.join("build", "try", "ba78")
if not os.path.isdir(out):
    os.makedirs(out)
for name, body in BODIES.items():
    with open(os.path.join(out, name + ".c"), "w") as f:
        f.write(HEAD + body)
    print(os.path.join(out, name + ".c"))
