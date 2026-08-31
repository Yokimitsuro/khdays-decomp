#!/usr/bin/env python3
"""Reverify every curated non-C report source before refreshing its attestation.

Requires the local compiler and ROM-derived build/func_index.json. CI consumes
the checked-in, source-hashed manifest; it never assumes all ASM stubs match.
"""
import hashlib
import json
import subprocess
import sys

from report_asm import ROOT, MANIFEST, source_digest, validate_owner


def main():
    path = ROOT / MANIFEST
    manifest = json.loads(path.read_text(encoding="utf-8"))
    index = json.loads((ROOT / "build/func_index.json").read_text())
    for name, entry in manifest["functions"].items():
        validate_owner(name, entry)
        target = index[name]
        command = [sys.executable, str(ROOT / "tools/verify_idx.py"), entry["source"], name]
        if target["mode"] == "thumb":
            command.append("--thumb")
        digest = source_digest(ROOT / entry["source"])
        subprocess.run(command, cwd=ROOT, check=True)
        if source_digest(ROOT / entry["source"]) != digest:
            raise RuntimeError(f"Source changed during verification: {name}")
        entry.update(source_sha256=digest, mode=target["mode"], size=target["size"],
                     target_sha256=hashlib.sha256(bytes.fromhex(target["hex"])).hexdigest())
    # Write only after every source has passed byte and relocation verification.
    path.write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8", newline="\n")
    print(f"VERIFIED_REPORT_ASM={len(manifest['functions'])}")


if __name__ == "__main__":
    main()
