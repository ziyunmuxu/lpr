
// lprDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "lpr.h"
#include "lprDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ClprDlg �Ի���




ClprDlg::ClprDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClprDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClprDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClprDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &ClprDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ClprDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// ClprDlg ��Ϣ�������

BOOL ClprDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void ClprDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void ClprDlg::OnPaint()
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
HCURSOR ClprDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//����ѡ��ͼƬ������ͼ��༭������ʾ

void ClprDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_strPicPath;  
	//����ѡ��ͼƬ�Ի���  
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"),NULL);  
	dlg.m_ofn.lpstrTitle = _T("Open Image");// ���ļ��Ի���ı�����  
	if( dlg.DoModal() != IDOK )        // �ж��Ƿ�����Ƶ  
		return;  
	m_strPicPath = dlg.GetPathName();           //��ȡͼƬ·��  
	m_strPicPath.Replace(_T("//"),_T("////"));  
  
	TheImage=cvLoadImage((CT2CA)m_strPicPath,1); //��ȡ��ɫͼ  
	Src = cvLoadImage((CT2CA)m_strPicPath,0);        //��ȡ�Ҷ�ͼƬ  
  
  
	if (TheImage != NULL)  
	{  
		ShowImage(TheImage, IDC_STATIC);  
		//ShowImage(Src, IDC_STATIC);
	} 
}

void ClprDlg::ShowImage(IplImage* img, UINT ID) //��picture�ؼ�����ʾͼƬ�Ĵ���  
{  
  CDC* pDC=GetDlgItem(ID)->GetDC();  
  HDC hDC=pDC->GetSafeHdc();  
  CRect rect;  
  GetDlgItem(ID)->GetClientRect(&rect);  
  SetRect(rect,rect.left,rect.top,rect.right,rect.bottom);  
  CvvImage cimg;  
  cimg.CopyOf( img ); // ����ͼƬ  
  cimg.DrawToHDC( hDC, &rect );  // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������  
  ReleaseDC( pDC );  
} 


//��ʼʶ�𴫹����ĵ�ɫͼ
void ClprDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LprMain();
}


//����ʶ���������
void ClprDlg::LprMain()
{
	IplImage *GrayImage =NULL;
	IplImage* PrePrecessingImg = ImPreProcessing(this->Src);
	
	LpLocation(PrePrecessingImg);

	//����ROI
	CvSize size = cvSize(colEnd-colStart,rowEnd-rowStart);
	cvSetImageROI(this->Src,cvRect(colStart,rowStart,size.width,size.height));//����Դͼ��ROI
	CvRect roi = cvGetImageROI(this->Src);
	IplImage* pDest = cvCreateImage(size,Src->depth,Src->nChannels);//����Ŀ��ͼ��

	cvCopy(Src,pDest); //����ͼ��
	cvResetImageROI(Src);//Դͼ����������ROI

	cvShowImage("RIO.bmp",pDest);

	cvReleaseImage(&PrePrecessingImg);
}

//ͼ��Ԥ������̣�����Ϊ��ɫͼ�����Ϊ������ָ��
IplImage* ClprDlg::ImPreProcessing(IplImage* GrayImage)
{
	//��ԭͼ����9*9�Ŀ����㣬����֮��Ľ����ԭͼ�������
	IplImage* temp = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);//�����������Ľ����Ҳ���������������л������
	IplImage* Egray = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);//������ſ�����Ľ��
	IplConvKernel* strel = cvCreateStructuringElementEx(9,9,4,4,CV_SHAPE_RECT);//�����������ģ�壬���д�СΪ9*9��ê��λ��Ϊ(4,4)λ�������ε��м�

	//������
	//?�������м������������壬ע��������Ҫtemp�����л���
	cvMorphologyEx(GrayImage,Egray,temp,strel,CV_MOP_OPEN,1);
	cvShowImage("b1.bmp",Egray);

	//�Ҷ����
	//cvSub�����������ָ�����ô����Ӧ��ȫ��Ϊ0
	//���ʹ�ÿ�����Ľ����ȥԭ���ĵ�ɫͼ���õ���ͼ��ȫ��Ϊ0
	//cvSub(Egray,GrayImage,temp);
	cvSub(GrayImage,Egray,temp,NULL);
	cvShowImage("b2.bmp",temp);
	
	//�Ҷ�����
	//��������ͼ��̫������Ҫ��ͼ���������
	//�Ҷ�����ĺ��������Լ�д��
	IplImage* AdjustImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	ImageAdjust(temp,AdjustImage,0.25,0.8,0,1);
	cvShowImage("b3.bmp",AdjustImage);


	////otsu��ֵ��
	//���������ͼ����ж�ֵ���������������б�Ե�ж�
	IplImage* otsuImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U, 1);
	cvThreshold(AdjustImage,otsuImage,0,255,CV_THRESH_OTSU);
	cvShowImage("��ֵ��.bmp",otsuImage);

	//������Ϲ���Ͷ�Ŀ������㣬ԭ��δ֪
	//����ģ��Ϊ23*7 ������
	//���������Ƚ������ͺ�ʴ���Ƕ԰�ɫ������У���ʵʹ��һ�����κ����������еĺ�ɫ������ʾ�����Ƶ�λ�� 
	IplImage* bg1 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(23,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(otsuImage,bg1,temp,strel,CV_MOP_CLOSE);
	cvShowImage("��ֵ��֮�������.bmp",bg1);

	//����ģ��Ϊ25*7�Ŀ�����
	//�����������Ƚ��и�ʴ�����ͣ�����ͼ������ЩС����İ�ɫ����
	IplImage* bg2 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(25,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(bg1,bg2,temp,strel,CV_MOP_OPEN);
	cvShowImage("������ͼ��.bmp",bg2);

	//����ģ��Ϊ9*1�Ŀ�����
	//����ͼ������Щ���ŵ�ϸС��ɫ����
	IplImage* bg3 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(1,9,0,4,CV_SHAPE_RECT);
	cvMorphologyEx(bg2,bg3,temp,strel,CV_MOP_OPEN);
	cvShowImage("��������.bmp",bg3);
	cvSaveImage("��������.bmp",bg3);

	cvReleaseImage(&temp);
	cvReleaseImage(&Egray);
	cvReleaseImage(&AdjustImage);
	cvReleaseImage(&bg1);
	cvReleaseImage(&bg2);

	//���й���cvCreateImage���ڴ�������⣿
	return bg3;
}



/****************************
***�������� ��			ͼ��Ҷ�����
***����		��img_in	��У��ͼ��ָ��
��low_in	����ͼ���һ���Ҷ���Сֵ
��high_in	����ͼ���һ���Ҷ����ֵ
��low_out	���ͼ���һ���Ҷ���Сֵ
��high_out	���ͼ���һ���Ҷ����ֵ
***���		��img_out	�Ҷ������ͼ��ָ��
***����ֵ	��			��У���ĽǶ�
*****************************/
void ClprDlg::ImageAdjust(IplImage *img_in,IplImage *img_out,double low_in, double high_in,double low_out, double high_out)
{
	double low = low_in * 255;
	double high = high_in * 255;
	double button = low_out * 255;
	double top = high_out * 255;
	double rate = (top - button)/(high - low);

	int x = 0;
	int y = 0;
	double value0 = 0;

	//һ����Ҫע�������ô��������ͼ������
	for (y = 0; y < img_in->height; y++)
	{
		for (x = 0; x < img_in->width; x++)
		{
			value0 = ((uchar*)(img_in->imageData + img_in->widthStep*y))[x*img_in->nChannels];
			value0 = rate * (value0 - low) + button;
			if (value0 < 0) value0 = 0;
			if (value0 > 255) value0 = 255;
			((uchar*)(img_out->imageData + img_out->widthStep*y))[x*img_out->nChannels] = value0;
		}
	}
}



//���ƶ�λ����
//���룺����ͼ��ѧ������ͼƬ
//����������еı�������ʼ�ͽ���������

void ClprDlg::LpLocation(IplImage *img_in)
{
	int row = img_in->height;
	int col = img_in->width;

	int* horiLine = new int[col];
	int* verLine = new int[row];
	
	memset(horiLine,0,sizeof(int)*col);
	memset(verLine,0,sizeof(int)*row);
	int value0;
	//ˮƽͶӰ�ʹ�ֱͶӰ
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			value0 = ((uchar*)(img_in->imageData + img_in->widthStep*i))[j*img_in->nChannels];
			if (value0 == 255)
			{
				verLine[i]++;
				horiLine[j]++;
			}
		}
	}

	//�ҵ�ˮƽ�ʹ�ֱ�Ŀ�ʼ�ͽ���λ��
	int rowStartTmp;
	int rowEndTmp;
	int colStartTmp;
	int colEndTmp;

	for (int i = row -1; i > 15; i--)
	{
		if (verLine[i] && verLine[i-3] && verLine[i-6] && verLine[i-15] )
		{
			rowEndTmp = i;
		}
	}

	for (int i = rowEndTmp; i > 0; i--)
	{
		if(!verLine[i])
		{
			rowStartTmp = i;
			break;
		}
	}

	/////////////////////////////
	for (int i = 0; i < col; i++)
	{
		if (horiLine[i] && horiLine[i+5] && horiLine[i+10] && horiLine[i+15] && horiLine[i+25] && horiLine[i+35] )
		{
			colStartTmp = i;
		}
	}

	for (int i = colStartTmp; i < col; i++)
	{
		if(!horiLine[i])
		{
			colEndTmp = i;
			break;
		}
	}

	//���ں���Ҳ��Ҫ��ͼ������Ҫ��������
	rowStart = rowStartTmp - 0.1*(rowEndTmp - rowStartTmp);
	rowEnd = rowEndTmp + 0.1*(rowEndTmp - rowStartTmp);
	colStart = colStartTmp - 0.15*(colEndTmp - colStartTmp);
	colEnd = colEndTmp+0.2*(colEndTmp - colStartTmp);

	if(rowStart < 0)
		rowStart = 0;
	if(colStart < 0)
		colStart = 0;

	delete []horiLine;
	delete []verLine;
}