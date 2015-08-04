/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.20                          *
*        Compiled Mar 19 2013, 15:01:00                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "includes.h"



#define METER_ADDR_TEXT_LEN     12

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#if 0
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "ReadMeterExt", ID_WINDOW_0, 0, 0, 240, 295, 0, 0x0, 0 },
  { TEXT_CreateIndirect,   "CalTime",      ID_TEXT_0, 14, 18, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Edit",         ID_BUTTON_0, 141, 13, 80, 20, 0, 0x64, 0 },
    
  { TEXT_CreateIndirect,   "CalTime",      ID_TEXT_0, 14, 18, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Edit",         ID_EDIT_0, 141, 13, 80, 20, 0, 0x64, 0 },
};
#endif

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect,  "ext",      ID_WINDOW_0,  0,   0,   240, 295, 0, 0x0, 0 },

  
  { TEXT_CreateIndirect,    MeterNum,     ID_TEXT_0,   12,  15,  100,  20, 0, 0x0, 0 },
  { EDIT_CreateIndirect,    "meter",      ID_EDIT_0,   125, 15,  110,  20, 0, 0x64, 0 },

  { TEXT_CreateIndirect,    CalTime_YMDW,  ID_TEXT_5,   12,  45,  110,  20, 0, 0x0, 0 },
  { TEXT_CreateIndirect,    CalTime_HMS,  ID_TEXT_6,   12,  75,  100,  20, 0, 0x0, 0 },

  { TEXT_CreateIndirect,    Read_YMDWHMS, ID_TEXT_1,   12,  105,  100,  20, 0, 0x0, 0 },




  
  { BUTTON_CreateIndirect,   "F1",         ID_BUTTON_2,  125, 45,  110,  20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "F2",         ID_BUTTON_3,  125, 75,  110,  20, 0, 0x0, 0 },
    
  { BUTTON_CreateIndirect,  "*",          ID_BUTTON_0,  125, 105,  110,  20, 0, 0x0, 0 },
    
  //{ TEXT_CreateIndirect,    MeterTimeYMD, ID_TEXT_2,   12,  75,  215,  20, 0, 0x0, 0 },
  //{ TEXT_CreateIndirect,    ReadTime_HMS, ID_TEXT_3,   12,  105,  100,  20, 0, 0x0, 0 },
  //{ TEXT_CreateIndirect,    MeterTimeHMS, ID_TEXT_4,   12,  135,  100,  20, 0, 0x0, 0 },

  { EDIT_CreateIndirect,    "metertime",      ID_EDIT_2,   12, 135,  223,  20, EDIT_CF_HCENTER, 0x64, 0 },
    
  
  //{ EDIT_CreateIndirect,    "YMDW",        ID_EDIT_1,    115, 75,  120,  20, 0, 0x64, 0 },
  //{ BUTTON_CreateIndirect,  "",         ID_BUTTON_1,  115, 105,  120,  20, 0, 0x0, 0 },

  //{ EDIT_CreateIndirect,    "HMS",        ID_EDIT_2,    115, 105,  120,  20, 0, 0x64, 0 },
    
  { BUTTON_CreateIndirect,  MsgLog,         ID_BUTTON_4,  75,  262, 90,  25, 0, 0x0, 0},
  { BUTTON_CreateIndirect,  Back,        ID_BUTTON_5,  175, 262, 55,  25, 0, 0x0, 0},
   
  { PROGBAR_CreateIndirect, "Progbar",    ID_PROGBAR_0, 8, 238, 224, 20, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//把报文中的年月日数据解析出来填入EDIT
void MTD_DipYMD(void)
{
    WM_HWIN hItem;
    hItem = WM_GetDialogItem(g_hWin_MeterTime, ID_EDIT_1);
    EDIT_SetText(hItem, "YearMonthDay");
}

void MTD_DipHMS(void)
{
    WM_HWIN hItem;
    hItem = WM_GetDialogItem(g_hWin_MeterTime, ID_EDIT_2);
    EDIT_SetText(hItem, "HourMinSec");
}

WM_HWIN MTD_GetYMD(void)
{
    return WM_GetDialogItem(g_hWin_MeterTime, ID_EDIT_1);
}

WM_HWIN MTD_GetTime(void)
{
    return WM_GetDialogItem(g_hWin_MeterTime, ID_EDIT_2);
}

WM_HWIN MTD_GetMeterAddr(void)
{
    return WM_GetDialogItem(g_hWin_MeterTime, ID_EDIT_0);
}

void MTD_SetAddrBkColor(WM_HWIN hItem)
{
    EDIT_SetBkColor(hItem, 0, GUI_GREEN);
}

WM_HWIN MTD_Get_PROGBAR()
{    
     return WM_GetDialogItem(g_hWin_MeterTime, ID_PROGBAR_0);            
}

static u8 MTD_Get_Read_Date_Para(WM_MESSAGE *pMsg)
{   
    WM_HWIN hItem;
    u8 len, buf[GUI_645_ADDR_LENGTH + 2];
    
 
    hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_0);
    EDIT_GetText(hItem, buf, GUI_645_ADDR_LENGTH+1);

    if(strlen(buf) != GUI_645_ADDR_LENGTH)
    {
        return DEV_ERROR;
    }

    if(DEV_OK != GUI_GetMeterAddr(buf, g_gui_para.dstAddr))
    {
        return DEV_ERROR;
    }
    
    g_gui_para.ctrlCode = c_645ctrlDef[g_rom_para.protocol][DL645_CTRL_READ_DATA];

    len = (DL645_1997 == g_rom_para.protocol) ? (DL645_97_DATA_ITEM_LEN) : (DL645_07_DATA_ITEM_LEN);

    memcpy(g_gui_para.dataItem, &c_645dataItemDef[g_rom_para.protocol][4], len);

    g_gui_para.dataLen = 0;

    g_gui_para.cmd = GUI_CMD_MRW;
    
    return DEV_OK;

}

static u8 MTD_Get_Read_Time_Para(WM_MESSAGE *pMsg)
{   
    WM_HWIN hItem;
    u8 len, buf[GUI_645_ADDR_LENGTH + 2];
    
 
    hItem=WM_GetDialogItem(g_hWin_MeterTime, ID_EDIT_0);
    EDIT_GetText(hItem, buf, GUI_645_ADDR_LENGTH+1);

    if(strlen(buf) != GUI_645_ADDR_LENGTH)
    {
        return DEV_ERROR;
    }

    if(DEV_OK != GUI_GetMeterAddr(buf, g_gui_para.dstAddr))
    {
        return DEV_ERROR;
    }
    
    g_gui_para.ctrlCode = c_645ctrlDef[g_rom_para.protocol][DL645_CTRL_READ_DATA];

    len = (DL645_1997 == g_rom_para.protocol) ? (DL645_97_DATA_ITEM_LEN) : (DL645_07_DATA_ITEM_LEN);

    memcpy(g_gui_para.dataItem, &c_645dataItemDef[g_rom_para.protocol][5], len);

    g_gui_para.dataLen = 0;

    g_gui_para.cmd = GUI_CMD_MRW;
    
    return DEV_OK;

}

static u8 MTD_Get_Cal_Date_Para(WM_MESSAGE *pMsg)
{   
    WM_HWIN hItem;
    u8 len, buf[GUI_645_ADDR_LENGTH + 2];
    u16 index;
    
 
    hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_0);
    EDIT_GetText(hItem, buf, GUI_645_ADDR_LENGTH+1);

    if(strlen(buf) != GUI_645_ADDR_LENGTH)
    {
        return DEV_ERROR;
    }

    if(DEV_OK != GUI_GetMeterAddr(buf, g_gui_para.dstAddr))
    {
        return DEV_ERROR;
    }
    
    g_gui_para.ctrlCode = c_645ctrlDef[g_rom_para.protocol][DL645_CTRL_WRITE_DATA];
    
    len = (DL645_1997 == g_rom_para.protocol) ? (DL645_97_DATA_ITEM_LEN) : (DL645_07_DATA_ITEM_LEN);

    memcpy(g_gui_para.dataItem, &c_645dataItemDef[g_rom_para.protocol][4], len);

    g_gui_para.dataLen = 0;
    index = 0;

    memcpy(&g_gui_para.dataBuf[index], &g_rom_para.meter_pwd, METER_PWD_LEN); //电表密码
    g_gui_para.dataLen += METER_PWD_LEN;
    index += METER_PWD_LEN;

    if(DL645_2007 == g_rom_para.protocol)   
    {
        memcpy(&g_gui_para.dataBuf[index], &g_rom_para.opcode, OPCODE_LEN); //操作者代码
        g_gui_para.dataLen += OPCODE_LEN;
        index += OPCODE_LEN;
    }

    g_gui_para.dataBuf[index++] = g_rtc_time[WEEK_POS] % 7;
    g_gui_para.dataBuf[index++] = g_rtc_time[DATE_POS];
    g_gui_para.dataBuf[index++] = g_rtc_time[MONTH_POS];
    g_gui_para.dataBuf[index++] = g_rtc_time[YEAR_POS];

    g_gui_para.dataLen += 4;

    g_gui_para.cmd = GUI_CMD_MRW;
    
    return DEV_OK;
}

static u8 MTD_Get_Cal_Time_Para(WM_MESSAGE *pMsg)
{   
    WM_HWIN hItem;
    u8 i, len, buf[GUI_645_ADDR_LENGTH + 2];
    u16 index;
 
    hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_0);
    EDIT_GetText(hItem, buf, GUI_645_ADDR_LENGTH+1);

    if(strlen(buf) != GUI_645_ADDR_LENGTH)
    {
        return DEV_ERROR;
    }

    if(DEV_OK != GUI_GetMeterAddr(buf, g_gui_para.dstAddr))
    {
        return DEV_ERROR;
    }
    
    g_gui_para.ctrlCode = c_645ctrlDef[g_rom_para.protocol][DL645_CTRL_WRITE_DATA];

    len = (DL645_1997 == g_rom_para.protocol) ? (DL645_97_DATA_ITEM_LEN) : (DL645_07_DATA_ITEM_LEN);
    
    memcpy(g_gui_para.dataItem, &c_645dataItemDef[g_rom_para.protocol][5], len);

    g_gui_para.dataLen = 0;
    index = 0;

    memcpy(&g_gui_para.dataBuf[index], &g_rom_para.meter_pwd, METER_PWD_LEN); //电表密码
    g_gui_para.dataLen += METER_PWD_LEN;
    index += METER_PWD_LEN;

    if(DL645_2007 == g_rom_para.protocol)   
    {
        memcpy(&g_gui_para.dataBuf[index], &g_rom_para.opcode, OPCODE_LEN); //操作者代码
        g_gui_para.dataLen += OPCODE_LEN;
        index += OPCODE_LEN;
    }

    g_gui_para.dataBuf[index++] = g_rtc_time[SEC_POS];
    g_gui_para.dataBuf[index++] = g_rtc_time[MIN_POS];
    g_gui_para.dataBuf[index++] = g_rtc_time[HOUR_POS];

    g_gui_para.dataLen += 3;

    g_gui_para.cmd = GUI_CMD_MRW;
    
    return DEV_OK;
}

void MTD_proc_resp_data(void)
{
    WM_HWIN hItem;
    static u8 meter_time[32];
    u8 *pbuf;
    u16 len;


    pbuf = g_proto_para.data_buf;
    len = g_proto_para.data_len;

    if(WM_HWIN_NULL != g_hWin_MeterTime)
    {   
        if(4 == len)
        {
            sprintf(&meter_time[0], "20%02x-%02x-%02x %s ", pbuf[3], pbuf[2], pbuf[1], TextWeek[pbuf[0] % 7]);

            if(DEV_OK == MTD_Get_Read_Time_Para(NULL))
            {
                g_gui_para.state = GUI_STATE_METER_TIME;
                OSMboxPost(g_sys_ctrl.up_mbox, (void*)&g_gui_para);
            }               
        }
        else if(3 == len)
        {
            sprintf(&meter_time[18], "%02x:%02x:%02x", pbuf[2], pbuf[1], pbuf[0]);
            
            hItem = MTD_GetTime();

            EDIT_SetText(hItem, meter_time);
        }  
    }   
}

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) 
{
    WM_HWIN hItem;
    int     NCode;
    int     Id;
    // USER START (Optionally insert additional variables)
    // USER END

    switch (pMsg->MsgId) 
    {
        case WM_INIT_DIALOG:
            u8 t_buf[16];
            hItem = RMD_Get_MeterNum();
            /*从抄表页面获取表地址并填充到此页面中*/
            EDIT_GetText(hItem, t_buf, METER_ADDR_TEXT_LEN + 1); 
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
            EDIT_SetText(hItem, t_buf);
            WM_DisableWindow(hItem);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
            BUTTON_SetBkColor(hItem, 0, GUI_CYAN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
            BUTTON_SetBkColor(hItem, 0, GUI_CYAN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
            BUTTON_SetBkColor(hItem, 0, GUI_CYAN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
            BUTTON_SetBkColor(hItem, 0, GUI_CYAN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
            BUTTON_SetBkColor(hItem, 0, GUI_CYAN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
            BUTTON_SetBkColor(hItem, 0, GUI_YELLOW);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
            EDIT_SetText(hItem, "0000-00-00 XXXX 00:00:00");
            WM_DisableWindow(hItem);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
            break;
            
        case WM_NOTIFY_PARENT:
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
            
            break;
                   
        case WM_KEY:
            if((((WM_KEY_INFO *)(pMsg->Data.p))->PressedCnt) == 1)
            {
                Id    = WM_GetId(pMsg->hWinSrc);
                switch(((WM_KEY_INFO*)(pMsg->Data.p))->Key)
                {  
                    case GUI_KEY_YELLOW:
                        WM_DeleteWindow(g_hWin_MeterTime);
                        g_hWin_MeterTime = HBWIN_NULL;
                        RMD_SetFocus();
                        
                        hItem = RMD_Get_MeterNum();
                        EDIT_SetText(hItem, (const char *)GUI_hex2MeterAddrStr(g_sys_ctrl.recentMeterAddr, 6));
                        
                        g_gui_para.state = GUI_STATE_IDLE;
                        break;

                    case '#':
                        WM_BringToTop(g_hWin_msg);
                        WM_ShowWindow(g_hWin_msg);                    
                        WM_SetFocus(g_hWin_msg);
                        break;

                    case '*':
                        if(DEV_OK == MTD_Get_Read_Date_Para(pMsg)) //获取参数数据
                        {
                            g_gui_para.state = GUI_STATE_METER_TIME;
                            OSMboxPost(g_sys_ctrl.up_mbox, (void*)&g_gui_para);
                        }
                        break;

                    case GUI_KEY_F1:
                        if(DEV_OK == MTD_Get_Cal_Date_Para(pMsg)) //获取参数数据
                        {
                            g_gui_para.state = GUI_STATE_METER_TIME;
                            OSMboxPost(g_sys_ctrl.up_mbox, (void*)&g_gui_para);
                        }                        
                        break;
                        
                    case GUI_KEY_F2:
                        if(DEV_OK == MTD_Get_Cal_Time_Para(pMsg)) //获取参数数据
                        {
                            g_gui_para.state = GUI_STATE_METER_TIME;
                            OSMboxPost(g_sys_ctrl.up_mbox, (void*)&g_gui_para);
                        }       
                        break;

                    case GUI_KEY_ENTER:
                        if(ID_EDIT_0 == Id)
                        {
                            g_sys_ctrl.selectWidget = EDIT_METER_ADDE;
                            g_hWin_Input = Create_Edit_Set(g_hWin_MeterTime);
                        }
                        break;
                }
            }
            
            break;
            
        default:
            WM_DefaultProc(pMsg);
            break;
    }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateReadMeterExt
*/
WM_HWIN CreateExtFnct(void);
WM_HWIN CreateExtFnct(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, g_hWin_ReadMeter, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
