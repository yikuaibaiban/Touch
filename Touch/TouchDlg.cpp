
// TouchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Touch.h"
#include "TouchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTouchDlg �Ի���



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


// CTouchDlg ��Ϣ�������

BOOL CTouchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_bFullScreen = !m_bFullScreen; // ����ȫ����ʾ��־

	//һ�ָ��õ�ȫ����ʾ
	LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	if (m_bFullScreen)//ȫ����ʾ
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTouchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTouchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CTouchDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO:  �ڴ˴������Ϣ����������
//	//m_html.put_Width(cx);
//	//m_html.put_Height(cy);
//}


void CTouchDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	return;
	CDialogEx::OnOK();
}


void CTouchDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	//return;
	int messagebox = MessageBox(L"ȷ��Ҫ�˳�������", L"�˳�", MB_YESNO);
	if (messagebox == IDYES)
	{
		CDialogEx::OnCancel();
	}
	else{
		return;
	}
}
