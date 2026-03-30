/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M9_Front_Communication.h"


void Front_Communication(void);
void front_rx_communication(void);
void convert_received_data_asc_to_dec(void);
U8 calculate_checksum(void);
void apply_receive_data(U8 *mu8_rx_data);
void front_tx_communication(void);
void make_front_tx_data(void);
void convert_final_asc_data(U8 *mu8_tx_data, U8 mu8_length);
void Uart_ISR2_Front_Panel_Rx(void);
void Uart_ISR2_Front_Panel_Tx ( void );
void front_transmit_error_check(void);
void front_transmit_start(void);









/*..hui [18-8-9오후 1:10:24] 아스키로 받은 데이터 버퍼..*/
U8 gu8_front_rx_buffer_temp[FRONT_RX_BUFFER_SIZE];
/*..hui [18-8-9오후 1:10:38] 아스키를 10진수로 변환한 최종 데이터 버퍼..*/
U8 gu8_front_rx_buffer[FRONT_RX_BUFFER_SIZE];

U8 gu8_front_tx_buffer_temp[FRONT_TX_BUFFER_SIZE];

U8 gu8_front_tx_buffer[FRONT_TX_BUFFER_SIZE];
U8 gu8_front_rx_receive_cnt;
U8 gu8_front_tx_count;

BIT F_Front_Rx_Complete;
BIT F_Front_Tx_Request;

U16 gu16_front_rcv_select_key_data;
U8 gu8_front_rcv_extract_key_data;

U8 gu8_front_rcv_service_input_data;

U8 gu8_front_tx_retry_cnt;

U8 asdfasdf[9];
I8 fedfwefew[9];


U8 gu8_cs_error_cnt;
U8 gu8_busy_error_cnt;
U8 gu8_comm_error_cnt;
U8 gu8_front_comm_error_timer;

U8 gu8_front_version;

U8 gu8_front_uv_ice_faucet_current;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Front_Communication(void)
{
    front_rx_communication();
    front_tx_communication();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_rx_communication(void)
{
    U16 mu16_cal_crc = 0;
    U8 mu8_crc_high = 0;
    U8 mu8_crc_low = 0;

    if(F_Front_Rx_Complete == SET)
    {
        /*convert_received_data_asc_to_dec();*/

        mu16_cal_crc = (U16)Rx_CRC_CCITT(gu8_front_rx_buffer, FRONT_CRC_CALC_RANGE);

        mu8_crc_high = (U8)HighByte(mu16_cal_crc);
        mu8_crc_low = (U8)LowByte(mu16_cal_crc);

        if(gu8_front_rx_buffer[FRONT_CRC_HIGH_ROCATION] == mu8_crc_high
           && gu8_front_rx_buffer[FRONT_CRC_LOW_ROCATION] == mu8_crc_low)
        {
            switch( gu8_front_rx_buffer[FRONT_COMMAND_ROCATION] )
            {
                case REQUEST_COMMAND_FRONT_COMM:

                    //

                    break;

                case RESPONSE_COMMAND_FRONT_COMM:

                    F_Front_Tx_Request = SET;
                    apply_receive_data(gu8_front_rx_buffer);

                    break;

                default :

                    break;
            }
        }
        else
        {
            gu8_cs_error_cnt++;
        }

        F_Front_Rx_Complete = CLEAR;
        gu8_front_comm_error_timer = 0;
    }
    else
    {
        gu8_front_comm_error_timer++;

        /*..hui [19-12-13오후 7:01:15] 5초 연속 통신 안될경우 키 입력 초기화..*/
        if(gu8_front_comm_error_timer >= 100)
        {
            gu8_front_comm_error_timer = 100;
            /*..hui [19-7-17오후 7:51:24] 통신 에러 발생 시 키 입력 초기화..*/
            gu8_Key_Water_Extract = 0;
            gu8_Key_Ice_Extract = 0;
            gu16_Key_Input = 0;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_received_data_asc_to_dec(void)
{
#if 0
    gu8_front_rx_buffer[0] = gu8_front_rx_buffer_temp[0];
    gu8_front_rx_buffer[1] = gu8_front_rx_buffer_temp[1];
    gu8_front_rx_buffer[2] = gu8_front_rx_buffer_temp[2];

    gu8_front_rx_buffer[3] = AscToHex(gu8_front_rx_buffer_temp[3], gu8_front_rx_buffer_temp[4]);
    gu8_front_rx_buffer[4] = AscToHex(gu8_front_rx_buffer_temp[5], gu8_front_rx_buffer_temp[6]);
    gu8_front_rx_buffer[5] = AscToHex(gu8_front_rx_buffer_temp[7], gu8_front_rx_buffer_temp[8]);
    gu8_front_rx_buffer[6] = AscToHex(gu8_front_rx_buffer_temp[9], gu8_front_rx_buffer_temp[10]);

    gu8_front_rx_buffer[7] = gu8_front_rx_buffer_temp[11];
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 calculate_checksum(void)
{
    U8 mu8_temp = 0;
    U8 mu8_cnt = 0;
    U8 mu8_cal_cs = 0;

    for(mu8_temp = 0; mu8_temp < 6; mu8_temp++ )
    {
        mu8_cal_cs += gu8_front_rx_buffer[mu8_temp];
    }

    return mu8_cal_cs;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_receive_data(U8 *mu8_rx_data)
{
    gu16_front_rcv_select_key_data = (U16)((mu8_rx_data[3] * 256) + mu8_rx_data[4]);

    gu8_Key_Water_Extract = (U8)((gu16_front_rcv_select_key_data >> 3) & 0x01);
    gu8_Key_Ice_Extract  = (U8)((gu16_front_rcv_select_key_data >> 2) & 0x01);
    gu16_Key_Input = (U16)(gu16_front_rcv_select_key_data & 0xFFF0);

    gu8_front_version = mu8_rx_data[5];
	
	gu8_front_uv_ice_faucet_current = mu8_rx_data[6];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_tx_communication(void)
{
    front_transmit_error_check();
    front_transmit_start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_transmit_start(void)
{
    U8 mu8_busy_chk = 0;

    if(1)
    {
        if(F_Front_Tx_Request == SET)
        {
            make_front_tx_data();
            TXD2 = gu8_front_tx_buffer[0];
            gu8_front_tx_count = 1;
        }
        else{}
    }
    else
    {
        gu8_busy_error_cnt++;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_transmit_error_check(void)
{
    if(F_Front_Tx_Request == CLEAR)
    {
        gu8_front_tx_retry_cnt++;

        if(gu8_front_tx_retry_cnt >= TX_RETRY_COUNT)
        {
            gu8_comm_error_cnt++;
            gu8_front_tx_retry_cnt = 0;
            F_Front_Tx_Request = SET;
            R_UART2_Start();
        }
        else{}
    }
    else
    {
        gu8_front_tx_retry_cnt = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_front_tx_data(void)
{
    U8 mu8_temp = 0;
    U8 mu8_cnt = 0;
    U16 mu16_cal_crc = 0;
    U8 mu8_crc_high = 0;
    U8 mu8_crc_low = 0;
    U8 mu8_buffer[FRONT_TX_BUFFER_SIZE];

    gu8_front_tx_buffer[0] = STX_FRONT_COMM;
    gu8_front_tx_buffer[1] = REQUEST_COMMAND_FRONT_COMM;
    gu8_front_tx_buffer[2] = MAIN_TO_FRONT_DATA_TOTAL_LENGTH;

    gu8_front_tx_buffer[3] = gu8_front_fnd_thousand;
    gu8_front_tx_buffer[4] = gu8_front_fnd_hundred;
    gu8_front_tx_buffer[5] = gu8_front_fnd_ten;
    gu8_front_tx_buffer[6] = gu8_front_fnd_one;
    gu8_front_tx_buffer[7] = gu8_front_extract_uv_led;
    gu8_front_tx_buffer[8] = gu8_front_etc_led;
    gu8_front_tx_buffer[9] = gu8_front_select_led;
    gu8_front_tx_buffer[10] = gu8_front_temp_led;
    gu8_front_tx_buffer[11] = gu8_front_setting_led;
    gu8_front_tx_buffer[12] = gu8_time_wifi_setting_led;

    gu8_front_tx_buffer[13] = gu8_dimming_set_ice_first;
    gu8_front_tx_buffer[14] = gu8_dimming_hot_ambient;
    gu8_front_tx_buffer[15] = gu8_dimming_cold_amount;
    gu8_front_tx_buffer[16] = gu8_dimming_extract;
    gu8_front_tx_buffer[17] = gu8_dimming_setting_etc;
    gu8_front_tx_buffer[18] = gu8_dimming_cont_pot;
    gu8_front_tx_buffer[19] = gu8_dimming_2cups_1cup;

    gu8_front_tx_buffer[20] = gu8_dimming_half_cups_colon;
    gu8_front_tx_buffer[21] = gu8_dimming_Am_Pm;
    //gu8_front_tx_buffer[21] = gu8_time_setting_led;
    gu8_front_tx_buffer[22] = u8ETCDimmingSel_L;
    gu8_front_tx_buffer[23] = u8ETCDimmingSel_H;
    /*gu8_front_tx_buffer[21] = gu8_etc_1;*/
    gu8_front_tx_buffer[24] = gu8_dimming_temp;
    gu8_front_tx_buffer[25] = f_ice_extraction_out;
    gu8_front_tx_buffer[26] = gu8_dimming_Wifi;
	
	/*.. dimming 추가하면서 tx_buffer 추가..*/
    gu8_front_tx_buffer[27] = gu8_dimming_fnd_2_1;
    gu8_front_tx_buffer[28] = gu8_dimming_fnd_4_3;
	gu8_front_tx_buffer[29] = gu8_Dimming_seg;
	gu8_front_tx_buffer[30] = gu8_fota_start;
	
	/*.. Fota 진행하면서 OTA표시용 buffer추가 ..*/

    mu16_cal_crc = Rx_CRC_CCITT(gu8_front_tx_buffer, MAIN_CRC_CALC_RANGE);

    mu8_crc_high = (U8)HighByte(mu16_cal_crc);
    mu8_crc_low = (U8)LowByte(mu16_cal_crc);

    gu8_front_tx_buffer[31] = mu8_crc_high;
    gu8_front_tx_buffer[32] = mu8_crc_low;

    gu8_front_tx_buffer[33] = ETX_FRONT_COMM;

    /*convert_final_asc_data( gu8_front_tx_buffer_temp, 13 );*/
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_final_asc_data(U8 *mu8_tx_data, U8 mu8_length)
{
#if 0
    gu8_front_tx_buffer[0] = mu8_tx_data[0];
    gu8_front_tx_buffer[1] = mu8_tx_data[1];
    gu8_front_tx_buffer[2] = mu8_tx_data[2];

    gu8_front_tx_buffer[3] = (U8)( (HexToAsc(mu8_tx_data[3]) >> 8) & 0xFF );
    gu8_front_tx_buffer[4] = (U8)( (HexToAsc(mu8_tx_data[3])) & 0xFF );

    gu8_front_tx_buffer[5] = (U8)( (HexToAsc(mu8_tx_data[4]) >> 8) & 0xFF );
    gu8_front_tx_buffer[6] = (U8)( (HexToAsc(mu8_tx_data[4])) & 0xFF );

    gu8_front_tx_buffer[7] = (U8)( (HexToAsc(mu8_tx_data[5]) >> 8) & 0xFF );
    gu8_front_tx_buffer[8] = (U8)( (HexToAsc(mu8_tx_data[5])) & 0xFF );

    gu8_front_tx_buffer[9] = (U8)( (HexToAsc(mu8_tx_data[6]) >> 8) & 0xFF );
    gu8_front_tx_buffer[10] = (U8)( (HexToAsc(mu8_tx_data[6])) & 0xFF );

    gu8_front_tx_buffer[11] = (U8)( (HexToAsc(mu8_tx_data[7]) >> 8) & 0xFF );
    gu8_front_tx_buffer[12] = (U8)( (HexToAsc(mu8_tx_data[7])) & 0xFF );

    gu8_front_tx_buffer[13] = (U8)( (HexToAsc(mu8_tx_data[8]) >> 8) & 0xFF );
    gu8_front_tx_buffer[14] = (U8)( (HexToAsc(mu8_tx_data[8])) & 0xFF );

    gu8_front_tx_buffer[15] = (U8)( (HexToAsc(mu8_tx_data[9]) >> 8) & 0xFF );
    gu8_front_tx_buffer[16] = (U8)( (HexToAsc(mu8_tx_data[9])) & 0xFF );

    gu8_front_tx_buffer[17] = (U8)( (HexToAsc(mu8_tx_data[10]) >> 8) & 0xFF );
    gu8_front_tx_buffer[18] = (U8)( (HexToAsc(mu8_tx_data[10])) & 0xFF );

    gu8_front_tx_buffer[19] = (U8)( (HexToAsc(mu8_tx_data[11]) >> 8) & 0xFF );
    gu8_front_tx_buffer[20] = (U8)( (HexToAsc(mu8_tx_data[11])) & 0xFF );

    gu8_front_tx_buffer[21] = mu8_tx_data[12];
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR2_Front_Panel_Rx(void)
{
    U8 mu8_rx_buffer = RXD2;
    U8 mu8_packet_length = 0;

    if( (F_Front_Rx_Complete == CLEAR) && (F_Front_Tx_Request == CLEAR) )
    {
        gu8_front_rx_buffer[gu8_front_rx_receive_cnt] = mu8_rx_buffer;

        if (gu8_front_rx_buffer[0] == STX_FRONT_COMM)
        {
            switch(gu8_front_rx_receive_cnt)
            {
                case FRONT_COMMAND_ROCATION:

                    if( gu8_front_rx_buffer[FRONT_COMMAND_ROCATION] != RESPONSE_COMMAND_FRONT_COMM )
                    {
                        gu8_front_rx_receive_cnt = 0;
                    }
                    else{}

                    break;

                case (FRONT_LENGTH_ROCATION + 1):

                    /*mu8_packet_length = AscToHex(gu8_front_rx_buffer_temp[FRONT_LENGTH_ROCATION], gu8_front_rx_buffer_temp[FRONT_LENGTH_ROCATION + 1]);*/

                    break;

                default :

                    break;
            }

            if(gu8_front_rx_receive_cnt >= (U8)(FRONT_TO_MAIN_DATA_TOTAL_LENGTH - 1))
            {
                if(gu8_front_rx_buffer[gu8_front_rx_receive_cnt] == ETX_FRONT_COMM)
                {
                    gu8_front_rx_receive_cnt = 0;
                    F_Front_Rx_Complete = SET;
                }
                else
                {
                    gu8_front_rx_receive_cnt = 0;
                }
            }
            else
            {
                gu8_front_rx_receive_cnt++;
            }
        }
        else
        {
            gu8_front_rx_receive_cnt = 0;
        }
    }
    else
    {
        gu8_front_rx_receive_cnt = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR2_Front_Panel_Tx ( void )
{
    if(gu8_front_tx_count < MAIN_TO_FRONT_DATA_TOTAL_LENGTH)
    {
        TXD2 = gu8_front_tx_buffer[gu8_front_tx_count];
        gu8_front_tx_count++;
    }
    else
    {
        F_Front_Tx_Request = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

