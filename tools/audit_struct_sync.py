"""audit_struct_sync.py -- object layouts decoded in the C tree that Ghidra does not have.

The struct rule says: when you decode a layout, create the Ghidra type IN THE SAME
BATCH.  A struct is "real" only when both halves exist -- in the .c, because that is
what makes the match and what the port reads, and in Ghidra, because that is what
makes every OTHER function touching the object readable.

    python tools/audit_struct_sync.py            # summary + the real debt, ranked
    python tools/audit_struct_sync.py --all      # also show what was filtered and why
    python tools/audit_struct_sync.py --list     # every file of every debt entry

WHY THE CLASSIFICATION EXISTS (rewritten 2026-07-23).  The first version counted every
named struct in the tree against Ghidra and reported "817 of 878 unsynced".  That number
is not debt, and chasing it would waste a session: most of those names are not object
layouts at all.  Measured over the whole tree, they split three ways.

  * CODEGEN DEVICES.  `struct bf { unsigned b : 8; }` appears in 407 files and
    `struct hw60 { unsigned short lo:8, hi:8; }` in 658.  A bit-field-only struct has no
    address and no semantics: it exists to force `lsl #24 ; lsr #24` instead of
    `and #0xff`, or a bit-0 extract instead of `and #1`.  Typing them in Ghidra would be
    inventing a data model the game does not have.  DETECTED, not blocklisted: every
    member is a bit-field.

  * SCRATCH NAMES.  `Obj` is declared in 596 files with 61 DIFFERENT bodies; `S` in 292
    files with 67.  The name is a per-file placeholder, so there is nothing to unify --
    and unifying it would be actively wrong.  Detected by disagreement across files.

  * ALIASES of a type Ghidra already has.  `Vec3` (527 files), `vec3`, `vec`, `v3` and
    `w3` are all `int x, y, z`, which is the existing VecFx32; `hw60` is `Hw60`.  Reported
    separately so they are not mistaken for missing work.

What is left -- one consistent body, more than a bit-field, no Ghidra type of that name
and no existing type of that shape -- is the real debt, and it is small.

The old version also had a bug worth remembering: it built the "Ghidra knows this" set
with `re.findall(r'\\w+')` over the whole bridge response, so any word appearing in a
path or a description counted as a type.  A membership test that cannot fail is not a
test.  This one parses the `Name | Size: N | Path: P` rows.
"""
import os
import re
import sys
import urllib.parse
import urllib.request
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BRIDGE = "http://127.0.0.1:8089"

# `} NAME;` also closes an if/loop followed by a bare statement, which is how `break`
# and `return` showed up as "structs" on this tool's first ever run.
KEYWORDS = {"break", "return", "continue", "goto", "else", "do", "while", "if", "switch"}

TAGGED = re.compile(r"\bstruct\s+(\w+)\s*\{(.*?)\}\s*;", re.S)
TYPEDEF = re.compile(r"\btypedef\s+struct\s*(?:\w+\s*)?\{(.*?)\}\s*(\w+)\s*;", re.S)

# Shapes Ghidra already carries.  Keyed by the NORMALISED shape (member types and array
# lengths, field names dropped) so that `int w[11]`, `int a[11]` and `int m[11]` all land
# on the same entry -- the field names in these are arbitrary per file.
SHAPE_ALIASES = {
    "int,int,int": "VecFx32",
    "int[3]": "VecFx32",
    "int[9]": "MtxFx33",
    "int[3][3]": "MtxFx33",
    "int[11]": "ActorXfmBlock",
    "int,int,int,int": "Quaternion",
    "int[4]": "Quaternion",
}


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", " ", text)


def norm(body):
    return " ".join(body.split())


def collect():
    """name -> (Counter of bodies, set of files)."""
    bodies = defaultdict(Counter)
    files = defaultdict(set)
    for base in ("src", "libs"):
        for dirpath, dirnames, names in os.walk(os.path.join(ROOT, base)):
            dirnames[:] = [d for d in dirnames if d != "asm_stubs"]
            for name in names:
                if not name.endswith(".c"):
                    continue
                path = os.path.join(dirpath, name)
                rel = os.path.relpath(path, ROOT).replace(os.sep, "/")
                try:
                    with open(path, encoding="utf-8", errors="replace") as fh:
                        text = strip_comments(fh.read())
                except OSError:
                    continue
                for match in TAGGED.finditer(text):
                    if match.group(1) in KEYWORDS:
                        continue
                    bodies[match.group(1)][norm(match.group(2))] += 1
                    files[match.group(1)].add(rel)
                for match in TYPEDEF.finditer(text):
                    if match.group(2) in KEYWORDS:
                        continue
                    bodies[match.group(2)][norm(match.group(1))] += 1
                    files[match.group(2)].add(rel)
    return bodies, files


PAD = re.compile(r"^(?:char|unsigned char|u8|char\s+unsigned)\s+\w*pad\w*\s*\[", re.I)


def members_of(body):
    """Split a normalised body into members, expanding `int a, b, c;` into three."""
    out = []
    for chunk in body.split(";"):
        chunk = chunk.strip()
        if not chunk:
            continue
        if "," in chunk and "[" not in chunk and ":" not in chunk:
            head = chunk.split()[0]
            for part in chunk.split(","):
                part = part.strip()
                out.append(part if " " in part else "%s %s" % (head, part))
        else:
            out.append(chunk)
    return out


def normalised_shape(body):
    """Member types with names dropped: `int x, y, z;` -> `int,int,int`."""
    shape = []
    for member in members_of(body):
        if ":" in member:
            return None                       # bit-fields are not a shape
        m = re.match(r"^(.*?)\s*\**\s*\w+\s*((?:\[[^\]]*\])*)\s*$", member)
        if not m:
            return None
        base = " ".join(m.group(1).split())
        if "*" in member.split()[-1] or "*" in member:
            base += " *"
        shape.append(base + m.group(2))
    return ",".join(shape) if shape else None


def kind_of(body):
    """'device' for an accessor/copy shim, 'layout' for something that describes an object.

    An object layout has to name at least three real fields.  Everything short of that is
    a way of REACHING a field or COPYING N words: a bit-field to force lsl/lsr, a padding
    run plus one member to reach an offset, a bag of unnamed words to force ldm/stm.  None
    of those is a claim about the object, so none of them belongs in Ghidra.
    """
    members = members_of(body)
    if not members:
        return "device"
    if all(":" in m for m in members):
        return "device"
    real = [m for m in members if not PAD.match(m)]
    return "device" if len(real) <= 2 else "layout"


def ghidra_types():
    """Names Ghidra actually has, parsed from the `Name | Size: N | Path: P` rows."""
    found = set()
    for pattern in ("a", "e", "i", "o", "u", "_", "0", "1", "2", "3"):
        url = "%s/search_data_types?%s" % (
            BRIDGE, urllib.parse.urlencode({"pattern": pattern, "limit": 2000}))
        try:
            with urllib.request.urlopen(url, timeout=180) as fh:
                text = fh.read().decode("utf-8", "replace")
        except Exception as exc:  # noqa: BLE001 - bridge down is a normal outcome
            if not found:
                print("!! Ghidra bridge unreachable (%s) -- start it on :8089." % exc)
                sys.exit(2)
            break
        for line in text.splitlines():
            parts = [p.strip() for p in line.split("|")]
            if len(parts) >= 3 and parts[1].startswith("Size:") and parts[2].startswith("Path:"):
                name = parts[0]
                if name and "*" not in name and "[" not in name:
                    found.add(name)
    return found


def main():
    show_all = "--all" in sys.argv
    show_files = "--list" in sys.argv

    bodies, files = collect()
    known = ghidra_types()

    synced, device, scratch, alias, debt = [], [], [], [], []
    for name, counter in bodies.items():
        nfiles = len(files[name])
        total = sum(counter.values())
        top_body, top_n = counter.most_common(1)[0]
        agreement = top_n * 100 // total
        row = [nfiles, name, len(counter), agreement, top_body]

        target = SHAPE_ALIASES.get(normalised_shape(top_body) or "")
        if name in known:
            synced.append(row)
        elif len(counter) > 2 and agreement < 60:
            scratch.append(row)
        elif target in known:
            alias.append(row + [target])
        elif kind_of(top_body) == "device":
            device.append(row)
        else:
            debt.append(row)

    for group in (synced, device, scratch, alias, debt):
        group.sort(key=lambda r: (-r[0], r[1]))

    print("named structs declared in the C tree: %d" % len(bodies))
    print("  already a Ghidra type ............. %4d" % len(synced))
    print("  codegen devices (bit-fields only) . %4d  no address, nothing to type" % len(device))
    print("  scratch names (bodies disagree) ... %4d  a placeholder, not one object" % len(scratch))
    print("  aliases of an existing type ....... %4d" % len(alias))
    print("  >>> REAL DEBT ..................... %4d" % len(debt))
    print()

    if alias:
        print("aliases -- already typed under another name:")
        for nfiles, name, _v, _a, _b, target in alias[:12]:
            print("  %-22s %4d file(s)  ->  %s" % (name, nfiles, target))
        print()

    print("real debt, richest first:")
    for nfiles, name, variants, agreement, body in debt[:40]:
        print("  %-22s %4d file(s)  %d variant(s), %d%% agree" % (
            name, nfiles, variants, agreement))
        print("      %s" % body[:140])
        if show_files:
            for path in sorted(files[name])[:8]:
                print("        %s" % path)

    if show_all:
        print("\nfiltered as codegen devices:")
        for nfiles, name, _v, _a, body in device[:20]:
            print("  %-22s %4d file(s)  %s" % (name, nfiles, body[:80]))
        print("\nfiltered as scratch names:")
        for nfiles, name, variants, agreement, _b in scratch[:20]:
            print("  %-22s %4d file(s)  %d variants, top body only %d%%" % (
                name, nfiles, variants, agreement))


if __name__ == "__main__":
    main()
