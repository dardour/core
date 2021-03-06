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

#ifndef INCLUDED_CPPCANVAS_SOURCE_WRAPPER_IMPLSPRITE_HXX
#define INCLUDED_CPPCANVAS_SOURCE_WRAPPER_IMPLSPRITE_HXX

#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/rendering/XSpriteCanvas.hpp>
#include <com/sun/star/rendering/XSprite.hpp>
#include <cppcanvas/sprite.hxx>
#include <implspritecanvas.hxx>

namespace cppcanvas
{
    namespace internal
    {
        class ImplSprite : public virtual Sprite
        {
        public:
            ImplSprite( const css::uno::Reference<
                                  css::rendering::XSpriteCanvas >&                    rParentCanvas,
                        const css::uno::Reference<
                                  css::rendering::XSprite >&                          rSprite,
                        const ImplSpriteCanvas::TransformationArbiterSharedPtr&       rTransformArbiter );
            virtual ~ImplSprite();

            virtual void setAlpha( const double& rAlpha ) SAL_OVERRIDE;
            virtual void movePixel( const ::basegfx::B2DPoint& rNewPos ) SAL_OVERRIDE;
            virtual void move( const ::basegfx::B2DPoint& rNewPos ) SAL_OVERRIDE;
            virtual void transform( const ::basegfx::B2DHomMatrix& rMatrix ) SAL_OVERRIDE;
            virtual void setClipPixel( const ::basegfx::B2DPolyPolygon& rClipPoly ) SAL_OVERRIDE;
            virtual void setClip( const ::basegfx::B2DPolyPolygon& rClipPoly ) SAL_OVERRIDE;
            virtual void setClip() SAL_OVERRIDE;

            virtual void show() SAL_OVERRIDE;
            virtual void hide() SAL_OVERRIDE;

            virtual void setPriority( double fPriority ) SAL_OVERRIDE;

            virtual css::uno::Reference<
                css::rendering::XSprite >  getUNOSprite() const SAL_OVERRIDE;

        private:
            ImplSprite(const ImplSprite&) SAL_DELETED_FUNCTION;
            ImplSprite& operator=( const ImplSprite& ) SAL_DELETED_FUNCTION;

            css::uno::Reference< css::rendering::XGraphicDevice >         mxGraphicDevice;
            const css::uno::Reference< css::rendering::XSprite >          mxSprite;
            const css::uno::Reference< css::rendering::XAnimatedSprite >  mxAnimatedSprite;
            ImplSpriteCanvas::TransformationArbiterSharedPtr              mpTransformArbiter;
        };
    }
}

#endif // INCLUDED_CPPCANVAS_SOURCE_WRAPPER_IMPLSPRITE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
