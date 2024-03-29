/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2009 OpenCFD Ltd.
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
    Foam::hPsiMixtureThermoNew

Description
    Foam::hPsiMixtureThermoNew

SourceFiles
    hPsiMixtureThermoNew.C

\*---------------------------------------------------------------------------*/

#ifndef hPsiMixtureThermoNew_H
#define hPsiMixtureThermoNew_H

#include "hCombustionThermo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class hPsiMixtureThermoNew Declaration
\*---------------------------------------------------------------------------*/

template<class MixtureType>
class hPsiMixtureThermoNew
:
    public hCombustionThermo,
    public MixtureType
{
    // Private member functions

        void calculate();

        //- Construct as copy (not implemented)
        hPsiMixtureThermoNew(const hPsiMixtureThermoNew<MixtureType>&);


public:

    //- Runtime type information
    TypeName("hPsiMixtureThermoNew");


    // Constructors

        //- Construct from mesh
        hPsiMixtureThermoNew(const fvMesh&);


    //- Destructor
    virtual ~hPsiMixtureThermoNew();


    // Member functions

        //- Return the compostion of the multi-component mixture
        virtual basicMultiComponentMixtureNew& composition()
        {
            return *this;
        }

        //- Return the compostion of the multi-component mixture
        virtual const basicMultiComponentMixtureNew& composition() const
        {
            return *this;
        }

        //- Update properties
        virtual void correct();

        //- Chemical enthalpy [J/kg]
        virtual tmp<volScalarField> hc() const;


        // Fields derived from thermodynamic state variables

            //- Enthalpy for cell-set [J/kg]
            virtual tmp<scalarField> h
            (
                const scalarField& T,
                const labelList& cells
            ) const;

            //- Enthalpy for patch [J/kg]
            virtual tmp<scalarField> h
            (
                const scalarField& T,
                const label patchi
            ) const;

            //- Heat capacity at constant pressure for patch [J/kg/K]
            virtual tmp<scalarField> Cp
            (
                const scalarField& T,
                const label patchi
            ) const;

            //- Heat capacity at constant pressure [J/kg/K]
            virtual tmp<volScalarField> Cp() const;


        //- Read thermophysicalProperties dictionary
        virtual bool read();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "hPsiMixtureThermoNew.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
