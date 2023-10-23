#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_SIZE 4
#define MAX_SEQUENCE_NUM 7
#define TIMEOUT 3

// Function to simulate network conditions (randomly drop packets)
bool isPacketLost() {
    return rand() % 10 < 3;  // Simulating a 30% packet loss rate
}

// Function to send data packets
void sendPacket(int packet) {
    if (!isPacketLost()) {
        printf("Sent packet: %d\n", packet);
    } else {
        printf("Packet %d lost during transmission\n", packet);
    }
}

int main() {
    srand(time(NULL));
    int senderSeqNum = 0;
    int lastAckReceived = -1;
    int sendWindow[WINDOW_SIZE];
    int ackReceived[MAX_SEQUENCE_NUM + 1];

    for (int i = 0; i < WINDOW_SIZE; i++) {
        sendWindow[i] = -1;  // Initialize the send window
    }

    while (true) {
        for (int i = 0; i < WINDOW_SIZE; i++) {
            if (sendWindow[i] == -1 && senderSeqNum <= MAX_SEQUENCE_NUM) {
                sendPacket(senderSeqNum);
                sendWindow[i] = senderSeqNum;
                senderSeqNum = (senderSeqNum + 1) % (MAX_SEQUENCE_NUM + 1);
            }
        }

        if (isPacketLost()) {
            printf("Ack lost.\n");
        } else {
            int receivedAck;
            printf("Enter the last received ACK: ");
            scanf("%d", &receivedAck);

            if (ackReceived[receivedAck] == 0) {
                printf("Duplicate ACK received: %d\n", receivedAck);
            } else if (receivedAck >= sendWindow[0]) {
                printf("Received ACK: %d\n", receivedAck);
                ackReceived[receivedAck] = 1;
                for (int i = 0; i < WINDOW_SIZE; i++) {
                    if (sendWindow[i] == receivedAck) {
                        sendWindow[i] = -1;
                    }
                }
            }
        }
    }

    return 0;
}
