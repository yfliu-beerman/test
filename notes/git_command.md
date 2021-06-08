//好像有个叫markdown toc的东西，到时候看看

#创建版本库
git init
git add
git status
* 对于不同的，需要rm和add修改状态后才能commit，似乎中间存在一个缓冲层

git commit -m
* 它能发现一个文件被移到另一个文件夹

## 一个上传的流程
修改文件到合适 - git add - git status/git diff - git commit

## 时光穿梭

git log 参数很多需要一个表

>commit ccf4a3f644e68802e312f75e9d72f63bebc0db64 (HEAD -> master)
Author: yfliu <625074401@qq.com>
Date:   Mon May 31 11:03:10 2021 +0800
    first version

git reset --hard HEAD^ （大小写 hard

* 此时log不会显示后面的，一种办法是使用

git reflog 查看id

> ccf4a3f (HEAD -> master) HEAD@{0}: reset: moving to HEAD^
326a838 HEAD@{1}: commit: test command
ccf4a3f (HEAD -> master) HEAD@{2}: commit (initial): first version

## 工作区，暂存区概念

工作区就是当前目录，暂存区的概念重要
它相当于一个老旧的版本镜像，并不会跟踪记录你的所有变化，你的add，rm相当于操纵这个暂存区，当它与当前工作区一致，可以commit在当前分支形成新的一个节点，同时master是第一个分支的名字，head是指针名