/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2010-2010 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

InClass
    Foam::solidChemistryModel

Description
    Creates solid chemistry model instances templated on the type of
    solid thermodynamics

\*---------------------------------------------------------------------------*/

#include "makeChemistryModel.H"

#include "ODESolidChemistryModel.H"
#include "solidChemistryModel.H"
#include "solidThermoPhysicsTypes.H"
#include "thermoPhysicsTypes.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makeSolidChemistryModel
    (
        ODESolidChemistryModel,
        solidChemistryModel,
        constSolidThermoPhysics,
        gasThermoPhysics
    );

    makeSolidChemistryModel
    (
        ODESolidChemistryModel,
        solidChemistryModel,
        expoSolidThermoPhysics,
        gasThermoPhysics
    );
}

// ************************************************************************* //
