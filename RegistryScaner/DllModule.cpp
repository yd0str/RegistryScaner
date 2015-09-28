/**
	Project - Regestry Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "StdAfx.h"
#include "DllModule.h"

namespace RegestryScanner { namespace Details {

	DllModule::DllModule(String const& libName, DWORD flags)
		: m_LibName(_T(""))
		, m_Flags(0)
		, m_Handle(nullptr)
	{
		Load(libName, flags);
	}
	
	DllModule::~DllModule() {
		Free();
	}
	
	DllModule::DllModule(DllModule const& obj)
		: m_LibName(_T(""))
		, m_Flags(0)
		, m_Handle(nullptr)
	{
		Load(obj.m_LibName, obj.m_Flags);
	}
	
	DllModule &DllModule::operator=(DllModule const& obj)
	{
		if (this != &obj)
			Load(obj.m_LibName, obj.m_Flags);

		return *this;
	}
	
	bool DllModule::Load(String const& libName, DWORD flags)
	{
		Free();

		if (flags != 0)
			m_Handle = LoadLibraryEx(libName.c_str(), nullptr, flags);
		else
			m_Handle = LoadLibrary(libName.c_str());

		if (IsLoad())
		{
			m_LibName.assign(libName);
			m_Flags = flags;

			return true;
		}

		return false;
	}
	
	void DllModule::Free()
	{
		if (IsLoad())
		{
			FreeLibrary(m_Handle);
			m_Handle = nullptr;
		}
	}
	
	bool DllModule::IsLoad() const {
		return m_Handle != nullptr;
	}

}} /// end namespace RegestryScanner::Details
