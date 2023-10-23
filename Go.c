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
    int expectedSeqNum = 0;
    int senderSeqNum = 0;
    int lastAckReceived = -1;

    while (true) {
        if (senderSeqNum < expectedSeqNum + WINDOW_SIZE) {
            sendPacket(senderSeqNum);
            senderSeqNum = (senderSeqNum + 1) % (MAX_SEQUENCE_NUM + 1);
        }

        if (isPacketLost()) {
            printf("Ack lost.\n");
        } else {
            int receivedAck;
            printf("Enter the last received ACK: ");
            scanf("%d", &receivedAck);

            if (receivedAck == lastAckReceived) {
                printf("Duplicate ACK received: %d\n", receivedAck);
            } else if (receivedAck >= expectedSeqNum) {
                printf("Received ACK: %d\n", receivedAck);
                expectedSeqNum = receivedAck + 1;
                lastAckReceived = receivedAck;
            }
        }
    }

    return 0;
}
