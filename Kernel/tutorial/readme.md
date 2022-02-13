# kernel exception for ko

### step 1. run a user space executable file and stopped unexpectedly
- `$ ./test` run the executable file directly
````
Killed
````

### step 2. use gdb to check the executable file
- `$ gdb test` use gdb to debug
- `(gdb) run`
````
Starting program: /usr/bin/test 
[Inferior 1 (process 4317) exited with code 01]
````

- `(gdb) bt` to show back trace
````
No stack.
````
- got nothing, it could be a kernel exception instead of executable issue

### step 3. use dmesg to check kernel log
- print or control the kernel ring buffer
  - `$ dmesg` to check the kernel log
````
[  464.342837] BUG: kernel NULL pointer dereference, address: 0000000000000000
[  464.342838] #PF: supervisor write access in kernel mode
[  464.342839] #PF: error_code(0x0002) - not-present page
[  464.342840] PGD 0 P4D 0 
[  464.342841] Oops: 0002 [#4] SMP NOPTI
[  464.342843] CPU: 11 PID: 4028 Comm: test Tainted: G      D    OE     5.4.174 #11
[  464.342844] Hardware name: VMware, Inc. VMware Virtual Platform/440BX Desktop Reference Platform, BIOS 6.00 11/12/2020
[  464.342847] RIP: 0010:hugo_ioctl+0x2e/0x160 [hugo]
[  464.342848] Code: 00 55 48 89 e5 41 57 41 56 41 55 41 54 41 89 f4 53 48 89 d3 4c 8b af c8 00 00 00 48 c7 c7 50 b3 8c c0 e8 84 90 7f e0 48 89 da <c7> 04 25 00 00 00 00 01 00 00 00 44 89 e6 48 c7 c7 78 b3 8c c0 4d
[  464.342849] RSP: 0018:ffffbd9a855dbe28 EFLAGS: 00010282
[  464.342850] RAX: 0000000000000023 RBX: 00007ffcf2fe9588 RCX: 0000000000000006
[  464.342850] RDX: 00007ffcf2fe9588 RSI: 0000000000000096 RDI: ffffa0bb75edc8c0
[  464.342851] RBP: ffffbd9a855dbe50 R08: 00000000000007d1 R09: ffffa0bb7fef1ea4
[  464.342851] R10: 0000000000000000 R11: ffffbd9a855dbc98 R12: 0000000040046402
[  464.342852] R13: ffffa0bb6ac447d0 R14: 0000000040046402 R15: 00007ffcf2fe9588
[  464.342852] FS:  00007f8d62b75740(0000) GS:ffffa0bb75ec0000(0000) knlGS:0000000000000000
[  464.342853] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[  464.342853] CR2: 0000000000000000 CR3: 000000020e756000 CR4: 0000000000740ee0
[  464.342870] PKRU: 55555554
[  464.342871] Call Trace:
[  464.342876]  do_vfs_ioctl+0xa9/0x640
[  464.342877]  ksys_ioctl+0x75/0x80
[  464.342878]  __x64_sys_ioctl+0x1a/0x20
[  464.342880]  do_syscall_64+0x57/0x190
[  464.342884]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
[  464.342885] RIP: 0033:0x7f8d62470317
[  464.342885] Code: b3 66 90 48 8b 05 71 4b 2d 00 64 c7 00 26 00 00 00 48 c7 c0 ff ff ff ff c3 66 2e 0f 1f 84 00 00 00 00 00 b8 10 00 00 00 0f 05 <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d 41 4b 2d 00 f7 d8 64 89 01 48
[  464.342886] RSP: 002b:00007ffcf2fe9578 EFLAGS: 00000202 ORIG_RAX: 0000000000000010
[  464.342887] RAX: ffffffffffffffda RBX: 0000000000000000 RCX: 00007f8d62470317
[  464.342887] RDX: 00007ffcf2fe9588 RSI: 0000000040046402 RDI: 0000000000000003
[  464.342888] RBP: 00007ffcf2fe9640 R08: 0000000000000000 R09: 00007f8d624c82e0
[  464.342888] R10: 0000000000000000 R11: 0000000000000202 R12: 0000556dff6998b0
[  464.342888] R13: 00007ffcf2fe9720 R14: 0000000000000000 R15: 0000000000000000
[  464.342889] Modules linked in: hugo(OE) rfcomm bnep vmw_vsock_vmci_transport vsock snd_ens1371 snd_ac97_codec sch_fq_codel btusb gameport btrtl ac97_bus btbcm snd_pcm btintel vmwgfx snd_seq_midi snd_seq_midi_event snd_rawmidi snd_seq bluetooth snd_seq_device snd_timer crct10dif_pclmul crc32_pclmul ghash_clmulni_intel snd aesni_intel vmw_balloon crypto_simd input_leds cryptd joydev glue_helper soundcore vmw_vmci serio_raw ecdh_generic ecc ttm drm_kms_helper mac_hid drm fb_sys_fops syscopyarea sysfillrect sysimgblt parport_pc ppdev lp parport ip_tables x_tables autofs4 hid_generic usbhid hid mptspi mptscsih ahci mptbase psmouse e1000 libahci i2c_piix4 scsi_transport_spi pata_acpi [last unloaded: hugo]
[  464.342914] CR2: 0000000000000000
[  464.342916] ---[ end trace b04cbeaac073f214 ]---
[  464.342917] RIP: 0010:hugo_ioctl+0x2e/0x160 [hugo]
````
- `kernel NULL pointer dereference, address: 0000000000000000` exception reason
- `hugo_ioctl+0x2e/0x160 [hugo]` this is key point log for this exception
  - `[hugo]` ko name
  - `hugo_ioctl` function name
  - `0x160` exectuable's address

### step 4. use objdump to show executable's address
- display information from object files
  - `$ objdump -dSlr hugo.ko > hugo.disasm`
    - `-d` Display the assembler mnemonics for the machine instructions from objfile
    - `-S` Display source code intermixed with disassembly, if possible
	- `-l` line-numbers
	- `-r` Print the relocation entries of the file
  - $ cat hugo.disasm
````
...
/home/hugo/work/driver/05_file_io/kernel_space_ko/hugo1.c:73
	pr_err("hugo_ioctl() cmd=0x%x arg=0x%lx\n", cmd, arg);
 157:	e8 00 00 00 00       	callq  15c <hugo_ioctl+0x4c>
			158: R_X86_64_PC32	printk-0x4
get_current():
/home/hugo/work/kernel/linux-5.4.174/./arch/x86/include/asm/current.h:15
 15c:	65 48 8b 04 25 00 00 	mov    %gs:0x0,%rax
 163:	00 00 
			161: R_X86_64_32S	current_task
hugo_ioctl():
/home/hugo/work/driver/05_file_io/kernel_space_ko/hugo1.c:74
...
````

### step 5. examine the source code and fix it
````
static long hugo_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct data_ctx *ctx = filp->private_data;
	long ret = 0;
	struct hugo_ioctl_cmd *data = &ctx->ioctl;
	int *p = 0;
	
	pr_err("hugo crash test 1 !!!!!!!!!!!!!!!!!\n");
	*p = 1; //crash here
````
