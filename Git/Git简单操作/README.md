# Git 简单操作

## 在现有目录中初始化Git仓库
```shell
$ git init
```
这会创建一个名为`.git`的子目录

## 克隆现有仓库
```shell
$ git clone [url]
```

## 查看当前文件状态
```shell
$ git status
```

## 跟踪新文件
```shell
$ git add (files)
```

## 忽略文件
让某一类我呢间不被Git自动添加，例如日志文件等
```shell
$ cat .gitignore
```
`.gitignore`文件中匹配模式的规则如下：
+ 空行或者以`#`开始的行会忽略
+ 支持标准的`glob`模式(类似于简化版的正则表达式)
+ 以`/`开头的模式可用于禁用递归匹配
+ 以`/`结尾的模式表示目录
+ 以感叹号开始的模式表示取反

例子：
```
*.a         # 忽略.a类型的文件
!lib.a      # 仍然跟踪lib.a，即使上一行忽略
/TODO       # 只忽略当前目录的TODO文件，而不忽略子目录下的TODO
build/      # 忽略build/目录下的所有文件
doc/*.txt   # 忽略doc/notes.txt，而不忽略doc/server/arch.txt
doc/**/*.pdf    # 忽略doc/目录下所有的.pdf文件
```

## 查看已暂存和为暂存的变更
```shell
$ git diff
```
会显示出还没有进入暂存区的那些变更
```shell
$ git diff -staged
```
显示哪些已缓存的内容会进入下一次提交


## 提交变更
```shell
$ git commit
```

## 跳过暂存区
```shell
$ git commit -a -m '...'
```

## 移除文件
```shell
$ git rm (files)
```
从暂存区中移除
```shell
$ git rm --cached (files)
```
保留文件在硬盘上，但不想让Git对其进行跟踪


## 移动文件
```shell
$ git mv README.md README
```
相当于
```shell
$ mv README.md README
$ git rm README.md
$ git add README
```

## 查看提交历史
```shell
$ git log
```


## 撤销操作
```shell
$ git commit --amend
```

## 撤销已暂存的文件
```shell
$ git reset HEAD (files)
```
把文件移除暂存区

## 撤销对文件的修改
```shell
$ git checkout -- (files)
```

## 显示远程仓库
```shell
$ git remote -v
```

## 添加远程仓库
```shell
$ git remote add (仓库名) (仓库url)
```

## 从远程仓库获取和拉取数据
```shell
$ git fetch [remote-name]
```
只会拉取数据到本地仓库，不会合并

```shell
$ git pull
```

## 将数据推动到远程仓库
```shell
$ git push origin master
```

## 检查远程仓库
```shell
$ git remote show origin
```

## 删除或重命名远程仓库
```shell
$ git remote rename (oldname) (newname)
```

```shell
$ git remote rm (name)
```

## 标记版本
```shell
$ git tag
```