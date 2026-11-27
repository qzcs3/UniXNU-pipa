// SPDX-License-Identifier: BSD-2-Clause-Patent
// No-op definitions of the probe hooks the patched XNU references while pipa_defconfig leaves their component out.
// Each hook runs only on its boot argument, which board.toml does not pass; the kernel link needs the symbol anyway.

// offline-component-load-probes.patch, bsd_init: called on offline-legacy-register=1 (NativeLegacyDisplay). Weak: with
// CONFIG_XNU_NATIVE_LEGACY_DISPLAY the display archive's LegacyDisplayProbe.cpp defines the real probe.
void native_legacy_display_probe(void);
__attribute__((weak)) void native_legacy_display_probe(void)
{
}

// NativeHidInput registers its button callback with a board button driver (power, volume up/down). Weak: Buttons.c (in the
// display archive) defines the real one. The kernel is linked statically, where an undefined weak reference does not link.
void native_buttons_set_sink(void (*sink)(void *, unsigned), void *context);
__attribute__((weak)) void native_buttons_set_sink(void (*sink)(void *, unsigned), void *context)
{
  (void)sink;
  (void)context;
}

// NativeAdrenoPublish.cpp (CONFIG_XNU_NATIVE_ADRENO) hands the Metal plugin's exported pipeline caches to the board log, which
// UniXNU-tb128fu's BootLog.c writes into NativeUfs's export region. pipa has no UFS write path yet: -4 is BootLog.c's answer
// when there is no export region.
typedef unsigned int u32;
int boot_log_export_put(u32 generation, u32 total, u32 offset, const void *data, u32 size);
__attribute__((weak)) int boot_log_export_put(u32 generation, u32 total, u32 offset, const void *data, u32 size)
{
  (void)generation;
  (void)total;
  (void)offset;
  (void)data;
  (void)size;
  return -4;
}

// When OWNER_ROOT_AUDIT is disabled, vfs_syscalls still references native_owner_root_accepted
// and native_owner_root_mount_device under the macOS profile.
typedef int dev_t;
volatile int native_owner_root_accepted = 0;
volatile dev_t native_owner_root_mount_device = (dev_t)-1;
void native_owner_root_accepted_checkpoint(int apple, int owner);
__attribute__((weak)) void native_owner_root_accepted_checkpoint(int apple, int owner)
{
  (void)apple;
  (void)owner;
}

// Native exit trace stub for macOS k27 parity
void native_exit_trace(int pid, const char *name, int status);
__attribute__((weak)) void native_exit_trace(int pid, const char *name, int status)
{
  (void)pid;
  (void)name;
  (void)status;
}

// GOP handoff stubs when legacy display is not linked in M1
int native_gop_handoff_call(unsigned int op, void *task, const void *in, unsigned long inSize, void *out, unsigned long outSize);
__attribute__((weak)) int native_gop_handoff_call(unsigned int op, void *task, const void *in, unsigned long inSize, void *out, unsigned long outSize)
{
  (void)op;
  (void)task;
  (void)in;
  (void)inSize;
  (void)out;
  (void)outSize;
  return -1;
}

void *native_gop_handoff_memory(void);
__attribute__((weak)) void *native_gop_handoff_memory(void)
{
  return 0;
}

// corecrypto original kmod stubs for first pass
void *source_corecrypto14_original(void);
__attribute__((weak)) void *source_corecrypto14_original(void)
{
  return 0;
}

int source_corecrypto14_start_once(void *module, void *data);
__attribute__((weak)) int source_corecrypto14_start_once(void *module, void *data)
{
  (void)module;
  (void)data;
  return 0;
}




