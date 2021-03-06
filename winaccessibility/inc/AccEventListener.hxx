/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_WINACCESSIBILITY_INC_ACCEVENTLISTENER_HXX
#define INCLUDED_WINACCESSIBILITY_INC_ACCEVENTLISTENER_HXX

#include <com/sun/star/accessibility/XAccessibleEventListener.hpp>
#include <com/sun/star/accessibility/XAccessible.hpp>

#include <cppuhelper/implbase.hxx>

#include <osl/mutex.hxx>

class AccObjectManagerAgent;

/**
 * AccEventListener is the general event listener for all controls. It defines the
 * procedure of all the event handling and provides the basic support for some simple
 * methods.
 */
class AccEventListener
    : public ::cppu::WeakImplHelper<
        com::sun::star::accessibility::XAccessibleEventListener>
{
protected:
    //accessible owner's pointer
    com::sun::star::uno::Reference<
        com::sun::star::accessibility::XAccessible> m_xAccessible;
    //agent pointer for objects' manager
    AccObjectManagerAgent* pAgent;
public:
    AccEventListener( com::sun::star::accessibility::XAccessible* pAcc, AccObjectManagerAgent* Agent);
    virtual ~AccEventListener();

    // XEventListener
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw (::com::sun::star::uno::RuntimeException);

    // XAccessibleEventListener
    virtual void SAL_CALL notifyEvent( const ::com::sun::star::accessibility::AccessibleEventObject& aEvent ) throw (::com::sun::star::uno::RuntimeException);

    //for name changed event
    virtual void HandleNameChangedEvent(css::uno::Any name);

    //for description changed event
    virtual void HandleDescriptionChangedEvent(css::uno::Any desc);

    //for state changed event
    virtual void HandleStateChangedEvent(
            css::uno::Any oldValue, css::uno::Any newValue);
    virtual void SetComponentState(short state, bool enable);
    virtual void FireStatePropertyChange(short state, bool set);
    virtual void FireStateFocusedChange(bool enable);

    //for bound rect changed event
    virtual void HandleBoundrectChangedEvent();

    //for visible data changed event
    virtual void HandleVisibleDataChangedEvent();

    // get the accessible role of m_xAccessible
    virtual short GetRole();
    //get the accessible parent's role
    virtual short GetParentRole();

    void RemoveMeFromBroadcaster();
};

#endif // INCLUDED_WINACCESSIBILITY_INC_ACCEVENTLISTENER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
