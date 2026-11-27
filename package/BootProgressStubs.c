/* SPDX-License-Identifier: MIT
 * Zero-valued storage for the optional components the boot-progress/ramoops page reads.
 * Every definition is weak so a real driver linked next to it takes precedence.
 */
#include <stdint.h>
#pragma clang attribute push (__attribute__((weak)), apply_to = any(function, variable))

void boot_ui_trace_snapshot(unsigned a) { (void)a; }
char boot_ui_trace_rows[14][120];
char boot_ui_trace_label[120];
unsigned boot_ui_trace_ready;
volatile unsigned boot_ui_trace_phase;
volatile unsigned boot_ui_trace_index;
void boot_process_capture(void) { }
void boot_process_snapshot(void) { }
void sheng_cpufreq_poll(void) { }
char boot_process_rows[10][120];
unsigned boot_ui_trace_role_rows(unsigned a,char b[][120],unsigned c,unsigned d) { (void)a;(void)b;(void)c;(void)d;return 0; }
unsigned boot_ui_trace_hot_rows(char rows[][120], unsigned max) { (void)rows; (void)max; return 0; }

char native_touch_rows[4][120];
char native_touch_trace[8][120];
volatile unsigned native_touch_stage_req;
volatile unsigned native_touch_stroke_count;
volatile int32_t native_touch_strokes[16][7];
volatile int32_t native_touch_extent[4];

char native_buttons_row[120];
volatile unsigned native_buttons_changes;
volatile int native_buttons_error;
volatile uint32_t native_buttons_mask;
void native_buttons_set_sink(void (*a)(void *, uint32_t), void *b) { (void)a; (void)b; }

char native_battery_row[120];
volatile unsigned native_battery_changes;
volatile int native_battery_error;
volatile unsigned native_battery_published;

char native_gesture_rows[8][120];
volatile unsigned native_gesture_written;
volatile int native_gesture_error;
char native_gesture_timeline[4096];
volatile unsigned native_gesture_timeline_seq;

volatile uint64_t native_ufs_block_reads;
volatile uint64_t native_ufs_block_failures;
volatile uint64_t native_ufs_read_ticks;
volatile uint64_t native_ufs_verify_ticks;
struct native_ufs_reader_view { char name[24]; uint64_t reads, failures, read_ticks, verify_ticks; };
struct native_ufs_reader_view native_ufs_readers[12];
int native_ufs_store_write_cached(uint64_t b, uint32_t n, const void *s) { (void)b; (void)n; (void)s; return 0; }

char native_gpu_rows[31][120];
volatile unsigned native_gpu_changes;
volatile unsigned native_gpu_step;

char native_mdss_rows[31][120];
volatile unsigned native_mdss_changes;
volatile unsigned native_mdss_step;

char native_flip_rows[16][120];
volatile unsigned native_flip_changes;

volatile uint32_t native_legacy_stage;
volatile uint32_t native_legacy_gop_width;
volatile uint32_t native_legacy_gop_height;
volatile uint64_t native_legacy_gop_virtual;
volatile uint64_t native_legacy_gop_physical;
volatile uint64_t native_legacy_gop_bytes;
volatile uint32_t native_legacy_swap_validation_calls;
volatile uint32_t native_legacy_transfer_calls;
volatile uint32_t native_legacy_retirement_calls;
volatile uint32_t native_legacy_client_calls;
volatile int native_legacy_unit_scale_status;
volatile uint32_t native_legacy_unit_scale_calls;
volatile uint32_t native_legacy_chosen_scale;
volatile uint32_t native_legacy_chosen_rotation;
unsigned native_legacy_swap_pacing(char *out, unsigned cap) { (void)out; (void)cap; return 0; }
unsigned native_legacy_prepare_brief(char *out, unsigned cap) { (void)out; (void)cap; return 0; }
unsigned native_legacy_vsync_brief(char *out, unsigned cap) { (void)out; (void)cap; return 0; }
int native_legacy_vsync_kick(void) { return 0; }
volatile uint32_t native_legacy_gpu_fallbacks;
volatile uint32_t native_legacy_gpu_last_status;
volatile uint64_t native_legacy_early_retires;
volatile uint64_t native_legacy_early_failures;

volatile uint32_t armcpu_smp_step[8];
volatile uint32_t armcpu_smp_running;
volatile unsigned long armcpu_ipi_sent;
volatile unsigned long armcpu_ipi_interrupts;
volatile uint32_t armcpu_spi_ipi_base;

struct native_adreno_client_text_view { char name[20]; char text[100]; };
struct native_adreno_client_text_view native_adreno_client_text[4];
struct native_adreno_client_record { char name[20]; uint32_t opens, refused, closes, slot, peak_mib, last_refusal; };
struct native_adreno_client_record native_adreno_client_log[8];
struct native_adreno_metal_diag_view { uint32_t flags, phase, step, error; };
struct native_adreno_metal_diag_view native_adreno_metal_diag;
struct native_adreno_open_record { char name[20]; uint32_t pid, slot; };
struct native_adreno_open_record native_adreno_open_log[8];
volatile uint32_t native_adreno_open_log_count;
struct native_adreno_asker_record { char name[20]; uint32_t reads; };
struct native_adreno_asker_record native_adreno_metal_askers[12];
volatile int native_gpu_addon_files, native_gpu_addon_written, native_gpu_addon_same, native_gpu_addon_failed, native_gpu_addon_error;
volatile int native_gpu_addon_stage, native_gpu_addon_status, native_gpu_addon2_stage, native_gpu_addon2_status, native_gpu_addon3_stage, native_gpu_addon3_status;
volatile uint64_t native_gop_wait_stats[7];
volatile uint32_t native_adreno_fence_wait[8];
char native_adreno_metal_rows[48][96];

#pragma clang attribute pop
