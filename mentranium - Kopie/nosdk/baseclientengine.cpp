/* * * * * * * * * * * * * * * * 
 * 	 /// MENTRANIUM \\\
 *
 *  - By Leystyku
 * * * * * * * * * * * * * * * */

#include "baseclientengine.h"

IBaseClientEngine::IBaseClientEngine( PDWORD_PTR* pdwClass )
{

	this->base = pdwClass;

}

template <typename T> T IBaseClientEngine::GetFunction( PDWORD_PTR* pdwClass, unsigned int uiIndex ){

	PDWORD_PTR pdwVMT = *pdwClass;

	return (T)pdwVMT[ uiIndex ];

}

PDWORD_PTR* IBaseClientEngine::GetBase( ){

	return this->base;

}

/* ========================================
	Name : IBaseClientEngine::GetAllClasses
	Returns : void
=========================================== */

ClientClass* IBaseClientEngine::GetAllClasses()
{

	return this->GetFunction< GetAllClassesFn >( this->base, INDEX_BASECLIENTENGINE_GETALLCLASSES )( this->base );

}

/* ========================================
	Name : IBaseClientEngine::GetScreenWidth
	Returns : void
=========================================== */

int IBaseClientEngine::GetScreenWidth()
{

	return this->GetFunction< GetScreenWidthFn >( this->base, INDEX_BASECLIENTENGINE_GETSCREENWIDTH )( this->base );

}

/* ========================================
	Name : IBaseClientEngine::GetScreenHeight
	Returns : void
=========================================== */

int IBaseClientEngine::GetScreenHeight()
{

	return this->GetFunction< GetScreenHeightFn >( this->base, INDEX_BASECLIENTENGINE_GETSCREENHEIGHT )( this->base );

}
