#include <iostream>
#include<pcap.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

void printpacket(u_char* arg, const struct pcap_pkthdr *pkthdr, const u_char* packet){
    int *id = (int*) arg;

    printf("id:%d\n", ++(*id));
    printf("Packet length:%d\n", pkthdr->len);
    printf("Number of bytes:%d\n", pkthdr->caplen);
    printf("Rececived time:%s", ctime((const time_t *)&pkthdr->ts.tv_sec));

    int i;
    for (i=0; i != pkthdr->len; i++){
        printf("%02x", packet[i]);
        if((i+1)%16 == 0){
            printf("\n");
        }
    }

    printf("\n\n");
}


int main() {
    char errBuf[PCAP_ERRBUF_SIZE], *devStr;

    /* 获取网络接口名
     * char* pcap_lookupdev(char* errBuf)
     * 该函数用于返回第一个合适的网络接口的字符串指针
     * 若出错，则errBuf存放出错信息字符串
     * errBuf至少是PCAP_ERRBUF_SIZE个字节长度的
     *
     * pcap_lookupdev一般是可以跨平台的，且能够在各个平台上
     * 的网络接口名称不相同的情况下使用
     *
     * 在手动指定要监听的网络接口的情况下，可以省略
     * */
    devStr = pcap_lookupdev(errBuf);


    if(devStr){
        printf("success: device %s\n", devStr);

        /* 打开网络接口
         * pcap_t *pcap_open_live(const char* device, int snaplen, int promisc, int to_ms, char* errbuf)
         * 该函数用于打开网络接口，成功的话会返回一个pcap_t类型的指针，后续的几乎所有操作都需要使用该指针
         * 第一个参数是获取到的网络接口名称，也可以采用硬编码
         *
         * 第二个参数是对于每个网络报，从开头要抓多少个字节，可以设置这个值只抓每个数据包的头部，而不关心
         * 具体的内容。典型的以太网帧的长度是1518字节，但其他的某些协议的数据包会更长一点，但任何一个数据包
         * 长度都必然小于65535字节
         *
         * 第三个参数指定是否打开混杂模式(Promiscuous Mode)，0表示非混杂模式，任何其他值表示混合模式。如果
         * 要打开混杂模式，那么网卡也必须要打开混杂模式，可以使用如下命令打开 ifconfig wlan0 promisc
         *
         * 第四个参数指定需要等待的毫秒数，超过这个数值后，第三部获取数据包的这几个函数就会立即返回。0表示
         * 一直等待直到有数据包的到来
         *
         * 第五个参数用于存放出错信息的数组
         * */

        pcap_t *device = pcap_open_live(devStr, 65535, 1, 0, errBuf);
	int *data_link_types;
	int data_links = pcap_list_datalinks(device, &data_link_types);
	for(int j=0; j!=data_links; j++){
		printf("type:%d\n", data_link_types[j]);
}
	printf("\n\n");
        /* 链路层解析
         * int pcap_datalink(pcap_t* p)
         * 返回数据链路层类型
         *
         * libpcap能够识别超过180种不同的链接类型
         *
         * */

//        printf("DataLink is %d\n", pcap_datalink(device));

        if (!device){
            printf("error: pcap_open_live(): %s\n", errBuf);
            exit(1);
        }

        /* 获取数据包
         * u_char* pcap_next(pcap_t* p, struct pcap_pkthdr *h)
         * 第一个参数为打开的网络接口
         *
         * 第二个参数是保存收到的第一个数据包pcap_pkthdr类型的指针
         *
         * pcap_pkthdr结构如下
         * struct pcap_pkthdr{
         *     struct timeval ts; *时间戳*
         *     bpf_u_int32 caplen; *length of portion present：亦即实际捕获的包长度*
         *     bpf_u_int32 len; *length this packet (off wire)：亦即包应该的实际长度*
         * }
         *
         * 该函数在收到一个数据包后会立即返回
         * */
        //struct pcap_pkthdr packet;
        //const u_char* pktStr = pcap_next(device, &packet);


        /* 网络数据接收函数
         *
         * int pcap_loop(pcap_t* p, int cnt, pcap_handler callback, u_char* user)
         *
         * 第一个参数是网络接口指针
         *
         * 第二个参数是需要抓取的包数量，一旦抓取到cnt个数据包，pcap_loop立即返回
         * 负数的cnt表示pcap_loop永远循环抓包，直到出现错误
         *
         * 第三个参数是一个回调函数指针，其函数形式如下：
         * void callback(u_char *userarg, const struct pcap_pkthdr *pkthdr, const u_char* packet)
         * 第一个参数是pcap_loop的最后一个参数，当收到足够数量的包后pcap_loop会调用callback回调函数
         * 同时将pcap_loop()的user参数传递给它
         *
         * 第二个参数是收到的数据包的pcap_pkthdr类型的指针，pcap_pkthdr结构体含有补货到的数据分组的信息
         * 但是并没有含有该分组数据，故此需要传入u_char* 类型的指针指向分组数据
         *
         * 第三个参数是收到的数据包数据
         *
         *
         * int pcap_dispatch(pcap_t* p, int cnt, pcap_handler callback, u_char* user)
         *
         * 第一个参数是网络接口指针
         *
         * 第二个参数是需要抓取的包数量
         *
         * 第三个参数在超过to_ms毫秒后就会返回(to_ms 为pcap_open_live 的第四个参数)
         * */

        //int id=1;
        //int pcap_result = pcap_loop(device, -1, printpacket, (u_char *) &id);

//        printf("Packet length: %d\n", packet.len);
//        printf("Number of bytes: %d\n", packet.caplen);
//        printf("Recieved time: %s\n", ctime((const time_t *)&packet.ts.tv_sec));


        /* 关闭释放网络接口
         *
         * void pcap_close(pcap_t *p)
         * 该函数用于关闭pcap_open_live()获取的pcap_t的网络接口对象并释放相关资源
         * */
        pcap_close(device);

    }else{
        printf("error: %s\n", errBuf);
    }
    return 0;
}
