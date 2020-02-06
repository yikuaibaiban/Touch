
// TouchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Touch.h"
#include "TouchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTouchDlg 对话框



CTouchDlg::CTouchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTouchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTouchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_html);
}

BEGIN_MESSAGE_MAP(CTouchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTouchDlg 消息处理程序

BOOL CTouchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_bFullScreen = !m_bFullScreen; // 设置全屏显示标志

	//一种更好的全屏显示
	LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	if (m_bFullScreen)//全屏显示
	{
		style &= ~(WS_DLGFRAME | WS_THICKFRAME);
		SetWindowLong(this->m_hWnd, GWL_STYLE, style);
		this->ShowWindow(SW_SHOWMAXIMIZED);
		CRect rect;
		this->GetWindowRect(&rect);
		::SetWindowPos(this->m_hWnd, HWND_NOTOPMOST, rect.left - 1, rect.top - 1, rect.right - rect.left + 3, rect.bottom - rect.top + 3, SWP_FRAMECHANGED);
	}
	else
	{
		style |= WS_DLGFRAME | WS_THICKFRAME;
		SetWindowLong(this->m_hWnd, GWL_STYLE, style);
		this->ShowWindow(SW_NORMAL);
	}


	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);

	CString str;
	//LPWSTR path = _T("");
	//GetCurrentDirectory(MAX_PATH, path);

	CFile file(path + _T("\\url.txt"), CFile::modeRead);

	char* lpBuf = new char[file.GetLength()];
	memset(lpBuf, 0, file.GetLength());

	//CFile file(wcscat(path, _T("/url.txt")), CFile::modeRead);
	file.Read(lpBuf, file.GetLength());
	str = lpBuf;

	//this->MessageBox(str);

	m_html.put_Silent(TRUE);
	m_html.Navigate(str, NULL, NULL, NULL, NULL);
	////m_html.Navigate(_T("http://cmp.blztb.gov.cn"), NULL, NULL, NULL, NULL);
	CRect rect;
	GetWindowRect(&rect);
	m_html.put_Width(rect.Width());
	m_html.put_Height(rect.Height());
	delete lpBuf;
	file.Close();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTouchDlg::OnPaint()
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
HCURSOR CTouchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CTouchDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO:  在此处添加消息处理程序代码
//	//m_html.put_Width(cx);
//	//m_html.put_Height(cy);
//}


void CTouchDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnOK();
}


void CTouchDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	//return;
	int messagebox = MessageBox(L"确定要退出程序吗？", L"退出", MB_YESNO);
	if (messagebox == IDYES)
	{
		CDialogEx::OnCancel();
	}
	else{
		return;
	}
}
