#include <BLE_Stack.h>

typedef struct
{
    const CYBLE_EVENT_T event;
    const char *event_name;
} event_pair;

const event_pair lookup_table[] = 
{		
    { CYBLE_EVT_HOST_INVALID, "CYBLE_EVT_HOST_INVALID" },
    { CYBLE_EVT_STACK_ON, "CYBLE_EVT_STACK_ON" },
    { CYBLE_EVT_TIMEOUT, "CYBLE_EVT_TIMEOUT" },
    { CYBLE_EVT_HARDWARE_ERROR, "CYBLE_EVT_HARDWARE_ERROR" },
    { CYBLE_EVT_HCI_STATUS, "CYBLE_EVT_HCI_STATUS" },
    { CYBLE_EVT_STACK_BUSY_STATUS, "CYBLE_EVT_STACK_BUSY_STATUS" },
//	{ CYBLE_EVT_MEMORY_REQUEST, "CYBLE_EVT_MEMORY_REQUEST" },
    { CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT, "CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT" },
    { CYBLE_EVT_GAP_AUTH_REQ, "CYBLE_EVT_GAP_AUTH_REQ" },
    { CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST, "CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST" },
    { CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST, "CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST" },
    { CYBLE_EVT_GAP_AUTH_COMPLETE, "CYBLE_EVT_GAP_AUTH_COMPLETE" },
    { CYBLE_EVT_GAP_AUTH_FAILED, "CYBLE_EVT_GAP_AUTH_FAILED" },
    { CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP, "CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP" },
    { CYBLE_EVT_GAP_DEVICE_CONNECTED, "CYBLE_EVT_GAP_DEVICE_CONNECTED" },
    { CYBLE_EVT_GAP_DEVICE_DISCONNECTED, "CYBLE_EVT_GAP_DEVICE_DISCONNECTED" },
    { CYBLE_EVT_GAP_ENCRYPT_CHANGE, "CYBLE_EVT_GAP_ENCRYPT_CHANGE" },
    { CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE, "CYBLE_EVT_GAP_CONNECTION_UPDATE_COMPLETE" },
    { CYBLE_EVT_GAPC_SCAN_START_STOP, "CYBLE_EVT_GAPC_SCAN_START_STOP" },
    { CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT, "CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT" },
//    { CYBLE_EVT_GAP_NUMERIC_COMPARISON_REQUEST, "CYBLE_EVT_GAP_NUMERIC_COMPARISON_REQUEST" },
//    { CYBLE_EVT_GAP_KEYPRESS_NOTIFICATION, "CYBLE_EVT_GAP_KEYPRESS_NOTIFICATION" },
//    { CYBLE_EVT_GAP_OOB_GENERATED_NOTIFICATION, "CYBLE_EVT_GAP_OOB_GENERATED_NOTIFICATION" },
//    { CYBLE_EVT_GAP_DATA_LENGTH_CHANGE, "CYBLE_EVT_GAP_DATA_LENGTH_CHANGE" },
//    { CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE, "CYBLE_EVT_GAP_ENHANCE_CONN_COMPLETE" },
//    { CYBLE_EVT_GAPC_DIRECT_ADV_REPORT, "CYBLE_EVT_GAPC_DIRECT_ADV_REPORT" },
//    { CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO, "CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO" },
    { CYBLE_EVT_GATTC_ERROR_RSP, "CYBLE_EVT_GATTC_ERROR_RSP" },
    { CYBLE_EVT_GATT_CONNECT_IND, "CYBLE_EVT_GATT_CONNECT_IND" },
    { CYBLE_EVT_GATT_DISCONNECT_IND, "CYBLE_EVT_GATT_DISCONNECT_IND" },
    { CYBLE_EVT_GATTS_XCNHG_MTU_REQ, "CYBLE_EVT_GATTS_XCNHG_MTU_REQ" },
    { CYBLE_EVT_GATTC_XCHNG_MTU_RSP, "CYBLE_EVT_GATTC_XCHNG_MTU_RSP" },
    { CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP, "CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP" },
    { CYBLE_EVT_GATTC_READ_BY_TYPE_RSP, "CYBLE_EVT_GATTC_READ_BY_TYPE_RSP" },
    { CYBLE_EVT_GATTC_FIND_INFO_RSP, "CYBLE_EVT_GATTC_FIND_INFO_RSP" },
    { CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP, "CYBLE_EVT_GATTC_FIND_BY_TYPE_VALUE_RSP" },
    { CYBLE_EVT_GATTC_READ_RSP, "CYBLE_EVT_GATTC_READ_RSP" },
    { CYBLE_EVT_GATTC_READ_BLOB_RSP, "CYBLE_EVT_GATTC_READ_BLOB_RSP" },
    { CYBLE_EVT_GATTC_READ_MULTI_RSP, "CYBLE_EVT_GATTC_READ_MULTI_RSP" },
    { CYBLE_EVT_GATTS_WRITE_REQ, "CYBLE_EVT_GATTS_WRITE_REQ" },
    { CYBLE_EVT_GATTC_WRITE_RSP, "CYBLE_EVT_GATTC_WRITE_RSP" },
    { CYBLE_EVT_GATTS_WRITE_CMD_REQ, "CYBLE_EVT_GATTS_WRITE_CMD_REQ" },
    { CYBLE_EVT_GATTS_PREP_WRITE_REQ, "CYBLE_EVT_GATTS_PREP_WRITE_REQ" },
    { CYBLE_EVT_GATTS_EXEC_WRITE_REQ, "CYBLE_EVT_GATTS_EXEC_WRITE_REQ" },
    { CYBLE_EVT_GATTC_EXEC_WRITE_RSP, "CYBLE_EVT_GATTC_EXEC_WRITE_RSP" },
    { CYBLE_EVT_GATTC_HANDLE_VALUE_NTF, "CYBLE_EVT_GATTC_HANDLE_VALUE_NTF" },
    { CYBLE_EVT_GATTC_HANDLE_VALUE_IND, "CYBLE_EVT_GATTC_HANDLE_VALUE_IND" },
    { CYBLE_EVT_GATTS_HANDLE_VALUE_CNF, "CYBLE_EVT_GATTS_HANDLE_VALUE_CNF" },
    { CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ, "CYBLE_EVT_GATTS_DATA_SIGNED_CMD_REQ" },
    { CYBLE_EVT_GATTC_STOP_CMD_COMPLETE, "CYBLE_EVT_GATTC_STOP_CMD_COMPLETE" },
    { CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ, "CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ" },
//	{ CYBLE_EVT_GATTC_LONG_PROCEDURE_END, "CYBLE_EVT_GATTC_LONG_PROCEDURE_END" },
    { CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ, "CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ" },
    { CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP, "CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP" },
    { CYBLE_EVT_L2CAP_COMMAND_REJ, "CYBLE_EVT_L2CAP_COMMAND_REJ" },
    { CYBLE_EVT_L2CAP_CBFC_CONN_IND, "CYBLE_EVT_L2CAP_CBFC_CONN_IND" },
    { CYBLE_EVT_L2CAP_CBFC_CONN_CNF, "CYBLE_EVT_L2CAP_CBFC_CONN_CNF" },
    { CYBLE_EVT_L2CAP_CBFC_DISCONN_IND, "CYBLE_EVT_L2CAP_CBFC_DISCONN_IND" },
    { CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF, "CYBLE_EVT_L2CAP_CBFC_DISCONN_CNF" },
    { CYBLE_EVT_L2CAP_CBFC_DATA_READ, "CYBLE_EVT_L2CAP_CBFC_DATA_READ" },
    { CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND, "CYBLE_EVT_L2CAP_CBFC_RX_CREDIT_IND" },
    { CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND, "CYBLE_EVT_L2CAP_CBFC_TX_CREDIT_IND" },
    { CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND, "CYBLE_EVT_L2CAP_CBFC_DATA_WRITE_IND" },
#ifdef CYBLE_HOST_QUALIFICATION
	CYBLE_EVT_QUAL_SMP_PAIRING_REQ_RSP = 0x80u,
	CYBLE_EVT_QUAL_SMP_LOCAL_PUBLIC_KEY,
	CYBLE_EVT_QUAL_SMP_PAIRING_FAILED_CMD,
#endif
    { CYBLE_EVT_PENDING_FLASH_WRITE, "CYBLE_EVT_PENDING_FLASH_WRITE" },
    { CYBLE_EVT_LE_PING_AUTH_TIMEOUT, "CYBLE_EVT_LE_PING_AUTH_TIMEOUT" },
    { CYBLE_EVT_MAX, "CYBLE_EVT_MAX" }
};

#define NUM_PAIRS (sizeof(lookup_table) / sizeof((lookup_table)[0]))

const char *hkj_GetEventName(CYBLE_EVENT_T event)
{
    unsigned int i;
    for (i=0; i < NUM_PAIRS; i++)
        if (lookup_table[i].event == event)
            return lookup_table[i].event_name;
            
    return 0;
}	
		