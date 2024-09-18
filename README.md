# Reboot Server
Small windows TCP/IP server that triggers a system reboot upon receiving the right message.
---
This program is meant to be launched as a service when Windows starts. This way, in the event of an unexpected system error preventing remote access (RDP) to the machine, the reboot signal can still be sent and the system can recover.
