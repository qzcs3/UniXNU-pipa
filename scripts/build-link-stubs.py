#!/usr/bin/env python3
"""Archive the no-op probe hooks of kits/pipa/LinkStubs.c for the kernel link (CONFIG_XNU_EXTRA_LD_ARCHIVES)."""
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from kernel_target import TRIPLE

source = ROOT / 'kits/pipa/LinkStubs.c'
out = ROOT / 'build/link-stubs'
out.mkdir(parents=True, exist_ok=True)
obj, archive = out / 'LinkStubs.o', out / 'libLinkStubs.a'
clang = os.environ.get('CROSS_CLANG', '/opt/unixnu-linux/llvm/bin/clang')
subprocess.run([clang, f'--target={TRIPLE}', '-mkernel',
                '-Os', '-Wall', '-Werror', '-Wno-overriding-option', '-c', source, '-o', obj], check=True)
archive.unlink(missing_ok=True)
subprocess.run(['xcrun', 'ar', 'rcs', archive, obj], check=True)
print(archive)
