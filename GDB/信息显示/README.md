# 信息显示

## 显示gdb版本信息
```
(gdb) show version
```

## 显示gdb版权相关信息
```
(gdb) show copying
```

## 启动时不显示提示信息
```
$ gdb -q
(gdb)
```

## gdb退出时不显示提示信息
```
(gdb) set confirm off
```

## 输出信息多时不会暂停输出
```
有时当gdb输出信息较多时，gdb会暂停输出，并会打印
“---Type <return> to continue, or q <return> to quit---”
这样的提示信息解决办法是使用“set pagination off”或者“set height 0”命令。
这样gdb就会全部输出，中间不会暂停。
```