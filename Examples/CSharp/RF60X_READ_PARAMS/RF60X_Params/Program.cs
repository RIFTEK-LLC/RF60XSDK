// See https://aka.ms/new-console-template for more information
using RF60XSharp;
using RFTYPES;
using System;
namespace RF60X_PARAMS
{
    class Program
    {
        static void Main(string[] args)
        {



            RF60X dev = new RF60X();

            dev.bind_network_address(1);
            var result = dev.open_serial_port("COM3", 9600);

            Console.WriteLine(result);
            uart_hello_rf60x_net_t helloMSg = dev.hello_msg_uart();


            Console.WriteLine("deviceType: " + helloMSg.deviceType);
            Console.WriteLine("deviceModificaton: " + helloMSg.deviceModificaton);
            Console.WriteLine("deviceSerial: " + helloMSg.deviceSerial);
            Console.WriteLine("deviceMaxDistance: " + helloMSg.deviceMaxDistance);
            Console.WriteLine("deviceRange: " + helloMSg.deviceRange);

            if (dev.get_sensor().Item1)
            {
                Console.WriteLine("Sensor value: "+dev.get_sensor().Item2);

                if (dev.get_sensor().Item2==0)
                {
                 Console.WriteLine("Result of parameter change : "+dev.set_sensor(1));
                }
                else
                {
                    Console.WriteLine("Result of parameter change : "+dev.set_sensor(0));
                }
            }
            else
            {
                Console.WriteLine("Error receiving parameter");
            }

            uart_stream_measure_net_t measure=new uart_stream_measure_net_t();
            dev.send_command(RFTYPES.COMMAND_UART.START_STREAM);
            for(int i = 0; i<10; ++i) {
                if(dev.get_measure_uart(ref measure))
                {
                    float value = (measure.value*helloMSg.deviceRange)/16384f;
                    Console.WriteLine("Measure :"+string.Format("{0:F2}", value)+" mm,");
                }
                Console.WriteLine("Measurement not received");

            }

            dev.send_command(RFTYPES.COMMAND_UART.STOP_STREAM);

            Console.WriteLine("IP ADDRESS: "+dev.get_source_ip_address());


            dev.close_serial_port();


        }
    }
}



