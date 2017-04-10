//
// Created by maxtang on 17-4-2.
//

#include<pcap.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
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


int main(){
    char errBuf[PCAP_ERRBUF_SIZE], *devStr;
    devStr = pcap_lookupdev(errBuf);
    devStr = "wlx50fa84099dc8";
	if(!devStr){
        printf("Cannot find a internet card!");
        exit(1);
    }

    /*
     * get netaddr and mask
     * */

    bpf_u_int32  netaddr = 0, mask = 0;

    pcap_lookupnet(devStr, &netaddr, &mask, errBuf);

    printf("netaddr:%d\n", netaddr);
    printf("mask:%d\n", mask);


    pcap_t* device = pcap_open_live(devStr, 65535, 1, 0, errBuf);
    if(!device){
        printf("Error: can not open NIC");
        exit(1);
    }
	int data_link_type = pcap_datalink(device);
    struct pcap_pkthdr packet;
    int seq = 0;
    while(true) {
        const u_char *pktStr = pcap_next(device, &packet);
        seq ++;
        printf("linktype:%d\n", data_link_type);
		printf("Seq:%d\n", seq);
        printf("Packet length:%d\n", packet.len);
        printf("Number of bytes:%d\n", packet.caplen);
        printf("Time:%s\n", ctime((const time_t*)&packet.ts.tv_sec));
  		if(!pktStr){  
	    	printf("did not capture a packet!\n");  
	    	exit(1);  
	  	}  	  
		printf("Receive packet");
		printf("len:%d\n",sizeof(packet)/sizeof(u_char));
        for(int i=0; i!=packet.len; i++){
            printf("%02x", pktStr[i]);
            printf("||");
			if((i+1)%16 == 0){
                printf("\n");
            }
        }
        printf("\n\n");
    }


//    struct pcap_pkthdr packet;
//    int id = 1;
//    int pcap_result = pcap_loop(device, -1, process_packet, (u_char*) &id);

    return 0;
}
