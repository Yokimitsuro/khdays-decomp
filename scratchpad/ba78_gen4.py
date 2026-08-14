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

E = "((Ov002PoseEntry *)(*(char **)(base + 4) + off))"

# d1: no entry local at all -- every use is the inline expression
B["d1_pureinline"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002Vec3 *from;

        if (src == 0) {
            from = &%s->vecIn;
        } else {
            from = src;
        }
        %s->vecOut = *from;
        if (value == -1) {
            %s->nValue = %s->nField0c;
        } else {
            %s->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
""" % (E, E, E, E, E)

# d2: same through a macro
B["d2_macro"] = """#define ENTRY ((Ov002PoseEntry *)(*(char **)(base + 4) + off))

void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002Vec3 *from;

        if (src == 0) {
            from = &ENTRY->vecIn;
        } else {
            from = src;
        }
        ENTRY->vecOut = *from;
        if (value == -1) {
            ENTRY->nValue = ENTRY->nField0c;
        } else {
            ENTRY->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""

# e1: entry at function scope, from inside the loop body
B["e1_entryouter"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    Ov002PoseEntry *entry;
    int off = 0;
    int i = 0;

    do {
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

# e2: entry at function scope declared first of all
B["e2_entryfirst"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    Ov002PoseEntry *entry;
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
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

# e3: entry at function scope, explicit destination local inside the body
B["e3_entryouter_dstinner"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    Ov002PoseEntry *entry;
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002Vec3 *from;
        Ov002Vec3 *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
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

# e4: from at function scope, entry inside the loop body
B["e4_fromouter"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    Ov002Vec3 *from;
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
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

# e5: entry outer, from outer, declared entry-before-from
B["e5_bothouter"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    Ov002PoseEntry *entry;
    Ov002Vec3 *from;
    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
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

# e6: entry outer declared after base but before the counters, from inner,
#     destination written through the entry with an explicit cast
B["e6_entrymid"] = """void func_ov002_0206ba78(Ov002Vec3 *src, int value) {
    char *base = data_ov002_0207fa00 + 0x8bcc;
    Ov002PoseEntry *entry;
    Ov002Vec3 *from;
    int off = 0;
    int i = 0;

    do {
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

out = os.path.join("build", "try", "ba78")
if not os.path.isdir(out):
    os.makedirs(out)
for name, body in B.items():
    with open(os.path.join(out, name + ".c"), "w") as f:
        f.write(HEAD + body)
print("wrote %d" % len(B))
