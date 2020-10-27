# FdFix

This plugin fixes an issue in PS Vita homebrews where file descriptors are invalidated after suspend and resume.

## Installation

1. Download [fd_fix.skprx](https://github.com/TheOfficialFloW/FdFix/releases/download/v1.0/fd_fix.skprx)

2. Add these lines to taiHEN config.txt at `ux0:tai/config.txt`:

   ```
   *KERNEL
   ux0:tai/fd_fix.skprx
   ```

3. Reboot your device and relaunch HENkaku.