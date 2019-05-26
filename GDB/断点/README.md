# 总结

## 在匿名空间设置断点
```
(gdb) b Foo::foo
(gdb) b (anonymous namespace)::bar
```

## 在程序地址上打断点
```
(gdb) b *0x400522
```

## 在程序入口处打断点
+ 有调试信息
```
(gdb) start
```
+ 没有调试信息：先通过readelf或者进入gdb，执行info files获得入口地址，然后：
```
(gdb) b *0x400440
(gdb) r
```

## 在文件行号上打断点
```
(gdb) b linenum
(gdb) b filename:linenum
```

## 保存已经设置的断点
在gdb中，可以使用如下命令将设置的断点保存下来：
```
(gdb) save breakpoints file-name-to-save
```
下此调试时，可以使用如下命令批量设置保存的断点：
```
(gdb) source file-name-to-save
```

## 设置临时断点
```
(gdb) tb a.c:15
```

## 设置条件断点
```
(gdb) break … if cond
```

## 忽略断点
`ignore bnum count`：意思是接下来count次编号为bnum的断点触发都不会让程序中断，只有第count + 1次断点触发才会让程序中断

