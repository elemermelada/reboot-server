# Reboot Server
### Small Windows TCP/IP server that triggers a system reboot upon receiving the right message
![C++](https://img.shields.io/badge/-C++-blue?logo=cplusplus)
## Instructions
 1. Launch the executable
 1. Grant network permissions
 1. Program binds to port 1234
 1. Upon receiving a TCP message starting with "r", the `WX_REBOOT` signal is sent to the system

> The TCP message can be sent using tools like `telnet` (Windows) or `netcat` (Unix).

> This program is meant to be launched as a service when Windows starts. This way, in the event of an unexpected system error preventing remote access (RDP) to the machine, the reboot signal can still be sent and the system can recover.
