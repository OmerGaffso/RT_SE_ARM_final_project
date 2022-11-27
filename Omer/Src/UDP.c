

#include "RTG.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "UDP.h"
#include "stdio.h"


/* IMPLEMENTATION FOR UDP Server :   source:https://www.geeksforgeeks.org/udp-server-client-implementation-c/

1. Create UDP socket.
2. Bind the socket to server address.
3. Wait until datagram packet arrives from client.
4. Process the datagram packet and send a reply to client.
5. Go back to Step 3.
*/
void udp_receive_callback(	void *arg,
							struct udp_pcb *upcb,
							struct pbuf *p,
							const ip_addr_t *addr,
							u16_t port);

void udpServer_init()
{
	// UDP Control Block structure
   struct udp_pcb *upcb;
   err_t err;

   /* 1. Create a new UDP control block  */
   upcb = udp_new();

   /* 2. Bind the upcb to the local port */
   ip_addr_t myIPADDR;
   IP_ADDR4(&myIPADDR, 192, 168, 1, 10);

   err = udp_bind(upcb, &myIPADDR, MY_PORT);  // 55555 is the server UDP port


   /* 3. Set a receive callback for the upcb */
   if(err == ERR_OK)
   {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else
   {
	   udp_remove(upcb);
   }
}

// udp_receive_callback will be called, when the client sends some data to the server
/* 4. Process the datagram packet and send a reply to client. */



void udp_receive_callback(
		void *arg,
		struct udp_pcb *upcb,
		struct pbuf *p,
		const ip_addr_t *addr,
		u16_t port)
{
	/// empty packet received
	if (p->len == 0 || p->payload == NULL)
		return;

//	*client_ip_addr = *addr;	//saving the client ip address for
	struct pbuf *txBuf;			//the packet we construct to return to client
	char buf[REPLY_BUFF_LEN];	//the buffer that contains the data to return
	uint8_t test_result;
	/* struct to store the packet data based on test fields */
	packet_t rec_packet;
	/* pointer for coping the data from the received packet into the packet
	struct */

	char *payload_data;
	payload_data = p->payload;

	memcpy(&rec_packet.test_id, payload_data, ID_LEN);
	payload_data += ID_LEN;
	memcpy(&rec_packet.test_per, payload_data++, CONTROL_FIELD_LEN);
	memcpy(&rec_packet.test_iter,payload_data++, CONTROL_FIELD_LEN);
	memcpy(&rec_packet.test_bitfield_len,payload_data++, CONTROL_FIELD_LEN);
	memcpy(&rec_packet.test_bitfield_data, payload_data, DATA_SIZE);

	free(p);

    /* send the packet_t var to the tests fucntion */
	test_result = send_to_test(&rec_packet);
    /* copy id to the first 4 bytes in the result buf */
	memcpy(buf, rec_packet.test_id, ID_LEN);
	/* store the test result at the last index of the result buf */
	buf[TEST_RESULT_INDEX] = (char) test_result;

	/* allocate pbuf from RAM*/
	txBuf = pbuf_alloc(PBUF_TRANSPORT,REPLY_BUFF_LEN, PBUF_RAM);

	/* copy the data into the buffer  */
	pbuf_take(txBuf, buf, REPLY_BUFF_LEN);

	/* Connect to the remote client */
	udp_connect(upcb, addr, port);

	/* Send a Reply to the Client */
	udp_send(upcb, txBuf);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p_tx buffer */
	pbuf_free(txBuf);

	/* Free the p buffer */
	pbuf_free(p);
}

