# Git分支机制

## 分支机制简介
+ 当使用`git commit`进行提交操作时，Git会先计算每一个子目录的校验和，然后在Git仓库中这些校验和保存为树对象。
随后，Git 便会创建一个提交对象，它除了包含上面提到的那些信息外，还包含指向这个树对象（项目根目录）的指针。
如此一来，Git 就可以在需要的时候重现此次保存的快照。
+ 现在，Git 仓库中有五个对象：三个 blob 对象（保存着文件快照） 、一个树对象（记录着目
录结构和 blob 对象索引） 以及一个提交对象（包含着指向前述树对象的指针和所有提交信息）

![]()

+ 做些修改后再次提交，那么这次产生的提交对象会包含一个指向上次提交对象（父对象）的指针

![]()


## 创建新分支
```shell
$ git branch testing
```
在Git中，`HEAD`是一个指针，指向当前所在的本地分支

## 切换分支
```shell
$ git checkout testing
```
这样`HEAD`就指向testing分支了

由于 Git 的分支实质上仅是包含所指对象校验和（长度为40的SHA-1值字符串）的文件，所以它的创建和销毁都异常高效

## 同时创建和切换
```shell
$ git checkout -b hotfix
```

## 合并分支
```shell
$ git merge hotfix
```

## 合并分支的冲突处理
如果你在两个不同的分支中，对同一个文件的同一个部分进行了不同的修改，Git 就没法干净的合并它们

出现冲突的文件会包含一些特殊区段，看起来像下面这个样子：
```
<<<<<<< HEAD:index.html
<div id="footer">contact : email.support@github.com</div>
=======
<div id="footer">
please contact us at support@github.com
</div>
>>>>>>> iss53:index.html
```

这表示 HEAD 所指示的版本（ 也就是你的 master 分支所在的位置，因为你在运行 merge 命令的时候已经检出到了这个分支） 在这个区段的上半部分（======= 的上半部分） ，而iss53 分支所指示的版本在 ======= 的下半部分。

为了解决冲突，你必须选择使用由======= 分割的两部分中的一个，或者你也可以自行合并这些内容。 例如，你可以通过把这段内容换成下面的样子来解决冲突：
```
<div id="footer">
please contact us at email.support@github.com
</div>
```
上述的冲突解决方案仅保留了其中一个分支的修改，并且 <<<<<<< , ======= , 和 >>>>>>>这些行被完全删除了。 在你解决了所有文件里的冲突之后，对每个文件使用 git add 命令来将其标记为冲突已解决


## 删除分支
```shell
$ git branch -d testing
```

## 分支管理
git branch 命令不只是可以创建与删除分支。 如果不加任何参数运行它，会得到当前所有
分支的一个列表：
```shell
$ git branch
iss53
* master
testing
```
注意 master 分支前的 * 字符：它代表现在检出的那一个分支（ 也就是说，当前 HEAD 指针所指向的分支）

如果需要查看每一个分支的最后一次提交，可以运行 git branch -v 命令：
```shell
$ git branch -v
iss53 93b412c fix javascript issue
* master 7a98805 Merge branch 'iss53'
testing 782fd34 add scott to the author list in the readmes
```

如果要查看哪些分支已经合并到当前分支，可以运行 git branch --merged
```shell
$ git branch --merged
iss53
* master
```

查看所有包含未合并工作的分支，可以运行 git branch --no-merged
```shell
$ git branch --no-merged
testing
```