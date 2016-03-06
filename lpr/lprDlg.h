
// lprDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include "CvvImage.h"

// ClprDlg �Ի���
class ClprDlg : public CDialogEx
{
// ����
public:
	ClprDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LPR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void ShowImage(IplImage* img, UINT ID);

//����ԭͼ�������ָ��TheImage ����ԭͼ��Src����ԭͼ�ĵ�ɫͼ
private:
	IplImage* TheImage;
	IplImage* Src;
public:
	afx_msg void OnBnClickedButton2();


protected:
	void LprMain();
	IplImage* ImPreProcessing(IplImage* GrayImage);
	//�Ҷ����캯��
	void ImageAdjust(IplImage *img_in,IplImage *img_out,double low_in, double high_in,double low_out, double high_out);
};
