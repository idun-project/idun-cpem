#ifndef HOST_H
#define HOST_H

#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

const char *NMIPORT = "/tmp/idunmm-nmi";

static uint8 COPY_FCB_6502[43] = {
  0x1a, 0x80, 0x1a, 0x80, 0xc3, 0xc2, 0xcd, 0x31, 0x30, 0xa0, 0xa0, 0xa0,
  0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
  0xa0, 0xa0, 0xa2, 0x10, 0xbd, 0x09, 0x80, 0x9d, 0x00, 0x0b, 0xca, 0x10,
  0xf7, 0xa9, 0x40, 0x8d, 0x36, 0x0f, 0x60
};
#define FILENAME_OFFSET 0x09

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
    // First send 2-byte header which is the message size
    uint16 hdr = htobe16(43);
    if (sendto(sockfd, &hdr, 2, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("nmi sendto");
        close(sockfd);
        return -1;
    } else {
        // Then send body of the message
        sendto(sockfd, COPY_FCB_6502, sizeof(COPY_FCB_6502), 0, 
               (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
    }

    // Close the socket
    close(sockfd);
    return 0;
}

char asc2pet(char a) {
    if (a>0x40 && a<=0x5a)
        return a+0x80;
    else if (a>0x60 && a<=0x7a)
        return a-0x20;
    else
        return a;
}

void to_pet(char *dest, const char* src, uint16 max) {
    while (*src && max--) {
        *dest = asc2pet(*src);
        src++;
        dest++;
    }
    *dest = '\0';
}

uint8 hostbdos(uint16 fcb) {
	CPM_FCB* F = (CPM_FCB*)_RamSysAddr(fcb);

	if (!_SelectDisk(F->dr)) {
		_FCBtoHostname(fcb, &filename[0]);
		if (!filename[4])
            return(0xff);
        to_pet((char *)&COPY_FCB_6502[FILENAME_OFFSET], (const char *)filename, 17);
        return nmi();
    }
    return(0xff);
}

#endif