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

Class
    Foam::filmPyrolysisVelocityCoupledFvPatchVectorField

Description
    Velocity boundary condition for patches on the primary region:

    - where the film height > height threshold value:
        apply film surface velocity values
    - else
        apply pyrolysis out-gassing velocity values

SourceFiles
    filmPyrolysisVelocityCoupledFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef filmPyrolysisVelocityCoupledFvPatchVectorField_H
#define filmPyrolysisVelocityCoupledFvPatchVectorField_H

#include "fixedValueFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
       Class filmPyrolysisVelocityCoupledFvPatchVectorField Declaration
\*---------------------------------------------------------------------------*/

class filmPyrolysisVelocityCoupledFvPatchVectorField
:
    public fixedValueFvPatchVectorField
{
    // Private data

        //- Name of flux field
        word phiName_;

        //- Name of density field
        word rhoName_;

        //- Film height threshold beyond which it is considered 'wet'
        scalar deltaWet_;


public:

    //- Runtime type information
    TypeName("filmPyrolysisVelocityCoupled");


    // Constructors

        //- Construct from patch and internal field
        filmPyrolysisVelocityCoupledFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        filmPyrolysisVelocityCoupledFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  filmPyrolysisVelocityCoupledFvPatchVectorField onto a new patch
        filmPyrolysisVelocityCoupledFvPatchVectorField
        (
            const filmPyrolysisVelocityCoupledFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        filmPyrolysisVelocityCoupledFvPatchVectorField
        (
            const filmPyrolysisVelocityCoupledFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new filmPyrolysisVelocityCoupledFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        filmPyrolysisVelocityCoupledFvPatchVectorField
        (
            const filmPyrolysisVelocityCoupledFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new filmPyrolysisVelocityCoupledFvPatchVectorField(*this, iF)
            );
        }


    // Member functions

        // Access

            //- Return the name of phi
            const word& phiName() const
            {
                return phiName_;
            }

            //- Return reference to the name of phi to allow adjustment
            word& phiName()
            {
                return phiName_;
            }

            //- Return the name of rho
            const word& rhoName() const
            {
                return rhoName_;
            }

            //- Return reference to the name of rho to allow adjustment
            word& rhoName()
            {
                return rhoName_;
            }


        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
