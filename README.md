# OpenList
Simple application to whow OpenVPN CLIENT LIST and some operations with them
### How to build
I`s simple
```bash
$ qmake && make
```
### TODO
It`s alfa version.

### Authors
me

### Settings in web server
Create virtual host in OpenVPN tun IP
and in www root create link like this:
```bash
index.html -> /etc/openvpn/openvpn-status.log

```
