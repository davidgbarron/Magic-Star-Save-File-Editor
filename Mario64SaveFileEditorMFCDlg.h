
// Mario64SaveFileEditorMFCDlg.h : header file
//

#pragma once
#include <memory>

// CMario64SaveFileEditorMFCDlg dialog
class CMario64SaveFileEditorMFCDlg : public CDialogEx
{
// Construction
public:
	CMario64SaveFileEditorMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MARIO64SAVEFILEEDITORMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	//afx_msg void SetupInterfacePointers();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnHelpAbout();
	afx_msg void OnFileExit();
	afx_msg void OnBnClickedOpenfile();
	
private:

public:
	afx_msg void OnMenuFileOpen();
};

//Declare a new OBject for the MAIN EDITOR that's a child from CDialogEX
class MainEditor : public CDialogEx
{
public:
	//Construction
public:
	MainEditor(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINEDITOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//This Must Be Declared In Order to Have Communication with the dialog
	DECLARE_MESSAGE_MAP()


// Implementation

public:
	afx_msg void OnFileExit();
	afx_msg void OnMenuFileOpen();
	afx_msg void OnUpdateButton(CCmdUI* CCmdUI);
	afx_msg void OnBnClickedLvl1star1checkbox();
	afx_msg void OnBnClickedSavefile();
	BOOL ReadFileFromDisk(CString path, unsigned char* masterBuff, unsigned char* tempbuff, UINT* bsize);
	void SetCheckBoxesOnStart();
	void SetCoinScoresOnStart();
	void SaveFileToDisk(CString path, unsigned char* tempbuff, UINT bsize);
	void ChecksumCalculation(unsigned char* tempbuff, UINT16* chksum, UINT8* part1, UINT8* part2, UINT savslot);// use pointers in order to directly change the original value with the ref, not a copy
	
	// Hex and Binary Conversions
	CString HexToString(unsigned char* tempbuff, UINT lvloffset);
	UINT8 BinaryStringToHex(CString lvlbinstring);
	
	
	
	afx_msg void OnBnClickedLvl1star2checkbox();
	afx_msg void OnBnClickedLvl1star3checkbox();
	afx_msg void OnBnClickedLvl1star4checkbox();
	afx_msg void OnBnClickedLvl1star5checkbox();
	afx_msg void OnBnClickedLvl1star6checkbox();
	afx_msg void OnBnClickedLvl1star7checkbox();
	afx_msg void OnBnClickedLvl1cannoncheckbox();
	afx_msg void OnBnClickedLvl2star1checkbox();
	afx_msg void OnBnClickedLvl2star2checkbox();
	afx_msg void OnBnClickedLvl2star3checkbox();
	afx_msg void OnBnClickedLvl2star4checkbox();
	afx_msg void OnBnClickedLvl2star5checkbox();
	afx_msg void OnBnClickedLvl2star6checkbox();
	afx_msg void OnBnClickedLvl2star7checkbox();
	afx_msg void OnBnClickedLvl2cannoncheckbox();
	afx_msg void OnBnClickedLv3star1checkbox();
	afx_msg void OnBnClickedLvl3star2checkbox();
	afx_msg void OnBnClickedLvl3star3checkbox();
	afx_msg void OnBnClickedLvl3star4checkbox();
	afx_msg void OnBnClickedLvl3star5checkbox();
	afx_msg void OnBnClickedLvl3star6checkbox();
	afx_msg void OnBnClickedLvl3star7checkbox();
	afx_msg void OnBnClickedLvl3cannoncheckbox();
	afx_msg void OnBnClickedLvl4star1checkbox();
	afx_msg void OnBnClickedLvl4star2checkbox();
	afx_msg void OnBnClickedLvl4star3checkbox();
	afx_msg void OnBnClickedLvl4star4checkbox();
	afx_msg void OnBnClickedLvl4star5checkbox();
	afx_msg void OnBnClickedLvl4star6checkbox();
	afx_msg void OnBnClickedLvl4star7checkbox();
	afx_msg void OnBnClickedLvl4cannoncheckbox();
	afx_msg void OnBnClickedLvl5star1checkbox();
	afx_msg void OnBnClickedLvl5star2checkbox();
	afx_msg void OnBnClickedLvl5star3checkbox();
	afx_msg void OnBnClickedLvl5star4checkbox();
	afx_msg void OnBnClickedLvl5star5checkbox();
	afx_msg void OnBnClickedLvl5star6checkbox();
	afx_msg void OnBnClickedLvl5star7checkbox();
	afx_msg void OnBnClickedLvl5cannoncheckbox();
	afx_msg void OnBnClickedLvl6star1checkbox();
	afx_msg void OnBnClickedLvl6star2checkbox();
	afx_msg void OnBnClickedLvl6star3checkbox();
	afx_msg void OnBnClickedLvl6star4checkbox();
	afx_msg void OnBnClickedLvl6star5checkbox();
	afx_msg void OnBnClickedLvl6star6checkbox();
	afx_msg void OnBnClickedLvl6star7checkbox();
	afx_msg void OnBnClickedLvl6cannoncheckbox();
	afx_msg void OnBnClickedLvl7star1checkbox();
	afx_msg void OnBnClickedLvl7star2checkbox();
	afx_msg void OnBnClickedLvl7star3checkbox();
	afx_msg void OnBnClickedLvlstar4checkbox();
	afx_msg void OnBnClickedLvl7star5checkbox();
	afx_msg void OnBnClickedLvl7star6checkbox();
	afx_msg void OnBnClickedLvl7star7checkbox();
	afx_msg void OnBnClickedLvl7cannoncheckbox();
	afx_msg void OnBnClickedLvl8star1checkbox();
	afx_msg void OnBnClickedLvl8star2checkbox();
	afx_msg void OnBnClickedLvl8star3checkbox();
	afx_msg void OnBnClickedLvl8star4checkbox();
	afx_msg void OnBnClickedLvl8star5checkbox();
	afx_msg void OnBnClickedLvl8star6checkbox();
	afx_msg void OnBnClickedLvl8star7checkbox();
	afx_msg void OnBnClickedLvl8cannoncheckbox();
	afx_msg void OnBnClickedLvl9star1checkbox();
	afx_msg void OnBnClickedLvl9star2checkbox();
	afx_msg void OnBnClickedLvl9star3checkbox();
	afx_msg void OnBnClickedLvl9star4checkbox();
	afx_msg void OnBnClickedLvl9star5checkbox();
	afx_msg void OnBnClickedLvl9star6checkbox();
	afx_msg void OnBnClickedLvl9star7checkbox();
	afx_msg void OnBnClickedLvl9cannoncheckbox();
	afx_msg void OnBnClickedLvl10star1checkbox();
	afx_msg void OnBnClickedLvl10star2checkbox();
	afx_msg void OnBnClickedLvl10star3checkbox();
	afx_msg void OnBnClickedLvl10star4checkbox();
	afx_msg void OnBnClickedLvl10star5checkbox();
	afx_msg void OnBnClickedLvl10star6checkbox();
	afx_msg void OnBnClickedLvl10star7checkbox();
	afx_msg void OnBnClickedLvl10cannoncheckbox();
	afx_msg void OnBnClickedLvl11star1checkbox();
	afx_msg void OnBnClickedLvl11star2checkbox();
	afx_msg void OnBnClickedLvl11star3checkbox();
	afx_msg void OnBnClickedLvl11star4checkbox();
	afx_msg void OnBnClickedLvl11star5checkbox();
	afx_msg void OnBnClickedLvl11star6checkbox();
	afx_msg void OnBnClickedLvl11star7checkbox();
	afx_msg void OnBnClickedLvl11cannoncheckbox();
	afx_msg void OnBnClickedLvl12star1checkbox();
	afx_msg void OnBnClickedLvl12star2checkbox();
	afx_msg void OnBnClickedLvl12star3checkbox();
	afx_msg void OnBnClickedLvl12star4checkbox();
	afx_msg void OnBnClickedLvl12star5checkbox();
	afx_msg void OnBnClickedLvl12star6checkbox();
	afx_msg void OnBnClickedLvl12star7checkbox();
	afx_msg void OnBnClickedLvl12cannoncheckbox();
	afx_msg void OnBnClickedLvl13star1checkbox();
	afx_msg void OnBnClickedLvl13star2checkbox();
	afx_msg void OnBnClickedLvl13star3checkbox();
	afx_msg void OnBnClickedLvl13star4checkbox();
	afx_msg void OnBnClickedLvl13star5checkbox();
	afx_msg void OnBnClickedLvl13star6checkbox();
	afx_msg void OnBnClickedLvl13star7checkbox();
	afx_msg void OnBnClickedLvl13cannoncheckbox();
	afx_msg void OnBnClickedLvl14star1checkbox();
	afx_msg void OnBnClickedLvl14star2checkbox();
	afx_msg void OnBnClickedLvl14star3checkbox();
	afx_msg void OnBnClickedLvl14star4checkbox();
	afx_msg void OnBnClickedLvl14star5checkbox();
	afx_msg void OnBnClickedLvl14star6checkbox();
	afx_msg void OnBnClickedLvl14star7checkbox();
	afx_msg void OnBnClickedLvl14cannoncheckbox();
	afx_msg void OnBnClickedLvl15star1checkbox();
	afx_msg void OnBnClickedLvl15star2checkbox();
	afx_msg void OnBnClickedLvl15star3checkbox();
	afx_msg void OnBnClickedLvl15star4checkbox();
	afx_msg void OnBnClickedLvl15star5checkbox();
	afx_msg void OnBnClickedLvl15star6checkbox();
	afx_msg void OnBnClickedLvl15star7checkbox();
	afx_msg void OnBnClickedLvl15cannoncheckbox();
	afx_msg void OnBnClickedPeachslidestar();
	afx_msg void OnBnClickedPeachslidestar2();
	afx_msg void OnBnClickedPeachsecretaquariumstar();
	afx_msg void OnBnClickedToadstar1();
	afx_msg void OnBnClickedToadstar2();
	afx_msg void OnBnClickedToadstar3();
	afx_msg void OnBnClickedMipsstar1();
	afx_msg void OnBnClickedMipsstar2();
	afx_msg void OnBnClickedCavernmetalcapstar();
	afx_msg void OnBnClickedWingmariorainbowstar();
	afx_msg void OnBnClickedVanishcapmoatstar();
	afx_msg void OnBnClickedTowerwingcapstar();
	afx_msg void OnBnClickedBowserdarkworldstar();
	afx_msg void OnBnClickedBowserfireseastar();
	afx_msg void OnBnClickedBowserskystar();
	afx_msg void OnBnClickedCapstolensnowmancheckbox();
	afx_msg void OnBnClickedCapstolenbirdcheckbox();
	afx_msg void OnBnClickedCapstolenmonkeycheckbox();
	afx_msg void OnBnClickedCheck136();
	afx_msg void OnBnClickedDddportalmovedcheckbox();
	afx_msg void OnBnClickedCastlemoatdrainedcheckbox();
	afx_msg void OnBnClickedPeachsecretslidedoorunlocked();
	afx_msg void OnBnClickedWhompsfortressdoorunlocked();
	afx_msg void OnBnClickedCoolmountaindoorunlocked();
	afx_msg void OnBnClickedJollyrogerdoorunlocked();
	afx_msg void OnBnClickedBowser1stardoorunlocked();
	afx_msg void OnBnClickedBowser2stardoorunlocked();
	afx_msg void OnBnClickedWingcapswitch();
	afx_msg void OnBnClickedMetalcapswitch();
	afx_msg void OnBnClickedVanishcapswitch();
	afx_msg void OnBnClickedBowser1key();
	afx_msg void OnBnClickedBowser2key();
	afx_msg void OnBnClickedBasementdoorunlocked();
	afx_msg void OnBnClickedUpstairsdoorunlocked();
	afx_msg void OnEnChangeLvl1coinscoreEb();
	afx_msg void OnEnChangeLvl2coinscoreEb();
	afx_msg void OnEnChangeLvl3coinscoreEb();
	afx_msg void OnEnChangeLvl4coinscoreEb();
	afx_msg void OnEnChangeLvl5coinscoreEb();
	afx_msg void OnEnChangeLvl6coinscoreEb();
	afx_msg void OnEnChangeLvl7coinscoreEb();
	afx_msg void OnEnChangeLvl8coinscoreEb();
	afx_msg void OnEnChangeLvl9coinscoreEb();
	afx_msg void OnEnChangeLvl10coinscoreEb();
	afx_msg void OnEnChangeLvl11coinscoreEb();
	afx_msg void OnEnChangeLvl12coinscoreEb();
	afx_msg void OnEnChangeLvl13coinscoreEb();
	afx_msg void OnEnChangeLvl14coinscoreEb();
	afx_msg void OnEnChangeLvl15coinscoreEb();
};

