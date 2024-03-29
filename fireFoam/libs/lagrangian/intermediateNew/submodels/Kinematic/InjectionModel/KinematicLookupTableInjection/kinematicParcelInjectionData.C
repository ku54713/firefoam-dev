/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2010-2010 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "kinematicParcelInjectionData.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(kinematicParcelInjectionData, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::kinematicParcelInjectionData::kinematicParcelInjectionData()
:
    x_(point::zero),
    U_(vector::zero),
    d_(0.0),
    rho_(0.0),
    mDot_(0.0)
{}


Foam::kinematicParcelInjectionData::kinematicParcelInjectionData
(
    const dictionary& dict
)
:
    x_(dict.lookup("x")),
    U_(dict.lookup("U")),
    d_(readScalar(dict.lookup("d"))),
    rho_(readScalar(dict.lookup("rho"))),
    mDot_(readScalar(dict.lookup("mDot")))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::kinematicParcelInjectionData::~kinematicParcelInjectionData()
{}


// ************************************************************************* //
