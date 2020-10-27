#include <psp2kern/kernel/modulemgr.h>
#include <taihen.h>
#include <stdio.h>
#include <string.h>

static tai_hook_ref_t ksceVfsNodeInitializePartitionRef;
static SceUID uid = -1;

static int ksceVfsNodeInitializePartitionPatched(int *node, int *new_node_p,
                                                 void *opt, int flags) {
  int res = TAI_CONTINUE(int, ksceVfsNodeInitializePartitionRef, node,
                         new_node_p, opt, flags);

  if (res == 0 && new_node_p) {
    int *new_node = (int *)*new_node_p;
    int *mount = (int *)new_node[19];
    mount[20] &= ~0x10000;
  }

  return res;
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
  uid = taiHookFunctionExportForKernel(KERNEL_PID,
                                       &ksceVfsNodeInitializePartitionRef,
                                       "SceIofilemgr",
                                       TAI_ANY_LIBRARY,
                                       0xA5A6A55C,
                                       ksceVfsNodeInitializePartitionPatched);
  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  if (uid >= 0)
    taiHookReleaseForKernel(uid, ksceVfsNodeInitializePartitionRef);
  return SCE_KERNEL_STOP_SUCCESS;
}
