# Log
- `$ cat /etc/rsyslog.conf`
````
$IncludeConfig /etc/rsyslog.d/*.conf
````

- `$ vi /etc/rsyslog.d/50-default.conf`
````
auth,authpriv.*                 /var/log/auth.log
*.*;auth,authpriv.none          -/var/log/syslog
#cron.*                         /var/log/cron.log
#daemon.*                       -/var/log/daemon.log
kern.*                          -/var/log/kern.log
#lpr.*                          -/var/log/lpr.log
mail.*                          -/var/log/mail.log
#user.*                         -/var/log/user.log

#mail.info                      -/var/log/mail.info
#mail.warn                      -/var/log/mail.warn
mail.err                        /var/log/mail.err

#
# Emergencies are sent to everybody logged in.
#
*.emerg                         :omusrmsg:*
````

- `$ ls -al /var/log`
````
-rw-r-----   1 syslog            adm              361222 Feb  2 20:37 kern.log
-rw-r-----   1 syslog            adm             3783175 Jan 30 02:06 kern.log.1
-rw-r-----   1 syslog            adm               55361 Feb  2 20:37 syslog
-rw-r-----   1 syslog            adm              400316 Feb  2 04:02 syslog.1
````

# passwd
- `$ cat /etc/passwd`
````
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
...
hugo:x:1000:1000:hugo,,,:/home/hugo:/bin/bash
````

- `$ vi /etc/shadow`
````
root:!:19020:0:99999:7:::
daemon:*:18885:0:99999:7:::
...
hugo:$1$W7vpYImA$Gcpwzp/Jh7qOJup94X6Ag1:19020:0:99999:7:::
````

- `$ vi /etc/group`
````
root:x:0:
daemon:x:1:
bin:x:2:
sys:x:3:
...
hugo:x:1000:
````

# cron
- `$ vi /etc/crontab`
````
# m h dom mon dow user  command
17 *    * * *   root    cd / && run-parts --report /etc/cron.hourly
25 6    * * *   root    test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.daily )
47 6    * * 7   root    test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.weekly )
52 6    1 * *   root    test -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.monthly )
````

