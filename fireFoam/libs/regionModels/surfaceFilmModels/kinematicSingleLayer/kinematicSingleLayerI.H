/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2009-2010 OpenCFD Ltd.
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

#include "surfaceInterpolate.H"
#include "fvcSurfaceIntegrate.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace surfaceFilmModels
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const Switch& kinematicSingleLayer::momentumPredictor() const
{
    return momentumPredictor_;
}


inline label kinematicSingleLayer::nOuterCorr() const
{
    return nOuterCorr_;
}


inline label kinematicSingleLayer::nCorr() const
{
    return nCorr_;
}


inline label kinematicSingleLayer::nNonOrthCorr() const
{
    return nNonOrthCorr_;
}


inline scalar kinematicSingleLayer::Cf() const
{
    return Cf_;
}


inline const volScalarField& kinematicSingleLayer::mu() const
{
    return mu_;
}


inline const volScalarField& kinematicSingleLayer::sigma() const
{
    return sigma_;
}


inline const volScalarField& kinematicSingleLayer::delta() const
{
    return delta_;
}


inline volVectorField& kinematicSingleLayer::USpPrimary()
{
    return USpPrimary_;
}


inline volScalarField& kinematicSingleLayer::pSpPrimary()
{
    return pSpPrimary_;
}


inline volScalarField& kinematicSingleLayer::rhoSpPrimary()
{
    return rhoSpPrimary_;
}


inline volVectorField& kinematicSingleLayer::USp()
{
    return USp_;
}


inline volScalarField& kinematicSingleLayer::pSp()
{
    return pSp_;
}


inline volScalarField& kinematicSingleLayer::rhoSp()
{
    return rhoSp_;
}


inline const volVectorField& kinematicSingleLayer::USp() const
{
    return USp_;
}


inline const volScalarField& kinematicSingleLayer::pSp() const
{
    return pSp_;
}


inline const volScalarField& kinematicSingleLayer::rhoSp() const
{
    return rhoSp_;
}


inline const volVectorField& kinematicSingleLayer::UPrimary() const
{
    return UPrimary_;
}


inline const volScalarField& kinematicSingleLayer::pPrimary() const
{
    return pPrimary_;
}


inline const volScalarField& kinematicSingleLayer::rhoPrimary() const
{
    return rhoPrimary_;
}


inline const volScalarField& kinematicSingleLayer::muPrimary() const
{
    return muPrimary_;
}


inline injectionModelList& kinematicSingleLayer::injection()
{
    return injection_;
}


inline tmp<volScalarField> kinematicSingleLayer::mass() const
{
    return rho_*delta_*magSf();
}


inline tmp<volScalarField> kinematicSingleLayer::netMass() const
{
    dimensionedScalar d0("SMALL", dimLength, ROOTVSMALL);
    return
        fvc::surfaceSum(phi_/(fvc::interpolate(delta_) + d0))*time().deltaT()
      + rho_*delta_*magSf();
}


inline tmp<volScalarField> kinematicSingleLayer::gNorm() const
{
    tmp<volScalarField> tgNorm
    (
        new volScalarField
        (
            IOobject
            (
                "gNorm",
                time().timeName(),
                regionMesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            g_ & nHat(),
            zeroGradientFvPatchScalarField::typeName
        )
    );

    return tgNorm;
}


inline tmp<volScalarField> kinematicSingleLayer::gNormClipped() const
{
    tmp<volScalarField> tgNormClipped
    (
        new volScalarField
        (
            IOobject
            (
                "gNormClipped",
                time().timeName(),
                regionMesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            g_ & nHat(),
            zeroGradientFvPatchScalarField::typeName
        )
    );

    volScalarField& gNormClipped = tgNormClipped();
    gNormClipped.min(0.0);

    return tgNormClipped;
}


inline tmp<volVectorField> kinematicSingleLayer::gTan() const
{
    tmp<volVectorField> tgTan
    (
        new volVectorField
        (
            IOobject
            (
                "gTan",
                time().timeName(),
                regionMesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            g_ - nHat()*gNorm(),
            zeroGradientFvPatchVectorField::typeName
        )
    );

    return tgTan;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace surfaceFilmModels
} // End namespace regionModels
} // End namespace Foam

// ************************************************************************* //
