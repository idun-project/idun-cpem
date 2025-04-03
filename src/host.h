#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

const char *NMIPORT = "/tmp/idunmm-nmi";

static uint8 COPY_FCB_6502[45] = {0x2b,0x00,
  0x1a, 0x80, 0x1a, 0x80, 0xc3, 0xc2, 0xcd, 0x31, 0x30, 0xa0, 0xa0, 0xa0,
  0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
  0xa0, 0xa0, 0xa2, 0x10, 0xbd, 0x09, 0x80, 0x8d, 0x00, 0x0b, 0xca, 0x10,
  0xf7, 0xa9, 0x80, 0x8d, 0x36, 0x0f, 0x60
};
#define FILENAME_OFFSET 0x0b

uint8 nmi() {
    int sockfd;
    struct sockaddr_un addr;
    
    // Create the socket
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("nmi socket");
        return -1;
    }

    // Clear and set up the address structure
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, NMIPORT, sizeof(addr.sun_path) - 1);

    // Send the message to the socket
    if (sendto(sockfd, COPY_FCB_6502, sizeof(COPY_FCB_6502), 0, 
               (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("nmi sendto");
        close(sockfd);
        return -1;
    }

    // Close the socket
    close(sockfd);
    return 0;
}

uint8 hostbdos(uint16 fcb) {
	CPM_FCB* F = (CPM_FCB*)_RamSysAddr(fcb);

	if (!_SelectDisk(F->dr)) {
		_FCBtoHostname(fcb, &filename[0]);
		if (!filename[4])
            return(0xff);
        strncpy((char *)&COPY_FCB_6502[FILENAME_OFFSET], (const char *)filename, 17);
        return nmi();
    }
    return(0xff);
}

#endif