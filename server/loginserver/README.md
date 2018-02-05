客户端请求消息服务器逻辑:
1. 客户端发起TCP连接, 此时BaseSocket::callback为client_callback(), 该回调函数在 BaseSocket::_AcceptNewConnect()函数中被调用.
2. clent_callback函数中,创建一个LoginConn对象并且调用其onConnect方法
3. onConnect方法将重新设置BaseSocket::callback为conn_callback, conn_callback()的功能是根据传入的消息类型处理消息
4. 客户端发送请求消息服务器的pdu. 服务器处理该pdu后发送服务器相关信息给客户端,随后关闭连接

