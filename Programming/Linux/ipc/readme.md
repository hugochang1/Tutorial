# Linux IPC comparison
- https://jasonblog.github.io/note/linux_system/xi_shuo_linux_ipcff1a_ge_zhong_ipc_xing_shi_bi_jia.html

|method|pros|cons|notes|
|-|-|-|-|
|shared memory|fast|non-synchronized|lifecycle: kernel|
|socket|synchronized, can be used for Internet or IPC||lifecycle: process, tcp: streaming, udp: message|
|pipe|synchronized|only used for fork()|lifecycle: process|
|fifo|synchronized, similar with pipe||lifecycle: process, streaming|
|signal||non-synchronized, can only carry few data|triggered by system|
|message queue|synchronized||lifecycle: process|
