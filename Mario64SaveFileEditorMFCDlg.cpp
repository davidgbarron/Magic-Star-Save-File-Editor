
// Mario64SaveFileEditorMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Mario64SaveFileEditorMFC.h"
#include "Mario64SaveFileEditorMFCDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <atlimage.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <tchar.h>
#include <bitset>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//global variables
CString gpathname;
CString gfilename;
unsigned char mbuff[512];
unsigned char tbuff[512];
UINT buffsize = 0;
UINT16 checksum = 0;
UINT8 checksumbyte1 = 0;
UINT8 checksumbyte2 = 0;
UINT saveslot = 1;
//level bit strings
CString lvl1bits;
CString lvl2bits;
CString lvl3bits;
CString lvl4bits;
CString lvl5bits;
CString lvl6bits;
CString lvl7bits;
CString lvl8bits;
CString lvl9bits;
CString lvl10bits;
CString lvl11bits;
CString lvl12bits;
CString lvl13bits;
CString lvl14bits;
CString lvl15bits;
CString PeachSlideStars;
CString ToadMipsStars;
CString CastleFlag1;
CString CastleFlag2;
CString CastleFlag3;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	// declare a pointer to Cstatic class
	CStatic* pAboutIcon;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) 
{
	
	CDialogEx::DoDataExchange(pDX);
	//Initialize the CStatic object and set it to the Image.
	pAboutIcon = (CStatic*)GetDlgItem(IDC_ABOUTICON);
	HBITMAP AboutIcon = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 45, 45, LR_DEFAULTSIZE);// Use MAKEINTRESOURCE to embed to exe
	//AboutIcon = (HBITMAP)LoadImage(NULL, _T("res/MarioIconLarge.bmp"), IMAGE_BITMAP, 45, 45, LR_LOADFROMFILE); // Use LoadImage _T() to load from sep res folder, not embed exe.
	pAboutIcon->SetBitmap(AboutIcon);

}


// CMario64SaveFileEditorMFCDlg dialog



CMario64SaveFileEditorMFCDlg::CMario64SaveFileEditorMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MARIO64SAVEFILEEDITORMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(_T("res/MarioIcon.ico"));

}

void CMario64SaveFileEditorMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMario64SaveFileEditorMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, &CMario64SaveFileEditorMFCDlg::OnHelpAbout)
	ON_COMMAND(ID_FILE_EXIT, &CMario64SaveFileEditorMFCDlg::OnFileExit)
	ON_BN_CLICKED(ID_OPENFILE, &CMario64SaveFileEditorMFCDlg::OnBnClickedOpenfile)
	ON_COMMAND(ID_FILE_OPEN32771, &CMario64SaveFileEditorMFCDlg::OnMenuFileOpen)
	// use this to gray out buttons on -UpdateDialogControls(this,FALSE) 
	//ON_UPDATE_COMMAND_UI(ID_OPENFILE, &CMario64SaveFileEditorMFCDlg::OnUpdateButton)
END_MESSAGE_MAP()


// CMario64SaveFileEditorMFCDlg message handlers

BOOL CMario64SaveFileEditorMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//Declare a pointer pPcavater Object to the Class CStatic. used for images
	CStatic* pPCAvatar;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Create Main Mario Background Image using the pointer and defining it add to pic control
	pPCAvatar = (CStatic*)GetDlgItem(IDC_AVATAR);
	/*HBITMAP bg;
	bg = (HBITMAP)LoadImage(NULL, _T("res/MarioBG01.bmp"), IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE);*/
	HBITMAP bg = reinterpret_cast<HBITMAP>(LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 300, 300, LR_LOADTRANSPARENT));
	pPCAvatar->SetBitmap(bg);
	

	//Set the Mario Icon for the Main Window
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMario64SaveFileEditorMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMario64SaveFileEditorMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		
		//hdc = BeginPaint(&ps);
		//LoadAndBlitBitmap(_T("C:/Users/David G Barron/source/repos/Mario64SaveFileEditorMFC/res/"), hdc);
		
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMario64SaveFileEditorMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMario64SaveFileEditorMFCDlg::OnHelpAbout()
{

	CAboutDlg dlgAbout;
	dlgAbout.DoModal();

}

//Sends a message to close the application from the EXIT in the Main Menu.
void CMario64SaveFileEditorMFCDlg::OnFileExit()
{
	PostMessage(WM_CLOSE);
	
}

//Creates an open file menu on Open button clicked.
void CMario64SaveFileEditorMFCDlg::OnBnClickedOpenfile()
{
	LPCTSTR pszFileFilter = _T("Mario 64 Save Files |*.eep|");//encapsulate the file ext filter btw |*.ext|
	CFileDialog openDlg(TRUE, _T(".eep"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, pszFileFilter, AfxGetMainWnd());
	if (openDlg.DoModal() == IDOK)
	{
		CString pathname = openDlg.GetPathName();
		CString filename = openDlg.GetFileName();
		gpathname = pathname;
		gfilename = filename;
		//MessageBox(filename + pathname);

		MainEditor me;
		me.DoModal();
	}
	
}

// use this to create a file open menu from the OPEN in the Main Menu
void CMario64SaveFileEditorMFCDlg::OnMenuFileOpen()
{
	LPCTSTR pszFileFilter = _T("Mario 64 Save Files |*.eep|");
	CFileDialog openDlg(TRUE, _T(".eep"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, pszFileFilter, AfxGetMainWnd());
	if (openDlg.DoModal() == IDOK)
	{
		CString pathname = openDlg.GetPathName();
		CString filename = openDlg.GetFileName();
		gpathname = pathname;
		gfilename = filename;
		//MessageBox(filename + pathname);
		MainEditor me;
		me.DoModal();

		////use a string to collect the Binary number bit by bit and edit each bit individually according to star selection in descending order.
		//std::string bin = "10010101";
		//bin[5] = '0';
		////this set's the data to a UINT8 for saving, do not call this until the user hits save
		//std::bitset<8> set(bin);
		//UINT8 bin2byte = (set.to_ulong());
		//
		//CString mes;
		//mes.Format(_T("%x"), bin2byte);
		//MessageBox(mes);



	}
}


////////////////////////////////
//		MAIN EDITOR CODE
////////////////////////////////

MainEditor::MainEditor(CWnd* pParent) : CDialogEx(IDD_MAINEDITOR, pParent)
{
}

void MainEditor::DoDataExchange(CDataExchange* pDX)
{
	//Creates the Mario Icon for the Main Editor Dialog
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, TRUE);
	// creates a CMenu object and also a submenu object that allows us to manipulate the menu ID_OBJECTS
	CMenu* mmenu = GetMenu();
	mmenu->GetSubMenu(0);
	//Grays out the OPEN command in the Main Editor FILE drop down located on our submenu.
	

		mmenu->EnableMenuItem(ID_FILE_OPEN32771, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	ReadFileFromDisk(gpathname, mbuff, tbuff, &buffsize);

		//tbuff[126] = 0x95;// this is the way to edit the values directly on the temp buffer

		// set the binary strings of each level
	lvl1bits = HexToString(tbuff, 12);
	lvl2bits = HexToString(tbuff, 13);
	lvl3bits = HexToString(tbuff, 14);
	lvl4bits = HexToString(tbuff, 15);
	lvl5bits = HexToString(tbuff, 16);
	lvl6bits = HexToString(tbuff, 17);
	lvl7bits = HexToString(tbuff, 18);
	lvl8bits = HexToString(tbuff, 19);
	lvl9bits = HexToString(tbuff, 20);
	lvl10bits = HexToString(tbuff, 21);
	lvl11bits = HexToString(tbuff, 22);
	lvl12bits = HexToString(tbuff, 23);
	lvl13bits = HexToString(tbuff, 24);
	lvl14bits = HexToString(tbuff, 24);
	lvl15bits = HexToString(tbuff, 26);
	PeachSlideStars = HexToString(tbuff, 30);
	ToadMipsStars = HexToString(tbuff, 8);
	CastleFlag1 = HexToString(tbuff, 9);
	CastleFlag2 = HexToString(tbuff, 10);
	CastleFlag3 = HexToString(tbuff, 11);


	SetCheckBoxesOnStart();
	SetCoinScoresOnStart();

	//ChecksumCalculation(tbuff, &checksum, &checksumbyte1, &checksumbyte2, saveslot);
	//SaveFileToDisk(gpathname, tbuff, sizeof(tbuff));
	
	//CString size;
	//CString hi;// temporary string used in the message box for debugging.
	//UINT hi = 149;
	//size.Format(_T("%x"), hi);// used for debugging
	//MessageBox(lvl1bits);// used for debugging
}

BEGIN_MESSAGE_MAP(MainEditor, CDialogEx)
	ON_COMMAND(ID_FILE_EXIT, &MainEditor::OnFileExit)
	ON_COMMAND(ID_FILE_OPEN32771, &MainEditor::OnMenuFileOpen)
	ON_BN_CLICKED(IDC_LVL1STAR1CHECKBOX, &MainEditor::OnBnClickedLvl1star1checkbox)
	ON_BN_CLICKED(ID_SAVEFILE, &MainEditor::OnBnClickedSavefile)
	ON_BN_CLICKED(IDC_LVL1STAR2CHECKBOX, &MainEditor::OnBnClickedLvl1star2checkbox)
	//	level coin scores message map
	ON_EN_CHANGE(IDC_LVL1COINSCORE_EB, &MainEditor::OnEnChangeLvl1coinscoreEb)
	ON_EN_CHANGE(IDC_LVL15COINSCORE_EB, &MainEditor::OnEnChangeLvl15coinscoreEb)
	ON_EN_CHANGE(IDC_LVL14COINSCORE_EB, &MainEditor::OnEnChangeLvl14coinscoreEb)
	ON_EN_CHANGE(IDC_LVL13COINSCORE_EB, &MainEditor::OnEnChangeLvl13coinscoreEb)
	ON_EN_CHANGE(IDC_LVL12COINSCORE_EB, &MainEditor::OnEnChangeLvl12coinscoreEb)
	ON_EN_CHANGE(IDC_LVL11COINSCORE_EB, &MainEditor::OnEnChangeLvl11coinscoreEb)
	ON_EN_CHANGE(IDC_LVL10COINSCORE_EB, &MainEditor::OnEnChangeLvl10coinscoreEb)
	ON_EN_CHANGE(IDC_LVL9COINSCORE_EB, &MainEditor::OnEnChangeLvl9coinscoreEb)
	ON_EN_CHANGE(IDC_LVL8COINSCORE_EB, &MainEditor::OnEnChangeLvl8coinscoreEb)
	ON_EN_CHANGE(IDC_LVL7COINSCORE_EB, &MainEditor::OnEnChangeLvl7coinscoreEb)
	ON_EN_CHANGE(IDC_LVL6COINSCORE_EB, &MainEditor::OnEnChangeLvl6coinscoreEb)
	ON_EN_CHANGE(IDC_LVL5COINSCORE_EB, &MainEditor::OnEnChangeLvl5coinscoreEb)
	ON_EN_CHANGE(IDC_LVL4COINSCORE_EB, &MainEditor::OnEnChangeLvl4coinscoreEb)
	ON_EN_CHANGE(IDC_LVL3COINSCORE_EB, &MainEditor::OnEnChangeLvl3coinscoreEb)
	ON_EN_CHANGE(IDC_LVL2COINSCORE_EB, &MainEditor::OnEnChangeLvl2coinscoreEb)
	// level check box message map
	ON_BN_CLICKED(IDC_UPSTAIRSDOORUNLOCKED, &MainEditor::OnBnClickedUpstairsdoorunlocked)
	ON_BN_CLICKED(IDC_BASEMENTDOORUNLOCKED, &MainEditor::OnBnClickedBasementdoorunlocked)
	ON_BN_CLICKED(IDC_BOWSER2KEY, &MainEditor::OnBnClickedBowser2key)
	ON_BN_CLICKED(IDC_BOWSER1KEY, &MainEditor::OnBnClickedBowser1key)
	ON_BN_CLICKED(IDC_VANISHCAPSWITCH, &MainEditor::OnBnClickedVanishcapswitch)
	ON_BN_CLICKED(IDC_METALCAPSWITCH, &MainEditor::OnBnClickedMetalcapswitch)
	ON_BN_CLICKED(IDC_WINGCAPSWITCH, &MainEditor::OnBnClickedWingcapswitch)
	ON_BN_CLICKED(IDC_BOWSER2STARDOORUNLOCKED, &MainEditor::OnBnClickedBowser2stardoorunlocked)
	ON_BN_CLICKED(IDC_BOWSER1STARDOORUNLOCKED, &MainEditor::OnBnClickedBowser1stardoorunlocked)
	ON_BN_CLICKED(IDC_JOLLYROGERDOORUNLOCKED, &MainEditor::OnBnClickedJollyrogerdoorunlocked)
	ON_BN_CLICKED(IDC_COOLMOUNTAINDOORUNLOCKED, &MainEditor::OnBnClickedCoolmountaindoorunlocked)
	ON_BN_CLICKED(IDC_WHOMPSFORTRESSDOORUNLOCKED, &MainEditor::OnBnClickedWhompsfortressdoorunlocked)
	ON_BN_CLICKED(IDC_PEACHSECRETSLIDEDOORUNLOCKED, &MainEditor::OnBnClickedPeachsecretslidedoorunlocked)
	ON_BN_CLICKED(IDC_CASTLEMOATDRAINEDCHECKBOX, &MainEditor::OnBnClickedCastlemoatdrainedcheckbox)
	ON_BN_CLICKED(IDC_DDDPORTALMOVEDCHECKBOX, &MainEditor::OnBnClickedDddportalmovedcheckbox)
	ON_BN_CLICKED(IDC_CHECK136, &MainEditor::OnBnClickedCheck136)
	ON_BN_CLICKED(IDC_CAPSTOLENMONKEYCHECKBOX, &MainEditor::OnBnClickedCapstolenmonkeycheckbox)
	ON_BN_CLICKED(IDC_CAPSTOLENBIRDCHECKBOX, &MainEditor::OnBnClickedCapstolenbirdcheckbox)
	ON_BN_CLICKED(IDC_CAPSTOLENSNOWMANCHECKBOX, &MainEditor::OnBnClickedCapstolensnowmancheckbox)
	ON_BN_CLICKED(IDC_BOWSERSKYSTAR, &MainEditor::OnBnClickedBowserskystar)
	ON_BN_CLICKED(IDC_BOWSERFIRESEASTAR, &MainEditor::OnBnClickedBowserfireseastar)
	ON_BN_CLICKED(IDC_BOWSERDARKWORLDSTAR, &MainEditor::OnBnClickedBowserdarkworldstar)
	ON_BN_CLICKED(IDC_TOWERWINGCAPSTAR, &MainEditor::OnBnClickedTowerwingcapstar)
	ON_BN_CLICKED(IDC_VANISHCAPMOATSTAR, &MainEditor::OnBnClickedVanishcapmoatstar)
	ON_BN_CLICKED(IDC_WINGMARIORAINBOWSTAR, &MainEditor::OnBnClickedWingmariorainbowstar)
	ON_BN_CLICKED(IDC_CAVERNMETALCAPSTAR, &MainEditor::OnBnClickedCavernmetalcapstar)
	ON_BN_CLICKED(IDC_MIPSSTAR2, &MainEditor::OnBnClickedMipsstar2)
	ON_BN_CLICKED(IDC_MIPSSTAR1, &MainEditor::OnBnClickedMipsstar1)
	ON_BN_CLICKED(IDC_TOADSTAR3, &MainEditor::OnBnClickedToadstar3)
	ON_BN_CLICKED(IDC_TOADSTAR2, &MainEditor::OnBnClickedToadstar2)
	ON_BN_CLICKED(IDC_TOADSTAR1, &MainEditor::OnBnClickedToadstar1)
	ON_BN_CLICKED(IDC_PEACHSECRETAQUARIUMSTAR, &MainEditor::OnBnClickedPeachsecretaquariumstar)
	ON_BN_CLICKED(IDC_PEACHSLIDESTAR2, &MainEditor::OnBnClickedPeachslidestar2)
	ON_BN_CLICKED(IDC_PEACHSLIDESTAR, &MainEditor::OnBnClickedPeachslidestar)
	ON_BN_CLICKED(IDC_LVL2CANNONCHECKBOX, &MainEditor::OnBnClickedLvl2cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL2STAR7CHECKBOX, &MainEditor::OnBnClickedLvl2star7checkbox)
	ON_BN_CLICKED(IDC_LVL2STAR6CHECKBOX, &MainEditor::OnBnClickedLvl2star6checkbox)
	ON_BN_CLICKED(IDC_LVL2STAR5CHECKBOX, &MainEditor::OnBnClickedLvl2star5checkbox)
	ON_BN_CLICKED(IDC_LVL2STAR4CHECKBOX, &MainEditor::OnBnClickedLvl2star4checkbox)
	ON_BN_CLICKED(IDC_LVL2STAR3CHECKBOX, &MainEditor::OnBnClickedLvl2star3checkbox)
	ON_BN_CLICKED(IDC_LVL2STAR2CHECKBOX, &MainEditor::OnBnClickedLvl2star2checkbox)
	ON_BN_CLICKED(IDC_LVL2STAR1CHECKBOX, &MainEditor::OnBnClickedLvl2star1checkbox)
	ON_BN_CLICKED(IDC_LVL1CANNONCHECKBOX, &MainEditor::OnBnClickedLvl1cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL1STAR7CHECKBOX, &MainEditor::OnBnClickedLvl1star7checkbox)
	ON_BN_CLICKED(IDC_LVL1STAR6CHECKBOX, &MainEditor::OnBnClickedLvl1star6checkbox)
	ON_BN_CLICKED(IDC_LVL1STAR5CHECKBOX, &MainEditor::OnBnClickedLvl1star5checkbox)
	ON_BN_CLICKED(IDC_LVL1STAR4CHECKBOX, &MainEditor::OnBnClickedLvl1star4checkbox)
	ON_BN_CLICKED(IDC_LVL1STAR3CHECKBOX, &MainEditor::OnBnClickedLvl1star3checkbox)
	ON_BN_CLICKED(IDC_LVL15CANNONCHECKBOX, &MainEditor::OnBnClickedLvl15cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL15STAR7CHECKBOX, &MainEditor::OnBnClickedLvl15star7checkbox)
	ON_BN_CLICKED(IDC_LVL15STAR6CHECKBOX, &MainEditor::OnBnClickedLvl15star6checkbox)
	ON_BN_CLICKED(IDC_LVL15STAR5CHECKBOX, &MainEditor::OnBnClickedLvl15star5checkbox)
	ON_BN_CLICKED(IDC_LVL15STAR4CHECKBOX, &MainEditor::OnBnClickedLvl15star4checkbox)
	ON_BN_CLICKED(IDC_LVL15STAR3CHECKBOX, &MainEditor::OnBnClickedLvl15star3checkbox)
	ON_BN_CLICKED(IDC_LVL15STAR2CHECKBOX, &MainEditor::OnBnClickedLvl15star2checkbox)
	ON_BN_CLICKED(IDC_LVL15STAR1CHECKBOX, &MainEditor::OnBnClickedLvl15star1checkbox)
	ON_BN_CLICKED(IDC_LVL14CANNONCHECKBOX, &MainEditor::OnBnClickedLvl14cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL14STAR7CHECKBOX, &MainEditor::OnBnClickedLvl14star7checkbox)
	ON_BN_CLICKED(IDC_LVL14STAR6CHECKBOX, &MainEditor::OnBnClickedLvl14star6checkbox)
	ON_BN_CLICKED(IDC_LVL14STAR5CHECKBOX, &MainEditor::OnBnClickedLvl14star5checkbox)
	ON_BN_CLICKED(IDC_LVL14STAR4CHECKBOX, &MainEditor::OnBnClickedLvl14star4checkbox)
	ON_BN_CLICKED(IDC_LVL14STAR3CHECKBOX, &MainEditor::OnBnClickedLvl14star3checkbox)
	ON_BN_CLICKED(IDC_LVL14STAR2CHECKBOX, &MainEditor::OnBnClickedLvl14star2checkbox)
	ON_BN_CLICKED(IDC_LVL14STAR1CHECKBOX, &MainEditor::OnBnClickedLvl14star1checkbox)
	ON_BN_CLICKED(IDC_LVL13CANNONCHECKBOX, &MainEditor::OnBnClickedLvl13cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL13STAR7CHECKBOX, &MainEditor::OnBnClickedLvl13star7checkbox)
	ON_BN_CLICKED(IDC_LVL13STAR6CHECKBOX, &MainEditor::OnBnClickedLvl13star6checkbox)
	ON_BN_CLICKED(IDC_LVL13STAR5CHECKBOX, &MainEditor::OnBnClickedLvl13star5checkbox)
	ON_BN_CLICKED(IDC_LVL13STAR4CHECKBOX, &MainEditor::OnBnClickedLvl13star4checkbox)
	ON_BN_CLICKED(IDC_LVL13STAR3CHECKBOX, &MainEditor::OnBnClickedLvl13star3checkbox)
	ON_BN_CLICKED(IDC_LVL13STAR2CHECKBOX, &MainEditor::OnBnClickedLvl13star2checkbox)
	ON_BN_CLICKED(IDC_LVL13STAR1CHECKBOX, &MainEditor::OnBnClickedLvl13star1checkbox)
	ON_BN_CLICKED(IDC_LVL12CANNONCHECKBOX, &MainEditor::OnBnClickedLvl12cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL12STAR7CHECKBOX, &MainEditor::OnBnClickedLvl12star7checkbox)
	ON_BN_CLICKED(IDC_LVL12STAR6CHECKBOX, &MainEditor::OnBnClickedLvl12star6checkbox)
	ON_BN_CLICKED(IDC_LVL12STAR5CHECKBOX, &MainEditor::OnBnClickedLvl12star5checkbox)
	ON_BN_CLICKED(IDC_LVL12STAR4CHECKBOX, &MainEditor::OnBnClickedLvl12star4checkbox)
	ON_BN_CLICKED(IDC_LVL12STAR3CHECKBOX, &MainEditor::OnBnClickedLvl12star3checkbox)
	ON_BN_CLICKED(IDC_LVL12STAR2CHECKBOX, &MainEditor::OnBnClickedLvl12star2checkbox)
	ON_BN_CLICKED(IDC_LVL12STAR1CHECKBOX, &MainEditor::OnBnClickedLvl12star1checkbox)
	ON_BN_CLICKED(IDC_LVL11CANNONCHECKBOX, &MainEditor::OnBnClickedLvl11cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL11STAR7CHECKBOX, &MainEditor::OnBnClickedLvl11star7checkbox)
	ON_BN_CLICKED(IDC_LVL11STAR6CHECKBOX, &MainEditor::OnBnClickedLvl11star6checkbox)
	ON_BN_CLICKED(IDC_LVL11STAR5CHECKBOX, &MainEditor::OnBnClickedLvl11star5checkbox)
	ON_BN_CLICKED(IDC_LVL11STAR4CHECKBOX, &MainEditor::OnBnClickedLvl11star4checkbox)
	ON_BN_CLICKED(IDC_LVL11STAR3CHECKBOX, &MainEditor::OnBnClickedLvl11star3checkbox)
	ON_BN_CLICKED(IDC_LVL11STAR2CHECKBOX, &MainEditor::OnBnClickedLvl11star2checkbox)
	ON_BN_CLICKED(IDC_LVL11STAR1CHECKBOX, &MainEditor::OnBnClickedLvl11star1checkbox)
	ON_BN_CLICKED(IDC_LVL10CANNONCHECKBOX, &MainEditor::OnBnClickedLvl10cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL10STAR7CHECKBOX, &MainEditor::OnBnClickedLvl10star7checkbox)
	ON_BN_CLICKED(IDC_LVL10STAR6CHECKBOX, &MainEditor::OnBnClickedLvl10star6checkbox)
	ON_BN_CLICKED(IDC_LVL10STAR5CHECKBOX, &MainEditor::OnBnClickedLvl10star5checkbox)
	ON_BN_CLICKED(IDC_LVL10STAR4CHECKBOX, &MainEditor::OnBnClickedLvl10star4checkbox)
	ON_BN_CLICKED(IDC_LVL10STAR3CHECKBOX, &MainEditor::OnBnClickedLvl10star3checkbox)
	ON_BN_CLICKED(IDC_LVL10STAR2CHECKBOX, &MainEditor::OnBnClickedLvl10star2checkbox)
	ON_BN_CLICKED(IDC_LVL10STAR1CHECKBOX, &MainEditor::OnBnClickedLvl10star1checkbox)
	ON_BN_CLICKED(IDC_LVL9CANNONCHECKBOX, &MainEditor::OnBnClickedLvl9cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL9STAR7CHECKBOX, &MainEditor::OnBnClickedLvl9star7checkbox)
	ON_BN_CLICKED(IDC_LVL9STAR6CHECKBOX, &MainEditor::OnBnClickedLvl9star6checkbox)
	ON_BN_CLICKED(IDC_LVL9STAR5CHECKBOX, &MainEditor::OnBnClickedLvl9star5checkbox)
	ON_BN_CLICKED(IDC_LVL9STAR4CHECKBOX, &MainEditor::OnBnClickedLvl9star4checkbox)
	ON_BN_CLICKED(IDC_LVL9STAR3CHECKBOX, &MainEditor::OnBnClickedLvl9star3checkbox)
	ON_BN_CLICKED(IDC_LVL9STAR2CHECKBOX, &MainEditor::OnBnClickedLvl9star2checkbox)
	ON_BN_CLICKED(IDC_LVL9STAR1CHECKBOX, &MainEditor::OnBnClickedLvl9star1checkbox)
	ON_BN_CLICKED(IDC_LVL8CANNONCHECKBOX, &MainEditor::OnBnClickedLvl8cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL8STAR7CHECKBOX, &MainEditor::OnBnClickedLvl8star7checkbox)
	ON_BN_CLICKED(IDC_LVL8STAR6CHECKBOX, &MainEditor::OnBnClickedLvl8star6checkbox)
	ON_BN_CLICKED(IDC_LVL8STAR5CHECKBOX, &MainEditor::OnBnClickedLvl8star5checkbox)
	ON_BN_CLICKED(IDC_LVL8STAR4CHECKBOX, &MainEditor::OnBnClickedLvl8star4checkbox)
	ON_BN_CLICKED(IDC_LVL8STAR3CHECKBOX, &MainEditor::OnBnClickedLvl8star3checkbox)
	ON_BN_CLICKED(IDC_LVL8STAR2CHECKBOX, &MainEditor::OnBnClickedLvl8star2checkbox)
	ON_BN_CLICKED(IDC_LVL8STAR1CHECKBOX, &MainEditor::OnBnClickedLvl8star1checkbox)
	ON_BN_CLICKED(IDC_LVL7CANNONCHECKBOX, &MainEditor::OnBnClickedLvl7cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL7STAR7CHECKBOX, &MainEditor::OnBnClickedLvl7star7checkbox)
	ON_BN_CLICKED(IDC_LVL7STAR6CHECKBOX, &MainEditor::OnBnClickedLvl7star6checkbox)
	ON_BN_CLICKED(IDC_LVL7STAR5CHECKBOX, &MainEditor::OnBnClickedLvl7star5checkbox)
	ON_BN_CLICKED(IDC_LVLSTAR4CHECKBOX, &MainEditor::OnBnClickedLvlstar4checkbox)
	ON_BN_CLICKED(IDC_LVL7STAR3CHECKBOX, &MainEditor::OnBnClickedLvl7star3checkbox)
	ON_BN_CLICKED(IDC_LVL7STAR2CHECKBOX, &MainEditor::OnBnClickedLvl7star2checkbox)
	ON_BN_CLICKED(IDC_LVL7STAR1CHECKBOX, &MainEditor::OnBnClickedLvl7star1checkbox)
	ON_BN_CLICKED(IDC_LVL6CANNONCHECKBOX, &MainEditor::OnBnClickedLvl6cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL6STAR7CHECKBOX, &MainEditor::OnBnClickedLvl6star7checkbox)
	ON_BN_CLICKED(IDC_LVL6STAR6CHECKBOX, &MainEditor::OnBnClickedLvl6star6checkbox)
	ON_BN_CLICKED(IDC_LVL6STAR5CHECKBOX, &MainEditor::OnBnClickedLvl6star5checkbox)
	ON_BN_CLICKED(IDC_LVL6STAR4CHECKBOX, &MainEditor::OnBnClickedLvl6star4checkbox)
	ON_BN_CLICKED(IDC_LVL6STAR3CHECKBOX, &MainEditor::OnBnClickedLvl6star3checkbox)
	ON_BN_CLICKED(IDC_LVL6STAR2CHECKBOX, &MainEditor::OnBnClickedLvl6star2checkbox)
	ON_BN_CLICKED(IDC_LVL6STAR1CHECKBOX, &MainEditor::OnBnClickedLvl6star1checkbox)
	ON_BN_CLICKED(IDC_LVL5CANNONCHECKBOX, &MainEditor::OnBnClickedLvl5cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL5STAR7CHECKBOX, &MainEditor::OnBnClickedLvl5star7checkbox)
	ON_BN_CLICKED(IDC_LVL5STAR6CHECKBOX, &MainEditor::OnBnClickedLvl5star6checkbox)
	ON_BN_CLICKED(IDC_LVL5STAR5CHECKBOX, &MainEditor::OnBnClickedLvl5star5checkbox)
	ON_BN_CLICKED(IDC_LVL5STAR4CHECKBOX, &MainEditor::OnBnClickedLvl5star4checkbox)
	ON_BN_CLICKED(IDC_LVL5STAR3CHECKBOX, &MainEditor::OnBnClickedLvl5star3checkbox)
	ON_BN_CLICKED(IDC_LVL5STAR2CHECKBOX, &MainEditor::OnBnClickedLvl5star2checkbox)
	ON_BN_CLICKED(IDC_LVL5STAR1CHECKBOX, &MainEditor::OnBnClickedLvl5star1checkbox)
	ON_BN_CLICKED(IDC_LVL4CANNONCHECKBOX, &MainEditor::OnBnClickedLvl4cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL4STAR7CHECKBOX, &MainEditor::OnBnClickedLvl4star7checkbox)
	ON_BN_CLICKED(IDC_LVL4STAR6CHECKBOX, &MainEditor::OnBnClickedLvl4star6checkbox)
	ON_BN_CLICKED(IDC_LVL4STAR5CHECKBOX, &MainEditor::OnBnClickedLvl4star5checkbox)
	ON_BN_CLICKED(IDC_LVL4STAR4CHECKBOX, &MainEditor::OnBnClickedLvl4star4checkbox)
	ON_BN_CLICKED(IDC_LVL4STAR3CHECKBOX, &MainEditor::OnBnClickedLvl4star3checkbox)
	ON_BN_CLICKED(IDC_LVL4STAR2CHECKBOX, &MainEditor::OnBnClickedLvl4star2checkbox)
	ON_BN_CLICKED(IDC_LVL4STAR1CHECKBOX, &MainEditor::OnBnClickedLvl4star1checkbox)
	ON_BN_CLICKED(IDC_LVL3CANNONCHECKBOX, &MainEditor::OnBnClickedLvl3cannoncheckbox)
	ON_BN_CLICKED(IDC_LVL3STAR7CHECKBOX, &MainEditor::OnBnClickedLvl3star7checkbox)
	ON_BN_CLICKED(IDC_LVL3STAR6CHECKBOX, &MainEditor::OnBnClickedLvl3star6checkbox)
	ON_BN_CLICKED(IDC_LVL3STAR5CHECKBOX, &MainEditor::OnBnClickedLvl3star5checkbox)
	ON_BN_CLICKED(IDC_LVL3STAR4CHECKBOX, &MainEditor::OnBnClickedLvl3star4checkbox)
	ON_BN_CLICKED(IDC_LVL3STAR3CHECKBOX, &MainEditor::OnBnClickedLvl3star3checkbox)
	ON_BN_CLICKED(IDC_LVL3STAR2CHECKBOX, &MainEditor::OnBnClickedLvl3star2checkbox)
	ON_BN_CLICKED(IDC_LV3STAR1CHECKBOX, &MainEditor::OnBnClickedLv3star1checkbox)
	//ON_UPDATE_COMMAND_UI(ID_OPENFILE, &MainEditor::OnUpdateButton)
END_MESSAGE_MAP()

//Start of Main Editor Functions
void MainEditor::OnFileExit()
{
	PostMessage(WM_CLOSE);
}
// displays a message telling the user he can't use Open while editing a file
void MainEditor::OnMenuFileOpen()
{
	MessageBox(_T("Cannot open another file while one is being edited."), _T("Magic Star Editor Message."));
}

void MainEditor::OnUpdateButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(0);
}


///////////////////////////////////////////////
//				Read Binary File Code
//////////////////////////////////////////////

BOOL MainEditor::ReadFileFromDisk(CString path, unsigned char* masterBuff, unsigned char* tempbuff, UINT* bsize)
{
	//read the file from disk
	//the function returns the new Buffsize from the for loop with the exact size needed to write to the new file.
	//this is good but we can also use the "siseof(tbuff) after the copy.
	//Create a CFile that opens the file to read with the following atts
	CFile oFile;//create the open object
	oFile.Open(path, CFile::modeRead | CFile::typeBinary);//set the open atts
	*bsize = oFile.SeekToEnd();//set the size of the buff by seeking to end from current pos(start) and assign end to buffsize
	oFile.SeekToBegin();// return to the beginning of the file in order to copy from beginning to end.
	oFile.Read(masterBuff, *bsize);//read from the file and copy data to master buff, the buff size is our file length.
	
	
	//create a temp buffer using a for loop to copy the contents of the original master buffer byte by byte.
	//this temp buffer holds the file contents while it's being edited, and eventually saved replacind the original buffer.
	for (UINT i = 0; i < *bsize; i++)
	{
		tempbuff[i] = masterBuff[i];
	}
	//close the read file after copying to temp buffer
	oFile.Close();
	return 1;
}

void MainEditor::SaveFileToDisk(CString path, unsigned char* tempbuff, UINT bsize)
{
	CFile wFile;// create a CFile that will be used to Write to the final file.
	wFile.Open(path, CFile::modeWrite | CFile::typeBinary | CFile::modeCreate);//template for saving file.
	wFile.Write(tempbuff, bsize);//512 size for final
	wFile.Flush();
	wFile.Close();
}

void MainEditor::ChecksumCalculation(unsigned char* tempbuff, UINT16* chksum, UINT8* part1, UINT8* part2, UINT savslot)
{
	//use pointers in order to directly modify the original ref value, otherwise it could create a copy that might be empty, not necessary in this situation.
	switch (savslot)
	{
		// checkum calculation for save slot 1
	case 1:
		for (UINT i = 0; i < 54; i++)
		{
			*chksum += tempbuff[i];
		}
		*part1 = static_cast<UINT8>((*chksum & 0xFF00) >> 8);
		*part2 = static_cast<UINT8>(*chksum & 0x00FF);
		tempbuff[54] = *part1;
		tempbuff[55] = *part2;
		*chksum = 0000; //always zero the chksum pointer after it has been calculated otherwise it will be incremented if the user opens another file after closing one.
		break;
		// checksum calculation for save slot 2
	case 2:
		for (UINT i = 112; i < 166; i++)
		{
			*chksum += tempbuff[i];
		}
		*part1 = static_cast<UINT8>((*chksum & 0xFF00) >> 8);
		*part2 = static_cast<UINT8>(*chksum & 0x00FF);
		tempbuff[166] = *part1;
		tempbuff[167] = *part2;
		break;
		
		// checksum calculation for save slot 3
	case 3:
		for (UINT i = 224; i < 278; i++)
		{
			*chksum += tempbuff[i];
		}
		*part1 = static_cast<UINT8>((*chksum & 0xFF00) >> 8);
		*part2 = static_cast<UINT8>(*chksum & 0x00FF);
		tempbuff[278] = *part1;
		tempbuff[279] = *part2;
		break;
		
		//  checksum calculation for save slot 4
	case 4:
		for (UINT i = 336; i < 390; i++)
		{
			*chksum += tempbuff[i];
		}
		*part1 = static_cast<UINT8>((*chksum & 0xFF00) >> 8);
		*part2 = static_cast<UINT8>(*chksum & 0x00FF);
		tempbuff[390] = *part1;
		tempbuff[391] = *part2;
		break;
	}
}

// lvl Hex to Binary 
CString MainEditor::HexToString(unsigned char* tempbuff, UINT lvloffset)
{
	UINT hextobin = tempbuff[lvloffset];
	std::bitset<8> set(hextobin);
	std::string tempbin = set.to_string();
	CString ctempbin(tempbin.c_str());
	return ctempbin;
}

UINT8 MainEditor::BinaryStringToHex(CString lvlbinstring)
{
	CT2A templvl(lvlbinstring);// converts our CString into a std::string
	std::string tempbin(templvl);
	std::bitset<8> set2(tempbin);//converts our std::string into binary
	UINT8 bin2byte = static_cast<UINT8>(set2.to_ulong());//converts our binary into a UINT8/BYTE
	return bin2byte;
}



void MainEditor::SetCheckBoxesOnStart()
{	
	// Leve1 Star 1
	CButton* check1 = (CButton*)GetDlgItem(IDC_LVL1STAR1CHECKBOX);
	if (lvl1bits[7] == '1')
		check1->SetCheck(1);
	else 
		check1->SetCheck(0);
	// Level 1 Star 2
	CButton* check2 = (CButton*)GetDlgItem(IDC_LVL1STAR2CHECKBOX);
	if (lvl1bits[6] == '1')
		check2->SetCheck(1);
	else
		check2->SetCheck(0);
	//Level 1 Star 3
	CButton* check3 = (CButton*)GetDlgItem(IDC_LVL1STAR3CHECKBOX);
	if (lvl1bits[5] == '1')
		check3->SetCheck(1);
	else
		check3->SetCheck(0);

	// Level 1 Star 4
	CButton* check4 = (CButton*)GetDlgItem(IDC_LVL1STAR4CHECKBOX);
	if (lvl1bits[4] == '1')
		check4->SetCheck(1);
	else
		check4->SetCheck(0);

	// Leve1 Star 5
	CButton* check5 = (CButton*)GetDlgItem(IDC_LVL1STAR5CHECKBOX);
	if (lvl1bits[3] == '1')
		check5->SetCheck(1);
	else
		check5->SetCheck(0);
	// Level 1 Star 6
	CButton* check6 = (CButton*)GetDlgItem(IDC_LVL1STAR6CHECKBOX);
	if (lvl1bits[2] == '1')
		check6->SetCheck(1);
	else
		check6->SetCheck(0);
	//Level 1 Star 7
	CButton* check7 = (CButton*)GetDlgItem(IDC_LVL1STAR7CHECKBOX);
	if (lvl1bits[1] == '1')
		check7->SetCheck(1);
	else
		check7->SetCheck(0);

	// Level 1 Cannon
	CButton* check8 = (CButton*)GetDlgItem(IDC_LVL1CANNONCHECKBOX);
	if (lvl1bits[0] == '1')
		check8->SetCheck(1);
	else
		check8->SetCheck(0);

//// LEVEL 2 STARS 

	// Leve2 Star 1
	CButton* check9 = (CButton*)GetDlgItem(IDC_LVL2STAR1CHECKBOX);
	if (lvl2bits[7] == '1')
		check9->SetCheck(1);
	else
		check9->SetCheck(0);
	// Level 2 Star 2
	CButton* check10 = (CButton*)GetDlgItem(IDC_LVL2STAR2CHECKBOX);
	if (lvl2bits[6] == '1')
		check10->SetCheck(1);
	else
		check10->SetCheck(0);
	//Level 2 Star 3
	CButton* check11 = (CButton*)GetDlgItem(IDC_LVL2STAR3CHECKBOX);
	if (lvl2bits[5] == '1')
		check11->SetCheck(1);
	else
		check11->SetCheck(0);

	// Level 2 Star 4
	CButton* check12 = (CButton*)GetDlgItem(IDC_LVL2STAR4CHECKBOX);
	if (lvl12bits[4] == '1')
		check12->SetCheck(1);
	else
		check12->SetCheck(0);

	// Leve2 Star 5
	CButton* check13 = (CButton*)GetDlgItem(IDC_LVL2STAR5CHECKBOX);
	if (lvl2bits[3] == '1')
		check13->SetCheck(1);
	else
		check13->SetCheck(0);
	// Level 2 Star 6
	CButton* check14 = (CButton*)GetDlgItem(IDC_LVL2STAR6CHECKBOX);
	if (lvl2bits[2] == '1')
		check14->SetCheck(1);
	else
		check14->SetCheck(0);
	//Level 2 Star 7
	CButton* check15 = (CButton*)GetDlgItem(IDC_LVL2STAR7CHECKBOX);
	if (lvl2bits[1] == '1')
		check15->SetCheck(1);
	else
		check15->SetCheck(0);

	// Level 2 Cannon
	CButton* check16 = (CButton*)GetDlgItem(IDC_LVL2CANNONCHECKBOX);
	if (lvl2bits[0] == '1')
		check16->SetCheck(1);
	else
		check16->SetCheck(0);

///////// LEVEL 3

	// Leve3 Star 1
	CButton* check17 = (CButton*)GetDlgItem(IDC_LV3STAR1CHECKBOX);
	if (lvl3bits[7] == '1')
		check17->SetCheck(1);
	else
		check17->SetCheck(0);
	// Leve3 1 Star 2
	CButton* check18 = (CButton*)GetDlgItem(IDC_LVL3STAR2CHECKBOX);
	if (lvl3bits[6] == '1')
		check18->SetCheck(1);
	else
		check18->SetCheck(0);
	//Level 3 Star 3
	CButton* check19 = (CButton*)GetDlgItem(IDC_LVL3STAR3CHECKBOX);
	if (lvl3bits[5] == '1')
		check19->SetCheck(1);
	else
		check19->SetCheck(0);

	// Level 3 Star 4
	CButton* check20 = (CButton*)GetDlgItem(IDC_LVL3STAR4CHECKBOX);
	if (lvl3bits[4] == '1')
		check20->SetCheck(1);
	else
		check20->SetCheck(0);

	// Leve 3 Star 5
	CButton* check21 = (CButton*)GetDlgItem(IDC_LVL3STAR5CHECKBOX);
	if (lvl3bits[3] == '1')
		check21->SetCheck(1);
	else
		check21->SetCheck(0);
	// Level 3 Star 6
	CButton* check22 = (CButton*)GetDlgItem(IDC_LVL3STAR6CHECKBOX);
	if (lvl3bits[2] == '1')
		check22->SetCheck(1);
	else
		check22->SetCheck(0);
	//Level 3 Star 7
	CButton* check23 = (CButton*)GetDlgItem(IDC_LVL3STAR7CHECKBOX);
	if (lvl3bits[1] == '1')
		check23->SetCheck(1);
	else
		check23->SetCheck(0);

	// Level 3 Cannon
	CButton* check24 = (CButton*)GetDlgItem(IDC_LVL3CANNONCHECKBOX);
	if (lvl3bits[0] == '1')
		check24->SetCheck(1);
	else
		check24->SetCheck(0);

	//// LEVEL 4 STARS 

		// Leve4 Star 1
	CButton* check25 = (CButton*)GetDlgItem(IDC_LVL4STAR1CHECKBOX);
	if (lvl4bits[7] == '1')
		check25->SetCheck(1);
	else
		check25->SetCheck(0);
	// Level 4 Star 2
	CButton* check26 = (CButton*)GetDlgItem(IDC_LVL4STAR2CHECKBOX);
	if (lvl4bits[6] == '1')
		check26->SetCheck(1);
	else
		check26->SetCheck(0);
	//Level 4 Star 3
	CButton* check27 = (CButton*)GetDlgItem(IDC_LVL4STAR3CHECKBOX);
	if (lvl4bits[5] == '1')
		check27->SetCheck(1);
	else
		check27->SetCheck(0);

	// Level 4 Star 4
	CButton* check28 = (CButton*)GetDlgItem(IDC_LVL4STAR4CHECKBOX);
	if (lvl4bits[4] == '1')
		check28->SetCheck(1);
	else
		check28->SetCheck(0);

	// Leve 4 Star 5
	CButton* check29 = (CButton*)GetDlgItem(IDC_LVL4STAR5CHECKBOX);
	if (lvl4bits[3] == '1')
		check29->SetCheck(1);
	else
		check29->SetCheck(0);
	// Level 4 Star 6
	CButton* check30 = (CButton*)GetDlgItem(IDC_LVL4STAR6CHECKBOX);
	if (lvl4bits[2] == '1')
		check30->SetCheck(1);
	else
		check30->SetCheck(0);
	//Level 4 Star 7
	CButton* check31 = (CButton*)GetDlgItem(IDC_LVL4STAR7CHECKBOX);
	if (lvl4bits[1] == '1')
		check31->SetCheck(1);
	else
		check31->SetCheck(0);

	// Level 4 Cannon
	CButton* check32 = (CButton*)GetDlgItem(IDC_LVL4CANNONCHECKBOX);
	if (lvl4bits[0] == '1')
		check32->SetCheck(1);
	else
		check32->SetCheck(0);

	// Level 5

	// Leve5 Star 1
	CButton* check33 = (CButton*)GetDlgItem(IDC_LVL5STAR1CHECKBOX);
	if (lvl5bits[7] == '1')
		check33->SetCheck(1);
	else
		check33->SetCheck(0);
	// Level 5 Star 2
	CButton* check34 = (CButton*)GetDlgItem(IDC_LVL5STAR2CHECKBOX);
	if (lvl5bits[6] == '1')
		check34->SetCheck(1);
	else
		check34->SetCheck(0);
	//Level 5 Star 3
	CButton* check35 = (CButton*)GetDlgItem(IDC_LVL5STAR3CHECKBOX);
	if (lvl5bits[5] == '1')
		check35->SetCheck(1);
	else
		check35->SetCheck(0);

	// Level 5 Star 4
	CButton* check36 = (CButton*)GetDlgItem(IDC_LVL5STAR4CHECKBOX);
	if (lvl5bits[4] == '1')
		check36->SetCheck(1);
	else
		check36->SetCheck(0);

	// Leve 5 Star 5
	CButton* check37 = (CButton*)GetDlgItem(IDC_LVL5STAR5CHECKBOX);
	if (lvl5bits[3] == '1')
		check37->SetCheck(1);
	else
		check37->SetCheck(0);
	// Level 5 Star 6
	CButton* check38 = (CButton*)GetDlgItem(IDC_LVL5STAR6CHECKBOX);
	if (lvl5bits[2] == '1')
		check38->SetCheck(1);
	else
		check38->SetCheck(0);
	//Level 5 Star 7
	CButton* check39 = (CButton*)GetDlgItem(IDC_LVL5STAR7CHECKBOX);
	if (lvl5bits[1] == '1')
		check39->SetCheck(1);
	else
		check39->SetCheck(0);

	// Level 5 Cannon
	CButton* check40 = (CButton*)GetDlgItem(IDC_LVL5CANNONCHECKBOX);
	if (lvl5bits[0] == '1')
		check40->SetCheck(1);
	else
		check40->SetCheck(0);

	//// LEVEL 6 STARS 

	// Leve 6 Star 1
	CButton* check41 = (CButton*)GetDlgItem(IDC_LVL6STAR1CHECKBOX);
	if (lvl6bits[7] == '1')
		check41->SetCheck(1);
	else
		check41->SetCheck(0);
	// Leve 6 Star 2
	CButton* check42 = (CButton*)GetDlgItem(IDC_LVL6STAR2CHECKBOX);
	if (lvl6bits[6] == '1')
		check42->SetCheck(1);
	else
		check42->SetCheck(0);
	//Level 6 Star 3
	CButton* check43 = (CButton*)GetDlgItem(IDC_LVL6STAR3CHECKBOX);
	if (lvl6bits[5] == '1')
		check43->SetCheck(1);
	else
		check43->SetCheck(0);

	// Level 6 Star 4
	CButton* check44 = (CButton*)GetDlgItem(IDC_LVL6STAR4CHECKBOX);
	if (lvl6bits[4] == '1')
		check44->SetCheck(1);
	else
		check44->SetCheck(0);

	// Leve 6 Star 5
	CButton* check45 = (CButton*)GetDlgItem(IDC_LVL6STAR5CHECKBOX);
	if (lvl6bits[3] == '1')
		check45->SetCheck(1);
	else
		check45->SetCheck(0);
	// Leve 6 2 Star 6
	CButton* check46 = (CButton*)GetDlgItem(IDC_LVL6STAR6CHECKBOX);
	if (lvl6bits[2] == '1')
		check46->SetCheck(1);
	else
		check46->SetCheck(0);
	//Level 6 Star 7
	CButton* check47 = (CButton*)GetDlgItem(IDC_LVL6STAR7CHECKBOX);
	if (lvl6bits[1] == '1')
		check47->SetCheck(1);
	else
		check47->SetCheck(0);

	// Leve 6 Cannon
	CButton* check48 = (CButton*)GetDlgItem(IDC_LVL6CANNONCHECKBOX);
	if (lvl6bits[0] == '1')
		check48->SetCheck(1);
	else
		check48->SetCheck(0);

	///////// LEVEL 7

		// Leve3 Star 1
	CButton* check49 = (CButton*)GetDlgItem(IDC_LVL7STAR1CHECKBOX);
	if (lvl7bits[7] == '1')
		check49->SetCheck(1);
	else
		check49->SetCheck(0);
	// Leve3 1 Star 2
	CButton* check50 = (CButton*)GetDlgItem(IDC_LVL7STAR2CHECKBOX);
	if (lvl7bits[6] == '1')
		check50->SetCheck(1);
	else
		check50->SetCheck(0);
	//Level 3 Star 3
	CButton* check51 = (CButton*)GetDlgItem(IDC_LVL7STAR3CHECKBOX);
	if (lvl7bits[5] == '1')
		check51->SetCheck(1);
	else
		check51->SetCheck(0);

	// Level 3 Star 4
	CButton* check52 = (CButton*)GetDlgItem(IDC_LVLSTAR4CHECKBOX);
	if (lvl7bits[4] == '1')
		check52->SetCheck(1);
	else
		check52->SetCheck(0);

	// Leve 3 Star 5
	CButton* check53 = (CButton*)GetDlgItem(IDC_LVL7STAR5CHECKBOX);
	if (lvl7bits[3] == '1')
		check53->SetCheck(1);
	else
		check53->SetCheck(0);
	// Level 3 Star 6
	CButton* check54 = (CButton*)GetDlgItem(IDC_LVL7STAR6CHECKBOX);
	if (lvl7bits[2] == '1')
		check54->SetCheck(1);
	else
		check54->SetCheck(0);
	//Level 3 Star 7
	CButton* check55 = (CButton*)GetDlgItem(IDC_LVL7STAR7CHECKBOX);
	if (lvl7bits[1] == '1')
		check55->SetCheck(1);
	else
		check55->SetCheck(0);

	// Level 7 Cannon
	CButton* check56 = (CButton*)GetDlgItem(IDC_LVL7CANNONCHECKBOX);
	if (lvl7bits[0] == '1')
		check56->SetCheck(1);
	else
		check56->SetCheck(0);

	//// LEVEL 8 STARS 

		// Leve4 Star 1
	CButton* check57 = (CButton*)GetDlgItem(IDC_LVL8STAR1CHECKBOX);
	if (lvl8bits[7] == '1')
		check57->SetCheck(1);
	else
		check57->SetCheck(0);
	// Level 4 Star 2
	CButton* check58 = (CButton*)GetDlgItem(IDC_LVL8STAR2CHECKBOX);
	if (lvl8bits[6] == '1')
		check58->SetCheck(1);
	else
		check58->SetCheck(0);
	//Level 4 Star 3
	CButton* check59 = (CButton*)GetDlgItem(IDC_LVL8STAR3CHECKBOX);
	if (lvl8bits[5] == '1')
		check59->SetCheck(1);
	else
		check59->SetCheck(0);

	// Level 4 Star 4
	CButton* check60 = (CButton*)GetDlgItem(IDC_LVL8STAR4CHECKBOX);
	if (lvl8bits[4] == '1')
		check60->SetCheck(1);
	else
		check60->SetCheck(0);

	// Leve 4 Star 5
	CButton* check61 = (CButton*)GetDlgItem(IDC_LVL8STAR5CHECKBOX);
	if (lvl8bits[3] == '1')
		check61->SetCheck(1);
	else
		check61->SetCheck(0);
	// Level 4 Star 6
	CButton* check62 = (CButton*)GetDlgItem(IDC_LVL8STAR6CHECKBOX);
	if (lvl8bits[2] == '1')
		check62->SetCheck(1);
	else
		check62->SetCheck(0);
	//Level 4 Star 7
	CButton* check63 = (CButton*)GetDlgItem(IDC_LVL8STAR7CHECKBOX);
	if (lvl8bits[1] == '1')
		check63->SetCheck(1);
	else
		check63->SetCheck(0);

	// Level 4 Cannon
	CButton* check121 = (CButton*)GetDlgItem(IDC_LVL8CANNONCHECKBOX);
	if (lvl8bits[0] == '1')
		check121->SetCheck(1);
	else
		check121->SetCheck(0);

	//////// LEVEL 9

	// Leve1 Star 1
	CButton* check64 = (CButton*)GetDlgItem(IDC_LVL9STAR1CHECKBOX);
	if (lvl9bits[7] == '1')
		check64->SetCheck(1);
	else
		check64->SetCheck(0);
	// Level 1 Star 2
	CButton* check65 = (CButton*)GetDlgItem(IDC_LVL9STAR2CHECKBOX);
	if (lvl9bits[6] == '1')
		check65->SetCheck(1);
	else
		check65->SetCheck(0);
	//Level 1 Star 3
	CButton* check66 = (CButton*)GetDlgItem(IDC_LVL9STAR3CHECKBOX);
	if (lvl9bits[5] == '1')
		check66->SetCheck(1);
	else
		check66->SetCheck(0);

	// Level 1 Star 4
	CButton* check67 = (CButton*)GetDlgItem(IDC_LVL9STAR4CHECKBOX);
	if (lvl9bits[4] == '1')
		check67->SetCheck(1);
	else
		check67->SetCheck(0);

	// Leve1 Star 5
	CButton* check68 = (CButton*)GetDlgItem(IDC_LVL9STAR5CHECKBOX);
	if (lvl9bits[3] == '1')
		check68->SetCheck(1);
	else
		check68->SetCheck(0);
	// Level 1 Star 6
	CButton* check69 = (CButton*)GetDlgItem(IDC_LVL9STAR6CHECKBOX);
	if (lvl9bits[2] == '1')
		check69->SetCheck(1);
	else
		check69->SetCheck(0);
	//Level 1 Star 7
	CButton* check70 = (CButton*)GetDlgItem(IDC_LVL9STAR7CHECKBOX);
	if (lvl9bits[1] == '1')
		check70->SetCheck(1);
	else
		check70->SetCheck(0);

	// Level 1 Cannon
	CButton* check71 = (CButton*)GetDlgItem(IDC_LVL9CANNONCHECKBOX);
	if (lvl9bits[0] == '1')
		check71->SetCheck(1);
	else
		check71->SetCheck(0);

	//// LEVEL 10 STARS 

		// Leve10 Star 1
	CButton* check72 = (CButton*)GetDlgItem(IDC_LVL10STAR1CHECKBOX);
	if (lvl10bits[7] == '1')
		check72->SetCheck(1);
	else
		check72->SetCheck(0);
	// Level 2 Star 2
	CButton* check73 = (CButton*)GetDlgItem(IDC_LVL10STAR2CHECKBOX);
	if (lvl10bits[6] == '1')
		check73->SetCheck(1);
	else
		check73->SetCheck(0);
	//Level 2 Star 3
	CButton* check74 = (CButton*)GetDlgItem(IDC_LVL10STAR3CHECKBOX);
	if (lvl10bits[5] == '1')
		check74->SetCheck(1);
	else
		check74->SetCheck(0);

	// Level 2 Star 4
	CButton* check75 = (CButton*)GetDlgItem(IDC_LVL10STAR4CHECKBOX);
	if (lvl10bits[4] == '1')
		check75->SetCheck(1);
	else
		check75->SetCheck(0);

	// Leve2 Star 5
	CButton* check76 = (CButton*)GetDlgItem(IDC_LVL10STAR5CHECKBOX);
	if (lvl10bits[3] == '1')
		check76->SetCheck(1);
	else
		check76->SetCheck(0);
	// Level 2 Star 6
	CButton* check77 = (CButton*)GetDlgItem(IDC_LVL10STAR6CHECKBOX);
	if (lvl10bits[2] == '1')
		check77->SetCheck(1);
	else
		check77->SetCheck(0);
	//Level 2 Star 7
	CButton* check78 = (CButton*)GetDlgItem(IDC_LVL10STAR7CHECKBOX);
	if (lvl10bits[1] == '1')
		check78->SetCheck(1);
	else
		check78->SetCheck(0);

	// Level 2 Cannon
	CButton* check79 = (CButton*)GetDlgItem(IDC_LVL10CANNONCHECKBOX);
	if (lvl10bits[0] == '1')
		check79->SetCheck(1);
	else
		check79->SetCheck(0);

	///////// LEVEL 11

		// Leve3 Star 1
	CButton* check80 = (CButton*)GetDlgItem(IDC_LVL11STAR1CHECKBOX);
	if (lvl11bits[7] == '1')
		check80->SetCheck(1);
	else
		check80->SetCheck(0);
	// Leve3 1 Star 2
	CButton* check81 = (CButton*)GetDlgItem(IDC_LVL11STAR2CHECKBOX);
	if (lvl11bits[6] == '1')
		check81->SetCheck(1);
	else
		check81->SetCheck(0);
	//Level 3 Star 3
	CButton* check82= (CButton*)GetDlgItem(IDC_LVL11STAR3CHECKBOX);
	if (lvl11bits[5] == '1')
		check82->SetCheck(1);
	else
		check82->SetCheck(0);

	// Level 3 Star 4
	CButton* check83 = (CButton*)GetDlgItem(IDC_LVL11STAR4CHECKBOX);
	if (lvl11bits[4] == '1')
		check83->SetCheck(1);
	else
		check83->SetCheck(0);

	// Leve 3 Star 5
	CButton* check84 = (CButton*)GetDlgItem(IDC_LVL11STAR5CHECKBOX);
	if (lvl11bits[3] == '1')
		check84->SetCheck(1);
	else
		check84->SetCheck(0);
	// Level 3 Star 6
	CButton* check85 = (CButton*)GetDlgItem(IDC_LVL11STAR6CHECKBOX);
	if (lvl11bits[2] == '1')
		check85->SetCheck(1);
	else
		check85->SetCheck(0);
	//Level 3 Star 7
	CButton* check86 = (CButton*)GetDlgItem(IDC_LVL11STAR7CHECKBOX);
	if (lvl11bits[1] == '1')
		check86->SetCheck(1);
	else
		check86->SetCheck(0);

	// Level 3 Cannon
	CButton* check87 = (CButton*)GetDlgItem(IDC_LVL11CANNONCHECKBOX);
	if (lvl11bits[0] == '1')
		check87->SetCheck(1);
	else
		check87->SetCheck(0);

	//// LEVEL 12 STARS 

		// Leve4 Star 1
	CButton* check88 = (CButton*)GetDlgItem(IDC_LVL12STAR1CHECKBOX);
	if (lvl2bits[7] == '1')
		check88->SetCheck(1);
	else
		check88->SetCheck(0);
	// Level 4 Star 2
	CButton* check89 = (CButton*)GetDlgItem(IDC_LVL12STAR2CHECKBOX);
	if (lvl12bits[6] == '1')
		check89->SetCheck(1);
	else
		check89->SetCheck(0);
	//Level 4 Star 3
	CButton* check90 = (CButton*)GetDlgItem(IDC_LVL12STAR3CHECKBOX);
	if (lvl12bits[5] == '1')
		check90->SetCheck(1);
	else
		check90->SetCheck(0);

	// Level 4 Star 4
	CButton* check91 = (CButton*)GetDlgItem(IDC_LVL12STAR4CHECKBOX);
	if (lvl12bits[4] == '1')
		check91->SetCheck(1);
	else
		check91->SetCheck(0);

	// Leve 4 Star 5
	CButton* check92 = (CButton*)GetDlgItem(IDC_LVL12STAR5CHECKBOX);
	if (lvl12bits[3] == '1')
		check92->SetCheck(1);
	else
		check92->SetCheck(0);
	// Level 4 Star 6
	CButton* check93 = (CButton*)GetDlgItem(IDC_LVL12STAR6CHECKBOX);
	if (lvl12bits[2] == '1')
		check93->SetCheck(1);
	else
		check93->SetCheck(0);
	//Level 4 Star 7
	CButton* check94 = (CButton*)GetDlgItem(IDC_LVL12STAR7CHECKBOX);
	if (lvl12bits[1] == '1')
		check94->SetCheck(1);
	else
		check94->SetCheck(0);

	// Level 4 Cannon
	CButton* check95 = (CButton*)GetDlgItem(IDC_LVL12CANNONCHECKBOX);
	if (lvl12bits[0] == '1')
		check95->SetCheck(1);
	else
		check95->SetCheck(0);

	///// LEVEL 13

	// Leve13 Star 1
	CButton* check96 = (CButton*)GetDlgItem(IDC_LVL13STAR1CHECKBOX);
	if (lvl13bits[7] == '1')
		check96->SetCheck(1);
	else
		check96->SetCheck(0);
	// Level 1 Star 2
	CButton* check97 = (CButton*)GetDlgItem(IDC_LVL13STAR2CHECKBOX);
	if (lvl13bits[6] == '1')
		check97->SetCheck(1);
	else
		check97->SetCheck(0);
	//Level 1 Star 3
	CButton* check98 = (CButton*)GetDlgItem(IDC_LVL13STAR3CHECKBOX);
	if (lvl13bits[5] == '1')
		check98->SetCheck(1);
	else
		check98->SetCheck(0);

	// Level 1 Star 4
	CButton* check99 = (CButton*)GetDlgItem(IDC_LVL13STAR4CHECKBOX);
	if (lvl13bits[4] == '1')
		check99->SetCheck(1);
	else
		check99->SetCheck(0);

	// Leve1 Star 5
	CButton* check100 = (CButton*)GetDlgItem(IDC_LVL13STAR5CHECKBOX);
	if (lvl13bits[3] == '1')
		check100->SetCheck(1);
	else
		check100->SetCheck(0);
	// Level 1 Star 6
	CButton* check101 = (CButton*)GetDlgItem(IDC_LVL13STAR6CHECKBOX);
	if (lvl13bits[2] == '1')
		check101->SetCheck(1);
	else
		check101->SetCheck(0);
	//Level 1 Star 7
	CButton* check102 = (CButton*)GetDlgItem(IDC_LVL13STAR7CHECKBOX);
	if (lvl13bits[1] == '1')
		check102->SetCheck(1);
	else
		check102->SetCheck(0);

	// Level 1 Cannon
	CButton* check103 = (CButton*)GetDlgItem(IDC_LVL13CANNONCHECKBOX);
	if (lvl13bits[0] == '1')
		check103->SetCheck(1);
	else
		check103->SetCheck(0);

	//// LEVEL 14 STARS 

		// Leve2 Star 1
	CButton* check104 = (CButton*)GetDlgItem(IDC_LVL14STAR1CHECKBOX);
	if (lvl14bits[7] == '1')
		check104->SetCheck(1);
	else
		check104->SetCheck(0);
	// Level 2 Star 2
	CButton* check105 = (CButton*)GetDlgItem(IDC_LVL14STAR2CHECKBOX);
	if (lvl14bits[6] == '1')
		check105->SetCheck(1);
	else
		check105->SetCheck(0);
	//Level 2 Star 3
	CButton* check106 = (CButton*)GetDlgItem(IDC_LVL14STAR3CHECKBOX);
	if (lvl14bits[5] == '1')
		check106->SetCheck(1);
	else
		check106->SetCheck(0);

	// Level 2 Star 4
	CButton* check107 = (CButton*)GetDlgItem(IDC_LVL14STAR4CHECKBOX);
	if (lvl14bits[4] == '1')
		check107->SetCheck(1);
	else
		check107->SetCheck(0);

	// Leve2 Star 5
	CButton* check108 = (CButton*)GetDlgItem(IDC_LVL14STAR5CHECKBOX);
	if (lvl14bits[3] == '1')
		check108->SetCheck(1);
	else
		check108->SetCheck(0);
	// Level 2 Star 6
	CButton* check109 = (CButton*)GetDlgItem(IDC_LVL14STAR6CHECKBOX);
	if (lvl14bits[2] == '1')
		check109->SetCheck(1);
	else
		check109->SetCheck(0);
	//Level 2 Star 7
	CButton* check110 = (CButton*)GetDlgItem(IDC_LVL14STAR7CHECKBOX);
	if (lvl14bits[1] == '1')
		check110->SetCheck(1);
	else
		check110->SetCheck(0);

	// Level 2 Cannon
	CButton* check111 = (CButton*)GetDlgItem(IDC_LVL14CANNONCHECKBOX);
	if (lvl14bits[0] == '1')
		check111->SetCheck(1);
	else
		check111->SetCheck(0);

	///////// LEVEL 15

		// Leve3 Star 1
	CButton* check112 = (CButton*)GetDlgItem(IDC_LVL15STAR1CHECKBOX);
	if (lvl15bits[7] == '1')
		check112->SetCheck(1);
	else
		check112->SetCheck(0);
	// Leve3 1 Star 2
	CButton* check113 = (CButton*)GetDlgItem(IDC_LVL15STAR2CHECKBOX);
	if (lvl15bits[6] == '1')
		check113->SetCheck(1);
	else
		check113->SetCheck(0);
	//Level 3 Star 3
	CButton* check114 = (CButton*)GetDlgItem(IDC_LVL15STAR3CHECKBOX);
	if (lvl15bits[5] == '1')
		check114->SetCheck(1);
	else
		check114->SetCheck(0);

	// Level 3 Star 4
	CButton* check115 = (CButton*)GetDlgItem(IDC_LVL15STAR4CHECKBOX);
	if (lvl15bits[4] == '1')
		check115->SetCheck(1);
	else
		check115->SetCheck(0);

	// Leve 3 Star 5
	CButton* check116 = (CButton*)GetDlgItem(IDC_LVL15STAR5CHECKBOX);
	if (lvl15bits[3] == '1')
		check116->SetCheck(1);
	else
		check116->SetCheck(0);
	// Level 3 Star 6
	CButton* check118 = (CButton*)GetDlgItem(IDC_LVL15STAR6CHECKBOX);
	if (lvl15bits[2] == '1')
		check118->SetCheck(1);
	else
		check118->SetCheck(0);
	//Level 3 Star 7
	CButton* check119 = (CButton*)GetDlgItem(IDC_LVL15STAR7CHECKBOX);
	if (lvl15bits[1] == '1')
		check119->SetCheck(1);
	else
		check119->SetCheck(0);

	// Level 3 Cannon
	CButton* check120 = (CButton*)GetDlgItem(IDC_LVL15CANNONCHECKBOX);
	if (lvl15bits[0] == '1')
		check120->SetCheck(1);
	else
		check120->SetCheck(0);

	// Secret Star Check boxes
	CButton* check122 = (CButton*)GetDlgItem(IDC_PEACHSLIDESTAR);
	if (PeachSlideStars[7] == '1')
		check122->SetCheck(1);
	else
		check122->SetCheck(0);

	CButton* check123 = (CButton*)GetDlgItem(IDC_PEACHSLIDESTAR2);
	if (PeachSlideStars[6] == '1')
		check123->SetCheck(1);
	else
		check123->SetCheck(0);

	CButton* check124 = (CButton*)GetDlgItem(IDC_PEACHSECRETAQUARIUMSTAR);
	if (tbuff[35] == 0x01)
		check124->SetCheck(1);
	else
		check124->SetCheck(0);

	CButton* check125 = (CButton*)GetDlgItem(IDC_TOADSTAR1);
	if (ToadMipsStars[7] == '1')
		check125->SetCheck(1);
	else
		check125->SetCheck(0);
	
	CButton* check126 = (CButton*)GetDlgItem(IDC_TOADSTAR2);
	if (ToadMipsStars[5] == '1')
		check126->SetCheck(1);
	else
		check126->SetCheck(0);

	CButton* check127 = (CButton*)GetDlgItem(IDC_TOADSTAR3);
	if (ToadMipsStars[4] == '1')
		check127->SetCheck(1);
	else
		check127->SetCheck(0);

	CButton* check128 = (CButton*)GetDlgItem(IDC_MIPSSTAR1);
	if (ToadMipsStars[6] == '1')
		check128->SetCheck(1);
	else
		check128->SetCheck(0);

	CButton* check129 = (CButton*)GetDlgItem(IDC_MIPSSTAR2);
	if (ToadMipsStars[3] == '1')
		check129->SetCheck(1);
	else
		check129->SetCheck(0);

	CButton* check130 = (CButton*)GetDlgItem(IDC_CAVERNMETALCAPSTAR);
	if (tbuff[31] == 0x01)
		check130->SetCheck(1);
	else
		check130->SetCheck(0);

	CButton* check131 = (CButton*)GetDlgItem(IDC_TOWERWINGCAPSTAR);
	if (tbuff[34] == 0x01)
		check131->SetCheck(1);
	else
		check131->SetCheck(0);

	CButton* check132 = (CButton*)GetDlgItem(IDC_VANISHCAPMOATSTAR);
	if (tbuff[33] == 0x01)
		check132->SetCheck(1);
	else
		check132->SetCheck(0);

	CButton* check133 = (CButton*)GetDlgItem(IDC_WINGMARIORAINBOWSTAR);
	if (tbuff[32] == 0x01)
		check133->SetCheck(1);
	else
		check133->SetCheck(0);

	CButton* check134 = (CButton*)GetDlgItem(IDC_BOWSERDARKWORLDSTAR);
	if (tbuff[27] == 0x01)
		check134->SetCheck(1);
	else
		check134->SetCheck(0);

	CButton* check135 = (CButton*)GetDlgItem(IDC_BOWSERFIRESEASTAR);
	if (tbuff[28] == 0x01)
		check135->SetCheck(1);
	else
		check135->SetCheck(0);

	CButton* check136 = (CButton*)GetDlgItem(IDC_BOWSERSKYSTAR);
	if (tbuff[29] == 0x01)
		check136->SetCheck(1);
	else
		check136->SetCheck(0);

	CButton* check137 = (CButton*)GetDlgItem(IDC_CAPSTOLENSNOWMANCHECKBOX);
	if (CastleFlag1[7] == '1')
		check137->SetCheck(1);
	else
		check137->SetCheck(0);

	CButton* check138 = (CButton*)GetDlgItem(IDC_CAPSTOLENBIRDCHECKBOX);
	if (CastleFlag1[6] == '1')
		check138->SetCheck(1);
	else
		check138->SetCheck(0);

	CButton* check139 = (CButton*)GetDlgItem(IDC_CAPSTOLENMONKEYCHECKBOX);
	if (CastleFlag1[5] == '1')
		check139->SetCheck(1);
	else
		check139->SetCheck(0);

	CButton* check140 = (CButton*)GetDlgItem(IDC_CHECK136);
	if (CastleFlag1[4] == '1')
		check140->SetCheck(1);
	else
		check140->SetCheck(0);

	CButton* check141 = (CButton*)GetDlgItem(IDC_DDDPORTALMOVEDCHECKBOX);
	if (CastleFlag2[7] == '1')
		check141->SetCheck(1);
	else
		check141->SetCheck(0);

	CButton* check142 = (CButton*)GetDlgItem(IDC_CASTLEMOATDRAINEDCHECKBOX);
	if (CastleFlag2[6] == '1')
		check142->SetCheck(1);
	else
		check142->SetCheck(0);

	CButton* check143 = (CButton*)GetDlgItem(IDC_PEACHSECRETSLIDEDOORUNLOCKED);
	if (CastleFlag2[5] == '1')
		check143->SetCheck(1);
	else
		check143->SetCheck(0);

	CButton* check144 = (CButton*)GetDlgItem(IDC_WHOMPSFORTRESSDOORUNLOCKED);
	if (CastleFlag2[4] == '1')
		check144->SetCheck(1);
	else
		check144->SetCheck(0);

	CButton* check145 = (CButton*)GetDlgItem(IDC_COOLMOUNTAINDOORUNLOCKED);
	if (CastleFlag2[3] == '1')
		check145->SetCheck(1);
	else
		check145->SetCheck(0);

	CButton* check146 = (CButton*)GetDlgItem(IDC_JOLLYROGERDOORUNLOCKED);
	if (CastleFlag2[2] == '1')
		check146->SetCheck(1);
	else
		check146->SetCheck(0);

	CButton* check147 = (CButton*)GetDlgItem(IDC_BOWSER1STARDOORUNLOCKED);
	if (CastleFlag2[1] == '1')
		check147->SetCheck(1);
	else
		check147->SetCheck(0);

	CButton* check148 = (CButton*)GetDlgItem(IDC_BOWSER2STARDOORUNLOCKED);
	if (CastleFlag2[0] == '1')
		check148->SetCheck(1);
	else
		check148->SetCheck(0);

	CButton* check149 = (CButton*)GetDlgItem(IDC_WINGCAPSWITCH);
	if (CastleFlag3[6] == '1')
		check149->SetCheck(1);
	else
		check149->SetCheck(0);

	CButton* check150 = (CButton*)GetDlgItem(IDC_METALCAPSWITCH);
	if (CastleFlag3[5] == '1')
		check150->SetCheck(1);
	else
		check150->SetCheck(0);

	CButton* check151 = (CButton*)GetDlgItem(IDC_VANISHCAPSWITCH);
	if (CastleFlag3[4] == '1')
		check151->SetCheck(1);
	else
		check151->SetCheck(0);

	CButton* check152 = (CButton*)GetDlgItem(IDC_BOWSER1KEY);
	if (CastleFlag3[3] == '1')
		check152->SetCheck(1);
	else
		check152->SetCheck(0);

	CButton* check153 = (CButton*)GetDlgItem(IDC_BOWSER2KEY);
	if (CastleFlag3[2] == '1')
		check153->SetCheck(1);
	else
		check153->SetCheck(0);

	CButton* check154 = (CButton*)GetDlgItem(IDC_BASEMENTDOORUNLOCKED);
	if (CastleFlag3[1] == '1')
		check154->SetCheck(1);
	else
		check154->SetCheck(0);

	CButton* check155 = (CButton*)GetDlgItem(IDC_UPSTAIRSDOORUNLOCKED);
	if (CastleFlag3[0] == '1')
		check155->SetCheck(1);
	else
		check155->SetCheck(0);
}

void MainEditor::SetCoinScoresOnStart()
{
	SetDlgItemInt(IDC_LVL1COINSCORE_EB, tbuff[37], 1);
	SetDlgItemInt(IDC_LVL2COINSCORE_EB, tbuff[38], 1);
	SetDlgItemInt(IDC_LVL3COINSCORE_EB, tbuff[39], 1);
	SetDlgItemInt(IDC_LVL4COINSCORE_EB, tbuff[40], 1);
	SetDlgItemInt(IDC_LVL5COINSCORE_EB, tbuff[41], 1);
	SetDlgItemInt(IDC_LVL6COINSCORE_EB, tbuff[42], 1);
	SetDlgItemInt(IDC_LVL7COINSCORE_EB, tbuff[43], 1);
	SetDlgItemInt(IDC_LVL8COINSCORE_EB, tbuff[44], 1);
	SetDlgItemInt(IDC_LVL9COINSCORE_EB, tbuff[45], 1);
	SetDlgItemInt(IDC_LVL10COINSCORE_EB, tbuff[46], 1);
	SetDlgItemInt(IDC_LVL11COINSCORE_EB, tbuff[47], 1);
	SetDlgItemInt(IDC_LVL12COINSCORE_EB, tbuff[48], 1);
	SetDlgItemInt(IDC_LVL13COINSCORE_EB, tbuff[49], 1);
	SetDlgItemInt(IDC_LVL14COINSCORE_EB, tbuff[50], 1);
	SetDlgItemInt(IDC_LVL15COINSCORE_EB, tbuff[51], 1);
}
//File Saving Functions
void MainEditor::OnBnClickedSavefile()
{
	//Converts all the level selections from binary to UINT8 Hex Bytes
	tbuff[12] = BinaryStringToHex(lvl1bits);
	tbuff[13] = BinaryStringToHex(lvl2bits);
	tbuff[14] = BinaryStringToHex(lvl3bits);
	tbuff[15] = BinaryStringToHex(lvl4bits);
	tbuff[16] = BinaryStringToHex(lvl5bits);
	tbuff[17] = BinaryStringToHex(lvl6bits);
	tbuff[18] = BinaryStringToHex(lvl7bits);
	tbuff[19] = BinaryStringToHex(lvl8bits);
	tbuff[20] = BinaryStringToHex(lvl9bits);
	tbuff[21] = BinaryStringToHex(lvl10bits);
	tbuff[22] = BinaryStringToHex(lvl11bits);
	tbuff[23] = BinaryStringToHex(lvl12bits);
	tbuff[24] = BinaryStringToHex(lvl13bits);
	tbuff[25] = BinaryStringToHex(lvl14bits);
	tbuff[26] = BinaryStringToHex(lvl15bits);
	tbuff[30] = BinaryStringToHex(PeachSlideStars);
	tbuff[8] = BinaryStringToHex(ToadMipsStars);
	tbuff[9] = BinaryStringToHex(CastleFlag1);
	tbuff[10] = BinaryStringToHex(CastleFlag2);
	tbuff[11] = BinaryStringToHex(CastleFlag3);
	
	//Calculates our Checksum.
	
	ChecksumCalculation(tbuff, &checksum, &checksumbyte1, &checksumbyte2, saveslot);
	SaveFileToDisk(gpathname, tbuff, sizeof(tbuff));
	MessageBox(_T("             File Saved Successfully"),_T("MagicStar Save File Editor Message."));
	PostMessage(WM_CLOSE);
	
}

// Check Box Functions
//	Level 1
void MainEditor::OnBnClickedLvl1star1checkbox()
{
	if (lvl1bits[7] == '1')
		lvl1bits.SetAt(7, '0');
	else
		lvl1bits.SetAt(7, '1');
	
}
void MainEditor::OnBnClickedLvl1star2checkbox()
{
	if (lvl1bits[6] == '1')
		lvl1bits.SetAt(6, '0');
	else
		lvl1bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl1star3checkbox()
{
	if (lvl1bits[5] == '1')
		lvl1bits.SetAt(5, '0');
	else
		lvl1bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl1star4checkbox()
{
	if (lvl1bits[4] == '1')
		lvl1bits.SetAt(4, '0');
	else
		lvl1bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl1star5checkbox()
{
	if (lvl1bits[3] == '1')
		lvl1bits.SetAt(3, '0');
	else
		lvl1bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl1star6checkbox()
{
	if (lvl1bits[2] == '1')
		lvl1bits.SetAt(2, '0');
	else
		lvl1bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl1star7checkbox()
{
	if (lvl1bits[1] == '1')
		lvl1bits.SetAt(1, '0');
	else
		lvl1bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl1cannoncheckbox()
{
	if (lvl1bits[0] == '1')
		lvl1bits.SetAt(0, '0');
	else
		lvl1bits.SetAt(0, '1');
}

//	Level 2
void MainEditor::OnBnClickedLvl2star1checkbox()
{
	if (lvl2bits[7] == '1')
		lvl2bits.SetAt(7, '0');
	else
		lvl2bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl2star2checkbox()
{
	if (lvl2bits[6] == '1')
		lvl2bits.SetAt(6, '0');
	else
		lvl2bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl2star3checkbox()
{
	if (lvl2bits[5] == '1')
		lvl2bits.SetAt(5, '0');
	else
		lvl2bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl2star4checkbox()
{
	if (lvl2bits[4] == '1')
		lvl2bits.SetAt(4, '0');
	else
		lvl2bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl2star5checkbox()
{
	if (lvl2bits[3] == '1')
		lvl2bits.SetAt(3, '0');
	else
		lvl2bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl2star6checkbox()
{
	if (lvl2bits[2] == '1')
		lvl2bits.SetAt(2, '0');
	else
		lvl2bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl2star7checkbox()
{
	if (lvl2bits[1] == '1')
		lvl2bits.SetAt(1, '0');
	else
		lvl2bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl2cannoncheckbox()
{
	if (lvl2bits[0] == '1')
		lvl2bits.SetAt(0, '0');
	else
		lvl2bits.SetAt(0, '1');
}

//	Level 3
void MainEditor::OnBnClickedLv3star1checkbox()
{
	if (lvl3bits[7] == '1')
		lvl3bits.SetAt(7, '0');
	else
		lvl3bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl3star2checkbox()
{
	if (lvl3bits[6] == '1')
		lvl3bits.SetAt(6, '0');
	else
		lvl3bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl3star3checkbox()
{
	if (lvl3bits[5] == '1')
		lvl3bits.SetAt(5, '0');
	else
		lvl3bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl3star4checkbox()
{
	if (lvl3bits[4] == '1')
		lvl3bits.SetAt(4, '0');
	else
		lvl3bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl3star5checkbox()
{
	if (lvl3bits[3] == '1')
		lvl3bits.SetAt(3, '0');
	else
		lvl3bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl3star6checkbox()
{
	if (lvl3bits[2] == '1')
		lvl3bits.SetAt(2, '0');
	else
		lvl3bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl3star7checkbox()
{
	if (lvl3bits[1] == '1')
		lvl3bits.SetAt(1, '0');
	else
		lvl3bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl3cannoncheckbox()
{
	if (lvl3bits[0] == '1')
		lvl3bits.SetAt(0, '0');
	else
		lvl3bits.SetAt(0, '1');
}

//	Level 4
void MainEditor::OnBnClickedLvl4star1checkbox()
{
	if (lvl4bits[7] == '1')
		lvl4bits.SetAt(7, '0');
	else
		lvl4bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl4star2checkbox()
{
	if (lvl4bits[6] == '1')
		lvl4bits.SetAt(6, '0');
	else
		lvl4bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl4star3checkbox()
{
	if (lvl4bits[5] == '1')
		lvl4bits.SetAt(5, '0');
	else
		lvl4bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl4star4checkbox()
{
	if (lvl4bits[4] == '1')
		lvl4bits.SetAt(4, '0');
	else
		lvl4bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl4star5checkbox()
{
	if (lvl4bits[3] == '1')
		lvl4bits.SetAt(3, '0');
	else
		lvl4bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl4star6checkbox()
{
	if (lvl4bits[2] == '1')
		lvl4bits.SetAt(2, '0');
	else
		lvl4bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl4star7checkbox()
{
	if (lvl4bits[1] == '1')
		lvl4bits.SetAt(1, '0');
	else
		lvl4bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl4cannoncheckbox()
{
	if (lvl4bits[0] == '1')
		lvl4bits.SetAt(0, '0');
	else
		lvl4bits.SetAt(0, '1');
}

//	Level 5
void MainEditor::OnBnClickedLvl5star1checkbox()
{
	if (lvl5bits[7] == '1')
		lvl5bits.SetAt(7, '0');
	else
		lvl5bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl5star2checkbox()
{
	if (lvl5bits[6] == '1')
		lvl5bits.SetAt(6, '0');
	else
		lvl5bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl5star3checkbox()
{
	if (lvl5bits[5] == '1')
		lvl5bits.SetAt(5, '0');
	else
		lvl5bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl5star4checkbox()
{
	if (lvl5bits[4] == '1')
		lvl5bits.SetAt(4, '0');
	else
		lvl5bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl5star5checkbox()
{
	if (lvl5bits[3] == '1')
		lvl5bits.SetAt(3, '0');
	else
		lvl5bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl5star6checkbox()
{
	if (lvl5bits[2] == '1')
		lvl5bits.SetAt(2, '0');
	else
		lvl5bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl5star7checkbox()
{
	if (lvl5bits[1] == '1')
		lvl5bits.SetAt(1, '0');
	else
		lvl5bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl5cannoncheckbox()
{
	if (lvl5bits[0] == '1')
		lvl5bits.SetAt(0, '0');
	else
		lvl5bits.SetAt(0, '1');
}

//	Level 6
void MainEditor::OnBnClickedLvl6star1checkbox()
{
	if (lvl6bits[7] == '1')
		lvl6bits.SetAt(7, '0');
	else
		lvl6bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl6star2checkbox()
{
	if (lvl6bits[6] == '1')
		lvl6bits.SetAt(6, '0');
	else
		lvl6bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl6star3checkbox()
{
	if (lvl6bits[5] == '1')
		lvl6bits.SetAt(5, '0');
	else
		lvl6bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl6star4checkbox()
{
	if (lvl6bits[4] == '1')
		lvl6bits.SetAt(4, '0');
	else
		lvl6bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl6star5checkbox()
{
	if (lvl6bits[3] == '1')
		lvl6bits.SetAt(3, '0');
	else
		lvl6bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl6star6checkbox()
{
	if (lvl6bits[2] == '1')
		lvl6bits.SetAt(2, '0');
	else
		lvl6bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl6star7checkbox()
{
	if (lvl6bits[1] == '1')
		lvl6bits.SetAt(1, '0');
	else
		lvl6bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl6cannoncheckbox()
{
	if (lvl6bits[0] == '1')
		lvl6bits.SetAt(0, '0');
	else
		lvl6bits.SetAt(0, '1');
}

// Level 7
void MainEditor::OnBnClickedLvl7star1checkbox()
{
	if (lvl7bits[7] == '1')
		lvl7bits.SetAt(7, '0');
	else
		lvl7bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl7star2checkbox()
{
	if (lvl7bits[6] == '1')
		lvl7bits.SetAt(6, '0');
	else
		lvl7bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl7star3checkbox()
{
	if (lvl7bits[5] == '1')
		lvl7bits.SetAt(5, '0');
	else
		lvl7bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvlstar4checkbox()
{
	if (lvl7bits[4] == '1')
		lvl7bits.SetAt(4, '0');
	else
		lvl7bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl7star5checkbox()
{
	if (lvl7bits[3] == '1')
		lvl7bits.SetAt(3, '0');
	else
		lvl7bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl7star6checkbox()
{
	if (lvl7bits[2] == '1')
		lvl7bits.SetAt(2, '0');
	else
		lvl7bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl7star7checkbox()
{
	if (lvl7bits[1] == '1')
		lvl7bits.SetAt(1, '0');
	else
		lvl7bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl7cannoncheckbox()
{
	if (lvl7bits[0] == '1')
		lvl7bits.SetAt(0, '0');
	else
		lvl7bits.SetAt(0, '1');
}

// Level 8
void MainEditor::OnBnClickedLvl8star1checkbox()
{
	if (lvl8bits[7] == '1')
		lvl8bits.SetAt(7, '0');
	else
		lvl8bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl8star2checkbox()
{
	if (lvl8bits[6] == '1')
		lvl8bits.SetAt(6, '0');
	else
		lvl8bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl8star3checkbox()
{
	if (lvl8bits[5] == '1')
		lvl8bits.SetAt(5, '0');
	else
		lvl8bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl8star4checkbox()
{
	if (lvl8bits[4] == '1')
		lvl8bits.SetAt(4, '0');
	else
		lvl8bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl8star5checkbox()
{
	if (lvl8bits[3] == '1')
		lvl8bits.SetAt(3, '0');
	else
		lvl8bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl8star6checkbox()
{
	if (lvl8bits[2] == '1')
		lvl8bits.SetAt(2, '0');
	else
		lvl8bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl8star7checkbox()
{
	if (lvl8bits[1] == '1')
		lvl8bits.SetAt(1, '0');
	else
		lvl8bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl8cannoncheckbox()
{
	if (lvl8bits[0] == '1')
		lvl8bits.SetAt(0, '0');
	else
		lvl8bits.SetAt(0, '1');
}

//	Level 9
void MainEditor::OnBnClickedLvl9star1checkbox()
{
	if (lvl9bits[7] == '1')
		lvl9bits.SetAt(7, '0');
	else
		lvl9bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl9star2checkbox()
{
	if (lvl9bits[6] == '1')
		lvl9bits.SetAt(6, '0');
	else
		lvl9bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl9star3checkbox()
{
	if (lvl9bits[5] == '1')
		lvl9bits.SetAt(5, '0');
	else
		lvl9bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl9star4checkbox()
{
	if (lvl9bits[4] == '1')
		lvl9bits.SetAt(4, '0');
	else
		lvl9bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl9star5checkbox()
{
	if (lvl9bits[3] == '1')
		lvl9bits.SetAt(3, '0');
	else
		lvl9bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl9star6checkbox()
{
	if (lvl9bits[2] == '1')
		lvl9bits.SetAt(2, '0');
	else
		lvl9bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl9star7checkbox()
{
	if (lvl9bits[1] == '1')
		lvl9bits.SetAt(1, '0');
	else
		lvl9bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl9cannoncheckbox()
{
	if (lvl9bits[0] == '1')
		lvl9bits.SetAt(0, '0');
	else
		lvl9bits.SetAt(0, '1');
}

//	Level 10
void MainEditor::OnBnClickedLvl10star1checkbox()
{
	if (lvl10bits[7] == '1')
		lvl10bits.SetAt(7, '0');
	else
		lvl10bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl10star2checkbox()
{
	if (lvl10bits[6] == '1')
		lvl10bits.SetAt(6, '0');
	else
		lvl10bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl10star3checkbox()
{
	if (lvl10bits[5] == '1')
		lvl10bits.SetAt(5, '0');
	else
		lvl10bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl10star4checkbox()
{
	if (lvl10bits[4] == '1')
		lvl10bits.SetAt(4, '0');
	else
		lvl10bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl10star5checkbox()
{
	if (lvl10bits[3] == '1')
		lvl10bits.SetAt(3, '0');
	else
		lvl10bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl10star6checkbox()
{
	if (lvl10bits[2] == '1')
		lvl10bits.SetAt(2, '0');
	else
		lvl10bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl10star7checkbox()
{
	if (lvl10bits[1] == '1')
		lvl10bits.SetAt(1, '0');
	else
		lvl10bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl10cannoncheckbox()
{
	if (lvl10bits[0] == '1')
		lvl10bits.SetAt(0, '0');
	else
		lvl10bits.SetAt(0, '1');
}

//	Level 11
void MainEditor::OnBnClickedLvl11star1checkbox()
{
	if (lvl11bits[7] == '1')
		lvl11bits.SetAt(7, '0');
	else
		lvl11bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl11star2checkbox()
{
	if (lvl11bits[6] == '1')
		lvl11bits.SetAt(6, '0');
	else
		lvl11bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl11star3checkbox()
{
	if (lvl11bits[5] == '1')
		lvl11bits.SetAt(5, '0');
	else
		lvl11bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl11star4checkbox()
{
	if (lvl11bits[4] == '1')
		lvl11bits.SetAt(4, '0');
	else
		lvl11bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl11star5checkbox()
{
	if (lvl11bits[3] == '1')
		lvl11bits.SetAt(3, '0');
	else
		lvl11bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl11star6checkbox()
{
	if (lvl11bits[2] == '1')
		lvl11bits.SetAt(2, '0');
	else
		lvl11bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl11star7checkbox()
{
	if (lvl11bits[1] == '1')
		lvl11bits.SetAt(1, '0');
	else
		lvl11bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl11cannoncheckbox()
{
	if (lvl11bits[0] == '1')
		lvl11bits.SetAt(0, '0');
	else
		lvl11bits.SetAt(0, '1');
}

//	Level 12
void MainEditor::OnBnClickedLvl12star1checkbox()
{
	if (lvl12bits[7] == '1')
		lvl12bits.SetAt(7, '0');
	else
		lvl12bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl12star2checkbox()
{
	if (lvl12bits[6] == '1')
		lvl12bits.SetAt(6, '0');
	else
		lvl12bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl12star3checkbox()
{
	if (lvl12bits[5] == '1')
		lvl12bits.SetAt(5, '0');
	else
		lvl12bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl12star4checkbox()
{
	if (lvl12bits[4] == '1')
		lvl12bits.SetAt(4, '0');
	else
		lvl12bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl12star5checkbox()
{
	if (lvl12bits[3] == '1')
		lvl12bits.SetAt(3, '0');
	else
		lvl12bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl12star6checkbox()
{
	if (lvl12bits[2] == '1')
		lvl12bits.SetAt(2, '0');
	else
		lvl12bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl12star7checkbox()
{
	if (lvl12bits[1] == '1')
		lvl12bits.SetAt(1, '0');
	else
		lvl12bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl12cannoncheckbox()
{
	if (lvl12bits[0] == '1')
		lvl12bits.SetAt(0, '0');
	else
		lvl12bits.SetAt(0, '1');
}

//	Level 13
void MainEditor::OnBnClickedLvl13star1checkbox()
{
	if (lvl13bits[7] == '1')
		lvl13bits.SetAt(7, '0');
	else
		lvl13bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl13star2checkbox()
{
	if (lvl13bits[6] == '1')
		lvl13bits.SetAt(6, '0');
	else
		lvl13bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl13star3checkbox()
{
	if (lvl13bits[5] == '1')
		lvl13bits.SetAt(5, '0');
	else
		lvl13bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl13star4checkbox()
{
	if (lvl13bits[4] == '1')
		lvl13bits.SetAt(4, '0');
	else
		lvl13bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl13star5checkbox()
{
	if (lvl13bits[3] == '1')
		lvl13bits.SetAt(3, '0');
	else
		lvl13bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl13star6checkbox()
{
	if (lvl13bits[2] == '1')
		lvl13bits.SetAt(2, '0');
	else
		lvl13bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl13star7checkbox()
{
	if (lvl13bits[1] == '1')
		lvl13bits.SetAt(1, '0');
	else
		lvl13bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl13cannoncheckbox()
{
	if (lvl13bits[0] == '1')
		lvl13bits.SetAt(0, '0');
	else
		lvl13bits.SetAt(0, '1');
}

//	Level 14
void MainEditor::OnBnClickedLvl14star1checkbox()
{
	if (lvl14bits[7] == '1')
		lvl14bits.SetAt(7, '0');
	else
		lvl14bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl14star2checkbox()
{
	if (lvl14bits[6] == '1')
		lvl14bits.SetAt(6, '0');
	else
		lvl14bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl14star3checkbox()
{
	if (lvl14bits[5] == '1')
		lvl14bits.SetAt(5, '0');
	else
		lvl14bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl14star4checkbox()
{
	if (lvl14bits[4] == '1')
		lvl14bits.SetAt(4, '0');
	else
		lvl14bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl14star5checkbox()
{
	if (lvl14bits[3] == '1')
		lvl14bits.SetAt(3, '0');
	else
		lvl14bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl14star6checkbox()
{
	if (lvl14bits[2] == '1')
		lvl14bits.SetAt(2, '0');
	else
		lvl14bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl14star7checkbox()
{
	if (lvl14bits[1] == '1')
		lvl14bits.SetAt(1, '0');
	else
		lvl14bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl14cannoncheckbox()
{
	if (lvl14bits[0] == '1')
		lvl14bits.SetAt(0, '0');
	else
		lvl14bits.SetAt(0, '1');
}

//	Level 15
void MainEditor::OnBnClickedLvl15star1checkbox()
{
	if (lvl15bits[7] == '1')
		lvl15bits.SetAt(7, '0');
	else
		lvl15bits.SetAt(7, '1');
}
void MainEditor::OnBnClickedLvl15star2checkbox()
{
	if (lvl15bits[6] == '1')
		lvl15bits.SetAt(6, '0');
	else
		lvl15bits.SetAt(6, '1');
}
void MainEditor::OnBnClickedLvl15star3checkbox()
{
	if (lvl15bits[5] == '1')
		lvl15bits.SetAt(5, '0');
	else
		lvl15bits.SetAt(5, '1');
}
void MainEditor::OnBnClickedLvl15star4checkbox()
{
	if (lvl15bits[4] == '1')
		lvl15bits.SetAt(4, '0');
	else
		lvl15bits.SetAt(4, '1');
}
void MainEditor::OnBnClickedLvl15star5checkbox()
{
	if (lvl15bits[3] == '1')
		lvl15bits.SetAt(3, '0');
	else
		lvl15bits.SetAt(3, '1');
}
void MainEditor::OnBnClickedLvl15star6checkbox()
{
	if (lvl15bits[2] == '1')
		lvl15bits.SetAt(2, '0');
	else
		lvl15bits.SetAt(2, '1');
}
void MainEditor::OnBnClickedLvl15star7checkbox()
{
	if (lvl15bits[1] == '1')
		lvl15bits.SetAt(1, '0');
	else
		lvl15bits.SetAt(1, '1');
}
void MainEditor::OnBnClickedLvl15cannoncheckbox()
{
	if (lvl15bits[0] == '1')
		lvl15bits.SetAt(0, '0');
	else
		lvl15bits.SetAt(0, '1');
}

//	Secret Stars
void MainEditor::OnBnClickedPeachslidestar()
{
	if (PeachSlideStars[7] == '1')
		PeachSlideStars.SetAt(7, '0');
	else
		PeachSlideStars.SetAt(7, '1');
}
void MainEditor::OnBnClickedPeachslidestar2()
{
	if (PeachSlideStars[6] == '1')
		PeachSlideStars.SetAt(6, '0');
	else
		PeachSlideStars.SetAt(6, '1');
	
}
void MainEditor::OnBnClickedPeachsecretaquariumstar()
{
	if (tbuff[35] == 0x01)
		tbuff[35] = 0x00;
	else
		tbuff[35] = 0x01;
}

void MainEditor::OnBnClickedToadstar1()
{
	if (ToadMipsStars[7] == '1')
		ToadMipsStars.SetAt(7, '0');
	else
		ToadMipsStars.SetAt(7, '1');
}
void MainEditor::OnBnClickedToadstar2()
{
	if (ToadMipsStars[5] == '1')
		ToadMipsStars.SetAt(5, '0');
	else
		ToadMipsStars.SetAt(5, '1');
}
void MainEditor::OnBnClickedToadstar3()
{
	if (ToadMipsStars[4] == '1')
		ToadMipsStars.SetAt(4, '0');
	else
		ToadMipsStars.SetAt(4, '1');
}
void MainEditor::OnBnClickedMipsstar1()
{
	if (ToadMipsStars[6] == '1')
		ToadMipsStars.SetAt(6, '0');
	else
		ToadMipsStars.SetAt(6, '1');
}
void MainEditor::OnBnClickedMipsstar2()
{
	if (ToadMipsStars[3] == '1')
		ToadMipsStars.SetAt(3, '0');
	else
		ToadMipsStars.SetAt(3, '1');
}

void MainEditor::OnBnClickedCavernmetalcapstar()
{
	if (tbuff[31] == 0x01)
		tbuff[31] = 0x00;
	else
		tbuff[31] = 0x01;
}
void MainEditor::OnBnClickedWingmariorainbowstar()
{
	if (tbuff[32] == 0x01)
		tbuff[32] = 0x00;
	else
		tbuff[32] = 0x01;
}
void MainEditor::OnBnClickedVanishcapmoatstar()
{
	if (tbuff[33] == 0x01)
		tbuff[33] = 0x00;
	else
		tbuff[33] = 0x01;
}
void MainEditor::OnBnClickedTowerwingcapstar()
{
	if (tbuff[34] == 0x01)
		tbuff[34] = 0x00;
	else
		tbuff[34] = 0x01;
}
void MainEditor::OnBnClickedBowserdarkworldstar()
{
	if (tbuff[27] == 0x01)
		tbuff[27] = 0x00;
	else
		tbuff[27] = 0x01;
}
void MainEditor::OnBnClickedBowserfireseastar()
{
	if (tbuff[28] == 0x01)
		tbuff[28] = 0x00;
	else
		tbuff[28] = 0x01;
}
void MainEditor::OnBnClickedBowserskystar()
{
	if (tbuff[29] == 0x01)
		tbuff[29] = 0x00;
	else
		tbuff[29] = 0x01;
}

//	Castle Flags
void MainEditor::OnBnClickedCapstolensnowmancheckbox()
{
	if (CastleFlag1[7] == '1')
		CastleFlag1.SetAt(7, '0');
	else
		CastleFlag1.SetAt(7, '1');
}
void MainEditor::OnBnClickedCapstolenbirdcheckbox()
{
	if (CastleFlag1[6] == '1')
		CastleFlag1.SetAt(6, '0');
	else
		CastleFlag1.SetAt(6, '1');
}
void MainEditor::OnBnClickedCapstolenmonkeycheckbox()
{
	if (CastleFlag1[5] == '1')
		CastleFlag1.SetAt(5, '0');
	else
		CastleFlag1.SetAt(5, '1');
}
void MainEditor::OnBnClickedCheck136()
{
	if (CastleFlag1[4] == '1')
		CastleFlag1.SetAt(4, '0');
	else
		CastleFlag1.SetAt(4, '1');
}

void MainEditor::OnBnClickedDddportalmovedcheckbox()
{
	if (CastleFlag2[7] == '1')
		CastleFlag2.SetAt(7, '0');
	else
		CastleFlag2.SetAt(7, '1');
}
void MainEditor::OnBnClickedCastlemoatdrainedcheckbox()
{
	if (CastleFlag2[6] == '1')
		CastleFlag2.SetAt(6, '0');
	else
		CastleFlag2.SetAt(6, '1');
}
void MainEditor::OnBnClickedPeachsecretslidedoorunlocked()
{
	if (CastleFlag2[5] == '1')
		CastleFlag2.SetAt(5, '0');
	else
		CastleFlag2.SetAt(5, '1');
}
void MainEditor::OnBnClickedWhompsfortressdoorunlocked()
{
	if (CastleFlag2[4] == '1')
		CastleFlag2.SetAt(4, '0');
	else
		CastleFlag2.SetAt(4, '1');
}
void MainEditor::OnBnClickedCoolmountaindoorunlocked()
{
	if (CastleFlag2[3] == '1')
		CastleFlag2.SetAt(3, '0');
	else
		CastleFlag2.SetAt(3, '1');
}
void MainEditor::OnBnClickedJollyrogerdoorunlocked()
{
	if (CastleFlag2[2] == '1')
		CastleFlag2.SetAt(2, '0');
	else
		CastleFlag2.SetAt(2, '1');
}
void MainEditor::OnBnClickedBowser1stardoorunlocked()
{
	if (CastleFlag2[1] == '1')
		CastleFlag2.SetAt(1, '0');
	else
		CastleFlag2.SetAt(1, '1');
}
void MainEditor::OnBnClickedBowser2stardoorunlocked()
{
	if (CastleFlag2[0] == '1')
		CastleFlag2.SetAt(0, '0');
	else
		CastleFlag2.SetAt(0, '1');
}

void MainEditor::OnBnClickedWingcapswitch()
{
	if (CastleFlag3[6] == '1')
		CastleFlag3.SetAt(6, '0');
	else
		CastleFlag3.SetAt(6, '1');
}
void MainEditor::OnBnClickedMetalcapswitch()
{
	if (CastleFlag3[5] == '1')
		CastleFlag3.SetAt(5, '0');
	else
		CastleFlag3.SetAt(5, '1');
}
void MainEditor::OnBnClickedVanishcapswitch()
{
	if (CastleFlag3[4] == '1')
		CastleFlag3.SetAt(4, '0');
	else
		CastleFlag3.SetAt(4, '1');
}
void MainEditor::OnBnClickedBowser1key()
{
	if (CastleFlag3[3] == '1')
		CastleFlag3.SetAt(3, '0');
	else
		CastleFlag3.SetAt(3, '1');
}
void MainEditor::OnBnClickedBowser2key()
{
	if (CastleFlag3[2] == '1')
		CastleFlag3.SetAt(2, '0');
	else
		CastleFlag3.SetAt(2, '1');
}
void MainEditor::OnBnClickedBasementdoorunlocked()
{
	if (CastleFlag3[1] == '1')
		CastleFlag3.SetAt(1, '0');
	else
		CastleFlag3.SetAt(1, '1');
}
void MainEditor::OnBnClickedUpstairsdoorunlocked()
{
	if (CastleFlag3[0] == '1')
		CastleFlag3.SetAt(0, '0');
	else
		CastleFlag3.SetAt(0, '1');
}

// Coin Scores

void MainEditor::OnEnChangeLvl1coinscoreEb()
{
	
	//GetDlgItemText(IDC_LVL1COINSCORE_EB, coin1);
	UINT uCoin1 = GetDlgItemInt(IDC_LVL1COINSCORE_EB);
	//coin1.Format(_T("%u"), uCoin1);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL1COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[37] = uCoin1;
	}

}
void MainEditor::OnEnChangeLvl2coinscoreEb()
{

	UINT uCoin1 = GetDlgItemInt(IDC_LVL2COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL2COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[38] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl3coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL3COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL3COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[39] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl4coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL4COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL4COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[40] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl5coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL5COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL5COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[41] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl6coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL6COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL6COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[42] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl7coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL7COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL7COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[43] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl8coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL8COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL8COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[44] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl9coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL9COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL9COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[45] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl10coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL10COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL10COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[46] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl11coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL11COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL11COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[47] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl12coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL12COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL12COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[48] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl13coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL13COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL13COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[49] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl14coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL14COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL14COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[50] = uCoin1;
	}
}
void MainEditor::OnEnChangeLvl15coinscoreEb()
{
	UINT uCoin1 = GetDlgItemInt(IDC_LVL15COINSCORE_EB);
	if (uCoin1 > 100)
	{
		MessageBox(_T("               Enter values below 100"), _T("MagicStar Save File Editor Message."));
		SetDlgItemInt(IDC_LVL15COINSCORE_EB, 00, 1);
	}
	else
	{
		tbuff[51] = uCoin1;
	}
}


