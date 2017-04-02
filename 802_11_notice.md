### libpcap 抓取 802.11 数据帧格式
int pcap_datalink(pcap_t* p)

LinkType_Name               LinkType_Value             Corresponding DLT_ name

LINKTYPE_IEEE802_11                 105                       DLT_IEEE802_11
LINKTYPE_IEEE802_11_PRISM           119                       DLT_PRISM_HEADER
LINKTYPE_IEEE802_11_RADIOTAP        127                       DLT_IEEE802_11_RADIO
LINKTYPE_IEEE802_11_AVS             163                       DLT_IEEE802_11_RADIO_AVS

1. 105:linktype_ieee802_11
    > 

2. 119:linktype_ieee802_11_prism
    > 帧结构：
    >
    > MsgCode: 4 Octets<br/>
    > Msglen: 4 Octets <br/> 
    > Device Name: 16 Octets<br/>
    > DID: 4 Octets<br/>
    > Status: 2 Octets<br/>
    > Length: 2 Octets<br/>
    > Data: n Octets<br/>
    > Pyload<br/>
    > MsgCode可能的取值为0x00000041或者是0x000044<br/>
    > Msglen是Prism的首部长度，事实上，这个值几乎是固定的144字节
    > Device Name是适配器的接口名
    > 在理论上，{DID, Status, Length, Data}组成一个四元组的形式出现，在一个Prism头
    > 中，一般会出现十个左右该四元组，每一个四元组代表了一个参数的值，DID用于表征这个参数是什么<br/>
    > * 对于Msgcode=0x00000041的Prism帧，DID的值域为：
    > > 0x00001041 - host time<br/>
        0x00002041 - MAC time<br/>
        0x00003041 - channel<br/>
        0x00004041 - RSSI<br/>
        0x00005041 - signal quality<br/>
        0x00006041 - signal<br/>
        0x00007041 - noise<br/>
        0x00008041 - rate<br/>
        0x00009041 - transmitted frame indicator<br/>
        0x0000A041 - frame length<br/>
    > * 对于Msgcode=0x00000044的Prism帧，DID的值域为：
    > > 0x00010044 - host time<br/>
        0x00020044 - MAC time<br/>
        0x00030044 - channel<br/>
        0x00040044 - RSSI<br/>
        0x00050044 - signal quality<br/>
        0x00060044 - signal<br/>
        0x00070044 - noise<br/>
        0x00080044 - rate<br/>
        0x00090044 - transmitted frame indicator<br/>
        0x000A0044 - frame length<br/>
    > 当该参数值被提供时候，Status设为0否则为1，Length字段的值则是
    > 后续Data段的大小，理论上Data可以为任意值，但是一般为4字节大小。
    > Data段包含有该字段的值
   
### 值得注意的事，对于不同的网络适配器，上述值也会不同，因为并没有一个
### 针对Prism的官方声明

3. linktype_ieee802_11_radiotap:radiotap是目前ieee802.11事实上的标准，
相对于传统的Prism头和AVS头部，灵活性更强

4. linktype_ieee802_11_AVS:传统的802.11帧头的一种
    > [详细信息](http://web.archive.org/web/20040803232023/http://www.shaftnet.org/~pizza/software/capturefrm.txt)