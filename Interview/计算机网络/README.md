# 腾讯OMG团队(实习)
## 1. 画出tcp头部的协议格式
![](https://github.com/liu-jianhao/note/blob/master/Interview/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/TCP%E9%A6%96%E9%83%A8.png)

## 2. HTTP的报文头部
### 请求报文：它会向Web服务器请求一个动作
请求报文的格式：
+ 起始行：  `<method> <request-URL> <version>`
+ 头部：    `<headers>`
+ 主体：    `<entity-body>`

 
### 响应报文：它会将请求的结果返回给客户端。
响应报文的格式：
+ 起始行：  `<version> <status> <reason-phrase>`
+ 头部：    `<headers>`
+ 主体：    `<entity-body>`

## 从浏览器输入网址到显示页面的过程？
1. 浏览器向DNS服务器查询URL对应的IP地址
2. DNS返回IP地址
3. 浏览器打开TCP连接(默认为80)，并向Web服务器发送HTTP请求
4. 若页面发生跳转，服务器则以一个重定向响应，然后转到5，否则直接转到6
5. 浏览器跟随重定向，再次发送HTTP请求
6. 浏览器处理请求， 并发回HTML响应
7. 浏览器接受请求的页面源码
8. 浏览器开始渲染HTML
9. 浏览器发送嵌入到HTML中的对象请求
10. 浏览器进一步发送异步(Ajax)请求
11. 浏览器关闭TCP连接


## TIME_WAIT
完成主动关闭后，TCP结点接收到了FIN报文。这表示对端执行了一个被动关闭。
此时这个TCP结点将在TIME_WAIT状态中等待一段固定时间
+ 确保TCP连接可靠地终止
+ 为了确保任何老的报文在重新建立同样的连接之前在网络中超时消失

### SO_REUSEADDR套接字选项
避免TCP服务重启，尝试将套接字绑定到当前已经同TCP结点相关联的端口上时出现的EADDRINUSE错误

## CLOSE_WAIT
TCP结点从对端收到FIN报文后将处于CLOSE_WAIT状态


## 什么是CDN(内容分发网络)?
