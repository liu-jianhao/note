# 总结

## 让catchpoint只触发一次
`tcatch` + event，该事件发生时停止

## 为fork调用设置catchpoint
catch fork

## 为系统调用设置catchpoint
catch syscall


## 通过为ptrace调用设置catchpoint破解anti-debugging的程序
有些程序不想被gdb调试，它们就会在程序中调用“ptrace”函数，一旦返回失败，就证明程序正在被gdb等类似的程序追踪，所以就直接退出

破解这类程序的办法就是为ptrace调用设置catchpoint，通过修改ptrace的返回值，达到目的
