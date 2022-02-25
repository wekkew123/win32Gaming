#pragma once

#define SAFE_DELETE(p)    if(p)       {delete p; p =NULL;}
#define SAFE_DELETE_ARRAY(p)     if(p)        {delete[]  p; p=NULL;}
#define SAFE_RELLASE(p)		if(p)		{p->Release(); p = NULL;}

#define DECLARE_SINGLE(Type)	\
	private:\
		static Type*	m_pInst;\
	public:\
		static Type* GetInst()\
		{\
			if(!m_pInst)\
				m_pInst = new Type;\
			return m_pInst;\
		}\
		static void DestroyInst()\
		{\
			SAFE_DELETE(m_pInst);\
		}\
		private:\
		Type();\
		~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_pInst =NULL;
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()
#define GetRESOLUTION	CCore::GetInst()->GetResolution()
#define GETWINDOWHANDLE	CCore::GetInst()->GetWindowHandle()

#define KEYDOWN(key)	CInput::GetInst()->KeyDown(key)
#define KEYPRESS(key)	CInput::GetInst()->KeyPress(key)
#define KEYUP(key)		CInput::GetInst()->KeyUp(key)