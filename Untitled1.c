#include <stdio.h>

// Global variables
int timer = 0, wait_for_ack = -1, frameQ = 0, cansend = 1, t = 0;

void sender(int i, int* frame);
void recv(int i);

int main() {
    int i, j, frame[5];  // Array to hold frames
    // Input for frame data (assuming it's integers for simplicity)
    printf("Enter the time when data frame will be ready (5 times):\n");
    for (j = 0; j < 3; j++) {
        printf("Frame %d ready at time: ", j + 1);
        scanf("%d", &frame[j]);  // Input frame times
    }

    // Simulate the sending and receiving process
    for (i = 0; i < 10; i++) {
        sender(i, frame);  // Call sender to simulate sending a frame
        recv(i);            // Call recv to simulate receiving a frame
    }

    return 0;
}

// Sender function: Simulates sending a frame
void sender(int i, int* frame) {
    wait_for_ack++;

    // Acknowledge frame after a certain number of time units
    if (wait_for_ack == 3) {
        printf("Acknowledging frame at time = %d\n", i);
        wait_for_ack = 0;  // Reset wait_for_ack after acknowledgment
    }

    // If frame is ready to send
    if (i == frame[t]) {
        frameQ++;  // Increment frame queue (indicating a frame is ready to send)
        t++;       // Move to the next frame
    }

    if (frameQ == 0) {
        printf("NO FRAME TO SEND at time=%d\n", i);
    }

    if (frameQ > 0 && cansend == 1) {
        printf("FRAME SEND AT TIME=%d\n", i);
        cansend = -1;  // Block sending further frames
        frameQ--;      // Decrease frame queue
        timer++;       // Start a timer
        printf("timer in sender=%d\n", timer);
    }

    if (frameQ > 0 && cansend == -1) {
        printf("FRAME IN Q FOR TRANSMISSION AT TIME=%d\n", i);
    }

    printf("frameQ=%d\n", frameQ);
    printf("i=%d, t=%d\n", i, t);
    if (t > 0) {
        printf("Frame[%d] value: %d\n", t-1, frame[t-1]);
    }
}

// Receiver function: Simulates receiving a frame and handling acknowledgment
void recv(int i) {
    printf("timer in receiver=%d\n", timer);

    // Timer simulation (for acknowledgment)
    if (timer > 0) {
        timer++;
    }

    if (timer == 3) {
        printf("FRAME ARRIVED AT TIME=%d\n", i);
        wait_for_ack = 0;  // Reset the wait for acknowledgment counter
        timer = 0;         // Reset the timer
    } else {
        printf("WAITING FOR FRAME AT TIME %d\n", i);
    }
}

