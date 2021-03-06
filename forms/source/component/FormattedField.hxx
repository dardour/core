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

#ifndef INCLUDED_FORMS_SOURCE_COMPONENT_FORMATTEDFIELD_HXX
#define INCLUDED_FORMS_SOURCE_COMPONENT_FORMATTEDFIELD_HXX

#include "EditBase.hxx"
#include <tools/link.hxx>
#include <comphelper/propmultiplex.hxx>
#include <cppuhelper/implbase1.hxx>
#include "errorbroadcaster.hxx"

struct ImplSVEvent;

namespace frm
{
class OFormattedModel
                    :public OEditBaseModel
                    ,public OErrorBroadcaster
    {
        // the original, in case I faked the format properties of my aggregated model,
        // i.e. I just passed on the attributes of the field to which I am bound
        // (only valid if loaded)

        css::uno::Reference< css::util::XNumberFormatsSupplier>   m_xOriginalFormatter;
        css::util::Date        m_aNullDate;
        css::uno::Any          m_aSaveValue;

        sal_Int32                           m_nFieldType;
        sal_Int16                           m_nKeyType;
        bool                                m_bOriginalNumeric      : 1,
                                            m_bNumeric              : 1;    // analogous for the TreatAsNumeric-property

    protected:
        css::uno::Reference< css::util::XNumberFormatsSupplier>  calcDefaultFormatsSupplier() const;
        css::uno::Reference< css::util::XNumberFormatsSupplier>  calcFormFormatsSupplier() const;
        css::uno::Reference< css::util::XNumberFormatsSupplier>  calcFormatsSupplier() const;

        DECLARE_DEFAULT_LEAF_XTOR( OFormattedModel );

        friend class OFormattedFieldWrapper;

    protected:
        // XInterface
        DECLARE_UNO3_AGG_DEFAULTS( OFormattedModel, OEditBaseModel )

        // XTypeProvider
        virtual css::uno::Sequence< css::uno::Type> _getTypes() SAL_OVERRIDE;

        // XAggregation
        virtual css::uno::Any SAL_CALL queryAggregation(const css::uno::Type& _rType) throw(css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // OComponentHelper
        virtual void SAL_CALL disposing() SAL_OVERRIDE;

        // XServiceInfo
        OUString SAL_CALL getImplementationName()
            throw (css::uno::RuntimeException, std::exception) SAL_OVERRIDE
        { return OUString("com.sun.star.form.OFormattedModel"); }

        virtual css::uno::Sequence<OUString> SAL_CALL getSupportedServiceNames() throw(std::exception) SAL_OVERRIDE;

        // XPersistObject
        virtual void SAL_CALL write(const css::uno::Reference< css::io::XObjectOutputStream>& _rxOutStream) throw ( css::io::IOException, css::uno::RuntimeException, std::exception) SAL_OVERRIDE;
        virtual void SAL_CALL read(const css::uno::Reference< css::io::XObjectInputStream>& _rxInStream) throw ( css::io::IOException, css::uno::RuntimeException, std::exception) SAL_OVERRIDE;
        virtual OUString SAL_CALL getServiceName() throw ( css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // XPropertySet
        virtual void SAL_CALL getFastPropertyValue(css::uno::Any& rValue, sal_Int32 nHandle ) const SAL_OVERRIDE;
        virtual sal_Bool SAL_CALL convertFastPropertyValue(css::uno::Any& rConvertedValue, css::uno::Any& rOldValue,
                                              sal_Int32 nHandle, const css::uno::Any& rValue )
                                            throw(css::lang::IllegalArgumentException) SAL_OVERRIDE;
        virtual void SAL_CALL setFastPropertyValue_NoBroadcast(sal_Int32 nHandle, const css::uno::Any& rValue) throw ( css::uno::Exception, std::exception) SAL_OVERRIDE;

        // XLoadListener
        virtual void SAL_CALL loaded(const css::lang::EventObject& rEvent) throw ( css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // XPropertyState
        void setPropertyToDefaultByHandle(sal_Int32 nHandle) SAL_OVERRIDE;
        css::uno::Any getPropertyDefaultByHandle(sal_Int32 nHandle) const SAL_OVERRIDE;

        void SAL_CALL setPropertyToDefault(const OUString& aPropertyName) throw(css::beans::UnknownPropertyException, css::uno::RuntimeException, std::exception) SAL_OVERRIDE;
        css::uno::Any SAL_CALL getPropertyDefault( const OUString& aPropertyName ) throw(css::beans::UnknownPropertyException, css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // OControlModel's property handling
        virtual void describeFixedProperties(
            css::uno::Sequence< css::beans::Property >& /* [out] */ _rProps
        ) const SAL_OVERRIDE;
        virtual void describeAggregateProperties(
            css::uno::Sequence< css::beans::Property >& /* [out] */ _rAggregateProps
        ) const SAL_OVERRIDE;

        // XPropertyChangeListener
        virtual void _propertyChanged(const css::beans::PropertyChangeEvent& evt) throw(css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // prevent method hiding
        using OEditBaseModel::disposing;
        using OEditBaseModel::getFastPropertyValue;

    protected:
        virtual sal_uInt16 getPersistenceFlags() const SAL_OVERRIDE;
        // as we have an own version handling for persistence

        // OBoundControlModel overridables
        virtual css::uno::Any
                            translateDbColumnToControlValue( ) SAL_OVERRIDE;
        virtual bool        commitControlValueToDbColumn( bool _bPostReset ) SAL_OVERRIDE;

        virtual css::uno::Sequence< css::uno::Type >
                            getSupportedBindingTypes() SAL_OVERRIDE;
        virtual css::uno::Any
                            translateExternalValueToControlValue( const css::uno::Any& _rExternalValue ) const SAL_OVERRIDE;
        virtual css::uno::Any
                            translateControlValueToExternalValue( ) const SAL_OVERRIDE;
        virtual void onConnectedExternalValue( ) SAL_OVERRIDE;

        virtual css::uno::Any
                            getDefaultForReset() const SAL_OVERRIDE;
        virtual void        resetNoBroadcast() SAL_OVERRIDE;

        virtual void        onConnectedDbColumn( const css::uno::Reference< css::uno::XInterface >& _rxForm ) SAL_OVERRIDE;
        virtual void        onDisconnectedDbColumn() SAL_OVERRIDE;

    private:
        virtual css::uno::Reference< css::util::XCloneable > SAL_CALL createClone(  ) throw (css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        void implConstruct();

        void    updateFormatterNullDate();
    };

    typedef ::cppu::ImplHelper1< css::awt::XKeyListener> OFormattedControl_BASE;
    class OFormattedControl :    public OBoundControl
                                ,public OFormattedControl_BASE
    {
        ImplSVEvent * m_nKeyEvent;

    public:
        OFormattedControl(const css::uno::Reference< css::uno::XComponentContext>& _rxContext);
        virtual ~OFormattedControl();

        DECLARE_UNO3_AGG_DEFAULTS(OFormattedControl, OBoundControl)
        virtual css::uno::Any SAL_CALL queryAggregation(const css::uno::Type& _rType) throw(css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        virtual css::uno::Sequence< css::uno::Type> _getTypes() SAL_OVERRIDE;

        // css::lang::XServiceInfo
        OUString SAL_CALL getImplementationName()
            throw (css::uno::RuntimeException, std::exception) SAL_OVERRIDE
        { return OUString("com.sun.star.form.OFormattedControl"); }

        virtual css::uno::Sequence<OUString> SAL_CALL getSupportedServiceNames() throw(std::exception) SAL_OVERRIDE;

        // css::lang::XEventListener
        virtual void SAL_CALL disposing(const css::lang::EventObject& _rSource) throw(css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // css::awt::XKeyListener
        virtual void SAL_CALL keyPressed(const css::awt::KeyEvent& e) throw ( css::uno::RuntimeException, std::exception) SAL_OVERRIDE;
        virtual void SAL_CALL keyReleased(const css::awt::KeyEvent& e) throw ( css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // css::awt::XControl
        virtual void SAL_CALL setDesignMode(sal_Bool bOn) throw ( css::uno::RuntimeException, std::exception) SAL_OVERRIDE;

        // disambiguation
        using OBoundControl::disposing;

    private:
        DECL_LINK_TYPED( OnKeyPressed, void*, void );
    };
}
#endif // INCLUDED_FORMS_SOURCE_COMPONENT_FORMATTEDFIELD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
