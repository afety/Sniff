//
// Created by maxtang on 17-4-2.
//

#include<pcap.h>
#include<iostream>
#include<stdio.h>

using namespace std;

void process_packet(u_char* arg, const struct pcap_pkthdr* p, const u_char* packet){
    int i, *id = (int *)arg;

    printf("id:%d", ++(*id));
    printf("Packet length:%d", p->len);
    printf("Number bytes:%d", p->caplen);
    printf("Received time:%s", ctime((const time_t*)&p->ts.tv_sec));

    for(i=0; i!=p->len; i++){
        printf("%02x", packet[i]);
        if((i+1)%16 == 0){
            printf("\n");
        }
    }
    printf("\n\n");
}


int main(int argc, char *argv[]){
    char errBuf[PCAP_ERRBUF_SIZE], *devStr;
    devStr = pcap_lookupdev(errBuf);
    if(!devStr){
        printf("Cannot find a internet card!");
        exit(1);
    }

    /*
     * get netaddr and mask
     * */

    bpf_u_int32  netaddr = 0, mask = 0;

    pcap_lookupnet(devStr, &netaddr, &mask, errBuf);

    printf("netaddr:%s\n", netaddr);
    printf("mask:%s\n", mask);


    pcap_t* device = pcap_open_live(devStr, 65535, 1, 0, errBuf);
    if(!device){
        printf("Error: can not open NIC");
        exit(1);
    }


//    struct pcap_pkthdr packet;
    int id = 1;
    int pcap_result = pcap_loop(device, -1, process_packet, (u_char*) &id);

    return 0;
}