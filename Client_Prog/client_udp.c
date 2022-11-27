/**
 * @file main.c
 * @author Omer Penso
 * @brief This is the main file of client side test application for the 
 * Arm programming RTG course.
 */
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include "files.h"
#include "client_udp.h"

int main(void)
{
        /*************************************** Vars ***************************************************/
        struct sockaddr_in dest; // Holds Destination socket (IP+PORT)
        int socket_fd;           // Holds socket file descriptor
        unsigned int ssize;      // Holds size of dest
        int retVal = 0;          // Holds return Value for recvfrom() / sendto()
        resv_t resv;             // Holds the return value from server
        packet_t packet;         // Holds the values to send to the server
        uint32_t next_test_id;   // ID of the test
        struct timeval start;    // used for calculating the test time
        struct timeval end;      // used for calculating the test time 
        /************************************* Initialization ******************************************/
        socket_fd = socket(AF_INET, SOCK_DGRAM, FLAG_ZERO); // Create socket
        if (socket_fd == ERROR)
        {
                perror("Create socket");
                exit(TRUE);
        } // Validate the socket

        bzero((char *)&dest, sizeof(dest));           // Clearing the struct
        dest.sin_family = (short)AF_INET;             // Setting IPv4
        dest.sin_port = htons(PORT);                  // Setting port
        dest.sin_addr.s_addr = inet_addr(IP_ADDRESS); // Setting IP address
        ssize = sizeof(dest); // Get dest size

        /************************************* Code *****************************************************/
        // get id of the next test
        next_test_id = get_id();
        printf("Welcome to hardware test app for stm32f746zg!\n");
        uint8_t peripheral_code;
       
        while (TRUE)
        {
                print_test_menu();
                
                // assign the test id to the packet
                packet.test_id = next_test_id;
                // user choice of peripheral
                peripheral_code = peripheral_choice();
                
                if ( peripheral_code == EXIT )
                        break;

                // store the peripheral code in the packet
                packet.test_peri = peripheral_code;
                packet.test_iter = get_iteration();
                if(     peripheral_code == CODE_UART || 
                        peripheral_code == CODE_SPI || 
                        peripheral_code == CODE_I2C)
                        {
                                printf("Enter data:\n");
                                scanf("%s", packet.test_bitfield_data);
                                packet.test_bitfield_len = 
                                strlen(packet.test_bitfield_data);
                        }
                else 
                {
                        packet.test_bitfield_len = 0;
                        memset(packet.test_bitfield_data, 0, MAX_BITFIELD_LEN);
                }

                // save the time when sending the packet
                gettimeofday(&start, 0);
                // transmit to stm32f746zg
                retVal = sendto(socket_fd, 
                                // tx_buf,
                                (const packet_t *) &packet, 
                                sizeof(packet), 
                                FLAG_ZERO, 
                                (struct sockaddr *)&dest, 
                                ssize); // Send Ping
                if (retVal < 0)
                {
                        printf("ERROR: Failed to transmit packet.\n");

                        break;
                }

                // receive the answer from stm32f746zg
                retVal = recvfrom(      socket_fd, 
                                        &resv,
                                        sizeof(resv_t), 
                                        FLAG_ZERO, 
                                        (struct sockaddr *)&dest, 
                                        &ssize); // Get answer
                if (retVal < 0)
                {
                        printf("ERROR: Failed to get response.\n");
                        break;
                }

                // get time at the end of the test (when packet returned)
                gettimeofday(&end, 0);
                double time_delta = (double)(end.tv_usec - start.tv_usec) / 
                MILLISECONDS_CONV + (double)(end.tv_sec - start.tv_sec);
                
                // save the test results to file 
                save_test_to_file(resv.test_id, 
                                        resv.test_result, 
                                        time_delta);
                
                // sets the next id to use
                next_test_id++;
                // save the next id to use into the file
                save_id(next_test_id);
                // reset the packet struct for next packet
                memset(&packet, 0, sizeof(packet_t));
                printf("Finished test %"PRId32"\n", resv.test_id);
                sleep(SLEEP_TIME);
                // clears the screen
                system("clear");
        }

        close(socket_fd); // Closing socket
        printf("Closing client...\n");
        return 0;
} // Main()
