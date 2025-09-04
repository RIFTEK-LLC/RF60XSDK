program RF60X_UART_Measure;

{$APPTYPE CONSOLE}

uses
  System.SysUtils,
  RF60X_UART_Measure_main in 'RF60X_UART_Measure_main.pas';
begin
  try
    TExampleApp.Run;
  except
    on E: Exception do
      Writeln(E.ClassName, ': ', E.Message);
  end;
end.
