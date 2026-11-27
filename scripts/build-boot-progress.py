#!/usr/bin/env python3
"""Archive the board's boot progress hooks for the kernel link: kits/pipa/BootRamoops.c, the kernel log in the stock ramoops console
zone (XNU_BOOT_PROGRESS with XNU_BOOT_PROGRESS_STANDALONE), and kits/pipa/BootWatchdogPolicy.c (UniXNU-tb128fu's, from sheng):
sheng_boot_watchdog_policy, which load_init_program calls with the owner root chain (sheng-disable-watchdogd, sheng-disable-jobs).
build-xnu-4k-baseline.sh runs this before the kernel build and force-loads build/boot-progress/libBootProgress.a. BootRamoops.c
declares the few kernel interfaces it calls, so it builds without the kernel's headers; the policy builds with kern_exec.o's
compile record of the previous XNU pass."""
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from kernel_target import TRIPLE
source = ROOT / 'kits/pipa/BootRamoops.c'
out = ROOT / 'build/boot-progress'
out.mkdir(parents=True, exist_ok=True)
obj, archive = out / 'BootRamoops.o', out / 'libBootProgress.a'

def compile_like(object_record, source, target, extra):
    """An XNU object's own compile command (its build record) with SOURCE and TARGET in place of its own, warnings dropped."""
    record = json.loads((ROOT / 'build/xnu/ios-obj/DEVELOPMENT_ARM64_BCM2837' / object_record).read_text().strip().rstrip(','))
    command, args, i = [], record['arguments'], 0
    while i < len(args):
        arg = args[i]
        if arg == record['file']:
            command.append(str(source))
        elif arg == '-o':
            command += ['-o', str(target)]
            i += 1
        elif arg.startswith('--target='):
            command.append(f'--target={TRIPLE}')
        elif arg in ('-MF', '-MT', '-MJ'):
            i += 1
        elif arg == '-Xclang' and args[i + 1].startswith('-W'):
            i += 1
        elif not arg.startswith('-W'):
            command.append(arg)
        i += 1
    subprocess.run(command + ['-mgeneral-regs-only', '-Wall', '-Wextra', '-Werror',
                              '-Wno-overriding-option', '-Wno-missing-designated-field-initializers',
                              '-Wno-unused-but-set-global', *extra],
                   cwd=record['directory'], check=True, timeout=90)

compile_like('osfmk/DEVELOPMENT/startup.o.json', source, obj, ['-I', str(ROOT / '.cache/xnu-work/osfmk')])

# The policy with kern_exec.o's command (BSD).
policy_obj = out / 'BootWatchdogPolicy.o'
compile_like('bsd/DEVELOPMENT/kern_exec.o.json', ROOT / 'kits/pipa/BootWatchdogPolicy.c', policy_obj, [])
# kits/pipa/BootFaultProbe.c (UniXNU-tb128fu's, from sheng): the EL0 breakpoint/abort records and the crash line of an exiting
# process, which BootRamoops.c writes to the log. It reads Mach's task and VM internals: startup.o's command (osfmk), as
# UniXNU-tb128fu compiles it.
fault_obj = out / 'BootFaultProbe.o'
compile_like('osfmk/DEVELOPMENT/startup.o.json', ROOT / 'kits/pipa/BootFaultProbe.c', fault_obj,
             ['-I', str(ROOT / '.cache/xnu-work/osfmk')])

# kits/pipa/BootProcessProbe.c and BootUiTraceProbe.c (UniXNU-tb128fu's, sheng's unchanged): the process pass and the user and
# kernel stacks of backboardd's and SpringBoard's threads, which BootRamoops.c captures on a worker of its own and logs. They read
# Mach's task, thread and IPC internals: startup.o's command (osfmk), as BootFaultProbe.c.
probe_objs = []
for probe in ('BootProcessProbe', 'BootUiTraceProbe', 'BootProgressStubs'):
    probe_obj = out / f'{probe}.o'
    compile_like('osfmk/DEVELOPMENT/startup.o.json', ROOT / f'kits/pipa/{probe}.c', probe_obj,
                 ['-I', str(ROOT / '.cache/xnu-work/osfmk')])
    probe_objs.append(probe_obj)

archive.unlink(missing_ok=True)
subprocess.run(['xcrun', 'ar', 'rcs', archive, obj, policy_obj, fault_obj, *probe_objs], check=True)
print(archive)
