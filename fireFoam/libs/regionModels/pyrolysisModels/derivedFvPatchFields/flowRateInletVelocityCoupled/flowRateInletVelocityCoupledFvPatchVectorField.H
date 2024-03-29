/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2006-2010 OpenCFD Ltd.
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

Class
    Foam::flowRateInletVelocityCoupledFvPatchVectorField

Description
    Describes a volumetric/mass flow normal vector boundary condition by its
    magnitude as an integral over its area.

    The inlet mass flux is taken from the neighbor region.

    phi is used to determine if the flow is compressible or incompressible.

    The basis of the patch (volumetric or mass) is determined by the
    dimensions of the flux, phi.
    The current density is used to correct the velocity when applying the
    mass basis.

    Example of the boundary condition specification:
    @verbatim
    inlet
    {
        type            flowRateInletVelocityCoupled;
        phi             phi;
        rho             rho;
        neigPhi         neigPhiName_;    // Volumetric/mass flow rate [m3/s or kg/s]
        value           uniform (0 0 0); // placeholder
    }
    @endverbatim

Note
    - The value is positive inwards
    - May not work correctly for transonic inlets
    - Strange behaviour with potentialFoam since the U equation is not solved

SourceFiles
    flowRateInletVelocityCoupledFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef flowRateInletVelocityCoupledFvPatchVectorField_H
#define flowRateInletVelocityCoupledFvPatchVectorField_H

#include "fixedValueFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
/*---------------------------------------------------------------------------*\
               Class flowRateInletVelocityFvPatch Declaration
\*---------------------------------------------------------------------------*/

class flowRateInletVelocityCoupledFvPatchVectorField
:
    public fixedValueFvPatchVectorField
{
    // Private data

        //- Name of the neighbor flux setting the inlet mass flux
        word nbrPhiName_;

        //- Name of the local mass flux
        word phiName_;

        //- Name of the density field used to normalize the mass flux
        word rhoName_;


public:

   //- Runtime type information
   TypeName("flowRateInletVelocityCoupled");


   // Constructors

        //- Construct from patch and internal field
        flowRateInletVelocityCoupledFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        flowRateInletVelocityCoupledFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  flowRateInletVelocityCoupledFvPatchVectorField
        //  onto a new patch
        flowRateInletVelocityCoupledFvPatchVectorField
        (
            const flowRateInletVelocityCoupledFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        flowRateInletVelocityCoupledFvPatchVectorField
        (
            const flowRateInletVelocityCoupledFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new flowRateInletVelocityCoupledFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        flowRateInletVelocityCoupledFvPatchVectorField
        (
            const flowRateInletVelocityCoupledFvPatchVectorField&,
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
                new flowRateInletVelocityCoupledFvPatchVectorField(*this, iF)
            );
        }


    // Member functions


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
