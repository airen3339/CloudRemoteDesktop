
#pragma once

#include <iostream>


/*
@brief client/server operation cmd define
*/
enum class CMDTYPE
{
	CMD_UNKNOWN				= 0,
	CMD_MOUSE_MOVE_TO		= 1,
	CMD_MOUSE_LEFT_DOWN		= 2,
	CMD_MOUSE_LEFT_UP		= 3,
	CMD_MOUSE_RIGHT_DOWN	= 4,
	CMD_MOUSE_RIGHT_UP		= 5,
	CMD_MOUSE_WHEEL			= 6,
	CMD_MOUSE_DOUBLE_CLICK	= 7,
	CMD_KEY_PRESS			= 8,
	CMD_KEY_RELEASE			= 9,
	CMD_GET_SCREEN_SIZE		= 11,
	CMD_GET_SCREEN_SIZE_RES = 12,
	CMD_SEND_SERVER_SCREEN_SIZE = 13,
};

/*
@brief system type
*/
enum class SYSTYPE
{
	UNKNOWN = 0,
	WINDOWS	= 1,
	LINUX	= 2,
	MAC		= 3,
};

constexpr int msgProtocolLength = 20;

const int BLOCK_WIDTH = 50;
const int BLOCK_HEIGHT = 50;
const int DIFF_PIX = 5;
const int DIFF_THN = 10;

//! server <--> client msg
const static int MAP_SERVER_MSG_PORT = 5647;

//! server <--> client img
const static int MAP_SERVER_IMG_PORT = 5648;

const static int CMD_SERVER_PORT = 5649;

//**********************************

/*
@brief	control msg define introduce
		1. msg length is 20 byte.
		2. mouse msg and keyboard msg
		2.1 mouse msg
			c[0]: msg type, include mouse move or press, and keyboard press
			c[1]: controller(client) system type, eg: Windows/Linux/Mac
			c[2]: controlled(server) system type, eg: Windows/Linux/Mac
			c[3]: extend data, default is 0.
		
			//! c[4]-c[7], use 4 byte(int32_t) storage mouse position of x
			c[4]:
			c[5]:
			c[6]:
			c[7]:

			//! c[8]-c[11], use 4 byte(int32_t) storage mouse position of y
			c[8]:
			c[9]:
			c[10]:
			c[11]:

			//! c[12]-c[15], use 4 byte(int32_t) storage mouse wheel step
			c[12]:
			c[13]:
			c[14]:
			c[15]:

			//! c[12]-c[15], extend data, default is 0.
			c[16]:
			c[17]:
			c[18]:
			c[19]:

		2.2 keyboard msg
			c[0]: msg type, include mouse move or press, and keyboard press
			c[1]: controller(client) system type, eg: Windows/Linux/Mac
			c[2]: controlled(server) system type, eg: Windows/Linux/Mac
			c[3]: extend data, Qt::keyboardModifiers.
		
			//! c[4]-c[7], use 4 byte(int32_t) storage keyboard key value
			c[4]:
			c[5]:
			c[6]:
			c[7]:

			//! c[8]-c[11], use 4 byte(int32_t) storage nativeScanCode
			c[8]:
			c[9]:
			c[10]:
			c[11]:

			//! c[12]-c[15], use 4 byte(int32_t) storage nativeVirtualKey
			c[12]:
			c[13]:
			c[14]:
			c[15]:

			//! c[16]-c[19], use 4 byte(int32_t) storage nativemodifiers
			c[16]:
			c[17]:
			c[18]:
			c[19]:
*/
//**********************************


/*
@brief client/server msg protocol data define
*/
class CMDData
{
public:
	//! whole data
	char c[20];

	/*
	@brief common header data
	*/
	//! use 1byte, command, like mousemove, mouse left button press
	CMDTYPE cmdType;
	//! use 1byte, client sys type
	SYSTYPE cSysType;
	//! use 1byte, server sys type
	SYSTYPE sSysType;
	//! use 1byte, extend data
	char cExtend;

	/*
	@brief mouse msg data
	*/
	//! use 4byte, pt.x
	int32_t  xPos;
	//! use 4byte, pt.y
	int32_t  yPos;
	//! use 4byte, mouse wheel, delta
	int32_t delta;

	/*
	@brief keyboard msg data
	*/
	//! use 4byte, key value
	int32_t kbValue;
	//! use 4byte, native scan code
	int32_t nativeScanCode;
	//! use 4byte, native virtual key
	int32_t nativeVirtualKey;
	//! use 4byte, native modifiers
	int32_t nativeModifiers;
	//! 

public:
	CMDData();

	void Reset();

	void SetData(CMDData cmdData);

	void GetData(CMDData& cmdData);

	void SetData(char* p);

	void GetData(char* p);

	void GetCMD(CMDTYPE& type);

	void SetCMD(CMDTYPE cmd);

	void GetX(int32_t& x);

	void GetY(int32_t& y);

	void SetX(int32_t x);

	void SetY(int32_t y);

	void GetW(int32_t& w);

	void GetH(int32_t& h);

	void GetDelta(int32_t& deltaValue);

	void SetDelta(int32_t deltaValue);

	void GetKeyValue(int32_t& keyValue);

	void SetKeyValue(int32_t keyValue);

	void GetScanCode(int32_t& scanCode);

	void SetScanCode(int32_t scanCode);

	void GetVirtualKey(int32_t& virtualKey);

	void SetVirtualKey(int32_t virtualKey);

	void GetModifier(int32_t& modifier);

	void SetModifier(int32_t modifier);

};

/*
@brief Wrap process cmd msg data storage and analyze.
	   Each of msg process at derived class.	
*/
class CmdHanldeBase
{
public:
	CmdHanldeBase();
	CmdHanldeBase(char* p);
	CmdHanldeBase(const CMDData& data);
	virtual ~CmdHanldeBase();

public:
	void SetData(const CMDData& data);
	void GetData(CMDData& data);
	void GetData(char* p);

public:
	//!
	void SetCMD(CMDTYPE cmd);
	void GetCMD(CMDTYPE& type);
	void GetX(int32_t& x);
	void GetY(int32_t&y);
	void SetX(int32_t x);
	void SetY(int32_t y);
	void GetW(int32_t& w);
	void GetH(int32_t& h);

public:
	CMDData m_cmdData;

};

/*
@brief	process mouse move
		CMD_MOUSE_MOVE_TO
*/
class CmdMouseMove : public CmdHanldeBase
{
public:
	CmdMouseMove();
	CmdMouseMove(char* p);
	CmdMouseMove(const CMDData& data);
	~CmdMouseMove();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_LEFT_DOWN
*/
class CmdMouseLeftDown : public CmdHanldeBase
{
public:
	CmdMouseLeftDown();
	CmdMouseLeftDown(char* p);
	CmdMouseLeftDown(const CMDData& data);
	~CmdMouseLeftDown();

public:
	//! extend

private:
	
};

/*
@brief	process mouse press
		CMD_MOUSE_LEFT_UP
*/
class CmdMouseLeftUp : public CmdHanldeBase
{
public:
	CmdMouseLeftUp();
	CmdMouseLeftUp(char* p);
	CmdMouseLeftUp(const CMDData& data);
	~CmdMouseLeftUp();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_RIGHT_DOWN
*/
class CmdMouseRightDown : public CmdHanldeBase
{
public:
	CmdMouseRightDown();
	CmdMouseRightDown(char* p);
	CmdMouseRightDown(const CMDData& data);
	~CmdMouseRightDown();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_RIGHT_UP
*/
class CmdMouseRightUp : public CmdHanldeBase
{
public:
	CmdMouseRightUp();
	CmdMouseRightUp(char* p);
	CmdMouseRightUp(const CMDData& data);
	~CmdMouseRightUp();

public:
	//! extend

private:

};

/*
@brief	process mouse press
		CMD_MOUSE_WHEEL
*/
class CmdMouseWheel : public CmdHanldeBase
{
public:
	CmdMouseWheel();
	CmdMouseWheel(char* p);
	CmdMouseWheel(const CMDData& data);
	~CmdMouseWheel();

public:
	//! extend

private:
	//! 
};


/*
@brief	process mouse press
		CMD_MOUSE_DOUBLE_CLICK
*/
class CmdMouseDbClick : public CmdHanldeBase
{
public:
	CmdMouseDbClick();
	CmdMouseDbClick(char* p);
	CmdMouseDbClick(const CMDData& data);
	~CmdMouseDbClick();

public:
	//! extend

private:

};

/*
@brief	process keyboard press
		CMD_KEY_PRESS
*/
class CmdKeyPress : public CmdHanldeBase
{
public:
	CmdKeyPress();
	CmdKeyPress(char* p);
	CmdKeyPress(const CMDData& data);
	~CmdKeyPress();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_KEY_RELEASE
*/
class CmdKeyRelease : public CmdHanldeBase
{
public:
	CmdKeyRelease();
	CmdKeyRelease(char* p);
	CmdKeyRelease(const CMDData& data);
	~CmdKeyRelease();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_GET_SCREEN_SIZE
*/
class CmdGetScreenSize : public CmdHanldeBase
{
public:
	CmdGetScreenSize();
	CmdGetScreenSize(char* p);
	CmdGetScreenSize(const CMDData& data);
	~CmdGetScreenSize();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_GET_SCREEN_SIZE_RES
*/
class CmdGetScreenSizeRes : public CmdHanldeBase
{
public:
	CmdGetScreenSizeRes();
	CmdGetScreenSizeRes(char* p);
	CmdGetScreenSizeRes(const CMDData& data);
	~CmdGetScreenSizeRes();

public:
	//! extend

private:

};

/*
@brief	process keyboard release
		CMD_SEND_SERVER_SCREEN_SIZE
*/
class CmdSendServerScreenSize : public CmdHanldeBase
{
public:
	CmdSendServerScreenSize();
	CmdSendServerScreenSize(char* p);
	CmdSendServerScreenSize(const CMDData& data);
	~CmdSendServerScreenSize();

public:
	//! extend

private:

};