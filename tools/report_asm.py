"""Source-bound attestations for the narrowly approved non-C report matches."""
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = Path("config/arm9/report_asm_matches.json")


def source_digest(path):
    # Git's Windows checkout may use CRLF; CI uses LF for the same source.
    return hashlib.sha256(path.read_text(encoding="utf-8").encode("utf-8")).hexdigest()


def validate_owner(name, entry, root=ROOT):
    source = entry["source"]
    path = Path(source)
    if path.is_absolute() or ".." in path.parts or "nonmatching" in path.parts:
        raise ValueError(f"Invalid report source: {source}")
    if path.stem != name or path.suffix != ".c":
        raise ValueError(f"Report source does not identify {name}: {source}")
    kind = entry["kind"]
    if kind == "canonical_sdk_asm":
        if not re.fullmatch(r"libs/(?:nitro|msl)/[^/]+/asm_stubs/(?:auto|calls)/[^/]+\.c", source):
            raise ValueError(f"SDK assembly must be library-owned: {source}")
    elif kind == "authorized_clz":
        approvals = json.loads((root / "config/arm9/asm_exceptions.json").read_text())
        approval = approvals.get("exceptions", {}).get(name, {})
        if not (approval.get("kind") == "single_inline_clz"
                and approval.get("approved_by") == "user"
                and approval.get("classification") == "authorized_asm_exception"
                and approval.get("counts_as_real_c") is False):
            raise ValueError(f"Missing explicit CLZ authorization: {name}")
        body = (root / source).read_text(encoding="utf-8")
        body = re.sub(r"/\*.*?\*/|//[^\n]*", "", body, flags=re.S)
        body, count = re.subn(r"\basm\s*\{\s*clz\s+(\w+)\s*,\s*\1\s*\}", "", body)
        if count != 1 or re.search(r"\b(?:asm|__asm|__asm__|dcd)\b", body, re.I):
            raise ValueError(f"CLZ authorization scope exceeded: {name}")
    else:
        raise ValueError(f"Unapproved non-C report kind: {kind}")


def load_verified_matches(root=ROOT):
    path = root / MANIFEST
    if not path.exists():
        return {}
    manifest = json.loads(path.read_text(encoding="utf-8"))
    if manifest.get("schema_version") != 1:
        raise ValueError("Unsupported ASM report manifest version")
    entries = manifest["functions"]
    for name, entry in entries.items():
        validate_owner(name, entry, root)
        if source_digest(root / entry["source"]) != entry.get("source_sha256"):
            raise ValueError(f"Stale ASM verification: {name}; run tools/verify_report_asm.py")
        if (entry.get("mode") not in ("arm", "thumb") or entry.get("size", 0) <= 0
                or not re.fullmatch(r"[0-9a-f]{64}", entry.get("target_sha256", ""))):
            raise ValueError(f"Missing byte-exact evidence: {name}")
    return entries


def is_verified_match(func, entries):
    entry = entries.get(func["name"])
    if not entry:
        return False
    if (func.get("source") != entry["source"] or func["size"] != entry["size"]
            or func.get("mode") != entry["mode"]):
        raise ValueError(f"ASM report symbol metadata changed: {func['name']}")
    return True
