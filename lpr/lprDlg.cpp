
// lprDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "lpr.h"
#include "lprDlg.h"
#include "afxdialogex.h"

#define PI 3.1415926

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
	 //TODO: 在此添加控件通知处理程序代码
	CString m_strPicPath;  
	//弹出选择图片对话框  
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,_T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"),NULL);  
	dlg.m_ofn.lpstrTitle = _T("Open Image");// 打开文件对话框的标题名  
	if( dlg.DoModal() != IDOK )        // 判断是否获得视频  
		return;  
	m_strPicPath = dlg.GetPathName();           //获取图片路径  
	m_strPicPath.Replace(_T("//"),_T("////"));  
  
	Src=cvLoadImage((CT2CA)m_strPicPath,1); //读取彩色图  
	//Src = cvLoadImage((CT2CA)m_strPicPath,0);        //读取灰度图片  
  
  
	if (TheImage != NULL)  
	{  
		ShowImage(Src, IDC_STATIC);  
		//ShowImage(Src, IDC_STATIC);
	} 


	//源程序
	//CFileDialog dlg(TRUE, NULL, NULL, NULL,NULL,this);
	//CString strFileName;//记录选择文件路径
	//if (!dlg.DoModal() == IDOK) return;
	//strFileName = dlg.GetPathName();

	////IplImage *image=NULL; //原始图像
	//if(Src) cvReleaseImage(&Src);
	//Src = cvLoadImage(strFileName); //显示图片

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
	LprMain(this->Src);
}


//车牌识别的主程序
//void ClprDlg::LprMain()
void ClprDlg::LprMain(IplImage *ImageSrc)
{
	IplImage *GrayImage =NULL;
	GrayImage = cvCreateImage(cvSize(ImageSrc->width,ImageSrc->height),IPL_DEPTH_8U,1);
	//把彩色图像转换为灰度图像
	cvCvtColor(ImageSrc,GrayImage,CV_RGB2GRAY);


	IplImage* PrePrecessingImg = ImPreProcessing(GrayImage);
	
	LpLocation(PrePrecessingImg);

	//定义ROI
	CvSize size = cvSize(colEnd-colStart,rowEnd-rowStart);
	cvSetImageROI(GrayImage,cvRect(colStart,rowStart,size.width,size.height));//设置源图像ROI
	CvRect roi = cvGetImageROI(GrayImage);
	IplImage* pDest = cvCreateImage(size,GrayImage->depth,GrayImage->nChannels);//创建目标图像

	cvCopy(GrayImage,pDest); //复制图像
	cvResetImageROI(GrayImage);//源图像用完后，清空ROI

	cvShowImage("RIO.bmp",pDest);

	//现在的图像为pDest，为一个粗定位的图片
	IplImage* OtsuOrienImage = cvCreateImage(cvGetSize(pDest),pDest->depth,pDest->nChannels);
	cvThreshold(pDest,OtsuOrienImage,0,255,CV_THRESH_OTSU);
	cvShowImage("OtsuOrientImage",OtsuOrienImage);
	cvSaveImage("二值化之后的图像.bmp",OtsuOrienImage);



	//对车牌进行旋转，其中angle
	double angle = 0;
	IplImage* RotateImage_tmp = cvCreateImage(cvGetSize(pDest),pDest->depth,pDest->nChannels);
	angle = LineFitting(OtsuOrienImage);





	//cvReleaseImage(&PrePrecessingImg);
	cvReleaseImage(&pDest);
	cvReleaseImage(&OtsuOrienImage);





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
	//cvShowImage("b1.bmp",Egray);

	//灰度相减
	//cvSub中如果相减出现负数怎么处理，应该全部为0
	//如果使用开运算的结果减去原来的单色图，得到的图像全部为0
	//cvSub(Egray,GrayImage,temp);
	cvSub(GrayImage,Egray,temp,NULL);
	//cvShowImage("b2.bmp",temp);
	
	//灰度拉伸
	//由于整个图像太暗，需要对图像进行拉伸
	//灰度拉伸的函数是由自己写的
	IplImage* AdjustImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	ImageAdjust(temp,AdjustImage,0.25,0.8,0,1);
	//cvShowImage("b3.bmp",AdjustImage);


	////otsu二值化
	//对拉伸完的图像进行二值化处理，方便后面进行边缘判断
	IplImage* otsuImage = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U, 1);
	cvThreshold(AdjustImage,otsuImage,0,255,CV_THRESH_OTSU);
	//cvShowImage("二值化.bmp",otsuImage);

	//？进行瞎鸡巴多的开闭运算，原因未知
	//进行模板为23*7 闭运算
	//闭运算是先进行膨胀后腐蚀，是对白色区域进行；其实使用一个矩形核消除车牌中的黑色区域，显示出车牌的位置 
	IplImage* bg1 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(23,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(otsuImage,bg1,temp,strel,CV_MOP_CLOSE);
	//cvShowImage("二值化之后闭运算.bmp",bg1);

	//进行模板为25*7的开运算
	//开运算是是先进行腐蚀后膨胀，消除图像中那些小面积的白色部分
	IplImage* bg2 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(25,7,11,3,CV_SHAPE_RECT);
	cvMorphologyEx(bg1,bg2,temp,strel,CV_MOP_OPEN);
	//cvShowImage("开运算图像.bmp",bg2);

	//进行模板为9*1的开运算
	//消除图像中那些横着的细小白色条纹
	IplImage* bg3 = cvCreateImage(cvGetSize(GrayImage),IPL_DEPTH_8U,1);
	strel = cvCreateStructuringElementEx(1,9,0,4,CV_SHAPE_RECT);
	cvMorphologyEx(bg2,bg3,temp,strel,CV_MOP_OPEN);
	//cvShowImage("二闭运算.bmp",bg3);
	cvSaveImage("二闭运算.bmp",bg3);

	cvReleaseImage(&temp);
	cvReleaseImage(&Egray);
	cvReleaseImage(&AdjustImage);
	cvReleaseImage(&bg1);
	cvReleaseImage(&bg2);

	//其中关于cvCreateImage的内存分配问题？
	return bg3;
}

//源程序
//IplImage *ClprDlg::ImPreProcessing(IplImage *GrayImage)
//{
//	IplImage * temp = cvCreateImage(cvGetSize(GrayImage), 8,1);	
//	IplImage *Egray = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//开运算后的结果  的存放数组
//	IplConvKernel *strel=cvCreateStructuringElementEx(9,9,4,4,CV_SHAPE_RECT);	//开运算模板 9*9
//	//开运算
//	cvMorphologyEx(GrayImage,Egray,temp,strel,CV_MOP_OPEN,1);
//	cvShowImage("b1.bmp",Egray);
//	//灰度相减
//	cvSub(GrayImage,Egray,temp,NULL);
//	cvShowImage("b2.bmp",temp);
//
//	//灰度拉伸
//	IplImage *AdjustImage =cvCreateImage(cvGetSize(GrayImage), 8,1);
//	ImageAdjust(temp,AdjustImage,0.25,0.8,0,1);
//	cvShowImage("b3.bmp",AdjustImage);
//	//otsu二值化
//	IplImage *OtsuImage =cvCreateImage(cvGetSize(GrayImage), 8,1);
//	cvThreshold(AdjustImage, OtsuImage, 0, 255 , CV_THRESH_OTSU); //
//	cvShowImage("OtsuImage", OtsuImage); 
//	//闭运算
//	IplImage *bg1 = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//开运算后的结果
//	strel=cvCreateStructuringElementEx(23,7,11,3,CV_SHAPE_RECT);	//闭运算模板 9*25
//	cvMorphologyEx(OtsuImage,bg1,temp,strel,CV_MOP_CLOSE,1);
//	cvShowImage("bg1", bg1);
//	//开运算
//	IplImage *bg2 = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//开运算后的结果
//	strel=cvCreateStructuringElementEx(25,7,11,3,CV_SHAPE_RECT);	//开运算模板 9*27
//	cvMorphologyEx(bg1,bg2,temp,strel,CV_MOP_OPEN,1);
//	cvShowImage("bg2", bg2);
//	//开运算
//	IplImage *bg3 = cvCreateImage(cvSize(GrayImage->width,GrayImage->height),IPL_DEPTH_8U,1);	//开运算后的结果
//	strel=cvCreateStructuringElementEx(1,9,0,4,CV_SHAPE_RECT);	//开运算模板 9*1
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
//源程序
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

//车牌定位程序
//输入：经过图像学处理后的图片
//输出：在类中的变量，开始和结束的行列
//0307其中读取图像的时候位置有问题(左上角才为0,0)
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
	//水平投影和垂直投影
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

	//找到水平和垂直的开始和结束位置
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

	//由于后面也需要抠图所以需要增大区域
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
//源程序
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
//	//水平投影
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
//	//垂直投影
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


//对图像进行角度校正，输出需要旋转的角度
double ClprDlg::LineFitting(IplImage* img)
{
	double angle1 = 0, angle2 = 0, angle = 0;
	int rows = img->height;
	int cols = img->width;
	int count = 0;
	int grayval;

	//下边缘拟合
	//首先统计下边缘的范围中有多少个点需要拟合
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

	//这时候得到了下边缘的x和y的坐标,返回的值是下边缘相对于x轴的角度
	angle1 = PolyFit(x1,y1,count);

	//上边缘拟合
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

	//这时候得到了下边缘的x和y的坐标,返回的值是下边缘相对于x轴的角度
	angle2 = PolyFit(x2,y2,count);

	angle = (angle1 + angle2)/2;

	delete[] x1;
	delete[] y1;
	delete[] x2;
	delete[] y2;

	return angle;
}

//输入count个xy坐标，拟合成一条直线，并输出直线的角度
double ClprDlg::PolyFit(int* x, int* y, int count)
{
	double a=0,b=0,c=0,d=0;
	double k=0; //直线斜率

	for(int i = 0;i < count;i++)
	{
		a += x[i]*x[i];
		b += x[i];
		c += x[i]*y[i];
		d += y[i];
	}
	k = (count*c - b*d)/(count*a - b*b);
	//斜率反正切值，得到一个弧度，通过PI的计算得到最后的角度
	return atan(k)*180/PI;
}


//图像旋转
/****************************
***函数功能 ：			图像旋转
***输入		：src		待旋转的图像
			：angle		待拟旋转的角度
***返回值	：			旋转后的图像的指针
*****************************/
void bound(int x, int y, float ca, float sa, int *xmin, int *xmax, int *ymin, int *ymax)
{   
	int rx,ry;
	// 顺时针旋转
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