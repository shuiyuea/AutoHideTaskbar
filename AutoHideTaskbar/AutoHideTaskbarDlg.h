
// AutoHideTaskbarDlg.h: 头文件
//

#pragma once


// CAutoHideTaskbarDlg 对话框
class CAutoHideTaskbarDlg : public CDialogEx
{
// 构造
public:
	CAutoHideTaskbarDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOHIDETASKBAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void EnableBarAutoHide(bool bEnable);

	bool IsBarAutoHide();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
