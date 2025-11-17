/*	 Copyright (c) 2000 by ULYS SOFT, Saint Jorioz, France


   Environment :	PC	(Langage C)

   DESCRIPTION:

   Bibliothèque d'accès aux cartes EXXOTEST Multiplexage //
   DLL interface for EXXOTest Multiplexing board

   AUTHOR : Philippe CHAZOT

   MODIFICATION:

        V 1.00	   Philippe CHAZOT
      - Created.

        V 2.00	   Philippe CHAZOT
      - Adatapted for MultiCAN board.

        V 2.01	   Philippe CHAZOT
      - Change prototype of CANReadTransceiverLS function

        V 3.00	   Philippe CHAZOT
      - Insert Lin functions

        V 3.10	   Philippe CHAZOT
      - Add xxxClearFifoRx functions

        V 4.0	   Philippe CHAZOT
      - Add USB functions

        V 4.1	   13/08/2002   Philippe CHAZOT
      - Change ISO functions

        V 4.2	   13/08/2002   Philippe CHAZOT
      - Add periodic functions (xxxPeriodicCreate,

        V 4.3	   13/08/2002   Philippe CHAZOT
      - Add ISO functions (Iso14230SendMsg, ....)

        V 5.0	   18/12/2002   Philippe CHAZOT
      - Add ISO15765-2 functions (NwcFunctions ....) - "Diag On CAN" and OSEK segmentation
      - Add xxxGetFifoRxLevel to get the count of events in the FIFO queue
      - Add IOGetCount to get the number of input and output
      - Add IOConfigInput to store input event in FIFO Rx

        V 5.1	   25/02/2003   Philippe CHAZOT
      - Modify KWP2000 data length up to 256 bytes
      - Add functions : NwcGetChannelState

        V 5.20	   6/03/2003   Philippe CHAZOT
      - Change all functions with __stdcall argument to be compatible with other langage than C
        This version is not compatible with previous - Contact your provider for more information

        V 5.21	   14/03/2003   Philippe CHAZOT
      - Add IsoSendMsg pointer function
      - Add IsoConfigPeriodic & IsoWaitResponse & IsoChangeBaudRate functions
      - Change stdcall format for compatiblity with VISUAL C++
      - Add CanConfigDualFilter function
      - Modify KWP2000 data length up to 260 bytes to manage raw data field up to 255
      - Add SPITransfer function

        V 5.22	   17/04/2003   Philippe CHAZOT
      - Bug fixed on PCI board in function IsoWaitResponse
      - Manage wTidle during fast initialization
      - Replace tIsoEvent.dwReserved1 by using wKeyWord and wReserved (this is able to make difference between 9141 and 14230 key word)
      - Add new boards

        V 5.30	   22/04/2003   Philippe CHAZOT
      - Add J1587 functions
      - Add IOConfigOutput to setup trigger condition
      - Add 20833 for LIN baud rate

        V 5.31	   17/06/2003   Philippe CHAZOT
      - Rx enhanced when ECU response during stop bit address (ISO 5 bauds init)

        V 5.32	   08/09/2003   Philippe CHAZOT
      - ISO Fast init delay is more accuracy
      - L line is managed on PCI board during ISO initialization
      - CAN minor modification
      - NWC speed optimization
      - ISO baud rate
      - Add NwcChannelClose & NwcChannelSendAsyncMsg functions
      - Add xxxIsBusActivate function
      - Support USB_MUX_CV32A device and Add Anaxxx functions

        V 5.33	   02/12/2003   Philippe CHAZOT
      - Support CL500 device

        V 5.34	   23/03/2003   Philippe CHAZOT
      - Add NMEA0183 functions, I2C, PWM and User functions
      - Add MuxTrace mode in tMuxMode enum
      - Add ISO_ERR_TO_RESPn error code

        V 5.35	   24/05/2004   Philippe CHAZOT
      - Add LinSetVersion to be conform with new V2.0 LIN Spécification ( V2.0 is not compatible with V 1.2 and V 1.3, thanks to LIN consortium)
      - Add Internal Event to restart in frame response
      - Change MoxLoadDLL to look muxdll.dll in bin folder before windwos\system

        V 5.36	   13/09/2004   Alexandre GAMBIER
      - Add support for Windows CE v3.x or above. (READ THE MANUAL FOR MORE INFORMATION ON DEVELOPPING UNDER WINDOWS CE)
      - Under Windows CE STATUS_NOT_SUPPORTED is replace by STATUS_UNSUPPORTED (STATUS_NOT_SUPPORTED is already defined for Windows CE)
      - Add REFMUX_STR macro due to Windows CE developing tools which does not accept 'char*' strings but 'unsigned short*' strings.

        V 5.37alpha	   13/10/2004   Alexandre GAMBIER
      - Add support of unaligned pointer access under Windows CE.
      - Correct some structure aligments for Windows CE that make NWC_Activate fails.
      - USB communication is more efficient (some IsoGevent didn't occured under Windows CE)
      - Correct a bug that make some function to return STATUS_ERR_TO_USB error code, due to an USB communication bug.

        V 5.38
      - Correct a bug that make the WinCE driver to lose some event (CAN, ISO, LIN, ...)
      - Increase the WinCE Driver Thread priority level in order to enhance it

        V 5.39
      - Correct a bug that make the WinCE driver to lose some NWC event

        V 5.40	10/01/2005	Alexandre GAMBIER
      - NWC_Register is now obsolete, all NWC_xxx function are always enabled. 

        V 5.41	17/01/2005	Lionel DEGOUTTE
      - The FctProprietary function works now with all the USB-MUX-XXX devices.
      - The USB devices must be uploaded with software v2.30 or above.
      - The internal USB structures has been changed.

        V 5.42	19/01/2005	Alexandre GAMBIER
      - Correct a bug under WinCE when opening multiple instance of the muxdll.dll with multiple process.
      - Under Windows CE, had a power monitoring feature that will make sure that the driver is still loaded
        or not after the pocket pc has gone to power down mode. If the driver has been unloaded by the OS, the
        muxdll will not crash when doing USB access BUT THE MUXDLL.DLL MUST BE RELOADED.
      - Add WINCExxx functions that will give the user the possibility to prevent the pocket to power down or
        to know when the driver has been unloaded
      - Add EVENT_WINCE_xxx events
      - User can know the pocket pc's battery state.

        V 5.43	31/01/2005	Nouredine BOUNEMOURA
      - Under CVI suite, the _MUXAPI is now declared as "#define _MUXAPI __declspec(dllimport) __stdcall"
        elsewhere the CVI can not access to the muxdll.dll correctly.

        V 5.44	22/02/2005	Alexandre GAMBIER
      - Add new MuxCheckAlignment function which can check if the alignment options are correctly set to use the muxdll.dll
        returns STATUS_ERR_ALIGNMENT error code if the alignment options are not correctly set.
      - Correct a bug with IsoChangeBaudRate function. After having set a new baud rate, the messages ISO_MSG_NORMAL
        were not sent.

        V 5.45	24/03/2005	Alexandre GAMBIER
      - Correct a bug in the NwcDeactivate function which did not free memory allocated by NwcActivate.

        V 5.46	12/04/2005	Alexandre GAMBIER
      - Correct a bug in the time stamp when opening a card in MODE_DEMO.
      - Correct a bug in MODE_DEMO, when using IsoSendMsg, a EVENT_ISO_MSGRX event was generated and not a EVENT_ISO_MSGTX
      - Add ISO_BAUD_5 enum value. USB Device Firmware must be 2.32 or above
      - Add MuxClientServerMode (RESERVED) function which enable the client server mode to protect all multiple access to one device.
      - Add MuxLoadDLLClient function which load the client library to access to the devices in client/server mode.
        returns STATUS_ERR_SERVERNOTLOADED when the server is not loaded.
      - Correct a bug with IsoSendMsg function, the ISO_MSG_WAITRESP message type was not supported.
      - Correct a bug on the NWC buses, that crash making a NULL adress reading when using NWC_Active with a lot of activity on the bus

        V 5.47	30/06/2005	Nouredine BOUNEMOURA / Alexandre GAMBIER
      - Add IsoSendResp function.
      - Add LinClearBufferIFR function.
      - Remove the __declspec(dllimport) for the CVI compiler
	  
        V 5.48	07/09/2005	Alexandre GAMBIER / Nouredine BOUNEMOURA
      - Add support for new devices
            + USB_MUX_2C2L    (USB/WiFi Device - 2 CAN 2ISO/LIN)
            + USB_MUX_DIAG_V2 (USB/WiFi Device - 2 CAN 4ISO/LIN)
      - Add Linux support
      - Add following function, especially for Linux :
            + MuxGlobalInit
            + MuxCreateEvent
            + MuxCloseEvent
            + MuxWaitOnEvent
            + MuxSetEvent
      - Correct a bug under Windows CE if more than one devices are connected, always access to the same device.
      - Add J18xxx functions

        V 5.49 12/10/2005	Alexandre GAMBIER / Nouredine BOUNEMOURA
      - Add new J18xxx function to the client dll aebridge.dll for using it with MUXServer.
      - Correct a bug in the CanGetBusState function.

        V 5.50 07/11/2005	Alexandre GAMBIER / Nouredine BOUNEMOURA
      - Correct a bug when using more than one USB device and close one. All other function returner STATUS_ERR_PARAM_USB.
      - Add support for the USB DEVICE ATR N°10201

        V 5.51 18/11/2005	Alexandre GAMBIER
      - Add functions :
            + MuxGetInformations
      - Add administration functions :
            + AdminOpenSession
            + AdminWriteConfig
            + AdminReadConfig

        V 5.52 03/02/2006	Alexandre GAMBIER
      - Add following macros for each network using wParam parameter in xxxConfigPeriodic functions
            + xxx_PERIODIC_PARAM_ENABLE
            + xxx_PERIODIC_PARAM_DISABLE
            + xxx_PERIODIC_PARAM_WITHEVENTS
            + xxx_PERIODIC_PARAM_NOEVENTS
	  - Add functions:
            + CanConfigPeriodicList
            + CanSendMsgList
            + VanConfigPeriodicList
            + VanSendMsgList
            + LinConfigPeriodicList
            + LinSendMsgList

        V 5.53 16/02/2006	Alexandre GAMBIER
      - Add support for the following devices :
            + EXXOClim

        V 5.54 16/02/2006	Alexandre GAMBIER, Nouredine BOUNEMOURA
      - Correct the value of the J18_BUSSPEED_4X enum
      - Add support for the following devices :
            + MAZDA (prototype)
      - Add functions
            + CanConfigClock (for new USb devices)
      - Change CanConfigBus function to bew fully compatible with all device.

        V 5.55 11/04/2006	Alexandre GAMBIER
      - Add new licence functions :
            + MuxIsLicenceActive
      - Add new Admin functions :
            + AdminGetLicenceCount
            + AdminReadLicences
            + AdminWriteLicences

        V 5.56 07/07/2006	Alexandre GAMBIER
      - Add support for new devices
            + USB_MUX_4C4L_FHS
            + USB_MUX_4C4L_MC			   
      - Add new error code
            + STATUS_ERR_LICENCE when the lending licence has expired.

        V 5.57 21/07/2006	Alexandre GAMBIER
      - Add new device
            + USB_PRESSURE_TESTSTAND
      - Add functions to perform file operation
            + FlashFileOpen
            + FlashFileClose
            + FlashFileRead
            + FlashFileWrite
            + FlashFileSeek
            + FlashFileTell
            + FlashFileGetSize
            + FlashGetInformations
            + FlashFindFirstFile
            + FlashFindNextFile
            + FlashFileDelete
            + FlashFileDownload
            + FlashFileRepair
            + FlashFormat
      - Add functions to get analogic register value
            + ANAGetInput
	  - Add new channel Propriotary
            + PryActivate
            + PryDeactivate
            + PryGetEvent
            + PrySetNotification
            + PryClearFifoRx
            + PryGetFifoRxLevel
      - Add new error codes
            + STATUS_ERR_SERVER_TIMEOUT
            + STATUS_ERR_SERVER_BUSY
            + STATUS_ERR_SERVER_FCTNOTSUPPORTED
      - Correct some bugs in the ISO function when the wBus parameter was greater than 4
      - Correct a compatibility bug on the AdminOpenSession function
      - Correct a bug into MuxGetInformations function.
        A zero was not always attend at the end of the serial number string.
      - When calling MuxFreeDLL some system objects were not closed

        V 5.58 22/01/2007	Nouredine BOUNEMOURA
      - Add functions for the NWL layer
            + NwlGetChannelCount
            + NwlChannelOpen
            + NwlChannelConfig
            + NwlChannelParam
            + NwlChannelAddr
            + NwlChannelStart
            + NwlChannelStop
            + NwlChannelClose
            + NwlSetNotification
            + NwlActivate
            + NwlIsBusActive
            + NwlDeactivate
            + NwlChannelSendMsg
            + NwlChannelReceiveMsg
            + NwlGetEvent
            + NwlGetFifoRxLevel
            + NwlGetChannelState
      - Add new LIN functions
            + LinConfigUart
      - Add new ISO functions
            + IsoConfigUart
            + IsoSetDataRxLevel
      - Add following error codes
            + STATUS_ERR_NWL_OPEN
            + STATUS_ERR_NWL_BUSY
      - Add following events
            + EVENT_NWL_MSGTX   
            + EVENT_NWL_MSGRX
            + EVENT_NWL_MSGTXERR
            + EVENT_NWL_MSGRXERR
            + EVENT_NWL_MSGRXFF
            + EVENT_NWL_MSGTXFF

        V 5.59 25/01/2007 Alexandre GAMBIER
      - Correct memory leak error when loading and closing muxdll.dll

        V 5.60 02/02/2007 Alexandre GAMBIER
      - Correct access violations when bus index was out of range.

        V 5.61 11/02/2007 Nouredine BOUNEMOURA / Alexandre GAMBIER
      - Minor changes in LIN functions
      - Remove the following device type which are obsoletes
            - USB_ART_10201
            - USB_EXXOCLIM
            - USB_MAZDA
            - USB_PRESSURE_TESTSTAND

        V 5.62 26/02/2007 Alexandre GAMBIER / Nouredine BOUNEMOURA
      - Add followings function
            - MuxGetDescription
            - MuxGetBuildNumber
      - Resurrection of dead products
            - USB_ART_10201
            - USB_EXXOCLIM
      - Minor change in the LIN layer for PCI devices
      - Add szRefProduct field in the tMuxInformations structure

        V 5.63 27/03/2007 Alexandre GAMBIER
      - Performance improved
      - Add following functions
            - USBLIB_GetDeviceList
            - USBLIB_Open
            - USBLIB_Close
            - USBLIB_GetPipesInfos
            - USBLIB_Send
            - USBLIB_Read
            - USBLIB_ReadCancel
            - SysSetNotification
            - SysGetEvent
            - MuxSetUserTimerFct
      - Add following event
            - EVENT_SYS_USBDEVICELOST	  	
      - Add following error codes
            - STATUS_ERR_NO_DEVICE
            - STATUS_ERR_DEVICE_NOT_OPENED

        V 5.64 16/04/2007	Alexandre GAMBIER
      - in MuxUsbGetCardInfo function the dwCardInfo parameter has been renaned as dwProductID
      - Correct a bug in the following functions :
            - LinConfigUart
            - IsoConfigUart

        V 5.65 20/04/2007	Alexandre GAMBIER
      - enhanced EXXOTest driver support

        V 5.66 03/05/2007	Alexandre GAMBIER
      - Enhanced USB 2.0 with EXXOTest driver
      - Enhanced packet size support for USB 2.0.

        V 5.67 14/05/2007 Nouredine BOUNEMOURA
      - Correct NWL Event error

        V 5.68 20/06/2007 Alexandre GAMBIER
      - Add support for Real Time Clock onboard, using :
            - tRTCValue structure
            - MuxGetRTCValue function
            - MuxSetRTCValue function

        V 5.69 25/07/2007 Alexandre GAMBIER
      - Correct access violation when opening more than one devices with the same dll.
      - Correct a bug in the MuxGetVersion function : VersionKernel was always set to 0.

        V 5.70 13/09/2007	Alexandre GAMBIER
      - Correct a bug with EXXOTest driver when opening several cards with same process
        some events were lost.

        V 5.71 26/10/2007 François-Georges REY
      - Add USB-MUX-DIAG-V2-HS support

        V 5.72 21/11/2007	Nouredine BOUNEMOURA / Alexandre GAMBIER
      - Add new ISO baudrate:
            - 19200
      - Add new ISO oper mode:
            - ISO_OPER_FREE
      - Add new functions :
            - CanConfigRangeFilter

        V 5.73 13/12/2007	Alexandre GAMBIER 
      - Add following structure
            - TTimingValue
            - TTimings
      - Add following function
            - MuxGetTimings
      - Add CAN error constants : CAN_ERROR_xxx

        V 5.74 08/02/2008	Cyril BOJIDAROVITCH
      - Improve FlashGetInformations for get :
            + Compact Flash Serial Number.
            + Compact Flash Model name.
            + Compact Flash PIO mode.

        V 5.75 18/02/2008	Cyril BOJIDAROVITCH
      - correct bug in NWC USB function call.

        V 5.76 19/03/2008	Vincent COMINOTTI / Cyril BOJIDAROVITCH
      - Add following functions :
            + USBLIB_WritePipe00
            + USBLIB_ReadPipe00
            + USBLIB_GetEndpointNumber
            + FlashFileCountSession
            + FlashFindFirstFileInFilter
            + FlashFindNextFileInFilter
        V 5.77 06/06/2008	Cyril BOJIDAROVITCH
      - Add following functions:
            + MuxWifiCountCards
            + MuxWifiGetCardInfo
            + MuxGetLastErrorEx

        V 5.78.4 15/09/08	Cyril BOJIDAROVITCH
      - Change timeout for all DLC clock function.
      - correct bug in WIFI (in muxopen, and NWL functions)
      - improve CanconfigPeriodic with buffer for configure frame.

        V 5.79 1/10/08 Cyril BOJIDAROVITCH
      - improve WIFI functions
      - correct WIFI integration in NWL
      - improve MuxClose for WIFI
      - use of EVENT_SYS_WIFIDEVICELOST
      - correct a bug in muxinit when no card connected (driver EXXO)

        V 5.80 25/09/2009	Cyril BOJIDAROVITCH
      - add following functions:
            + CanChangeBaudRate
      - add UNICODE support
      - correct MuxGetVersion (wrong KernelVersion return)
      - improve muxserver
      - correct bug in vandeactivate

        V 5.81 5/03/2010 Cyril BOJIDAROVITCH
      - Correct a bug in Windriver support.( CAN MAX up to 8 ==> rebuild mux_kp)
      - Change enum on CanSelectTransceiverHS.
      - Improve CanSelectTransceiverHS for support of CAN SINGLEWIRE for MUX_6C6L
      - Add type event EVENT_ANA_INPUT. make the difference between CAN event and ANA event.
      - Correct a HANDLE leak.
      - Add MuxGetHardwareID

        V 5.82 30/04/2010	Nouredine BOUNEMOURA & Cyril BOJIDAROVITCH
      - Add LIN 2.x missing features for PCI boards (only protocol part).
      - Improve management of shared memory

        V 5.83 02/06/2010 Nouredine BOUNEMOURA / Cyril BOJIDAROVITCH
      - Add CanReadMsg && CanWriteMsg.
      - Correct a memory leak in MuxGetInformations
      - correct a memory leak in UsbScanDevice

        V 5.84 (old drivers) 13/07/2010 Cyril BOJIDAROVITCH
      - Add 10400 baudrate on LIN for PCI card.
      - Add MuxgetHardwareId support in Muxserver.

        V 5.85 (old drivers) 01/09/2010 Cyril BOJIDAROVITCH
      - Change define for CVI
      - Add function for ETH support.

        V 5.86 (old drivers) 08/10/2010 Cyril BOJIDAROVITCH
      - Add support of CanChangeBaudRate for 6C6L.
      - Improve drivers for 6C6L support

        V 5.87 (old drivers) 29/10/2010 Cyril BOJIDAROVITCH
      - Improve max licence number.

        V 5.88 (old drivers) 15/11/2010 Cyril BOJIDAROVITCH
      - Add 4C4L support.
      - Improve drivers version for 4C4L

        V 5.89 (old drivers) 11/02/2011 Cyril BOJIDAROVITCH / Vincent COMINOTTI / Nouredine BOUNEMOURA / David PROVENT
      - Improve FlashFile function for Windows Vista and Seven.
      - Correct LIN 2.X management for PCI boards
      - Add 38400 baudrate on LIN for PCI card.
      - Add additional length byte option for ISO14230 messages less than 64 bytes
      - Add new ISO speed

        V 5.90 (old drivers) 02/03/2011 Cyril BOJIDAROVITCH
      - Correct CanconfigBus for the bus load calculation

        V 5.91 (old drivers) 12/05/2011 Cyril BOJIDAROVITCH
      - Add J1939 function.

        V 5.92 (old drivers) 29/06/2011 Cyril BOJIDAROVITCH
      - Add NwcSetBytePadding function

        V 5.93 (old drivers) 25/07/2011 Cyril BOJIDAROVITCH
      - Add NMEA2000 support

        V 6.00 (new driver) 19/04/2010 Cyril BOJIDAROVITCH
      - Add support of Windows 64 bits architecture.
      - Porting Muxdll On visual Studio.
	
        V 6.01 (new driver) 10/05/2010 Cyril BOJIDAROVITCH
      - Add some fonctionnality in driver.

        V 6.02 (new driver) 03/06/2010
      - Send preRelease for some test.

        V 6.03 (new driver) 01/07/2010 Cyril BOJIDAROVITCH
      - Add CanReadMsg && CanWriteMsg.

        V 6.04 (new driver) 19/07/2010 Cyril BOJIDAROVITCH
      - Powers fonctions Added to the drivers.
      - Add some internals fonctions.
      - Correct a size error on Win2k.

        V 6.05 (new driver) 26/07/2010 Cyril BOJIDAROVITCH
      - Improve efficiency in spy mode.
      - On client software crash, unplug device is no longer necessary.

        V 6.06 (new driver) 18/08/2010 Cyril BOJIDAROVITCH
      - Correct a memory leak in MuxLoadDLL.

        V 6.07 (new driver) 31/08/2010 Cyril BOJIDAROIVTCH
      - Correct a bug in MuxGetVersion.
      - Add MuxSetEthernet & MuxGetEthernet functions.

        V 6.08 (new driver) 07/10/2010 Cyril BOJIDAROVITCH
      - Add support of CanChangeBaudRate for 6C6L.

        V 6.09 (new driver) 29/10/2010 Cyril BOJIDAROVITCH
      - Improve max licence number. 

        V 6.10 (new driver) 15/11/2010	Cyril BOJIDAROVITCH
      - Add support of 4C4L.

        V 6.11 (new driver) 11/02/2011	Cyril BOJIDAROVITCH / Vincent COMINOTTI / Nouredine BOUNEMOURA / David PROVENT
      - Correct LIN 2.X management for PCI boards
      - Add additional length byte option for ISO14230 messages less than 64 bytes
      - Add new LIN / ISO speed

        V 6.12 (new driver) 02/03/2011 Cyril BOJIDAROVITCH
      - Correct CanconfigBus for the bus load calculation 

        V 6.13 (new driver) 12/05/2011 Cyril BOJIDAROVITCH
      - Add J1939 protocol.

        V 6.14 (new driver) 07/06/2011 Cyril BOJIDAROVITCH
      - Add NwcSetBytePadding function

        V 6.15 (new driver) 25/07/2011 Cyril BOJIDAROVITCH
      - Add NMEA2000 support

        V 6.16 28/10/2011 Nouredine BOUNEMOURA
      - End of support for Exxotest v1.x.x and Jungo v5.2.2 USB drivers
      - Support now Exxotest USB v2.x.x & above, Jungo PCI v6.0.3 (Kernel Plugin v1.2.4, VXD 4.34)
      - Remove cards counting from MuxInit, MuxPciGetCardInfo and MuxUsbGetCardInfo
      - Dynamically load Winsock 2 and IP Helper DLLs at main entry
      - Change MuxEthCountCards and add new function MuxEthGetCardInfo
      - Change MuxOpen & MuxClose for Ethernet cards (wired and wireless), update IP routing table if necessary
      - MuxWifiCountCards & MuxWifiGetCardInfo deprecated : use MuxEthCountCards & MuxEthGetCardInfo instead
      - Minor change in EEPROM initialization routine for PCI boards
      - MuxGetHardwareID function valid only for USB cards
      - CAN error events of same type now signaled only once per ms (PCI boards)
      - Minor change for LIN IFR handling (PCI boards)
      - Correction in length management for ISO 9141 & ISO 14230 protocols (PCI boards)
      - Add new function NMEA0183ConfigUart

        V 6.17 07/12/2011 Nouredine BOUNEMOURA
      - All USB drivers workable (Exxotest v1.x.x/v2.x.x and Jungo v6.0.3)
      - Dynamically load extern DLLs during execution (only when needed and no more at main entry)
      - Ensure that all allocated resources are freed when DLL is being unloaded
      - Minors corrections in the FlashFileDownload function
      - Add extra informations to LIN events : checksum and protected identifier
      - Add 64 bits version of the MUXDLL library

        V 6.18 14/12/2011 Nouredine BOUNEMOURA
      - Add version number for Exxotest USB drivers
      - Correct index of the configuration's interface to be registered for USB data transfer
      - Correct a parameter passed to the ETH data transfer function

        V 6.19 22/06/2012 Nouredine BOUNEMOURA
      - Fix MuxGetBuildNumber function
      - Start migration to Jungo WDU library
      - Minors corrections in the MuxOpen function
      - Support of the opening of non multiplexed Ethernet cards
      - TCP sockets are now placed in non-blocking mode
      - The wCard parameter is now correctly checked in the MuxEthGetCardInfo function
      - Change the handling of CAN periodic frames to correct some minor bugs (PCI boards) 
      - Support commands whose response has unknown size
      - Minors changes in FlashGetInformations and FlashFileDownload functions
      - Fix the position numbers in IO events (for edge-triggered inputs)
      - Change the calling convention for all J1939 functions, add J19ChannelParam and correct a memory leak
      - General code cleanup

        V 6.20 28/01/2013 Nouredine BOUNEMOURA
      - Minor change in FlashGetInformations function
      - Change default timeout value to 5s for wireless ethernet cards
      - Remove counter used for opening and closing USB driver
      - All CAN clock frequencies are now supported for non multiplexed cards
      - MuxPciCountCards, MuxUsbCountCards and MuxEthCountCards are now thread safe again
      - MuxInit will now fail if the card is in the opened state (may be forced by setting MSB of wCard parameter)
      - Changes in MuxEthCountCards function to differentiate between wired and wireless cards
      - Changes in the way of opening and closing ethernet cards
      - Some resources are not freed anymore when MuxClose is called as a result of process termination

        V 6.21 31/05/2013 Nouredine BOUNEMOURA / Alexandre GAMBIER / François-Georges REY
       - Add support for a new device
            + USB_MUX_DIAG_V2_LT (USB Device - 1 CAN 1 ISO/LIN)
       - Add new Admin functions :
            + AdminGetLicenceData
            + AdminSetLicenceData
            + AdminReadLicencesData
            + AdminWriteLicencesData
       - Minor changes to AdminReadLicences and AdminWriteLicences functions
       - Add a new function to stop the read thread of Exxotest v2.x.x USB driver (when required)
       - Fix a problem with the initialization of the TX FIFO for ISO 9141 & ISO 14230 protocols
       - Change to MuxEthCountCards: for wireless networks, send several times the counting datagram

        V 6.30 21/05/2014 Nouredine BOUNEMOURA
       - Update Jungo Windriver to version 8.02 and add 64-bit support for PCI boards
       - Change to AdminWriteLicencesData: accept NULL parameters to enable erase of the last remaining licence data
       - Change to MuxEthCountCards: enhance the processing of received datagrams
       - Unload extern DLLs after execution (MuxOpen, MuxClose and MuxEthCountCards) 
       - Minor changes to the formatting of the last error string
       - Remove the keyword 'HANDLE' from the header file and change the definition of '_MUXAPI'
       - J19ChannelSendMsg & J19ChannelSendNMEAFastPacket functions send now variable-length messages
       - Fix a closing issue after opening a J1939 channel
       - Fix a closing issue after opening a PCI card
       - Fix a memory leak when scanning the USB bus fails (Exxotest v1.x.x/v2.x.x drivers)
       - Fix the CARB mode of the Iso14230SendMsg function 

        V 6.31 11/12/2014 Nouredine BOUNEMOURA
       - Fix the alignment of structures for the 32-bit version of the library
       - Fix the handling of a LIN IFR by a 1.x master (PCI boards)
       - Fix the packet reassembly algorithm of the reading thread

        V 6.32 12/12/2014 Nouredine BOUNEMOURA
       - Fix the return value of MuxGetHardwareID function

        V 6.33 01/07/2015 Nouredine BOUNEMOURA
       - Change packing alignment value for 64-bit applications
       - Add the location ID information for each item in the USB card list
       - Fix some output parameters in the functions MuxPciGetCardInfo & MuxUsbGetCardInfo
       - Fix dependency problems between the functions MuxPciCountCards, MuxUsbCountCards, MuxEthCountCards & MuxOpen
       - Add the device instance ID to the multistring value returned by the function MuxGetHardwareID
       - ISO15765-2: fix an issue for the parameter N_AE when using mixed addressing
       - ISO15765-2: mixed addressing is now supported for 11 bit CAN identifier
       - ISO15765-2: add a new spy mode working on a per-channel basis

        V 6.34 02/09/2015 Nouredine BOUNEMOURA
       - Fix an issue when calling the function USBLIB_GetDeviceList more than seven times
       - Update some strings used for the last-error code

        V 6.35 13/11/2015 Nouredine BOUNEMOURA
       - Fix an issue when mixing multiplexed and non multiplexed USB cards
       - Change the declaration specifier and calling convention for the GNU compiler
*/

#ifndef _REFMUX_H_
#define _REFMUX_H_
 
//	Dont forget to call MuxGetBuildNumber function to get information about the timestamp of the build
#define MUX_DLL_VERSION     0x635          // DLL version

#if defined(_WIN64) || defined(_LP64) || defined(__LP64__)
#pragma pack(push,8) 	  			        // 8-byte alignment
#else
#pragma pack(push,2) 	  			        // 2-byte alignment: MSVC & Borland
#endif

#ifdef  __BORLANDC__
#pragma option push -b                      // Treat enums on 4 bytes
#endif

#ifdef LINUX
#ifndef INFINITE
	#define	INFINITE		-1			// Infinite time out
#endif	// INFINITE
#endif	// LINUX

#ifdef MUX_EXPORT_DLL
	#ifndef LINUX
		#define _MUXSPEC __declspec(dllexport) 
		#define _MUXAPI __stdcall 
	#else
		#define _MUXSPEC
		#define _MUXAPI
	#endif	// LINUX
#else
	#ifdef LINUX
		#define _MUXSPEC
		#define _MUXAPI
	#else
		#if defined __BORLANDC__
			#define _MUXSPEC __declspec(dllimport)
			#define _MUXAPI __stdcall
		#elif defined _MSC_VER
			#define _MUXSPEC
			#define _MUXAPI
		#elif defined _CVI_
			#define _MUXSPEC
			#define _MUXAPI __stdcall
		#elif defined __GNUC__
			#define _MUXSPEC __declspec(dllimport)
			#define _MUXAPI __stdcall
		#endif
	#endif
#endif

/*******************************************************************************
; Macros générales	// Main macros
*******************************************************************************/
#ifndef _MUXALIGN
#ifndef _WIN32_WCE
#define	_MUXALIGN
#else
#define	_MUXALIGN			__unaligned
#endif
#endif

#ifndef _WIN32_WCE
#define	REFMUX_STR(s)		s
#else
#define	REFMUX_STR(s)		_T(s)		/* Convertir le (char*) en (unsigned short*) // Cast (char*) into (unsigned short*) */
#endif // _WIN32_WCE

#ifdef _UNICODE
	#define		_MUXDLLBIN_STR	L".\\bin\\muxdll.dll"
	#define		_MUXDLLCUR_STR	L".\\muxdll.dll"
	#define		_MUXDLL_STR		L"muxdll.dll"
	#define		_MUTEX_NAME		L"SERVERMUX_MUTEX_SERVERISRUNNING"
	#define		_AEBRDGBIN_STR	L".\\bin\\AEBRIDGE.dll"
	#define		_AEBRDGB_STR	L"AEBRIDGE.dll"
#else
	#ifdef UNICODE
		#define		_MUXDLLBIN_STR	L".\\bin\\muxdll.dll"
		#define		_MUXDLLCUR_STR	L".\\muxdll.dll"
		#define		_MUXDLL_STR		L"muxdll.dll"
		#define		_MUTEX_NAME		L"SERVERMUX_MUTEX_SERVERISRUNNING"
		#define		_AEBRDGBIN_STR	L".\\bin\\AEBRIDGE.dll"
		#define		_AEBRDGB_STR	L"AEBRIDGE.dll"
	#else
		#define		_MUXDLLBIN_STR	".\\bin\\muxdll.dll"
		#define		_MUXDLLCUR_STR	".\\muxdll.dll"
		#define		_MUXDLL_STR		"muxdll.dll"
		#define		_MUTEX_NAME		"SERVERMUX_MUTEX_SERVERISRUNNING"
		#define		_AEBRDGBIN_STR	".\\bin\\AEBRIDGE.dll"
		#define		_AEBRDGB_STR	"AEBRIDGE.dll"
	#endif
#endif
/*******************************************************************************
; Déclaration pour les routines générales // main definition
*******************************************************************************/
typedef enum
{
	STATUS_OK               			= 1,			/* OK */
	STATUS_ERR_OPEN         			= 2,			/* Erreur ouverture handle sur carte             // Denies access to board */
	STATUS_ERR_OPENKP       			= 3,			/* Erreur ouverture handle sur driver kernel     // Denies access to the kernel driver */
	STATUS_ERR_MEMORY       			= 4,			/* Erreur d'allocation mémoire                   // Not enough memory */
	STATUS_ERR_PARAM        			= 5,			/* Erreur de paramètre d'entrée                  // Input parameters error */
	STATUS_ERR_SEQUENCE     			= 6,			/* Erreur d'enchainement des commandes           // Sequence error */
	STATUS_ERR_BANK         			= 7,			/* Erreur d'allocation de banc mémoire           // Denies access to Memory bank */
	STATUS_ERR_INTERRUPT    			= 8,			/* Erreur d'autorisation des ITs                 // Error while allocating interrupt */
	STATUS_ERR_MSGEXCEED    			= 9,			/* Erreur nombre de messages déclaré trop grand  // Message count has exceeded the maximum */
	STATUS_ERR_MSGEXIST     			= 10,			/* Erreur l'id déclaré existe déjà               // Identifier has already been declared */
	STATUS_ERR_MSGSVC       			= 11,			/* Service non supporté                          // Service message is not supported */
	STATUS_ERR_MSGBUSY      			= 12,			/* Erreur message en cours de transmission       // Message is already transmitted (buffer mode only) */
	STATUS_ERR_TSSOVER      			= 13,			/* Erreur dépassement mémoire ou canaux du TSS   // Memory or channel count has reached */
	STATUS_ERR_HANDLE       			= 14,			/* Erreur handle de communication                // Invalid message handle */
	STATUS_ERR_FIFOFULL     			= 15,			/* Fifo de transmission pleine                   // Tx FIFO is full */
	STATUS_ERR_BUSOFF       			= 16,			/* Erreur bus déconnecté                         // CAN bus off */
	STATUS_ERR_FILEDLL      			= 17,			/* Erreur de fichier DLLs                        // DLL file error */
	STATUS_ERR_OPENDLL      			= 18,			/* Erreur d'initialisation des DLLs              // DLL call error */
	STATUS_ERR_BOARD        			= 19,			/* Type de carte non supporté                    // Board is not supported by DLL */
	STATUS_WARNING          			= 20,			/* Avertissement, fonction non supportée         // Warning - function is not supported */
	STATUS_ERR_TO_USB       			= 21,			/* Erreur de communication sur l'USB             // USB communication error */
	STATUS_ERR_SEQ_USB      			= 22,			/* Erreur de communication sur l'USB             // USB communication error */
	STATUS_ERR_PARAM_USB    			= 23,			/* Erreur de communication sur l'USB             // USB communication error */
	STATUS_ERR_FLASH        			= 24,			/* Erreur de programmation de la flash           // USB flash error */
#ifdef _WIN32_WCE	// Under Windows CE the STATUS_NOT_SUPPORTED is already defined
	STATUS_UNSUPPORTED      			= 25,			/* Requête non supportée                         // Not supported function */
#else
	STATUS_NOT_SUPPORTED    			= 25,			/* Requête non supportée                         // Not supported function */
#endif	//  _WIN32_WCE
	STATUS_ERR_REGISTER     			= 26,			/* Requête non enregistrée                       // No registered function */
	STATUS_ERR_NWC_OPEN     			= 27,			/* Erreur d'ouverture du canal NWC               // NWC channel open error */
	STATUS_ERR_NWC_BUSY     			= 28,			/* Erreur d'ouverture du canal NWC               // NWC channel open error */
	STATUS_ERR_ALREADY_OPEN 			= 29,			/* Erreur device déjà ouvert                     // Device already open error */
	STATUS_ERR_FUNCTION     			= 31,			/* Erreur sur la fonction                        // Function error */
	STATUS_ERR_ALIGNMENT    			= 32,			/* Erreur d'alignement                           // alignment error */
	STATUS_ERR_SERVERNOTLOADED			= 33,			/* Le serveur n'est pas chargé                   // Server is not loaded */
	STATUS_ERR_TIMEOUT					= 34,			/* Timeout atteint                               // Timeout has occured */
	STATUS_ERR_LICENCE					= 35,			/*	La licence de prêt est expirée				//		*/
	STATUS_ERR_TOOMANYFILEOPENED		= 36,			/* Trop de ficher sont ouvert sur la flash		// Too many files are opened on the flash */
	STATUS_ERR_FILEACCESS				= 37,			/* Impossible d'accéder au fichier				// Can not access to file */
	STATUS_ERR_FILENOTOPENED			= 38,			/* Fichier non ouvert							// File not opened */
	STATUS_ERR_NOCFCARD 				= 39,			/*	Pas de carte compact flash					// No compactcard flash */
	STATUS_CANCELLED 					= 40,			/*	Annulée									//	Cancelled */
	STATUS_COMMANDE_IN_PROGRESS			= 41,			/* Commande en progression */
	STATUS_COMMANDE_ALREADY_OPENED 		= 42,  			/* La commande a déjà en cours... */
	STATUS_ERR_CF_FORMAT				= 43,			/* Erreur lors du formatage de la carte compactflash */
	STATUS_ERR_SERVER_TIMEOUT			= 44,			/* Timeout en communicant avec le serveur */
	STATUS_ERR_SERVER_BUSY				= 45,			/* Le serveur semble occupé */
	STATUS_ERR_SERVER_FCTNOTSUPPORTED 	= 46,			/* Fonction non supporté en mode serveur */
	STATUS_ERR_NWL_OPEN					= 47,			/* Erreur d'ouverture du canal NWL               // NWL channel open error */
	STATUS_ERR_NWL_BUSY					= 48,			/* Erreur d'ouverture du canal NWL               // NWL channel open error */
	STATUS_ERR_NO_DEVICE				= 49,			/* Pas de périphérique connecté					//	No connected devices */
	STATUS_ERR_DEVICE_NOT_OPENED		= 50,			/* Périphérique non ouvert					//	Device not opened */
  	STATUS_FILE_FOUND					= 51,			/* Fichier trouvé (enregisteur)            // File Found (datalogger)*/
	STATUS_ERR_CFCARD_BUSY	= 52			/* Carte en cours d'utilisation (enregisteur)            // CF Card busy (datalogger)*/

} tMuxStatus;

typedef enum
{
	MODE_APPLI    = 0,                      /* Mode application                         // Application mode */
	MODE_KERNEL   = 1,                      /* Mode kernel                              // Kernel mode */
	MODE_DEMO     = 2,                      /* Mode démonstration (sans carte)          // Demonstration mode (without board) */
	MODE_MUXTRACE = 3                       /* Mode MuxTrace                            // MuxTrace mode */
} tMuxMode;

typedef struct
{
    tMuxMode        eMuxMode;           /* Mode de fonctionnement interne               // Internal mode */
    unsigned short  wBusInterface;      /* Mode d'interface (Individuel ou groupé)      // Interface mode */
} tMuxConfigMode;

typedef struct
{
    unsigned long   dwUSBPacketCount;   /* Nombre de paquet USB recu                    // USB transfer packet count */
    unsigned long   dwUSBByteCount;     /* Nbre d'octet USB recu                        // USB transfer byte count  */
} tMuxInternalInfo;

typedef enum
{
	EVENT_EMPTY					=   0x0,      /* Pas d'événement présent                                    // No event*/
	EVENT_ANA_INPUT				=   0x0D,	  /* information entré ANA										// Input ANA information */
    EVENT_PWM_INPUT				=   0x0E,     /* Informations entrée PWM                                    // Input PWM information */
    EVENT_IO_INPUT				=   0x0F,     /* Changement d'état d'une entrée                             // Input edge detcted */
	EVENT_CAN_MSGTX				=   0x10,     /* Fin de transmission                                        // End of transmission */
    EVENT_CAN_MSGRX				=   0x11,     /* Réception                                                  // Message has been received */
    EVENT_CAN_ERROR				=   0x12,     /* Erreur bus                                                 // Bus error */
    EVENT_CAN_BUSCHANGE			=   0x13,     /* Chgt d'état du comp. (active,passive,busoff)               // Chip state has chaged active or passive error ou bus off*/
    EVENT_CAN_BUSLOAD			=   0x14,     /* Information charge bus courante                            // Bus load information  */
    EVENT_VAN_MSGTX				=   0x20,     /* Fin de transmission                                        // End of transmission */
	EVENT_VAN_MSGRX				=   0x21,     /* Réception                                                  // Message has been received */
    EVENT_VAN_MSGTXERR			=   0x22,     /* Fin de transmission en erreur                              // End of transmission with error */
    EVENT_VAN_MSGRXERR			=   0x23,     /* Erreur de réception                                        // Rx error */
    EVENT_VAN_BUSCHANGE			=   0x24,     /* Changement de la ligne de réception                        // Communication indication  */
    EVENT_VAN_BUSLOAD			=   0x25,     /* Information charge bus courante                            // Bus load information  */
	EVENT_ISO_MSGTX				=   0x30,     /* Fin de transmission                                        // End of transmission */
	EVENT_ISO_MSGRX				=   0x31,     /* Réception                                                  // Message has been received */
    EVENT_ISO_MSGTXERR			=   0x32,     /* Fin de transmission en erreur                              // End of transmission with error */
    EVENT_ISO_MSGRXERR			=   0x33,     /* Erreur de réception                                        // Rx error */
    EVENT_ISO_BUSLOAD			=   0x34,     /* Information charge bus courante                            // Bus load information  */
    EVENT_ISO_ERROR				=   0x35,     /* Erreur bus                                                 // Serial communication error */
    EVENT_ISO_RXCHAR			=   0x36,     /* Réception d'un caractère                                   // Character has been received */
    EVENT_LIN_MSGTX				=   0x40,     /* Fin de transmission                                        // End of transmission */
    EVENT_LIN_MSGRX				=   0x41,     /* Réception                                                  // Message has been received */
    EVENT_LIN_MSGTXERR			=   0x42,     /* Fin de transmission en erreur                              // End of transmission with error */
    EVENT_LIN_MSGRXERR			=   0x43,     /* Erreur de réception                                        // Rx error */
    EVENT_LIN_BUSCHANGE			=   0x44,     /* Changement do contrôleur                                   // Communication indication  */
    EVENT_LIN_BUSLOAD			=   0x45,     /* Information charge bus courante                            // Bus load information  */
    EVENT_NWC_MSGTX				=   0x50,     /* Fin de transmission                                        // End of transmission */
    EVENT_NWC_MSGRX				=   0x51,     /* Réception                                                  // Message has been received */
    EVENT_NWC_MSGTXERR			=   0x52,     /* Fin de transmission en erreur                              // End of transmission with error */
    EVENT_NWC_MSGRXERR			=   0x53,     /* Erreur de réception                                        // Rx error */
    EVENT_NWC_MSGRXFF			=   0x54,     /* Réception d'une FF                                         // First frame indication */
    EVENT_NWC_MSGTXFF			=   0x55,     /* Début de transmission d'une FF                             // First frame start of transmission */
	EVENT_J1587_MSGTX			=   0x60,     /* Fin de transmission                                        // End of transmission */
	EVENT_J1587_MSGRX			=   0x61,     /* Réception                                                  // Message has been received */
    EVENT_J1587_BUSCHANGE		=   0x62,     /* Changement do contrôleur                                   // Communication indication  */
    EVENT_J1587_BUSLOAD			=   0x63,     /* Information charge bus courante                            // Bus load information  */
    EVENT_NMEA0183_MSGTX		=   0x70,     /* Fin de transmission                                        // End of transmission */
    EVENT_NMEA0183_MSGRX		=   0x71,     /* Réception                                                  // Message has been received */
    EVENT_NMEA0183_MSGTXERR		=   0x72,     /* Fin de transmission en erreur                              // End of transmission with error */
	EVENT_NMEA0183_MSGRXERR		=   0x73,     /* Erreur de réception                                        // Rx error */
    EVENT_NMEA0183_BUSCHANGE	=   0x74,     /* Changement do contrôleur                                   // Communication indication  */
    EVENT_NMEA0183_BUSLOAD		=   0x75,     /* Information charge bus courante                            // Bus load information  */
	EVENT_WINCE_BATTSTATE		=	0x80,     /* Information sur l'état de la batterie                      // Battery state information */
	EVENT_WINCE_POWERDOWN		=   0x81,     /* L'alimentation passe en veille                             // Power is going down */
	EVENT_WINCE_POWERRESUME		=	0x82,     /* L'alimentation se réveille                                 // Power is going up */
	EVENT_WINCE_DRIVERUNLOADED	=	0x83,     /* Le driver a été déchargé, il faut recharger la muxdll.dll  // Driver has been unload, the muxdll.dll file must be fully reload */
	EVENT_J18_MSGTX             =   0x90,     /* Fin de transmission                          // End of transmission */
    EVENT_J18_MSGRX             =   0x91,     /* Réception                                    // Message has been received */
    EVENT_J18_MSGRXERR          =   0x92,     /* Erreur                                       // Error */
    EVENT_PRY_MSGTX             =   0xA0,     /* Fin de transmission                          // End of transmission */
    EVENT_PRY_MSGRX             =   0xA1,     /* Réception                                    // Message has been received */
	EVENT_NWL_MSGTX				=   0xB0,     /* Fin de transmission                          // End of transmission */
	EVENT_NWL_MSGRX				=   0xB1,     /* Réception                                    // Message has been received */
	EVENT_NWL_MSGTXERR			=   0xB2,     /* Fin de transmission en erreur                // End of transmission with error */
	EVENT_NWL_MSGRXERR			=   0xB3,     /* Erreur de réception                          // Rx error */
	EVENT_NWL_MSGRXFF			=   0xB4,     /* Réception d'une FF                           // First frame indication */
	EVENT_NWL_MSGTXFF			=   0xB5,     /* Début de transmission d'une FF               // First frame start of transmission */
	EVENT_J19_MSGTX				=	0xC0,     /* Fin de transmission                                        // End of transmission */
	EVENT_J19_MSGRX				=	0xC1,     /* Réception                                                  // Message has been received */
	EVENT_J19_MSGTXERR			=	0xC2,     /* Fin de transmission en erreur                              // End of transmission with error */
	EVENT_J19_MSGRXERR			=	0xC3,     /* Erreur de réception                                        // Rx error */
	EVENT_J19_MSGRXFF			=	0xC4,     /* Début de transmission d'une FF                             // First frame start of transmission */
	EVENT_J19_MSGTXFF			=	0xC5,     /* Début de transmission d'une FF                             // First frame start of transmission */
    EVENT_TIMER					=   0x100,    /* Timer applicatif                                           // Application timer */
    EVENT_TIMEERROR				=   0x101,    /* Information perte d'interruption timer                     // Time error detection */
    EVENT_TRIGGER				=   0x200,	  /* Evénement trigger							                // Trigger event */
	EVENT_INTERNAL				=   0x201,	  /* Evénement interne							                // Internal event */
	EVENT_SYS_USBDEVICELOST		=	0x300,		/*	On a perdu la com avec le périphérique USB			//	We lost the usb device link */
	EVENT_SYS_WIFIDEVICELOST	=	0x301,		/*	On a perdu la com avec le périphérique WIFI			//	We lost the WIFI device link */
	EVENT_FIFO_OVF				=   0x8000,		/* Bit indiquant une perte de message                         // Message lost cause fifo overflow */
} tMuxTypeEvent;

typedef enum
{
	xxx_MUX_UNREACHABLE	 	=   0xFC,           //	Carte non accessible                         //	Card unreachable
	xxx_MUX_SIMU	 		=   0xFD,           //	Simulation d'une carte MUX                   //	Card simulator
	xxx_MUX_UNKNOWN	 		=   0xFE,           //	Inconnu                                      //	Unknown
	PCI_MUX_DEMO			=   0xFF,           //	Pas de materiel                              // No card
	PCI_MUX_C3V2L			=   0x00,           //	Carte PCI 1 CAN, 3 VAN et 2 LIN/ISO9141      // PCI board 1 CAN, 3 VAN and 2 ISO9141/LIN channels
	PCI_MUX_CVL				=   0x01,           //	Carte PCI 1 CAN, 1 VAN et 1 LIN/ISO9141      // PCI board 1 CAN, 1 VAN and 1 ISO9141/LIN channels
	PCI_MUX_CAN				=   0x02,           //	Carte PCI 1 CAN                              // PCI board 1 CAN channel
	PCI_MUX_VAN				=   0x03,           //	Carte PCI 1 VAN                              // PCI board 1 VAN channel
	PCI_MUX_MultiCAN		=   0x08,           //	V 2.0 Carte PCI 4 CAN                        // PCI board 4 CAN channels
	USB_MUX_C3VL			=   0x10,           //	Carte USB 1 CAN, 3 VAN et 1 LIN              // USB board 1 CAN, 3 VAN and 1 LIN channel
	USB_CL500				=   0x11,           //	Carte USB CL500  1 CAN et 1 ISO9141    	     // USB board 1 CAN, 1 ISO9141 channel
	USB_MUX_CL				=   0x12,           //	Carte USB 1 CAN et 1 LIN                     // USB board 1 CAN channel and 1 LIN channel
	USB_OBD_EX1				=   0x13,           //	Carte USB OBD-EX1  1 CAN et 1 ISO9141 	     // USB board 1 CAN, 1 ISO9141 channel
	USB_CM					=   0x14,           //	Carte USB CM       1 CAN et 1 ISO9141 	     // USB board 1 CAN, 1 ISO9141 channel
	USB_MUX_4C2L			=   0x18,           //	Carte USB 4 CAN et 2 LIN                     // USB board 4 CAN channels and 2 LIN channels
	USB_MUX_4C4IJ			=   0x20,           //	Carte USB 4 CAN, 4 ISO9141 et 1 J1587        // USB board 4 CAN, 4 ISO9141 and 1 J1587 channel
	USB_MUX_DIAG			=   0x21,           //	Carte USB 2 CAN, 4 ISO9141                   // USB board 2 CAN and 4 ISO9141 channels
	USB_MUX_CV32A			=   0x22,           //	Carte USB 1 CAN, 1VAN ,1 ISO9141 et 32 ANA   // USB board 1 CAN, 1 VAN, & ISO9141 channels and 32 analog channels
	USB_MUX_2C2L			=   0x23,           //	Carte USB/WIFI 2 CAN, 2 ISO9141/LIN          // USB/WIFI board 2 CAN, 2 ISO9141/LIN
	USB_MUX_DIAG_V2			=   0x24,           //	Carte USB/WIFI 2 CAN, 4 ISO9141/LIN, 2 J1850 // USB/WIFI board 2 CAN, 4 ISO9141/LIN and 2 J1850 channels
	USB_ART_10201			=   0x25,           //  Carte USB 1 CAN et 3 ISO9141                 // USB board 1 CAN, 3 ISO9141 channels */
	USB_EXXOCLIM			=   0x26,			//  EXXOClim
	USB_MUX_4C4L_FHS		=	0x28,			//	Carte USB 4 CAN, 4 ISO9141 (HighSpeed)
	USB_MUX_4C4L_MC 		=	0x29,			//	Carte USB 4 CAN, 4 ISO9141 (MixedCAN)
	USB_MUX_6C6L			=	0x2A,			//	Carte USB/ETHERNET 6 CAN 6 ISO9141/LIN
	USB_MUX_4C4L			=	0x2B,			//	Carte USB 4 CAN 4 ISO9141/LIN 				 // USB board 4 CAN 4 ISO9141/LIN
	USB_MUX_DIAG_V2_LT		=   0x2C,           //	Carte USB 1 CAN et 1 ISO9141/LIN             // USB board 1 CAN and 1 ISO9141/LIN
	USB_PID					=	0x8000			//	USB device
} tMuxHWType;


#define	MUXALIGNEMENT_8BITS_TESTVALUE		0x80
#define	MUXALIGNEMENT_16BITS_TESTVALUE		0x8000
#define	MUXALIGNEMENT_32BITS_TESTVALUE		0x80000000
#define	MUXALIGNEMENT_ENUM_TESTVALUE		STATUS_ERR_FILEDLL

typedef struct
{
	unsigned char	b8Bits;				// unsigned 8 bits value
    unsigned long   dw32Bits;			// unsigned 32 bits value
	tMuxStatus		eEnum;				// Enum type
    unsigned short	w16Bits;			// unsigned 16 bits value
} tMuxAlignment ;

typedef enum
{
	CSMODE_DISABLED	=	0,			// Client/Server is disabled
	CSMODE_ENABLED	=	1			// Client/Server is enabled
} tMuxCSMode ;

typedef struct
{
	char			szSerialNumber[ 16 ];	//	Numéro de série du produits
	char			szRefProduct[ 16 ];		//	Référence produit
	unsigned char	pbReserved[ 218 ];
} tMuxInformations ;

typedef enum
{
	LICLOCK_UNKNOWN					=	0,	 	//	Raison inconnu
	LICLOCK_EXPIRED					=	1,	 	//	La durée d'utilisation de la licence est expirée
	LICLOCK_INVALIDTIME				=	2, 		//	L'heure du jour est fausse (on a essayé de reculer les jours pour gagner du temps)
	LICLOCK_NOTYETACTIVATED			=	3, 		//	La licence n'a jamais été activée
	LICLOCK_EEPROMACCESS			=	4, 		//	Erreur lors de l'accès à l'eeprom contenant les licences
	LICLOCK_CURRENTTIMEUNKNOWN		=	5, 		//	L'heure du jour est inconnue
	LICLOCK_MANUALLOCK				=	6,		//	Blocage manuel
	LICLOCK_CURRENTHOSTIDUNKNOWN	=	7,		//	L'equipement en cours est inconnu
	LICLOCK_INVALIDHOSTID			=	8		//	L'équipement associé ne correspond pas
} tMuxLicenceLock ;

typedef struct
{
	unsigned short	wHour;						//	Heure							//	Hou
	unsigned short	wMinute;					//	Minute							//	Minutes
	unsigned short	wDay;						//	Jour							//	Day
	unsigned short	wMonth;						//	Mois de 1 à 12					// Month from 1 to 12
	unsigned long	dwYear;						//	Année							//	Year
} tMuxLicenceDate ;

typedef struct
{
	unsigned short 	wActivated;			//	La licence est active ?						//	Is the licence activated ?
	tMuxLicenceLock	eLock;				//	Raison si une licence n'est pas active		//	Reason why it's not activated
	tMuxLicenceDate	tFinalDate;			//	Date finale d'utilisation de la licence		//	Date when the licence will be locked (set to 0 if no date)
} tMuxLicence ;

typedef enum
{
    NO_PARITY            =   0,      /* Pas de bit de parité                         // No parity */
    ODD_PARITY             =   1,      /* Parité impaire                               // Odd parity */
    EVEN_PARITY            =   2       /* Parité paire                                 // Even parity */
} tUartParity;

typedef enum
{
    ONE_STOP_BIT             =   0,     /* 1 bit de stop                                 // 1 stop bit */
    TWO_STOP_BIT             =   1      /* 2 bits de stop                                // 2 stop bits */
} tUartStopBit;

typedef enum
{
    FIVE_DATA_BIT            =   0,     /* 5 bits de données                             // 5 data bits */
    SIX_DATA_BIT             =   1,     /* 6 bits de données                             // 6 data bits */
    SEVEN_DATA_BIT           =   2,     /* 7 bits de données                             // 7 data bits */
    EIGHT_DATA_BIT           =   3,     /* 8 bits de données                             // 8 data bits */
    NINE_DATA_BIT            =   4      /* 9 bits de données                             // 9 data bits */
} tUartDataBit;

typedef struct
{
	tUartParity     eParity;                /* Type de parité                               // Parity: none, even or odd */
    tUartStopBit    eStopBit;               /* Nombre de bits de stop                       // Number of stop bits */
    tUartDataBit    eDataBit;               /* Nombre de bits de données                    // Data bits number */
    unsigned long   dwBaudrate;             /* Vitesse du bus                               // Baudrate */
    unsigned short  wError;                 /* % d'erreur admise                            // Deviation */
    unsigned short  wReserved1;            /* Réservé pour utilisation future              // Reserved */
    unsigned short  wReserved2;            /* Réservé pour utilisation future              // Reserved */
    unsigned short  wReserved3;            /* Réservé pour utilisation future              // Reserved */
    unsigned short  wReserved4;            /* Réservé pour utilisation future              // Reserved */
} tUartConfig;

typedef struct
{
	unsigned short	wStructSize;			//	Taille de la tRTCValue	//	Size of tRTCValue
	unsigned short	wDay;					//	Jour de 1 à 31	//	Day from 1 to 31
	unsigned short	wMonth;					//	Mois de 1 à 12		//	Month from 1 to 12
	unsigned short	wYear;					//	Année de 0 à 99	//	Year from 0 to 99
	unsigned short	wHour;					//	Heure de 0 à 23	//	Hour from 0 to 23
	unsigned short	wMinute;				//	Minute de 0 à 59	//	Minutes from 0 to 59
	unsigned short	wSecond;				//	Seconde de 0 à 59	//	Second from 0 to 59
	unsigned short	wDayOfWeek;				//	Jour de la semaine (0>dimanche, ... )	//	Day of the week (0>sunday, ...)
} tRTCValue ;

typedef struct
{
	unsigned long	ulLowPart;				//	Partie base pour le 64 bits
	unsigned long	ulHighPart;				//	Partie haute pour le 64 bits
	unsigned long	ulRealValue;			//	Datation correspondante en 100µs
} TTimingValue ;

typedef struct
{
	TTimingValue	tMuxOpen;				//	Datation du dernier muxopen	//	Dating of the Last MuxOpen
} TTimings ;

//	Pointeur de fonction pour la datation personnalisée	//	Pointer of function for the custom timer
typedef unsigned long ( *tMuxUserTimerFct )( void );

typedef enum 
{
	ETH_Disabled	= 0,
	ETH_Enabled		= 1
}tETHState;

/*******************************************************************************
; Routines générales // main functions
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif

#ifndef MUX_DYNAMIC_DLL
/* Récupère les timings	//	Gets timings' information	*/
_MUXSPEC tMuxStatus _MUXAPI MuxGetTimings( unsigned short wCard, TTimings *ptTimings, TTimingValue *tBaseCounter );
/* Initialize la librairie sous Linux // Initialize the library under Linux */
_MUXSPEC tMuxStatus _MUXAPI MuxGlobalInit(void);
//	Définit une datation personnalisée (mode démo)
_MUXSPEC tMuxStatus _MUXAPI MuxSetUserTimerFct( tMuxUserTimerFct hUserTimerFct );
/* Crée un évenement // Create an event object */
_MUXSPEC  void * _MUXAPI MuxCreateEvent(void);
/* Détruit un événement // Delete an event object */
_MUXSPEC tMuxStatus _MUXAPI MuxCloseEvent(void * hEvent);
/* Attend un événement // Wait for an event */
_MUXSPEC tMuxStatus _MUXAPI MuxWaitOnEvent(void * hEvent, unsigned long dwMilliseconds);
/* Signal un événement // Set an event */
_MUXSPEC tMuxStatus _MUXAPI MuxSetEvent(void * hEvent);
/* Active ou non le mode client/serveur RESERVE // Active or not the client/server mode RESERVED */
_MUXSPEC tMuxStatus _MUXAPI MuxClientServerMode(char *szUnlockKey, tMuxCSMode eCSMode);
/* Affiche les valeur contenu dans la structure afin de vérifier si les options d'alignements sont correctes	// Display all the values of the structure in order to check if the alignment options are correctly set */
_MUXSPEC tMuxStatus _MUXAPI MuxCheckAlignment(tMuxAlignment *hMuxAlignment, unsigned short wDisplayValues);
/* Retourne le nombre de cartes gérées par les DLLs                         // Indicate the number of boards managed by DLL */
_MUXSPEC tMuxStatus _MUXAPI MuxCountCards(unsigned long *dwCardsCount);
/* Retourne le nombre de cartes sur le bus PCI                              // Indicate the number of PCI boards on the PCI bus */
_MUXSPEC tMuxStatus _MUXAPI MuxPciCountCards(unsigned long *dwCardsCount);
/* Retourne le nombre de cartes sur le bus USB                              // Indicate the number of USB devices USB bus */
_MUXSPEC tMuxStatus _MUXAPI MuxUsbCountCards(unsigned long *dwCardsCount);
/* Retourne le nombre de cartes sur le réseau ethernet							// Indicate the number of eth boards on the ETH network */
_MUXSPEC tMuxStatus _MUXAPI MuxEthCountCards(unsigned long *dwCardsCount);
/* Retourne les informations concernant la carte PCI                        // Give information about the PCI board */
_MUXSPEC tMuxStatus _MUXAPI MuxPciGetCardInfo(unsigned short wCard, unsigned long *dwCardBus, unsigned long *dwCardSlot, unsigned long *dwCardInfo);
/* Retourne les informations concernant la carte USB                        // Give information about the USB device */
_MUXSPEC tMuxStatus _MUXAPI MuxUsbGetCardInfo(unsigned short wCard, unsigned long *dwHubNum, unsigned long *dwPortNum, unsigned long *dwSerialNum, unsigned long *dwDeviceAddress, unsigned long *dwProductID, unsigned long *dwUniqueId);
/* Retourne les informations concernant la carte Ethernet                   // Give information about the ETH device */
_MUXSPEC tMuxStatus _MUXAPI MuxEthGetCardInfo(unsigned short wCard, unsigned char *bInfo, unsigned short *wSize);
/* Initialise les variable interne de la carte                              // Init. internal driver state and variables */
_MUXSPEC tMuxStatus _MUXAPI MuxInit(unsigned short wCard);
/* Retourne un handle de communication avec la carte                        // Return an handle to communicate with board */
_MUXSPEC tMuxStatus _MUXAPI MuxOpen(unsigned short wCard, tMuxConfigMode *hMuxConfigMode);
/* Retourne les informations concernant le logiciel                         // Give version informations */
_MUXSPEC tMuxStatus _MUXAPI MuxGetVersion(unsigned short wCard,unsigned long *dwVersionDll,unsigned long *dwVersionDriver,unsigned long *dwVersionKernel, tMuxHWType *eNumHWType);
/* Retourne la description de la carte en cours	// Give device description */
_MUXSPEC tMuxStatus _MUXAPI MuxGetDescription( unsigned short wCard, char *szDescription );
/* Retourne le numéro de série												// Get the serial number	*/
_MUXSPEC tMuxStatus _MUXAPI MuxGetInformations( unsigned short wCard, tMuxInformations *tInfos );
/* Fermeture du handle de communication avec la carte                       // Close the handle */
_MUXSPEC tMuxStatus _MUXAPI MuxClose(unsigned short wCard);
/* Récupération d'une chaine de compte rendu d'erreur                       // Return a string which indicate the last error message */
_MUXSPEC tMuxStatus _MUXAPI MuxGetLastErrorString(char **pString);
/* Code de protection de la carte                                           // Get protected code */
_MUXSPEC tMuxStatus _MUXAPI MuxGetProtectedCode(unsigned short wCard, unsigned short *wCode);
/* Téléchargement USB                                                       // Download code */
_MUXSPEC tMuxStatus _MUXAPI MuxUsbDownload(unsigned short wCard, char *pcFileName, unsigned short wMode);
/* Réservé                                                                  // Reserved, do not used */
_MUXSPEC tMuxStatus _MUXAPI MuxGetInternalInfo(unsigned short wCard, tMuxInternalInfo *pstMuxInternalInfo);
/* Connaitre si une licence est active ou non								// Get if a licence is active or not */
_MUXSPEC tMuxStatus _MUXAPI MuxIsLicenceActive( unsigned short wCard, unsigned short wLicenceID, tMuxLicence *tLic );
/* Active la recherche des product ID */
_MUXSPEC tMuxStatus _MUXAPI MuxSetProductIDMode( unsigned short wEnabled );
/* Récupère le n° du build number au format AAMMJJHHMMSS Get the build number using format YYMMDDHHMMSS */
_MUXSPEC tMuxStatus _MUXAPI MuxGetBuildNumber( unsigned long *pdwBN, char *szBN );
/* Récupère l'heure de l'horloge embarquée // Read the timestamp of the embedded clock */
_MUXSPEC tMuxStatus _MUXAPI MuxGetRTCValue( unsigned short wCard, tRTCValue *tValue );
/* Défini l'heure de l'horloge embarquée // Set the timestamp of the embedded clock */
_MUXSPEC tMuxStatus _MUXAPI MuxSetRTCValue( unsigned short wCard, tRTCValue *tValue );
/* Reset un pipe // Reset a pipe */
_MUXSPEC tMuxStatus _MUXAPI MuxUsbResetPipe( unsigned short wCard, unsigned short wPipeNumber );
/* recupere le HARDWARE ID de la prise. //get peripheral HARDWARE ID*/
_MUXSPEC tMuxStatus _MUXAPI MuxGetHardwareID(unsigned short wCard, char *szHardwareID, unsigned long dwSize);
/* active ou pas le support de l'ETHERNET. // set or not ETHERNET support. */
_MUXSPEC tMuxStatus _MUXAPI MuxSetEthernet ( tETHState hEthState );
/* Récupère l'etat de l'ETHERNET. // read ETHERNET State. */
_MUXSPEC tMuxStatus _MUXAPI MuxGetEthernet ( tETHState *hEthState );

#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tMuxGetTimings )( unsigned short wCard, TTimings *ptTimings, TTimingValue *tBaseCounter );
typedef tMuxStatus (__stdcall * tMuxGlobalInit)(void);
typedef tMuxStatus (__stdcall * tMuxSetUserTimerFct )( tMuxUserTimerFct hUserTimerFct );
typedef void *     (__stdcall * tMuxCreateEvent)(void);
typedef tMuxStatus (__stdcall * tMuxCloseEvent)(void * hEvent);
typedef tMuxStatus (__stdcall * tMuxWaitOnEvent)(void * hEvent, unsigned long dwMilliseconds);
typedef tMuxStatus (__stdcall * tMuxSetEvent)(void * hEvent);
typedef tMuxStatus (__stdcall * tMuxClientServerMode)(char *szUnlockKey, tMuxCSMode eCSMode);
typedef tMuxStatus (__stdcall * tMuxCheckAlignment)(tMuxAlignment *hMuxAlignment, unsigned short wDisplayValues);
typedef tMuxStatus (__stdcall * tMuxCountCards)(unsigned long *dwCardsCount);
typedef tMuxStatus (__stdcall * tMuxPciCountCards)(unsigned long *dwCardsCount);
typedef tMuxStatus (__stdcall * tMuxUsbCountCards)(unsigned long *dwCardsCount);
typedef tMuxStatus (__stdcall * tMuxEthCountCards)(unsigned long *dwCardsCount);
typedef tMuxStatus (__stdcall * tMuxPciGetCardInfo)(unsigned short wCard, unsigned long *dwCardBus, unsigned long *dwCardSlot, unsigned long *dwCardInfo);
typedef tMuxStatus (__stdcall * tMuxUsbGetCardInfo)(unsigned short wCard, unsigned long *dwHubNum, unsigned long *dwPortNum, unsigned long *dwSerialNum, unsigned long *dwDeviceAddress, unsigned long *dwCardInfo, unsigned long *dwUniqueId);
typedef tMuxStatus (__stdcall * tMuxEthGetCardInfo)(unsigned short wCard, unsigned char *bInfo, unsigned short *wSize);
typedef tMuxStatus (__stdcall * tMuxInit)(unsigned short wCard);
typedef tMuxStatus (__stdcall * tMuxOpen)(unsigned short wCard, tMuxConfigMode *hMuxConfigMode);
typedef tMuxStatus (__stdcall * tMuxGetVersion)(unsigned short wCard,unsigned long *dwVersionDll,unsigned long *dwVersionDriver,unsigned long *dwVersionKernel, tMuxHWType *eNumHWType);
typedef tMuxStatus (__stdcall * tMuxGetDescription)( unsigned short wCard, char *szDescription );
typedef tMuxStatus (__stdcall * tMuxGetInformations)( unsigned short wCard, tMuxInformations *tInfos );
typedef tMuxStatus (__stdcall * tMuxClose)(unsigned short wCard);
typedef tMuxStatus (__stdcall * tMuxGetLastErrorString)(char **pString);
typedef tMuxStatus (__stdcall * tMuxGetProtectedCode)(unsigned short wCard, unsigned short *wCode);
typedef tMuxStatus (__stdcall * tMuxUsbDownload)(unsigned short wCard, char *pcFileName, unsigned short wMode);
typedef tMuxStatus (__stdcall * tMuxGetInternalInfo)(unsigned short wCard, tMuxInternalInfo *pstMuxInternalInfo);
typedef tMuxStatus (__stdcall * tMuxIsLicenceActive)( unsigned short wCard, unsigned short wLicenceID, tMuxLicence *tLic );
typedef tMuxStatus (__stdcall * tMuxSetProductIDMode )( unsigned short wEnabled );
typedef tMuxStatus (__stdcall * tMuxGetBuildNumber )( unsigned long *pdwBN, char *szBN );
typedef tMuxStatus (__stdcall * tMuxGetRTCValue )( unsigned short wCard, tRTCValue *tValue );
typedef tMuxStatus (__stdcall * tMuxSetRTCValue )( unsigned short wCard, tRTCValue *tValue );
typedef tMuxStatus (__stdcall * tMuxUsbResetPipe )( unsigned short wCard, unsigned short wPipeNumber );
typedef tMuxStatus (__stdcall * tMuxGetHardwareID)(unsigned short wCard, char *szHardwareID, unsigned long dwSize);
typedef tMuxStatus (__stdcall * tMuxSetEthernet) ( tETHState hEthState );
typedef tMuxStatus (__stdcall * tMuxGetEthernet) ( tETHState hEthState );
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Routines d'administration des cartes // USB devices setup function
*******************************************************************************/
#define ADMIN_MAX_DATA		512
typedef struct
{
	unsigned char	bData[ ADMIN_MAX_DATA ];		// Données de configuration		// Setup data
	unsigned short	wDataLen;						// Taille des données			// Setup data length
} tAdminConfig ;

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef MUX_DYNAMIC_DLL
// Ouvre une session d'administration	// Open a administration session
_MUXSPEC tMuxStatus _MUXAPI AdminOpenSession( unsigned short wCard, unsigned char *szAccessKey, unsigned char *szUnlockKey );
// Ecrit une configuration	// Write a setup buffer
_MUXSPEC tMuxStatus _MUXAPI AdminWriteConfig( unsigned short wCard, tAdminConfig *tConfig );
// Lit une configuration	// Read a setup buffer
_MUXSPEC tMuxStatus _MUXAPI AdminReadConfig( unsigned short wCard, tAdminConfig *tConfig );
//	Lit le nombre de licence de max pouvant être géré par la carte	//	Get how many licence can be manage by the device
_MUXSPEC tMuxStatus _MUXAPI AdminGetLicenceCount( unsigned short wCard, unsigned short *pwLicenceCount );
//	Lit la liste des licences	//	Read licences config
_MUXSPEC tMuxStatus _MUXAPI AdminReadLicences( unsigned short wCard, void *pBuffer, unsigned short *pwBufferLen );
//	Ecrit la liste des licences	//	Write licences config
_MUXSPEC tMuxStatus _MUXAPI AdminWriteLicences( unsigned short wCard, void *pBuffer, unsigned short wBufferLen );
//	Lit les données d'une licence	//	Read data of a licence
_MUXSPEC tMuxStatus _MUXAPI AdminGetLicenceData( unsigned short wCard, unsigned short wLicenceID, void *pBuffer, unsigned short *pwBufferLen );
//	Ecrit les données d'une licence	//	Write data of a licence
_MUXSPEC tMuxStatus _MUXAPI AdminSetLicenceData( unsigned short wCard, unsigned short wLicenceID, void *pBuffer, unsigned short wBufferLen );
//	Lit les données des licences	//	Read licences data
_MUXSPEC tMuxStatus _MUXAPI AdminReadLicencesData( unsigned short wCard, void *pBuffer, unsigned short *pwBufferLen );
//	Ecrit les données des licences	//	Write licenses data
_MUXSPEC tMuxStatus _MUXAPI AdminWriteLicencesData( unsigned short wCard, void *pBuffer, unsigned short wBufferLen );
#else
// Ouvre une session d'administration	// Open a administration session
typedef tMuxStatus (__stdcall * tAdminOpenSession)( unsigned short wCard, unsigned char *szAccessKey, unsigned char *szUnlockKey );
// Ecrit une configuration	// Write a setup buffer
typedef tMuxStatus (__stdcall * tAdminWriteConfig)( unsigned short wCard, tAdminConfig *tConfig );
// Lit une configuration	// Read a setup buffer
typedef tMuxStatus (__stdcall * tAdminReadConfig)( unsigned short wCard, tAdminConfig *tConfig );
//	Lit le nombre de licence de max pouvant être géré par la carte	//	Get how many licence can be manage by the device
typedef tMuxStatus (__stdcall * tAdminGetLicenceCount)( unsigned short wCard, unsigned short *pwLicenceCount );
//	Lit la liste des licences	//	Read licences config
typedef tMuxStatus (__stdcall * tAdminReadLicences)( unsigned short wCard, void *pBuffer, unsigned short *pwBufferLen );
//	Ecrit la liste des licences	//	Write licences config
typedef tMuxStatus (__stdcall * tAdminWriteLicences)( unsigned short wCard, void *pBuffer, unsigned short wBufferLen );
//	Lit les données d'une licence	//	Read data of a licence
typedef tMuxStatus (__stdcall * tAdminGetLicenceData)( unsigned short wCard, unsigned short wLicenceID, void *pBuffer, unsigned short *pwBufferLen );
//	Ecrit les données d'une licence	//	Write data of a licence
typedef tMuxStatus (__stdcall * tAdminSetLicenceData)( unsigned short wCard, unsigned short wLicenceID, void *pBuffer, unsigned short wBufferLen );
//	Lit les données des licences	//	Read licences data
typedef tMuxStatus (__stdcall * tAdminReadLicencesData)( unsigned short wCard, void *pBuffer, unsigned short *pwBufferLen );
//	Ecrit les données des licences	//	Write licences data
typedef tMuxStatus (__stdcall * tAdminWriteLicencesData)( unsigned short wCard, void *pBuffer, unsigned short wBufferLen );
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
	routine d'événement système	//	System Events functions
*******************************************************************************/
typedef struct _tSysEvent
{
	tMuxTypeEvent	eTypeEvent;			//	Type d'événement		//	Event type
} tSysEvent ;

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef MUX_DYNAMIC_DLL
//	Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application
_MUXSPEC tMuxStatus _MUXAPI SysSetNotification( unsigned short wCard, void * hWinEvent );
//	Récupère un évenement	//	Get a event
_MUXSPEC tMuxStatus _MUXAPI SysGetEvent( unsigned short wCard, tSysEvent *hSysEvent );
#else
//	Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application
typedef tMuxStatus (__stdcall * tSysSetNotification )( unsigned short wCard, void * hWinEvent );
//	Récupère un évenement	//	Get a event
typedef tMuxStatus (__stdcall * tSysGetEvent )( unsigned short wCard, tSysEvent *hSysEvent );
#endif

#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines CAN // CAN definitions
*******************************************************************************/
#define	CAN_MAX_DATA	        		8		/* Nbre de données max CAN                      // Maximum CAN data length */

#define CAN_PERIODIC_PARAM_ENABLE		1		/* Active la périodique							// Enable periodic frame */
#define CAN_PERIODIC_PARAM_DISABLE		0		/* Desactive la periodique						// Disable periodic frame */
#define CAN_PERIODIC_PARAM_WITHEVENTS	2		/* Active la remontée des événements			// Enable the events */
#define CAN_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

#define	CAN_ERROR_BITERROR				0x0000	//	Erreur de bit
#define	CAN_ERROR_FORMAT				0x0040	//	Erreur de format
#define	CAN_ERROR_STUFFING				0x0080	//	Erreur de stuffing
#define	CAN_ERROR_MISCELLANEOUS			0x00C0	//	Divers
#define	CAN_ERROR_TX					0x0000	//	Transmission
#define CAN_ERROR_RX					0x0020	//	Réception
#define	CAN_ERROR_ID20TOID21			0x0002	//	ID20 a ID21
#define	CAN_ERROR_STARTOFFRAME			0x0003	//	Start of Frame
#define	CAN_ERROR_BITSRTR				0x0004	//	Bit SRTR
#define	CAN_ERROR_BITIDE				0x0005	//	Bit IDE
#define	CAN_ERROR_ID20TOID18			0x0006	//	ID20 TO ID18
#define	CAN_ERROR_ID17TOID13			0x0007	//	ID17 TO ID 13
#define	CAN_ERROR_CRCFIELD				0x0008	//	Champ CRC
#define	CAN_ERROR_RESERVEDBIT0			0x0009	//	Bit réservé
#define	CAN_ERROR_DATAFIELD				0x000A	//	Champ DATA
#define	CAN_ERROR_DLCFIELD				0x000B	//	Champ DLC
#define	CAN_ERROR_RTRBIT				0x000C	//	CRC BIT
#define	CAN_ERROR_RESERVEDBIT1			0x000D	//	Bit réservé
#define	CAN_ERROR_ID4TOID0				0x000E	//	ID4 a ID0
#define	CAN_ERROR_ID12TOID5				0x000F	//	ID13 a ID5
#define	CAN_ERROR_ACTIVEERROR			0x0011	//	Erreur active
#define	CAN_ERROR_INTERMISSION			0x0012	//	Intermission
#define	CAN_ERROR_DOMINANTBITS			0x0013	//	Dominant bits
#define	CAN_ERROR_PASSIVEERROR			0x0016	//	Erreur passive
#define	CAN_ERROR_ERRORDELIMITER		0x0017	//	Delimiteur d'erreur
#define	CAN_ERROR_CRCDELIMITER			0x0018	//	Delimiteur CRC
#define	CAN_ERROR_ACKNOWLEDGESLOT		0x0019	//	Acquitement
#define	CAN_ERROR_ENDOFFRAME			0x001A	//	Fin de trame
#define	CAN_ERROR_ACKNOWLEDGEDELIMITER	0x001B	//	Delimiteur d'acquitement
#define	CAN_ERROR_OVERLOAD				0x001C	//	Surchage

typedef enum
{
	CAN_OPER_ANA_FIFO       =   0,      /* Mode analyse, stockage fifo                  // Analyse mode, event is stored in fifo mode */
    CAN_OPER_ANA_BUFF       =   1       /* Mode analyse, stockage buffer                // Analyse mode, event is stored in buffer mode */
} tCanOperMode;

typedef struct
{
    tCanOperMode    eCanOperMode;       /* Type d'interface avec l'application          // Operating mode with API */
    unsigned short  wFifoSize;          /* Taille de la FIFO                            // FIFO Size */
} tCanOper;

typedef enum
{
    CAN_ID_STD              =   0,      /* Identificateur standard (11 bits)            // Standard identifier */
    CAN_ID_XTD              =   1       /* Identificateur étendu (29 bits)              // Extended identifier */
} tCanTypeId;

/*ATTENTION: Ne plus utiliser cet ENUM pour la fonction CanSelectTransceiverHS         // WARNING : don't use it for CanSelectTransceiverHS function.*/
typedef enum
{
    CAN_FALSE               =   0,      /* Booléen faux                                 // FALSE */
    CAN_TRUE                =   1       /* Booléen vrai                                 // TRUE */
} tCanBoolean;
typedef enum
{
	CAN_LS                =   0,      /* CAN LOW SPEED */
	CAN_HS                =   1,      /* CAN HIGH SPEED */
	CAN_SW                =   2       /* CAN SINGLE WIRE */
} tCanType;
typedef enum
{
    CAN_SVC_TRANSMIT_DATA   =   0,      /* Transmission de données                      // Transmit message */
    CAN_SVC_RECEIVE_DATA    =   1,      /* Réception de données                         // Receive message */
    CAN_SVC_TRANSMIT_RTR    =   2,      /* Transmission de remote                       // Transmit a remote */
    CAN_SVC_RECEIVE_RTR     =   3       /* Réception de remote                          // Receive a remote */
} tCanService;
typedef enum
{
	CAN_BUS_ACTIVE          =   0,      /* Etat erreur active                           // Active error state */
    CAN_BUS_PASSIVE         =   1,      /* Etat erreur passive                          // Passive error state */
    CAN_BUS_OFF             =   2       /* Etat bus off                                 // Bus off state */
} tCanChipState;
typedef enum
{
    CAN_SLOPE_CONTROL       =   0,      /* Front couché (interface de ligne)            // Slope control (line interface) */
    CAN_SLOPE_HIGH_SPEED    =   1       /* Front droit (interface de ligne)             // High speed (line interface) */
} tCanSlope;

typedef struct
{
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
    unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
    unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
    unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
    unsigned long   dwErrTxBit;         /* Erreur de type Bit en Tx                     // Bit error during transmission */
    unsigned long   dwErrRxBit;         /* Erreur de type Bit en Rx                     // Bit error during reception */
    unsigned long   dwErrTxForm;        /* Erreur de format en Tx                       // Format error during transmission */
    unsigned long   dwErrRxForm;        /* Erreur de format en Rx                       // Format error during reception */
    unsigned long   dwErrTxStuff;       /* Erreur de stuffing en Tx                     // Stuff error during transmission */
    unsigned long   dwErrRxStuff;       /* Erreur de stuffing en Rx                     // Stuff error during reception */
    unsigned long   dwErrTxOther;       /* Erreur autre que les 3 types ci-dessus en Tx // Other error during transmission */
    unsigned long   dwErrRxOther;       /* Erreur autre que les 3 types ci-dessus en Rx // Other error during reception */
    unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tCanStat;

typedef struct
{
    unsigned short  wBRP;               /* Baud rate prescaler [1-64]                   // Baud rate prescaler */
    unsigned short  wTSEG1;             /* Délai avant point d'échantillonnage [3-16]   // Time segment 1 */
    unsigned short  wTSEG2;             /* Délai après point d'échantillonnage [2-8]    // Time segment 2 */
    unsigned short  wSJW;               /* Saut de resynchronisation max [1-4]          // Synchronisation jump width */
    unsigned short  wSPL;               /* Nbre de point d'échantillonnage [1 ou 3]     // Sampling mode [1 or 3] */
} tCanBus;

typedef struct
{
    unsigned long   dwFiltIdent;        /* Identificateur pour filtrage                 // Identifier for filtering */
    tCanTypeId      eTypeId;            /* Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) */
    unsigned long   dwFiltMask;         /* Masque pour filtrage                         // Acceptance mask */
    tCanBoolean     eAckEnable;         /* Validation / dévalidation de l'acquittement  // Enable or disable acknowlegment */
    tCanBoolean     eRxAll;             /* Réception des ident non déclarés             // All messages or only programmed message are given to the application */
    unsigned short  wSpecialModes;      /* Réservé pour utilisation futures             // Reserved for future used */
} tCanParam;

typedef struct
{
	unsigned short  wFiltIdent1;		/* Identificateur pour filtrage (1er groupe)    // Identifier for filtering (1st group) */
	unsigned short  wFiltMask1;		    /* Masque pour filtrage         (1er groupe)    // Acceptance mask (1st group) */
	unsigned short  wFiltIdent2;		/* Identificateur pour filtrage (2ème groupe)   // Identifier for filtering (2nd group) */
	unsigned short  wFiltMask2;		    /* Masque pour filtrage         (2ème groupe)   // Acceptance mask (2nd group) */
	tCanTypeId      eTypeId;            /* Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) */
} tCanDualFilter;

typedef enum
{
    CAN_CLOCK_16MHZ         =   0,      /* fCAN = 16MHZ pour SJA1000 (valeur par défaut) */
    CAN_CLOCK_40MHZ         =   1,      /* fCAN = 40MHZ pour TWINCAN (= fCPU) */
    CAN_CLOCK_5MHZ          =   2       /* fCAN = 5MHZ pour TWINCAN (= fCPU/8) */
} tCanClockFreq;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                                // Bus number */
    unsigned short  wHandleMsg;         /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement retourné à l'application    // Event type */
    unsigned long   dwIdent;            /* Identificateur du message                    // CAN identifier value */
    tCanTypeId      eTypeId;            /* Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) */
    unsigned long   dwTimeStamp;        /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                     // Time accuracy */
    tCanService     eService;           /* Service de la requête                        // CAN services */
    unsigned short  wError;             /* Type d'erreur                                // Error type */
    tCanChipState   eChipState;         /* Etat du composants                           // Chip state */
    unsigned short  wLineState;         /* Etat de l'interface de ligne LS              // Low speed line interface state */
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned long   dwReserved1;        /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[CAN_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tCanEvent;

typedef struct
{
    unsigned short  wHandleMsg;         /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    unsigned long   dwIdent;            /* Identificateur du message                    // CAN identifier value */
    tCanTypeId      eTypeId;            /* Type d'identificateur STD ou XTD             // Identifier type (standard (11 bits) or extended (29 bits) */
    unsigned long   dwMask;				/* Masque apposé sur l'identificateur           // Mask code */
    tCanService     eService;           /* Service de la requête                        // CAN services */
    unsigned long   lPeriod;            /* Periodicité en ms                            // Period */
    unsigned long   dwReserved1;        /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned long   dwReserved2;        /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[CAN_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tCanMsg;

typedef struct
{
	unsigned short	wOffset;			/* Offset du message periodic					// Offset du message periodic */
	unsigned short	wParam;				/* Paramètre pour la périodique					// Parameters for the periodic */
	tCanMsg			hCanMsg;			/* Message à émettre							// Message to send */
} tCanPeriodicMsg;

typedef struct
{
	tCanTypeId      eTypeId;            /* Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) */
	unsigned long	dwLowIdent;			/*	Ident bas // Low Ident */
	unsigned long	dwHighIdent;		/*	Ident Haut // High Ident */
} tCanRangeFilter ;

/*******************************************************************************
; Routines CAN // CAN prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du mode de fonctionnement des buffers                      // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI CanConfigOper(unsigned short wCard, unsigned short wBus, tCanOper *hCanOper);
/* Configuration du bus                                                     // Bus parameter */
_MUXSPEC tMuxStatus _MUXAPI CanConfigBus(unsigned short wCard, unsigned short wBus, tCanBus *hCanBus);
/* Configuration des paramètres supplémentaires                             // Extra parameter */
_MUXSPEC tMuxStatus _MUXAPI CanConfigParam(unsigned short wCard, unsigned short wBus, tCanParam *hCanParam);
/* configuration du filtre sur plage	//	Range filter settings */
_MUXSPEC tMuxStatus _MUXAPI CanConfigRangeFilter(unsigned short wCard, unsigned short wBus, tCanRangeFilter *hCanRangeFilter );
/* Configuration de l'horloge du contrôleur CAN                             // Clock parameter */
_MUXSPEC tMuxStatus _MUXAPI CanConfigClock(unsigned short wCard, unsigned short wBus, tCanClockFreq eCanClock);
/* Configuration des filtres d'acceptance double                            // Set dual filter */
_MUXSPEC tMuxStatus _MUXAPI CanConfigDualFilter(unsigned short wCard, unsigned short wBus, tCanDualFilter *hCanDualFilter);
/* Configuration des statistques                                            // Statistics configuration */
_MUXSPEC tMuxStatus _MUXAPI CanConfigStat(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
/* Configuration de l'interface de ligne HS                                 // High speed transceiver configuration */
_MUXSPEC tMuxStatus _MUXAPI CanConfigTransceiverHS(unsigned short wCard, unsigned short wBus, tCanSlope eCanSlope);
/* Sélection de l'interface de ligne / Ou du single wire                    // Transceiver HS selection or single wire */
_MUXSPEC tMuxStatus _MUXAPI CanSelectTransceiverHS(unsigned short wCard, unsigned short wBus, tCanType eCanType);
/* Configuration de l'interface de ligne LS                                 // Low speed transceiver configuration */
_MUXSPEC tMuxStatus _MUXAPI CanConfigTransceiverLS(unsigned short wCard, unsigned short wBus, unsigned short wStandBy, unsigned short wEnable, unsigned short wWakeUp);
/* Configuration des résistances de rappel CANLS                            // Low speed pull up resistor configuration */
_MUXSPEC tMuxStatus _MUXAPI CanConfigTerminationLS(unsigned short wCard, unsigned short wBus, unsigned short wValue);
/* Lecture de l'interface de ligne LS                                       // Low speed transceiver information */
_MUXSPEC tMuxStatus _MUXAPI CanReadTransceiverLS(unsigned short wCard, unsigned short wBus, unsigned short *wLineState);
/* Création des messages de communication                                   // Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI CanCreateMsg(unsigned short wCard, unsigned short wBus, tCanMsg *hCanMsg);
/* Lecture des messages de communication                                   // Messages read */
_MUXSPEC tMuxStatus _MUXAPI CanReadMsg(unsigned short wCard, unsigned short wBus, unsigned short wNumMsg, tCanMsg *hCanMsg);
/* modification des messages de communication                                  // Messages modification */
_MUXSPEC tMuxStatus _MUXAPI CanWriteMsg(unsigned short wCard, unsigned short wBus, unsigned short wNumMsg, tCanMsg *hCanMsg);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI CanConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tCanMsg *hCanMsg);
/* Création de plusieurs message périodique                                 // Several Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI CanConfigPeriodicList(unsigned short wCard, unsigned short wBus, unsigned short wPeriodicCount, tCanPeriodicMsg *hPeriodicCanMsgList);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI CanSetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI CanActivate(unsigned short wCard, unsigned short wBus);
/* Etat du bus de communication                                             // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI CanIsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI CanDeactivate(unsigned short wCard, unsigned short wBus);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI CanSendMsg(unsigned short wCard, unsigned short wBus, tCanMsg *hCanMsg);
/* Emission plusieurs messages											// Transmit several messages */
_MUXSPEC tMuxStatus _MUXAPI CanSendMsgList(unsigned short wCard, unsigned short wBus, unsigned short wMsgCount, tCanMsg *hCanMsgList);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI CanGetEvent(unsigned short wCard, unsigned short wBus, tCanEvent *hCanEvent);
/* Reconnexion du bus après passage en bus off                              // Connect CAN bus after bus off transition */
_MUXSPEC tMuxStatus _MUXAPI CanBusOn(unsigned short wCard, unsigned short wBus);
/* change la vitesse du bus can 											//change can baudrate */
_MUXSPEC tMuxStatus _MUXAPI CanChangeBaudRate(unsigned short wCard, unsigned short wBus, tCanBus *hCanBus);

/* Lecture des statistiques                                                 // Statistics information */
_MUXSPEC tMuxStatus _MUXAPI CanGetStat(unsigned short wCard, unsigned short wBus, tCanStat *hCanStat);
/* Récupération de l'état du contrôleur de protocole                        // CAN controller state */
_MUXSPEC tMuxStatus _MUXAPI CanGetBusState(unsigned short wCard, unsigned short wBus, tCanChipState *eCanChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI CanClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI CanGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);

/* Lecture d'un octet sur un composant CAN                                  // Read byte from the CAN controller */
_MUXSPEC tMuxStatus _MUXAPI CanReadByte(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char *bData);
/* Ecriture d'un octet sur un composant CAN                                 // Write byte to the CAN controller */
_MUXSPEC tMuxStatus _MUXAPI CanWriteByte(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char bData);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tCanConfigOper)(unsigned short wCard, unsigned short wBus, tCanOper *hCanOper);
typedef tMuxStatus (__stdcall * tCanConfigBus)(unsigned short wCard, unsigned short wBus, tCanBus *hCanBus);
typedef tMuxStatus (__stdcall * tCanConfigParam)(unsigned short wCard, unsigned short wBus, tCanParam *hCanParam);
typedef tMuxStatus (__stdcall * tCanConfigRangeFilter)(unsigned short wCard, unsigned short wBus, tCanRangeFilter *hCanRangeFilter );
typedef tMuxStatus (__stdcall * tCanConfigClock)(unsigned short wCard, unsigned short wBus, tCanClockFreq eCanClock);
typedef tMuxStatus (__stdcall * tCanConfigDualFilter)(unsigned short wCard, unsigned short wBus, tCanDualFilter *hCanDualFilter);
typedef tMuxStatus (__stdcall * tCanConfigStat)(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
typedef tMuxStatus (__stdcall * tCanConfigTransceiverHS)(unsigned short wCard, unsigned short wBus, tCanSlope eCanSlope);
typedef tMuxStatus (__stdcall * tCanSelectTransceiverHS)(unsigned short wCard, unsigned short wBus,  tCanType eCanType);
typedef tMuxStatus (__stdcall * tCanConfigTransceiverLS)(unsigned short wCard, unsigned short wBus, unsigned short wStandBy, unsigned short wEnable, unsigned short wWakeUp);
typedef tMuxStatus (__stdcall * tCanConfigTerminationLS)(unsigned short wCard, unsigned short wBus, unsigned short wValue);
typedef tMuxStatus (__stdcall * tCanReadTransceiverLS)(unsigned short wCard, unsigned short wBus, unsigned short *wLineState);
typedef tMuxStatus (__stdcall * tCanCreateMsg)(unsigned short wCard, unsigned short wBus, tCanMsg *hCanMsg);
typedef tMuxStatus (__stdcall * tCanReadMsg)(unsigned short wCard, unsigned short wBus, unsigned short wNumMsg, tCanMsg *hCanMsg);
typedef tMuxStatus (__stdcall * tCanWriteMsg)(unsigned short wCard, unsigned short wBus, unsigned short wNumMsg, tCanMsg *hCanMsg);
typedef tMuxStatus (__stdcall * tCanConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tCanMsg *hCanMsg);
typedef tMuxStatus (__stdcall * tCanConfigPeriodicList)(unsigned short wCard, unsigned short wBus, unsigned short wPeriodicCount, tCanPeriodicMsg *hPeriodicCanMsgList);
typedef tMuxStatus (__stdcall * tCanSetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tCanActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tCanIsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tCanDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tCanSendMsg)(unsigned short wCard, unsigned short wBus, tCanMsg *hCanMsg);
typedef tMuxStatus (__stdcall * tCanSendMsgList)(unsigned short wCard, unsigned short wBus, unsigned short wMsgCount, tCanMsg *hCanMsgList);
typedef tMuxStatus (__stdcall * tCanGetEvent)(unsigned short wCard, unsigned short wBus, tCanEvent *hCanEvent);
typedef tMuxStatus (__stdcall * tCanBusOn)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tCanChangeBaudRate)(unsigned short wCard, unsigned short wBus, tCanBus *hCanBus);
typedef tMuxStatus (__stdcall * tCanGetStat)(unsigned short wCard, unsigned short wBus, tCanStat *hCanStat);
typedef tMuxStatus (__stdcall * tCanGetBusState)(unsigned short wCard, unsigned short wBus, tCanChipState *eCanChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
typedef tMuxStatus (__stdcall * tCanClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tCanGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus (__stdcall * tCanReadByte)(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char *bData);
typedef tMuxStatus (__stdcall * tCanWriteByte)(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char bData);
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines NWC // NWC definitions
*******************************************************************************/
#define	NWC_MAX_DATA	        4095	/* Nbre de données max NWC                      // Maximum NWC data length */
typedef enum
{
    NWC_MODE_PHYSICAL       =   0,      /* Adressage physique     1 vers 1              // Physical address */
    NWC_MODE_FUNCTIONNAL    =   1       /* Adressage fonctionnel  1 vers n              // Functionnal address */
} tNwcAddrMode;

typedef enum
{
    NWC_FORMAT_NORMAL       =   0,      /* Adressage normal                             // Normal addressing */
    NWC_FORMAT_NORMAL_FIXED =   1,      /* Adressage normal fixe (ident préprogrammé)   // Normal fixed addressing */
    NWC_FORMAT_EXTENDED     =   2,      /* Adressage étendu                             // Extended addressing */
    NWC_FORMAT_MIXED        =   3       /* Adressage mixe (ident préprogrammé           // Mixed addressing */
} tNwcAddrFormat;

typedef enum
{
    NWC_COMM_HALF_DUPLEX    =   0,      /* Communication half duplex                    // Half-duplex communication */
    NWC_COMM_FULL_DUPLEX    =   1       /* Communication full duplex                    // Full-duplex communication */
} tNwcCommMode;

typedef enum
{
	NWC_SVC_TRANSMIT_DATA   =   0,      /* Transmission de données                      // Transmit message */
	NWC_SVC_RECEIVE_DATA    =   1       /* Réception de données                         // Receive message */
} tNwcService;

typedef struct
{
    unsigned short wBlockSize;      /* Nbre de blocs consécutifs // maximum number of consecutives frames */
    unsigned short wSTmin;          /* Délai entre 2 blocs // Separation time */
    unsigned short wN_As;           /* Délai max de transmission coté transmetteur // Time for transmission (transmitter side) */
    unsigned short wN_Ar;           /* Délai max de transmission coté récepteur // Time for transmission (receiver side) */
    unsigned short wN_Bs;           /* Délai jusqu'à réception du FC // Time until reception of next FC */
    unsigned short wN_Br;           /* Délai jusqu'à transmission du FC // Time until transmission of next FC*/
    unsigned short wN_Cr;           /* Délai jusqu'à réception du CF // Time until reception of next CF */
    unsigned short wN_WFTmax;       /* Nbre de FC max. attendue // max flow control wait */
} tNwcParam;

#define NWC_VARIABLE_LEN    0x0000  /* Emission des trames de longueur variable // Messages length variable */
#define NWC_FIXED_LEN       0x0001  /* Emission des trames forcée à 8 octets // Messages length fixed to 8 */
#define NWC_CAN_NO_EVENT    0x0000  /* Pas de remonté des événements CAN // CAN events are ignored */
#define NWC_CAN_EVENT       0x0002  /* Remoonté des événements FF // FF events are stored in NWC FIFO */
#define NWC_NOFLOW_7402     0x0000  /* Pasnté des événements CAN // CAN events are stored in CAN FIFO */
#define NWC_FF_NO_EVENT     0x0000  /* Pas de remonté des événements FF // FF events are ignored */
#define NWC_FF_EVENT        0x0004  /* Rem de gestion du 7402 // No 7402 management */
#define NWC_FLOW_7402       0x0008  /* Gestion du 7402 // 7402 management */
#define NWC_NOSPY_MODE      0x0000  // Le canal n'est pas en mode espion
#define NWC_SPY_MODE        0x0010  // Le canal est en mode espion

typedef struct
{
    tNwcAddrMode    eNwcAddrMode;   /* Mode d'adressage // Target address mode (1->1 or 1->n) */
    tNwcAddrFormat  eNwcAddrFormat; /* Format d'adressage // Address format (normal, fixe ...) */
    tNwcCommMode    eNwcCommMode;   /* Mode de communication // Communication mode */
    tNwcService     eNwcService;    /* Sens de la requête // Networw services */
    unsigned short  wParam;         /* (NWC_FIXED_LEN...) Paramètres supplémentaires // Further parameters */
} tNwcConfig;

typedef struct
{
    unsigned char   bSA;            /* Adresse source // Source address */
    unsigned char   bTA;            /* Adresse cible // Target address */
    unsigned char   bAE;            /* Adresse étendue // Extended address */
    unsigned char   bReserved;      /* Réservé // Reserved for future used */
    unsigned long   dwIdentTx;      /* Identificateur d'émission // Transmitter */
    tCanTypeId      eTypeIdTx;      /* Type d'identifcateur STD ou XTD // Identifier type (standard (11 bits) or extended (29 bits) */
    unsigned long   dwIdentFC;      /* Identificateur control de flux  // Flow Ccontrol Identifier */
    tCanTypeId      eTypeIdFC;      /* Type d'identifcateur STD ou XTD // Identifier type (standard (11 bits) or extended (29 bits) */
} tNwcAddr;

typedef struct
{
    tCanTypeId      eTypeId;        /* Type d'identifcateur STD ou XTD // Identifier type (standard (11 bits) or extended (29 bits) */
    unsigned long   dwIdentReq;     /* Identificateur de la requête et FC réponse // Request and FC response identifier */
    unsigned long   dwIdentRsp;     /* Identificateur de la réponse et FC requete // Response and FC request identifier */
    unsigned long   dwMask;		    /* Masque apposé sur l'identificateur           // Mask code */
    unsigned short  wParam;         /* (NWC_FIXED_LEN...) Paramètres supplémentaires // Further parameters */
} tNwcSpyAddr;

typedef struct
{
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[NWC_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tNwcMsg;

typedef enum
{
    NWC_NO_ERR              =   0x0000, /* Pas d'erreur                                 // No error */
    NWC_ERR_TOUT_AS         =   0x0001, /* Time out AS                                  // AS Time out */
    NWC_ERR_TOUT_BS         =   0x0002, /* Time out BS                                  // BS Time out */
    NWC_ERR_TOUT_AR         =   0x0003, /* Time out AR                                  // AR Time out */
    NWC_ERR_TOUT_CR         =   0x0004, /* Time out CR                                  // CR Time out */
    NWC_ERR_SN              =   0x0005, /* Séquence invalide                            // Invalid SN */
    NWC_ERR_FIFO_OVF        =   0x0010, /* Plus de place dans la fifo de trnasmission   // Fifo overflow */
    NWC_ERR_MEMORY          =   0x0011, /* Manque d'espace mémoire                      // Not enough memory */
    NWC_ERR_INV_PDU         =   0x0012, /* Format de PDU invalide                       // Invalid PDU format */
    NWC_ERR_INV_STATE       =   0x0013  /* Etat de réception incorrecte                 // Invalid State sequence */
} tNwcError;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                                // Bus number */
    unsigned short  wChannel;           /* Numéro de canal                              // Channel number */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement retourné à l'application    // Event type */
    unsigned long   dwIdent;            /* Identificateur du message                    // CAN identifier value */
    tCanTypeId      eTypeId;            /* Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) */
    unsigned long   dwTimeStamp;        /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                     // Time accuracy */
    tNwcService     eService;           /* Service de la requête                        // NWC services */
    tNwcError       eError;             /* Type d'erreur                                // Error type */
    unsigned long   dwReserved1;        /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[NWC_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tNwcEvent;

typedef struct 
{
	unsigned char bData[6];				/* Buffer de donnée								// Data buffer*/
    unsigned long   dwReserved1;        /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
} tNwcBytePadding;
/* Etat de la voie // Channel State */
#define NWC_CHANNEL_STATE_STARTED         0x0001  /* Canal démarré                            // Channel is activated */
#define NWC_CHANNEL_STATE_BUSY            0x0002  /* Canal en cours de communication          // Channel is currently transmitting ou receiving */

/*******************************************************************************
; Routines de segmentations ISO 15765-2 // ISO 15765-2 prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Autorise les fonctions ISO 15765-2                                       // Register ISO 15765 functions */
_MUXSPEC tMuxStatus _MUXAPI NwcRegister(char *szString, char *szKey);
/* Nbre de canaux de communication disponible                               // Channel communicaion available */
_MUXSPEC tMuxStatus _MUXAPI NwcGetChannelCount(unsigned short wCard, unsigned short wBus, unsigned short *wChannelCount);
/* Ouverture d'un canal de communication                                    // Open a channel communicaion */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelOpen(unsigned short wCard, unsigned short wBus, unsigned short *wChannel);
/* Configuration d'un canal de communication                                // Channel communicaion configuration */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelConfig(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcConfig *hNwcChannelConfig);
/* Paramètres de communication d'un canal                                   // Channel comm. parameter */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelParam(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcParam *hNwcChannelParam);
/* Paramètres les adresses d'un canal                                       // Channel addr. parameter */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelAddr(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcAddr *hNwcChannelAddr);
/* Autorise la communication sur le canal                                   // Channel start communication */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelStart(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Arrête la communication sur le canal                                     // Channel stop communication */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelStop(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Ferme le canal de communication                                          // Close a channel communication */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelClose(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI NwcSetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI NwcActivate(unsigned short wCard, unsigned short wBus);
/* Etat du bus decommunication                                              // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI NwcIsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI NwcDeactivate(unsigned short wCard, unsigned short wBus);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelSendMsg(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcMsg *hNwcChannelMsg);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelSendAsyncMsg(unsigned short wCard, unsigned short wBus, unsigned short wChannel, unsigned short wChannelRx, unsigned short wParam, tNwcMsg *hNwcChannelMsg);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI NwcGetEvent(unsigned short wCard, unsigned short wBus, tNwcEvent *hNwcEvent);
/* Retourne les identifcateurs utilisés                                     // Get CAN identifier in use */
_MUXSPEC tMuxStatus _MUXAPI NwcGetIdent(tNwcConfig *pstNwcConfig,tNwcAddr *pstNwcAddr);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI NwcGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI NwcConfigSpyMode(unsigned short wCard, unsigned short wBus, tNwcSpyAddr *hNwcSpyAddr);
/* Etat du canal de communication                                           // Channel communication state */
_MUXSPEC tMuxStatus _MUXAPI NwcGetChannelState(unsigned short wCard, unsigned short wBus, unsigned short wChannel, unsigned short *wChannelState, tNwcError *eLastTxStatus);
/* Personnalisation des octets de bourrage de trame							// padding byte customization  */
_MUXSPEC tMuxStatus _MUXAPI NwcChannelSetBytePadding(unsigned short wCard,unsigned short wBus, unsigned short wChannel, tNwcBytePadding *hNwcBytePadding );
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tNwcRegister)(char *szString, char *szKey);
typedef tMuxStatus (__stdcall * tNwcGetChannelCount)(unsigned short wCard, unsigned short wBus, unsigned short *wChannelCount);
typedef tMuxStatus (__stdcall * tNwcChannelOpen)(unsigned short wCard, unsigned short wBus, unsigned short *wChannel);
typedef tMuxStatus (__stdcall * tNwcChannelConfig)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcConfig *hNwcChannelConfig);
typedef tMuxStatus (__stdcall * tNwcChannelParam)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcParam *hNwcChannelParam);
typedef tMuxStatus (__stdcall * tNwcChannelAddr)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcAddr *hNwcChannelAddr);
typedef tMuxStatus (__stdcall * tNwcChannelStart)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwcChannelStop)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwcChannelClose)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwcSetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tNwcActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNwcIsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tNwcDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNwcChannelSendMsg)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwcMsg *hNwcChannelMsg);
typedef tMuxStatus (__stdcall * tNwcChannelSendAsyncMsg)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, unsigned short wChannelRx, unsigned short wParam, tNwcMsg *hNwcChannelMsg);
typedef tMuxStatus (__stdcall * tNwcGetIdent)(tNwcConfig *pstNwcConfig,tNwcAddr *pstNwcAddr);
typedef tMuxStatus (__stdcall * tNwcGetEvent)(unsigned short wCard, unsigned short wBus, tNwcEvent *hNwcEvent);
typedef tMuxStatus (__stdcall * tNwcGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus (__stdcall * tNwcConfigSpyMode)(unsigned short wCard, unsigned short wBus, tNwcSpyAddr *hNwcSpyAddr);
typedef tMuxStatus (__stdcall * tNwcGetChannelState)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, unsigned short *wChannelState, tNwcError *eLastTxStatus);
typedef tMuxStatus (__stdcall * tNwcChannelSetBytePadding)(unsigned short wCard,unsigned short wBus, unsigned short wChannel, tNwcBytePadding *hNwcBytePadding);
#endif
#ifdef __cplusplus
	}
#endif


/******************************************************************************
; Déclaration pour les routines J1939  // J1939 functions
******************************************************************************/
#define	J19_MAX_DATA	        1785	// Nbre de données max J1939                      // Maximum J1939 data length //
#define J19_NB_CHANNEL  32

typedef enum
{
	J19_SVC_TRANSMIT_DATA   =   0,      // Transmission de données                      // Transmit message //
	J19_SVC_RECEIVE_DATA    =   1       // Réception de données                         // Receive message //
} tJ19Service;

#define J19_CAN_NO_EVENT		0x0000
#define J19_CAN_EVENT           0x0001      // Indicateur si remonté des evtx par le CAN
#define J19_RTS_NO_EVENT		0x0000
#define J19_RTS_EVENT           0x0002      // Indicateur si remonté des evts FF
#define J19_SPY_MODE			0x0004

typedef enum
{
    J19_NO_ERR              =   0x0000, /* Pas d'erreur                                 // No error */
	J19_ERR_TR		        =   0x0001, /* */
	J19_ERR_TH		        =   0x0002, /* */
	J19_ERR_T1              =   0x0003, /* */
	J19_ERR_T2              =   0x0004, /* */
    J19_ERR_T3              =   0x0005, /* */
	J19_ERR_T4				=	0x0006,
	J19_ERR_BAM				=   0x0007,
	J19_ERR_CA				=	0x0008,
	J19_ERR_SN				= 	0x0009,
	J19_ERR_FIFO_OVF        =   0x0010,
    J19_ERR_MEMORY          =   0x0011,
} tJ19Error;

typedef struct
{
	unsigned short  wBus;               // Numéro de bus                                // Bus number //
	unsigned short  wChannel;           // Numéro de canal                              // Channel number //
	tMuxTypeEvent   eTypeEvent;         // Type d'événement retourné à l'application    // Event type //
	unsigned long   dwIdent;            // Identificateur du message                    // CAN identifier value //
	tCanTypeId      eTypeId;            // Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) //
	unsigned long   dwTimeStamp;        // Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec //
	unsigned short  wTimePrecision;     // Précision de la datation                     // Time accuracy //
	tJ19Service     eService;           // Service de la requête                        // NWC services //
	tJ19Error       eError;             // Type d'erreur                                // Error type //
	unsigned long   dwPGN;              // numéro du PGN					            // PGN Number //
	unsigned char	bSA;				// adresse source								// source addres//
	unsigned char	bReserved1;         // Réservé pour utilisation future              // Reserved //
	unsigned short  dwReserved2;        // Réservé pour utilisation future              // Reserved //
	unsigned short  wDataLen;           // Taille des données                           // Data length //
	unsigned char   bData[J19_MAX_DATA];// Buffer de donnée                             // Data buffer //
} tJ19Event;

typedef struct
{
	tJ19Service     eJ19Service;    // Sens de la requête // Networw services //
	unsigned short  wParam;         //
} tJ19Config;

typedef struct
{
	unsigned char bPriority;
	unsigned long dwPGN;
	unsigned char bSA;
}tJ19Addr;

typedef struct
{
	unsigned short  wDataLen;           /* Taille des données                           // Data length */
	unsigned char   bData[J19_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tJ19Msg;

typedef struct
{
	unsigned short wTr;
	unsigned short wTh;
	unsigned short wT1;
	unsigned short wT2;
	unsigned short wT3;
	unsigned short wT4;
} tJ19Param;

/******************************************************************************
; Routines de segmentations J1939 // J1939 prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelOpen(unsigned short wCard, unsigned short wBus, unsigned short *wChannel);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelAddr(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tJ19Addr * hJ19ChannelAddr);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelParam(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tJ19Param *hJ19ChannelParam);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelConfig(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tJ19Config *hJ19ChannelConfig);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelStart(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelStop(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelClose(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
_MUXSPEC tMuxStatus	_MUXAPI	J19Activate(unsigned short wCard, unsigned short wBus);
_MUXSPEC tMuxStatus	_MUXAPI	J19ConfigBus(unsigned short wCard, unsigned short wBus, unsigned short wParam);
_MUXSPEC tMuxStatus	_MUXAPI	J19Deactivate(unsigned short wCard, unsigned short wBus);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelSendMsg(unsigned short wCard, unsigned short wBus,unsigned short wChannel, tJ19Msg *hJ19ChannelMsg);
_MUXSPEC tMuxStatus	_MUXAPI	J19ChannelSendNMEAFastPacket(unsigned short wCard, unsigned short wBus,unsigned short wChannel, tJ19Msg *hJ19ChannelMsg);
_MUXSPEC tMuxStatus	_MUXAPI	J19SetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
_MUXSPEC tMuxStatus	_MUXAPI	J19GetEvent(unsigned short wCard, unsigned short wBus, tJ19Event *hJ19Event);
_MUXSPEC tMuxStatus	_MUXAPI	J19GetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
_MUXSPEC tMuxStatus	_MUXAPI	J19StoreNMEAFastPacket(unsigned short wCard, unsigned short wBus, unsigned long dwIdent, unsigned short wSize);

#else
typedef tMuxStatus	(__stdcall * tJ19ChannelOpen)(unsigned short wCard, unsigned short wBus, unsigned short *wChannel);
typedef tMuxStatus	(__stdcall * tJ19ChannelAddr)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tJ19Addr * hJ19ChannelAddr);
typedef tMuxStatus	(__stdcall * tJ19ChannelParam)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tJ19Param *hJ19ChannelParam);
typedef tMuxStatus	(__stdcall * tJ19ChannelConfig)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tJ19Config *hJ19ChannelConfig);
typedef tMuxStatus	(__stdcall * tJ19ChannelStart)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus	(__stdcall * tJ19ChannelStop)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus	(__stdcall * tJ19ChannelClose)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus	(__stdcall * tJ19Activate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus	(__stdcall * tJ19ConfigBus)(unsigned short wCard, unsigned short wBus, unsigned short wParam);
typedef tMuxStatus	(__stdcall * tJ19Deactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus	(__stdcall * tJ19ChannelSendMsg)(unsigned short wCard, unsigned short wBus,unsigned short wChannel, tJ19Msg *hJ19ChannelMsg);
typedef tMuxStatus	(__stdcall * tJ19ChannelSendNMEAFastPacket)(unsigned short wCard, unsigned short wBus,unsigned short wChannel, tJ19Msg *hJ19ChannelMsg);
typedef tMuxStatus	(__stdcall * tJ19SetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus	(__stdcall * tJ19GetEvent)(unsigned short wCard, unsigned short wBus, tJ19Event *hJ19Event);
typedef tMuxStatus	(__stdcall * tJ19GetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus	(__stdcall * tJ19StoreNMEAFastPacket)(unsigned short wCard, unsigned short wBus, unsigned long dwIdent, unsigned short wSize);
#endif
#ifdef __cplusplus
	}
#endif


/*******************************************************************************
; Déclaration pour les routines LIN  // LIN functions
*******************************************************************************/
#define	LIN_MAX_DATA	        		8		/* Nbre de données max LIN                      // Maximum LIN data length */

#define LIN_PERIODIC_PARAM_ENABLE		1		/* Active la périodique							// Enable periodic frame */
#define LIN_PERIODIC_PARAM_DISABLE		0		/* Desactive la periodique						// Disable periodic frame */
#define LIN_PERIODIC_PARAM_WITHEVENTS	2		/* Active la remontée des événements			// Enable the events */
#define LIN_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

typedef enum
{
    LIN_OPER_ANA_FIFO       =   0       /* Mode analyse, stockage fifo                  // Analyse mode, event is stored in fifo mode */
} tLinOperMode;

typedef struct
{
    tLinOperMode    eLinOperMode;       /* Type d'interface avec l'application          // Operating mode with API */
    unsigned short  wFifoSize;          /* Taille de la FIFO                            // FIFO Size */
} tLinOper;
typedef enum
{
    LIN_BAUD_2400   =   2400L,	    	/* 2400 baud */
    LIN_BAUD_9600   =   9600L,	    	/* 9600 baud */
	LIN_BAUD_10400	=	10400L,			/* 10400 baud */
    LIN_BAUD_19200  =   19200L,	    	/* 19200 baud */
    LIN_BAUD_20833  =   20833L,	    	/* 20833 baud */
	LIN_BAUD_38400	=	38400L	 	    /* 38400 baud */
} tLinBaudRate;
typedef enum
{
    LIN_GEN_NO_ERR          =   0x0000, /* Pas d'erreur                                 // No error */
    LIN_GEN_ERR_P0          =   0x0001, /* Erreur du bit de parité P0                   // P0 parity error */
    LIN_GEN_ERR_P1          =   0x0002, /* Erreur du bit de parité P1                   // P1 parity error */
    LIN_GEN_ERR_CRC         =   0x0003, /* Erreur de CRC                                // CRC error */
    LIN_GEN_ERR_SYNCH       =   0x0004, /* Erreur de caractère de synchro               // Synchro char error */
    LIN_GEN_ERR_DATP1       =   0x0005, /* + 1 octet de donnée                          // +1 byte in data field */
    LIN_GEN_ERR_DATP2       =   0x0006, /* + 2 octets de données                        // +2 bytes in data field */
    LIN_GEN_ERR_DATL1       =   0x0007, /* - 1 octet de donnée                          // -1 byte in data field */
    LIN_GEN_ERR_DATL2       =   0x0008, /* - 2 octets de données                        // -2 bytes in data field */
//	LIN_GEN_FREE_ID         =   0x0009,  /* Identificateur libre                         // Free ident */
    LIN_GEN_FREE_ID         =   0x0100, /* Identificateur libre                         // Free ident */
	LIN_GEN_CLASSIC_CRC     =   0x0200  /* Force le checksum classique                  // Classic checksum */
}
tLinGenErr;
typedef enum
{
    LIN_NO_ERR              =   0x0000, /* Pas d'erreur                                 // No error */
    LIN_ERR_BIT             =   0x0001, /* Erreur de bit                                // Bit error */
    LIN_ERR_CRC             =   0x0002, /* Erreur dans le calcul du CRC                 // CRC error */
    LIN_ERR_TIMEOUT         =   0x0003, /* Time out réponse esclave                     // Slave not responding */
    LIN_ERR_PARITY          =   0x0004, /* Erreur de parité                             // Parity error */
    LIN_ERR_SYNCHRO         =   0x0005, /* Erreur de réception du car de synchro        // Inconsistent synch bit error */
    LIN_ERR_LENGTH          =   0x0006, /* Erreur de réception de la longueur           // Length requested error */
    LIN_ERR_TO_TX           =   0x0007, /* Time out en transmission                     // Timeout while transmitting */
    LIN_ERR_TO_SYNCHRO      =   0x0008, /* Time out sur rx du car de synchro            // Timeout waiting synchro field */
    LIN_ERR_TO_IDENT        =   0x0009, /* Time out sur rx du car ident                 // Timeout waiting ident field */
    LIN_ERR_TO_DATA         =   0x000A, /* Time out sur rx des données                  // Timeout waiting data field */
    LIN_ERR_TO_CRC          =   0x000B  /* Time out sur rx CRC                          // Timeout waiting CRC field */
} tLinError;
typedef enum
{
    LIN_SVC_TRANSMIT_DATA   =   0,      /* Transmission de données                      // Transmit message */
    LIN_SVC_RECEIVE_DATA    =   1,      /* Réception de données                         // Receive message */
    LIN_SVC_REQUEST_IFR     =   2,      /* Demande de réponse dans la trame             // Reply IFR message */
    LIN_SVC_UPDATE_IFR      =   3,      /* Mise à jour pour réponse dans la trame       // Update IFR (without transmission) */
    LIN_SVC_WAKEUP          =   4       /* Indication réception signal de wakeup        // Wake up signal detected */
} tLinService;
typedef enum
{
    LIN_BUS_NOMINAL         =   0,      /* Etat nominal                                 // Nominal state */
    LIN_BUS_ERROR           =   1,      /* Etat erreur                                  // Error state */
    LIN_BUS_IDLE            =   2       /* Etat bus idle                                // Bus idle state */
} tLinChipState;
typedef enum
{
    LIN_FALSE               =   0,      /* Booléen faux                                 // FALSE */
    LIN_TRUE                =   1       /* Booléen vrai                                 // TRUE */
} tLinBoolean;
typedef struct
{
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
    unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
    unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
    unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
    unsigned long   dwErrBit;           /* Erreur de type Bit                           // Bit error */
    unsigned long   dwErrCrc;           /* Erreur de CRC                                // CRC error */
    unsigned long   dwErrTimeOut;       /* Erreur de time-out                           // Timeout error */
    unsigned long   dwErrSynchro;       /* Erreur de caractère de synchro               // Inconsistent synch bit error */
    unsigned long   dwErrIdent;         /* Erreur de caractère ident                    // Ident error */
    unsigned long   dwErrOther;         /* Erreur autre                                 // Other error */
    unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tLinStat;

typedef struct
{
    tLinBaudRate    eBaudRate;          /* Débit du bus                                 // Baud rate */
} tLinBus;

typedef struct
{
    tLinBoolean     eDefDelayBusIdle;   /* Utilisation des délais par défaut            // Default delay for bus idle */
    unsigned long   dwDelayBusIdle;     /* Delai avant bus idle                         // Delay before detect bus idle */
    unsigned short  wSpecialModes;      /* Réservé pour utilisation futures             // Reserved for future used */
} tLinParam;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                                // Bus number */
    unsigned short  wHandleMsg;         /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement retourné à l'application    // Event type */
    unsigned short  wIdent;             /* Identificateur du message                    // LIN identifier value */
    unsigned long   dwTimeStamp;        /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                     // Time accuracy */
    tLinService     eService;           /* Service de la requête                        // LIN services */
    tLinError       eError;             /* Type d'erreur                                // Error type */
    tLinChipState   eChipState;         /* Etat du composants                           // Chip state */
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned long   dwReserved1;        /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[LIN_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tLinEvent;

typedef struct
{
    unsigned short  wHandleMsg;         /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    unsigned short  wIdent;             /* Identificateur LIN du message                // LIN Identifier value */
    tLinService     eService;           /* Service de la requête                        // LIN services */
    unsigned long   lPeriod;            /* Periodicité en ms                            // Period */
    tLinBoolean     eLevel3Enable;      /* Gestion des couches de communication         // Enable communication management */
    tLinGenErr      eLinGenErr;         /* Gestion erronéé du protocole                 // Generate protocol error */
    unsigned long   dwReserved1;        /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned long   dwReserved2;        /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[LIN_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tLinMsg;

typedef struct
{
	unsigned short	wOffset;			/* Offset du message periodic					// Offset du message periodic */
	unsigned short	wParam;				/* Paramètre pour la périodique					// Parameters for the periodic */
    tLinMsg			hLinMsg;			/* Message à émettre							// Message to send */
} tLinPeriodicMsg;

/*******************************************************************************
; Routines LIN // LIN prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du mode de fonctionnement des buffers                      // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI LinConfigOper(unsigned short wCard, unsigned short wBus, tLinOper *hLinOper);
/* Configuration du bus                                                     // Bus parameter */
_MUXSPEC tMuxStatus _MUXAPI LinConfigBus(unsigned short wCard, unsigned short wBus, tLinBus *hLinBus);
/* Paramètres de configuration                                              // Uart parameter */
_MUXSPEC tMuxStatus _MUXAPI LinConfigUart(unsigned short wCard, unsigned short wBus, tUartConfig *hUartConfig);
/* Configuration des paramètres supplémentaires                             // Extra parameter */
_MUXSPEC tMuxStatus _MUXAPI LinConfigParam(unsigned short wCard, unsigned short wBus, tLinParam *hLinParam);
/* Configuration des statistques                                            // Statistics configuration */
_MUXSPEC tMuxStatus _MUXAPI LinConfigStat(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
/* Configuration de la version                                              // Version setup */
_MUXSPEC tMuxStatus _MUXAPI LinSetVersion(unsigned short wCard, unsigned short wBus, unsigned long dwVersion);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI LinSetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI LinActivate(unsigned short wCard, unsigned short wBus);
/* Etat du bus de communication                                             // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI LinIsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Configuration de l'impédance de ligne Maitre ou Esclave                  // Master or Slave Bus line configuration */
_MUXSPEC tMuxStatus _MUXAPI LinConfigTransceiver(unsigned short wCard, unsigned short wBus, unsigned short wEnable, unsigned short wRMaster);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI LinConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tLinMsg *hLinMsg);
/* Création d'une liste de message periodide								// Periodic message list configuration */
_MUXSPEC tMuxStatus _MUXAPI LinConfigPeriodicList(unsigned short wCard, unsigned short wBus, unsigned short wPeriodicCount, tLinPeriodicMsg *hLinPeriodicMsgList);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI LinDeactivate(unsigned short wCard, unsigned short wBus);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI LinSendMsg(unsigned short wCard, unsigned short wBus, tLinMsg *hLinMsg);
/* Emission d'une liste de message											// Transmit a list of message */
_MUXSPEC tMuxStatus _MUXAPI LinSendMsgList(unsigned short wCard, unsigned short wBus, unsigned short wMsgCount, tLinMsg *hLinMsgList);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI LinGetEvent(unsigned short wCard, unsigned short wBus, tLinEvent *hLinEvent);

/* Lecture des statistiques                                                 // Statistics information */
_MUXSPEC tMuxStatus _MUXAPI LinGetStat(unsigned short wCard, unsigned short wBus, tLinStat *hLinStat);
/* Récupération de l'état du contrôleur de protocole                        // CAN controller state */
_MUXSPEC tMuxStatus _MUXAPI LinGetBusState(unsigned short wCard, unsigned short wBus, tLinChipState *eLinChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
/* Emission d'un message de mise en veille du bus                           // Sleep mode command message */
_MUXSPEC tMuxStatus _MUXAPI LinSetSleepMode(unsigned short wCard, unsigned short wBus);
/* Emission d'un signal de réveil                                           // WakeUp signal */
_MUXSPEC tMuxStatus _MUXAPI LinSetWakeUpMode(unsigned short wCard, unsigned short wBus);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI LinClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Purge du buffer d'émission des IFR                                  		// Flush FIFO IFR */
_MUXSPEC tMuxStatus _MUXAPI LinClearBufferIFR(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI LinGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);

#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tLinConfigOper)(unsigned short wCard, unsigned short wBus, tLinOper *hLinOper);
typedef tMuxStatus (__stdcall * tLinConfigBus)(unsigned short wCard, unsigned short wBus, tLinBus *hLinBus);
typedef tMuxStatus (__stdcall * tLinConfigUart)(unsigned short wCard, unsigned short wBus, tUartConfig *hUartConfig);
typedef tMuxStatus (__stdcall * tLinConfigParam)(unsigned short wCard, unsigned short wBus, tLinParam *hLinParam);
typedef tMuxStatus (__stdcall * tLinConfigStat)(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
typedef tMuxStatus (__stdcall * tLinSetVersion)(unsigned short wCard, unsigned short wBus, unsigned long dwVersion);
typedef tMuxStatus (__stdcall * tLinSetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tLinActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tLinIsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tLinConfigTransceiver)(unsigned short wCard, unsigned short wBus, unsigned short wEnable, unsigned short wRMaster);
typedef tMuxStatus (__stdcall * tLinConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tLinMsg *hLinMsg);
typedef tMuxStatus (__stdcall * tLinConfigPeriodicList)(unsigned short wCard, unsigned short wBus, unsigned short wPeriodicCount, tLinPeriodicMsg *hLinPeriodicMsgList);
typedef tMuxStatus (__stdcall * tLinDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tLinSendMsg)(unsigned short wCard, unsigned short wBus, tLinMsg *hLinMsg);
typedef tMuxStatus (__stdcall * tLinSendMsgList)(unsigned short wCard, unsigned short wBus, unsigned short wMsgCount, tLinMsg *hLinMsgList);
typedef tMuxStatus (__stdcall * tLinGetEvent)(unsigned short wCard, unsigned short wBus, tLinEvent *hLinEvent);
typedef tMuxStatus (__stdcall * tLinGetStat)(unsigned short wCard, unsigned short wBus, tLinStat *hLinStat);
typedef tMuxStatus (__stdcall * tLinGetBusState)(unsigned short wCard, unsigned short wBus, tLinChipState *eLinChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
typedef tMuxStatus (__stdcall * tLinSetSleepMode)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tLinSetWakeUpMode)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tLinClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tLinClearBufferIFR)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tLinGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
#endif

#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines NWL // NWL definitions
*******************************************************************************/
#define	NWL_MAX_DATA	        4095	/* Nbre de données max NWL                      // Maximum NWL data length */

typedef enum
{
    NWL_SVC_TRANSMIT_DATA   =   0,      /* Transmission de données (Maître)             // Transmit message */
    NWL_SVC_RECEIVE_DATA    =   1,      /* Réception de données (Esclave)               // Receive message */
    NWL_SVC_REQUEST_IFR     =   2,      /* Réception de données (Maître)                // Receive message */
    NWL_SVC_UPDATE_IFR      =   3       /* Transmission de données (Esclave)            // Transmit message */
} tNwlService;

typedef struct
{
    unsigned short wN_Cs;           /* Délai entre 2 blocs // Separation time */
    unsigned short wN_As;           /* Délai max de transmission coté transmetteur // Time for transmission (transmitter side) */
    unsigned short wN_Cr;           /* Délai jusqu'à réception du CF // Time until reception of next CF */
    unsigned short wP2min;          /* Délai REQ / REP  MASTER : time-out UCE : [50-500ms] // Time out between master request and slave(s) response(s) */
    unsigned short wP2max;          /* Délai REQ / REP  MASTER : time-out UCE : [50-500ms] // Time out between master request and slave(s) response(s) */
    unsigned short uwReserved1;		   // Reserved for future use
    unsigned short uwReserved2;		   // Reserved for future use
    unsigned short uwReserved3;		   // Reserved for future use
} tNwlParam;

#define NWL_LIN_NO_EVENT    0x0000  /* Pas de remonté des événements LIN // LIN events are ignored */
#define NWL_LIN_EVENT       0x0001  /* Remonté des événements LIN // LIN events are stored in LIN FIFO */
#define NWL_FF_NO_EVENT     0x0000  /* Pas de remonté des événements FF // FF events are ignored */
#define NWL_FF_EVENT        0x0002  /* Remonté des événements FF // FF events are stored in NWL FIFO */

typedef struct
{
    tNwlService     eNwlService;    /* Sens de la requête // Networw services */
    unsigned short uwReserved1;		   // Reserved for future use
    unsigned short uwReserved2;		   // Reserved for future use
    unsigned short  wParam;         /* Paramètres supplémentaires // Further parameters */
} tNwlConfig;

typedef struct
{
    unsigned short  wNad;           /* Identificateur du noeud // Node address */
    unsigned long   dwReserved1;    /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;    /* Réservé pour utilisation future              // Reserved */
} tNwlAddr;

typedef struct
{
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[NWL_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tNwlMsg;

typedef enum
{
    NWL_NO_ERR              =   0x0000, /* Pas d'erreur                                 // No error */
    NWL_ERR_TOUT_AS         =   0x0001, /* Time out AS                                  // AS Time out */
    NWL_ERR_TOUT_CR         =   0x0002, /* Time out CR                                  // CR Time out */
    NWL_ERR_TOUT_P2         =   0x0003, /* Time out P2                                  // P2 Time out */
    NWL_ERR_SN              =   0x0004, /* Séquence invalide                            // Invalid SN */
    NWL_ERR_FIFO_OVF        =   0x0005, /* Plus de place dans la fifo de transmission   // Fifo overflow */
    NWL_ERR_MEMORY          =   0x0006, /* Manque d'espace mémoire                      // Not enough memory */
    NWL_ERR_INV_PDU         =   0x0007, /* Format de PDU invalide                       // Invalid PDU format */
    NWL_ERR_INV_STATE       =   0x0008  /* Etat de réception incorrecte                 // Invalid State sequence */
} tNwlError;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                                // Bus number */
    unsigned short  wChannel;           /* Numéro de canal                              // Channel number */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement retourné à l'application    // Event type */
    unsigned short  wNad;               /* Identificateur du message                    // LIN identifier value */
    unsigned long   dwTimeStamp;        /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                     // Time accuracy */
    tNwlService     eService;           /* Service de la requête                        // NWL services */
    tNwlError       eError;             /* Type d'erreur                                // Error type */
    unsigned long   dwReserved1;        /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[NWL_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tNwlEvent;

/* Etat de la voie // Channel State */
#define NWL_CHANNEL_STATE_STARTED         0x0001  /* Canal démarré                            // Channel is activated */
#define NWL_CHANNEL_STATE_BUSY            0x0002  /* Canal en cours de communication          // Channel is currently transmitting ou receiving */

/*******************************************************************************
; Routines de segmentations ISO 15765-2 // ISO 15765-2 prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Nbre de canaux de communication disponible                               // Channel communicaion available */
_MUXSPEC tMuxStatus _MUXAPI NwlGetChannelCount(unsigned short wCard, unsigned short wBus, unsigned short *wChannelCount);
/* Ouverture d'un canal de communication                                    // Open a channel communicaion */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelOpen(unsigned short wCard, unsigned short wBus, unsigned short *wChannel);
/* Configuration d'un canal de communication                                // Channel communicaion configuration */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelConfig(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlConfig *hNwlChannelConfig);
/* Paramètres de communication d'un canal                                   // Channel comm. parameter */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelParam(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlParam *hNwlChannelParam);
/* Paramètres les adresses d'un canal                                       // Channel addr. parameter */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelAddr(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlAddr *hNwlChannelAddr);
/* Autorise la communication sur le canal                                   // Channel start communication */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelStart(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Arrête la communication sur le canal                                     // Channel stop communication */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelStop(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Ferme le canal de communication                                          // Close a channel communication */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelClose(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI NwlSetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI NwlActivate(unsigned short wCard, unsigned short wBus);
/* Etat du bus decommunication                                              // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI NwlIsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI NwlDeactivate(unsigned short wCard, unsigned short wBus);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelSendMsg(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlMsg *hNwlChannelMsg);
/* Réception d'un message                                                    // Receive a message */
_MUXSPEC tMuxStatus _MUXAPI NwlChannelReceiveMsg(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI NwlGetEvent(unsigned short wCard, unsigned short wBus, tNwlEvent *hNwlEvent);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI NwlGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
/* Etat du canal de communication                                           // Channel communication state */
_MUXSPEC tMuxStatus _MUXAPI NwlGetChannelState(unsigned short wCard, unsigned short wBus, unsigned short wChannel, unsigned short *wChannelState, tNwlError *eLastTxStatus);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tNwlGetChannelCount)(unsigned short wCard, unsigned short wBus, unsigned short *wChannelCount);
typedef tMuxStatus (__stdcall * tNwlChannelOpen)(unsigned short wCard, unsigned short wBus, unsigned short *wChannel);
typedef tMuxStatus (__stdcall * tNwlChannelConfig)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlConfig *hNwlChannelConfig);
typedef tMuxStatus (__stdcall * tNwlChannelParam)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlParam *hNwlChannelParam);
typedef tMuxStatus (__stdcall * tNwlChannelAddr)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlAddr *hNwlChannelAddr);
typedef tMuxStatus (__stdcall * tNwlChannelStart)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwlChannelStop)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwlChannelClose)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwlSetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tNwlActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNwlIsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tNwlDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNwlChannelSendMsg)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, tNwlMsg *hNwlChannelMsg);
typedef tMuxStatus (__stdcall * tNwlChannelReceiveMsg)(unsigned short wCard, unsigned short wBus, unsigned short wChannel);
typedef tMuxStatus (__stdcall * tNwlGetEvent)(unsigned short wCard, unsigned short wBus, tNwlEvent *hNwlEvent);
typedef tMuxStatus (__stdcall * tNwlGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus (__stdcall * tNwlGetChannelState)(unsigned short wCard, unsigned short wBus, unsigned short wChannel, unsigned short *wChannelState, tNwlError *eLastTxStatus);
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines VAN  // VAN functions
*******************************************************************************/
#define	VAN_MAX_DATA	        		28		/* Nbre de données max VAN                      // Maximum VAN data length */

#define VAN_PERIODIC_PARAM_ENABLE		1		/* Active la périodique							// Enable periodic frame */
#define VAN_PERIODIC_PARAM_DISABLE		0		/* Desactive la periodique						// Disable periodic frame */
#define VAN_PERIODIC_PARAM_WITHEVENTS	2		/* Active la remontée des événements			// Enable the events */
#define VAN_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

typedef enum
{
    VAN_OPER_ANA_FIFO       =   0,      /* Mode analyse, stockage fifo                  // Analyse mode, event is stored in fifo mode */
    VAN_OPER_ANA_BUFF       =   1,      /* Mode analyse, stockage buffer                // Analyse mode, event is stored in buffer mode */
    VAN_OPER_SIMU_FIFO      =   2,      /* Mode simulation, stockage fifo               // Simulation mode, event is stored in fifo mode */
    VAN_OPER_SIMU_BUFF      =   3       /* Mode simulation, stockage buffer             // Simulation mode, event is stored in buffer mode */
} tVanOperMode;

typedef struct
{
    tVanOperMode    eVanOperMode;       /* Type d'interface avec l'application          // Operating mode with API */
    unsigned short  wFifoSize;          /* Taille de la FIFO                            // FIFO Size */
} tVanOper;

typedef enum
{
    VAN_BAUD_5      =   5208L,	    	/* 5,21  kTS */
    VAN_BAUD_7	    =   7812L,	    	/* 7,81  kTS */
    VAN_BAUD_10	    =   10416L,	    	/* 10,42 kTS */
    VAN_BAUD_15	    =   15625L,	    	/* 15,63 kTS */
    VAN_BAUD_20	    =   20833L,	    	/* 20,83 kTS */
    VAN_BAUD_31	    =   31250L,	    	/* 31,25 kTS */
    VAN_BAUD_41	    =   41666L,	    	/* 41,57 kTS */
    VAN_BAUD_62	    =   62500L,		    /* 62,5  kTS */
    VAN_BAUD_83	    =   83333L,		    /* 83,33 kTS */
    VAN_BAUD_125	=   125000L,		/* 125   kTS */
    VAN_BAUD_166	=   166666L,		/* 166,67kTS */
    VAN_BAUD_250	=   250000L,		/* 250   kTS */
    VAN_BAUD_333	=   333333L,		/* 333,33kTS */
    VAN_BAUD_500	=   500000L,		/* 500   kTS */
    VAN_BAUD_666	=   666666L,		/* 666,67kTS */
    VAN_BAUD_1000	=   1000000L 		/* 1000  kTS */
} tVanBaudRate;
typedef enum
{
    VAN_LINE_NOT_INVERTED   =   0,      /* Ligne non inversée                           // Line is not inverted */
    VAN_LINE_INVERTED       =   1       /* Ligne inversée                               // Line is inverted */
} tVanLine;
typedef enum
{
    VAN_CODING_MANCHESTER   =   0,      /* Codage manchester comprimé                   // Data is transmitted or received in enhanced manchester code */
    VAN_CODING_PULSED       =   1       /* Codage mode pulsé                            // Data is transmitted or received in pulsed mode */
} tVanCoding;
typedef enum
{
    VAN_MODULE_SYNCHRONOUS  =   0,      /* Module synchrone (en attente de SOF)         // Synchronous access module (ECU is waiting SOF before transmitted) */
    VAN_MODULE_AUTONOMOUS   =   1       /* Module autonome                              // Autonomous module */
} tVanModuleType;
typedef enum
{
    VAN_FALSE               =   0,      /* Booléen faux                                 // FALSE */
    VAN_TRUE                =   1       /* Booléen vrai                                 // TRUE  */
} tVanBoolean;
typedef enum
{
    VAN_RX_FORCED_RXD0      =   0,      /* Communication forçée sur RXD0                // Communication is forced on RXD0 (differential) */
    VAN_RX_FORCED_RXD1      =   2,      /* Communication forçée sur RXD1                // Communication is forced on RXD2 (datab) */
    VAN_RX_FORCED_RXD2      =   1,      /* Communication forçée sur RXD2                // Communication is forced on RXD1 (data) */
    VAN_RX_AUTOMATIC        =   3       /* Communication en mode automatique            // Automatic selection */
} tVanRxMode;
typedef enum
{
    VAN_SVC_TRANSMIT_DATA   =   0,      /* Transmission de données                      // Transmit message */
    VAN_SVC_RECEIVE_DATA    =   1,      /* Réception de données                         // Receive message */
    VAN_SVC_REQUEST_IFR     =   2,      /* Demande de réponse dans la trame             // Reply IFR message */
    VAN_SVC_UPDATE_IFR      =   3,      /* Mise à jour pour réponse dans la trame       // Update IFR (without transmission) */
    VAN_SVC_TX_DIFFERED     =   4,      /* Transmission d'une réponse différée          // Transmit differed message */
    VAN_SVC_RX_DIFFERED     =   5       /* Réception d'une réponse différée             // Receive differed message */
} tVanService;
typedef enum
{
    VAN_NO_ERR              =   0x0000, /* Pas d'erreur                                 // No error */
    VAN_ERR_BOC             =   0x0001, /* Buffer occupé                                // Buffer occupied */
    VAN_ERR_BOV             =   0x0002, /* Dépassement du buffer                        // Buffer overflow */
    VAN_ERR_TYPE            =   0x0003, /* Erreur de service VAN                        // Erreur type mismatch */
    VAN_ERR_FCSE            =   0x0004, /* Erreur de CRC                                // CRC error */
    VAN_ERR_ACKE            =   0x0005, /* Erreur d'acquittement                        // ACK error */
    VAN_ERR_CV              =   0x0006, /* Viol de code                                 // Code violation */
    VAN_ERR_FV              =   0x0007, /* Viol de trame                                // Frame violation */
    VAN_ERR_NOIFR           =   0x0100  /* Plus de place pour IFR                       // No buffer for IFR */
} tVanError;
typedef enum
{
    VAN_RX_NOMINAL          =   0,      /* Communication en mode différentiel           // Nominal mode */
    VAN_RX_FAULT_ON_DATA    =   1,      /* Communication sur Datab                      // Communication on Datab */
    VAN_RX_FAULT_ON_DATAB   =   2,      /* Communication sur Data                       // Communication on Data */
    VAN_RX_MAJOR_ERROR      =   3       /* Pas de communication                         // Major error */
} tVanChipState;
typedef enum
{
    VAN_SLEEP_MODE          =   0,      /* Mise en veille du réseau (Maître)            // VAN sleep (master node) */
    VAN_NO_SLEEP_MODE       =   1       /* Réveil du réseau (Maître)                    // VAN wakeup (master node) */
} tVanSleepMode;
typedef enum
{
    VAN_WAKEUP_MODE         =   1,      /* Réveil du réseau (Esclave)                   // VAN wakeup (slave node) */
    VAN_NO_WAKEUP_MODE      =   0       /* Pas de réveil du réseau (Esclave)            // No action */
} tVanWakeUpMode;

typedef struct
{
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
    unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
    unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
    unsigned long   dwTxErr;            /* Fin de transmission incorrecte               // Error end of tx */
    unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
    unsigned long   dwRxErr;            /* Réception en erreur                          // Error during reception */
    unsigned long   dwErrBoc;           /* Buffer occupé                                // Buffer occupied error */
    unsigned long   dwErrBov;           /* Dépassement de buffer                        // Buffer overflow error */
    unsigned long   dwErrType;          /* Erreur de service VAN                        // Type mismatch error */
    unsigned long   dwErrFcse;          /* Erreur de CRC                                // CRC Error */
    unsigned long   dwErrAcke;          /* Erreur d'acquittement                        // ACK error */
    unsigned long   dwErrCv;            /* Viol de code                                 // Code violation */
    unsigned long   dwErrFv;            /* Viol de trame                                // Frame violation */
    unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tVanStat;

typedef struct
{
    tVanBaudRate    eBaudRate;          /* Débit du bus                                 // Baud rate */
    tVanLine        eLineInvertTx;      /* Inversion de la ligne TX                     // Invert TxD output */
    tVanLine        eLineInvertRx;      /* Inversion de la ligne RX                     // Invert Rx input */
    tVanCoding      eLineCoding;        /* Mode pulsé ou manchester                     // Enhanced manchester or plused mode */
    unsigned short  wMaxRetries;        /* Nbre de répétition                           // Number of retries */
    tVanModuleType  eModuleType;        /* Type de module                               // Module type */
    tVanBoolean     eTIPEnable;         /* Validation du diag en émission               // Enable transmission diagnosis */
    tVanBoolean     eSDCEnable;         /* Validation de l'horloge SDC                  // Enable synchronous diagnosis clock */
    unsigned short  wSDCValue;          /* Valeur de l'horloge SDC                      // Diagnosis clock value */
    tVanRxMode      eRxMode;            /* Mode de réception                            // Rx Line mode operation */
} tVanBus;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                                // Bus number */
    unsigned short  wHandleMsg;         /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement retourné à l'application    // Event type */
    unsigned short  wIdent;             /* Identificateur du message                    // VAN identifier value */
    unsigned long   dwTimeStamp;        /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                     // Time accuracy */
    tVanService     eService;           /* Service de la requête                        // VAN services */
    tVanBoolean     eAckEnable;         /* Acquittement                                 // Acknowledgment indication */
    tVanError       eError;             /* Type d'erreur                                // Error type */
    tVanChipState   eChipState[2];      /* Etat de la comm. des composants 1 et 2       // Current Rx. line mode*/
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned long   dwReserved1;        /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[VAN_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tVanEvent;

typedef struct
{
    unsigned short  wHandleMsg;         /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    unsigned short  wIdent;             /* Identificateur VAN du message                // VAN Identifier value */
    unsigned short  wMask;				/* Masque apposé sur l'identificateur           // Mask associated with VAN identifier */
    tVanService     eService;           /* Service de la requête                        // VAN services */
    tVanBoolean     eAckEnable;         /* Demande d'acquittement                       // Request acknowlegment */
    unsigned long   lPeriod;            /* Periodicité en ms                            // Period */
    tVanBoolean     eLevel3Enable;      /* Gestion des couches de communication         // Enable communication management */
    unsigned short  wNumChip;           /* Num. de composant lié avec le msg (Infos DLL)// Chip number associated with the message returned by DLL */
    unsigned short  wNumChannel;        /* Num. de canal dans le composant (Infos DLL)  // Channel number inside the chip returned by DLL */
    unsigned short  wMaxSize;           /* Taille max par message (Infos DLL)           // Maximum size (Reserved for DLL) */
    unsigned long   dwReserved1;        /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned long   dwReserved2;        /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[VAN_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tVanMsg;

typedef struct
{
	unsigned short	wOffset;			/* Offset de la périodique						// Periodic offset */
	unsigned short	wParam;				/* Paramètre de la périodique					// Periodic parameters */
	tVanMsg			hVanMsg;			/* Message à emettre							// Frame to send */
} tVanPeriodicMsg;

typedef struct
{
    unsigned short  wSizeTx;            /* Taille max. des tx et demande d'IFR          // Maximum data length for Tx and reply request */
    unsigned short  wSizeRx;            /* Taille max. des rx (données et différée)     // Maximum data length for Rx data and differed */
    unsigned short  wSizeIfr;           /* Taille max. des IFR                          // Maximum data length for IFR */
    unsigned short  wFiltIdent;         /* Identificateur pour filtrage                 // Acceptance code */
    unsigned short  wFiltMask;          /* Masque pour filtrage                         // Acceptance mask */
    tVanBoolean     eAckEnable;         /* Validation / dévalidation de l'acquittement  // Enable or disable acknowlegment */
    tVanBoolean     eRxAll;             /* Réception des ident non déclarés             // All messages or only programmed message are given to the application */
    unsigned short  wSpecialModes;      /* Réservé pour utilisation futures             // Reserved for future used */
} tVanParam;

/*******************************************************************************
; Routines VAN // VAN prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du mode de fonctionnement des buffers                      // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI VanConfigOper(unsigned short wCard, unsigned short wBus, tVanOper *hVanOper);
/* Configuration du bus                                                     // Bus parameter */
_MUXSPEC tMuxStatus _MUXAPI VanConfigBus(unsigned short wCard, unsigned short wBus, tVanBus *hVanBus);
/* Configuration des paramètres supplémentaires                             // Extra parameter */
_MUXSPEC tMuxStatus _MUXAPI VanConfigParam(unsigned short wCard, unsigned short wBus, tVanParam *hVanParam);
/* Configuration des statistques                                            // Statistics configuration */
_MUXSPEC tMuxStatus _MUXAPI VanConfigStat(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
/* Création des messages de communication                                   // Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI VanCreateMsg(unsigned short wCard, unsigned short wBus, tVanMsg *hVanMsg);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI VanConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tVanMsg *hVanMsg);
/* Configuration d'une liste de message periodique							// Periodic messages list configuration */
_MUXSPEC tMuxStatus _MUXAPI VanConfigPeriodicList(unsigned short wCard, unsigned short wBus, unsigned short wPeriodicCount, tVanPeriodicMsg *hVanPeriodicMsgList);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI VanSetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI VanActivate(unsigned short wCard, unsigned short wBus);
/* Etat du bus decommunication                                              // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI VanIsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI VanDeactivate(unsigned short wCard, unsigned short wBus);
/* Emission d'un message ou mise à jour pour réponse dans la trame          // Transmit a message or update an IFR */
_MUXSPEC tMuxStatus _MUXAPI VanSendMsg(unsigned short wCard, unsigned short wBus, tVanMsg *hVanMsg);
/* Emission de plusieurs message											// Transmit several messages */
_MUXSPEC tMuxStatus _MUXAPI VanSendMsgList(unsigned short wCard, unsigned short wBus, unsigned short wMsgCount, tVanMsg *hVanMsgList);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI VanGetEvent(unsigned short wCard, unsigned short wBus, tVanEvent *hVanEvent);

/* Lecture des statistiques                                                 // Statistics information */
_MUXSPEC tMuxStatus _MUXAPI VanGetStat(unsigned short wCard, unsigned short wBus, tVanStat *hVanStat);
/* Lecture du mode de communication des composants                          // Give information about Rx communication mode */
_MUXSPEC tMuxStatus _MUXAPI VanGetBusState(unsigned short wCard, unsigned short wBus, tVanChipState *eVanChip0State, tVanChipState *eVanChip1State);
/* Active la broche sleep de l'interface de ligne REMX (Maître)             // REMX SleepB pins setup (used by a master node to sleep or wakeup the bus */
_MUXSPEC tMuxStatus _MUXAPI VanSetSleepMode(unsigned short wCard, unsigned short wBus, tVanSleepMode eVanSleepMode);
/* Active la broche wake up de l'interface de ligne REMX (Esclave)          // REMX WakeUp pins setup (used by a slave node to wakeup the bus */
_MUXSPEC tMuxStatus _MUXAPI VanSetWakeUpMode(unsigned short wCard, unsigned short wBus, tVanWakeUpMode eVanWakeUpMode);
/* Récupère l'état de la broche SREG de l'interface de ligne                // REMX SREG pins status (used by a master node to power slave) */
_MUXSPEC tMuxStatus _MUXAPI VanGetSleepMode(unsigned short wCard, unsigned short wBus, tVanSleepMode *eVanSleepMode);
/* Validation / dévalidation du diagnostic en émission                      // Diagnostic when transmission in progress */
_MUXSPEC tMuxStatus _MUXAPI VanSetTIP(unsigned short wCard, unsigned short wBus, tVanBoolean eTIPEnable);
/* Retourne la valeur en fonction du débit et de l'horloge en désirée       // Returned SDC value depending on baudrate and SDC time desired */
_MUXSPEC tMuxStatus _MUXAPI VanGetSDCValue(tVanBaudRate eBaudRate,unsigned long dwSDCTimeMs,unsigned long *dwSDCValue);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI VanClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI VanGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);

/* Lecture d'un octet sur un composant VAN                                  // Read byte from the VAN controller */
_MUXSPEC tMuxStatus _MUXAPI VanReadByte(unsigned short wCard, unsigned short wBus, unsigned short wChip, unsigned short wOffset,unsigned char *bData);
/* Ecriture d'un octet sur un composant VAN                                 // Write byte to the VAN controller */
_MUXSPEC tMuxStatus _MUXAPI VanWriteByte(unsigned short wCard, unsigned short wBus, unsigned short wChip, unsigned short wOffset,unsigned char bData);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tVanConfigOper)(unsigned short wCard, unsigned short wBus, tVanOper *hVanOper);
typedef tMuxStatus (__stdcall * tVanConfigBus)(unsigned short wCard, unsigned short wBus, tVanBus *hVanBus);
typedef tMuxStatus (__stdcall * tVanConfigParam)(unsigned short wCard, unsigned short wBus, tVanParam *hVanParam);
typedef tMuxStatus (__stdcall * tVanConfigStat)(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
typedef tMuxStatus (__stdcall * tVanCreateMsg)(unsigned short wCard, unsigned short wBus, tVanMsg *hVanMsg);
typedef tMuxStatus (__stdcall * tVanConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tVanMsg *hVanMsg);
typedef tMuxStatus (__stdcall * tVanConfigPeriodicList)(unsigned short wCard, unsigned short wBus, unsigned short wPeriodicCount, tVanPeriodicMsg *hVanPeriodicMsgList);
typedef tMuxStatus (__stdcall * tVanSetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tVanActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tVanIsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tVanDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tVanSendMsg)(unsigned short wCard, unsigned short wBus, tVanMsg *hVanMsg);
typedef tMuxStatus (__stdcall * tVanSendMsgList)(unsigned short wCard, unsigned short wBus, unsigned short wMsgCount, tVanMsg *hVanMsgList);
typedef tMuxStatus (__stdcall * tVanGetEvent)(unsigned short wCard, unsigned short wBus, tVanEvent *hVanEvent);
typedef tMuxStatus (__stdcall * tVanGetStat)(unsigned short wCard, unsigned short wBus, tVanStat *hVanStat);
typedef tMuxStatus (__stdcall * tVanGetBusState)(unsigned short wCard, unsigned short wBus, tVanChipState *eVanChip0State, tVanChipState *eVanChip1State);
typedef tMuxStatus (__stdcall * tVanSetSleepMode)(unsigned short wCard, unsigned short wBus, tVanSleepMode eVanSleepMode);
typedef tMuxStatus (__stdcall * tVanSetWakeUpMode)(unsigned short wCard, unsigned short wBus, tVanWakeUpMode eVanWakeUpMode);
typedef tMuxStatus (__stdcall * tVanGetSleepMode)(unsigned short wCard, unsigned short wBus, tVanSleepMode *eVanSleepMode);
typedef tMuxStatus (__stdcall * tVanSetTIP)(unsigned short wCard, unsigned short wBus, tVanBoolean eTIPEnable);
typedef tMuxStatus (__stdcall * tVanGetSDCValue)(tVanBaudRate eBaudRate,unsigned long dwSDCTimeMs,unsigned long *dwSDCValue);
typedef tMuxStatus (__stdcall * tVanClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tVanGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus (__stdcall * tVanReadByte)(unsigned short wCard, unsigned short wBus, unsigned short wChip, unsigned short wOffset,unsigned char *bData);
typedef tMuxStatus (__stdcall * tVanWriteByte)(unsigned short wCard, unsigned short wBus, unsigned short wChip, unsigned short wOffset,unsigned char bData);
#endif

#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines ISO9141 // ISO 9141 definitions
*******************************************************************************/
#define	ISO_MAX_DATA	        		260		            /* Nbre de données max KWP2000-2F           // Maximum KWP2000-2F message length */
#define	ISO14230_MAX_DATA	    		(ISO_MAX_DATA-5)	/* Nbre de données max ISO14230             // Maximum ISO14230 message length */

#define ISO_PERIODIC_PARAM_ENABLE		1		/* Active la périodique							// Enable periodic frame */
#define ISO_PERIODIC_PARAM_DISABLE		0		/* Desactive la periodique						// Disable periodic frame */
#define ISO_PERIODIC_PARAM_WITHEVENTS	2		/* Active la remontée des événements			// Enable the events */
#define ISO_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

typedef enum
{
	ISO_OPER_TESTER         =   0,      /* Mode testeur                             	// Tester mode */
	ISO_OPER_ANALYZER       =   1,      /* Mode analyseur                           	// Analyzer mode */
	ISO_OPER_SIMU           =   2,      /* Mode simulation d'UCE                    	// Simulation mode */
	ISO_OPER_FREE           =   3       /* Mode libre                    	        // Free mode */
} tIsoOperMode;

typedef struct
{
	tIsoOperMode    eIsoOperMode;       /* Type d'interface avec l'application          // Operating mode with API */
    unsigned short  wFifoSize;          /* Taille de la FIFO                            // FIFO Size */
} tIsoOper;

typedef struct
{
    unsigned short  wFiltTP;			/* Filtre du TesterPresent                      // Tester Present filter */
    unsigned short  wSpecialModes;      /* Réservé pour utilisation futures             // Reserved for future used */
} tIsoParam;

typedef struct
{
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
    unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
    unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
    unsigned long   dwTxErr;            /* Fin de transmission incorrecte               // Error end of tx */
    unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
    unsigned long   dwRxErr;            /* Réception en erreur                          // Error during reception */
    unsigned long   dwErrBreak;         /* Erreur de type Break                         // Break error */
    unsigned long   dwErrFE;            /* Erreur de format                             // Framing error */
    unsigned long   dwErrPE;            /* Erreur de parité                             // Parity error */
    unsigned long   dwErrOE;            /* Erreur de dépassement                        // Overrun error */
    unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tIsoStat;

typedef enum
{
    ISO_PARITY_NOCHANGE 	=   0,      /* Adresse envoyée telle quelle             // 8 bits address - transmit without any change */
    ISO_PARITY_ODD          =   1,      /* Force la parité impaire                  // 7 bits address - transmit with odd parity */
    ISO_PARITY_EVEN         =   2       /* Force la parité paire                    // 7 bits address - transmit with even parity */
} tIso5BdsAddrParity;

typedef enum
{                                       /* Débit possible avec l'UART               // Serial baud rate */
    ISO_BAUD_5	    	=   5,
    ISO_BAUD_9600	    =   9600,
    ISO_BAUD_10400	    =   10400,
	ISO_BAUD_19200	    =   19200,
	ISO_BAUD_38400		=	38400,
    ISO_BAUD_62500	    =   62500,
    ISO_BAUD_125000     =   125000
} tIsoBaudRate;

typedef struct
{
    /* Paramètres pour initialisation à 5 bauds */
    unsigned short      wW0;            /* Délai bus idle avant init. TESTER > 300ms    UCE : time-out (attente ligne K stable avant émission code à 5 bauds) */
                                        /* Bus high idle time prior to transmission of address byte */
    unsigned short      wW1;            /* Délai avant code synchro   TESTER : time-out UCE : [60,250ms] */
                                        /* Time out between address byte and synchronisation pattern */
    unsigned short      wW2;            /* Délai avant mot clef1      TESTER : time-out UCE : [5,50ms] */
                                        /* Time out between synchronisation pattern and key byte 1 */
    unsigned short      wW3;            /* Délai avant mot clef2      TESTER : time-out UCE : [0,20ms] */
                                        /* Time out between key byte 1 and key byte 2 */
    unsigned short      wW4a;           /* Délai avant mot clef2B     TESTER : [25,50ms]UCE : time-out */
                                        /* Time between key byte 2 and inverted key byte 2 */
    unsigned short      wW4b;           /* Délai avant code AdresB    TESTER : time-out UCE : [25,50ms] */
                                        /* Time out between inv. key byte 2 and inv. address */
    unsigned short      wW5;            /* Délai avant répét. init    TESTER > 300ms    UCE : time-out (attente ligne K stable avant émission code à 5 bauds) */
                                        /* Time out before retry of initialization */
    unsigned short      wP0;            /* Délai avant 1ère requête   TESTER : [5,250ms]UCE : time-out */
                                        /* Time out between initialization and the first request */
    tIso5BdsAddrParity  eParity;        /* Codage de l'adresse à 5 bauds */
                                        /* Parity for 5bauds address during initialisation */
    /* Paramètres pour initialisation rapide */
    unsigned short      wTIdle;         /* Délai bus idle avant init. TESTER > 300ms    UCE : time-out (attente ligne K stable avant émission séquence d'init) */
                                        /* Bus high idle time prior to transmission of init. */
    unsigned short      wTInitL;        /* Durée du pattern ligne L   TESTER : 25ms */
                                        /* Time for wakeup pattern bus low */
    unsigned short      wTWup;          /* Durée totale de la séqunce TESTER : 50ms */
    /* Paramètre de communication */
    tIsoBaudRate        eBaudRate;      /* Débit (10400 bauds) */
                                        /* Serial baud rate communication */
    unsigned short      wP1;            /* Time-out interbyte REP     TESTER : time-out UCE : [0-10ms] */
                                        /* Inter byte time out for ECU response */
    unsigned short      wP2;            /* Délai REQ / REP            TESTER : time-out UCE : [1-250ms] */
                                        /* Time out between tester request and ECU response(s) */
    unsigned short      wP3;            /* Délai REP / REQ            TESTER : [1,5000ms]TypeI ou [5,5000ms]TypeII UCE : time-out[4750,5250ms] */
                                        /* Time between ECU response and tester request */
    unsigned short      wP4;            /* Time-out interbyte REQ     TESTER : [0,10ms]TypeI ou [5,10ms]TypeII UCE : time-out[20-25ms] */
                                        /* Inter byte time for tester request */
} tIsoBus;

typedef enum
{
    ISO_MSG_NORMAL      =   0x00,       /* Emission d'un msg                        // Message transmission */
    ISO_MSG_INIT5BDS    =   0x01,       /* Emission d'un msg avec une init. à 5 bds // Message transmission with 5 bauds init. */
    ISO_MSG_INITFAST    =   0x02,       /* Emission d'un msg avec une init. rapide  // Message transmission with fast init. */
    ISO_MSG_WAITRESP    =   0xFFFF      /* Attente d'une nouvelle réponse sans Tx   // Wait a new frame without reception */
} tIsoTypeMsg;

typedef enum
{
    ISO_HEADER_NOADDR   =   0x00,       /* Aucune information d'adresse             // No address information */
    ISO_HEADER_CARB     =   0x40,       /* Mode d'exception (CARB)                  // Reserved for CARB */
    ISO_HEADER_PHYS     =   0x80,       /* Avec information d'adresse physique      // Physical address */
    ISO_HEADER_FUNCT    =   0xC0        /* Avec information d'adresse fonctionnel   // Functionnal address */
} tIsoTypeHeader;

typedef enum
{
    ISO_NO_ERR              =   0,      /* Pas d'erreur                             // No error */
    ISO_ERR_FE              =   1,      /* Erreur stop bit                          // Framing error */
    ISO_ERR_PE              =   2,      /* Erreur bit de parité                     // Parity error */
    ISO_ERR_OE              =   3,      /* Erreur dépassement                       // Overrun error */
    ISO_ERR_BREAK           =   4,      /* Détection d'un break                     // Break detection */
	ISO_ERR_NOECHO			=	5,		/* Time out en émission						// Tx time out */
	ISO_ERR_BADECHO			=	6,		/* Echo incorrect							// Bad echo */
    ISO_ERR_TO_SYNCHRO      =   10,     /* Time out code synchro                    // Time out waiting synchro char */
    ISO_ERR_BAD_SYNCHRO     =   11,     /* Valeur du code synchro incorrecte        // Bad Synchro value */
    ISO_ERR_TO_KEY1         =   12,     /* Time out mot clef 1                      // Time out waiting key word 1 char */
    ISO_ERR_BAD_KEY1        =   13,     /* Valeur du mot clef 1 incorrecte          // Bad key word 1 value */
    ISO_ERR_TO_KEY2         =   14,     /* Time out mot clef 2                      // Time out waiting key word 2 char */
    ISO_ERR_BAD_KEY2        =   15,     /* Valeur du mot clef 2 incorrecte          // Bad key word 2 value */
    ISO_ERR_TO_ADDR         =   16,     /* Time out code addresse inversée          // Time out waiting address code */
    ISO_ERR_BAD_ADDR        =   17,     /* Valeur du code adresse incorrecte        // Bad address code value */
    ISO_ERR_TO_RESP         =   18,     /* Time out attente de réponse              // Time out waiting response */
    ISO_ERR_RX_OVER         =   19,     /* Longueur de la réponse trop longue       // Response data length overflow */
    ISO_ERR_TO_RESPn        =   20,     /* Time out attente de multi-réponse        // Time out waiting multiple response */
    ISO_ERR_BAD_LEN         =   21,     /* Longueur de la réponse incorrecte        // Incorrect response data length */
    ISO_ERR_BAD_CRC         =   22      /* CRC de la réponse incorrecte				// Bad CRC response */
} tIsoError;

typedef struct
{
    tIsoTypeMsg     eTypeMsg;           /* Type de message                          // Message type */
    unsigned short  wCodeAddr;          /* Code adresse pour init à 5 bauds         // source address for 5 bauds init */
    unsigned long   lPeriod;            /* Périodicité en ms                        // Périod */
    unsigned short  wDataLen;           /* Taille des données                       // Data length */
    unsigned char   bData[ISO_MAX_DATA];/* Buffer de donnée                         // Data buffer */
} tIsoMsg;

typedef struct
{
    unsigned short  wDataLen;           /* Taille des données                       // Data length */
    unsigned short  wTimeOut;           /* Valeur de timeout                        // Timeout value */
    unsigned char   bData[ISO_MAX_DATA];/* Données à comparer                       // Data to compare */
    unsigned char   bMask[ISO_MAX_DATA];/* Masque de donnée                         // Data Mask */
} tIsoTrigMsg;

typedef struct
{
    tIsoTypeMsg     eTypeMsg;           /* Type de message                          // Message type */
	tIsoTypeHeader	eIsoTypeHeader;		/* Format du message d'entête				// Header format */
    unsigned long   lPeriod;            /* Mettre à 0 (réservé utilisation future)  // Must be set to 0 (Reserved for future used) */
	unsigned short  wCodeAddr;          /* Code adresse pour init à 5 bauds         // source address for 5 bauds init */
	unsigned short  wSrcAddr;           /* Adresse source							// Source address */
	unsigned short  wDstAddr;           /* Adresse cible							// Dest address */
    unsigned short  wDataLen;           /* Taille des données                       // Data length */
    unsigned char   bData[ISO14230_MAX_DATA];/* Buffer de donnée                    // Data buffer */
} tIso14230Msg;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                            // Bus number */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement                         // Event type */
    unsigned long   dwTimeStamp;        /* Heure de l'événement en multiple de 0.1ms// Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                 // Time accuracy */
    tIsoError       eError;             /* Indication du type d'erreur              // Error type */
    unsigned char   bData;              /* Octet de donnée                          // Data */
    unsigned char   bDummy;             /* Octet de remplissage                     // Dummy field */
} tIsoChar;

typedef struct
{
    unsigned short  wBus;               /* Numéro de bus                                // Bus number */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement                             // Event type */
    unsigned long   dwTimeStamp;		/* Heure de l'événement en multiple de 0.1ms// Time of event in 100 µSec */
    unsigned short  wTimePrecision;     /* Précision de la datation                     // Time accuracy */
    tIsoError       eError;             /* Indication du type d'erreur                  // Error type */
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wKeyWord;           /* Mot clef reçu lors de l'init à 5 bauds       // Keyword received during 5 bauds init. */
    unsigned short  wReserved1;         /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;        /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;           /* Taille des données                           // Data length */
    unsigned char   bData[ISO_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tIsoEvent;

/*******************************************************************************
; Routines ISO9141 // ISO9141 prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du mode de fonctionnement de l'application                 // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI IsoConfigOper(unsigned short wCard, unsigned short wBus, tIsoOper *hIsoOper);
/* Configuration des paramètres de communication                            // Bus parameters */
_MUXSPEC tMuxStatus _MUXAPI IsoConfigBus(unsigned short wCard, unsigned short wBus, tIsoBus *hIsoBus);
/* Configuration des paramètres                                             // Uart parameters */
_MUXSPEC tMuxStatus _MUXAPI IsoConfigUart(unsigned short wCard, unsigned short wBus, tUartConfig *hUartConfig);
/* Configuration des paramètres supplémentaires                             // Extra parameter */
_MUXSPEC tMuxStatus _MUXAPI IsoConfigParam(unsigned short wCard, unsigned short wBus, tIsoParam *hIsoParam);
/* Configuration des statistques                                            // Statistics configuration */
_MUXSPEC tMuxStatus _MUXAPI IsoConfigStat(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI IsoActivate(unsigned short wCard, unsigned short wBus);
/* Etat du bus de communication                                             // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI IsoIsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI IsoDeactivate(unsigned short wCard, unsigned short wBus);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI IsoConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tIsoMsg *hIsoMsg);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI Iso14230ConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tIso14230Msg *hIso14230Msg);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI IsoSetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Emission d'un message (requête avec ou sans séquence d'initialisation)   // Transmit a message with or without init. sequence */
_MUXSPEC tMuxStatus _MUXAPI IsoSendMsg(unsigned short wCard, unsigned short wBus, tIsoMsg *hIsoMsg);
/* Emission d'un message (requête avec ou sans séquence d'initialisation)   // Transmit a message with or without init. sequence */
_MUXSPEC tMuxStatus _MUXAPI Iso14230SendMsg(unsigned short wCard, unsigned short wBus, tIso14230Msg *hIso14230Msg);
/* Récupération d'un événement en provenance du bus (mode analyzer)         // Get response event */
_MUXSPEC tMuxStatus _MUXAPI IsoGetEvent(unsigned short wCard, unsigned short wBus, tIsoEvent *hIsoEvent);
/* Attente d'une nouvelle réponse                                           // Wait next response */
_MUXSPEC tMuxStatus _MUXAPI IsoWaitResponse(unsigned short wCard, unsigned short wBus, unsigned short wTimeOut);
/* Attente d'une réponse pré-définie et émission d'un message   			// Wait a predefined response before transmitting the request */
_MUXSPEC tMuxStatus _MUXAPI IsoSendResp(unsigned short wCard, unsigned short wBus, tIsoTrigMsg *hIsoTrigMsg, tIsoMsg *hIsoMsg);
/* Programmation d'un nouveau débit                                         // Change baud rate */
_MUXSPEC tMuxStatus _MUXAPI IsoChangeBaudRate(unsigned short wCard, unsigned short wBus, tIsoBaudRate eBaudRateTx, tIsoBaudRate eBaudRateRx);
/* Lecture des statistiques                                                 // Statistics information */
_MUXSPEC tMuxStatus _MUXAPI IsoGetStat(unsigned short wCard, unsigned short wBus, tIsoStat *hIsoStat);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI IsoClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI IsoGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
/* Taille des evts dans la FIFO                                             // Data length of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI IsoSetDataRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wLevel);
/* Lecture d'un octet sur un composant UART                                 // Read byte from the UART */
_MUXSPEC tMuxStatus _MUXAPI IsoReadByte(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char *bData);
/* Ecriture d'un octet sur un composant UART                                // Write byte to the UART */
_MUXSPEC tMuxStatus _MUXAPI IsoWriteByte(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char bData);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tIsoConfigOper)(unsigned short wCard, unsigned short wBus, tIsoOper *hIsoOper);
typedef tMuxStatus (__stdcall * tIsoConfigBus)(unsigned short wCard, unsigned short wBus, tIsoBus *hIsoBus);
typedef tMuxStatus (__stdcall * tIsoConfigUart)(unsigned short wCard, unsigned short wBus, tUartConfig *hUartConfig);
typedef tMuxStatus (__stdcall * tIsoConfigParam)(unsigned short wCard, unsigned short wBus, tIsoParam *hIsoParam);
typedef tMuxStatus (__stdcall * tIsoConfigStat)(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
typedef tMuxStatus (__stdcall * tIsoActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tIsoIsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tIsoDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tIsoConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tIsoMsg *hIsoMsg);
typedef tMuxStatus (__stdcall * tIso14230ConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tIso14230Msg *hIso14230Msg);
typedef tMuxStatus (__stdcall * tIsoSetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tIsoSendMsg)(unsigned short wCard, unsigned short wBus, tIsoMsg *hIsoMsg);
typedef tMuxStatus (__stdcall * tIso14230SendMsg)(unsigned short wCard, unsigned short wBus, tIso14230Msg *hIso14230Msg);
typedef tMuxStatus (__stdcall * tIsoGetEvent)(unsigned short wCard, unsigned short wBus, tIsoEvent *hIsoEvent);
typedef tMuxStatus (__stdcall * tIsoWaitResponse)(unsigned short wCard, unsigned short wBus, unsigned short wTimeOut);
typedef tMuxStatus (__stdcall * tIsoSendResp)(unsigned short wCard, unsigned short wBus, tIsoTrigMsg *hIsoTrigMsg, tIsoMsg *hIsoMsg);
typedef tMuxStatus (__stdcall * tIsoChangeBaudRate)(unsigned short wCard, unsigned short wBus, tIsoBaudRate eBaudRateTx, tIsoBaudRate eBaudRateRx);
typedef tMuxStatus (__stdcall * tIsoGetStat)(unsigned short wCard, unsigned short wBus, tIsoStat *hIsoStat);
typedef tMuxStatus (__stdcall * tIsoClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tIsoGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus (__stdcall * tIsoSetDataRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wLevel);
typedef tMuxStatus (__stdcall * tIsoReadByte)(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char *bData);
typedef tMuxStatus (__stdcall * tIsoWriteByte)(unsigned short wCard, unsigned short wBus, unsigned short wOffset,unsigned char bData);
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines J1850 // J1850 definitions
*******************************************************************************/
#define J18_MAX_DATA      11

#define J18_PERIODIC_PARAM_ENABLE		1		/* Active la périodique							// Enable periodic frame */
#define J18_PERIODIC_PARAM_DISABLE		0		/* Desactive la periodique						// Disable periodic frame */
#define J18_PERIODIC_PARAM_WITHEVENTS	2		/* Active la remontée des événements			// Enable the events */
#define J18_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

typedef enum
{
	J18_OPER_TESTER         =   0,      /* Mode testeur                             // Tester mode */
	J18_OPER_ANALYZER       =   1,      /* Mode analyseur                           // Analyzer mode */
	J18_OPER_SIMU           =   2       /* Mode simulation d'UCE                    // Simulation mode */
} tJ18OperMode;

typedef struct
{
	tJ18OperMode  eJ18OperMode;         /* Type d'interface avec l'application          // Operating mode with API */
	unsigned short  wFifoSize;              /* Taille de la FIFO                            // FIFO Size */
} tJ18Oper;

typedef struct
{
	unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
	unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
	unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
	unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
	unsigned long   dwTxErr;            /* Fin de transmission incorrecte               // Error end of tx */
	unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
	unsigned long   dwRxErr;            /* Réception en erreur                          // Error during reception */
	unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tJ18Stat;

typedef enum
{
	J18_NO_ERR              =   0x0000     /* Pas d'erreur                                 // No error */
} tJ18Error;

typedef enum
{
	J18_BUSTYPE_PWM         =   0x0000,    /* J1850 PWM Bus									// J1850 PWM Bus */
	J18_BUSTYPE_VPW         =   0x0001     /* J1850 PWM Bus									// J1850 PWM Bus */
} tJ18BusType;

typedef enum
{
	J18_BUSSPEED_STD        =   0x0000,    /* J1850 vitesse standard						// J1850 Standard bus speed */
	J18_BUSSPEED_4X         =   0x0001     /* J1850 vitesse X4								// J1850 4X speed */
} tJ18BusSpeed;

typedef struct
{
    tJ18BusType			eType;				/* Type de bus J1850 VPW ou PWM					// Bus Type VPW or PWM */
    tJ18BusSpeed		eSpeed;				/* Mode de l'interface de ligne */
} tJ18Bus;

typedef struct
{
    unsigned short  wHandleMsg;            /* Index de comm. sur le msg (Infos DLL)    // Communication handle returned by DLL */
    unsigned short  wDataLen;              /* Taille des données                       // Data length */
    unsigned long   lPeriod;               /* Mettre à 0 (réservé pour utilisation future) // Must be set to 0 (Reserved for future used) */
    unsigned char   bData[J18_MAX_DATA];   /* Buffer de donnée                         // Data buffer */
} tJ18Msg;

typedef struct
{
    unsigned short  wBus;                  /* Numéro de bus                                // Bus number */
    tMuxTypeEvent	eTypeEvent;            /* Type d'événement                             // Event type */
    unsigned long   dwTimeStamp;	   /* Heure de l'événement en multiple de 0.1ms// Time of event in 100 µSec */
    tJ18Error       eError;                /* Indication du type d'erreur                  // Error type */
    unsigned short  wBusLoad;              /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wDataLen;              /* Taille des données                           // Data length */
    unsigned short  wDummy;
    unsigned char   bData[J18_MAX_DATA];/* Buffer de donnée                             // Data buffer */
} tJ18Event;

/*******************************************************************************
; Routines J1850   // J1850   prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du mode de fonctionnement des buffers                      // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI J18ConfigOper(unsigned short wCard, unsigned short wBus, tJ18Oper *hJ18Oper);
/* Configuration du bus                                                     // Bus parameter */
_MUXSPEC tMuxStatus _MUXAPI J18ConfigBus(unsigned short wCard, unsigned short wBus, tJ18Bus *hJ18Bus);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI J18Activate(unsigned short wCard, unsigned short wBus);
/* Etat du bus de communication                                             // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI J18IsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI J18ConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tJ18Msg *hJ18Msg);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI J18SendMsg(unsigned short wCard, unsigned short wBus, tJ18Msg *hJ18Msg);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI J18GetEvent(unsigned short wCard, unsigned short wBus, tJ18Event *hJ18Event);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI J18Deactivate(unsigned short wCard, unsigned short wBus);

/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI J18SetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tJ18ConfigOper)(unsigned short wCard, unsigned short wBus, tJ18Oper *hJ18Oper);
typedef tMuxStatus (__stdcall * tJ18ConfigBus)(unsigned short wCard, unsigned short wBus, tJ18Bus *hJ18Bus);
typedef tMuxStatus (__stdcall * tJ18Activate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tJ18IsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tJ18SendMsg)(unsigned short wCard, unsigned short wBus, tJ18Msg *hJ18Msg);
typedef tMuxStatus (__stdcall * tJ18GetEvent)(unsigned short wCard, unsigned short wBus, tJ18Event *hJ18Event);
typedef tMuxStatus (__stdcall * tJ18Deactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tJ18SetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
#endif
#ifdef __cplusplus
	}
#endif




/*******************************************************************************
; Déclaration pour les routines J1587 // J1587 definitions
*******************************************************************************/
#define J1587_MAX_DATA      				20

#define J1587_PERIODIC_PARAM_ENABLE			1		/* Active la périodique							// Enable periodic frame */
#define J1587_PERIODIC_PARAM_DISABLE		0		/* Desactive la periodique						// Disable periodic frame */
#define J1587_PERIODIC_PARAM_WITHEVENTS		2		/* Active la remontée des événements			// Enable the events */
#define J1587_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

typedef enum
{
	J1587_OPER_ANA_FIFO       =   0         /* Mode analyse, stockage fifo      // Analyse mode, event is stored in fifo mode */
} tJ1587OperMode;

typedef struct
{
	tJ1587OperMode  eJ1587OperMode;         /* Type d'interface avec l'application          // Operating mode with API */
	unsigned short  wFifoSize;              /* Taille de la FIFO                            // FIFO Size */
} tJ1587Oper;

typedef enum
{
	J1587_BAUD_9600   =   9600L	    	    /* 9600 bauds */
} tJ1587BaudRate;

typedef struct
{
	unsigned long   dwDelayBusIdle;     /* Delai avant bus idle                         // Delay before detect bus idle */
	unsigned short  wFiltMID;           /* MID pour filtrage                            // MID for filtering */
	unsigned short  wFiltMask;          /* Masque pour filtrage                         // Acceptance mask */
	unsigned short  wFiltPass;          /* Indication si le filtre est passant/bloquant // Filter by pass or block */
	unsigned short  wSpecialModes;      /* Réservé pour utilisation futures             // Reserved for future used */
} tJ1587Param;

typedef struct
{
	unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
	unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
	unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
	unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
	unsigned long   dwTxErr;            /* Fin de transmission incorrecte               // Error end of tx */
	unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
	unsigned long   dwRxErr;            /* Réception en erreur                          // Error during reception */
	unsigned long   dwErrBreak;         /* Erreur de type Break                         // Break error */
	unsigned long   dwErrFE;            /* Erreur de format                             // Framing error */
	unsigned long   dwErrPE;            /* Erreur de parité                             // Parity error */
	unsigned long   dwErrOE;            /* Erreur de dépassement                        // Overrun error */
	unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tJ1587Stat;

typedef enum
{
	J1587_NO_ERR              =   0x0000,   /* Pas d'erreur                                 // No error */
	J1587_ERR_BIT             =   0x0001,   /* Erreur de bit                                // Bit error */
	J1587_ERR_CRC             =   0x0002    /* Erreur dans le calcul du CRC                 // CRC error */
} tJ1587Error;

typedef struct
{
	tJ1587BaudRate    eBaudRate;            /* Débit du bus                                 // Baud rate */
} tJ1587Bus;

typedef enum
{
	J1587_BUS_NOMINAL         =   0,      /* Etat nominal                                 // Nominal state */
	J1587_BUS_ERROR           =   1,      /* Etat erreur                                  // Error state */
	J1587_BUS_IDLE            =   2       /* Etat bus idle                                // Bus idle state */
} tJ1587ChipState;

typedef struct
{
	unsigned short  wHandleMsg;             /* Index de comm. sur le msg (Infos DLL)    // Communication handle returned by DLL */
	unsigned short  wPriority;              /* Priorité du message [1-8]                // Message priority */
	unsigned long   lPeriod;                /* Periodicité en ms                        // Period */
	unsigned long   dwReserved1;            /* Réservé pour utilisation future          // Reserved */
	unsigned long   dwReserved2;            /* Réservé pour utilisation future          // Reserved */
	unsigned short  wMID;                   /* Identificateur du message                // Message identifier */
	unsigned short  wDataLen;               /* Taille des données                       // Data length */
	unsigned char   bData[J1587_MAX_DATA];  /* Buffer de donnée                         // Data buffer */
} tJ1587Msg;

typedef struct
{
	unsigned short  wBus;                   /* Numéro de bus                                // Bus number */
	unsigned short  wHandleMsg;             /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
	tMuxTypeEvent   eTypeEvent;             /* Type d'événement retourné à l'application    // Event type */
	unsigned long   dwTimeStamp;            /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
	unsigned short  wTimePrecision;         /* Précision de la datation                     // Time accuracy */
	tJ1587Error     eError;                 /* Type d'erreur                                // Error type */
	tJ1587ChipState eChipState;             /* Etat du composants                           // Chip state */
	unsigned short  wBusLoad;               /* Valeur de la charge bus                      // Bus load value */
	unsigned long   dwReserved1;            /* Réservé pour utilisation future              // Reserved */
	unsigned long   dwReserved2;            /* Réservé pour utilisation future              // Reserved */
	unsigned short  wMID;                   /* Identificateur du message                // Message identifier */
	unsigned short  wDataLen;               /* Taille des données               // Data length */
	unsigned char   bData[J1587_MAX_DATA];  /* Buffer de donnée                 // Data buffer */
} tJ1587Event;

/*******************************************************************************
; Routines J1587   // J1587   prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du mode de fonctionnement des buffers                      // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI J1587ConfigOper(unsigned short wCard, unsigned short wBus, tJ1587Oper *hJ1587Oper);
/* Configuration du bus                                                     // Bus parameter */
_MUXSPEC tMuxStatus _MUXAPI J1587ConfigBus(unsigned short wCard, unsigned short wBus, tJ1587Bus *hJ1587Bus);
/* Configuration des paramètres supplémentaires                             // Extra parameter */
_MUXSPEC tMuxStatus _MUXAPI J1587ConfigParam(unsigned short wCard, unsigned short wBus, tJ1587Param *hJ1587Param);
/* Configuration des statistques                                            // Statistics configuration */
_MUXSPEC tMuxStatus _MUXAPI J1587ConfigStat(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI J1587ConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tJ1587Msg *hJ1587Msg);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI J1587Activate(unsigned short wCard, unsigned short wBus);
/* Etat du bus de communication                                             // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI J1587IsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI J1587SendMsg(unsigned short wCard, unsigned short wBus, tJ1587Msg *hJ1587Msg);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI J1587GetEvent(unsigned short wCard, unsigned short wBus, tJ1587Event *hJ1587Event);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI J1587Deactivate(unsigned short wCard, unsigned short wBus);

/* Récupération de l'état du contrôleur de protocole                        // CAN controller state */
_MUXSPEC tMuxStatus _MUXAPI J1587GetBusState(unsigned short wCard, unsigned short wBus, tJ1587ChipState *eJ1587ChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
/* Lecture des statistiques                                                 // Statistics information */
_MUXSPEC tMuxStatus _MUXAPI J1587GetStat(unsigned short wCard, unsigned short wBus, tJ1587Stat *hJ1587Stat);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI J1587SetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI J1587ClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI J1587GetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tJ1587ConfigOper)(unsigned short wCard, unsigned short wBus, tJ1587Oper *hJ1587Oper);
typedef tMuxStatus (__stdcall * tJ1587ConfigBus)(unsigned short wCard, unsigned short wBus, tJ1587Bus *hJ1587Bus);
typedef tMuxStatus (__stdcall * tJ1587ConfigParam)(unsigned short wCard, unsigned short wBus, tJ1587Param *hJ1587Param);
typedef tMuxStatus (__stdcall * tJ1587ConfigStat)(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
typedef tMuxStatus (__stdcall * tJ1587ConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tJ1587Msg *hJ1587Msg);
typedef tMuxStatus (__stdcall * tJ1587Activate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tJ1587IsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tJ1587SendMsg)(unsigned short wCard, unsigned short wBus, tJ1587Msg *hJ1587Msg);
typedef tMuxStatus (__stdcall * tJ1587GetEvent)(unsigned short wCard, unsigned short wBus, tJ1587Event *hJ1587Event);
typedef tMuxStatus (__stdcall * tJ1587Deactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tJ1587GetBusState)(unsigned short wCard, unsigned short wBus, tJ1587ChipState *eJ1587ChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
typedef tMuxStatus (__stdcall * tJ1587GetStat)(unsigned short wCard, unsigned short wBus, tJ1587Stat *hJ1587Stat);
typedef tMuxStatus (__stdcall * tJ1587SetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tJ1587ClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tJ1587GetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines NMEA0183 // NMEA0183 definitions
*******************************************************************************/
#define	NMEA0183_MAX_DATA	      77    /* Nbre de données max NMEA0183       // Maximum NMEA0183 message length */
typedef enum
{
    NMEA0183_OPER_ANA_FIFO       =   0      /* Mode analyse, stockage fifo      // Analyse mode, event is stored in fifo mode */
} tNMEA0183OperMode;

typedef struct
{
    tNMEA0183OperMode  eNMEA0183OperMode;   /* Type d'interface avec l'application          // Operating mode with API */
    unsigned short  wFifoSize;              /* Taille de la FIFO                            // FIFO Size */
} tNMEA0183Oper;

typedef enum
{
    NMEA0183_BAUD_4800   =   4800L	    	/* 4800 bauds */
} tNMEA0183BaudRate;

typedef struct
{
    unsigned long   dwDelayBusIdle;     /* Delai avant bus idle                         // Delay before detect bus idle */
    unsigned long   dwDelayMsgTimeout;  /* Delai avant message en time out              // Delay before time out message */
    unsigned short  wControlCrc;        /* Vérification du CRC dans le message          // Check if CRC is present */
    unsigned short  wSpecialModes;      /* Réservé pour utilisation futures             // Reserved for future used */
} tNMEA0183Param;

typedef struct
{
    unsigned short  wBusLoad;           /* Valeur de la charge bus                      // Bus load value */
    unsigned short  wReserved;          /* Réservé pour utilisation future              // Reserved for future use */
    unsigned long   dwTxRq;             /* Demande de transmission                      // Tx request */
    unsigned long   dwTxOk;             /* Fin de transmission correcte                 // End of Tx Ok */
    unsigned long   dwTxErr;            /* Fin de transmission incorrecte               // Error end of tx */
    unsigned long   dwRxOk;             /* Réception correcte                           // Rx Ok */
    unsigned long   dwRxErr;            /* Réception en erreur                          // Error during reception */
    unsigned long   dwErrBreak;         /* Erreur de type Break                         // Break error */
    unsigned long   dwErrFE;            /* Erreur de format                             // Framing error */
    unsigned long   dwErrPE;            /* Erreur de parité                             // Parity error */
    unsigned long   dwErrOE;            /* Erreur de dépassement                        // Overrun error */
    unsigned long   dwErrFifoOvf;       /* Perte de message                             // FIFO Rx overflow */
} tNMEA0183Stat;

typedef enum
{
    NMEA0183_NO_ERR              =   0x0000, /* Pas d'erreur                                 // No error */
    NMEA0183_ERR_RX_OVER         =   0x0001, /* Longueur du message trop long			     // Message data length overflow */
    NMEA0183_ERR_INV_PDU         =   0x0002, /* Format de message invalide                   // Invalid PDU format */
    NMEA0183_ERR_BAD_CRC         =   0x0003, /* CRC incorrect                                // Invalid CRC */
    NMEA0183_ERR_BAD_EOS         =   0x0004, /* <CR>ou <LF> erreur                           // End of sequence error */
    NMEA0183_ERR_TO_MSG          =   0x0005  /* Timeout d'attente du message                 // Message timeout */
} tNMEA0183Error;

typedef struct
{
    tNMEA0183BaudRate    eBaudRate;          /* Débit du bus                                 // Baud rate */
} tNMEA0183Bus;

typedef enum
{
    NMEA0183_BUS_NOMINAL         =   0,      /* Etat nominal                                 // Nominal state */
    NMEA0183_BUS_ERROR           =   1,      /* Etat erreur                                  // Error state */
    NMEA0183_BUS_IDLE            =   2       /* Etat bus idle                                // Bus idle state */
} tNMEA0183ChipState;

typedef enum
{
    NMEA0183_GEN_RAW	    =   0x0000, /* Messages brutes                              // Raw message */
    NMEA0183_GEN_NO_CRC     =   0x0001, /* Uniquement les caractère $ et CR,LF          // $,CR and LF only */
    NMEA0183_GEN_CRC        =   0x0002  /* $,CR,LF et CRC + CRC delimiter               // $, CR , LF and CRC field + delimiter */
}
tNMEA0183GenErr;

typedef struct
{
    unsigned short  wHandleMsg;             /* Index de comm. sur le msg (Infos DLL)    // Communication handle returned by DLL */
    tNMEA0183GenErr eNMEA0183GenErr;        /* Type d'émission					        // Sending mode */
    unsigned long   lPeriod;                /* Periodicité en ms                        // Period */
    unsigned long   dwReserved1;            /* Réservé pour utilisation future          // Reserved */
    unsigned long   dwReserved2;            /* Réservé pour utilisation future          // Reserved */
    unsigned short  wDataLen;               /* Taille des données                       // Data length */
    unsigned char   bData[NMEA0183_MAX_DATA];    /* Buffer de donnée                    // Data buffer */
} tNMEA0183Msg;

typedef struct
{
    unsigned short  wBus;                   /* Numéro de bus                                // Bus number */
    unsigned short  wHandleMsg;             /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    tMuxTypeEvent   eTypeEvent;             /* Type d'événement retourné à l'application    // Event type */
    unsigned long   dwTimeStamp;            /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    tNMEA0183Error  eError;                 /* Type d'erreur                                // Error type */
    tNMEA0183ChipState eChipState;             /* Etat du composants                           // Chip state */
    unsigned short  wBusLoad;               /* Valeur de la charge bus                      // Bus load value */
    unsigned long   dwReserved1;            /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved2;            /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;               /* Taille des données               // Data length */
    unsigned char   bData[NMEA0183_MAX_DATA];  /* Buffer de donnée                 // Data buffer */
} tNMEA0183Event;

/*******************************************************************************
; Routines NMEA0183   // NMEA0183  prototypes
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL

#define NMEA0183_PERIODIC_PARAM_ENABLE			1		/* Active la périodique							// Enable periodic frame */
#define NMEA0183_PERIODIC_PARAM_DISABLE			0		/* Desactive la periodique						// Disable periodic frame */
#define NMEA0183_PERIODIC_PARAM_WITHEVENTS		2		/* Active la remontée des événements			// Enable the events */
#define NMEA0183_PERIODIC_PARAM_NOEVENTS		0		/* Desactive la remontée des événements			// Disable the events */

/* Configuration du mode de fonctionnement des buffers                      // Select the operating mode */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ConfigOper(unsigned short wCard, unsigned short wBus, tNMEA0183Oper *hNMEA0183Oper);
/* Configuration du bus                                                     // Bus parameter */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ConfigBus(unsigned short wCard, unsigned short wBus, tNMEA0183Bus *hNMEA0183Bus);
/* Configuration des paramètres                                             // Uart parameters */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ConfigUart(unsigned short wCard, unsigned short wBus, tUartConfig *hUartConfig);
/* Configuration des paramètres supplémentaires                             // Extra parameter */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ConfigParam(unsigned short wCard, unsigned short wBus, tNMEA0183Param *hNMEA0183Param);
/* Configuration des statistques                                            // Statistics configuration */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ConfigStat(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
/* Création de message périodique                                           // Periodic Messages configuration */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ConfigPeriodic(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tNMEA0183Msg *hNMEA0183Msg);
/* Démarrage de la communication                                            // Start communication */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183Activate(unsigned short wCard, unsigned short wBus);
/* Etat du bus de communication                                             // Bus state communication */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183IsBusActive(unsigned short wCard, unsigned short wBus, unsigned short *wState);
/* Emission d'un message                                                    // Transmit a message */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183SendMsg(unsigned short wCard, unsigned short wBus, tNMEA0183Msg *hNMEA0183Msg);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183GetEvent(unsigned short wCard, unsigned short wBus, tNMEA0183Event *hNMEA0183Event);
/* Arrêt de la communication                                                // Stop communication */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183Deactivate(unsigned short wCard, unsigned short wBus);

/* Récupération de l'état du contrôleur de protocole                        // CAN controller state */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183GetBusState(unsigned short wCard, unsigned short wBus, tNMEA0183ChipState *eNMEA0183ChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
/* Lecture des statistiques                                                 // Statistics information */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183GetStat(unsigned short wCard, unsigned short wBus, tNMEA0183Stat *hNMEA0183Stat);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183SetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183ClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI NMEA0183GetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tNMEA0183ConfigOper)(unsigned short wCard, unsigned short wBus, tNMEA0183Oper *hNMEA0183Oper);
typedef tMuxStatus (__stdcall * tNMEA0183ConfigBus)(unsigned short wCard, unsigned short wBus, tNMEA0183Bus *hNMEA0183Bus);
typedef tMuxStatus (__stdcall * tNMEA0183ConfigUart)(unsigned short wCard, unsigned short wBus, tUartConfig *hUartConfig);
typedef tMuxStatus (__stdcall * tNMEA0183ConfigParam)(unsigned short wCard, unsigned short wBus, tNMEA0183Param *hNMEA0183Param);
typedef tMuxStatus (__stdcall * tNMEA0183ConfigStat)(unsigned short wCard, unsigned short wBus, unsigned short wBusLoadTime);
typedef tMuxStatus (__stdcall * tNMEA0183ConfigPeriodic)(unsigned short wCard, unsigned short wBus, unsigned short wOffset, unsigned short wParam, tNMEA0183Msg *hNMEA0183Msg);
typedef tMuxStatus (__stdcall * tNMEA0183Activate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNMEA0183IsBusActive)(unsigned short wCard, unsigned short wBus, unsigned short *wState);
typedef tMuxStatus (__stdcall * tNMEA0183SendMsg)(unsigned short wCard, unsigned short wBus, tNMEA0183Msg *hNMEA0183Msg);
typedef tMuxStatus (__stdcall * tNMEA0183GetEvent)(unsigned short wCard, unsigned short wBus, tNMEA0183Event *hNMEA0183Event);
typedef tMuxStatus (__stdcall * tNMEA0183Deactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNMEA0183GetBusState)(unsigned short wCard, unsigned short wBus, tNMEA0183ChipState *eNMEA0183ChipState, unsigned char *bTxErrCount, unsigned char *bRxErrCount);
typedef tMuxStatus (__stdcall * tNMEA0183GetStat)(unsigned short wCard, unsigned short wBus, tNMEA0183Stat *hNMEA0183Stat);
typedef tMuxStatus (__stdcall * tNMEA0183SetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tNMEA0183ClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tNMEA0183GetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Déclaration pour les routines WinCE // WinCE definitions
*******************************************************************************/
#ifdef _WIN32_WCE	// Only Under Windows CE
typedef enum
{
	WINCE_FALSE		=	0,						/* Faux		// False */
	WINCE_TRUE		=	1						/* Vrai		// True */
}tWINCEBoolean;

typedef enum
{
	WINCE_POWERMODE_USESYSTEM_SETTINGS		= 0,	/* Utilise les options d'énergie définit par le système // Use all power management settings defined by the operating system */
	WINCE_POWERMODE_PREVENT_POWERDOWN		= 1		/* Empêche la mise en veille du pocket pc dès qu'une carte est ouverte // Prevent automatic power down as soon as a card is opened */
//	WINCE_POWERMODE_POWERDOWN_EXECPTDEVICE	= 2		/* Le pocket de mets en veille sauf la carte USB // Pocket can power down but not the USB device */
}tWINCEPowerMode;

typedef enum
{
	WINCE_BACKLIGHT_USESYSTEM_SETTINGS	= 0,		/* Utilise les options d'éclairage définit par le système // Use all backlight settings defined by the operating system */
	WINCE_BACKLIGHT_PREVENT_POWERDOWN	= 1			/* Empêche la mise en veille de l'éclairage dès qu'une carte est ouverte // Prevent automatic backlight power saving as soon as a card is opened */
}tWINCEBacklightMode;

typedef struct
{
	tWINCEPowerMode		ePowerMode;					/* Mode de gestion de l'alimentation	// Power mode management type */
	tWINCEBacklightMode	eBacklightMode;				/* Mode de gestion de l'éclairage		// Backligth mode management type */
	tWINCEBoolean		eSendEvents;				/* Remonte les évements 				// Send all event */
}tWINCEParam;

typedef enum
{
	WINCE_ACLINE_OFFLINE	= 0,					/* L'alimentation secteur n'est pas branchée	// AC line if offline */
	WINCE_ACLINE_ONLINE		= 1						/* L'alimentation secteur est branchée			// AC line if online */
}tWINCEACLineState;

/* Etats de la batterie						// Battery state flags */
/* Peut être une combinaison de ces valeurs	// Can be a combination of these values */
#define WINCE_BATTSTATE_HIGH			1			/* La batterie est pleine	// Battery is full */
#define WINCE_BATTSTATE_LOW				2			/* La batterie est faible	// Battery is low */
#define WINCE_BATTSTATE_CRITICAL		4			/* La batterie est critique	// Battery is critical */
#define WINCE_BATTSTATE_CHARGING		8			/* La batterie se recharge	// Battery is charging */
#define WINCE_BATTSTATE_NOBATTERY		128			/* Aucune batterie			// There is no battery */
#define WINCE_BATTSTATE_UNKNOWN			255			/* Etat inconnu				// Unknown state */

/* Durée de vie de la batterie	// Battery life time constants */
#define WINCE_BATTLIFETIME_UNKNOWN		0xFFFFFFFF

typedef struct
{
	tWINCEACLineState	eACLineState;				/* Etat de l'alimentation secteur				// AC Line state */
	unsigned short		wBatteryState;				/* Etat de la batterie (WINCE_BATTSTATE_xxx)	// Batterie state (WINCE_BATTSTATE_xxx) */
	unsigned short		wBatteryLifePercent;		/* Etat de la batterie en pourcentage			// Percentage of full battery charge remaining */
	unsigned long		dwBatteryLifeTime;			/* Durée de vie de la batterie					// Battery life time */
}tWINCEPowerState;

typedef struct
{
	tMuxTypeEvent		eTypeEvent;					/* Type d'événement retourné à l'application    // Event type */
	unsigned long		dwTimeStamp;				/* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
	tWINCEPowerState	hPowerState;				/* Etat de l'alimentation						// Power State */
}tWINCEEvent;

/*******************************************************************************
; Routines WinCE // WinCE functions
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration de mode de fonctionnement sous Windows CE  // Setup how it should works under Windows CE */
_MUXSPEC tMuxStatus _MUXAPI WINCEConfigParam(unsigned short wCard, tWINCEParam *hWINCEParam);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI WINCESetNotification(unsigned short wCard, void * hWinEvent);
/* Activation de la gestion de WinCE // Activate the WinCE engine */
_MUXSPEC tMuxStatus _MUXAPI WINCEActivate(unsigned short wCard);
/* Arrêt de la gestion de WinCE // Deactivate the WinCE engine */
_MUXSPEC tMuxStatus _MUXAPI WINCEDeactivate(unsigned short wCard);
/* Etat de l'alimentation	// Power state */
_MUXSPEC tMuxStatus _MUXAPI WINCEGetPowerState(unsigned short wCard, tWINCEPowerState *hPowerState);
/* Recupère les evenement en cours // Get the last events */
_MUXSPEC tMuxStatus _MUXAPI WINCEGetEvent(unsigned short wCard, tWINCEEvent *hEvent);
/* Indique si le driver à été déchargé // Return if the driver has been unloaded */
_MUXSPEC tMuxStatus _MUXAPI WINCEIsDriverUnloaded(unsigned short wCard, unsigned short *wIsDriverUnloaded);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tWINCEConfigParam)(unsigned short wCard, tWINCEParam *hWINCEParam);
typedef tMuxStatus (__stdcall * tWINCESetNotification)(unsigned short wCard, void * hWinEvent);
typedef tMuxStatus (__stdcall * tWINCEActivate)(unsigned short wCard);
typedef tMuxStatus (__stdcall * tWINCEDeactivate)(unsigned short wCard);
typedef tMuxStatus (__stdcall * tWINCEGetPowerState)(unsigned short wCard, tWINCEPowerState *hPowerState);
typedef tMuxStatus (__stdcall * tWINCEGetEvent)(unsigned short wCard, tWINCEEvent *hEvent);
typedef tMuxStatus (__stdcall * tWINCEIsDriverUnloaded)(unsigned short wCard, unsigned short *wIsDriverUnloaded);
#endif
#ifdef __cplusplus
	}
#endif	// __cplusplus
#endif	// _WIN32_WCE



/*******************************************************************************
; Routines de gestions des E/S // IO and User functions
*******************************************************************************/
#define SPI_CODE_READ       0x0000
#define SPI_CODE_WRITE      0x0001

#define SPI_MAX_DATA        16
typedef struct
{
    unsigned short  wCode;                  /* Code fonction                            // Function code */
    unsigned short  wDataLen;               /* Taille des données                       // Data length */
    unsigned char   bData[SPI_MAX_DATA];    /* Buffer de donnée                         // Data buffer */
} tSPIInfo;

#define I2C_CODE_READ       0x0000
#define I2C_CODE_WRITE      0x0001

#define I2C_MAX_DATA        50
typedef struct
{
    unsigned short  wCode;                  /* Code fonction                            // Function code */
    unsigned short  wSlave;                 /* Adresse esclave                          // Slave address */
    unsigned short  wDataLen;               /* Taille des données                       // Data length */
    unsigned char   bData[I2C_MAX_DATA];    /* Buffer de donnée                         // Data buffer */
} tI2CInfo;

#define PROPRIETARY_MAX_DATA        0x1000
typedef struct
{
    unsigned short  wDataLen;                       /* Taille des données                       // Data length */
    unsigned char   bData[PROPRIETARY_MAX_DATA];    /* Buffer de donnée                         // Data buffer */
} tProprietaryInfo;

#define PRY_MAX_DATA        		38		// pour faire un évènement de 64 octets
typedef struct
{
    unsigned short  wBus;                   /* Numéro de bus                                // Bus number */
    unsigned short  wHandleMsg;             /* Index de comm. sur le msg (Infos DLL)        // Communication handle returned by DLL */
    tMuxTypeEvent   eTypeEvent;         /* Type d'événement retourné à l'application    // Event type */
    unsigned long   dwTimeStamp;            /* Heure de l'événement en multiple de 0.1 ms   // Time of event in 100 µSec */
    unsigned short  wError;                 /* Type d'erreur                                // Error type */
    unsigned short  dwReserved1;            /* Réservé pour utilisation future              // Reserved */
    unsigned short  dwReserved2;            /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved3;            /* Réservé pour utilisation future              // Reserved */
    unsigned long   dwReserved4;            /* Réservé pour utilisation future              // Reserved */
    unsigned short  wDataLen;               /* Taille des données               // Data length */
    unsigned char   bData[PRY_MAX_DATA];    /* Buffer de donnée                 // Data buffer */
} tPryEvent;

#define TRG_BUS_NONE        0
#define TRG_BUS_CAN         1
#define TRG_BUS_LIN         2
#define TRG_BUS_ISO         3
#define TRG_BUS_VAN         4
#define TRG_BUS_J1587       5
#define TRG_BUS_NMEA0183    6

#define TRG_TYPE_IDENT      0				/* Trigger sur identificateur détecté */
#define TRG_TYPE_ERROR      1				/* Trigger sur trame d'erreur */
typedef struct
{
unsigned short  wTypeBus;					/* Type de bus (CAN, VAN...)                    // Bus type */
unsigned short  wBus;						/* Numéro de bus                                // Bus number */
unsigned short  wTypeTrigger;				/* Type de trigger                              // Trigger condition */
unsigned short  wDummy;
    union                                   /* Parameters */
    {
        struct
        {
        unsigned long   dwIdent;            /* Identificateur du message                    // CAN identifier value */
        tCanTypeId      eTypeId;            /* Type d'identifcateur STD ou XTD              // Identifier type (standard (11 bits) or extended (29 bits) */
        } hCan;
        struct
        {
        unsigned char   bDummy[50];
        } hDummy;
    }u;
} tTrigger;
#define IO_FALLING_EDGE     0x0001
#define IO_RISING_EDGE      0x0002


#define ANA_CODE_READ           0x0000
#define ANA_CODE_WRITE          0x0001
#define ANA_CODE_SET_MODE       0x0002
#define ANA_CODE_SET_CHANNEL    0x0003

#define ANA_MAX_COUNT       32

typedef struct
{
    unsigned short  wCode;                  /* Code fonction                            // Function code */
    unsigned short  wMode;
    union                                   /* Parameters */
    {
        struct
        {
            signed   long   lFactor[ANA_MAX_COUNT]; /* Facteur                                  // Factor */
            signed   long   lOffset[ANA_MAX_COUNT]; /* Offset                                   // Offset */
        } hReadWrite;
        struct
        {
            unsigned short  wChannel;               /* Canal de communication                   // Message offset */
            unsigned short  wPeriod;                /* Périodicité du message                   // Message periodicity */
            unsigned long   dwIdent;                /* Identificateur du message                // Message identifier */
            unsigned short  wTypeBus;               /* Type de bus (CAN, VAN...)                // Bus type */
            unsigned short  wBus;                   /* Numéro de bus                            // Bus number */
        } hSetChannel;
    }u;
} tAnaTransfer;


//#define UART_CODE_READ		0x0000
//#define UART_CODE_WRITE		0x0001
//#define UART_CODE_CONFIG	0x0002
//#define UART_CODE_OPEN		0x0003
//#define UART_CODE_CLOSE		0x0004
//
//#define UART_MAX_DATA       1024
//
//typedef struct
//{
//    unsigned short  wCode;                  /* Code fonction                            // Function code */
//    unsigned short  wLength;
//    union                                   /* Parameters */
//    {
//        struct
//        {
//			unsigned long   dwBaudrate;  
//			unsigned short	wStopBit;                                 
//			unsigned short	wParityType;                                 
//			unsigned short	wDataBit;                                 
//        } hConfig;
//     	unsigned char	bData[UART_MAX_DATA];/* Buffer de donnée                         // Data buffer */
//    }u;
//} tUartTransfer;


#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Gestion des sorties logiques                                             // Set diagital output state */
_MUXSPEC tMuxStatus _MUXAPI IOSetOutput(unsigned short wCard, unsigned short wOutputValue, unsigned short wOutputMask);
/* Gestion des entrées logiques                                             // Read digital input value */
_MUXSPEC tMuxStatus _MUXAPI IOGetInput(unsigned short wCard, unsigned short *wInputValue);
/* Nombre d'entrées/sorties logiques                                        // get input / output count */
_MUXSPEC tMuxStatus _MUXAPI IOGetCount(unsigned short wCard, unsigned short *wInputCount, unsigned short *wOutputCount);
/* Configure les remontées d'entrées                                        // Configure trigger input */
_MUXSPEC tMuxStatus _MUXAPI IOConfigInput(unsigned short wCard, unsigned short wInput, unsigned short wEdge);
/* Configure les sorties trigger                                            // Trigger output setup */
_MUXSPEC tMuxStatus _MUXAPI IOConfigOutput(unsigned short wCard, unsigned short wOutput, tTrigger *hTrigger);
/* Communication sur la liaison SPI                                         // SPI communication protocol */
_MUXSPEC tMuxStatus _MUXAPI SPITransfer(unsigned short wCard, tSPIInfo *hSPIInfo);
/* Communication sur la liaison I2C                                         // I2C communication protocol */
_MUXSPEC tMuxStatus _MUXAPI I2CTransfer(unsigned short wCard, tI2CInfo *hI2CInfo);
/* Appel de fonction propriétaire                                           // Proprietary function */
_MUXSPEC tMuxStatus _MUXAPI FctProprietary(unsigned short wCard, tProprietaryInfo *hProprietaryInfo);
/* Activation */
_MUXSPEC tMuxStatus _MUXAPI PryActivate(unsigned short wCard, unsigned short wBus);
/* Désactivation */
_MUXSPEC tMuxStatus _MUXAPI PryDeactivate(unsigned short wCard, unsigned short wBus);
/* Récupération d'un événement en provenance du réseau                      // Get an event from DLL */
_MUXSPEC tMuxStatus _MUXAPI PryGetEvent(unsigned short wCard, unsigned short wBus, tPryEvent *hPryEvent);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI PrySetNotification(unsigned short wCard, unsigned short wBus, void * hWinEvent);
/* Purge de la file d'attente de réception                                  // Flush FIFO rx */
_MUXSPEC tMuxStatus _MUXAPI PryClearFifoRx(unsigned short wCard, unsigned short wBus);
/* Etat de la FIFO                                                          // Counts of event in the receive queue */
_MUXSPEC tMuxStatus _MUXAPI PryGetFifoRxLevel(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
/* Configuration des voies analogiques                                      // Analog channels configuration */
_MUXSPEC tMuxStatus _MUXAPI ANATransfer(unsigned short wCard, tAnaTransfer *hAnaTransfer);
/* Lecture de la valeur des convertisseurs									//	Read the analogic register value */
_MUXSPEC tMuxStatus _MUXAPI ANAGetInput(unsigned short wCard, unsigned short wChannel, unsigned short *wInputValue);
/* Activation des entrées PWM                                               // PWM input configuration */
_MUXSPEC tMuxStatus _MUXAPI PWMInputActivate(unsigned short wCard, unsigned short wNum, unsigned short wBusType, unsigned short wBus, unsigned short wPeriod, unsigned short wTimeOut);
/* Désactivation des entrées PWM                                            // PWM input configuration */
_MUXSPEC tMuxStatus _MUXAPI PWMInputDeactivate(unsigned short wCard, unsigned short wNum);
/* Configuration des sorties PWM                                            // PWM output configuration */
_MUXSPEC tMuxStatus _MUXAPI PWMOutputConfig(unsigned short wCard, unsigned short wNum, unsigned short wPrescaler, unsigned short wPeriod);
/* Activation des sorties PWM                                               // PWM output start */
_MUXSPEC tMuxStatus _MUXAPI PWMOutputActivate(unsigned short wCard, unsigned short wNum, unsigned short wValue);
/* Arrêt des sorties PWM                                                    // PWM output stop */
_MUXSPEC tMuxStatus _MUXAPI PWMOutputDeactivate(unsigned short wCard, unsigned short wNum);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tIOSetOutput)(unsigned short wCard, unsigned short wOutputValue, unsigned short wOutputMask);
typedef tMuxStatus (__stdcall * tIOGetInput)(unsigned short wCard, unsigned short *wInputValue);
typedef tMuxStatus (__stdcall * tIOGetCount)(unsigned short wCard, unsigned short *wInputCount, unsigned short *wOutputCount);
typedef tMuxStatus (__stdcall * tIOConfigInput)(unsigned short wCard, unsigned short wInput, unsigned short wEdge);
typedef tMuxStatus (__stdcall * tIOConfigOutput)(unsigned short wCard, unsigned short wOutput, tTrigger *hTrigger);
typedef tMuxStatus (__stdcall * tSPITransfer)(unsigned short wCard, tSPIInfo *hSPIInfo);
typedef tMuxStatus (__stdcall * tI2CTransfer)(unsigned short wCard, tI2CInfo *hI2CInfo);
typedef tMuxStatus (__stdcall * tFctProprietary)(unsigned short wCard, tProprietaryInfo *hProprietaryInfo);
typedef tMuxStatus (__stdcall * tPryActivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tPryDeactivate)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tPryGetEvent)(unsigned short wCard, unsigned short wBus, tPryEvent *hPryEvent);
typedef tMuxStatus (__stdcall * tPrySetNotification)(unsigned short wCard, unsigned short wBus, void * hWinEvent);
typedef tMuxStatus (__stdcall * tPryClearFifoRx)(unsigned short wCard, unsigned short wBus);
typedef tMuxStatus (__stdcall * tPryGetFifoRxLevel)(unsigned short wCard, unsigned short wBus, unsigned short wParam, unsigned short *wCount, unsigned short *wMaxCount);
typedef tMuxStatus (__stdcall * tANATransfer)(unsigned short wCard, tAnaTransfer *hAnaTransfer);
typedef tMuxStatus (__stdcall * tANAGetInput)(unsigned short wCard, unsigned short wChannel, unsigned short *wInputValue);
typedef tMuxStatus (__stdcall * tPWMInputActivate)(unsigned short wCard, unsigned short wNum, unsigned short wBusType, unsigned short wBus, unsigned short wPeriod, unsigned short wTimeOut);
typedef tMuxStatus (__stdcall * tPWMInputDeactivate)(unsigned short wCard, unsigned short wNum);
typedef tMuxStatus (__stdcall * tPWMOutputConfig)(unsigned short wCard, unsigned short wNum, unsigned short wPrescaler, unsigned short wPeriod);
typedef tMuxStatus (__stdcall * tPWMOutputActivate)(unsigned short wCard, unsigned short wNum, unsigned short wValue);
typedef tMuxStatus (__stdcall * tPWMOutputDeactivate)(unsigned short wCard, unsigned short wNum);
#endif
#ifdef __cplusplus
	}
#endif
/*******************************************************************************
; Routines de gestion du timer
*******************************************************************************/
#ifdef __cplusplus
	extern "C" {
#endif
#ifndef MUX_DYNAMIC_DLL
/* Configuration du timer en millisecondes                                  // Milliseconde Timer configuration */
_MUXSPEC tMuxStatus _MUXAPI TimerSet(unsigned short wCard, unsigned short wTimerValue);
/* Initialisation du handle pour notifier un événement à l'application      // Set a communication handle to notify an event to the application */
_MUXSPEC tMuxStatus _MUXAPI TimerSetNotification(unsigned short wCard, void * hWinEvent);
/* Lecture de l'horloge                                                     // Time reading */
_MUXSPEC tMuxStatus _MUXAPI TimerRead(unsigned short wCard, unsigned long *dwTimerValue, unsigned short *wTimeError, unsigned short *wMaxTimePrecision);
#else
/* Déclaration pour chargement dynamic      // Dynamic loading definition */
typedef tMuxStatus (__stdcall * tTimerSet)(unsigned short wCard, unsigned short wTimerValue);
typedef tMuxStatus (__stdcall * tTimerSetNotification)(unsigned short wCard, void * hWinEvent);
typedef tMuxStatus (__stdcall * tTimerRead)(unsigned short wCard, unsigned long *dwTimerValue, unsigned short *wTimeError, unsigned short *wMaxTimePrecision);
#endif
#ifdef __cplusplus
	}
#endif

/*******************************************************************************
; Routines de gestion des fichiers en flash
*******************************************************************************/
#define	FILE_MAX_DATA			4096

//	Handle sur un fichier		//	file Handle
typedef unsigned short	tFlashFile;

typedef enum _tFlashFileWhence
{
	FLASHFILE_WHENCE_BEGINING  	=	0,			//	Debut du fichier			   	//	Begining of the file
	FLASHFILE_WHENCE_CURRENT	=	1,			//	Emplacement courant du fichier	//	Current position of the file
	FLASHFILE_WHENCE_END		=	2			//	Fin du fichier					//	End of the file
} tFlashFileWhence ;


typedef enum _tFlashFATKind
{
	FLASHFATK_Unknown			=	0,			//	Type inconnu					//	Unknown kind
	FLASHFATK_FAT12				=	1,			//	FAT	12
	FLASHFATK_FAT16				=	2,			//	FAT	16
	FLASHFATK_FAT32				=	3			//	FAT	32
} tFlashFATKind ;

typedef struct _tFlashInformations
{
	unsigned long	dwTotalSpace;				//	Capacité de la Flash en clusters					//	Capacity of the Flash card in clusters
	unsigned long	dwFreeSpace;				//	Capacité restante en clusters 						//	Free capacity in clusters
	unsigned char	bLogicalUnit;				//	Numéro du lecteur logique							// Logical Unit Number
	unsigned char	bReserved;					//	Réservé												// Reserved
	unsigned long	dwClusterSize;				//	Taille d'un cluster                					//  Cluster size
	unsigned long	dwClusterCount;				//	Nombre total de cluster								//	How many cluster ?
	char			szVolumeLabel[16];			//	Nom du volume										//	Volume name
	unsigned long	dwVolumeID;					//	Volume ID											//	Volume ID
	tFlashFATKind 	tFATKind;					//	Type de FAT (12,16,32,...)							//	FAT kind (12,16,32,...)
	char			szCFCardSN[20];				//  Numéro de série de la carte CompactFlash en ASCII	//Compact Flash serial number
	char			szCFCardModel[40];			//  Nom de la CF en ASCII 								//Compact Flash model name
	unsigned short	wPioMode;					//  Mode PIO (de 0 à 6) si 0xFFFF -> pas d'info 		//PIO mode
} tFlashInformations ;

typedef struct _tFlashFileDownloadData
{
	unsigned short	wReserved;					//	Réservé								//	Reserved
	void			*pvFatfile;					//	Réservé								//	Reserved
	unsigned short	tError;						//	Réservé								//	Reserved
	void			*pvUserData;				//	Pointeur sur des infos utilisateur		//	User data
	unsigned long	dwPacketCount;				//	N° du paquet reçu						//	Packet number
	unsigned long	dwBaudRate;					//	Débit du transfert						//	Baudrate
	unsigned long	dwBytesDone;				//	Nombre d'octets déjà récupéré			//	Number of bytes already downloaded
	unsigned long	dwTotalBytes;				//	Nombre d'octets total					//	total byte to download
	unsigned long	dwDataSize;					//	Nombre d'octet reçu ce coup ci		//	Number of bytes read this time
	unsigned char	bData[ FILE_MAX_DATA ];		//	Données lus							//	Data
} tFlashFileDownloadData ;

typedef unsigned short ( *tFlashFileDownload_Callback )( tFlashFileDownloadData *tDownloadData );

#ifdef __cplusplus
	extern "C" {
#endif


#ifndef MUX_DYNAMIC_DLL
//	Ouverture de fichier									//	Open a file
_MUXSPEC tMuxStatus _MUXAPI FlashFileOpen( unsigned short wCard, char *szFileName, char *szMode, tFlashFile *hFile );
//	Fermeture de fichier									//	Close a file
_MUXSPEC tMuxStatus _MUXAPI FlashFileClose( unsigned short wCard, tFlashFile *hFile );
//	Lecture depuis un fichier								//	Read a buffer from a file
_MUXSPEC tMuxStatus _MUXAPI FlashFileRead( unsigned short wCard, void *vBuffer, unsigned short wSize, tFlashFile *hFile );
//	Ecriture dans un fichier								//	Write a buffer to a file
_MUXSPEC tMuxStatus _MUXAPI FlashFileWrite( unsigned short wCard, void *vBuffer, unsigned short wSize, tFlashFile *hFile );
//	Déplacement dans un fichier							//	Seek into a file
_MUXSPEC tMuxStatus _MUXAPI FlashFileSeek( unsigned short wCard, tFlashFileWhence hWhence, signed long iOffset, tFlashFile *hFile );
//	Indique la position dans un fichier						// Tell the current file position
_MUXSPEC tMuxStatus _MUXAPI FlashFileTell( unsigned short wCard, unsigned long *dwPosition, tFlashFile *hFile );
//	Indique la taille d'un fichier						// Tell the size of a file
_MUXSPEC tMuxStatus _MUXAPI FlashFileGetSize( unsigned short wCard, unsigned long *dwSize, tFlashFile *hFile );
//	Informations sur la mémoire flash						//	Informations about flash card
_MUXSPEC tMuxStatus _MUXAPI FlashGetInformations( unsigned short wCard, tFlashInformations *tInfos );
//	Recherche le 1er fichier correspondant au masque	//	Find the first file mathcing the mask
_MUXSPEC tMuxStatus _MUXAPI FlashFindFirstFile( unsigned short wCard, char *szMask, char *szFoundFile );
//	Recherche le fichier suivant						//	Find the next file
_MUXSPEC tMuxStatus _MUXAPI FlashFindNextFile( unsigned short wCard, char *szFoundFile );
//	Efface le fichier									//	Delete the file
_MUXSPEC tMuxStatus _MUXAPI FlashFileDelete( unsigned short wCard, char *szFileName );
//	Télécharge un fichier le plus rapidement possible		//	Download a file using the faster way available
_MUXSPEC tMuxStatus _MUXAPI FlashFileDownload( unsigned short wCard, char *szFileName, unsigned long dwOffset, unsigned long dwSize, tFlashFileDownload_Callback tCallBack, void *pvUserData );
//	Répare un fichier corrompu							//	Repair a corrupted file
_MUXSPEC tMuxStatus _MUXAPI FlashFileRepair( unsigned short wCard, char *szFileName );
//	formate la flash									//	Format flash memory
_MUXSPEC tMuxStatus _MUXAPI FlashFormat( unsigned short wCard, char *szVolumeLabel, tFlashFATKind tFATKind, unsigned short wSectorPerCluster );
//	Informations sur le nombre de session				// Informations about session count
_MUXSPEC tMuxStatus _MUXAPI FlashFileCountSession( unsigned short wCard, unsigned long *wTotalSession, unsigned short *wEmptySession );
//	Recherche le 1er fichier correspondant au filtre	//	Find the first file mathcing the filter
_MUXSPEC tMuxStatus _MUXAPI FlashFindFirstFileInFilter( unsigned short wCard, char *szMask, char *szFoundFile, unsigned long * ulDateStart, unsigned long *ulDateStop );
//	Recherche le fichier suivant correspondant au filtre	//	Find the next file mathcing the filter
_MUXSPEC tMuxStatus _MUXAPI FlashFindNextFileInFilter( unsigned short wCard, char *szFoundFile);
#else
//	Ouverture de fichier									//	Open a file
typedef tMuxStatus (__stdcall * tFlashFileOpen)( unsigned short wCard, char *szFileName, char *szMode, tFlashFile *hFile );
//	Fermeture de fichier									//	Close a file
typedef tMuxStatus (__stdcall * tFlashFileClose)( unsigned short wCard, tFlashFile *hFile );
//	Lecture depuis un fichier								//	Read a buffer from a file
typedef tMuxStatus (__stdcall * tFlashFileRead)( unsigned short wCard, void *vBuffer, unsigned short wSize, tFlashFile *hFile );
//	Ecriture dans un fichier								//	Write a buffer to a file
typedef tMuxStatus (__stdcall * tFlashFileWrite)( unsigned short wCard, void *vBuffer, unsigned short wSize, tFlashFile *hFile );
//	Déplacement dans un fichier							//	Seek into a file
typedef tMuxStatus (__stdcall * tFlashFileSeek)( unsigned short wCard, tFlashFileWhence hWhence, signed long iOffset, tFlashFile *hFile );
//	Indique la position dans un fichier						// Tell the current file position
typedef tMuxStatus (__stdcall * tFlashFileTell)( unsigned short wCard, unsigned long *dwPosition, tFlashFile *hFile );
//	Indique la taille d'un fichier						// Tell the size of a file
typedef tMuxStatus (__stdcall * tFlashFileGetSize)( unsigned short wCard, unsigned long *dwSize, tFlashFile *hFile );
//	Informations sur la mémoire flash					//	Informations about flash card
typedef tMuxStatus (__stdcall * tFlashGetInformations)( unsigned short wCard, tFlashInformations *tInfos );
//	Informations sur la mémoire flash						//	Informations about flash card
typedef tMuxStatus (__stdcall * tFlashFindFirstFile )( unsigned short wCard, char *szMask, char *szFoundFile );
//	Recherche le fichier suivant						//	Find the next file
typedef tMuxStatus (__stdcall * tFlashFindNextFile )( unsigned short wCard, char *szFoundFile );
//	Efface le fichier									//	Delete the file
typedef tMuxStatus (__stdcall * tFlashFileDelete )( unsigned short wCard, char *szFileName );
//	Télécharge un fichier le plus rapidement possible		//	Download a file using the faster way available
typedef tMuxStatus (__stdcall * tFlashFileDownload )( unsigned short wCard, char *szFileName, unsigned long dwOffset, unsigned long dwSize, tFlashFileDownload_Callback tCallBack, void *pvUserData );
//	Répare un fichier corrompu							//	Repair a corrupted file
typedef tMuxStatus (__stdcall * tFlashFileRepair )( unsigned short wCard, char *szFileName );
//	formate la flash									//	Format flash memory
typedef tMuxStatus (__stdcall * tFlashFormat)( unsigned short wCard, char *szVolumeLabel, tFlashFATKind tFATKind, unsigned short wSectorPerCluster );
//	Informations sur le nombre de session				// Informations about session count
typedef tMuxStatus (__stdcall * tFlashFileCountSession)( unsigned short wCard, unsigned long *wTotalSession, unsigned short *wEmptySession );
//	Recherche le 1er fichier correspondant au filtre	//	Find the first file mathcing the filter
typedef tMuxStatus (__stdcall * tFlashFindFirstFileInFilter)( unsigned short wCard, char *szMask, char *szFoundFile, unsigned long * ulDateStart, unsigned long *ulDateStop );
//	Recherche le fichier suivant correspondant au filtre	//	Find the next file mathcing the filter
typedef tMuxStatus (__stdcall * tFlashFindNextFileInFilter)( unsigned short wCard, char *szFoundFile );
#endif

#ifdef __cplusplus
	}
#endif

/*******************************************************************************
;	Routines de gestion des périphériques USB
*******************************************************************************/
#define	USB_MAX_DEVICES		32
#define	USB_MAX_PIPES		32

typedef enum _tUSBPipeDirection
{
	USB_PipeDir_In				= 1,					//	Pipe en lecture				//	Read pipe
	USB_PipeDir_Out		   		= 2,					//	Pipe en ecriture			//	Write pipe
	USB_PipeDir_InOut			= 3						//	Pipe en lecture/ecriture   	//	Read/Write pipe
} tUSBPipeDirection ;

typedef enum _tUSBPipeType
{
	USB_PipeType_Control		= 0,					//	Pipe de control		//	Control pipe
	USB_PipeType_Isochronous	= 1,					//	Pipe isochrone		//	Isochronous pipe
	USB_PipeType_Bulk	        = 2,					//	Pipe bulk			//	Bulk pipe
	USB_PipeType_Interrupt		= 3						//	Interrupt pipe
} tUSBPipeType ;

typedef struct _tUSBPipe
{
	tUSBPipeDirection	tDirection;						//	Direction du pipe	//	Pipe direction
	tUSBPipeType		tType;							//	Type de pipe		//	Pipe type
	unsigned long		dwMaxPacketSize;				//	Taille max des paquets d'échange	//	Max size of usb packet data
} tUSBPipe ;

typedef struct _tUSBPipeInfos
{
	tUSBPipe		tPipeList[ USB_MAX_PIPES ];			//	Configuration des pipes	//	configuration of pipes
	unsigned short	wPipeCount;							//	Nombre de pipes	//	Number of pipes	
} tUSBPipeInfos ;

typedef struct _tUSBDeviceID
{
	unsigned short	wVendorID;							//	Vendor ID
	unsigned short	wProductID;							//	Product ID
} tUSBDeviceID ;

typedef struct _tUSBDeviceInfo
{
	unsigned long	dwHubNumber;						//	N° du hub		//	Hub number
	unsigned long	dwPortNumber;						//	N° du port		//	Port number
	unsigned long	dwFullSpeed;						//	USB Full Speed ?
	unsigned long	dwDeviceAdress;						//	Adresse du périphérique	//	Device address
	unsigned long	dwUniqueID;							//	ID du périphérique		//	Device ID
} tUSBDeviceInfo ;

typedef struct _tUSBDevice
{
	tUSBDeviceID	tID;								//	ID du périphérique	//	Device ID
	tUSBDeviceInfo	tInfos;								//	Informations			
} tUSBDevice ; 

typedef struct _tUSBDeviceList
{
	tUSBDevice		tDeviceList[ USB_MAX_DEVICES ];		//	Liste des périphérique	//	Liste des périphériques
	unsigned short	wDeviceCount;						//	Nombre de périphérique	//	Number of devices
} tUSBDeviceList ;

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef MUX_DYNAMIC_DLL
//	Récupère la liste des périphérique connectés	//	Get the list of connected devices
_MUXSPEC tMuxStatus _MUXAPI USBLIB_GetDeviceList( tUSBDeviceID *tDevFilter, tUSBDeviceList *tDevList );
//	Ouvre un périphérique	//	Open a device
_MUXSPEC tMuxStatus _MUXAPI USBLIB_Open( unsigned short wCard );
//	Ferme un périphérique	//	Ferme a device
_MUXSPEC tMuxStatus _MUXAPI USBLIB_Close( unsigned short wCard );
//	Récupère les informations sur les pipes	//	Gets informations about pipes
_MUXSPEC tMuxStatus _MUXAPI USBLIB_GetPipesInfos( unsigned short wCard, tUSBPipeInfos *tPipeInfos );
//	Envoi de données sur un pipe	//	Sends data on a pipe
_MUXSPEC tMuxStatus _MUXAPI USBLIB_Send( unsigned short wCard, unsigned short wPipe, unsigned char *szData, unsigned long dwDataLen, unsigned long dwTimeOut );
//	Envoi de données sur le pipe00	//	Writes data on pipe00
_MUXSPEC tMuxStatus _MUXAPI USBLIB_WritePipe00( unsigned short wCard, unsigned char *byBuffer, unsigned long dwDataLen, unsigned long dwTimeOut, unsigned char *bySetupPacket );
//	Lecture de données sur le pipe00	//	Reads datas on pipe00
_MUXSPEC tMuxStatus _MUXAPI USBLIB_ReadPipe00( unsigned short wCard, unsigned char *byBuffer, unsigned long dwDataLen, unsigned long dwTimeOut, unsigned char *bySetupPacket );
//	Lecture de donnée sur un pipe	//	Reads data on a pipe
_MUXSPEC tMuxStatus _MUXAPI USBLIB_Read( unsigned short wCard, unsigned short wPipe, unsigned char *szData, unsigned long *pdwDataLen, unsigned long dwTimeOut );
//	Arrêt d'une lecture en cours	//	Cancel a read operation in progress
_MUXSPEC tMuxStatus _MUXAPI USBLIB_ReadCancel( unsigned short wCard, unsigned short wPipe );
//	Compte le nombre de endpoint de la carte	// Retrieve the number of endpoints
_MUXSPEC tMuxStatus _MUXAPI USBLIB_GetEndpointNumber( unsigned short wCard, unsigned long *dwNumEndpoint );
#else
//	Récupère la liste des périphérique connectés	//	Get the list of connected devices
typedef tMuxStatus (__stdcall * tUSBLIB_GetDeviceList )( tUSBDeviceID *tDevFilter, tUSBDeviceList *tDevList );
//	Ouvre un périphérique	//	Open a device
typedef tMuxStatus (__stdcall * tUSBLIB_Open )( unsigned short wCard );
//	Ferme un périphérique	//	Ferme a device
typedef tMuxStatus (__stdcall * tUSBLIB_Close )( unsigned short wCard );
//	Récupère les informations sur les pipes	//	Gets informations about pipes
typedef tMuxStatus (__stdcall * tUSBLIB_GetPipesInfos )( unsigned short wCard, tUSBPipeInfos *tPipeInfos );
//	Envoi de données sur un pipe	//	Sends data on a pipe
typedef tMuxStatus (__stdcall * tUSBLIB_Send )( unsigned short wCard, unsigned short wPipe, unsigned char *szData, unsigned long dwDataLen, unsigned long dwTimeOut );
//	Envoi de données sur le pipe00	//	Writes data on pipe00
typedef tMuxStatus (__stdcall * tUSBLIB_WritePipe00 )( unsigned short wCard, unsigned char *byBuffer, unsigned long dwDataLen, unsigned long dwTimeOut, unsigned char *bySetupPacket );
//	Lecture de données sur le pipe00	//	Reads datas on pipe00
typedef tMuxStatus (__stdcall * tUSBLIB_ReadPipe00 )( unsigned short wCard, unsigned char *byBuffer, unsigned long dwDataLen, unsigned long dwTimeOut, unsigned char *bySetupPacket );
//	Lecture de donnée sur un pipe	//	Reads data on a pipe
typedef tMuxStatus (__stdcall * tUSBLIB_Read )( unsigned short wCard, unsigned short wPipe, unsigned char *szData, unsigned long *pdwDataLen, unsigned long dwTimeOut );
//	Arrêt d'une lecture en cours	//	Cancel a read operation in progress
typedef tMuxStatus (__stdcall * tUSBLIB_ReadCancel )( unsigned short wCard, unsigned short wPipe );
//	Compte le nombre de endpoint de la carte	// Retrieve the number of endpoints
typedef tMuxStatus (__stdcall * tUSBLIB_GetEndpointNumber )( unsigned short wCard, unsigned long *dwNumEndpoint );
#endif

#ifdef __cplusplus
	}
#endif

#ifdef MUX_DYNAMIC_DLL
/* Déclaration des pointeurs de fonctions vers la DLL   // DLL Function pointer */
#ifndef MUX_DYNAMIC_DLL_EXTERN
 #define _MUX_DLL_EXTERN /**/
#else
 #define _MUX_DLL_EXTERN extern
#endif

tMuxStatus MuxFreeDLL(void);
tMuxStatus MuxLoadDLL(void);
tMuxStatus MuxLoadDLLClient(void);

_MUX_DLL_EXTERN tMuxGetTimings			MuxGetTimings;
_MUX_DLL_EXTERN tMuxGlobalInit			MuxGlobalInit;
_MUX_DLL_EXTERN tMuxSetUserTimerFct		MuxSetUserTimerFct;
_MUX_DLL_EXTERN tMuxCreateEvent			MuxCreateEvent;
_MUX_DLL_EXTERN tMuxCloseEvent			MuxCloseEvent;
_MUX_DLL_EXTERN tMuxWaitOnEvent			MuxWaitOnEvent;
_MUX_DLL_EXTERN tMuxSetEvent			MuxSetEvent;
_MUX_DLL_EXTERN tMuxClientServerMode	MuxClientServerMode;
_MUX_DLL_EXTERN tMuxCheckAlignment		MuxCheckAlignment;
_MUX_DLL_EXTERN tMuxCountCards		    MuxCountCards;
_MUX_DLL_EXTERN tMuxPciCountCards	    MuxPciCountCards;
_MUX_DLL_EXTERN tMuxUsbCountCards	    MuxUsbCountCards;
_MUX_DLL_EXTERN tMuxEthCountCards		MuxEthCountCards;
_MUX_DLL_EXTERN tMuxPciGetCardInfo	    MuxPciGetCardInfo;
_MUX_DLL_EXTERN tMuxUsbGetCardInfo	    MuxUsbGetCardInfo;
_MUX_DLL_EXTERN tMuxEthGetCardInfo	    MuxEthGetCardInfo;
_MUX_DLL_EXTERN tMuxInit			    MuxInit;
_MUX_DLL_EXTERN tMuxOpen			    MuxOpen;
_MUX_DLL_EXTERN tMuxGetVersion		    MuxGetVersion;
_MUX_DLL_EXTERN tMuxGetDescription		MuxGetDescription;

_MUX_DLL_EXTERN tMuxGetInformations		MuxGetInformations;
_MUX_DLL_EXTERN tMuxClose			    MuxClose;
_MUX_DLL_EXTERN tMuxGetLastErrorString	MuxGetLastErrorString;
_MUX_DLL_EXTERN tMuxGetProtectedCode	MuxGetProtectedCode;
_MUX_DLL_EXTERN tMuxUsbDownload	        MuxUsbDownload;
_MUX_DLL_EXTERN tMuxGetInternalInfo	    MuxGetInternalInfo;
_MUX_DLL_EXTERN tMuxIsLicenceActive		MuxIsLicenceActive;
_MUX_DLL_EXTERN tMuxSetProductIDMode	MuxSetProductIDMode;
_MUX_DLL_EXTERN tMuxGetBuildNumber		MuxGetBuildNumber;
_MUX_DLL_EXTERN tMuxGetRTCValue			MuxGetRTCValue;
_MUX_DLL_EXTERN tMuxSetRTCValue			MuxSetRTCValue;
_MUX_DLL_EXTERN tMuxUsbResetPipe		MuxUsbResetPipe;
_MUX_DLL_EXTERN tMuxGetHardwareID		MuxGetHardwareID;
_MUX_DLL_EXTERN tMuxSetEthernet			MuxSetEthernet;
_MUX_DLL_EXTERN tMuxGetEthernet			MuxGetEthernet;


_MUX_DLL_EXTERN tAdminOpenSession		AdminOpenSession;
_MUX_DLL_EXTERN tAdminWriteConfig		AdminWriteConfig;
_MUX_DLL_EXTERN tAdminReadConfig		AdminReadConfig;
_MUX_DLL_EXTERN tAdminGetLicenceCount	AdminGetLicenceCount;
_MUX_DLL_EXTERN tAdminReadLicences		AdminReadLicences;
_MUX_DLL_EXTERN tAdminWriteLicences		AdminWriteLicences;
_MUX_DLL_EXTERN tAdminGetLicenceData	AdminGetLicenceData;
_MUX_DLL_EXTERN tAdminSetLicenceData	AdminSetLicenceData;
_MUX_DLL_EXTERN tAdminReadLicencesData	AdminReadLicencesData;
_MUX_DLL_EXTERN tAdminWriteLicencesData	AdminWriteLicencesData;

_MUX_DLL_EXTERN tSysSetNotification		SysSetNotification;
_MUX_DLL_EXTERN tSysGetEvent			SysGetEvent;

_MUX_DLL_EXTERN tCanConfigOper		    CanConfigOper;
_MUX_DLL_EXTERN tCanConfigBus		    CanConfigBus;
_MUX_DLL_EXTERN tCanConfigParam		    CanConfigParam;
_MUX_DLL_EXTERN tCanConfigRangeFilter	CanConfigRangeFilter;	
_MUX_DLL_EXTERN tCanConfigClock			CanConfigClock;
_MUX_DLL_EXTERN tCanConfigDualFilter    CanConfigDualFilter;
_MUX_DLL_EXTERN tCanConfigStat		    CanConfigStat;
_MUX_DLL_EXTERN tCanConfigTransceiverHS CanConfigTransceiverHS;
_MUX_DLL_EXTERN tCanSelectTransceiverHS CanSelectTransceiverHS;
_MUX_DLL_EXTERN tCanConfigTransceiverLS CanConfigTransceiverLS;
_MUX_DLL_EXTERN tCanConfigTerminationLS CanConfigTerminationLS;
_MUX_DLL_EXTERN tCanReadTransceiverLS   CanReadTransceiverLS;
_MUX_DLL_EXTERN tCanCreateMsg		    CanCreateMsg;
_MUX_DLL_EXTERN tCanReadMsg				CanReadMsg;
_MUX_DLL_EXTERN tCanWriteMsg			CanWriteMsg;
_MUX_DLL_EXTERN tCanConfigPeriodic		CanConfigPeriodic;
_MUX_DLL_EXTERN tCanConfigPeriodicList	CanConfigPeriodicList;
_MUX_DLL_EXTERN tCanSetNotification	    CanSetNotification;
_MUX_DLL_EXTERN tCanActivate		    CanActivate;
_MUX_DLL_EXTERN tCanIsBusActive         CanIsBusActive;
_MUX_DLL_EXTERN tCanDeactivate		    CanDeactivate;
_MUX_DLL_EXTERN tCanSendMsg			    CanSendMsg;
_MUX_DLL_EXTERN tCanSendMsgList			CanSendMsgList;
_MUX_DLL_EXTERN tCanGetEvent		    CanGetEvent;
_MUX_DLL_EXTERN tCanBusOn			    CanBusOn;
_MUX_DLL_EXTERN tCanChangeBaudRate		CanChangeBaudRate;
_MUX_DLL_EXTERN tCanGetStat			    CanGetStat;
_MUX_DLL_EXTERN tCanGetBusState		    CanGetBusState;
_MUX_DLL_EXTERN tCanClearFifoRx		    CanClearFifoRx;
_MUX_DLL_EXTERN tCanGetFifoRxLevel      CanGetFifoRxLevel;
_MUX_DLL_EXTERN tCanReadByte		    CanReadByte;
_MUX_DLL_EXTERN tCanWriteByte		    CanWriteByte;

_MUX_DLL_EXTERN tNwcRegister		    NwcRegister;
_MUX_DLL_EXTERN tNwcGetChannelCount	    NwcGetChannelCount;
_MUX_DLL_EXTERN tNwcChannelOpen 	    NwcChannelOpen;
_MUX_DLL_EXTERN tNwcChannelConfig       NwcChannelConfig;
_MUX_DLL_EXTERN tNwcChannelParam	    NwcChannelParam;
_MUX_DLL_EXTERN tNwcChannelAddr 	    NwcChannelAddr;
_MUX_DLL_EXTERN tNwcChannelStart	    NwcChannelStart;
_MUX_DLL_EXTERN tNwcChannelStop 	    NwcChannelStop;
_MUX_DLL_EXTERN tNwcChannelClose 	    NwcChannelClose;
_MUX_DLL_EXTERN tNwcSetNotification	    NwcSetNotification;
_MUX_DLL_EXTERN tNwcActivate            NwcActivate;
_MUX_DLL_EXTERN tNwcIsBusActive         NwcIsBusActive;
_MUX_DLL_EXTERN tNwcDeactivate          NwcDeactivate;
_MUX_DLL_EXTERN tNwcChannelSendMsg      NwcChannelSendMsg;
_MUX_DLL_EXTERN tNwcChannelSendAsyncMsg NwcChannelSendAsyncMsg;
_MUX_DLL_EXTERN tNwcGetEvent            NwcGetEvent;
_MUX_DLL_EXTERN tNwcGetIdent            NwcGetIdent;
_MUX_DLL_EXTERN tNwcGetFifoRxLevel      NwcGetFifoRxLevel;
_MUX_DLL_EXTERN tNwcConfigSpyMode       NwcConfigSpyMode;
_MUX_DLL_EXTERN tNwcGetChannelState     NwcGetChannelState;
_MUX_DLL_EXTERN tNwcChannelSetBytePadding		NwcChannelSetBytePadding;

_MUX_DLL_EXTERN tJ19ChannelOpen			J19ChannelOpen;
_MUX_DLL_EXTERN tJ19ChannelAddr			J19ChannelAddr;
_MUX_DLL_EXTERN tJ19ChannelParam		J19ChannelParam;
_MUX_DLL_EXTERN tJ19ChannelConfig		J19ChannelConfig;
_MUX_DLL_EXTERN tJ19ChannelStart		J19ChannelStart;
_MUX_DLL_EXTERN tJ19ChannelStop			J19ChannelStop;
_MUX_DLL_EXTERN tJ19ChannelClose		J19ChannelClose;
_MUX_DLL_EXTERN tJ19Activate			J19Activate;
_MUX_DLL_EXTERN tJ19ConfigBus           J19ConfigBus;
_MUX_DLL_EXTERN tJ19Deactivate			J19Deactivate;
_MUX_DLL_EXTERN tJ19ChannelSendMsg		J19ChannelSendMsg;
_MUX_DLL_EXTERN tJ19ChannelSendNMEAFastPacket	J19ChannelSendNMEAFastPacket;
_MUX_DLL_EXTERN tJ19SetNotification		J19SetNotification;
_MUX_DLL_EXTERN tJ19GetEvent			J19GetEvent;
_MUX_DLL_EXTERN tJ19GetFifoRxLevel		J19GetFifoRxLevel;
_MUX_DLL_EXTERN tJ19StoreNMEAFastPacket	J19StoreNMEAFastPacket;

_MUX_DLL_EXTERN tLinConfigOper          LinConfigOper;
_MUX_DLL_EXTERN tLinConfigBus		    LinConfigBus;
_MUX_DLL_EXTERN tLinConfigUart		    LinConfigUart;
_MUX_DLL_EXTERN tLinConfigParam		    LinConfigParam;
_MUX_DLL_EXTERN tLinConfigStat		    LinConfigStat;
_MUX_DLL_EXTERN tLinSetVersion		    LinSetVersion;
_MUX_DLL_EXTERN tLinSetNotification	    LinSetNotification;
_MUX_DLL_EXTERN tLinActivate		    LinActivate;
_MUX_DLL_EXTERN tLinIsBusActive		    LinIsBusActive;
_MUX_DLL_EXTERN tLinConfigTransceiver   LinConfigTransceiver;
_MUX_DLL_EXTERN tLinConfigPeriodic		LinConfigPeriodic;
_MUX_DLL_EXTERN tLinConfigPeriodicList	LinConfigPeriodicList;
_MUX_DLL_EXTERN tLinDeactivate		    LinDeactivate;
_MUX_DLL_EXTERN tLinSendMsg			    LinSendMsg;
_MUX_DLL_EXTERN tLinSendMsgList		    LinSendMsgList;
_MUX_DLL_EXTERN tLinGetEvent		    LinGetEvent;
_MUX_DLL_EXTERN tLinGetStat			    LinGetStat;
_MUX_DLL_EXTERN tLinGetBusState		    LinGetBusState;
_MUX_DLL_EXTERN tLinSetSleepMode	    LinSetSleepMode;
_MUX_DLL_EXTERN tLinSetWakeUpMode	    LinSetWakeUpMode;
_MUX_DLL_EXTERN tLinClearFifoRx	        LinClearFifoRx;
_MUX_DLL_EXTERN tLinClearBufferIFR	    LinClearBufferIFR;
_MUX_DLL_EXTERN tLinGetFifoRxLevel      LinGetFifoRxLevel;

_MUX_DLL_EXTERN tNwlGetChannelCount	    NwlGetChannelCount;
_MUX_DLL_EXTERN tNwlChannelOpen 	    NwlChannelOpen;
_MUX_DLL_EXTERN tNwlChannelConfig       NwlChannelConfig;
_MUX_DLL_EXTERN tNwlChannelParam	    NwlChannelParam;
_MUX_DLL_EXTERN tNwlChannelAddr 	    NwlChannelAddr;
_MUX_DLL_EXTERN tNwlChannelStart	    NwlChannelStart;
_MUX_DLL_EXTERN tNwlChannelStop 	    NwlChannelStop;
_MUX_DLL_EXTERN tNwlChannelClose 	    NwlChannelClose;
_MUX_DLL_EXTERN tNwlSetNotification	    NwlSetNotification;
_MUX_DLL_EXTERN tNwlActivate            NwlActivate;
_MUX_DLL_EXTERN tNwlIsBusActive         NwlIsBusActive;
_MUX_DLL_EXTERN tNwlDeactivate          NwlDeactivate;
_MUX_DLL_EXTERN tNwlChannelSendMsg      NwlChannelSendMsg;
_MUX_DLL_EXTERN tNwlChannelReceiveMsg   NwlChannelReceiveMsg;
_MUX_DLL_EXTERN tNwlGetEvent            NwlGetEvent;
_MUX_DLL_EXTERN tNwlGetFifoRxLevel      NwlGetFifoRxLevel;
_MUX_DLL_EXTERN tNwlGetChannelState     NwlGetChannelState;

_MUX_DLL_EXTERN tVanConfigOper          VanConfigOper;
_MUX_DLL_EXTERN tVanConfigBus           VanConfigBus;
_MUX_DLL_EXTERN tVanConfigParam         VanConfigParam;
_MUX_DLL_EXTERN tVanConfigStat          VanConfigStat;
_MUX_DLL_EXTERN tVanCreateMsg           VanCreateMsg;
_MUX_DLL_EXTERN tVanConfigPeriodic		VanConfigPeriodic;
_MUX_DLL_EXTERN tVanConfigPeriodicList	VanConfigPeriodicList;
_MUX_DLL_EXTERN tVanSetNotification     VanSetNotification;
_MUX_DLL_EXTERN tVanActivate            VanActivate;
_MUX_DLL_EXTERN tVanIsBusActive         VanIsBusActive;
_MUX_DLL_EXTERN tVanDeactivate          VanDeactivate;
_MUX_DLL_EXTERN tVanSendMsg             VanSendMsg;
_MUX_DLL_EXTERN tVanSendMsgList			VanSendMsgList;
_MUX_DLL_EXTERN tVanGetEvent            VanGetEvent;
_MUX_DLL_EXTERN tVanGetStat             VanGetStat;
_MUX_DLL_EXTERN tVanGetBusState         VanGetBusState;
_MUX_DLL_EXTERN tVanSetSleepMode        VanSetSleepMode;
_MUX_DLL_EXTERN tVanSetWakeUpMode       VanSetWakeUpMode;
_MUX_DLL_EXTERN tVanGetSleepMode        VanGetSleepMode;
_MUX_DLL_EXTERN tVanSetTIP              VanSetTIP;
_MUX_DLL_EXTERN tVanGetSDCValue         VanGetSDCValue;
_MUX_DLL_EXTERN tVanClearFifoRx         VanClearFifoRx;
_MUX_DLL_EXTERN tVanGetFifoRxLevel      VanGetFifoRxLevel;
_MUX_DLL_EXTERN tVanReadByte            VanReadByte;
_MUX_DLL_EXTERN tVanWriteByte           VanWriteByte;

_MUX_DLL_EXTERN tIsoConfigOper          IsoConfigOper;
_MUX_DLL_EXTERN tIsoConfigBus           IsoConfigBus;
_MUX_DLL_EXTERN tIsoConfigUart           IsoConfigUart;
_MUX_DLL_EXTERN tIsoConfigParam		    IsoConfigParam;
_MUX_DLL_EXTERN tIsoConfigStat		    IsoConfigStat;
_MUX_DLL_EXTERN tIsoConfigPeriodic		IsoConfigPeriodic;
_MUX_DLL_EXTERN tIso14230ConfigPeriodic	Iso14230ConfigPeriodic;
_MUX_DLL_EXTERN tIsoActivate            IsoActivate;
_MUX_DLL_EXTERN tIsoIsBusActive         IsoIsBusActive;
_MUX_DLL_EXTERN tIsoDeactivate          IsoDeactivate;
_MUX_DLL_EXTERN tIsoSetNotification     IsoSetNotification;
_MUX_DLL_EXTERN tIsoSendMsg             IsoSendMsg;
_MUX_DLL_EXTERN tIso14230SendMsg        Iso14230SendMsg;
_MUX_DLL_EXTERN tIsoGetEvent            IsoGetEvent;
_MUX_DLL_EXTERN tIsoWaitResponse        IsoWaitResponse;
_MUX_DLL_EXTERN tIsoSendResp            IsoSendResp;
_MUX_DLL_EXTERN tIsoChangeBaudRate      IsoChangeBaudRate;
_MUX_DLL_EXTERN tIsoGetStat			    IsoGetStat;
_MUX_DLL_EXTERN tIsoClearFifoRx		    IsoClearFifoRx;
_MUX_DLL_EXTERN tIsoGetFifoRxLevel      IsoGetFifoRxLevel;
_MUX_DLL_EXTERN tIsoSetDataRxLevel      IsoSetDataRxLevel;
_MUX_DLL_EXTERN tIsoReadByte            IsoReadByte;
_MUX_DLL_EXTERN tIsoWriteByte           IsoWriteByte;

_MUX_DLL_EXTERN tJ18ConfigOper          J18ConfigOper;
_MUX_DLL_EXTERN tJ18ConfigBus		J18ConfigBus;
_MUX_DLL_EXTERN tJ18Activate		J18Activate;
_MUX_DLL_EXTERN tJ18IsBusActive         J18IsBusActive;
_MUX_DLL_EXTERN tJ18Deactivate	        J18Deactivate;
_MUX_DLL_EXTERN tJ18SendMsg		J18SendMsg;
_MUX_DLL_EXTERN tJ18GetEvent		J18GetEvent;
_MUX_DLL_EXTERN tJ18SetNotification     J18SetNotification;

_MUX_DLL_EXTERN tJ1587ConfigOper        J1587ConfigOper;
_MUX_DLL_EXTERN tJ1587ConfigBus		    J1587ConfigBus;
_MUX_DLL_EXTERN tJ1587ConfigParam	    J1587ConfigParam;
_MUX_DLL_EXTERN tJ1587ConfigStat 	    J1587ConfigStat;
_MUX_DLL_EXTERN tJ1587ConfigPeriodic	J1587ConfigPeriodic;
_MUX_DLL_EXTERN tJ1587Activate		    J1587Activate;
_MUX_DLL_EXTERN tJ1587IsBusActive       J1587IsBusActive;
_MUX_DLL_EXTERN tJ1587Deactivate	    J1587Deactivate;
_MUX_DLL_EXTERN tJ1587SendMsg		    J1587SendMsg;
_MUX_DLL_EXTERN tJ1587GetEvent		    J1587GetEvent;
_MUX_DLL_EXTERN tJ1587GetBusState 	    J1587GetBusState;
_MUX_DLL_EXTERN tJ1587GetStat	 	    J1587GetStat;
_MUX_DLL_EXTERN tJ1587SetNotification   J1587SetNotification;
_MUX_DLL_EXTERN tJ1587ClearFifoRx		J1587ClearFifoRx;
_MUX_DLL_EXTERN tJ1587GetFifoRxLevel    J1587GetFifoRxLevel;

_MUX_DLL_EXTERN tNMEA0183ConfigOper      NMEA0183ConfigOper;
_MUX_DLL_EXTERN tNMEA0183ConfigBus		 NMEA0183ConfigBus;
_MUX_DLL_EXTERN tNMEA0183ConfigUart		 NMEA0183ConfigUart;
_MUX_DLL_EXTERN tNMEA0183ConfigParam	 NMEA0183ConfigParam;
_MUX_DLL_EXTERN tNMEA0183ConfigStat 	 NMEA0183ConfigStat;
_MUX_DLL_EXTERN tNMEA0183ConfigPeriodic	 NMEA0183ConfigPeriodic;
_MUX_DLL_EXTERN tNMEA0183Activate		 NMEA0183Activate;
_MUX_DLL_EXTERN tNMEA0183IsBusActive     NMEA0183IsBusActive;
_MUX_DLL_EXTERN tNMEA0183Deactivate	     NMEA0183Deactivate;
_MUX_DLL_EXTERN tNMEA0183SendMsg		 NMEA0183SendMsg;
_MUX_DLL_EXTERN tNMEA0183GetEvent		 NMEA0183GetEvent;
_MUX_DLL_EXTERN tNMEA0183GetBusState 	 NMEA0183GetBusState;
_MUX_DLL_EXTERN tNMEA0183GetStat	 	 NMEA0183GetStat;
_MUX_DLL_EXTERN tNMEA0183SetNotification NMEA0183SetNotification;
_MUX_DLL_EXTERN tNMEA0183ClearFifoRx	 NMEA0183ClearFifoRx;
_MUX_DLL_EXTERN tNMEA0183GetFifoRxLevel  NMEA0183GetFifoRxLevel;

#ifdef _WIN32_WCE	// Under Windows CE
_MUX_DLL_EXTERN tWINCEConfigParam		WINCEConfigParam;
_MUX_DLL_EXTERN tWINCESetNotification	WINCESetNotification;
_MUX_DLL_EXTERN tWINCEActivate			WINCEActivate;
_MUX_DLL_EXTERN tWINCEDeactivate		WINCEDeactivate;
_MUX_DLL_EXTERN tWINCEGetPowerState		WINCEGetPowerState;
_MUX_DLL_EXTERN tWINCEGetEvent			WINCEGetEvent;
_MUX_DLL_EXTERN tWINCEIsDriverUnloaded	WINCEIsDriverUnloaded;
#endif	// _WIN32_WCE	

_MUX_DLL_EXTERN tIOSetOutput		    IOSetOutput;
_MUX_DLL_EXTERN tIOGetInput			    IOGetInput;
_MUX_DLL_EXTERN tIOGetCount			    IOGetCount;
_MUX_DLL_EXTERN tIOConfigInput          IOConfigInput;
_MUX_DLL_EXTERN tIOConfigOutput         IOConfigOutput;
_MUX_DLL_EXTERN tSPITransfer            SPITransfer;
_MUX_DLL_EXTERN tI2CTransfer            I2CTransfer;
_MUX_DLL_EXTERN tFctProprietary         FctProprietary;
_MUX_DLL_EXTERN tPryActivate			PryActivate;
_MUX_DLL_EXTERN tPryDeactivate			PryDeactivate;
_MUX_DLL_EXTERN tPryGetEvent			PryGetEvent;
_MUX_DLL_EXTERN tPrySetNotification		PrySetNotification;
_MUX_DLL_EXTERN tPryClearFifoRx			PryClearFifoRx;
_MUX_DLL_EXTERN tPryGetFifoRxLevel		PryGetFifoRxLevel;

_MUX_DLL_EXTERN tANATransfer            ANATransfer;
_MUX_DLL_EXTERN tANAGetInput			ANAGetInput;
_MUX_DLL_EXTERN tPWMInputActivate       PWMInputActivate;
_MUX_DLL_EXTERN tPWMInputDeactivate     PWMInputDeactivate;
_MUX_DLL_EXTERN tPWMOutputConfig        PWMOutputConfig;
_MUX_DLL_EXTERN tPWMOutputActivate      PWMOutputActivate;
_MUX_DLL_EXTERN tPWMOutputDeactivate    PWMOutputDeactivate;

_MUX_DLL_EXTERN tTimerSet			    TimerSet;
_MUX_DLL_EXTERN tTimerSetNotification	TimerSetNotification;
_MUX_DLL_EXTERN tTimerRead			    TimerRead;

_MUX_DLL_EXTERN tFlashFileOpen			FlashFileOpen;
_MUX_DLL_EXTERN tFlashFileClose			FlashFileClose;
_MUX_DLL_EXTERN tFlashFileRead			FlashFileRead;
_MUX_DLL_EXTERN tFlashFileWrite			FlashFileWrite;
_MUX_DLL_EXTERN tFlashFileSeek			FlashFileSeek;
_MUX_DLL_EXTERN tFlashFileTell			FlashFileTell;
_MUX_DLL_EXTERN tFlashFileGetSize  		FlashFileGetSize;
_MUX_DLL_EXTERN tFlashGetInformations	FlashGetInformations;
_MUX_DLL_EXTERN tFlashFindFirstFile		FlashFindFirstFile;
_MUX_DLL_EXTERN tFlashFindNextFile		FlashFindNextFile;
_MUX_DLL_EXTERN tFlashFileDelete		FlashFileDelete;
_MUX_DLL_EXTERN tFlashFileDownload		FlashFileDownload;
_MUX_DLL_EXTERN tFlashFileRepair		FlashFileRepair;
_MUX_DLL_EXTERN tFlashFormat			FlashFormat;
_MUX_DLL_EXTERN tFlashFileCountSession	FlashFileCountSession;
_MUX_DLL_EXTERN tFlashFindFirstFileInFilter	FlashFindFirstFileInFilter;
_MUX_DLL_EXTERN tFlashFindNextFileInFilter	FlashFindNextFileInFilter;

_MUX_DLL_EXTERN tUSBLIB_GetDeviceList	USBLIB_GetDeviceList;
_MUX_DLL_EXTERN tUSBLIB_Open			USBLIB_Open;
_MUX_DLL_EXTERN tUSBLIB_Close			USBLIB_Close;
_MUX_DLL_EXTERN tUSBLIB_GetPipesInfos	USBLIB_GetPipesInfos;
_MUX_DLL_EXTERN tUSBLIB_Send			USBLIB_Send;
_MUX_DLL_EXTERN tUSBLIB_WritePipe00		USBLIB_WritePipe00;
_MUX_DLL_EXTERN tUSBLIB_ReadPipe00		USBLIB_ReadPipe00;
_MUX_DLL_EXTERN tUSBLIB_Read			USBLIB_Read;
_MUX_DLL_EXTERN tUSBLIB_ReadCancel		USBLIB_ReadCancel;
_MUX_DLL_EXTERN tUSBLIB_GetEndpointNumber	USBLIB_GetEndpointNumber;

#ifndef MUX_DYNAMIC_DLL_EXTERN
/* Il faut initialiser les pointeurs de fonction DLL // You must call this function first to initialise pointer to library */
static HINSTANCE	hInst=NULL;
tMuxStatus MuxInitAddr(void)
{
	if ((MuxGetTimings			=(tMuxGetTimings)			GetProcAddress(hInst, REFMUX_STR("MuxGetTimings"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGlobalInit			=(tMuxGlobalInit)			GetProcAddress(hInst, REFMUX_STR("MuxGlobalInit"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxSetUserTimerFct		=(tMuxSetUserTimerFct)		GetProcAddress(hInst, REFMUX_STR("MuxSetUserTimerFct"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxCreateEvent			=(tMuxCreateEvent)			GetProcAddress(hInst, REFMUX_STR("MuxCreateEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxCloseEvent			=(tMuxCloseEvent)			GetProcAddress(hInst, REFMUX_STR("MuxCloseEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxWaitOnEvent			=(tMuxWaitOnEvent)			GetProcAddress(hInst, REFMUX_STR("MuxWaitOnEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxSetEvent			=(tMuxSetEvent)				GetProcAddress(hInst, REFMUX_STR("MuxSetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxClientServerMode	=(tMuxClientServerMode)		GetProcAddress(hInst, REFMUX_STR("MuxClientServerMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxCheckAlignment		=(tMuxCheckAlignment)		GetProcAddress(hInst, REFMUX_STR("MuxCheckAlignment"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxCountCards			=(tMuxCountCards)           GetProcAddress(hInst, REFMUX_STR("MuxCountCards"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxPciCountCards		=(tMuxPciCountCards)	    GetProcAddress(hInst, REFMUX_STR("MuxPciCountCards"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxUsbCountCards		=(tMuxUsbCountCards)	    GetProcAddress(hInst, REFMUX_STR("MuxUsbCountCards"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxEthCountCards		=(tMuxEthCountCards)	    GetProcAddress(hInst, REFMUX_STR("MuxEthCountCards"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxPciGetCardInfo		=(tMuxPciGetCardInfo)	    GetProcAddress(hInst, REFMUX_STR("MuxPciGetCardInfo"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxUsbGetCardInfo		=(tMuxUsbGetCardInfo)	    GetProcAddress(hInst, REFMUX_STR("MuxUsbGetCardInfo"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxEthGetCardInfo		=(tMuxEthGetCardInfo)	    GetProcAddress(hInst, REFMUX_STR("MuxEthGetCardInfo"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxInit				=(tMuxInit)				    GetProcAddress(hInst, REFMUX_STR("MuxInit"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxOpen				=(tMuxOpen)				    GetProcAddress(hInst, REFMUX_STR("MuxOpen"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetVersion			=(tMuxGetVersion)		    GetProcAddress(hInst, REFMUX_STR("MuxGetVersion"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetDescription	  	=(tMuxGetDescription) 	    GetProcAddress(hInst, REFMUX_STR("MuxGetDescription"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetInformations		=(tMuxGetInformations)	    GetProcAddress(hInst, REFMUX_STR("MuxGetInformations"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxClose				=(tMuxClose)			    GetProcAddress(hInst, REFMUX_STR("MuxClose"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetLastErrorString	=(tMuxGetLastErrorString)   GetProcAddress(hInst, REFMUX_STR("MuxGetLastErrorString"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetProtectedCode	=(tMuxGetProtectedCode)     GetProcAddress(hInst, REFMUX_STR("MuxGetProtectedCode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxUsbDownload     	=(tMuxUsbDownload)          GetProcAddress(hInst, REFMUX_STR("MuxUsbDownload"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetInternalInfo    	=(tMuxGetInternalInfo)      GetProcAddress(hInst, REFMUX_STR("MuxGetInternalInfo"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxIsLicenceActive    	=(tMuxIsLicenceActive)      GetProcAddress(hInst, REFMUX_STR("MuxIsLicenceActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxSetProductIDMode   	=(tMuxSetProductIDMode)     GetProcAddress(hInst, REFMUX_STR("MuxSetProductIDMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetBuildNumber   	=(tMuxGetBuildNumber)     	GetProcAddress(hInst, REFMUX_STR("MuxGetBuildNumber"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetRTCValue  	 	=(tMuxGetRTCValue) 	    	GetProcAddress(hInst, REFMUX_STR("MuxGetRTCValue"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxSetRTCValue   		=(tMuxSetRTCValue)  	   	GetProcAddress(hInst, REFMUX_STR("MuxSetRTCValue"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxUsbResetPipe   		=(tMuxUsbResetPipe)  	   	GetProcAddress(hInst, REFMUX_STR("MuxUsbResetPipe"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetHardwareID  		=(tMuxGetHardwareID)  	   	GetProcAddress(hInst, REFMUX_STR("MuxGetHardwareID"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxSetEthernet 		=(tMuxSetEthernet)  	   	GetProcAddress(hInst, REFMUX_STR("MuxSetEthernet"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((MuxGetEthernet 		=(tMuxGetEthernet)  	   	GetProcAddress(hInst, REFMUX_STR("MuxGetEthernet"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((AdminOpenSession	 	=(tAdminOpenSession)		GetProcAddress(hInst, REFMUX_STR("AdminOpenSession"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminWriteConfig	 	=(tAdminWriteConfig)		GetProcAddress(hInst, REFMUX_STR("AdminWriteConfig"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminReadConfig	 	=(tAdminReadConfig)			GetProcAddress(hInst, REFMUX_STR("AdminReadConfig"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminGetLicenceCount	=(tAdminGetLicenceCount)	GetProcAddress(hInst, REFMUX_STR("AdminGetLicenceCount"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminReadLicences 		=(tAdminReadLicences)		GetProcAddress(hInst, REFMUX_STR("AdminReadLicences"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminWriteLicences		=(tAdminWriteLicences)		GetProcAddress(hInst, REFMUX_STR("AdminWriteLicences"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminGetLicenceData	=(tAdminGetLicenceData)		GetProcAddress(hInst, REFMUX_STR("AdminGetLicenceData"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminSetLicenceData	=(tAdminSetLicenceData)		GetProcAddress(hInst, REFMUX_STR("AdminSetLicenceData"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminReadLicencesData 	=(tAdminReadLicencesData)	GetProcAddress(hInst, REFMUX_STR("AdminReadLicencesData"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((AdminWriteLicencesData	=(tAdminWriteLicencesData)	GetProcAddress(hInst, REFMUX_STR("AdminWriteLicencesData"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((SysSetNotification		=(tSysSetNotification)		GetProcAddress(hInst, REFMUX_STR("SysSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((SysGetEvent			=(tSysGetEvent)			    GetProcAddress(hInst, REFMUX_STR("SysGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((CanConfigOper			=(tCanConfigOper)		    GetProcAddress(hInst, REFMUX_STR("CanConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigBus			=(tCanConfigBus)		    GetProcAddress(hInst, REFMUX_STR("CanConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigParam			=(tCanConfigParam)		    GetProcAddress(hInst, REFMUX_STR("CanConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigRangeFilter	=(tCanConfigRangeFilter)    GetProcAddress(hInst, REFMUX_STR("CanConfigRangeFilter"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigClock			=(tCanConfigClock)		    GetProcAddress(hInst, REFMUX_STR("CanConfigClock"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigDualFilter	=(tCanConfigDualFilter)		GetProcAddress(hInst, REFMUX_STR("CanConfigDualFilter"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigStat			=(tCanConfigStat)		    GetProcAddress(hInst, REFMUX_STR("CanConfigStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigTransceiverHS	=(tCanConfigTransceiverHS)	GetProcAddress(hInst, REFMUX_STR("CanConfigTransceiverHS"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanSelectTransceiverHS	=(tCanSelectTransceiverHS)	GetProcAddress(hInst, REFMUX_STR("CanSelectTransceiverHS"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigTransceiverLS	=(tCanConfigTransceiverLS)	GetProcAddress(hInst, REFMUX_STR("CanConfigTransceiverLS"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigTerminationLS	=(tCanConfigTerminationLS)	GetProcAddress(hInst, REFMUX_STR("CanConfigTerminationLS"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanReadTransceiverLS	=(tCanReadTransceiverLS)	GetProcAddress(hInst, REFMUX_STR("CanReadTransceiverLS"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanCreateMsg			=(tCanCreateMsg)		    GetProcAddress(hInst, REFMUX_STR("CanCreateMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanReadMsg				=(tCanReadMsg)			    GetProcAddress(hInst, REFMUX_STR("CanReadMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanWriteMsg			=(tCanWriteMsg)		    	GetProcAddress(hInst, REFMUX_STR("CanWriteMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigPeriodic		=(tCanConfigPeriodic) 	    GetProcAddress(hInst, REFMUX_STR("CanConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanConfigPeriodicList	=(tCanConfigPeriodicList) 	GetProcAddress(hInst, REFMUX_STR("CanConfigPeriodicList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanSetNotification		=(tCanSetNotification)	    GetProcAddress(hInst, REFMUX_STR("CanSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanActivate			=(tCanActivate)			    GetProcAddress(hInst, REFMUX_STR("CanActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanIsBusActive			=(tCanIsBusActive)			GetProcAddress(hInst, REFMUX_STR("CanIsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanDeactivate			=(tCanDeactivate)		    GetProcAddress(hInst, REFMUX_STR("CanDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanSendMsg				=(tCanSendMsg)			    GetProcAddress(hInst, REFMUX_STR("CanSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanSendMsgList			=(tCanSendMsgList)		    GetProcAddress(hInst, REFMUX_STR("CanSendMsgList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanGetEvent			=(tCanGetEvent)			    GetProcAddress(hInst, REFMUX_STR("CanGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanBusOn				=(tCanBusOn)			    GetProcAddress(hInst, REFMUX_STR("CanBusOn"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanChangeBaudRate		=(tCanChangeBaudRate)	    GetProcAddress(hInst, REFMUX_STR("CanChangeBaudRate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanGetStat				=(tCanGetStat)			    GetProcAddress(hInst, REFMUX_STR("CanGetStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanGetBusState			=(tCanGetBusState)		    GetProcAddress(hInst, REFMUX_STR("CanGetBusState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanClearFifoRx			=(tCanClearFifoRx)		    GetProcAddress(hInst, REFMUX_STR("CanClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanGetFifoRxLevel  	=(tCanGetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("CanGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanReadByte			=(tCanReadByte)			    GetProcAddress(hInst, REFMUX_STR("CanReadByte"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((CanWriteByte			=(tCanWriteByte)		    GetProcAddress(hInst, REFMUX_STR("CanWriteByte"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((NwcRegister 		    =(tNwcRegister)	            GetProcAddress(hInst, REFMUX_STR("NwcRegister"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcGetChannelCount	    =(tNwcGetChannelCount)	    GetProcAddress(hInst, REFMUX_STR("NwcGetChannelCount"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelOpen 	    =(tNwcChannelOpen)	        GetProcAddress(hInst, REFMUX_STR("NwcChannelOpen"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelConfig       =(tNwcChannelConfig)        GetProcAddress(hInst, REFMUX_STR("NwcChannelConfig"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelParam 	    =(tNwcChannelParam)	        GetProcAddress(hInst, REFMUX_STR("NwcChannelParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelAddr  	    =(tNwcChannelAddr)	        GetProcAddress(hInst, REFMUX_STR("NwcChannelAddr"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelStart 	    =(tNwcChannelStart)         GetProcAddress(hInst, REFMUX_STR("NwcChannelStart"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelStop  	    =(tNwcChannelStop)	        GetProcAddress(hInst, REFMUX_STR("NwcChannelStop"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelClose 	    =(tNwcChannelClose)	        GetProcAddress(hInst, REFMUX_STR("NwcChannelClose"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcSetNotification		=(tNwcSetNotification)	    GetProcAddress(hInst, REFMUX_STR("NwcSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcActivate            =(tNwcActivate)             GetProcAddress(hInst, REFMUX_STR("NwcActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcIsBusActive         =(tNwcIsBusActive)          GetProcAddress(hInst, REFMUX_STR("NwcIsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcDeactivate          =(tNwcDeactivate)           GetProcAddress(hInst, REFMUX_STR("NwcDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelSendMsg      =(tNwcChannelSendMsg)       GetProcAddress(hInst, REFMUX_STR("NwcChannelSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelSendAsyncMsg =(tNwcChannelSendAsyncMsg)  GetProcAddress(hInst, REFMUX_STR("NwcChannelSendAsyncMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcGetEvent            =(tNwcGetEvent)             GetProcAddress(hInst, REFMUX_STR("NwcGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcGetIdent            =(tNwcGetIdent)             GetProcAddress(hInst, REFMUX_STR("NwcGetIdent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcGetFifoRxLevel  	=(tNwcGetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("NwcGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcConfigSpyMode     	=(tNwcConfigSpyMode)	    GetProcAddress(hInst, REFMUX_STR("NwcConfigSpyMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcGetChannelState    	=(tNwcGetChannelState)	    GetProcAddress(hInst, REFMUX_STR("NwcGetChannelState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwcChannelSetBytePadding    	=(tNwcChannelSetBytePadding)	    GetProcAddress(hInst, REFMUX_STR("NwcChannelSetBytePadding"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((J19ChannelOpen			=(tJ19ChannelOpen)			GetProcAddress(hInst, REFMUX_STR("J19ChannelOpen"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelAddr			=(tJ19ChannelAddr)			GetProcAddress(hInst, REFMUX_STR("J19ChannelAddr"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelParam		=(tJ19ChannelParam)			GetProcAddress(hInst, REFMUX_STR("J19ChannelParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelConfig		=(tJ19ChannelConfig)		GetProcAddress(hInst, REFMUX_STR("J19ChannelConfig"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelStart		=(tJ19ChannelStart)			GetProcAddress(hInst, REFMUX_STR("J19ChannelStart"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelStop			=(tJ19ChannelStop)			GetProcAddress(hInst, REFMUX_STR("J19ChannelStop"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelClose		=(tJ19ChannelClose)			GetProcAddress(hInst, REFMUX_STR("J19ChannelClose"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19Activate			=(tJ19Activate)				GetProcAddress(hInst, REFMUX_STR("J19Activate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ConfigBus			=(tJ19ConfigBus)			GetProcAddress(hInst, REFMUX_STR("J19ConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19Deactivate			=(tJ19Deactivate)			GetProcAddress(hInst, REFMUX_STR("J19Deactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelSendMsg		=(tJ19ChannelSendMsg)		GetProcAddress(hInst, REFMUX_STR("J19ChannelSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19ChannelSendNMEAFastPacket=(tJ19ChannelSendNMEAFastPacket)GetProcAddress(hInst, REFMUX_STR("J19ChannelSendNMEAFastPacket"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19SetNotification		=(tJ19SetNotification)		GetProcAddress(hInst, REFMUX_STR("J19SetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19GetEvent			=(tJ19GetEvent)				GetProcAddress(hInst, REFMUX_STR("J19GetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19GetFifoRxLevel  	=(tJ19GetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("J19GetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J19StoreNMEAFastPacket	=(tJ19StoreNMEAFastPacket)  GetProcAddress(hInst, REFMUX_STR("J19StoreNMEAFastPacket"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((LinConfigOper			=(tLinConfigOper)		    GetProcAddress(hInst, REFMUX_STR("LinConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigBus			=(tLinConfigBus)		    GetProcAddress(hInst, REFMUX_STR("LinConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigUart			=(tLinConfigUart)		    GetProcAddress(hInst, REFMUX_STR("LinConfigUart"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigParam			=(tLinConfigParam)		    GetProcAddress(hInst, REFMUX_STR("LinConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigStat			=(tLinConfigStat)		    GetProcAddress(hInst, REFMUX_STR("LinConfigStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinSetVersion			=(tLinSetVersion)		    GetProcAddress(hInst, REFMUX_STR("LinSetVersion"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinSetNotification		=(tLinSetNotification)	    GetProcAddress(hInst, REFMUX_STR("LinSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinActivate			=(tLinActivate)			    GetProcAddress(hInst, REFMUX_STR("LinActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinIsBusActive			=(tLinIsBusActive)	        GetProcAddress(hInst, REFMUX_STR("LinIsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigTransceiver	=(tLinConfigTransceiver)    GetProcAddress(hInst, REFMUX_STR("LinConfigTransceiver"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigPeriodic		=(tLinConfigPeriodic) 	    GetProcAddress(hInst, REFMUX_STR("LinConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinConfigPeriodicList	=(tLinConfigPeriodicList)   GetProcAddress(hInst, REFMUX_STR("LinConfigPeriodicList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinDeactivate			=(tLinDeactivate)		    GetProcAddress(hInst, REFMUX_STR("LinDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinSendMsg				=(tLinSendMsg)			    GetProcAddress(hInst, REFMUX_STR("LinSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinSendMsgList			=(tLinSendMsgList)		    GetProcAddress(hInst, REFMUX_STR("LinSendMsgList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinGetEvent			=(tLinGetEvent)			    GetProcAddress(hInst, REFMUX_STR("LinGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinGetStat				=(tLinGetStat)			    GetProcAddress(hInst, REFMUX_STR("LinGetStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinGetBusState			=(tLinGetBusState)		    GetProcAddress(hInst, REFMUX_STR("LinGetBusState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinSetSleepMode		=(tLinSetSleepMode)		    GetProcAddress(hInst, REFMUX_STR("LinSetSleepMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinSetWakeUpMode		=(tLinSetWakeUpMode)	    GetProcAddress(hInst, REFMUX_STR("LinSetWakeUpMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinClearFifoRx 		=(tLinClearFifoRx   )	    GetProcAddress(hInst, REFMUX_STR("LinClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinClearBufferIFR 		=(tLinClearBufferIFR   )	GetProcAddress(hInst, "LinClearBufferIFR")) == NULL) return(STATUS_ERR_OPENDLL);
	if ((LinGetFifoRxLevel 		=(tLinGetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("LinGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((NwlGetChannelCount	    =(tNwlGetChannelCount)		GetProcAddress(hInst, REFMUX_STR("NwlGetChannelCount"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelOpen 	    =(tNwlChannelOpen)	        GetProcAddress(hInst, REFMUX_STR("NwlChannelOpen"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelConfig       =(tNwlChannelConfig)        GetProcAddress(hInst, REFMUX_STR("NwlChannelConfig"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelParam 	    =(tNwlChannelParam)	        GetProcAddress(hInst, REFMUX_STR("NwlChannelParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelAddr  	    =(tNwlChannelAddr)	        GetProcAddress(hInst, REFMUX_STR("NwlChannelAddr"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelStart 	    =(tNwlChannelStart)         GetProcAddress(hInst, REFMUX_STR("NwlChannelStart"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelStop  	    =(tNwlChannelStop)	        GetProcAddress(hInst, REFMUX_STR("NwlChannelStop"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelClose 	    =(tNwlChannelClose)	        GetProcAddress(hInst, REFMUX_STR("NwlChannelClose"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlSetNotification	    =(tNwlSetNotification)		GetProcAddress(hInst, REFMUX_STR("NwlSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlActivate            =(tNwlActivate)             GetProcAddress(hInst, REFMUX_STR("NwlActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlIsBusActive         =(tNwlIsBusActive)          GetProcAddress(hInst, REFMUX_STR("NwlIsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlDeactivate          =(tNwlDeactivate)           GetProcAddress(hInst, REFMUX_STR("NwlDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelSendMsg      =(tNwlChannelSendMsg)       GetProcAddress(hInst, REFMUX_STR("NwlChannelSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlChannelReceiveMsg   =(tNwlChannelReceiveMsg)    GetProcAddress(hInst, REFMUX_STR("NwlChannelReceiveMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlGetEvent            =(tNwlGetEvent)             GetProcAddress(hInst, REFMUX_STR("NwlGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlGetFifoRxLevel      =(tNwlGetFifoRxLevel)		GetProcAddress(hInst, REFMUX_STR("NwlGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NwlGetChannelState     =(tNwlGetChannelState)		GetProcAddress(hInst, REFMUX_STR("NwlGetChannelState"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((VanConfigOper			=(tVanConfigOper)		    GetProcAddress(hInst, REFMUX_STR("VanConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanConfigBus			=(tVanConfigBus)		    GetProcAddress(hInst, REFMUX_STR("VanConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanConfigParam			=(tVanConfigParam)		    GetProcAddress(hInst, REFMUX_STR("VanConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanConfigStat			=(tVanConfigStat)		    GetProcAddress(hInst, REFMUX_STR("VanConfigStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanCreateMsg			=(tVanCreateMsg)		    GetProcAddress(hInst, REFMUX_STR("VanCreateMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanConfigPeriodic		=(tVanConfigPeriodic) 	    GetProcAddress(hInst, REFMUX_STR("VanConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanConfigPeriodicList	=(tVanConfigPeriodicList)   GetProcAddress(hInst, REFMUX_STR("VanConfigPeriodicList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanSetNotification		=(tVanSetNotification)	    GetProcAddress(hInst, REFMUX_STR("VanSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanActivate			=(tVanActivate)		        GetProcAddress(hInst, REFMUX_STR("VanActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanIsBusActive			=(tVanIsBusActive)	        GetProcAddress(hInst, REFMUX_STR("VanIsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanDeactivate			=(tVanDeactivate)		    GetProcAddress(hInst, REFMUX_STR("VanDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanSendMsg			    =(tVanSendMsg)		        GetProcAddress(hInst, REFMUX_STR("VanSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanSendMsgList		    =(tVanSendMsgList)		    GetProcAddress(hInst, REFMUX_STR("VanSendMsgList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanGetEvent			=(tVanGetEvent)		        GetProcAddress(hInst, REFMUX_STR("VanGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanGetStat			    =(tVanGetStat)		        GetProcAddress(hInst, REFMUX_STR("VanGetStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanGetBusState			=(tVanGetBusState)		    GetProcAddress(hInst, REFMUX_STR("VanGetBusState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanSetSleepMode		=(tVanSetSleepMode)		    GetProcAddress(hInst, REFMUX_STR("VanSetSleepMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanSetWakeUpMode		=(tVanSetWakeUpMode)	    GetProcAddress(hInst, REFMUX_STR("VanSetWakeUpMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanGetSleepMode		=(tVanGetSleepMode)		    GetProcAddress(hInst, REFMUX_STR("VanGetSleepMode"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanSetTIP			    =(tVanSetTIP)		        GetProcAddress(hInst, REFMUX_STR("VanSetTIP"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanGetSDCValue			=(tVanGetSDCValue)		    GetProcAddress(hInst, REFMUX_STR("VanGetSDCValue"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanClearFifoRx			=(tVanClearFifoRx)		    GetProcAddress(hInst, REFMUX_STR("VanClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanGetFifoRxLevel		=(tVanGetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("VanGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanReadByte			=(tVanReadByte)		        GetProcAddress(hInst, REFMUX_STR("VanReadByte"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((VanWriteByte			=(tVanWriteByte)		    GetProcAddress(hInst, REFMUX_STR("VanWriteByte"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((IsoConfigOper			=(tIsoConfigOper)		    GetProcAddress(hInst, REFMUX_STR("IsoConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoConfigBus			=(tIsoConfigBus)		    GetProcAddress(hInst, REFMUX_STR("IsoConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoConfigUart			=(tIsoConfigUart)		    GetProcAddress(hInst, REFMUX_STR("IsoConfigUart"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoConfigParam			=(tIsoConfigParam)		    GetProcAddress(hInst, REFMUX_STR("IsoConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoConfigStat			=(tIsoConfigStat)		    GetProcAddress(hInst, REFMUX_STR("IsoConfigStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoConfigPeriodic		=(tIsoConfigPeriodic)		GetProcAddress(hInst, REFMUX_STR("IsoConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((Iso14230ConfigPeriodic	=(tIso14230ConfigPeriodic) 	GetProcAddress(hInst, REFMUX_STR("Iso14230ConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoActivate			=(tIsoActivate)		        GetProcAddress(hInst, REFMUX_STR("IsoActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoIsBusActive			=(tIsoIsBusActive)	        GetProcAddress(hInst, REFMUX_STR("IsoIsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoDeactivate			=(tIsoDeactivate)		    GetProcAddress(hInst, REFMUX_STR("IsoDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoSetNotification	 	=(tIsoSetNotification)	    GetProcAddress(hInst, REFMUX_STR("IsoSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoSendMsg				=(tIsoSendMsg)				GetProcAddress(hInst, REFMUX_STR("IsoSendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((Iso14230SendMsg		=(tIso14230SendMsg)	        GetProcAddress(hInst, REFMUX_STR("Iso14230SendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoGetEvent			=(tIsoGetEvent)		        GetProcAddress(hInst, REFMUX_STR("IsoGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoWaitResponse		=(tIsoWaitResponse)	        GetProcAddress(hInst, REFMUX_STR("IsoWaitResponse"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoSendResp			=(tIsoSendResp)				GetProcAddress(hInst, REFMUX_STR("IsoSendResp"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoChangeBaudRate 		=(tIsoChangeBaudRate)	    GetProcAddress(hInst, REFMUX_STR("IsoChangeBaudRate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoGetStat				=(tIsoGetStat)			    GetProcAddress(hInst, REFMUX_STR("IsoGetStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoClearFifoRx			=(tIsoClearFifoRx)		    GetProcAddress(hInst, REFMUX_STR("IsoClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoGetFifoRxLevel		=(tIsoGetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("IsoGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoSetDataRxLevel		=(tIsoSetDataRxLevel)	    GetProcAddress(hInst, REFMUX_STR("IsoSetDataRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoReadByte			=(tIsoReadByte)		        GetProcAddress(hInst, REFMUX_STR("IsoReadByte"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IsoWriteByte			=(tIsoWriteByte)		    GetProcAddress(hInst, REFMUX_STR("IsoWriteByte"))) == NULL) return(STATUS_ERR_OPENDLL);

    if ((J18ConfigOper			=(tJ18ConfigOper)		    GetProcAddress(hInst, REFMUX_STR("J18ConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18ConfigBus			=(tJ18ConfigBus)		    GetProcAddress(hInst, REFMUX_STR("J18ConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18Activate			=(tJ18Activate)				GetProcAddress(hInst, REFMUX_STR("J18Activate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18IsBusActive			=(tJ18IsBusActive)			GetProcAddress(hInst, REFMUX_STR("J18IsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18Deactivate	   		=(tJ18Deactivate)		    GetProcAddress(hInst, REFMUX_STR("J18Deactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18SendMsg	  			=(tJ18SendMsg)   		    GetProcAddress(hInst, REFMUX_STR("J18SendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18GetEvent			=(tJ18GetEvent)				GetProcAddress(hInst, REFMUX_STR("J18GetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J18SetNotification  	=(tJ18SetNotification)		GetProcAddress(hInst, REFMUX_STR("J18SetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((J1587ConfigOper		=(tJ1587ConfigOper)		    GetProcAddress(hInst, REFMUX_STR("J1587ConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587ConfigBus			=(tJ1587ConfigBus)		    GetProcAddress(hInst, REFMUX_STR("J1587ConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587ConfigParam	 	=(tJ1587ConfigParam)	    GetProcAddress(hInst, REFMUX_STR("J1587ConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587ConfigStat 	 	=(tJ1587ConfigStat)	        GetProcAddress(hInst, REFMUX_STR("J1587ConfigStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587ConfigPeriodic	=(tJ1587ConfigPeriodic)     GetProcAddress(hInst, REFMUX_STR("J1587ConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587Activate			=(tJ1587Activate)		    GetProcAddress(hInst, REFMUX_STR("J1587Activate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587IsBusActive		=(tJ1587IsBusActive)	    GetProcAddress(hInst, REFMUX_STR("J1587IsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587Deactivate	   	=(tJ1587Deactivate)		    GetProcAddress(hInst, REFMUX_STR("J1587Deactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587SendMsg	  		=(tJ1587SendMsg)   		    GetProcAddress(hInst, REFMUX_STR("J1587SendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587GetEvent			=(tJ1587GetEvent)			GetProcAddress(hInst, REFMUX_STR("J1587GetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587GetBusState 		=(tJ1587GetBusState)	    GetProcAddress(hInst, REFMUX_STR("J1587GetBusState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587GetStat	 		=(tJ1587GetStat)  		    GetProcAddress(hInst, REFMUX_STR("J1587GetStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587SetNotification  	=(tJ1587SetNotification)    GetProcAddress(hInst, REFMUX_STR("J1587SetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587ClearFifoRx	    =(tJ1587ClearFifoRx)	    GetProcAddress(hInst, REFMUX_STR("J1587ClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((J1587GetFifoRxLevel  	=(tJ1587GetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("J1587GetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((NMEA0183ConfigOper		 =(tNMEA0183ConfigOper)		    GetProcAddress(hInst, REFMUX_STR("NMEA0183ConfigOper"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183ConfigBus		 =(tNMEA0183ConfigBus)		    GetProcAddress(hInst, REFMUX_STR("NMEA0183ConfigBus"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183ConfigUart		 =(tNMEA0183ConfigUart)		    GetProcAddress(hInst, REFMUX_STR("NMEA0183ConfigUart"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183ConfigParam	 =(tNMEA0183ConfigParam)	    GetProcAddress(hInst, REFMUX_STR("NMEA0183ConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183ConfigStat 	 =(tNMEA0183ConfigStat)	        GetProcAddress(hInst, REFMUX_STR("NMEA0183ConfigStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183ConfigPeriodic	 =(tNMEA0183ConfigPeriodic)     GetProcAddress(hInst, REFMUX_STR("NMEA0183ConfigPeriodic"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183Activate		 =(tNMEA0183Activate)		    GetProcAddress(hInst, REFMUX_STR("NMEA0183Activate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183IsBusActive	 =(tNMEA0183IsBusActive)	    GetProcAddress(hInst, REFMUX_STR("NMEA0183IsBusActive"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183Deactivate	   	 =(tNMEA0183Deactivate)		    GetProcAddress(hInst, REFMUX_STR("NMEA0183Deactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183SendMsg	  	 =(tNMEA0183SendMsg)   		    GetProcAddress(hInst, REFMUX_STR("NMEA0183SendMsg"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183GetEvent		 =(tNMEA0183GetEvent)			GetProcAddress(hInst, REFMUX_STR("NMEA0183GetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183GetBusState 	 =(tNMEA0183GetBusState)	    GetProcAddress(hInst, REFMUX_STR("NMEA0183GetBusState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183GetStat	 	 =(tNMEA0183GetStat)  		    GetProcAddress(hInst, REFMUX_STR("NMEA0183GetStat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183SetNotification =(tNMEA0183SetNotification)    GetProcAddress(hInst, REFMUX_STR("NMEA0183SetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183ClearFifoRx	 =(tNMEA0183ClearFifoRx)	    GetProcAddress(hInst, REFMUX_STR("NMEA0183ClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((NMEA0183GetFifoRxLevel  =(tNMEA0183GetFifoRxLevel)	    GetProcAddress(hInst, REFMUX_STR("NMEA0183GetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);

#ifdef _WIN32_WCE	// Under Windows CE
	if ((WINCEConfigParam      = (tWINCEConfigParam)		GetProcAddress(hInst, REFMUX_STR("WINCEConfigParam"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((WINCESetNotification  = (tWINCESetNotification)	GetProcAddress(hInst, REFMUX_STR("WINCESetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((WINCEActivate         = (tWINCEActivate)			GetProcAddress(hInst, REFMUX_STR("WINCEActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((WINCEDeactivate       = (tWINCEDeactivate)			GetProcAddress(hInst, REFMUX_STR("WINCEDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((WINCEGetPowerState    = (tWINCEGetPowerState)		GetProcAddress(hInst, REFMUX_STR("WINCEGetPowerState"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((WINCEGetEvent         = (tWINCEGetEvent)			GetProcAddress(hInst, REFMUX_STR("WINCEGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((WINCEIsDriverUnloaded = (tWINCEIsDriverUnloaded)	GetProcAddress(hInst, REFMUX_STR("WINCEIsDriverUnloaded"))) == NULL) return(STATUS_ERR_OPENDLL);
#endif	// _WIN32_WCE	

	if ((TimerSet				=(tTimerSet)			    GetProcAddress(hInst, REFMUX_STR("TimerSet"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((TimerSetNotification	=(tTimerSetNotification)    GetProcAddress(hInst, REFMUX_STR("TimerSetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((TimerRead				=(tTimerRead)			    GetProcAddress(hInst, REFMUX_STR("TimerRead"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((IOSetOutput			=(tIOSetOutput)			    GetProcAddress(hInst, REFMUX_STR("IOSetOutput"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IOGetInput				=(tIOGetInput)			    GetProcAddress(hInst, REFMUX_STR("IOGetInput"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IOGetCount				=(tIOGetCount)			    GetProcAddress(hInst, REFMUX_STR("IOGetCount"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IOConfigInput   	    =(tIOConfigInput) 		    GetProcAddress(hInst, REFMUX_STR("IOConfigInput"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((IOConfigOutput   	    =(tIOConfigOutput) 		    GetProcAddress(hInst, REFMUX_STR("IOConfigOutput"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((SPITransfer       	    =(tSPITransfer) 		    GetProcAddress(hInst, REFMUX_STR("SPITransfer"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((I2CTransfer       	    =(tI2CTransfer) 		    GetProcAddress(hInst, REFMUX_STR("I2CTransfer"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FctProprietary       	=(tFctProprietary) 		    GetProcAddress(hInst, REFMUX_STR("FctProprietary"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PryActivate      	 	=(tPryActivate) 		    GetProcAddress(hInst, REFMUX_STR("PryActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PryDeactivate     	 	=(tPryDeactivate) 		    GetProcAddress(hInst, REFMUX_STR("PryDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PryGetEvent      	 	=(tPryGetEvent) 		    GetProcAddress(hInst, REFMUX_STR("PryGetEvent"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PrySetNotification    	=(tPrySetNotification) 	    GetProcAddress(hInst, REFMUX_STR("PrySetNotification"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PryClearFifoRx       	=(tPryClearFifoRx) 		    GetProcAddress(hInst, REFMUX_STR("PryClearFifoRx"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PryGetFifoRxLevel     	=(tPryGetFifoRxLevel)  	    GetProcAddress(hInst, REFMUX_STR("PryGetFifoRxLevel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((ANATransfer       	    =(tANATransfer) 		    GetProcAddress(hInst, REFMUX_STR("ANATransfer"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((ANAGetInput       	    =(tANAGetInput) 		    GetProcAddress(hInst, REFMUX_STR("ANAGetInput"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PWMInputActivate  	    =(tPWMInputActivate)        GetProcAddress(hInst, REFMUX_STR("PWMInputActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PWMInputDeactivate	    =(tPWMInputDeactivate)      GetProcAddress(hInst, REFMUX_STR("PWMInputDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PWMOutputConfig	    =(tPWMOutputConfig)         GetProcAddress(hInst, REFMUX_STR("PWMOutputConfig"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PWMOutputActivate	    =(tPWMOutputActivate)       GetProcAddress(hInst, REFMUX_STR("PWMOutputActivate"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((PWMOutputDeactivate    =(tPWMOutputDeactivate)     GetProcAddress(hInst, REFMUX_STR("PWMOutputDeactivate"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((FlashFileOpen			=(tFlashFileOpen)			GetProcAddress(hInst, REFMUX_STR("FlashFileOpen"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileClose			=(tFlashFileClose)			GetProcAddress(hInst, REFMUX_STR("FlashFileClose"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileRead			=(tFlashFileRead)			GetProcAddress(hInst, REFMUX_STR("FlashFileRead"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileWrite	   		=(tFlashFileWrite)			GetProcAddress(hInst, REFMUX_STR("FlashFileWrite"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileSeek			=(tFlashFileSeek)			GetProcAddress(hInst, REFMUX_STR("FlashFileSeek"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileTell			=(tFlashFileTell)			GetProcAddress(hInst, REFMUX_STR("FlashFileTell"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileGetSize		=(tFlashFileGetSize)		GetProcAddress(hInst, REFMUX_STR("FlashFileGetSize"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashGetInformations	=(tFlashGetInformations)	GetProcAddress(hInst, REFMUX_STR("FlashGetInformations"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFindFirstFile		=(tFlashFindFirstFile)		GetProcAddress(hInst, REFMUX_STR("FlashFindFirstFile"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFindNextFile		=(tFlashFindNextFile)		GetProcAddress(hInst, REFMUX_STR("FlashFindNextFile"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileDelete		=(tFlashFileDelete)			GetProcAddress(hInst, REFMUX_STR("FlashFileDelete"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileDownload		=(tFlashFileDownload)	   	GetProcAddress(hInst, REFMUX_STR("FlashFileDownload"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileRepair		=(tFlashFileRepair)		   	GetProcAddress(hInst, REFMUX_STR("FlashFileRepair"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFormat			=(tFlashFormat)		 	  	GetProcAddress(hInst, REFMUX_STR("FlashFormat"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFileCountSession	=(tFlashFileCountSession)	GetProcAddress(hInst, REFMUX_STR("FlashFileCountSession"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFindFirstFileInFilter	=(tFlashFindFirstFileInFilter)	GetProcAddress(hInst, REFMUX_STR("FlashFindFirstFileInFilter"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((FlashFindNextFileInFilter	=(tFlashFindNextFileInFilter)	GetProcAddress(hInst, REFMUX_STR("FlashFindNextFileInFilter"))) == NULL) return(STATUS_ERR_OPENDLL);

	if ((USBLIB_GetDeviceList 	=(tUSBLIB_GetDeviceList)   	GetProcAddress(hInst, REFMUX_STR("USBLIB_GetDeviceList"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_Open 			=(tUSBLIB_Open)   			GetProcAddress(hInst, REFMUX_STR("USBLIB_Open"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_Close 			=(tUSBLIB_Close)   			GetProcAddress(hInst, REFMUX_STR("USBLIB_Close"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_GetPipesInfos	=(tUSBLIB_GetPipesInfos)	GetProcAddress(hInst, REFMUX_STR("USBLIB_GetPipesInfos"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_Send			=(tUSBLIB_Send)				GetProcAddress(hInst, REFMUX_STR("USBLIB_Send"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_WritePipe00		=(tUSBLIB_WritePipe00)		GetProcAddress(hInst, REFMUX_STR("USBLIB_WritePipe00"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_ReadPipe00		=(tUSBLIB_ReadPipe00)		GetProcAddress(hInst, REFMUX_STR("USBLIB_ReadPipe00"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_Read			=(tUSBLIB_Read)				GetProcAddress(hInst, REFMUX_STR("USBLIB_Read"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_ReadCancel		=(tUSBLIB_ReadCancel)		GetProcAddress(hInst, REFMUX_STR("USBLIB_ReadCancel"))) == NULL) return(STATUS_ERR_OPENDLL);
	if ((USBLIB_GetEndpointNumber	=(tUSBLIB_GetEndpointNumber)	GetProcAddress(hInst, REFMUX_STR("USBLIB_GetEndpointNumber"))) == NULL) return(STATUS_ERR_OPENDLL);
    
	return(STATUS_OK);
}
tMuxStatus MuxFreeDLL(void)
{
	if (hInst != NULL) FreeLibrary(hInst);
    hInst=NULL;
    return(STATUS_OK);
}

tMuxStatus MuxLoadDLL(void)
{
	if ((hInst=LoadLibrary(_MUXDLLBIN_STR)) == NULL)				// Specific DLL (./bin)
	{
		if ((hInst=LoadLibrary(_MUXDLLCUR_STR)) == NULL)			// Specific DLL (./)
		{
			if ((hInst=LoadLibrary(REFMUX_STR(_MUXDLL_STR))) == NULL)					// Generic DLL (Windows/system)
			{
				return(STATUS_ERR_FILEDLL);
			}
		}
	}
	if (MuxInitAddr() != STATUS_OK)
	{
		MuxFreeDLL();
		return(STATUS_ERR_OPENDLL);
	}
	return STATUS_OK;
}

// Load the muxdll using server/client connection allowing to use several application with the same device
tMuxStatus MuxLoadDLLClient(void)
{
	void *	hMutex;

	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, _MUTEX_NAME);
    if(hMutex==NULL) return(STATUS_ERR_SERVERNOTLOADED);
    CloseHandle(hMutex);

	if ((hInst=LoadLibrary(_AEBRDGBIN_STR)) == NULL)				// Specific DLL
    {
		if ((hInst=LoadLibrary(_AEBRDGB_STR)) == NULL)					// Generic DLL (Windows/system)
        {
            return(STATUS_ERR_FILEDLL);
        }
    }
    if (MuxInitAddr() != STATUS_OK)
    {
        MuxFreeDLL();
        return(STATUS_ERR_OPENDLL);
    }
	return STATUS_OK;
}

#endif

#endif


#ifdef __BORLANDC__
#pragma option pop                  // Return as before
#endif
#pragma pack(pop)                   // Return as before


#endif                              // End of _REFMUX_H_


