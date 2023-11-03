
// AutoHideTaskbarDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AutoHideTaskbar.h"
#include "AutoHideTaskbarDlg.h"
#include "afxdialogex.h"
#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoHideTaskbarDlg 对话框



CAutoHideTaskbarDlg::CAutoHideTaskbarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOHIDETASKBAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoHideTaskbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAutoHideTaskbarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAutoHideTaskbarDlg 消息处理程序

BOOL CAutoHideTaskbarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//开启或关闭任务栏自动隐藏功能
	EnableBarAutoHide(!IsBarAutoHide());

	SetTimer(1, 2000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoHideTaskbarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutoHideTaskbarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAutoHideTaskbarDlg::EnableBarAutoHide(bool bEnable)
{
	//设置状态栏的自动隐藏状态
	//取消自动隐藏
	HWND hwndTaskbar = FindWindowW(L"Shell_TrayWnd", NULL);

	APPBARDATA appBarData = { sizeof(appBarData) };

	appBarData.cbSize = sizeof(appBarData);
	appBarData.hWnd = hwndTaskbar;

	if (bEnable)
		appBarData.lParam = ABS_AUTOHIDE | ABS_ALWAYSONTOP;
	else
		appBarData.lParam = ABS_ALWAYSONTOP;

	SHAppBarMessage(ABM_SETSTATE | ABM_SETAUTOHIDEBAR, &appBarData);
}

bool CAutoHideTaskbarDlg::IsBarAutoHide()
{
	//判断自动隐藏是否开启
	HWND hwndTaskbar = FindWindowW(L"Shell_TrayWnd", NULL);

	APPBARDATA barData = { sizeof(barData) };
	barData.cbSize = sizeof(barData);
	barData.hWnd = hwndTaskbar;
	UINT state = SHAppBarMessage(ABM_GETSTATE, &barData);

	if ((state & ABS_AUTOHIDE) != 0)
		return true;
	else
		return false;
}



void CAutoHideTaskbarDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(1);

	//关闭程序
	OnOK();

	CDialogEx::OnTimer(nIDEvent);
}
