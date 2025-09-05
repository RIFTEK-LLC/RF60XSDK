unit RF60X_Delphi;

interface

uses
  System.SysUtils, Winapi.Windows;

const
  RF60X_DLL = 'RF60X_C.dll'; // Name of the C DLL

type
  // Opaque pointer for the device handle
  TRF60XHandle = Pointer;
  // Opaque pointer for measurements
  AMeasureType = Pointer;

  // Measurement structs from rf60Xtypes.h
type
  // uart_result_with_encoder_t
  TUartResultWithEncoder = packed record
    Measure: Word;           // uint16_t measure
    RotationMarks: Word;     // uint16_t rotationMarks
    EncoderValue: Word;      // uint16_t encoderValue
  end;

  // udp_value_t
  TUDPValue = packed record
    Value: Word;             // uint16_t value
    Status: Byte;            // uint8_t status
  end;

  // udp_measure_t
  TUDPMeasure = packed record
    RF60XValArray: array[0..167] of TUDPValue;  // udp_value_t rf60xValArray[168]
    DeviceSerial: Word;                          // uint16_t deviceSerial
    DeviceBaseDistance: Word;                    // uint16_t deviceBaseDistance
    DeviceMeasureRange: Word;                    // uint16_t deviceMeasureRange
    PackCount: Byte;                             // uint8_t packCount
    PacketControlSumm: Byte;                     // uint8_t packetControlSumm
  end;

  // binocular_udp_value_t
  TBinocularUDPValue = packed record
    Measure: Word;           // uint16_t measure
    Exposition: Word;        // uint16_t exposition
    Status: Byte;            // uint8_t status
  end;

  // binocular_udp_measure_t
  TBinocularUDPMeasure = packed record
    RF60XBValArray: array[0..99] of TBinocularUDPValue;  // binocular_udp_value_t rf60xBValArray[100]
    Reserved: Word;                                      // uint16_t reserved
    Reserved2: Word;                                     // uint16_t reserved2
    DeviceSerial: Word;                                  // uint16_t deviceSerial
    DeviceBaseDistance: Word;                            // uint16_t deviceBaseDistance
    DeviceMeasureRange: Word;                            // uint16_t deviceMeasureRange
    PackCount: Byte;                                     // uint8_t packCount
    PacketControlSumm: Byte;                             // uint8_t packetControlSumm
  end;

  // C-style enums translated to Delphi
  TC_AL_MODE = (
    c_OutOfRange = 0,
    c_SlaveMode = 4,
    c_HardwareZeroSet = 8,
    c_LaserSwitch = 12,
    c_EncoderMode = 64,
    c_InputMode = 68,
    c_ResetEthernetCounter = 104,
    c_MasterMode = 76
  );

  TC_AVERAGING_MODE = (
    c_AveragingOverResults = 0,
    c_TimeAveraging = 32
  );

  TC_ANALOG_OUTPUT_MODE = (
    c_WindowMode = 0,
    c_FullRange = 2
  );

  TC_SAMPLING_MODE = (
    c_TimeSampling = 0,
    c_TriggerSampling = 1
  );

  TC_PROTOCOL_MEASURE_UART = (
    c_UartStreamMeasureT = 4,
    c_UartStreamAdvancedMeasureT = 6,
    c_UartStreamModifiedMeasureT = 10,
    c_UartResultWithEncoderT = 12
  );

  TC_COMMAND_UART = (
    c_WriteParam = $03,
    c_SaveToFlash = $F4,
    c_RestoreFromFlash = $04,
    c_GetResult = $06,
    c_StartStream = $07,
    c_StartStreamExtend = $0B,
    c_StartStreamAdvanced = $0C,
    c_StartStreamModified = $0D,
    c_StopStream = $08
  );

  // C-style structs translated to Delphi records
  TC_UartHello = record
    DeviceType: Byte;
    DeviceModificaton: Byte;
    DeviceSerial: Word;
    DeviceMaxDistance: Word;
    DeviceRange: Word;
  end;

  // Measurement structs from rf60Xtypes.h
  TStreamMeasure = record
    Value: Word;
    Count: Byte;
    Status: Byte;
    Reserved: Byte;
  end;

  TStreamAdvancedMeasure = record
      Value: Word;
      Status: Byte;
      Dir: Byte;
      Cnt: Byte;
  end;

// Function imports from the C DLL
function sdk_version: Integer; cdecl; external RF60X_DLL;

function create_rf60x: TRF60XHandle; cdecl; external RF60X_DLL;
procedure destroy_rf60x(dev: TRF60XHandle); cdecl; external RF60X_DLL;

function open_serial_port(dev: TRF60XHandle; comPortName: PAnsiChar; baudRate: Cardinal): Boolean; cdecl; external RF60X_DLL;
procedure close_serial_port(dev: TRF60XHandle); cdecl; external RF60X_DLL;
function connect_udp(dev: TRF60XHandle; hostAddress: PAnsiChar; port: Cardinal): Boolean; cdecl; external RF60X_DLL;
procedure disconnect_udp(dev: TRF60XHandle); cdecl; external RF60X_DLL;
procedure clear_serial_buffer(dev: TRF60XHandle); cdecl; external RF60X_DLL;

procedure bind_network_address(dev: TRF60XHandle; value: Cardinal); cdecl; external RF60X_DLL;
procedure set_wait_timer(dev: TRF60XHandle; value_ms: Cardinal); cdecl; external RF60X_DLL;

function set_sensor(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_analog_out(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_AL_mode(dev: TRF60XHandle; value: TC_AL_MODE): Boolean; cdecl; external RF60X_DLL;
function set_averaging_mode(dev: TRF60XHandle; value: TC_AVERAGING_MODE): Boolean; cdecl; external RF60X_DLL;
function set_analog_ouput_mode(dev: TRF60XHandle; value: TC_ANALOG_OUTPUT_MODE): Boolean; cdecl; external RF60X_DLL;
function set_sampling_mode(dev: TRF60XHandle; value: TC_SAMPLING_MODE): Boolean; cdecl; external RF60X_DLL;
function set_network_address(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_baute_rate(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_number_of_averaged_values(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_sampling_period(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_maximum_integration_time(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_begin_analog_range(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_end_analog_range(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_time_lock_of_result(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_zero_point(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_CAN_interface_speed(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_standard_identifier(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_extend_identifier(dev: TRF60XHandle; value: Cardinal): Boolean; cdecl; external RF60X_DLL;
function set_CAN_interface_identifier(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_CAN_interface(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_destination_ip_address(dev: TRF60XHandle; value: PAnsiChar): Boolean; cdecl; external RF60X_DLL;
function set_gateway_ip_address(dev: TRF60XHandle; value: PAnsiChar): Boolean; cdecl; external RF60X_DLL;
function set_subnet_mask(dev: TRF60XHandle; value: PAnsiChar): Boolean; cdecl; external RF60X_DLL;
function set_source_ip_address(dev: TRF60XHandle; value: PAnsiChar): Boolean; cdecl; external RF60X_DLL;
function set_number_of_measurements_in_the_packet(dev: TRF60XHandle; value: Word): Boolean; cdecl; external RF60X_DLL;
function set_ethernet_inteface(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_autostart_of_measurement_stream(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;
function set_protol_type(dev: TRF60XHandle; value: Byte): Boolean; cdecl; external RF60X_DLL;

function get_sensor(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_analog_out(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_AL_mode(dev: TRF60XHandle; out value_out: TC_AL_MODE): Boolean; cdecl; external RF60X_DLL;
function get_averaging_mode(dev: TRF60XHandle; out value_out: TC_AVERAGING_MODE): Boolean; cdecl; external RF60X_DLL;
function get_analog_ouput_mode(dev: TRF60XHandle; out value_out: TC_ANALOG_OUTPUT_MODE): Boolean; cdecl; external RF60X_DLL;
function get_sampling_mode(dev: TRF60XHandle; out value_out: TC_SAMPLING_MODE): Boolean; cdecl; external RF60X_DLL;
function get_network_address(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_baute_rate(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_number_of_averaged_values(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_sampling_period(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_maximum_integration_time(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_begin_analog_range(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_end_analog_range(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_time_lock_of_result(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_zero_point(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_CAN_interface_speed(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_standard_identifier(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_extend_identifier(dev: TRF60XHandle; out value_out: Cardinal): Boolean; cdecl; external RF60X_DLL;
function get_CAN_interface_identifier(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_CAN_interface(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_number_of_measurements_in_the_packet(dev: TRF60XHandle; out value_out: Word): Boolean; cdecl; external RF60X_DLL;
function get_ethernet_inteface(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_autostart_of_measurement_stream(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;
function get_protol_type(dev: TRF60XHandle; out value_out: Byte): Boolean; cdecl; external RF60X_DLL;

function get_source_ip_address(dev: TRF60XHandle; buffer: PAnsiChar; buffer_size: Cardinal): Boolean; cdecl; external RF60X_DLL;
function get_destination_ip_address(dev: TRF60XHandle; buffer: PAnsiChar; buffer_size: Cardinal): Boolean; cdecl; external RF60X_DLL;
function get_gateway_ip_address(dev: TRF60XHandle; buffer: PAnsiChar; buffer_size: Cardinal): Boolean; cdecl; external RF60X_DLL;
function get_subnet_mask(dev: TRF60XHandle; buffer: PAnsiChar; buffer_size: Cardinal): Boolean; cdecl; external RF60X_DLL;

function hello_msg_uart(dev: TRF60XHandle): TC_UartHello; cdecl; external RF60X_DLL;
function get_raw_measure_uart(dev: TRF60XHandle; bufferArray: PAnsiChar; size: Cardinal): Boolean; cdecl; external RF60X_DLL;
function get_single_measure(dev: TRF60XHandle; measure: Pointer): Boolean; cdecl; external RF60X_DLL;
function get_measure_uart(dev: TRF60XHandle; measure: Pointer; measure_type: TC_PROTOCOL_MEASURE_UART): Boolean; cdecl; external RF60X_DLL;
function send_command(dev: TRF60XHandle; value: TC_COMMAND_UART): Boolean; cdecl; external RF60X_DLL;
function request_custom_command(dev: TRF60XHandle; data: PAnsiChar; size: Byte): Boolean; cdecl; external RF60X_DLL;
function read_custom_command(dev: TRF60XHandle; command: Byte; size: Byte; vec_ref: PAnsiChar; vec_size: Cardinal): Boolean; cdecl; external RF60X_DLL;

type
  TStringGetterFunc = function(dev: TRF60XHandle; buffer: PAnsiChar; buffer_size: Cardinal): Boolean; cdecl;

// Delphi Wrapper Class
type
  TRF60X = class
  private
    FHandle: TRF60XHandle;
    function GetHandle: TRF60XHandle;
    function GetString(Getter: TStringGetterFunc; out AValue: string): Boolean; public
    constructor Create;
    destructor Destroy; override;

    function OpenSerialPort(AComPortName: string; ABaudRate: Cardinal): Boolean;
    procedure CloseSerialPort;
    function ConnectUDP(AHostAddress: string; APort: Cardinal): Boolean;
    procedure DisconnectUDP;
    procedure ClearSerialBuffer;

    procedure BindNetworkAddress(AValue: Cardinal);
    procedure SetWaitTimer(AValueMs: Cardinal);

    function SetSensor(AValue: Byte): Boolean;
    function SetAnalogOut(AValue: Byte): Boolean;
    function SetALMode(AValue: TC_AL_MODE): Boolean;
    function SetAveragingMode(AValue: TC_AVERAGING_MODE): Boolean;
    function SetAnalogOutputMode(AValue: TC_ANALOG_OUTPUT_MODE): Boolean;
    function SetSamplingMode(AValue: TC_SAMPLING_MODE): Boolean;
    function SetNetworkAddress(AValue: Byte): Boolean;
    function SetBaudRate(AValue: Byte): Boolean;
    function SetNumberOfAveragedValues(AValue: Byte): Boolean;
    function SetSamplingPeriod(AValue: Word): Boolean;
    function SetMaxIntegrationTime(AValue: Word): Boolean;
    function SetBeginAnalogRange(AValue: Word): Boolean;
    function SetEndAnalogRange(AValue: Word): Boolean;
    function SetTimeLockOfResult(AValue: Byte): Boolean;
    function SetZeroPoint(AValue: Word): Boolean;
    function SetCANInterfaceSpeed(AValue: Byte): Boolean;
    function SetStandardIdentifier(AValue: Word): Boolean;
    function SetExtendIdentifier(AValue: Cardinal): Boolean;
    function SetCANInterfaceIdentifier(AValue: Byte): Boolean;
    function SetCANInterface(AValue: Byte): Boolean;
    function SetDestinationIP(AValue: string): Boolean;
    function SetGatewayIP(AValue: string): Boolean;
    function SetSubnetMask(AValue: string): Boolean;
    function SetSourceIP(AValue: string): Boolean;
    function SetNumberOfMeasurementsInPacket(AValue: Word): Boolean;
    function SetEthernetInterface(AValue: Byte): Boolean;
    function SetAutostartOfMeasurementStream(AValue: Byte): Boolean;
    function SetProtocolType(AValue: Byte): Boolean;

    function GetSensor(out AValue: Byte): Boolean;
    function GetAnalogOut(out AValue: Byte): Boolean;
    function GetALMode(out AValue: TC_AL_MODE): Boolean;
    function GetAveragingMode(out AValue: TC_AVERAGING_MODE): Boolean;
    function GetAnalogOutputMode(out AValue: TC_ANALOG_OUTPUT_MODE): Boolean;
    function GetSamplingMode(out AValue: TC_SAMPLING_MODE): Boolean;
    function GetNetworkAddress(out AValue: Byte): Boolean;
    function GetBaudRate(out AValue: Byte): Boolean;
    function GetNumberOfAveragedValues(out AValue: Byte): Boolean;
    function GetSamplingPeriod(out AValue: Word): Boolean;
    function GetMaxIntegrationTime(out AValue: Word): Boolean;
    function GetBeginAnalogRange(out AValue: Word): Boolean;
    function GetEndAnalogRange(out AValue: Word): Boolean;
    function GetTimeLockOfResult(out AValue: Byte): Boolean;
    function GetZeroPoint(out AValue: Word): Boolean;
    function GetCANInterfaceSpeed(out AValue: Byte): Boolean;
    function GetStandardIdentifier(out AValue: Word): Boolean;
    function GetExtendIdentifier(out AValue: Cardinal): Boolean;
    function GetCANInterfaceIdentifier(out AValue: Byte): Boolean;
    function GetCANInterface(out AValue: Byte): Boolean;
    function GetNumberOfMeasurementsInPacket(out AValue: Word): Boolean;
    function GetEthernetInterface(out AValue: Byte): Boolean;
    function GetAutostartOfMeasurementStream(out AValue: Byte): Boolean;
    function GetProtocolType(out AValue: Byte): Boolean;

    function GetSourceIP(out AValue: string): Boolean;
    function GetDestinationIP(out AValue: string): Boolean;
    function GetGatewayIP(out AValue: string): Boolean;
    function GetSubnetMask(out AValue: string): Boolean;

    function GetHelloMsgUart: TC_UartHello;
    function GetRawMeasureUart(var ABuffer; ASize: Cardinal): Boolean;
    function GetSingleMeasure(var AMeasure: TStreamMeasure): Boolean;
    function GetMeasureUart(var AMeasure; AMeasureType: TC_PROTOCOL_MEASURE_UART): Boolean;

    function SendCommand(ACommand: TC_COMMAND_UART): Boolean;
    function RequestCustomCommand(AData: AnsiString): Boolean;
    function ReadCustomCommand(ACommand: Byte; ASize: Byte; out ABuffer: TBytes): Boolean;

    property Handle: TRF60XHandle read GetHandle;
    class function SdkVersion: Integer;
  end;

implementation

{ TRF60X }

constructor TRF60X.Create;
begin
  FHandle := create_rf60x;
  if FHandle = nil then
    raise Exception.Create('Failed to create RF60X device.');
end;

destructor TRF60X.Destroy;
begin
  if FHandle <> nil then
    destroy_rf60x(FHandle);
  inherited;
end;

function TRF60X.GetHandle: TRF60XHandle;
begin
  Result := FHandle;
end;

class function TRF60X.SdkVersion: Integer;
begin
  Result := sdk_version;
end;

function TRF60X.OpenSerialPort(AComPortName: string; ABaudRate: Cardinal): Boolean;
var
  PComPort: PAnsiChar;
begin
  PComPort := PAnsiChar(AnsiString(AComPortName));
  Result := open_serial_port(FHandle, PComPort, ABaudRate);
end;

procedure TRF60X.CloseSerialPort;
begin
  close_serial_port(FHandle);
end;

function TRF60X.ConnectUDP(AHostAddress: string; APort: Cardinal): Boolean;
var
  PHost: PAnsiChar;
begin
  PHost := PAnsiChar(AnsiString(AHostAddress));
  Result := connect_udp(FHandle, PHost, APort);
end;

procedure TRF60X.DisconnectUDP;
begin
  disconnect_udp(FHandle);
end;

procedure TRF60X.ClearSerialBuffer;
begin
  clear_serial_buffer(FHandle);
end;

procedure TRF60X.BindNetworkAddress(AValue: Cardinal);
begin
  bind_network_address(FHandle, AValue);
end;

procedure TRF60X.SetWaitTimer(AValueMs: Cardinal);
begin
  set_wait_timer(FHandle, AValueMs);
end;

function TRF60X.SetSensor(AValue: Byte): Boolean;
begin
  Result := set_sensor(FHandle, AValue);
end;

function TRF60X.SetAnalogOut(AValue: Byte): Boolean;
begin
    Result := set_analog_out(FHandle, AValue);
end;

function TRF60X.SetALMode(AValue: TC_AL_MODE): Boolean;
begin
  Result := set_AL_mode(FHandle, AValue);
end;

function TRF60X.SetAveragingMode(AValue: TC_AVERAGING_MODE): Boolean;
begin
    Result := set_averaging_mode(FHandle, AValue);
end;

function TRF60X.SetAnalogOutputMode(AValue: TC_ANALOG_OUTPUT_MODE): Boolean;
begin
    Result := set_analog_ouput_mode(FHandle, AValue);
end;

function TRF60X.SetSamplingMode(AValue: TC_SAMPLING_MODE): Boolean;
begin
    Result := set_sampling_mode(FHandle, AValue);
end;

function TRF60X.SetNetworkAddress(AValue: Byte): Boolean;
begin
    Result := set_network_address(FHandle, AValue);
end;

function TRF60X.SetBaudRate(AValue: Byte): Boolean;
begin
    Result := set_baute_rate(FHandle, AValue);
end;

function TRF60X.SetNumberOfAveragedValues(AValue: Byte): Boolean;
begin
    Result := set_number_of_averaged_values(FHandle, AValue);
end;

function TRF60X.SetSamplingPeriod(AValue: Word): Boolean;
begin
    Result := set_sampling_period(FHandle, AValue);
end;

function TRF60X.SetMaxIntegrationTime(AValue: Word): Boolean;
begin
    Result := set_maximum_integration_time(FHandle, AValue);
end;

function TRF60X.SetBeginAnalogRange(AValue: Word): Boolean;
begin
    Result := set_begin_analog_range(FHandle, AValue);
end;

function TRF60X.SetEndAnalogRange(AValue: Word): Boolean;
begin
    Result := set_end_analog_range(FHandle, AValue);
end;

function TRF60X.SetTimeLockOfResult(AValue: Byte): Boolean;
begin
    Result := set_time_lock_of_result(FHandle, AValue);
end;

function TRF60X.SetZeroPoint(AValue: Word): Boolean;
begin
    Result := set_zero_point(FHandle, AValue);
end;

function TRF60X.SetCANInterfaceSpeed(AValue: Byte): Boolean;
begin
    Result := set_CAN_interface_speed(FHandle, AValue);
end;

function TRF60X.SetStandardIdentifier(AValue: Word): Boolean;
begin
    Result := set_standard_identifier(FHandle, AValue);
end;

function TRF60X.SetExtendIdentifier(AValue: Cardinal): Boolean;
begin
    Result := set_extend_identifier(FHandle, AValue);
end;

function TRF60X.SetCANInterfaceIdentifier(AValue: Byte): Boolean;
begin
    Result := set_CAN_interface_identifier(FHandle, AValue);
end;

function TRF60X.SetCANInterface(AValue: Byte): Boolean;
begin
    Result := set_CAN_interface(FHandle, AValue);
end;

function TRF60X.SetDestinationIP(AValue: string): Boolean;
var
  PIP: PAnsiChar;
begin
  PIP := PAnsiChar(AnsiString(AValue));
  Result := set_destination_ip_address(FHandle, PIP);
end;

function TRF60X.SetGatewayIP(AValue: string): Boolean;
var
  PIP: PAnsiChar;
begin
  PIP := PAnsiChar(AnsiString(AValue));
  Result := set_gateway_ip_address(FHandle, PIP);
end;

function TRF60X.SetSubnetMask(AValue: string): Boolean;
var
  PIP: PAnsiChar;
begin
  PIP := PAnsiChar(AnsiString(AValue));
  Result := set_subnet_mask(FHandle, PIP);
end;

function TRF60X.SetSourceIP(AValue: string): Boolean;
var
  PIP: PAnsiChar;
begin
  PIP := PAnsiChar(AnsiString(AValue));
  Result := set_source_ip_address(FHandle, PIP);
end;

function TRF60X.SetNumberOfMeasurementsInPacket(AValue: Word): Boolean;
begin
    Result := set_number_of_measurements_in_the_packet(FHandle, AValue);
end;

function TRF60X.SetEthernetInterface(AValue: Byte): Boolean;
begin
    Result := set_ethernet_inteface(FHandle, AValue);
end;

function TRF60X.SetAutostartOfMeasurementStream(AValue: Byte): Boolean;
begin
    Result := set_autostart_of_measurement_stream(FHandle, AValue);
end;

function TRF60X.SetProtocolType(AValue: Byte): Boolean;
begin
    Result := set_protol_type(FHandle, AValue);
end;

function TRF60X.GetSensor(out AValue: Byte): Boolean;
begin
  Result := get_sensor(FHandle, AValue);
end;

function TRF60X.GetAnalogOut(out AValue: Byte): Boolean;
begin
    Result := get_analog_out(FHandle, AValue);
end;

function TRF60X.GetALMode(out AValue: TC_AL_MODE): Boolean;
begin
    Result := get_AL_mode(FHandle, AValue);
end;

function TRF60X.GetAveragingMode(out AValue: TC_AVERAGING_MODE): Boolean;
begin
    Result := get_averaging_mode(FHandle, AValue);
end;

function TRF60X.GetAnalogOutputMode(out AValue: TC_ANALOG_OUTPUT_MODE): Boolean;
begin
    Result := get_analog_ouput_mode(FHandle, AValue);
end;

function TRF60X.GetSamplingMode(out AValue: TC_SAMPLING_MODE): Boolean;
begin
    Result := get_sampling_mode(FHandle, AValue);
end;

function TRF60X.GetNetworkAddress(out AValue: Byte): Boolean;
begin
    Result := get_network_address(FHandle, AValue);
end;

function TRF60X.GetBaudRate(out AValue: Byte): Boolean;
begin
    Result := get_baute_rate(FHandle, AValue);
end;

function TRF60X.GetNumberOfAveragedValues(out AValue: Byte): Boolean;
begin
    Result := get_number_of_averaged_values(FHandle, AValue);
end;

function TRF60X.GetSamplingPeriod(out AValue: Word): Boolean;
begin
    Result := get_sampling_period(FHandle, AValue);
end;

function TRF60X.GetMaxIntegrationTime(out AValue: Word): Boolean;
begin
    Result := get_maximum_integration_time(FHandle, AValue);
end;

function TRF60X.GetBeginAnalogRange(out AValue: Word): Boolean;
begin
    Result := get_begin_analog_range(FHandle, AValue);
end;

function TRF60X.GetEndAnalogRange(out AValue: Word): Boolean;
begin
    Result := get_end_analog_range(FHandle, AValue);
end;

function TRF60X.GetTimeLockOfResult(out AValue: Byte): Boolean;
begin
    Result := get_time_lock_of_result(FHandle, AValue);
end;

function TRF60X.GetZeroPoint(out AValue: Word): Boolean;
begin
    Result := get_zero_point(FHandle, AValue);
end;

function TRF60X.GetCANInterfaceSpeed(out AValue: Byte): Boolean;
begin
    Result := get_CAN_interface_speed(FHandle, AValue);
end;

function TRF60X.GetStandardIdentifier(out AValue: Word): Boolean;
begin
    Result := get_standard_identifier(FHandle, AValue);
end;

function TRF60X.GetExtendIdentifier(out AValue: Cardinal): Boolean;
begin
    Result := get_extend_identifier(FHandle, AValue);
end;

function TRF60X.GetCANInterfaceIdentifier(out AValue: Byte): Boolean;
begin
    Result := get_CAN_interface_identifier(FHandle, AValue);
end;

function TRF60X.GetCANInterface(out AValue: Byte): Boolean;
begin
    Result := get_CAN_interface(FHandle, AValue);
end;

function TRF60X.GetNumberOfMeasurementsInPacket(out AValue: Word): Boolean;
begin
    Result := get_number_of_measurements_in_the_packet(FHandle, AValue);
end;

function TRF60X.GetEthernetInterface(out AValue: Byte): Boolean;
begin
    Result := get_ethernet_inteface(FHandle, AValue);
end;

function TRF60X.GetAutostartOfMeasurementStream(out AValue: Byte): Boolean;
begin
    Result := get_autostart_of_measurement_stream(FHandle, AValue);
end;

function TRF60X.GetProtocolType(out AValue: Byte): Boolean;
begin
    Result := get_protol_type(FHandle, AValue);
end;

function TRF60X.GetString(Getter: TStringGetterFunc; out AValue: string): Boolean;
var
  Buffer: array[0..255] of AnsiChar;
begin
  Result := Getter(FHandle, Buffer, SizeOf(Buffer));
  if Result then
    AValue := PAnsiChar(Buffer) // Correct way to convert null-terminated string
  else
    AValue := '';
end;

function TRF60X.GetSourceIP(out AValue: string): Boolean;
begin
  Result := GetString(@get_source_ip_address, AValue);
end;

function TRF60X.GetDestinationIP(out AValue: string): Boolean;
begin
  Result := GetString(@get_destination_ip_address, AValue);
end;

function TRF60X.GetGatewayIP(out AValue: string): Boolean;
begin
  Result := GetString(@get_gateway_ip_address, AValue);
end;

function TRF60X.GetSubnetMask(out AValue: string): Boolean;
begin
  Result := GetString(@get_subnet_mask, AValue);
end;

function TRF60X.GetHelloMsgUart: TC_UartHello;
begin
  Result := hello_msg_uart(FHandle);
end;

function TRF60X.GetRawMeasureUart(var ABuffer; ASize: Cardinal): Boolean;
begin
    Result := get_raw_measure_uart(FHandle, PAnsiChar(@ABuffer), ASize);
end;

function TRF60X.GetSingleMeasure(var AMeasure: TStreamMeasure): Boolean;
begin
  Result := get_single_measure(FHandle, @AMeasure);
end;

function TRF60X.GetMeasureUart(var AMeasure; AMeasureType: TC_PROTOCOL_MEASURE_UART): Boolean;
begin
    Result := get_measure_uart(FHandle, @AMeasure, AMeasureType);
end;

function TRF60X.SendCommand(ACommand: TC_COMMAND_UART): Boolean;
begin
  Result := send_command(FHandle, ACommand);
end;

function TRF60X.RequestCustomCommand(AData: AnsiString): Boolean;
begin
    Result := request_custom_command(FHandle, PAnsiChar(AData), Length(AData));
end;

function TRF60X.ReadCustomCommand(ACommand: Byte; ASize: Byte; out ABuffer: TBytes): Boolean;
var
  BufSize: Cardinal;
begin
  BufSize := 256; // Default buffer size
  SetLength(ABuffer, BufSize);
  Result := read_custom_command(FHandle, ACommand, ASize, PAnsiChar(ABuffer), BufSize);
  // The C function doesn't tell us the actual size, so we can't resize the buffer.
  // The caller must be aware of the expected data size.
end;

end.
