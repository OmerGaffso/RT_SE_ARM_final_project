#include "tools.h"
#include "client_udp.h"

void print_main_menu()
{
   printf("Choose a testing method:\n");
   printf("1.Automated tests\n");
   printf("2.Manual tests\n");
   printf("0.Exit\n");
}

void print_test_menu()
{
   printf("Choose a peripheral to test:\n");
   printf("1.TIMER\n");
   printf("2.UART\n");
   printf("3.SPI\n");
   printf("4.I2C\n");
   printf("5.ADC\n");
   printf("0.Exit\n");
}

bool manual_test(packet_t * packet, uint32_t next_test_id)
{
   uint8_t peripheral_code;
   char buff[MAX_BITFIELD_LEN]; // buff for user data input
   memset(buff, 0, MAX_BITFIELD_LEN); // fill buff with '\0'

   print_test_menu();
   // get the peripheral choice of the user
   peripheral_code = peripheral_choice();

   if (peripheral_code == EXIT)
      return false;

   packet->test_id = next_test_id; // assign the test id to the packet
   packet->test_peri = peripheral_code;//store the peripheral code in the packet
   packet->test_iter = get_iteration();      // get the number of iterations
   
   // the peripheria choosen is communication protocol
   if(peripheral_code == CODE_UART || peripheral_code == CODE_SPI || 
      peripheral_code == CODE_I2C)
      {
         printf("Enter data: (ENTER TO END)\n");
         get_bitfield_data(buff); // get bitfield data from user
         
         packet->test_bitfield_len = strlen(buff);
         strncpy(packet->test_bitfield_data, buff, 
                  packet->test_bitfield_len);
      }
   else 
   {
      // set the bitfield length and data to 0 for ADC or Timer tests
      packet->test_bitfield_len = 0;
      memset(packet->test_bitfield_data, 0, MAX_BITFIELD_LEN);
   }
   return true;
}

bool automated_test(packet_t * packet, uint32_t next_test_id)
{
   uint8_t peripheral_code;
   // default string for communications test
   char default_data[DEFAULT_DATA_LEN] = "abcdefghijklmnopqrstuvwxyz";
   print_test_menu();
   peripheral_code = peripheral_choice();

   if (peripheral_code == EXIT)
      return false;

   packet->test_id = next_test_id;
   packet->test_peri = peripheral_code;
   packet->test_iter = DEFAULT_ITERATIONS; // get the number of iterations

   // the peripheria choosen is communication protocol
   if(peripheral_code == CODE_UART || peripheral_code == CODE_SPI || 
      peripheral_code == CODE_I2C)
   {
         // set the bitfield length
         packet->test_bitfield_len = DEFAULT_DATA_LEN;    
         // set the bitdield data
         strncpy( packet->test_bitfield_data, 
                  default_data, 
                  packet->test_bitfield_len);
        
   }
   else 
   {
      // set the bitfield length and data to 0 for ADC or Timer tests
      packet->test_bitfield_len = 0;
      memset(packet->test_bitfield_data, 0, MAX_BITFIELD_LEN);
   }
   return true;
}



