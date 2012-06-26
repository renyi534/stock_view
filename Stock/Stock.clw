; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "stock.h"
LastPage=0

ClassCount=13
Class1=CChildFrame
Class2=CHistoryDoc
Class3=CHistoryFrame
Class4=CHistoryView
Class5=CMainFrame
Class6=CRealTimeDoc
Class7=CRealTimeFrame
Class8=CRealTimeView
Class9=CSelectionDlg
Class10=CStockApp
Class11=CAboutDlg
Class12=CStockDoc
Class13=CStockView

ResourceCount=7
Resource1=IDR_MAINFRAME
Resource2=IDR_HISTORY
Resource3=IDR_REALTIME
Resource4=IDR_STOCKTYPE
Resource5=IDD_ABOUTBOX
Resource6=IDD_SELECTION
Resource7=IDD_SLIDER

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CHistoryDoc]
Type=0
BaseClass=CDocument
HeaderFile=HistoryDoc.h
ImplementationFile=HistoryDoc.cpp

[CLS:CHistoryFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=HistoryFrame.h
ImplementationFile=HistoryFrame.cpp

[CLS:CHistoryView]
Type=0
BaseClass=CView
HeaderFile=HistoryView.h
ImplementationFile=HistoryView.cpp
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CRealTimeDoc]
Type=0
BaseClass=CDocument
HeaderFile=RealTimeDoc.h
ImplementationFile=RealTimeDoc.cpp

[CLS:CRealTimeFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=RealTimeFrame.h
ImplementationFile=RealTimeFrame.cpp
LastObject=ID_FILE_SAVE_AS

[CLS:CRealTimeView]
Type=0
BaseClass=CView
HeaderFile=RealTimeView.h
ImplementationFile=RealTimeView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CRealTimeView

[CLS:CSelectionDlg]
Type=0
BaseClass=CDialog
HeaderFile=SelectionDlg.h
ImplementationFile=SelectionDlg.cpp
LastObject=CSelectionDlg

[CLS:CStockApp]
Type=0
BaseClass=CWinApp
HeaderFile=Stock.h
ImplementationFile=Stock.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Stock.cpp
ImplementationFile=Stock.cpp
LastObject=CAboutDlg

[CLS:CStockDoc]
Type=0
BaseClass=CDocument
HeaderFile=StockDoc.h
ImplementationFile=StockDoc.cpp

[CLS:CStockView]
Type=0
BaseClass=CView
HeaderFile=StockView.h
ImplementationFile=StockView.cpp

[DLG:IDD_SELECTION]
Type=1
Class=CSelectionDlg
ControlCount=11
Control1=IDC_LISTCTRL,SysListView32,1350565909
Control2=IDC_STATIC,static,1342177793
Control3=IDC_EDITNO,edit,1350565889
Control4=IDC_STATIC,static,1342177793
Control5=IDC_EDITNAME,edit,1484783617
Control6=IDC_BUTTONHISTORY,button,1342181120
Control7=IDC_BUTTONREALTIME,button,1342181120
Control8=IDC_STATIC,static,1342308353
Control9=IDC_DATE_PICKER,SysDateTimePick32,1342242848
Control10=IDC_COMBOBOXEX1,ComboBoxEx32,1344340226
Control11=IDC_IS_DYNAMIC,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_STOCKTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_WINDOW_NEW
Command13=ID_WINDOW_CASCADE
Command14=ID_WINDOW_TILE_HORZ
Command15=ID_WINDOW_ARRANGE
Command16=ID_APP_ABOUT
CommandCount=16

[MNU:IDR_HISTORY]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[MNU:IDR_REALTIME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_SLIDER]
Type=1
Class=?
ControlCount=1
Control1=IDC_SLIDERCTRL,msctls_trackbar32,1342177300

