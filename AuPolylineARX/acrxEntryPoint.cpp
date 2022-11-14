// (C) Copyright 2002-2012 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "..\AuPolylineDBX\AuPolyline.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("ADSK")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CAuPolylineARXApp : public AcRxArxApp
{
public:
    CAuPolylineARXApp() : AcRxArxApp() {}

    virtual AcRx::AppRetCode On_kInitAppMsg(void *pkt)
    {
        // TODO: Load dependencies here

        // You *must* call On_kInitAppMsg here
        AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

        // TODO: Add your initialization code here

        return (retCode);
    }

    virtual AcRx::AppRetCode On_kUnloadAppMsg(void *pkt)
    {
        // TODO: Add your code here

        // You *must* call On_kUnloadAppMsg here
        AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

        // TODO: Unload dependencies here

        return (retCode);
    }

    virtual void RegisterServerComponents() {}

    static void ADSKMyGroupAuPolylineCreate()
    {
        // Put your command code here
        // AuPolyline entity Wrap pointer in smartpointer
        auto *pLOrdinaryPointer = new AuPolyline();

        AcDbObjectPointer<AuPolyline> pLs;
        pLs.acquire(pLOrdinaryPointer);

        int    nSides   = 36;
        double incAngle = 2 * 3.141592 / nSides;

        // Add vertex list
        // TODO 优化为 (princ "\nf(x)=A*sin(x)+ Bx : P < x < P+K*(2PI):")
        for (int i = 0; i < nSides; i++)
            // X坐标  i * incAngle
            // Y坐标  sin(i * incAngle)
            pLs->addVertexAt(i, AcGePoint2d(10 * i * incAngle, 10 * sin(i * incAngle)));

        // Set polyline as closed
        pLs->setClosed(Adesk::kFalse);

        // Open the proper entity container
        AcDbBlockTableRecordPointer modelSpace(ACDB_MODEL_SPACE, curDoc()->database(), AcDb::kForWrite);

        // Add the entity to container
        AcDbObjectId Id;
        modelSpace->appendAcDbEntity(Id, pLs);
    }
};

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CAuPolylineARXApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CAuPolylineARXApp, ADSKMyGroup, AuPolylineCreate, AuPLINEBATCH, ACRX_CMD_MODAL, nullptr)