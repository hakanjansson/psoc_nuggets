#include <project.h>
#include <hkj_library.h>

CYBLE_GAP_BD_ADDR_T	connectCentralDevice = {{0x56, 0x34, 0x12, 0x50, 0xa0, 0x00}, 0};

CYBLE_CONN_HANDLE_T connHandle = {0, 0};
uint8 gatt_disconnect_flag = 0;

CYBLE_GATTC_WRITE_REQ_T writeReqParam;
CYBLE_GATT_VALUE_T writeValue;
uint8 counter = 0;
uint8 last_written_counter = 0;

CYBLE_GATTC_READ_MULT_REQ_T readMultiReqParam;
uint16 handles[] = {0x0c, 0x0e, 0x10};

void GenericAppEventHandler(uint32 event, void *eventParam)
{
    hkj_ble_events_log_add(event, eventParam);
    switch(event)
	{
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if (CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
                  CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_CUSTOM);
            break;

        case CYBLE_EVT_TIMEOUT:
            break;                

        case CYBLE_EVT_GATT_CONNECT_IND:
            connHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
            break;
    		
    	case CYBLE_EVT_GATT_DISCONNECT_IND:
    		connHandle = (CYBLE_CONN_HANDLE_T){0, 0};
            gatt_disconnect_flag = 1;
    		break;

        case CYBLE_EVT_GATTC_READ_MULTI_RSP:
        case CYBLE_EVT_GATTC_READ_RSP:
            {
                CYBLE_GATTC_READ_RSP_PARAM_T *rsp = (CYBLE_GATTC_READ_RSP_PARAM_T *)eventParam;
                /* Data integrity check */
                if ( (last_written_counter > 0) && \
                        (   rsp->value.val[2] != last_written_counter || \
                            rsp->value.val[1] != last_written_counter || \
                            rsp->value.val[0] != (uint8)(last_written_counter - 15)) )
                    printf("ERROR: Characteristic value mismatch.\r\n");
            }
            break;
	}
}

int main()
{
    writeValue.val = (uint8 *)&counter;
    writeValue.len = sizeof(counter);
    writeValue.actualLen = sizeof(counter);
    writeReqParam.value = writeValue;        
    writeReqParam.attrHandle = 0x10;
    
    readMultiReqParam.handleList = handles;
    readMultiReqParam.actualCount = sizeof(handles) / sizeof(handles[0]);
    readMultiReqParam.listCount = sizeof(handles) / sizeof(handles[0]);
    
    UART_Start();
    hkj_debug_init();
    hkj_ble_events_log_init();
	CyGlobalIntEnable;
    debug_print("\r\nINFO: Starting GATT Client on GAP Peripheral\r\n");

    /* Configure advertising parameters for directed advertising */
    memcpy(cyBle_discoveryModeInfo.advParam->directAddr, connectCentralDevice.bdAddr, CYBLE_GAP_BD_ADDR_SIZE);
    cyBle_discoveryModeInfo.advParam->directAddrType = connectCentralDevice.type;   
    cyBle_discoveryModeInfo.advParam->advType = CYBLE_GAPP_CONNECTABLE_HIGH_DC_DIRECTED_ADV;

    CyBle_Start(GenericAppEventHandler);
    CyBle_ProcessEvents();
    
    for(;;)
    {
        debug_print("INFO: Start advertising\r\n");
        hkj_ble_events_log_clear();
        CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_CUSTOM);
        while (connHandle.bdHandle == 0) /* Wait for connection to GATT server */
            CyBle_ProcessEvents();

        debug_print("INFO: Connected to GATT Server\r\n");
        P1_0_Write(1);
        last_written_counter = counter;
        debug_print("INFO: Read multiple characteristics\r\n");
        CyBle_GattcReadMultipleCharacteristicValues(connHandle, &readMultiReqParam);
        counter++;
        debug_print("INFO: Write command x2\r\n");
        writeReqParam.attrHandle = 0x0e;
        CyBle_GattcWriteWithoutResponse(connHandle, &writeReqParam);
        writeReqParam.attrHandle = 0x10;
        CyBle_GattcWriteWithoutResponse(connHandle, &writeReqParam);

        gatt_disconnect_flag = 0;
        while (!gatt_disconnect_flag) /* Wait for disconnection from GATT server */
			CyBle_ProcessEvents();

        P1_0_Write(0);
        debug_print("INFO: Disconnected from GATT Server\r\n");
       
        hkj_ble_events_log_debug_print();
	}
}
