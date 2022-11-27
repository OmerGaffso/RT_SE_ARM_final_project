
#ifndef RTG_ARM_PROJECT_UDP
#define RTG_ARM_PROJECT_UDP

// The port the of the server UDP communication
#define MY_PORT 55555U

/*
	The max packet size is 263 = 4 byte for id, 1 byte for peripheral choice,
	1 byte for iteration, 1 byte for bitfield length, 256 bytes (maximum) for
	bitfield.
*/
#define MAX_PACKET_SIZE 263U

//We reply to the client 4 bytes for ID and 1 byte for test result - 5 bytes
//total
#define REPLY_BUFF_LEN 		5U
#define TEST_RESULT_INDEX	4U	// The index of the result in the return buff

void udpServer_init();


#endif
