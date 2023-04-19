# Security-Enhanced Linux
- https://www.youtube.com/watch?v=_WOKRaM-HI4
- SELinux provides more grained access control for
  - Users
  - Files
  - Directories
  - Memory
  - Sockets
  - TCP/UDP ports
  - etc.

- selinux policy
  - /etc/selinux/config
  - /etc/sysconfig/selinux
    - `# cat /etc/selinux/config`
    - SELINUX=enforcing
      - enforcing, permissive, disabled
    - SELINUXTYPE=targeted
      - targeted, minimum, mls (multi-level security)
  - `# /usr/sbin/getenforce`
    - to give you the status of SELinux (enforcing, permissive, disabled)
  - `# /usr/sbin/sestatus`
    - to give you more detail of SELinux status

# How SELinux work
- concept
  - Labeling
    - files, processes, prots, etc. are labeled with an SELinux context
    - files and directories, these labels are stored as extended attributes on the filesystem
    - kernel manages labels for process, port, etc.
    - format
      - user:role:type:level(optional)
  - Type enforcement
- command to check
  - `# ls -lZ /usr/sbin/httpd`
    - Z is to print SELinux context
    - system_u:object_r:httpd_exec_t:s0
      - user: system_u
      - role: object_r
      - type: httpd_exec_t
      - level: s0
  - `# ps axZ`
  - `# netstat -tnlpZ`
  - `# semanage port - l`
- /etc/shadow file
  - shadow_t

# SELinux errors
- booleans
  - on/off settings for SELinux
  - `# getsebool -a`
  - /etc/selinux/targeted/modules/active/booleans.local
- `# journalctl -b - 0`
  -  SELinux is preventing /usr/sbin/httpd from getattr access on the file /home/fred/public_html/index.html
- `# setsebool httpd_enable_homedirs 1 -P`
  - 1 is enable
  - P is permit
- `# chcon -u system_u -r object_r -t httpd_sys_content_t /var/www/html/index.html`
  - `# chcon -t httpd_system_content_t /var/www/html/index.html`
  - `# chcon --reference /var/www/html/ /var/www/html/index.html`
  - `# restorecon -vR /var/www/html/`
- `# setenforce 0`
  - set SELinux to permissive mode
- `# setenforce 1`
  - set SELinux to enforce mode

# Context
- /etc/selinux/targeted/contexts/files/file_contexts
  - to determine what a file or directory's context should be
