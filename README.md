hix-password
------------

This tool allows you to enter the debug mode (root shell) of a common series of
DSLAMs. Note that this does *not* allow you to bypass the usual authentication
process.

There is a short delay between logging in and before the prompt appears. In
this interval, press the '@' key and return, you should then see something like
this:

```
MAC-address is: DE:AD:BE:EF:12:34
enter password for debug access:
```

To get the password, run

```
$ ./hix-password DE:AD:BE:EF:12:34
MAC: de:ad:be:ef:12:34
Password: 3Xa64ijyyj
```

And use the generated password to enter the debug mode. Enjoy breaking your
DSLAM!
