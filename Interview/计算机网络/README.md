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
