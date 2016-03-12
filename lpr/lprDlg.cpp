
// lprDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "lpr.h"
#include "lprDlg.h"
#include "afxdialogex.h"

#define PI 3.1415926

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
	 //TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_strPicPath;  
	//����ѡ��ͼƬ�Ի���  
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"),NULL);  
	dlg.m_ofn.lpstrTitle = _T("Open Image");// ���ļ��Ի���ı�����  
	if( dlg.DoModal() != IDOK )        // �ж��Ƿ�����Ƶ  
		return;  
	m_strPicPath = dlg.GetPathName();           //��ȡͼƬ·��  
	m_strPicPath.Replace(_T("//"),_T("////"));  
  
	Src=cvLoadImage((CT2CA)m_strPicPath,1); //��ȡ��ɫͼ  
	//Src = cvLoadImage((CT2CA)m_strPicPath,0);        //��ȡ�Ҷ�ͼƬ  
  
  
	if (TheImage != NULL)  
	{  
		ShowImage(Src, IDC_STATIC);  
		//ShowImage(Src, IDC_STATIC);
	} 


	//Դ����
	//CFileDialog dlg(TRUE, NULL, NULL, NULL,NULL,this);
	//CString strFileName;//��¼ѡ���ļ�·��
	//if (!dlg.DoModal() == IDOK) return;
	//strFileName = dlg.GetPathName();

	////IplImage *image=NULL; //ԭʼͼ��
	//if(Src) cvReleaseImage(&Src);
	//Src = cvLoadImage(strFileName); //��ʾͼƬ

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
	LprMain(this->Src);
}


//����ʶ���������
//void ClprDlg::LprMain()
void ClprDlg::LprMain(IplImage *ImageSrc)
{
	IplImage *GrayImage =NULL;
	GrayImage = cvCreateImage(cvSize(ImageSrc->width,ImageSrc->height),IPL_DEPTH_8U,1);
	//�Ѳ�ɫͼ��ת��Ϊ�Ҷ�ͼ��
	cvCvtColor(ImageSrc,GrayImage,CV_RGB2GRAY);


	IplImage* PrePrecessingImg = ImPreProcessing(GrayImage);
	
	LpLocation(PrePrecessingImg);

	//����ROI
	CvSize size = cvSize(colEnd-colStart,rowEnd-rowStart);
	cvSetImageROI(GrayImage,cvRect(colStart,rowStart,size.width,size.height));//����Դͼ��ROI
	CvRect roi = cvGetImageROI(GrayImage);
	IplImage* pDest = cvCreateImage(size,GrayImage->depth,GrayImage->nChannels);//����Ŀ��ͼ��

	cvCopy(GrayImage,pDest); //����ͼ��
	cvResetImageROI(GrayImage);//Դͼ����������ROI

	cvShowImage("RIO.bmp",pDest);

	//���ڵ�ͼ��ΪpDest��Ϊһ���ֶ�λ��ͼƬ
	IplImage* OtsuOrienImage = cvCreateImage(cvGetSize(pDest),pDest->depth,pDest->nChannels);
	cvThreshold(pDest,OtsuOrienImage,0,255,CV_THRESH_OTSU);
	cvShowImage("OtsuOrientImage",OtsuOrienImage);
	cvSaveImage("��ֵ��֮���ͼ��.bmp",OtsuOrienImage);



	//�Գ��ƽ�����ת������angle
	double angle = 0;
	IplImage* RotateImage_tmp = cvCreateImage(cvGetSize(pDest),pDest->depth,pDest->nChannels);
	angle = LineFitting(OtsuOrienImage);





	//cvReleaseImage(&PrePrecessingImg);
	cvReleaseImage(&pDest);
	cvReleaseImage(&OtsuOrienImage);





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
	//cvShowImage("b1.bmp",Egray);

	//�Ҷ����
	//cvSub�����������ָ�����ô����Ӧ��ȫ��Ϊ0
	//���ʹ�ÿ�����Ľ����ȥԭ���ĵ�ɫͼ���õ���ͼ��ȫ��Ϊ0
	//cvSub(Egray,GrayImage,temp);
	cvSub(GrayImage,Egray,temp,NULL);
	//cvShowImage("b2.bmp",temp);
	
	//�Ҷ�����
	//��������ͼ��̫������Ҫ��ͼ���������
	//�Ҷ�����ĺ��������Լ�д��
	IplImage* AdjustImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	ImageAdjust(temp,AdjustImage,0.25,0.8,0,1);
	//cvShowImage("b3.bmp",AdjustImage);


	////otsu��ֵ��
	//���������ͼ����ж�ֵ���������������б�Ե�ж�
	IplImage* otsuImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U, 1);
	cvThreshold(AdjustImage,otsuImage,0,255,CV_THRESH_OTSU);
	//cvShowImage("��ֵ��.bmp",otsuImage);

	//������Ϲ���Ͷ�Ŀ������㣬ԭ��δ֪
	//����ģ��Ϊ23*7 ������
	//���������Ƚ������ͺ�ʴ���Ƕ԰�ɫ������У���ʵʹ��һ�����κ����������еĺ�ɫ������ʾ�����Ƶ�λ�� 
	IplImage* bg1 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(23,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(otsuImage,bg1,temp,strel,CV_MOP_CLOSE);
	//cvShowImage("��ֵ��֮�������.bmp",bg1);

	//����ģ��Ϊ25*7�Ŀ�����
	//�����������Ƚ��и�ʴ�����ͣ�����ͼ������ЩС����İ�ɫ����
	IplImage* bg2 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(25,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(bg1,bg2,temp,strel,CV_MOP_OPEN);
	//cvShowImage("������ͼ��.bmp",bg2);

	//����ģ��Ϊ9*1�Ŀ�����
	//����ͼ������Щ���ŵ�ϸС��ɫ����
	IplImage* bg3 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(1,9,0,4,CV_SHAPE_RECT);
	cvMorphologyEx(bg2,bg3,temp,strel,CV_MOP_OPEN);
	//cvShowImage("��������.bmp",bg3);
	cvSaveImage("��������.bmp",bg3);

	cvReleaseImage(&temp);
	cvReleaseImage(&Egray);
	cvReleaseImage(&AdjustImage);
	cvReleaseImage(&bg1);
	cvReleaseImage(&bg2);

	//���й���cvCreateImage���ڴ�������⣿
	return bg3;
}

//Դ����
//IplImage *ClprDlg::ImPreProcessing(IplImage *GrayImage)
//{
//	IplImage * temp = cvCreateImage(cvGetSize(GrayImage), 8,1);	
//	IplImage *Egray = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//�������Ľ��  �Ĵ������
//	IplConvKernel *strel=cvCreateStructuringElementEx(9,9,4,4,CV_SHAPE_RECT);	//������ģ�� 9*9
//	//������
//	cvMorphologyEx(GrayImage,Egray,temp,strel,CV_MOP_OPEN,1);
//	cvShowImage("b1.bmp",Egray);
//	//�Ҷ����
//	cvSub(GrayImage,Egray,temp,NULL);
//	cvShowImage("b2.bmp",temp);
//
//	//�Ҷ�����
//	IplImage *AdjustImage =cvCreateImage(cvGetSize(GrayImage), 8,1);
//	ImageAdjust(temp,AdjustImage,0.25,0.8,0,1);
//	cvShowImage("b3.bmp",AdjustImage);
//	//otsu��ֵ��
//	IplImage *OtsuImage =cvCreateImage(cvGetSize(GrayImage), 8,1);
//	cvThreshold(AdjustImage, OtsuImage, 0, 255 , CV_THRESH_OTSU); //
//	cvShowImage("OtsuImage", OtsuImage); 
//	//������
//	IplImage *bg1 = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//�������Ľ��
//	strel=cvCreateStructuringElementEx(23,7,11,3,CV_SHAPE_RECT);	//������ģ�� 9*25
//	cvMorphologyEx(OtsuImage,bg1,temp,strel,CV_MOP_CLOSE,1);
//	cvShowImage("bg1", bg1);
//	//������
//	IplImage *bg2 = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//�������Ľ��
//	strel=cvCreateStructuringElementEx(25,7,11,3,CV_SHAPE_RECT);	//������ģ�� 9*27
//	cvMorphologyEx(bg1,bg2,temp,strel,CV_MOP_OPEN,1);
//	cvShowImage("bg2", bg2);
//	//������
//	IplImage *bg3 = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//�������Ľ��
//	strel=cvCreateStructuringElementEx(1,9,0,4,CV_SHAPE_RECT);	//������ģ�� 9*1
//	cvMorphologyEx(bg2,bg3,temp,strel,CV_MOP_OPEN,1);
//
//	cvShowImage("bg3", bg3);
//
//	cvReleaseImage(&temp);
//	cvReleaseImage(&Egray);
//	cvReleaseImage(&AdjustImage);
//	cvReleaseImage(&OtsuImage);
//	cvReleaseImage(&bg1);
//	cvReleaseImage(&bg2);
//
//	return bg3;
//}


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
//Դ����
//void ClprDlg::ImageAdjust(IplImage *img_in,IplImage *img_out,double low_in, double high_in,double low_out, double high_out)
//{
//	double low = low_in*255;  
//	double high = high_in*255;  
//	double bottom = low_out*255;  
//	double top = high_out*255;  
//	double scope_in = high - low;  
//	double scope_out = top - bottom;  
//
//	int x,y;  
//	double val0/*,val1,val2*/;  
//
//	// intensity transform  
//	for( y = 0; y < img_in->height; y++) {  
//		for (x = 0; x < img_in->width; x++){  
//			val0 = ((uchar*)(img_in->imageData+img_in->widthStep*y))[x*img_in->nChannels];   
//			val0 = pow((val0 - low)/scope_in,1)*scope_out+bottom;  
//			if(val0>255) val0=255;   
//			if(val0<0) val0=0;   
//			((uchar*)(img_out->imageData+img_out->widthStep*y))[x*img_in->nChannels]=(uchar)val0;  
//		}  
//	}  
//}

//���ƶ�λ����
//���룺����ͼ��ѧ������ͼƬ
//����������еı�������ʼ�ͽ���������
//0307���ж�ȡͼ���ʱ��λ��������(���Ͻǲ�Ϊ0,0)
void ClprDlg::LpLocation(IplImage *img_in)
{
	int row = img_in->height;
	int col = img_in->width;

	int* horiLine = new int[col];
	int* verLine = new int[row];
	/*int horiLine[400];
	int verLine[400];*/
	
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

	for (int i = row -1; i > 0; i--)
	{
		if (verLine[i] && verLine[i-1] && verLine[i-2] && verLine[i-3] && verLine[i-10] && verLine[i-15] )
		{
			rowEndTmp = i;
			break;
		}
	}

	for (int i = rowEndTmp; i > rowEndTmp - 60; i--)
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
		if (horiLine[i]  && horiLine[i+10] && horiLine[i+20] && horiLine[i+30] && horiLine[i+40] )
		{
			colStartTmp = i;
			break;
		}
	}

	for (int i = colStartTmp + 1; i < colStartTmp + 200; i++)
	{
		if(!horiLine[i])
		{
			colEndTmp = i;
			break;
		}
	}

	//���ں���Ҳ��Ҫ��ͼ������Ҫ��������
	rowStart = rowStartTmp - 0.15*(rowEndTmp - rowStartTmp);
	rowEnd = rowEndTmp + 0.2*(rowEndTmp - rowStartTmp);
	colStart = colStartTmp - 0.1*(colEndTmp - colStartTmp);
	colEnd = colEndTmp+0.1*(colEndTmp - colStartTmp);
	/*rowStart = rowStartTmp;
	rowEnd = rowEndTmp;
	colStart = colStartTmp;
	colEnd = colEndTmp;*/

	if(rowStart < 0)
		rowStart = 0;
	if(colStart < 0)
		colStart = 0;

	delete []horiLine;
	delete []verLine;
}
//Դ����
//void ClprDlg::LpLocation(IplImage *img)
//{
//	int rows = img->height;
//	int cols = img->width;
//	int *rowtmp = new int[rows];
//	int *coltmp = new int[cols];
//	int grayval;
//	int startlinetmp=0;
//	int endlinetmp=0;
//	int startcoltmp=0;
//	int endcoltmp=0;
//
//	//ˮƽͶӰ
//	for(int y = 0; y < rows; y++) 
//	{
//		rowtmp[y]=0;
//		for (int x = 0; x < cols; x++)
//		{  
//			grayval = ((uchar*)(img->imageData+img->widthStep*y))[x*img->nChannels];   
//			if(grayval==255) rowtmp[y]++;    
//		}  
//	}  
//
//	for(int i=rows-1;i>0;i--)
//	{
//		if(rowtmp[i]&&rowtmp[i-1]&&rowtmp[i-2]&&rowtmp[i-3]&&rowtmp[i-10]&&rowtmp[i-15])
//		{
//			startlinetmp = i;
//			break;
//		}	
//	}
//
//	for(int i=startlinetmp;i>startlinetmp-60;i--)
//	{
//		if(!rowtmp[i])
//		{
//			endlinetmp = i;
//			break;
//		}	
//	}
//
//	//��ֱͶӰ
//	for (int x = 0; x < cols; x++) 
//	{  
//		coltmp[x] = 0;
//		for(int y = endlinetmp; y < startlinetmp; y++)
//		{  
//			grayval = ((uchar*)(img->imageData+img->widthStep*y))[x*img->nChannels];   
//			if(grayval==255) coltmp[x]++;    
//		}  
//	}  
//
//	for(int i=0;i<cols-1;i++)
//	{
//		if(coltmp[i]&&coltmp[i+10]&&coltmp[i+20]&&coltmp[i+30]&&coltmp[i+40])
//		{
//			startcoltmp = i;
//			break;
//		}	
//	}
//
//	for(int i=startcoltmp+1;i<startcoltmp+200;i++)
//	{
//		if(!coltmp[i])
//		{
//			endcoltmp = i;
//			break;
//		}	
//	}
//
//	rowEnd=startlinetmp+0.2*(startlinetmp-endlinetmp);
//	rowStart=endlinetmp-0.15*(startlinetmp-endlinetmp);
//	colStart=startcoltmp-0.1*(endcoltmp-startcoltmp);
//	colEnd=endcoltmp+0.1*(endcoltmp-startcoltmp);
//
//	delete []rowtmp;
//	delete []coltmp;
//}


//��ͼ����нǶ�У���������Ҫ��ת�ĽǶ�
double ClprDlg::LineFitting(IplImage* img)
{
	double angle1 = 0, angle2 = 0, angle = 0;
	int rows = img->height;
	int cols = img->width;
	int count = 0;
	int grayval;

	//�±�Ե���
	//����ͳ���±�Ե�ķ�Χ���ж��ٸ�����Ҫ���
	for (int x = 0; x < cols; x++)
	{
		for (int y = rows-1; y >2*rows/3; y--)
		{
			grayval = ((uchar*)(img->imageData + img->widthStep*y))[x*img->nChannels];
			if(grayval == 255)
			{
				count++;
				break;
			}
		}
	}

	int* x1 = new int[count];
	int* y1 = new int[count];
	int k = 0;

	for (int i = 0; i < cols; i++)
	{
		for(int j = rows - 1; j>2*rows/3; j--)
		{
			grayval = ((uchar*)(img->imageData + img->widthStep*j))[i*img->nChannels];
			if (grayval == 255)
			{
				x1[k] = i;
				y1[k] = j;
				k++;
				break;
			}
		}
	}

	//��ʱ��õ����±�Ե��x��y������,���ص�ֵ���±�Ե�����x��ĽǶ�
	angle1 = PolyFit(x1,y1,count);

	//�ϱ�Ե���
	count = 0;
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < 1*rows/3; y++)
		{
			grayval = ((uchar*)(img->imageData + img->widthStep*y))[x*img->nChannels];
			if(grayval == 255)
			{
				count++;
				break;
			}
		}
	}

	int* x2 = new int[count];
	int* y2 = new int[count];
	k = 0;

	for (int i = 0; i < cols; i++)
	{
		for(int j = 0; j < 1*rows/3; j++)
		{
			grayval = ((uchar*)(img->imageData + img->widthStep*j))[i*img->nChannels];
			if (grayval == 255)
			{
				x2[k] = i;
				y2[k] = j;
				k++;
				break;
			}
		}
	}

	//��ʱ��õ����±�Ե��x��y������,���ص�ֵ���±�Ե�����x��ĽǶ�
	angle2 = PolyFit(x2,y2,count);

	angle = (angle1 + angle2)/2;

	delete[] x1;
	delete[] y1;
	delete[] x2;
	delete[] y2;

	return angle;
}

//����count��xy���꣬��ϳ�һ��ֱ�ߣ������ֱ�ߵĽǶ�
double ClprDlg::PolyFit(int* x, int* y, int count)
{
	double a=0,b=0,c=0,d=0;
	double k=0; //ֱ��б��

	for(int i = 0;i < count;i++)
	{
		a += x[i]*x[i];
		b += x[i];
		c += x[i]*y[i];
		d += y[i];
	}
	k = (count*c - b*d)/(count*a - b*b);
	//б�ʷ�����ֵ���õ�һ�����ȣ�ͨ��PI�ļ���õ����ĽǶ�
	return atan(k)*180/PI;
}


//ͼ����ת
/****************************
***�������� ��			ͼ����ת
***����		��src		����ת��ͼ��
			��angle		������ת�ĽǶ�
***����ֵ	��			��ת���ͼ���ָ��
*****************************/
void bound(int x, int y, float ca, float sa, int *xmin, int *xmax, int *ymin, int *ymax)
{   
	int rx,ry;
	// ˳ʱ����ת
	rx = (int)floor(ca*(float)x+sa*(float)y);
	ry = (int)floor(-sa*(float)x+ca*(float)y);
	if (rx<*xmin) *xmin=rx; if (rx>*xmax) *xmax=rx;
	if (ry<*ymin) *ymin=ry; if (ry>*ymax) *ymax=ry;
}
IplImage *ClprDlg::ImageRotate(IplImage *src, double angle)
{
	double anglerad  = (CV_PI* (angle/180)) ;
	int newheight =int (fabs(( sin(anglerad)*src->width )) + fabs(( cos(anglerad)*src->height )) );
	int newwidth  =int (fabs(( sin(anglerad)*src->height)) + fabs(( cos(anglerad)*src->width)) );
	float m[6];            
	CvMat M = cvMat( 2, 3, CV_32F, m );
	int  nx,ny; 
	float  ca,sa;
	int  xmin,xmax,ymin,ymax,sx,sy;
	ca = (float)cos((double)(angle)*CV_PI/180.0);
	sa = (float)sin((double)(angle)*CV_PI/180.0);
	nx = src->width;
	ny=src->height;
	xmin = xmax = ymin = ymax = 0;
	bound(nx-1,0,ca,sa,&xmin,&xmax,&ymin,&ymax);
	bound(0,ny-1,ca,sa,&xmin,&xmax,&ymin,&ymax);
	bound(nx-1,ny-1,ca,sa,&xmin,&xmax,&ymin,&ymax);
	sx = xmax-xmin+1;
	sy = ymax-ymin+1;
	IplImage* newImage;
	newImage=cvCreateImage(cvSize(sx,sy),src->depth,src->nChannels);
	m[0] = ca;
	m[1] = sa;
	m[2] =-(float)xmin; 
	m[3] =-m[1];
	m[4] = m[0];
	m[5] =-(float)ymin;
	cvWarpAffine( src, newImage, &M,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS,cvScalarAll(0) );

	return newImage;
}