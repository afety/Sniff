### Notice

1. 在进行网络协议分析时候，需要使用ntohs()函数将大端序的网络数据转换为小端序数据
    > 常用的网络协议如下：
    > > * Internet Protocol Version 4(IPv4) 0x0800
    > > * Internet Protocol Version 6(IPv6) 0x86DD
    > > * Address Resolution Protocol(ARP): 0x0806
    > > * Reverse Address Resolution Protocol(RARP): 0x8035
    > > * AppleTalk over Ethernet(EtherTalk): 0x809B
    > > * Point-to-Point Protocol(PPP): 0x880B
    > > * PPPoE Discovery Stage : 0x8863
    > > * PPPoE Session Stage : 0x8864
    > > * Simple Network Management Protocol(SNMP) : 0x814C
2. 在了解索捕获包的网络层协议后，下一步则是解析其传输层协议
    >常用的传输层协议有：
    > > * Internet Control Message Protocol(ICMP): 0x01 RFC 792
    > > * Internet Group Management Protocol(IGMP): 0X02 RFC 3376
    > > * Transmission Control Protocol(TCP): 0x06 RFC 793
    > > * Exterior Gateway Protocol : 0x08 RFC 888
    > > * User Datagram Protocol(UDP): 0x11 RFC 768
    > > * IP v6 Routing Header : 0x2B RFC 1883
    > > * IP v6 Fragment Header : 0x2C RFC 1883
    > > * ICMP for IPv6 : 0x3A RFC 1883
3. Sniff抓取到的数据包一般而言是Malformed的，因为在网络上面传输的数据并不总是有效的
    一些包由于标准或者其他问题的干扰而不会被传输。事实上，如果在数据包中以太网类型
    字段标注为ARP数据，也并不意味这我们能够确实的找到一个ARP头部，很多情况下我们并
    不能相信IP数据包的协议域存在这标准所定义的头部字段。如果想要设计一个强大的能够
    避免分段错误和其他让人头疼的包分析工具，我们需要考虑所有的细节部分。
    > 技巧：
    > > * 检查接收到的数据包的总长度，譬如如果想要获取的包是以太网络中的ARP数据包，
           如果包长度不是14+28=42字节，则丢弃。（存在疑问，以太网全帧长度为16字节！！）
    > > * 检查IP检验和与TCP检验和，但是检验和有效并不能担保数据报含有有效的头信息
    > > * 所有由数据报中抓取的供与后续使用的数据都应该是有效的
    