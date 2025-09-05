unit RF60X_UART_Measure_main;

interface

uses
  System.SysUtils,
  RF60X_Delphi in '..\..\wrapper\RF60X_Delphi\RF60X_Delphi.pas';

type
  TExampleApp = class
  public
    class procedure Run;
  end;

const
  // TODO: Please change this to the actual COM port name on your system.
  DEFAULT_COM_PORT = 'COM3';

implementation

class procedure TExampleApp.Run;
var
  RF60XDevice: TRF60X;
  SensorValue: byte;
  CurrentSourceIP: string;
  IsConnected: boolean;
  Success: boolean;
  MeasureProtocol: TStreamMeasure;
  i: integer;
  HelloPacket: TC_UartHello;
begin
  Writeln('RF60X SDK Example for Delphi');
  Writeln('----------------------------');
  Writeln('SDK Version: ', TRF60X.SdkVersion);
  Writeln('');

  RF60XDevice := nil;
  try
    // 1. Create an instance of the device
    Writeln('Step 1: Creating device...');
    RF60XDevice := TRF60X.Create;
    Writeln('Device created successfully.');
    Writeln('');

    // 2. Attempt to connect to a serial port
    Writeln('Step 2: Connecting to serial port (', DEFAULT_COM_PORT, ')...');
    IsConnected := RF60XDevice.OpenSerialPort(DEFAULT_COM_PORT, 9600);

    if IsConnected then
    begin
      Writeln('Successfully connected to ', DEFAULT_COM_PORT, '.');
      Writeln('');

      // 3. Get a "hello" packet
      Writeln('Step 3: Getting a packet (hello)...');
      HelloPacket := RF60XDevice.GetHelloMsgUart();
      if HelloPacket.DeviceSerial <> 0 then
      begin
        Writeln('> Serial number: ', HelloPacket.DeviceSerial);
        Writeln('> Range of devices: ', HelloPacket.DeviceRange);
      end
      else
        Writeln('> Failed to get hello packet.');
      Writeln('');

      // 4. Get a parameter from the device
      Writeln('Step 4: Getting a parameter (Sensor laser power)...');
      Success := RF60XDevice.GetSensor(SensorValue);
      if Success then
        Writeln('> Current sensor laser power value: ', SensorValue)
      else
        Writeln('> Failed to get sensor value.');
      Writeln('');

      // 5. Set a parameter on the device
      Writeln('Step 5: Setting a parameter (Sensor laser power to 5)...');
      Success := RF60XDevice.SetSensor(5);
      if Success then
      begin
        Writeln('> Successfully set sensor value.');
        // Verify the change
        if RF60XDevice.GetSensor(SensorValue) then
          Writeln('> New sensor laser power value: ', SensorValue)
        else
          Writeln('> Could not verify the new sensor value.');
      end
      else
        Writeln('> Failed to set sensor value.');
      Writeln('');

      // 6. Get a string parameter
      Writeln('Step 6: Getting a string parameter (Source IP)...');
      Success := RF60XDevice.GetSourceIP(CurrentSourceIP);
      if Success then
        Writeln('> Current Source IP: ', CurrentSourceIP)
      else
        Writeln('> Failed to get Source IP.');
      Writeln('');

      // 7. Get a measurement
      Writeln('Step 7: Get a measurement...');
      Success := RF60XDevice.SendCommand(TC_COMMAND_UART.c_StartStream);
      if Success = False then
      begin
        Writeln('> An error occurred: Failed to send command to start stream');
      end
      else
      begin

        for i := 1 to 5 do
        begin
          Success := RF60XDevice.GetMeasureUart(MeasureProtocol,
            TC_PROTOCOL_MEASURE_UART.c_UartStreamMeasureT);
          if Success then
          begin
            Writeln('> Raw value of the measurement: ' + IntToStr(MeasureProtocol.Value) +
              #10 + '> Converted measurement: ' + FloatToStrF(
              (MeasureProtocol.Value * HelloPacket.DeviceRange) / 16384, ffFixed, 0, 3));
          end;
        end;

      end;
      Success := RF60XDevice.SendCommand(TC_COMMAND_UART.c_StopStream);
      if Success = False then
      begin
        Writeln('An error occurred: Failed to send command to stop stream');
      end;
      // 8. Disconnect
      Writeln('Step 8: Disconnecting...');
      RF60XDevice.CloseSerialPort;
      Writeln('Disconnected from ', DEFAULT_COM_PORT, '.');
    end
    else
    begin
      Writeln('Failed to connect to ', DEFAULT_COM_PORT,
        '. Please check the port name and that the device is connected.');
    end;

  finally
    // 9. Free the device instance
    Writeln('');
    Writeln('Step 9: Cleaning up...');
    if Assigned(RF60XDevice) then
    begin
      RF60XDevice.Free;
      Writeln('Device destroyed.');
    end;
  end;

  Writeln('');
  Writeln('Example finished. Press Enter to exit.');
  Readln;
end;

end.
