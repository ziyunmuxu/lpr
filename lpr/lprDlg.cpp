
// lprDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "lpr.h"
#include "lprDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// ClprDlg 对话框




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


// ClprDlg 消息处理程序

BOOL ClprDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClprDlg::OnPaint()
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
HCURSOR ClprDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//用来选择图片，并在图像编辑框中显示

void ClprDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_strPicPath;  
	//弹出选择图片对话框  
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"),NULL);  
	dlg.m_ofn.lpstrTitle = _T("Open Image");// 打开文件对话框的标题名  
	if( dlg.DoModal() != IDOK )        // 判断是否获得视频  
		return;  
	m_strPicPath = dlg.GetPathName();           //获取图片路径  
	m_strPicPath.Replace(_T("//"),_T("////"));  
  
	TheImage=cvLoadImage((CT2CA)m_strPicPath,1); //读取彩色图  
	Src = cvLoadImage((CT2CA)m_strPicPath,0);        //读取灰度图片  
  
  
	if (TheImage != NULL)  
	{  
		ShowImage(TheImage, IDC_STATIC);  
		//ShowImage(Src, IDC_STATIC);
	} 
}

void ClprDlg::ShowImage(IplImage* img, UINT ID) //在picture控件中显示图片的代码  
{  
  CDC* pDC=GetDlgItem(ID)->GetDC();  
  HDC hDC=pDC->GetSafeHdc();  
  CRect rect;  
  GetDlgItem(ID)->GetClientRect(&rect);  
  SetRect(rect,rect.left,rect.top,rect.right,rect.bottom);  
  CvvImage cimg;  
  cimg.CopyOf( img ); // 复制图片  
  cimg.DrawToHDC( hDC, &rect );  // 将图片绘制到显示控件的指定区域内  
  ReleaseDC( pDC );  
} 


//开始识别传过来的单色图
void ClprDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	LprMain();
}


//车牌识别的主程序
void ClprDlg::LprMain()
{
	ImPreProcessing(this->Src);
	
}

//图像预处理进程，输入为单色图，输出为处理后的指针
IplImage* ClprDlg::ImPreProcessing(IplImage* GrayImage)
{
	//对原图进行9*9的开运算，运算之后的结果和原图进行相见
	IplImage* temp = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);//用来存放相减的结果，也用来当做开运算中缓存的量
	IplImage* Egray = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);//用来存放开运算的结果
	IplConvKernel* strel = cvCreateStructuringElementEx(9,9,4,4,CV_SHAPE_RECT);//用来开运算的模板，其中大小为9*9，锚的位置为(4,4)位于正方形的中间

	//开运算
	//?开运算中几个参数的意义，注意里面需要temp来进行缓存
	cvMorphologyEx(GrayImage,Egray,temp,strel,CV_MOP_OPEN,1);
	cvShowImage("b1.bmp",Egray);

	//灰度相减
	//cvSub中如果相减出现负数怎么处理，应该全部为0
	//如果使用开运算的结果减去原来的单色图，得到的图像全部为0
	//cvSub(Egray,GrayImage,temp);
	cvSub(GrayImage,Egray,temp,NULL);
	cvShowImage("b2.bmp",temp);
	
	//灰度拉伸
	//由于整个图像太暗，需要对图像进行拉伸
	//灰度拉伸的函数是由自己写的
	IplImage* AdjustImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	ImageAdjust(temp,AdjustImage,0.25,0.8,0,1);
	cvShowImage("b3.bmp",AdjustImage);


	////otsu二值化
	//对拉伸完的图像进行二值化处理，方便后面进行边缘判断
	IplImage* otsuImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U, 1);
	cvThreshold(AdjustImage,otsuImage,0,255,CV_THRESH_OTSU);
	cvShowImage("二值化.bmp",otsuImage);

	//？进行瞎鸡巴多的开闭运算，原因未知
	//进行模板为23*7 闭运算
	IplImage* bg1 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(23,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(otsuImage,bg1,temp,strel,CV_MOP_CLOSE);
	cvShowImage("二值化之后闭运算.bmp",bg1);

	//进行模板为25*7的开运算
	IplImage* bg2 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(25,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(bg1,bg2,temp,strel,CV_MOP_OPEN);
	cvShowImage("开运算图像.bmp",bg2);

	//进行模板为9*1的开运算
	IplImage* bg3 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(1,9,0,4,CV_SHAPE_RECT);
	cvMorphologyEx(bg2,bg3,temp,strel,CV_MOP_OPEN);
	cvShowImage("二闭运算.bmp",bg3);

	return Egray;
}



/****************************
***函数功能 ：			图像灰度拉伸
***输入		：img_in	待校正图像指针
：low_in	输入图像归一化灰度最小值
：high_in	输入图像归一化灰度最大值
：low_out	输出图像归一化灰度最小值
：high_out	输出图像归一化灰度最大值
***输出		：img_out	灰度拉伸后图像指针
***返回值	：			需校正的角度
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

	//一定需要注意的是怎么遍历整个图像数组
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