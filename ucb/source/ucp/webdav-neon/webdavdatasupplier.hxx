/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef INCLUDED_UCB_SOURCE_UCP_WEBDAV_NEON_WEBDAVDATASUPPLIER_HXX
#define INCLUDED_UCB_SOURCE_UCP_WEBDAV_NEON_WEBDAVDATASUPPLIER_HXX

#include <config_lgpl.h>
#include <memory>
#include <vector>
#include <rtl/ref.hxx>
#include <ucbhelper/resultset.hxx>

namespace webdav_ucp {

struct DataSupplier_Impl;
class Content;

class DataSupplier : public ucbhelper::ResultSetDataSupplier
{
    std::unique_ptr<DataSupplier_Impl> m_pImpl;

private:
    bool getData();

public:
    DataSupplier( const com::sun::star::uno::Reference<
              com::sun::star::uno::XComponentContext >& rxContext,
              const rtl::Reference< Content >& rContent,
              sal_Int32 nOpenMode);

    virtual ~DataSupplier();

    virtual OUString queryContentIdentifierString( sal_uInt32 nIndex ) SAL_OVERRIDE;
    virtual com::sun::star::uno::Reference<
                com::sun::star::ucb::XContentIdentifier >
    queryContentIdentifier( sal_uInt32 nIndex ) SAL_OVERRIDE;
    virtual com::sun::star::uno::Reference< com::sun::star::ucb::XContent >
    queryContent( sal_uInt32 nIndex ) SAL_OVERRIDE;

    virtual bool getResult( sal_uInt32 nIndex ) SAL_OVERRIDE;

    virtual sal_uInt32 totalCount() SAL_OVERRIDE;
    virtual sal_uInt32 currentCount() SAL_OVERRIDE;
    virtual bool isCountFinal() SAL_OVERRIDE;

    virtual com::sun::star::uno::Reference< com::sun::star::sdbc::XRow >
    queryPropertyValues( sal_uInt32 nIndex  ) SAL_OVERRIDE;
    virtual void releasePropertyValues( sal_uInt32 nIndex ) SAL_OVERRIDE;

    virtual void close() SAL_OVERRIDE;

    virtual void validate()
        throw( com::sun::star::ucb::ResultSetException ) SAL_OVERRIDE;
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
