SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\Git\cmd;C:\MinGW\bin;C:\Users\umred\AppData\Local\Microsoft\WindowsApps;C:\Users\umred\AppData\Local\Programs\Microsoft VS Code\bin
SET CPU_TYPE=LPC2129
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\startup._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\door34.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\project_lockDoor3.lnp"
"C:\Keil\ARM\ARMCC\bin\fromelf.exe" ".\project_lockDoor3.axf" --i32combined --output ".\project_lockDoor3.hex"
