# ZeroMQ
ZeroMQ看起来像一个可嵌入的网络库，作用像一个并发框架。可以实现N对N的套接字连接：
+ 扇出
+ 发布-订阅
+ 任务分配
+ 请求-应答

## REQ - REP
![](https://img-blog.csdnimg.cn/20181215182136391.png)

## PUB - SUB
![](https://img-blog.csdnimg.cn/2018121518225290.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

## PUSH - PULL
并行流水线：
![](https://img-blog.csdnimg.cn/20181215182258794.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

公平排队：
![](https://img-blog.csdnimg.cn/20181215182203773.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlc3Ricm9va2xpdQ==,size_16,color_FFFFFF,t_70)

## 