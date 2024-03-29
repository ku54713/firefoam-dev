/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2009-2010 OpenCFD Ltd.
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
    Foam::noPyrolysis

Description
    Dummy surface pyrolysis model for 'none'

SourceFiles
    noPyrolysis.C

\*---------------------------------------------------------------------------*/

#ifndef noPyrolysis_H
#define noPyrolysis_H

#include "pyrolysisModel.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace pyrolysisModels
{

/*---------------------------------------------------------------------------*\
                          Class noPyrolysis Declaration
\*---------------------------------------------------------------------------*/

class noPyrolysis
:
    public pyrolysisModel
{
private:

    // Private member functions

        //- Disallow default bitwise copy construct
        noPyrolysis(const noPyrolysis&);

        //- Disallow default bitwise assignment
        void operator=(const noPyrolysis&);


protected:

    // Protected member functions

        //- Read control parameters from dictionary
        virtual bool read();


public:

    //- Runtime type information
    TypeName("none");


    // Constructors

        //- Construct from type name and mesh
        noPyrolysis(const word& modelType, const fvMesh& mesh);


    //- Destructor
    virtual ~noPyrolysis();


    // Member Functions

        // Fields

            //- Return density [kg/m3]
            virtual const volScalarField& rho() const;

            //- Return const temperature [K]
            virtual const volScalarField& T() const;

            //- Return specific heat capacity [J/kg/K]
            virtual const tmp<volScalarField> Cp() const;

            //- Return the region absorptivity [1/m]
            virtual const volScalarField& kappa() const;

            //- Return the region thermal conductivity [W/m/k]
            virtual const volScalarField& K() const;

            //- Return the total gas mass flux to primary region [kg/m2/s]
            virtual const surfaceScalarField& phiGas() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace pyrolysisModels
} // End namespace regionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
