# 1 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. 
// To get started please visit https://microsoft.github.io/azure-iot-developer-kit/docs/projects/connect-iot-hub?utm_source=ArduinoExtension&utm_medium=ReleaseNote&utm_campaign=VSCode
# 5 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 2
# 6 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 2
# 7 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 2
# 8 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 2
# 9 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 2
# 10 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 2

static const char* currentFirmwareVersion = "1.0.0";

static bool hasWifi = false;

static bool enableOTA = true;
static const FW_INFO* fwInfo = 
# 16 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                              __null
# 16 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                  ;
static MAP_HANDLE OTAStatusMap = 
# 17 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                                __null
# 17 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                    ;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utilities
// Initialize Wi-Fi
static void InitWifi()
{
  Screen.print(2, "Connecting...");

  if (WiFi.begin() == WL_CONNECTED)
  {
    IPAddress ip = WiFi.localIP();
    Screen.print(1, ip.get_address());
    hasWifi = true;
    Screen.print(2, "Running... \r\n");
  }
  else
  {
    hasWifi = false;
    Screen.print(1, "No Wi-Fi\r\n ");
  }
}

// Report the OTA update status to Azure
static void ReportOTAStatus(const char* currentFwVersion, const char* pendingFwVersion, const char* fwUpdateStatus, const char* fwUpdateSubstatus, const char* lastFwUpdateStartTime, const char* lastFwUpdateEndTime)
{
  OTAStatusMap = Map_Create(
# 43 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                           __null
# 43 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                               );
  Map_Add(OTAStatusMap, "type", "IoTDevKit"); // The type of the firmware
  if (currentFwVersion)
  {
    Map_Add(OTAStatusMap, "currentFwVersion", currentFwVersion);
  }
  if (pendingFwVersion)
  {
    Map_Add(OTAStatusMap, "pendingFwVersion", pendingFwVersion);
  }
  if (fwUpdateStatus)
  {
    Map_Add(OTAStatusMap, "fwUpdateStatus", fwUpdateStatus);
  }
  if (fwUpdateSubstatus)
  {
    Map_Add(OTAStatusMap, "fwUpdateSubstatus", fwUpdateSubstatus);
  }
  if (lastFwUpdateStartTime)
  {
    Map_Add(OTAStatusMap, "lastFwUpdateStartTime", lastFwUpdateStartTime);
  }
  if (lastFwUpdateEndTime)
  {
    Map_Add(OTAStatusMap, "lastFwUpdateEndTime", lastFwUpdateEndTime);
  }
  IoTHubClient_ReportOTAStatus(OTAStatusMap);
  Map_Destroy(OTAStatusMap);
  DevKitMQTTClient_Check();
}
// Enter a failed state, print failed message and report status
static void OTAUpdateFailed(const char* failedMsg)
{
  ReportOTAStatus(currentFirmwareVersion, fwInfo ? fwInfo->fwVersion : "", "Error", failedMsg, "", "");
  enableOTA = false;
  Screen.print(1, "OTA failed:");
  Screen.print(2, failedMsg);
  Screen.print(3, " ");
  do{{ (void)(0 && printf("Failed to update firmware %s: %s, disable OTA update.", fwInfo ? fwInfo->fwVersion : "<unknown>", failedMsg)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 81 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
 __null
# 81 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 81, 0x01, "Failed to update firmware %s: %s, disable OTA update.", fwInfo ? fwInfo->fwVersion : "<unknown>", failedMsg); } }; }while((void)0,0);
}

// Check for new firmware
static void CheckNewFirmware(void)
{
  if (!enableOTA)
  {
    return;
  }

  // Check if there has new firmware info.
  fwInfo = IoTHubClient_GetLatestFwInfo();
  if (fwInfo == 
# 94 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
               __null
# 94 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                   )
  {
    // No firmware update info
    return;
  }

  if (fwInfo->fwVersion == 
# 100 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                          __null 
# 100 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                               || fwInfo->fwPackageURI == 
# 100 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                                                          __null
# 100 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                                              )
  {
    // Disable 
    do{{ (void)(0 && printf("Invalid new firmware infomation retrieved, disable OTA update.")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 103 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
   __null
# 103 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 103, 0x01, "Invalid new firmware infomation retrieved, disable OTA update."); } }; }while((void)0,0);
    enableOTA = false;
    return;
  }

  // Check if the URL is https as we require it for safety purpose.
  if (strlen(fwInfo->fwPackageURI) < 6 || (strncmp("https:", fwInfo->fwPackageURI, 6) != 0))
  {
    // Report error status, URINotHTTPS
    OTAUpdateFailed("URINotHTTPS");
    return;
  }

  // Check if this is a new version.
  if (IoTHubClient_FwVersionCompare(fwInfo->fwVersion, currentFirmwareVersion) <= 0)
  {
    // The firmware version from cloud <= the running firmware version
    return;
  }

  // New firemware
  Screen.print(1, "New firmware:");
  Screen.print(2, fwInfo->fwVersion);
  do{{ (void)(0 && printf("New firmware is available: %s.", fwInfo->fwVersion)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 126 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
 __null
# 126 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 126, 0x01, "New firmware is available: %s.", fwInfo->fwVersion); } }; }while((void)0,0);

  Screen.print(3, " downloading...");
  do{{ (void)(0 && printf(">> Downloading from %s...", fwInfo->fwPackageURI)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 129 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
 __null
# 129 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 129, 0x01, ">> Downloading from %s...", fwInfo->fwPackageURI); } }; }while((void)0,0);
  // Report downloading status.
  char startTimeStr[30];
  time_t t = time(
# 132 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                 __null
# 132 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                     );
  strftime(startTimeStr, 30, "%Y-%m-%dT%H:%M:%S.0000000Z", gmtime(&t));
  ReportOTAStatus(currentFirmwareVersion, fwInfo->fwVersion, "Downloading", fwInfo->fwPackageURI, startTimeStr, "");

  // Close IoT Hub Client to release the TLS resource for firmware download.
  DevKitMQTTClient_Close();
  // Download the firmware. This can be customized according to the board type.
  uint16_t checksum = 0;
  int fwSize = OTADownloadFirmware(fwInfo->fwPackageURI, &checksum);

  // Reopen the IoT Hub Client for reporting status.
  DevKitMQTTClient_Init(true);

  // Check result
  if (fwSize == 0 || fwSize == -1)
  {
    // Report error status, DownloadFailed
    OTAUpdateFailed("DownloadFailed");
    return;
  }
  else if (fwSize == -2)
  {
    // Report error status, DeviceError
    OTAUpdateFailed("DeviceError");
    return;
  }
  else if (fwSize != fwInfo->fwSize)
  {
    // Report error status, FileSizeNotMatch
    OTAUpdateFailed("FileSizeNotMatch");
    return;
  }

  Screen.print(3, " Finished.");
  do{{ (void)(0 && printf(">> Finished download.")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 166 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
 __null
# 166 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 166, 0x01, ">> Finished download."); } }; }while((void)0,0);

  // CRC check
  if (fwInfo->fwPackageCheckValue != 
# 169 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                                    __null
# 169 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                        )
  {
    Screen.print(3, " verifying...");

    if (checksum == strtoul(fwInfo->fwPackageCheckValue, 
# 173 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                                                        __null
# 173 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                                            , 16))
    {
      Screen.print(3, " passed.");
      do{{ (void)(0 && printf(">> CRC check passed.")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 176 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
     __null
# 176 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
     ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 176, 0x01, ">> CRC check passed."); } }; }while((void)0,0);
    }
    else
    {
      // Report error status, VerifyFailed
      OTAUpdateFailed("VerifyFailed");
      Screen.print(3, " CRC failed.");
      return;
    }
  }

  // Applying
  if (OTAApplyNewFirmware(fwSize, checksum) != 0)
  {
    // Report error status, ApplyFirmwareFailed
    OTAUpdateFailed("ApplyFirmwareFailed");
    Screen.print(3, " Apply failed.");
    return;
  }
  // Report status
  char endTimeStr[30];
  t = time(
# 197 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
          __null
# 197 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
              );
  strftime(endTimeStr, 30, "%Y-%m-%dT%H:%M:%S.0000000Z", gmtime(&t));
  ReportOTAStatus(currentFirmwareVersion, fwInfo->fwVersion, "Applying", "", startTimeStr, endTimeStr);

  // Counting down and reboot
  Screen.clean();
  Screen.print(0, "Reboot system");
  do{{ (void)(0 && printf("Reboot system to apply the new firmware:")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 204 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
 __null
# 204 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 204, 0x01, "Reboot system to apply the new firmware:"); } }; }while((void)0,0);
  char msg[2] = { 0 };
  for (int i = 0; i < 5; i++)
  {
    msg[0] = '0' + 5 - i;
    Screen.print(2, msg);
    do{{ (void)(0 && printf(msg)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 210 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
   __null
# 210 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 210, 0x01, msg); } }; }while((void)0,0);
    delay(1000);
  }

  // Reboot system to apply the firmware.
  SystemReboot();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arduino sketch
void setup()
{
  Screen.init();
  Screen.print(0, "IoT DevKit");
  Screen.print(2, "Initializing...");

  Screen.print(3, " > Serial");
  Serial.begin(115200);

  // Initialize the WiFi module
  Screen.print(3, " > WiFi");
  hasWifi = false;
  InitWifi();
  if (!hasWifi)
  {
    return;
  }

  // Print out the version
  Screen.print(1, "FW version:");
  Screen.print(2, currentFirmwareVersion);
  Screen.print(3, " checking...");

  // Initialize MQTT client
  DevKitMQTTClient_SetOption("MiniSolution", "FirmwareOTA");
  DevKitMQTTClient_Init(true);

  do{{ (void)(0 && printf("FirmwareOTA demo: %s", currentFirmwareVersion)); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 247 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
 __null
# 247 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
 ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 247, 0x01, "FirmwareOTA demo: %s", currentFirmwareVersion); } }; }while((void)0,0);
  // Report OTA status
  ReportOTAStatus(currentFirmwareVersion, "", "Current", "", 
# 249 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                                                                     __null
# 249 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                                                         , 
# 249 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
                                                                           __null
# 249 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
                                                                               );
}

void loop()
{
  if (hasWifi)
  {
    DevKitMQTTClient_Check();

    // Check for new firmware
    CheckNewFirmware();

    do{{ (void)(0 && printf("No new firmware...")); { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 261 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino" 3 4
   __null
# 261 "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino"
   ) l(AZ_LOG_INFO, "c:\\Users\\d.gualandris\\Documents\\IoTWorkbenchProjects\\examples\\firmware_ota\\Device\\FirmwareOTA.ino", __func__, 261, 0x01, "No new firmware..."); } }; }while((void)0,0);
  }
  delay(1000);
}
